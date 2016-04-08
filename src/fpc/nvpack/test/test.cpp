// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../nvthread.h"
#include "../nv.h"
#include "../nvxml.h"
#include "../nvdll.h"

//#include <msgCSS.h>

#include <stdio.h>
#include <conio.h>

#include <windows.h>
#include "../nvconnection.h"
#include "iconv.h"

XML_Func		NVXmlTree::_xmlf={0};

class schemaA:public NVSchemaObject{
public:
	bool	Execute(){
		printf("\nSchema Object Execute!");
		return true;
	}
};


class Server:public NVTcpConnection{
	void OnDataRecved( NVSocketConnection *connection,NVSocket *socket,NVByte * buff,NVUInt16 len){
		printf("\nrecv data:%s",buff);
	}
	bool OnAcceptConnectReqest(NVTcpConnection * connection){
		printf("\n client request : %s",connection->GetSocket()->GetNetAddr()->GetIP().c_str());
		return true;
	}
	bool OnSubConnectionDisconnected(NVTcpConnection*){
		printf("\n client disconnect! ");
		return true;
	}
};
typedef NVTcpConnection Client;
NVCmdRequestWaitQueue queue;
NVCounter cnt;
NVCodec codec;


int main(int argc, char* argv[])
{
	NVXmlConfigSet cset;
	
	NVDll dll;	
	schemaA sa;
	/*
	NVSchemaObjectQueue schqueue;
	schqueue.Initialize();
	sa.SetAfterTime(5);
	schqueue.Enqueue(&sa);
	while(1){
		SLEEP_SEC(1);
	}

	cnt.Inc();*/
	NVUTF8 utf8 ;
	NVGB2312 gb;
	


	dll.LoadDll("libexpat.dll");
	
	XML_Func xmlf;
	Init_XmlFnc(&NVXmlTree::_xmlf,&dll);
//	tree.SetXML_Func(xmlf);
	


	char buff[1024*100];
//	unsigned short len;
	int ret;
	/*
	for(int n=0;n<1000000;n++){	
		MessageMediaRecordRequest mrr,*pmrr;
		mrr.Create();
		pmrr = (MessageMediaRecordRequest*) MessagePacket::Analyse(mrr._data,mrr._len);
		SLEEP_MSEC(200);
		delete pmrr;
		printf("\nTesting %d",n);
	}*/

	
//	printf("\n %s",a->GetValue()->c_str());
	dll.FreeDll();
	/*
	memset(buff,0,sizeof(buff));
	NVXmlAttr *a;
	a = tree.GetRootNode()->GetFirstAttr();
	NVXmlTreeNode *n,*r;
	n = tree.GetRootNode()->GetFirstNode();
	r = tree.GetRootNode();
	printf("\nA:%d,N:%d",tree.GetRootNode()->GetAttrCount(),tree.GetRootNode()->GetChildNodeCount());
	printf("\n name:%s",r->GetName()->c_str());
	int deep;
	deep=2;
	n = r->SearchNode("ROWDATA",&deep);
	if(n){
		n = n->GetFirstNode();
		while(n){
			printf("\n%s=%s",n->GetFirstAttr()->GetName()->c_str(),
								n->GetFirstAttr()->GetValue()->c_str());
			n = n->GetNext();
		}
	}*/
//	r = r->GetParent();
//	unsigned int size ;
//	size = 0;
  //	r->CalcBufferSize(&size);
//	char *allocbuff = new char[size+1];
//	memset(allocbuff,0,size+1);
//	r->ToXMLBuffer(allocbuff,size+1);
//	exit(0);

//	Sleep(2000);
	getch();
	
	
	
	
	return 0;
}

