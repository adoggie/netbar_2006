

#include "nvthread.h"

inline  
NVThread::NVThread(){
	_where = TAIL;
	_status = STOP;
	
}
inline  
NVThread::~NVThread(){
}

inline  
bool NVThread::Create(void *param){
	bool ret;
	NVCreateThead(_thrhand,NVThread::NewThread,this,ret);
	if( ret){ //--线程创建成功，等待线程运行状态改变
		while( GetStatus()!=NVThread::RUNNING){
			SLEEP_MSEC(100);
		}
	}
	return ret;
}

inline 
void NVThread::Terminate(){
	_status = STOP;
}

inline 
void * NVThread::NewThread(void *param){
	NVThread *thread = (NVThread *)param;
	THREAD_START(*thread);
	thread->Run(thread->_param);
	THREAD_END(*thread);
	return 0;
}

inline 
void NVThread::Run(void *param){
/*	while(THREAD_CONTINUE(*this)){
		Sleep(100);
	}	*/
}

inline 
void NVThread::Wait(){
	while(GetWhere()!=TAIL){
		SLEEP_MSEC(100);
	}
}

inline 
NVThread::STATUS NVThread::GetStatus(){
	return _status;
}

inline 
void NVThread::SetStatus(STATUS status){
	_status = status;
}

inline 
NVThread::WHERE NVThread::GetWhere(){
	return _where;
}

inline 
void NVThread::SetWhere(WHERE where){
	_where = where;
}



