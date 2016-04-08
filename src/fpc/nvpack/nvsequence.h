
#ifndef _NVSEQUENCE_H
#define _NVSEQUENCE_H

#include "nvlock.h"
typedef unsigned int NVSequenceValue;

class NVSequence:public NVObject{
public:
	NVSequence(){
		_from = 1;
		_to = 0xfff0;
	}
	void Range(NVSequenceValue from,NVSequenceValue to);
	NVSequenceValue		Next();
private:	
	NVSequenceValue 	_value,_from,_to;
	NVLock				_lock_v;
	
};

inline 
void NVSequence::Range(NVSequenceValue from,NVSequenceValue to){
	_from = from;
	_to = to;	
}

inline 
NVSequenceValue	NVSequence::Next(){	
	NVMutexLock lock(_lock_v);	
	if( _value == _to ){
		_value = _from;
	}else{
		_value++;
	}	
	return _value;
}


#endif
