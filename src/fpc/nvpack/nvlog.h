
/*
	nvlog.h
	----------------
	application logger
	2003.10 	created		scott	
	2005.09.10	rebuild		scott
				created RegFileWriter,UdpWriter,WindowWriter to distinguish log data type
	2005.09.22	modified RegFileWriter::RegFileWriter()	scott
	2005.11.10	scott 	add __FILE__,__LINE__
*/

#ifndef _NVLOG
#define _NVLOG

#ifdef _UNIX
 #include <unistd.h>
 #include <signal.h>
 #include <sys/socket.h>
 #include <fcntl.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
#endif

#ifdef WIN32
 #include <windows.h>
#include <winsock.h>
#include <io.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdarg.h>
#include <vector>
#include <algorithm>

#include "nvlock.h"
#include "nvcalendar.h"

class NVLog{
public:
	enum WriterType{
		UDP,	
		REGFILE,
		WINDOW,
		UNKNOWN
	};

	class LogWriter{
	public:
		LogWriter(){
			_type = UNKNOWN;
		}
		
		virtual ~LogWriter(){

		}

		virtual int 	Write(const char * data,unsigned int len){
			return 0;
		}
		virtual bool	Open(){
			return true;
		}
		virtual void	Close(){			
		}

		WriterType	GetType(){
			return _type;
		}
	protected:
		WriterType	_type;
	};
	#ifdef WIN32
	class WindowWriter:public LogWriter{
	public:

		virtual int 	Write(const char * data,unsigned int len){
			if( _refind){
				return Write2(_win_title.c_str(),data,len);
			}
			return SendMessageToWindow(_hwnd,data,len);
		}

		int 	Write2(const char * wintitle,const char * data,unsigned int len){			
			HWND hwnd = FindWindow(0,wintitle);
			len = SendMessageToWindow(hwnd,data,len);
		//	CloseHandle(hwnd);
			return len;
		}

		virtual bool	Open(){
			if( _refind){		//需要发送时发现 
				return true;
			}
			_hwnd = FindWindow(0,_win_title.c_str());
			if( !_hwnd){
				//MessageBox(NULL,"cannot find window",_win_title.c_str(),MB_OK);
				return false;
			}
			return true;
		}
		virtual void	Close(){
			if( _hwnd ){
				//CloseHandle(_hwnd);
			}

		}

		WindowWriter(const char * wintitle,bool refind=false){
			_win_title = wintitle;
			_hwnd = NULL;
			_type = WINDOW;
			_refind = refind;
		}

	protected:
		int SendMessageToWindow(HWND hwnd ,const char * data,unsigned int len){
			if( hwnd == NULL){
				return 0;
			}
			COPYDATASTRUCT cds;
			cds.lpData =(void*)data;
			cds.cbData = len;
			SendMessage(hwnd,WM_COPYDATA ,(UINT)hwnd,(long)&cds);
			return len;
		}
	private:
		std::string		_win_title;
		HWND			_hwnd;
		bool			_refind;
	};
	#endif
	
	class RegFileWriter:public LogWriter{
	public:
		typedef void (*OnReachedMaxFileSizeCB)(std::string &file);
		RegFileWriter(const char * file){
			_cb_maxsize = NULL;
			_fp = NULL ;
			_file = file;
			_type = REGFILE;
			_cur_size = 0;
			SetMaxFileSize();
		}
		virtual void OnReachedMaxFileSize(){
			Close();
			Open();
		}
		//void SetRoundTime(unsigned int round_time);	//达到指定时间循环到文件头部		
		void SetMaxFileSize(unsigned int max_size = 1024*1024*2,OnReachedMaxFileSizeCB cb=NULL){
			_max_size = max_size;
			_cb_maxsize = cb;
			
		}
		virtual bool	Open(){
			_fp = fopen(_file.c_str(),"w");
			if( !_fp){
				return false;
			}
			//fseek(fp,0,SEEK_END);
			_cur_size = 0;//ftell(fp);
			return true;
		}

		virtual int 	Write(const char * data,unsigned int len){
			int ret;
			if( _cur_size >= _max_size){
				OnReachedMaxFileSize();
			}
			if( _fp == NULL){
				return -1;
			}
			ret = fwrite(data,len,1,_fp);
			fflush(_fp);
			_cur_size += len;
			return len;
		}

		void	Close(){
			if( _fp ){
				fclose(_fp);
			}
			_fp = NULL;			
		}
		
	private:
		unsigned int _cur_size,_max_size;
		OnReachedMaxFileSizeCB	_cb_maxsize;
		
		FILE * 		_fp;
		std::string _file;
	};
	class Socket{
	public:
		Socket(){
			_sock = -1;
		}
		

	protected:
		std::string		_host;
		unsigned short	_port;
		int	_sock;
	};
	class UdpWriter:public Socket,public LogWriter{
	public:

		~UdpWriter(){
			Close();
		}

		UdpWriter(const char * dest,unsigned short port){
			_host =  dest;
			_port =  port;
			_type =  UDP;
		}
		
		virtual int 	Write(const char * data,unsigned int len){
			if( _sock < 0 ){
				return 0;
			}
			return send(_sock,data,len,0);
		}

		virtual bool	Open(){
			sockaddr_in sa;	
			#ifdef WIN32
			WORD wVersionRequested;
			WSADATA wsaData;
			int err; 
			wVersionRequested = MAKEWORD( 2, 2 );
			err = WSAStartup( wVersionRequested, &wsaData );
			if ( err != 0 ) {
				return false;
			}
			#endif
			sa.sin_family = AF_INET;
			sa.sin_port = htons(_port);
			sa.sin_addr.s_addr = inet_addr(_host.c_str());					
			_sock = socket(AF_INET,SOCK_DGRAM,0);
			if( _sock <0  ){
				return false;
			}
			connect(_sock,(sockaddr*)&sa,sizeof(sa));
			return true;
		}

		virtual void	Close(){
			if( _sock >= 0 ){
#ifdef  WIN32
				closesocket (_sock);
#endif
#ifdef _UNIX
				close(_sock);
#endif
				_sock = -1;
			}
		}
	};


	enum LEVEL{
		LOG_ERROR 	=0x01,		
		LOG_WARNING =0x02,
		LOG_MESSAGE =0x04,
		LOG_DEBUG	=0x08,
		LOG_ALL	=LOG_ERROR|LOG_WARNING|LOG_MESSAGE|LOG_DEBUG
	};		

	bool 	SetWriter(LogWriter * w){
		_writer_lock.Lock();
		_writer_list.push_back(w);
		_writer_lock.Unlock();
		return true;
	}

	void	RemoveWriter(LogWriter*w){
		std::vector<LogWriter* >::iterator itr;
		_writer_lock.Lock();
		itr = std::find(_writer_list.begin(),_writer_list.end(),w);
		if(itr != _writer_list.end()){
			_writer_list.erase(itr);
		}
		_writer_lock.Unlock();
	}

	NVLog(){
		SetFormat();
		SetLevel();
	}
	~NVLog(){

	}

	void 	SetLevel(int level = LOG_ERROR|LOG_WARNING|LOG_MESSAGE|LOG_DEBUG){
		_level = level;
	}
	#define LOG_MAX_BUFF_SIZE 1024*40
	void	Error(const char * fmt,...){
		va_list marker;		
		//char buff[LOG_MAX_BUFF_SIZE];
		char * buff = new char[LOG_MAX_BUFF_SIZE];
		if( !buff ) {
			return;
		}		
		va_start(marker,fmt);	
		vsprintf(buff,fmt,marker);
		va_end(marker); 
		PrintString(LOG_ERROR,buff);
		delete [] buff ;
	}
	void	Debug(const char * fmt,...){
		va_list marker;		
		char * buff = new char[LOG_MAX_BUFF_SIZE];
		if( !buff ) {
			return;
		}
		va_start(marker,fmt);	
		vsprintf(buff,fmt,marker);
		va_end(marker); 
		PrintString(LOG_DEBUG,buff);
		delete [] buff ;
	}
	void	Warning(const char * fmt,...){
		va_list marker;		
		char * buff = new char[LOG_MAX_BUFF_SIZE];
		if( !buff ) {
			return;
		}
		va_start(marker,fmt);	
		vsprintf(buff,fmt,marker);
		va_end(marker); 
		PrintString(LOG_WARNING,buff);
		delete [] buff ;
	}
	void	Message(const char * fmt,...){
		va_list marker;		
		char * buff = new char[LOG_MAX_BUFF_SIZE];
		if( !buff ) {
			return;
		}
		va_start(marker,fmt);	
		vsprintf(buff,fmt,marker);
		va_end(marker); 
		PrintString(LOG_MESSAGE,buff);
		delete [] buff ;
	}
	void	Print(int level,const char * fmt,...){
		va_list marker;		
		char * buff = new char[LOG_MAX_BUFF_SIZE];
		if( !buff ) {
			return;
		}
		va_start(marker,fmt);	
		vsprintf(buff,fmt,marker);
		va_end(marker); 
		PrintString(level,buff);
		delete [] buff ;
	}

	void	SetFormat(const char *format="<TIME>\t<LEVEL>\t<MESSAGE>\n"){
		_format = format;
	}
private:
	void	PrintString(int level,const char * data);
private:
	std::vector<LogWriter* > _writer_list;
	NVLock					_writer_lock;
	std::string				_format;	// "<LOGLEVEL><LINENO><TIME><MESSAGE>\n"
	unsigned int 			_level;
};

inline 
void	NVLog::PrintString(int level,const char * data){
	char *levelname;	
	if( !(level & _level) ){	
		return;	
	}
	
	switch(level){
		case LOG_ERROR:
			levelname = "ERROR";
			break;
		case LOG_WARNING:
			levelname = "WARNING";
			break;
		case LOG_MESSAGE:
			levelname = "MESSAGE";
			break;
		case LOG_DEBUG:
			levelname = "DEBUG";
			break;
		default:
			return;
	}
	if( _format == "" ){
		return ;
	}
	
	std::string format;
	char * mark;
	char * occur;
	format = _format;
	mark = "<LEVEL>";
	int len;
	len = strlen(mark);
	if( occur = (char*)strstr( format.c_str(),(const char*)mark) ) {
		format.replace( occur-format.c_str(),len,levelname);
	}
	mark = "<TIME>";
	len = strlen(mark);
	if( occur = (char*)strstr( format.c_str(),(const char*)mark) ) {
		format.replace( occur-format.c_str(),len,NVCalendar::GetCurTimeStr().c_str());
	}
	mark = "<MESSAGE>";
	len = strlen(mark);
	if( occur = (char*)strstr( format.c_str(),mark) ) {
		format.replace( occur-format.c_str(),len,data);
	}
	std::vector<LogWriter* >::iterator itr;
	_writer_lock.Lock();
	for( itr= _writer_list.begin();itr!=_writer_list.end();itr++){
		(*itr)->Write(format.c_str(),format.size());
	}	
	_writer_lock.Unlock();
}



#define NVLOG_ADD_UDP_WRITER(log,host,port)	\
					NVLog::UdpWriter * w = new NVLog::UdpWriter(host,port);\
					w->Open();\
					(log).SetWriter(w);

#endif

