
#ifndef _NVGUID_H
#define _NVGUID_H

#include "nv_vartype.h"

#ifdef WIN32
#include <winsock.h>
#include <windows.h>
#pragma  comment(lib,"ws2_32.lib")
#endif

#ifdef _UNIX
	#include <unistd.h>
	#include <pthread.h>
	#include <netinet/in.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 
class NVGuid{
public:
	static NVGuid GenerateGuid(){
		NVGuid guid;
		guid.data1 |= rand()<<16;
		guid.data1 |= rand();
		guid.data2 |= rand()<<16;
		guid.data2 |= rand();
		guid.data3 |= rand()<<16;
		guid.data3 |= rand();
		guid.data4 |= rand()<<16;
		guid.data4 |= rand();
		guid.data1 &=~GetProcessId();
		guid.data2 &=~GetThreadId();
	
		
		//guid.string = guid.String();;
		return guid;
	}
	
	bool	GuidEqual(NVGuid *g2){
		return (data1==g2->data1 && 
			data2 == g2->data2 &&
			data3 == g2->data3 &&
			data4 == g2->data4)?true:false;
	}
	
	NVString String( ){
		char guidstr[37];		
		sprintf(guidstr,"%08x-%08x-%08x-%08x",data1,data2,data4,data4);
		return NVString(guidstr);		
	}
	
	
	static unsigned int GetProcessId(){
		unsigned int id;
		#ifdef WIN32
		id = GetCurrentProcessId();
		#else
		id = (unsigned int )getpid();
		#endif
		return id;
	}	
	
	static unsigned int GetThreadId(){
		unsigned int id;
		#ifdef WIN32
		id = GetCurrentThreadId();
		#else
		id = (unsigned int)pthread_self();
		#endif
		return id;
	}
	/*
	void BuffToGuid(char *buff ,NVGUID *guid){
		NVUInt32 val;
		memcpy(&val,buff,4);
		guid->data1 = ntohl(val);
		buff +=4;
		memcpy(&val,buff,4);
		guid->data2 = ntohl(val);
		buff +=4;
		memcpy(&val,buff,4);
		guid->data3 = ntohl(val);
		buff +=4;
		memcpy(&val,buff,4);
		guid->data4 = ntohl(val);
	}*/
public:
	NVUInt32	data1;
	NVUInt32	data2;
	NVUInt32	data3;
	NVUInt32	data4;	
	NVString	string;
};
#endif








