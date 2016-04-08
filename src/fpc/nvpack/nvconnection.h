
#ifndef _NVCONNECTION_H
#define _NVCONNECTION_H


#include "nvobject.h"
#include "nvsocket.h"
#include "nvthread.h"
#include "nvcond.h"
#include <list>

enum NVConnectType{
	BIND,
	CONNECT
};
enum NVConnectMode{
	SYNC,
		ASYN
};

class NVSocketConnection:public NVObject,public virtual NVThread{
public:

public:
	NVSocketConnection();
	virtual ~NVSocketConnection()=0;
	virtual bool SetConnectTimeOut(unsigned short timeout);
	//bool Connect(NVNetAddr);
	virtual void Close();
	virtual bool OnConnected();
	virtual bool OnConnectFailed();
	virtual bool OnDisconnected();	
	virtual void OnDataRecved( NVSocketConnection *connection,NVSocket *socket,NVByte * buff,NVUInt16 len);
	NVSocket * GetSocket();
	void SetSocket(NVSocket*);
	
	virtual NVInt32 Write(NVByte * buff,NVUInt16 len);
	
	NVConnectType GetConnectType();
	void SetConnectType(NVConnectType);
	NVCond*		GetCond(){	return &_cond;}	//add 2006.01.09	
protected:
	NVSocket *		_socket;	
	NVConnectType 	_connect_type;
	NVUInt16 		_timeout;
	NVCond			_cond;
};

class NVTcpConnection;

typedef std::list<NVTcpConnection*> TcpConnection_List;
class NVTcpConnection:public NVSocketConnection{
public:
	NVTcpConnection();
	NVTcpConnection(NVTcpConnection *parent );		
	virtual ~NVTcpConnection();
	bool Connect(NVNetAddr,NVConnectMode mode,NVConnectType type,NVSocketError *error);	
	void 	Run(void *param);
	virtual bool OnConnected();
	virtual bool OnDisconnected();
	virtual bool OnAcceptConnectReqest(NVTcpConnection * connection);
	virtual NVTcpConnection* CreateInBoundConnection();	// add 2006.01.10 scott 创建入内连接类型，通过派生重载可以创建多态的连接类型
protected:	
	TcpConnection_List	_tcpcnn_list;
	NVTcpConnection*	_parent;
};

class NVUdpConnection:public NVSocketConnection{
public:
	NVUdpConnection();	
	virtual ~NVUdpConnection(){}
	bool Connect(NVNetAddr,NVConnectType type,bool run_thread,NVSocketError *error);
	void Run(void *param);
	NVInt32 Write(NVByte * buff,NVUInt16 len);
};


#define NVINLINE inline
#include "nvconnection.ii"


#endif

