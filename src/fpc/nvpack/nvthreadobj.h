
#ifndef _THREADOBJECT_H
#define _THREADOBJECT_H

/*
	file:	nvthreadobj.h
	class: 	NVThreadObject
	desc:	控制外部线程行为
*/


#include "nvthread.h"

class NVThreadObject:public NVThread{
public:
	void 	Run(void *param){
		_threadproc(param);	
	}
	bool	Create(THREAD_PROC proc,void *param=0){
		_threadproc = proc;
		_param = param;
		return NVThread::Create();
	}
protected:	
	THREAD_PROC	_threadproc;
};
#endif
//--
