/*
	file: nvobject.h
	desc:
	histroy:	
		2006.01.01 	scott 增加引用计数字段

*/

#ifndef  _NVOBJECT
#define  _NVOBJECT
#include "nvlock.h"

class NVObject{	
public:
	//NVString ToString();
	NVObject();
	virtual ~NVObject(){}
	void Lock();
	void Unlock();	
	void SetVoid(void *pv);
	void *GetVoid();
	
	void AddRef(){	NVMutexLock lock(_ref_lock);
					_ref++;					
				}
	void DecRef(){	NVMutexLock lock(_ref_lock);
					_ref--;
				}
	int	 GetRefCount(){	return _ref;}	
protected:
	int	_ref;		//引用计数
	void *_pvoid;
	NVLock _lock;
	NVLock _ref_lock;
};
typedef std::list<NVObject*>	Object_List;

 
inline 
NVObject::NVObject(){
	_pvoid =0;
	_ref = 0;
}

inline
void NVObject::Lock(){
	_lock.Lock();
}

inline
void NVObject::Unlock(){
	_lock.Unlock();
}

inline
void NVObject::SetVoid(void *pv){
	_pvoid = pv;
}

inline
void *NVObject::GetVoid(){
	return _pvoid;
}

#endif
