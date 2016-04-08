
#ifndef _NVTIMER_H
#define _NVTIMER_H

#include "nv_vartype.h"
#include "nvthread.h"
#include "nvplat.h"

#ifdef WIN32
#include <windows.h>
#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")
#endif

#ifdef _UNIX
#include <sys/socket.h>
#endif


class NVTimer:public NVThread{
public:
	NVTimer(){}
	~NVTimer(){}
	bool Create(unsigned short sec,unsigned short usec);
	void SetInterval(unsigned short sec,unsigned short usec);
	void 	Run(void *param);
	virtual void OnTimerEvent();
private:
	timeval _tv;
};

inline
bool NVTimer::Create(unsigned short sec,unsigned short usec){
	return NVThread::Create();
}

inline 
void NVTimer::SetInterval(unsigned short sec,unsigned short usec){
	_tv.tv_sec = sec;
	_tv.tv_usec = usec;
}

inline 
void NVTimer::Run(void *param){
	while( THREAD_CONTINUE_T ){
		SLEEP_MSEC(_tv.tv_sec*1000+_tv.tv_usec);
		OnTimerEvent();
	}
}
inline
void NVTimer::OnTimerEvent(){
		
}

#endif
