
#ifndef _CMDREQUEST_H
#define _CMDREQUEST_H


/**
	处理命令的请求和应答

*/

#include "nvobject.h"
#include "nvthread.h"
#include "nv_vartype.h"
#include "nvcalendar.h"

class NVCmdRequestWaitQueue;
/*
	CmdRequest描述一次网络命令请求操作
	CmdRequest请求产生之后将其发送到网络的其他系统端,然后将其置入CmdRequestWaitQueue,
	等待反馈的返回,或者等待超时的产生.
*/

	/*
		CmdRequest将在超时和反馈返回时从队列中被清除
		事件产生时将回调对象的TimeOut()和ResponseBack()处理
	*/

class NVCmdRequest{
public:
	virtual ~NVCmdRequest(){};
	virtual void 	TimeOut(){};											//请求对应的反馈没有返回
	virtual void 	ResponseBack(char * resp_data,unsigned short len){};	//当请求的响应返回时回调
	
protected:
	friend class NVCmdRequestWaitQueue;
	unsigned int	_trans_no;						//事务编号
	unsigned int	_expire;
};

typedef std::list<NVCmdRequest*> CmdRequest_List;
//反馈报到达,进行请求对象的匹配,查询到对应的请求,调用请求者的ResponseBack()处理函数

/**
	CmdRequestWaitQueue
*/
class NVCmdRequestWaitQueue:public NVThread{
public:
	void 		ResponseBack(unsigned int trans_no,char * resp_data,unsigned short len);
	void 		EnQueue(NVCmdRequest*,unsigned int trans_no,unsigned short wait_sec);
	void		EraseElement(NVCmdRequest*);
	bool		Start();
	void		Stop();
protected:
	void		Run(void*);	
	CmdRequest_List _request_list;
	NVLock			_lock_reqs;
};

inline 
void		NVCmdRequestWaitQueue::EraseElement(NVCmdRequest* req){
	CmdRequest_List::iterator itr;
	_lock_reqs.Lock();
	for(itr = _request_list.begin();itr!=_request_list.end();itr++){
		if( req == *itr){
			_request_list.erase(itr);
			_lock_reqs.Unlock();		
			return ;
		}
	}
	_lock_reqs.Unlock();
}

inline 
void NVCmdRequestWaitQueue::ResponseBack(unsigned int trans_no,char * resp_data,unsigned short len){
	CmdRequest_List::iterator itr;
	NVCmdRequest * req;
	_lock_reqs.Lock();
	for(itr = _request_list.begin();itr!=_request_list.end();itr++){
		req = *itr;
		if( req->_trans_no == trans_no){
			_request_list.erase(itr);
			_lock_reqs.Unlock();
			req->ResponseBack(resp_data,len);
			return;
		}
		
	}
	_lock_reqs.Unlock();
}

inline 
void NVCmdRequestWaitQueue::EnQueue(NVCmdRequest* req,unsigned int trans_no,unsigned short wait_sec){	

	if( !(THREAD_CONTINUE_T))	return;	
	
	req->_trans_no = trans_no;
	req->_expire = NVCalendar::GetTimeStamp()+wait_sec;
	_lock_reqs.Lock();
	_request_list.push_back(req);
	_lock_reqs.Unlock();	
}

inline 
bool NVCmdRequestWaitQueue::Start(){
	return NVThread::Create();
}

inline 
void NVCmdRequestWaitQueue::Stop(){
	NVThread::Terminate();
	NVThread::Wait();
}

inline
void NVCmdRequestWaitQueue::Run(void*){
	CmdRequest_List::iterator itr;
	NVCmdRequest * req;
	bool conti;
	while(THREAD_CONTINUE_T){
		SLEEP_SEC(1);
		conti = true;
		_lock_reqs.Lock();
		for(itr = _request_list.begin();itr!=_request_list.end();itr++){
			req = *itr;
			if( req->_expire < NVCalendar::GetTimeStamp()){
				_request_list.erase(itr);
				_lock_reqs.Unlock();
				req->TimeOut();
				conti = false;
				break;
			}
		}
		if( conti)
			_lock_reqs.Unlock();
	}

	_lock_reqs.Lock();
	for(itr = _request_list.begin();itr!=_request_list.end();itr++){
		req = *itr;
		req->TimeOut();
	}
	_lock_reqs.Unlock();	
}
#endif







