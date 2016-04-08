/*
	超时垃圾对象回收       
	mycop 2005                                                              
	zbin

*/

#ifndef  _NV_WAIT_H
#define  _NV_WAIT_H

#include "nvthread.h"
#include <list>
#include <time.h>

typedef std::list<NVObject*> WaitObject_List ;

class NVWait:public NVThread{
public:	
	enum{
		WAIT_ONE_DAY 	= 86400,
	};
 
	virtual void Start();
	virtual void Stop();
	
	virtual void Run(void *);
	virtual void OnTimeOut(NVObject* object){
		delete object;
	}
	
	void 	AddObject(NVObject *,unsigned int wait_sec=30);
	void	RemoveObject(NVObject * object){
		NVMutexLock lock(_objs_lock);
		_obj_list.remove( object );
	}
	unsigned int	GetQueueSize(){	return _obj_list.size();}
protected:
	Object_List 	_obj_list;
	NVLock			_objs_lock;
};
 

inline 
void NVWait::AddObject(NVObject * object,unsigned int wait_sec){
	object->SetVoid((void*)(time(0)+wait_sec));	
	NVMutexLock lock(_objs_lock);
	_obj_list.push_back(object);

}
inline 
void NVWait::Run(void *){
	unsigned long tv;
	Object_List::iterator cur,next;
	NVObject * object;
	while(THREAD_CONTINUE_T){
		SLEEP_SEC(1);
		NVMutexLock lock(_objs_lock);
		time_t ctm = time(0);
		for( cur =_obj_list.begin();cur!=_obj_list.end();){			
			object = *cur;
			tv = (unsigned long)object->GetVoid();
			if( time(0) > (time_t)tv ){ 
				cur++;
				next = cur;
				cur--;
				OnTimeOut(object);				
				_obj_list.erase(cur);
				cur = next;
			}else{
				cur++;
			}
		}			
	}
}


inline 	void NVWait::Start(){
	Create();
}

inline
void NVWait::Stop(){
	Terminate();
	Wait();
}
#endif

