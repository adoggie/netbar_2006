
/**
	�������ģ��
*/

#include "nvthread.h"
#include "nv.h"

class NVProcess:public NVObject{
public:
	NVProcess();
	~NVProcess();
	bool NVCreateThread();
	bool NVTerminateThread();	
public:
		
};
