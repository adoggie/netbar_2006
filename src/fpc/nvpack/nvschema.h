
/*
	NVSchemaObject :		计划执行对象		
	NVSchemaObjectQueue :	计划执行队列
*/

#ifndef _NVSCHEMA_H
#define _NVSCHEMA_H

#include "nvlock.h"
#include "nvthread.h"
#include "nvplat.h"
#include <list>
#include <time.h>

class NVSchemaObjectQueue;

class NVSchemaObject{
public:
	friend class NVSchemaObjectQueue;
	NVSchemaObject();
	void			SetAfterTime(unsigned short after);
	virtual			~NVSchemaObject()=0;	
private:
	unsigned int	GetThatTime();
	unsigned short	GetAfter()	{ return _after;}
protected:
	virtual bool	Execute()=0;		// if return true,indicate that object will be kept in schema_object_queue,or delete it from schema_object_queue
	unsigned short	_after;
	unsigned int	_that_time;
};

inline 
NVSchemaObject::NVSchemaObject(){
}

inline 
void	NVSchemaObject::SetAfterTime(unsigned short after){
	time_t now = time(0);
	_after = after;
	_that_time = now + after;
}

inline 
NVSchemaObject::~NVSchemaObject(){

}


inline 
unsigned int NVSchemaObject::GetThatTime(){
	return _that_time;
}

typedef std::list<NVSchemaObject*> SchemaObject_List;


//////////////////////////////////////////////////////////////////////////

class NVSchemaObjectQueue:public NVThread{
public:
	void Run(void*);
	bool Initialize();
	void Clearup();
	void Enqueue(NVSchemaObject * sobj);
	void Remove(NVSchemaObject * sobj);
protected:
	SchemaObject_List	_schobj_list;
	NVLock				_schobj_lock;

};

inline 
void NVSchemaObjectQueue::Run(void*){
	time_t curt;
	SchemaObject_List::iterator itr,next;
	NVSchemaObject * schobj;
	while(THREAD_CONTINUE_T){
		SLEEP_SEC(1);
		curt = time(0);
		_schobj_lock.Lock();
        int sz = _schobj_list.size();
		for(itr = _schobj_list.begin();itr!= _schobj_list.end();){
			schobj = *itr;
			if( schobj->GetThatTime() <=(unsigned int) curt){
				itr++;
                next = itr;
				itr--;
				if( !schobj->Execute()){
					_schobj_list.erase(itr);
					itr = next;
				}else{
					schobj->SetAfterTime(schobj->GetAfter()); //设置新的触发时间
					itr++;
				}
			}else{
				itr++;
			}			
		}		
		_schobj_lock.Unlock();
	}	
}

inline 
bool NVSchemaObjectQueue::Initialize(){
	return Create();
}

inline 
void NVSchemaObjectQueue::Clearup(){
	Terminate();
	Wait();
}

inline 
void NVSchemaObjectQueue::Enqueue(NVSchemaObject * sobj){
	_schobj_lock.Lock();
	_schobj_list.push_back(sobj);
	_schobj_lock.Unlock();
}

inline 
void NVSchemaObjectQueue::Remove(NVSchemaObject * sobj){
	SchemaObject_List::iterator itr;	
	_schobj_lock.Lock();	
	for( itr = _schobj_list.begin();itr!=_schobj_list.end();itr++){
		if( *itr == sobj){
			_schobj_list.erase(itr);
			break;
		}
	}
	_schobj_lock.Unlock();		
}

#endif
