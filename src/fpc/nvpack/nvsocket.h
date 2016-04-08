
#ifndef _NVSOCKET_H
#define  _NVSOCKET_H

#include "nvaddr.h"


#define NV_INVALIDE_SOCKET -1

#ifdef WIN32
#define NVCLOSESOCKET(s)	shutdown(s,2);\
							closesocket(s);\
							s=NV_INVALIDE_SOCKET;
#endif							

#ifdef _UNIX
#define NVCLOSESOCKET(s)	shutdown(s,SHUT_RDWR);\
							close(s);\
							s=NV_INVALIDE_SOCKET;
#endif							


enum NVSOCKETTYPE{
	NVDGRAM=SOCK_DGRAM,
	NVSTREAM=SOCK_STREAM
};

typedef int 	NVSocketHandle;	
typedef int		NVSocketError;

#define ESocket_Bind_Another	1001	//端口已经被占用

/**
	NVSocket 定义socket基本形式
*/

class NVSocketConnection ;

class NVSocket:public NVObject{
public:
	NVSocket();
	virtual ~NVSocket();
	virtual bool Create()=0;
	virtual void Destroy();
	/**
		读取socket数据，如果要获取发送方的ip信息就必须提供addr
	*/
	virtual int Read(char *buff ,unsigned int len,NVNetAddr *)=0;
	virtual int Write(char *buff,unsigned int len)=0;
	NVSocketHandle & GetSocketHandle();	
	void SetSocketHandle(NVSocketHandle);
	NVNetAddr *GetNetAddr();
	void SetNetAddr(NVNetAddr *);	
	NVSocketConnection *GetSocketConnection();
	void SetSocketConnection(NVSocketConnection *);
	
	/**
	设置socket是否是非阻塞模式。\n
	socket	句柄\n
	block	是否阻塞
	*/
	static bool SetSocketBlock(NVSocketHandle socket,bool block);
	/**设置socket关闭时是否延时关闭*/
	static bool SetLinger(NVSocketHandle socket,bool linger);
	
	static bool SetAddressReuse(NVSocketHandle socket);	//add on 2005.05.29 scott

	/**初始化winsock[win32]*/
	static bool InitSocket();
	static bool DeInitSocket();
	virtual bool Connect(NVNetAddr *addr);
	NVSOCKETTYPE GetSocketType();	
protected:
	NVSocketHandle _socket;
	NVSocketConnection *_connection;
	NVSOCKETTYPE	_socket_type;
	NVNetAddr	_naddr;
};

inline NVSocket::NVSocket(){
	_connection = NVNULL;
	_socket = -1;
}
inline
NVSocket::~NVSocket(){
	
}

inline
bool NVSocket::Connect(NVNetAddr *addr){
	int ret;
	ret = connect(_socket,(sockaddr*)addr->GetSockAddr(),sizeof(sockaddr));
	return ret==0?true:false;
}

inline NVSocketHandle &NVSocket::GetSocketHandle(){
	return _socket;	
}

inline 
void NVSocket::SetSocketHandle(NVSocketHandle socket){
	_socket = socket;
}

inline
NVNetAddr *NVSocket::GetNetAddr(){
	return &_naddr;
}

inline
void NVSocket::SetNetAddr(NVNetAddr *naddr){
	_naddr = *naddr;
}

inline
NVSocketConnection *NVSocket::GetSocketConnection(){
	return _connection;
}

inline
void NVSocket::SetSocketConnection(NVSocketConnection * connection){
	_connection = connection;
}

#ifdef _UNIX
inline
bool NVSocket::SetSocketBlock(NVSocketHandle socket,bool block){
	int ret;
    int flags = fcntl(socket, F_GETFL, 0);    
    if (flags == -1){
        return false;
    }    
    if(!block){
		flags |=O_NONBLOCK;    	
    }else{
		flags &=~O_NONBLOCK;
    }
    ret = fcntl(socket, F_SETFL, flags);    
    return ret!=0 ?false:true;	
}
#endif 


#ifdef WIN32


inline
bool NVSocket::SetSocketBlock(NVSocketHandle socket,bool block){
    unsigned long yes =block?0:1;    
	return ioctlsocket(socket,FIONBIO,&yes)==0?true:false;
}
#endif

inline
bool NVSocket::SetAddressReuse(NVSocketHandle socket){
	int rc = -1;
	int opt;
	int optsize;
	opt = 1;
	optsize = sizeof(opt);

#ifdef WIN32
	rc = setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, optsize);
#else
	rc = setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &opt, optsize);
#endif
	if (rc < 0)
		return false;

	return true;
}


inline
NVSOCKETTYPE NVSocket::GetSocketType(){
	return _socket_type;
}

inline
void NVSocket::Destroy(){
	NVCLOSESOCKET(_socket);
}

inline 
bool NVSocket::InitSocket(){
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
	return true;
}

inline 
bool NVSocket::DeInitSocket(){
#ifdef WIN32
	WSACleanup();
#endif	
	return true;
}

//--------------------------------------------------------------------------

class NVUdpSocket:public NVSocket{
public:
	NVUdpSocket(){;}
	bool Create(){
		int sock;
		sock = (int)socket(AF_INET,NVDGRAM,0);
		if( sock < 0){
			return false;
		}
		_socket = sock;
		_socket_type = NVDGRAM;
		return true;
	}
	/**读取等待超时,addr将返回发送者的地址信息*/
	int ReadTimeOut(char *buff ,unsigned int len,unsigned short  time_sec,NVNetAddr * addr=NVNULL);	
	int Read(char *buff ,unsigned int len,NVNetAddr * addr=NVNULL);
	int Write(char *buff,unsigned int len);
	static int WriteTo(NVNetAddr * addr,char *buff,unsigned int len);
	/**在指定端口范围只能查找空闲的端口邦定，并通过which返回邦定的端口号，socket返回句柄*/
	static bool BindRange(unsigned short from,unsigned short end,unsigned short *which,NVSocketHandle * socket);	
	/**socket返回创建的句柄*/
	static bool Bind(unsigned short port,NVSocketHandle * socket);	
};

inline 
bool NVUdpSocket::BindRange(unsigned short from,unsigned short end,unsigned short *which,NVSocketHandle * socket){
	unsigned short n;
	for(n = from ;n<=end;n++){
		if( Bind(n,socket)){
			*which = n;
			return true;
		}
	}
	return false;
}

inline
bool NVUdpSocket::Bind(unsigned short port,NVSocketHandle * hsocket){
	NVNetAddr addr;
	int ret;
	ret= socket(AF_INET,SOCK_DGRAM,0);
	if( ret < 0){
		return false;
	}
	addr.SetNetAddr(NVUInt32(0),htons(port));
	
	if( bind(ret,(sockaddr*)addr.GetSockAddr(),sizeof(sockaddr))){
		NVCLOSESOCKET(ret);
		return false;
	}
	*hsocket = ret;
	return true;
}

inline 
int NVUdpSocket::Read(char *buff ,unsigned int len,NVNetAddr * addr){
	int ret;
	NVNetAddr naddr;

	SOCKLEN socklen;
	socklen = sizeof(sockaddr);
	ret = recvfrom(_socket,buff,len,0,(sockaddr*)naddr.GetSockAddr(),&socklen);	
	if( addr){
		*addr = naddr;
	}
	return ret;
}

inline
int NVUdpSocket::ReadTimeOut(char *buff ,unsigned int len,unsigned short  time_sec,NVNetAddr * addr){
	int ret;
	NVNetAddr naddr;
	timeval tv;
	fd_set rset;
	SOCKLEN socklen;
	socklen = sizeof(sockaddr);
	tv.tv_sec = time_sec;
	tv.tv_usec =0;
	
	FD_ZERO(&rset);
	FD_SET(_socket,&rset);
	ret = select(_socket+1,&rset,0,0,&tv);
	if(ret <=0 ){
		return -1;
	}
	ret = recvfrom(_socket,buff,len,0,(sockaddr*)naddr.GetSockAddr(),&socklen);	
	if( addr){
		*addr = naddr;
	}
	return ret;
	
}

inline
int NVUdpSocket::Write(char *buff,unsigned int len){
	int ret;
	Lock();
	ret = send(_socket,buff,len,0);
	Unlock();
	return ret;
}

//--UPD server while it as binding server,don't send data on its socket
inline
int NVUdpSocket::WriteTo(NVNetAddr * addr,char *buff,unsigned int len){
	int sock,ret;
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if( sock < 0) return -1;
	ret = sendto(sock,buff,len,0,(sockaddr*)addr->GetSockAddr(),sizeof(sockaddr));
	NVCLOSESOCKET(sock);
	return ret;
}

class NVTcpSocket:public NVSocket{
public:
	bool Create(){
		int sock;
		sock = socket(AF_INET,NVSTREAM,0);
		if( sock < 0){
			return false;
		}
		_socket = sock;
		_socket_type = NVSTREAM;
		return true;
	}
	int Read(char *buff ,unsigned int len,NVNetAddr *);
	int Write(char *buff,unsigned int len);
//	NVNetAddr * GetPeerAddr();
public:
//	NVNetAddr	_peeraddr;;
};

inline 
int NVTcpSocket::Read(char *buff ,unsigned int len,NVNetAddr * addr){	
	return recv(_socket,buff,len,0);	
}

inline
int NVTcpSocket::Write(char *buff,unsigned int len){
	int ret;
	int left;
	left = len;	
	Lock();
	while(left>0){
		ret = send(_socket,buff,left,0);
		if(ret<=0){
			Unlock();
			return -1;			
		}
		left-=ret;
		buff+=ret;
	}	
	Unlock();
	return len;
}

inline
bool NVSocket::SetLinger(NVSocketHandle socket,bool linger){
	struct linger l;
	l.l_onoff=0;
	l.l_linger=0;
	if(linger)	l.l_onoff = 1;
	return setsockopt(socket,SOL_SOCKET,SO_LINGER,(char*)&l,sizeof(linger))==0? true:false;
}


#endif 
