

#ifndef _NV_COUNTER_H
#define _NV_COUNTER_H

#include "nvobject.h"

class NVCounter:public NVObject{
public:
	NVCounter( int count =0);	/**< count³õÊ¼Öµ*/
	void SetValue(int v);
	int Inc();
	int Dec();
	int GetValue();	
private:
	int _value;
};

inline
NVCounter::NVCounter( int v){
	_value= v;
}

inline
void NVCounter::SetValue(int v){
	_value = v;
}

inline
int NVCounter::Inc(){
	Lock();
	++_value;
	Unlock();
	return _value;
}

inline
int NVCounter::Dec(){
	Lock();
	--_value;
	Unlock();
	return _value;
}
inline
int NVCounter::GetValue(){
	return  _value;	
}

#endif
