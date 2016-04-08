
#include "nvlog.h"
#include "nvcalendar.h"
#include "nvsocket.h"

inline 
NVLog::NVLog(int port,char * host,DUMPTYPE dumptype){
	_dumptype = dumptype;
	_destport = port;
	_desthost = host;
	_fd = -1;
}

inline 
NVLog::NVLog(char * logfile,size_t fixsize){
	_fixsize = fixsize;	
	_dumptype= REGFILE;	
	_logfile = logfile;
	_fd = -1;
}
/*
#ifdef WIN32
NVLog::NVLog(char *win_title,bool keep_handle){
	_dumptype= WINDOW;	
	_fd = -1;
}

NVLog::NVLog(HWND hwin){
	_dumptype= WINDOW;	
	_fd = -1;
}
#endif
*/

inline 
NVLog::~NVLog(){
	
}

inline 
void 	NVLog::SetLevel(int level){
	_level = level;
}

inline 
bool 	NVLog::Init(){
	sockaddr_in sa;	
	NVSocket::InitSocket();
	SetLevel();
	SetFormat();
	switch(_dumptype){
		case UDP:
			sa.sin_family = AF_INET;
			sa.sin_port = htons(_destport);
			sa.sin_addr.s_addr = inet_addr(_desthost.c_str());					
			_fd = socket(AF_INET,SOCK_DGRAM,0);
			connect(_fd,(sockaddr*)&sa,sizeof(sa));
			break;
		case TCP:
			break;
		case REGFILE:
			#ifdef _UNIX
				_fd = open(_logfile.c_str(),O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
			#endif
			if(_fd < 0){
				return false;
			}						
			break;
		default:
			return false;
	}
	return true;
}

inline 
bool 	NVLog::DeInit(){	
	if(_dumptype == UDP || _dumptype == TCP){
		#ifdef WIN32
		closesocket(_fd);
		return true;
		#endif			
	}
	close(_fd);
	return true;
}


inline 
void	NVLog::Print(int level,char *fmt,...){
	char *levelname;
	
	//return ;
	va_list marker;	
	
	char buff1[2048],buff2[2048],buff3[1024],buff4[1024*10];
	if( !(level & _level) ){	
		return;	
	}
	va_start(marker,fmt);	
	vsprintf(buff4,fmt,marker);
	va_end(marker); 

	//-- dump out
	switch(_dumptype){
		case UDP:
			send(_fd,buff4,strlen(buff4)+1,0);
			break;
		case TCP:
			break;
		case REGFILE:
			write(_fd,buff4,strlen(buff4));
		default:
			return ;
	}
	return ;

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
	}
	//--format 
	buff2[0]='\0';
	char *pfound;
	char *mark;
	char *format;
	if(_format!=""){
		strcpy(buff2,_format.c_str());
		format = buff2;
		mark = "<LEVEL>";	
		if( (pfound = strstr(format,mark)) ){		
			buff1[0]='\0';
			strcpy(buff1,pfound+strlen(mark));
			(*pfound)='\0';
			strcat(buff2,levelname);
			strcat(buff2,buff1);
		}
		format = buff2;
		mark = "<LINENO>";	
		if( (pfound=strstr(format,mark)) ){		
			buff1[0]='\0';
			strcpy(buff1,pfound+strlen(mark));
			(*pfound)='\0';
			strcat(buff2,"<LINENO>");
			strcat(buff2,buff1);
		}
		format = buff2;
		mark = "<TIME>";	
		if( (pfound=strstr(format,mark))){		
			buff1[0]='\0';
			strcpy(buff1,pfound+strlen(mark));
			(*pfound)='\0';
			strcat(buff2,NVCalendar::GetCurTimeStr().c_str());
			strcat(buff2,buff1);
		}
		format = buff2;
		mark = "<MESSAGE>";	
		if( (pfound=strstr(format,mark)) ){		
			buff1[0]='\0';
			strcpy(buff1,pfound+strlen(mark));
			(*pfound)='\0';
			strcat(buff2,buff3);
			strcat(buff2,buff1);
		}
	}
	if( strlen(buff2) ==0){
		strcat(buff2,buff3);
	}
	//strcat(buff2,"\n");
	//-- dump out
	switch(_dumptype){
		case UDP:
			send(_fd,buff2,strlen(buff2)+1,0);
			break;
		case TCP:
			break;
		case REGFILE:
			write(_fd,buff2,strlen(buff2));
		default:
			return ;
	}
	return ;		
}

inline 
void NVLog::SetFormat(char *format){	
	_format = format;	 // become "%s %s %s"
}

inline 
void NVLog::LogPrint(NVLog * log,int level,char *fmt,...){
	va_list marker;	
	char buff[1024];
	va_start(marker,fmt);
	vsprintf(buff,fmt,marker);
	va_end(marker);
	log->Print(level,fmt);
}


