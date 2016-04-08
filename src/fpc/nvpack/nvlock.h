

#ifndef _NVLOCK_H
#define _NVLOCK_H

#ifdef WIN32
	#include "nvlock_win.h"
#endif
#ifdef _UNIX
	#include "nvlock_unix.h"
#endif

class NVMutexLock{
public:
	NVMutexLock(NVLock & lock):_lock(lock){
		_lock.Lock();

	}
	~NVMutexLock(){
		_lock.Unlock();
	}
	NVLock&	_lock;
}; 
#endif
