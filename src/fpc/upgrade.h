
/*
	desc:	fpc 系统自动升级模块
			fpc将查找 system32/fpc.conf中cms的指向，连接cms并检查fpc当前版本，发现版本差异则下载最新模块
			重写版本记录到注册表

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


