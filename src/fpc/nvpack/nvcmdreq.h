
#ifndef _CMDREQUEST_H
#define _CMDREQUEST_H


/**
	��������������Ӧ��

*/

#include "nvobject.h"
#include "nvthread.h"
#include "nv_vartype.h"
#include "nvcalendar.h"

class NVCmdRequestWaitQueue;
/*
	CmdRequest����һ�����������������
	CmdRequest�������֮���䷢�͵����������ϵͳ��,Ȼ��������CmdRequestWaitQueue,
	�ȴ������ķ���,���ߵȴ���ʱ�Ĳ���.
*/

	/*
		CmdRequest���ڳ�ʱ�ͷ�������ʱ�Ӷ����б����
		�¼�����ʱ���ص������TimeOut()��ResponseBack()����
	*/

class NVCmdRequest{
public:
	virtual ~NVCmdRequest(){};
	virtual void 	TimeOut(){};											//�����Ӧ�ķ���û�з���
	virtual void 	ResponseBack(char * resp_data,unsigned short len){};	//���������Ӧ����ʱ�ص�
	
protected:
	friend class NVCmdRequestWaitQueue;
	unsigned int	_trans_no;						//������
	unsigned int	_expire;
};

typedef std::list<NVCmdRequest*> CmdRequest_List;
//����������,������������ƥ��,��ѯ����Ӧ������,���������ߵ�ResponseBack()������

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







