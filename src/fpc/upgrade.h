
/*
	desc:	fpc ϵͳ�Զ�����ģ��
			fpc������ system32/fpc.conf��cms��ָ������cms�����fpc��ǰ�汾�����ְ汾��������������ģ��
			��д�汾��¼��ע���

*/

#ifndef _SYS_UPGRADE_H
#define _SYS_UPGRADE_H

#include <ice/ice.h>
#include "nvpack/nv.h"
#include "mps.h"
using namespace MPMS;
class SystemSync:public Ice::Application{
public:
	SystemSync(NVLog * log);
	int run(int, char**);
private:
	NVLog *		_log ;
	NVDll		_dll;
};


#endif


