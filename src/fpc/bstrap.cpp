// bstrap.cpp : 定义控制台应用程序的入口点。
// serivce 中显示窗体，必须创建服务类型中设置为 "允许服务与桌面交互" 可以通过安装软件进行设置
#include <Windows.h>
#include <Winsvc.h>
#include "base.h"
#include "nvpack/nv.h"
#include <ice/ice.h>
#include "upgrade.h"

#define FPC_SERVICE_NAME "mpms.fpc"

void OnUserLogin(){
	HANDLE  hevent = OpenEvent(EVENT_ALL_ACCESS,FALSE,SIGNAL_SYSLOGIN);
	if( !hevent ){
		;//MessageBox(0,"FPC is not existed!","warning",MB_OK);
	}else{
		SetEvent(hevent);
	}
}

//-------------------------------------------------------------
NVLog	syslog;
bool	running = false;
NVDll	dll_main;
int		(*dll_fpc_start)();
void	(*dll_fpc_stop)();

//系统同步
void fpc_sync(){
	SystemSync sync_app(&syslog);
	//sysnc_app(0,NULL,(Util::GetSystemDir()+"/fpc.conf").c_str());	
	sync_app.main(0,NULL,"fpc.conf");	

}

bool fpc_ready(){	
	/*
	fpc_sync();
	running = true;
	if( !dll_main.LoadDll("fpcmain.dll")){
		syslog.Debug("load fpc main.dll failed!");
		return false ;
	}
	dll_fpc_start = (int (*)())dll_main.LoadSymbol("fpc_start");
	dll_fpc_stop = (void (*)())dll_main.LoadSymbol("fpc_stop");
	if( !dll_fpc_start || !dll_fpc_stop ){
		syslog.Debug(" load symbol in main.dll failed!");
		return false;
	}*/
	
	return true ;
}

#include "nvpack/nv.h"
void fpc_start(){	
	/*
	if( !fpc_ready() ){
		return;
	}
	dll_fpc_start();		*/
	NVDll						_dll_dulex;

	if( !_dll_dulex.LoadDll("dulex.dll")){
	//	_log.Error("Load Dll dulex.dll failed!");
		return ;
	}
	DeluxProc					_proc_dulex;
	_proc_dulex.PlayMedia =(PlayMediaT)_dll_dulex.LoadSymbol("_PlayMedia");
	_proc_dulex.ParamConfig =(ParamConfigT)_dll_dulex.LoadSymbol("_ParamConfig");
//	_proc_dulex.ParamConfig();
	running = true;
	//MessageBox(0,"service hwnd test","",MB_OK);
	while(running){
		SLEEP_MSEC(200);
	}
}

void fpc_stop(){	
	running = false;
	//dll_fpc_stop();	//命令模块系统停止运行退出	
}


//---------------------------------------------------------------
SERVICE_STATUS_HANDLE ssh;


BOOL SendStatusToSCM (DWORD dwCurrentState,
					  DWORD dwWin32ExitCode,
					  DWORD dwServiceSpecificExitCode,
					  DWORD dwCheckPoint,
					  DWORD dwWaitHint)
{
	BOOL success;
	SERVICE_STATUS serviceStatus;

	// Fill in all of the SERVICE_STATUS fields
	serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	serviceStatus.dwCurrentState = dwCurrentState;

	// If in the process of doing something, then accept
	// no control events, else accept anything
	if (dwCurrentState == SERVICE_START_PENDING)
		serviceStatus.dwControlsAccepted = 0;
	else
		serviceStatus.dwControlsAccepted =
		SERVICE_ACCEPT_STOP |
		SERVICE_ACCEPT_PAUSE_CONTINUE |
		SERVICE_ACCEPT_SHUTDOWN;

	// if a specific exit code is defined, set up
	// the win32 exit code properly
	if (dwServiceSpecificExitCode == 0)
		serviceStatus.dwWin32ExitCode = dwWin32ExitCode;
	else
		serviceStatus.dwWin32ExitCode =
		ERROR_SERVICE_SPECIFIC_ERROR;
	serviceStatus.dwServiceSpecificExitCode =
		dwServiceSpecificExitCode;

	serviceStatus.dwCheckPoint = dwCheckPoint;
	serviceStatus.dwWaitHint = dwWaitHint;

	// Pass the status record to the SCM
	success = SetServiceStatus (ssh,&serviceStatus);
	return success;
}

//服务不支持 pause和continue,即便接收此信号也忽略
//
void  fpc_CtrlHandler(DWORD fdwControl ){
//	DWORD status; 
//	SERVICE_STATUS ss;
	DWORD currentState = 0;
    switch(fdwControl) 
    { 
        case SERVICE_CONTROL_PAUSE:                     
			currentState = SERVICE_PAUSED;
			syslog.Debug("SERVICE_CONTROL_PAUSE");       	            
            break; 
 
        case SERVICE_CONTROL_CONTINUE: 
			running = true;
			syslog.Debug("SERVICE_CONTROL_CONTINUE");       	            
			currentState = SERVICE_RUNNING;
            break; 
 
        case SERVICE_CONTROL_STOP:  
			SendStatusToSCM(SERVICE_STOPPED,0,0,1,5000);
			syslog.Debug("SERVICE_CONTROL_STOP");           
			fpc_stop();
            return; 
        case SERVICE_CONTROL_INTERROGATE:         
            break; 
        default: ;
    }      
    
	SendStatusToSCM(currentState, NO_ERROR, 0, 0, 0);
    return; 
}



void fpc_ServiceMain(DWORD argc, char** argv){
	SERVICE_STATUS ss;
	NVLog::LogWriter * w = new NVLog::WindowWriter("bstrap",true);
	w->Open();
	syslog.SetWriter(w);	
	w = new NVLog::UdpWriter("127.0.0.1",5001);	
	w->Open();
	syslog.SetWriter(w);	

	syslog.Debug("fpc_ServiceMain()");
	ssh = RegisterServiceCtrlHandler(FPC_SERVICE_NAME,( LPHANDLER_FUNCTION)fpc_CtrlHandler);
	if( !ssh ){		
		syslog.Debug("启动mpms.fpc服务失败!");
		return ;
	}
	SendStatusToSCM(SERVICE_START_PENDING,NO_ERROR, 0, 1, 15000);
	SetServiceStatus(ssh,&ss);
	//fpc_start();
	SendStatusToSCM(SERVICE_RUNNING,NO_ERROR, 0, 0, 0);
	fpc_start();
	SendStatusToSCM(SERVICE_STOPPED, 0,0, 0, 0);	
	syslog.Debug("程序即将退出");
	
}

bool fpc_CreateService(char * servic_name,char* service_desc,char * service_exe){
	SC_HANDLE  scm,news;
	bool ret = false;
	scm = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);
	if (!scm) {
		return ret;
	}
	// Install the new service
	news = CreateService(scm,  servic_name,service_desc,SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS ,
		SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,service_exe,0, 0, 0, 0, 0);
	if (news){
		ret = true;
	}
	CloseServiceHandle(news);
	CloseServiceHandle(scm);
	return ret;
}

bool fpc_DeleteService(char * servic_name){
	SC_HANDLE service, scm;
	BOOL success;
	SERVICE_STATUS status;
//	bool ret;

	scm = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);
	if (!scm){
		return false;
	}
	
	service = OpenService(scm, servic_name,SERVICE_ALL_ACCESS | DELETE);
	if (!service) {
		return false;
	}

	// Stop the service if necessary
	success = QueryServiceStatus(service, &status);
	if (!success) {
		return false;
	}

	if (status.dwCurrentState != SERVICE_STOPPED)
	{
		printf("\nStopping service...");
		success = ControlService(service,SERVICE_CONTROL_STOP, &status);
		if (!success) {
			printf("\nservice terminate failed!");
			return false;
		}
	}
	success = DeleteService(service);
	CloseServiceHandle(service);
	CloseServiceHandle(scm);
	return true;
}


int main(int argc, char** argv)
{
	//MessageBox(0,"service hwnd test","",MB_OK);

	//-- signal notification
	for( int i=1;i<argc;i++){
		if ( argv[i] == std::string("-login") ){
			OnUserLogin();
			return 0;
		}
		if( argv[i] == std::string("-install")){
			fpc_CreateService(FPC_SERVICE_NAME,"front play controllor","c:/bin/fpcsvc.exe");			
			return 0;
		}
		if( argv[i] == std::string("-uninstall") ){
			fpc_DeleteService(FPC_SERVICE_NAME);
			return 0;
		}
	}
	SERVICE_TABLE_ENTRY ServiceTable[2]={ {FPC_SERVICE_NAME,(LPSERVICE_MAIN_FUNCTION)fpc_ServiceMain},{NULL,NULL} };
	StartServiceCtrlDispatcher(ServiceTable);
	/*
	while(running){
		SLEEP_MSEC(100);
	}*/
	return 0;
}

