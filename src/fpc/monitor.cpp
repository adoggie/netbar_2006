
#include "monitor.h"
#include "fpc.h"

Monitor::Monitor(){
	_msleep = 200;
	_last = false;
}

void Monitor::SetInterval(int msleep){
	_msleep = msleep;
}

void Monitor::Run(void*){
	bool now;
	while(THREAD_CONTINUE(*this)){
		SLEEP_MSEC(_msleep);
		
		now= IsTriggered();
		if( now ){
			if( !_last){
				mainapp->EventTrigger(this->Type());	
				_last = now;
			}
		}else{
			_last = now;
		}
		
		
	}
	
}

void	Monitor::Start(){
	Create();
	return void();
}
void	Monitor::Stop(){
	Terminate();
	Wait();
	return void();
}



MsnMonitor::MsnMonitor(){
	_type = "msn";		
}

bool MsnMonitor::IsTriggered(){
  	HWND hwnd;
    if( hwnd=FindWindow(0,"MSN Messenger")){
        HMENU hm = GetMenu(hwnd);
        if( hm ){    
            hm = GetSubMenu(hm,0);
            MENUINFO  mi;
            mi.cbSize = sizeof(mi);            
            SendMessage(hwnd,WM_INITMENUPOPUP,(WPARAM)hm,1);
            if( !( GetMenuState(hm,1,MF_BYPOSITION) & MF_GRAYED) ){
                return true;                
            }
        }
    }
    return false;
}

QQMonitor::QQMonitor(){
	_type = "qq";
}


 

BOOL CALLBACK QQMonitor::enumproc(HWND hwnd,LPARAM lParam ){
    char str[1256];
   GetClassName(hwnd,str,sizeof(str));
    HWND hchild;
	
    QQMonitor * m = (QQMonitor*)lParam;
	if( std::string(str) ==  "#32770"){
		
        hchild = GetWindow( hwnd,GW_CHILD );
        while( hchild ){
           
			GetClassName(hchild,str,sizeof(str));
            if( std::string(str) == "Tencent_QQBar"){
                //ShowMessage(" found QQ ");
                m->_found = true;
                return false;
            }
            hchild = GetWindow( hchild,GW_HWNDNEXT );
        }
    }
    return true;
}


bool QQMonitor::IsTriggered(){
	_found = false;
	EnumWindows( (WNDENUMPROC )QQMonitor::enumproc,(LPARAM)this);	
	return _found;	
}


SysLoginMonitor::SysLoginMonitor(){
	_type="login";
}

void	SysLoginMonitor::Run(void*){
	HANDLE hd = CreateEvent(NULL,FALSE,FALSE,SIGNAL_SYSLOGIN);
	while(THREAD_CONTINUE(*this)){
		WaitForSingleObject( hd, INFINITE );
		mainapp->EventTrigger(this->Type());
	}
	CloseHandle(hd);
}

void SysLoginMonitor::SignalLogin(){
	HANDLE  hevent = OpenEvent(EVENT_ALL_ACCESS,FALSE,SIGNAL_SYSLOGIN);
	if( !hevent ){
		MessageBox(0,"FPC is not existed!","warning",MB_OK);
	}else{
		SetEvent(hevent);
	}
}

void SysLoginMonitor::Stop(){
	Terminate();
	SignalLogin();
	Monitor::Stop();
}