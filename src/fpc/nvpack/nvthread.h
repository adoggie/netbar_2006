
#ifndef _THREAD_H
#define _THREAD_H

#include "nv_vartype.h"
#include "nvplat.h"

#ifdef WIN32
#include <windows.h>
typedef HANDLE NVHANDLE;

#define NVCreateThead(handle,proc,param,bret) {\
												DWORD thrid;\
												handle = CreateThread(0,0,(LPTHREAD_START_ROUTINE)proc,(void*)param,0,&thrid);\
												bret  = true;\
											  }
#define THREAD_DETACH

#endif

#ifdef _UNIX
typedef pthread_t NVHANDLE;

#define NVCreateThead(handle,proc,param,bret)	{\
												 int ret;\
												 ret= pthread_create(&handle,0,proc,param);\
												 bret= (ret!=0)?false:true;\
												}
#define THREAD_DETACH			pthread_detach(pthread_self());
#endif


typedef void *(*THREAD_PROC)(void *param);


class NVThread{
public:
	enum STATUS{
		RUNNING,
		STOP
	};
	enum WHERE{
		HEAD,
		TAIL
	};
	NVThread();
	~NVThread();	
	bool		Create(void *param=0);
	void		Terminate();
	void		Wait();
	STATUS 		GetStatus();
	void 		SetStatus(STATUS status);
	WHERE 		GetWhere();
	void 		SetWhere(WHERE where);
	static void * 	NewThread(void *);
	virtual void 	Run(void *param);
protected:	
	NVHANDLE	_thrhand;
	STATUS		_status;
	WHERE		_where;
	void *		_param;
	void *		_void;
};

#define  THREAD_START(t)	(t).SetStatus(RUNNING); (t).SetWhere(HEAD);
#define  THREAD_END(t)	(t).SetStatus(STOP); (t).SetWhere(TAIL);THREAD_DETACH;
#define  THREAD_CONTINUE(t) ((t).GetStatus()== NVThread::RUNNING)?true:false

#define THREAD_START_T	THREAD_START(*this)
#define THREAD_END_T	THREAD_END(*this)
#define THREAD_CONTINUE_T THREAD_CONTINUE(*this)



#include "nvthread.i"

#endif
//--
