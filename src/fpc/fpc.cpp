
/*
revision:
	2006.05.12	scott fpcSettings增加 ieToolbar变量，ChangeSetting时将ieToolbar的url写入注册表，待toolbar运行读取
				toolbar点击之后应该产生通知到cms。 通过hook.dll共享内存的方式toolbar.ocx将通知消息存入hook.dll,然后
				调用hook.dll的通知函数发送消息到fpc接收主线程
	2006.06.15	scott
				1. 播放之后的上报处理方式采用回调方式，在用户关闭播放窗体时回调到主程序中进行发送播放信息
	2006.06.25	scott
				1. 修改与fpcdulex的数据交互模式，采用回调方式产生问题(bcb与vc堆栈模式差异导致程序异常)，现在
					的方式是fpcore产生playtrait,当dulex回放完成时通知fpcore来释放内存
				2. 实现整个功能流程

*/

#include "fpc.h"
#include "util.h"
#include "hook/hook.h"
MainApp* mainapp;
#include <algorithm>
#include <functional>


MainApp::MainApp(){
	mainapp = this;
	_timer_settings = NULL;
}

bool	MainApp::Initial(){
	
	NVLog::WindowWriter * w = new NVLog::WindowWriter("fpc",true);
	w->Open();
	_log.SetWriter(w);
	_thread_id = GetCurrentThreadId();
	if( !_dll_dulex.LoadDll("fpcdulex.dll")){
		_log.Error("Load Dll fpcdulex.dll failed!");
		return false;
	}
	if( !_dll_hook.LoadDll("fpchook.dll")){
		_log.Error("Load Dll fpchook.dll failed!");
		return false;
	}
	_proc_dulex.PlayMedia =(PlayMediaT)_dll_dulex.LoadSymbol("_PlayMedia");
	_proc_dulex.ParamConfig =(ParamConfigT)_dll_dulex.LoadSymbol("_ParamConfig");
	_hook_proc.UnSet = (UnSet_T)_dll_hook.LoadSymbol("UnSet");
	_hook_proc.IeToolbar_Clicked = (IeToolbar_Clicked_T)_dll_hook.LoadSymbol("IeToolbar_Clicked");
	_hook_proc.SetCaptureKey = (SetCaptureKey_T)_dll_hook.LoadSymbol("SetCaptureKey");
	_hook_proc.SetCaptureKey(WM_FPC_CONFIG,GetCurrentThreadId(),VK_F12,1,1,1);
	//--
	if(!_proc_dulex.PlayMedia || !_proc_dulex.ParamConfig ){
		return false;
	}
	//-- register three monitor ,let's run up!
	_mon_list.push_back( new MsnMonitor);
	_mon_list.push_back( new QQMonitor);
//	_mon_list.push_back( new SysLoginMonitor);
	std::for_each(_mon_list.begin(),_mon_list.end(),std::mem_fun(&Monitor::Start));
	//--如果开启了settings_update_interval参数则启动定时器

	return true;
}

void MainApp::Uninitial(){
	if( _timer_settings ){
		KillTimer( 0,_timer_settings);
	}
}

int MainApp::run(int, char*[]){
	Initial();
	Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("fpc");	
	Ice::ObjectPrx fpc = adapter->add(new fpcI,Ice::stringToIdentity("fpc sevant"));	
	_fpcPrx = FrontPlayControllerPrx::uncheckedCast(fpc);
	//-- connect fdc or cms
	ConnectServer();
	_wthread.Create();
	MSG msg;
	while( GetMessage(&msg,0,0,0)){
		if ( msg.message == WM_FPC_CONFIG){
			_log.Debug("catched system configure signal");
			//--
			_proc_dulex.ParamConfig(GetCurrentThreadId(),WM_FPC_CONFIG_CHANGED);
		}else if( msg.message == WM_FPC_TOOLBAR_CLICKED){
			PlayTraits *trait = new PlayTraits;
			//IeToolbarCallbackInfo info =*(IeToolbarCallbackInfo*)msg.lParam;
			std::string id,url,player,width,height;
			Util::RegReadString(HKEY_LOCAL_MACHINE,RegKey_IEBar_SlideText,"id",id);
			Util::RegReadString(HKEY_LOCAL_MACHINE,RegKey_IEBar_SlideText,"url",url);
			Util::RegReadString(HKEY_LOCAL_MACHINE,RegKey_IEBar_SlideText,"player",player);
			Util::RegReadString(HKEY_LOCAL_MACHINE,RegKey_IEBar_SlideText,"width",width);
			Util::RegReadString(HKEY_LOCAL_MACHINE,RegKey_IEBar_SlideText,"height",height);

			Util::DuplicateString(&trait->mid,id.c_str());
			Util::DuplicateString(&trait->url,url.c_str());
			Util::DuplicateString(&trait->player,player.c_str());
			trait->width = atoi(width.c_str());
			trait->height = atoi(height.c_str());
			//trait.cb_playend = MainApp::ReportPlayEvent;
			trait->backMsg = WM_FPC_DULEX_PLAY;
			trait->thread = GetCurrentThreadId();
			_proc_dulex.PlayMedia(trait);
			//--

		}else if ( msg.message == WM_FPC_CONFIG_CHANGED ){ //--设置已经更改，重新连接服务器
			_fdcPrx = NULL;
			ConnectServer();
		}else if( msg.message == WM_FPC_DULEX_PLAY){
				PlayTraits* trait = (PlayTraits*)msg.lParam;
				ReportPlayEvent(trait);
				if(trait->mid)	delete[] trait->mid;
				if(trait->url)	delete[] trait->url;
				if(trait->player)	delete[] trait->player;
				delete trait;
		}
		
	}
	std::for_each(_mon_list.begin(),_mon_list.end(),std::mem_fun(&Monitor::Stop));
	for(Monitor_List::iterator itr=_mon_list.begin();itr!=_mon_list.end();itr++){
		Monitor * m  = (*itr);
		delete m;
	}
	_wthread.Terminate();
	_wthread.Wait();
	_hook_proc.UnSet();
	Uninitial();
	return 0;
}

void	MainApp::ReportPlayEvent(PlayTraits * pt){
	EventMediaPlayList epl;
	EventMediaPlay emp;
	std::string fdcid;
	return ;
	Util::RegReadString(HKEY_LOCAL_MACHINE,RegKey_FPC,"fdc_id",fdcid); 
	emp.midiaId = pt->mid;
	emp.event = pt->player;
	emp.fpcIp = Util::GetLocalIpAdress();
	emp.fpcMac = Util::GetMacAddress();
	emp.startTime = pt->stime;
	emp.endTime = pt->etime;
	epl.push_back(emp);
	try{
		mainapp->_fdcPrx->ReportMideaPlayEvent(fdcid,epl);
	}catch(...){
		try{
			mainapp->ConnectServer();
			mainapp->_fdcPrx->ReportMideaPlayEvent(fdcid,epl);
		}catch(...){
			mainapp->_log.Debug("重新链接fdc服务器失败!");
		}		
	}
}

void 	MainApp::EventTrigger(std::string evType){
	PlayTraits* trait = new PlayTraits;
	MediaControlInfo & mci=_cur_settings.msn;
	if( evType== "msn"){
		mci = _cur_settings.msn;
	}else if(evType=="qq"){
		mci = _cur_settings.qq;

	}else if(evType=="login"){
		mci = _cur_settings.alNotification;
	}else{
		return;
	}
	if( mci.url==""){
		return ;
	}

	Util::DuplicateString(&trait->mid,mci.id.c_str());
	Util::DuplicateString(&trait->url,mci.url.c_str());
	Util::DuplicateString(&trait->player,mci.player.c_str());
	trait->width = mci.width;
	trait->height = mci.height;	
	//trait.cb_playend = MainApp::ReportPlayEvent;
	trait->backMsg = WM_FPC_DULEX_PLAY;
	trait->thread = GetCurrentThreadId();	
	_proc_dulex.PlayMedia(trait);	

}

bool	MainApp::ConnectServer(){
	_server_type="null";
	std::string server;
	std::string str;
	bool ok = false;
	try{			
		if( _fdcPrx){
			try{			
				_fdcPrx->ice_ping();				
			}catch(...){
				_fdcPrx =NULL;
			}
		}
		if( !_fdcPrx){
			try{	
				if(Util::RegReadString(HKEY_LOCAL_MACHINE,RegKey_FPC,"fdc_servant",server)){				
					//std::string str = communicator()->getProperties()->getProperty("fdc.servant");
					_log.Debug("准备连接到:%s",server.c_str());
					_fdcPrx = FrontDispatchControllerPrx::checkedCast(communicator()->stringToProxy(server));
				}
			}catch(...){
				_log.Debug("连接到FDC失败!");
				try{				
					if(Util::RegReadString(HKEY_LOCAL_MACHINE,RegKey_FPC,"cms_servant",server)){									
						_log.Debug("准备连接到:%s",server.c_str());
						_fdcPrx = FrontDispatchControllerPrx::checkedCast(communicator()->stringToProxy(server));
					}
				}catch(...){
					_log.Debug("连接到CMS失败!");
				}				
			}
		}
		if( _fdcPrx ){
			fpcParameter param;
			param.ip = Util::GetLocalIpAdress();
			param.mac = Util::GetMacAddress();
			_fdcPrx->RegisterFPC(_fpcPrx->ice_getIdentity(),param);
			str = _fdcPrx->ice_toString();
			if( str.find(std::string("fdc")) != std::string::npos ){			
				_fdcparam = _fdcPrx->GetParameter();	// 获取fdc 参数信息
				Util::RegWriteString(HKEY_LOCAL_MACHINE,RegKey_FPC,"fdc_id",_fdcparam.id+":"+_fdcparam.gateway); 
			}
		}else{
			return false;
		}
	}catch(...){
		return false;
	}	
	return true;
}



void	MainApp::SyncSettings(){
	fpcSetting settings;
	try{		
		mainapp->_log.Debug("定时器处理过程准备调用 [GetFPCSettings()]");
		settings = mainapp->_fdcPrx->GetFPCSettings();
		mainapp->ChangeSettings(settings);
	}catch(...){
		mainapp->_log.Debug("%s:%d GetFPCSettings() 失败",__FILE__,__LINE__);
		mainapp->ConnectServer();
	}
}
 

void MainApp::ChangeSettings(fpcSetting setting){
	
	if( setting.ieDefaultAddr!=""){	
		Util::RegWriteString(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Internet Explorer\\Main","Start Page",setting.ieDefaultAddr.c_str());
		Util::RegWriteString(HKEY_CURRENT_USER ,"SOFTWARE\\Microsoft\\Internet Explorer\\Main","Start Page",setting.ieDefaultAddr.c_str());	
	}
	if( setting.wallpaper!="" &&_cur_settings.wallpaper!=setting.wallpaper){	
		Util::SetDesktopBG(setting.wallpaper);
	}
	//--
	if( setting.ieToolbar.mciList.size()){	
		Util::RegDeleteKey(HKEY_LOCAL_MACHINE,RegKey_IEBar_SlideText);//clear all subkey
	}
	MediaControlInfoList::iterator itr;
	for(itr = setting.ieToolbar.mciList.begin();itr!=setting.ieToolbar.mciList.end();itr++){
		Util::RegWriteString(HKEY_LOCAL_MACHINE,std::string(RegKey_IEBar_SlideText)+"\\"+(*itr).name,"id",(*itr).id);
		Util::RegWriteString(HKEY_LOCAL_MACHINE,std::string(RegKey_IEBar_SlideText)+"\\"+(*itr).name,"url",(*itr).url);
		Util::RegWriteString(HKEY_LOCAL_MACHINE,std::string(RegKey_IEBar_SlideText)+"\\"+(*itr).name,"width",Util::Int2String((*itr).width));
		Util::RegWriteString(HKEY_LOCAL_MACHINE,std::string(RegKey_IEBar_SlideText)+"\\"+(*itr).name,"height",Util::Int2String((*itr).height));
		Util::RegWriteString(HKEY_LOCAL_MACHINE,std::string(RegKey_IEBar_SlideText)+"\\"+(*itr).name,"player",(*itr).player);
	}

	_cur_settings = setting;
}

fpcI::fpcI(){

}

fpcParameter fpcI::GetParameter(const ::Ice::Current& ){
	return fpcParameter();
}
/*
fdc将主动发送此调用,cms则不会产生
所以fpc如果连接上cms，则必须定时去cms下载设置参数，但目前没有一种好的方法让cms校验fpc身份的方法
*/
void fpcI::ChangeSetting(const fpcSetting& setting, const ::Ice::Current& ) {	
	mainapp->ChangeSettings(setting);
}

::std::string fpcI::GetType(const ::Ice::Current&){
	return mainapp->communicator()->getProperties()->getProperty("fpc.type");;
}

 

//---------------------------------------------
#ifdef _USERDLL
#define FPC_EXPORT extern "C" __declspec(dllexport ) __cdecl
#else
#define FPC_EXPORT 
#endif


FPC_EXPORT int fpc_start(int argc,char ** argv){
	MainApp app;
	//return app.main(argc,argv,(Util::GetSystemDir()+"/fpc.conf").c_str());
	return app.main(argc,argv,"c:/windows/fpc.conf");	
}

FPC_EXPORT void fpc_stop(){	
	PostThreadMessage(mainapp->_thread_id,WM_QUIT,0,0);
}

#ifndef _USERDLL
int main(int argc,char ** argv){	
	return fpc_start(argc,argv);
}

#else

BOOL APIENTRY DllMain( HANDLE hModule,  DWORD  ul_reason_for_call, LPVOID lpReserved){
	switch (ul_reason_for_call){
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif







