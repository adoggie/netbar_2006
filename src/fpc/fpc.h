

#ifndef _FPC_H
#define _FPC_H

#include "base.h"
#include "monitor.h"
#include "mps.h"
#include <ice/application.h>
class Monitor;
using namespace MPMS;

class MainApp;
extern MainApp* mainapp;
#define MAINLOG mainapp->GetLog()

class fpcI:public FrontPlayController{
public:
	fpcI();
	void ChangeSetting(const fpcSetting&, const ::Ice::Current& ) ;
	::std::string GetType(const ::Ice::Current&);
	fpcParameter GetParameter(const ::Ice::Current& );
};


/*Ç°¶Ë²¥·Å¿ØÖÆÆ÷*/
class MainApp:public Ice::Application{
public:	
	MainApp();
	int		run(int, char*[]);
	void 	EventTrigger(std::string evType);
	FrontDispatchControllerPrx&	GetServerProxy(){	return _fdcPrx;}
	NVLog&	GetLog(){	return _log;}
	void	ChangeSettings(fpcSetting settings);
	DWORD	_thread_id;
protected:	
	bool	Initial();
	void	Uninitial();
	bool	ConnectServer();	
	static void ReportPlayEvent(PlayTraits*);

	void	SyncSettings();
	class WorkThread:public NVThread{
	public:
		void	Run(void*){
			while( THREAD_CONTINUE_T){
				mainapp->SyncSettings();
				SLEEP_SEC(10);
			}
		}
	};

private:
	Monitor_List	_mon_list;
	NVLock			_mon_lock;
	NVLog			_log;
	FrontPlayControllerPrx			_fpcPrx;
	NVLock						_fdc_lock;
	FrontDispatchControllerPrx	_fdcPrx;
	CentreMangementSystemPrx	_cmsPrx;
	std::string					_server_type;
	NVDll						_dll_dulex;
	NVDll						_dll_hook;
	DeluxProc					_proc_dulex;
	fpcSetting					_cur_settings;
	UINT						_timer_settings;
	HookProcs					_hook_proc;
	WorkThread					_wthread;
	fdcParameter				_fdcparam;
	

};


#endif



