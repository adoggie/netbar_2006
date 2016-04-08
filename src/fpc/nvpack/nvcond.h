/*
	file: nvcond.h
	updated 2005.11.26	scott

*/
#ifndef _NV_CONDITION_H
#define _NV_CONDITION_H
#include "nv_vartype.h"
#include "nvplat.h"
#ifdef _UNIX
// simulate Event object on win32 platform 
class NVCond{
public:
	NVCond(){
		pthread_mutex_init(&_mtx_obj, NULL);
		pthread_cond_init(&_cond_obj,0);
		_signal = false;
	}
	~NVCond(){
		pthread_cond_destroy(&_cond_obj);
		pthread_mutex_destroy(&_mtx_obj);
	}
	/*if no signal,will be blocked*/
	void Wait(){
		if( !_signal ) {
			pthread_cond_wait(&_cond_obj,&_mtx_obj);
		}
	}
	
	void Signal(bool s ){
		_signal= s;
		if( _signal ){
			pthread_cond_signal(&_cond_obj);
		}
	}
	
	void NotifyAll(){
		pthread_cond_broadcast(&_cond_obj);
	}
private:
	pthread_cond_t  _cond_obj;
	pthread_mutex_t _mtx_obj;
	bool			_signal;
};

#endif

#ifdef WIN32
#include <windows.h>

class NVCond{
public:
	NVCond(){
		_event = CreateEvent(NULL,true,FALSE,NULL);
	}
	
	~NVCond(){
		CloseHandle(_event);
	}
	void Wait(){
		//ResetEvent(_event);
		WaitForSingleObject(_event,INFINITE);
	}
	
	void Signal(bool s ){
		if( s ){
			SetEvent(_event);
		}else{
			ResetEvent(_event);
		}
	}
	
	void NotifyAll(){
		//-- not supported yet
	}
private:
	HANDLE _event;
};

#endif

#endif
//-- end file



