

#ifndef _NVLOCK_WIN_H
#define _NVLOCK_WIN_H

#include <windows.h>

class NVLock{	
public:
	NVLock(){
		InitializeCriticalSection(&_mtx_obj);
	}
	~NVLock(){
		DeleteCriticalSection(&_mtx_obj);
	}
	void Lock(){
		EnterCriticalSection(&_mtx_obj);
	}
	void Unlock(){
		LeaveCriticalSection(&_mtx_obj);
	}
	bool TryLock(){
		//if(TryEnterCriticalSection(&_mtx_obj)){
		//	return true;
		//}
		return false;
	}
private:
	CRITICAL_SECTION _mtx_obj;
};

#endif
