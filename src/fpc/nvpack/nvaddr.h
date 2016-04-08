
#ifndef _NVADDR_H
#define _NVADDR_H

#include "nv_vartype.h"

#include <stdio.h>

#ifdef _UNIX
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

typedef socklen_t SOCKLEN ;
#endif

#ifdef WIN32
#include <windows.h>
#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")
typedef int SOCKLEN;
#endif


class  NVNetAddr{
public:
	NVNetAddr();
	NVNetAddr(const char *host,unsigned short port);
	NVNetAddr(unsigned int naddr,unsigned short nport);
	
	NVNetAddr(sockaddr_in *saddr);		
	sockaddr_in *GetSockAddr();
	in_addr	*GetInAddr();
	void SetNetAddr(const char *host,unsigned short port);
	void SetNetAddr(unsigned int naddr,unsigned short nport);
	NVString GetIP();
	NVString GetPort();
//	NVUInt32 GetIP();
	//NVUInt16 GetPort();
	
public:
	sockaddr_in _saddr;	
};

inline 
NVNetAddr::NVNetAddr(){

}

inline 
NVNetAddr::NVNetAddr(sockaddr_in *saddr){
	_saddr = *saddr;
}

inline 
NVNetAddr::NVNetAddr(const char *host,unsigned short port){
	SetNetAddr(host,port);
}
inline
NVNetAddr::NVNetAddr(unsigned int naddr,unsigned short nport){
	SetNetAddr(naddr,nport);
}

inline 
void NVNetAddr::SetNetAddr(const char *host,unsigned short port){
	_saddr.sin_addr.s_addr = inet_addr(host);
	_saddr.sin_port=htons(port);
	_saddr.sin_family = AF_INET;
}

inline
void NVNetAddr::SetNetAddr(unsigned int naddr,unsigned short nport){
	_saddr.sin_addr.s_addr = naddr;
	_saddr.sin_port=nport;
	_saddr.sin_family = AF_INET;	
	
}


inline
sockaddr_in *NVNetAddr::GetSockAddr(){
	return &_saddr;
}

inline
in_addr	*NVNetAddr::GetInAddr(){
	return &_saddr.sin_addr;
}

inline	
NVString NVNetAddr::GetIP(){
	in_addr *in;
	in = GetInAddr();
	return inet_ntoa(*in);
}

inline
NVString NVNetAddr::GetPort(){
	char buff[12];
	sprintf(buff,"%d",ntohs(_saddr.sin_port));
	return (NVString)buff;
}
/*
inline
NVUInt32 NVNetAddr::GetIP(){	
	return NVInt32(NVNetAddr::htonl((NVUInt32)_saddr.sin_addr.s_addr));
}

inline
NVUInt16 NVNetAddr::GetPort(){
	return NVInt16(NVNetAddr::htons((NVUInt16)_saddr.sin_port));	
}*/

/*
inline
static NVUInt32 NVNetAddr::htonl(NVUInt32 v){
	return htonl((long)v);
}
inline
static NVUInt16 NVNetAddr::htons(NVUInt16 v){
	return htons((short)v);
}


*/
#endif
