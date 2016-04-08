/*
	超时垃圾对象回收       
	mycop 2005                                                              
	zbin
	2005.01.01	scott	
		1.回收机制从超时回收改为引用回收

*/

#ifndef  _NVGARBAGE_COLL_H
#define _NVGARBAGE_COLL_H

#include "nvthread.h"
#include <list>
#include <time.h>

typedef std::list<NVObject*> GARBAGE_LIST;

class 	NVGarbageCollector:public NVThread{
public:
	NVGarbageCollector();
	void Start();
	void Stop();
	void DumpIn(NVObject *);
	virtual void 	Run(void *);
	unsigned int	GetQueueSize(){	return _obj_list.size();}
protected:
	Object_List 	_obj_list;
	NVLock			_objs_lock;
};

inline NVGarbageCollector::NVGarbageCollector(){

}

inline 
void NVGarbageCollector::DumpIn(NVObject * object){
	NVMutexLock lock(_objs_lock);
	_obj_list.push_back(object);
}

inline 
void NVGarbageCollector::Run(void *){

	Object_List::iterator cur,next;
	NVObject * object;
	while(THREAD_CONTINUE_T){
		SLEEP_SEC(1);
		NVMutexLock lock(_objs_lock);
		for( cur =_obj_list.begin();cur!=_obj_list.end();){			
			object = *cur;
			bool candel = false;
			object->Lock();
			if( object->GetRefCount() == 0 ){
				candel = true;
			}
			object->Unlock();
			if( candel ){ 
				cur++;
				next = cur;
				cur--;
				delete object;			
				_obj_list.erase(cur);
				cur = next;
			}else{
				cur++;
			}			
		}
	}
}


inline 	void NVGarbageCollector::Start(){
	Create();
}

inline
void NVGarbageCollector::Stop(){
	Object_List::iterator cur,next;
	NVObject * object;

	Terminate();
	Wait();
	for( cur =_obj_list.begin();cur!=_obj_list.end();cur++){			
		object = *cur;
		delete object;
	}
}
#endif

