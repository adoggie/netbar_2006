

#ifndef _NVLOCK_UNIX_H
#define _NVLOCK_UNIX_H

#include <pthread.h>
#include <unistd.h>

class NVLock{	
public:
	NVLock(){
		pthread_mutex_init(&_mtx_obj, NULL);
	}
	~NVLock(){
		pthread_mutex_destroy(&_mtx_obj);
	}
	void Lock(){
		pthread_mutex_lock(&_mtx_obj); 
	}
	
	void Unlock(){
		pthread_mutex_unlock(&_mtx_obj);
	}
	
	bool TryLock(){
		if(pthread_mutex_trylock(&_mtx_obj)==0){
			return true;
		}
		return false;
	}
private:
	pthread_mutex_t _mtx_obj;
};

#endif
