/*
	file:	nvarray.h
	desc:	
		array helper,auto free resource while exiting scope
*/
#ifndef _NVARRAY_H
#define _NVARRAY_H

template <class T>
class NVArray{
	T * 	_t;
	unsigned int _size;
public:
	template <class T>
	NVArray(unsigned int size){
		_t =  new T(size);
		if( _t ){
			_size = size;
		}
	}
	template <class T>
	~NVArray(){
		if( _t ){
			delete[] _t;
		}
	}
	template <class T>	
	T *	get(){	return _t;}
	template <class T>	
	unsigned int	size(){	return _size;}
};

#endif



