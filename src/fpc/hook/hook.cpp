
#include "hook.h"


#pragma data_seg("publicdata")
	int fshift=0;
	int fctrl =0;
	int falt = 0;
	int ckey=0;
	HHOOK hhk=0;
	DWORD backThread=0;
	DWORD backMsg =0;
    IeToolbarCallbackInfo ieTbBackInfo={0};
#pragma data_seg( )
#pragma comment(linker, "/SECTION:publicdata,RWS")

//dll中创建共享数据段，切记！！！所有变量必须初始化，否则创建将失败

#include <stdio.h>
#include <stdlib.h>

#include "../nvpack/nvlog.h"

NVLog log;
LRESULT CALLBACK GetMsgProc(
  int code,       // hook code
  WPARAM wParam,  // removal option
  LPARAM lParam   // message
  ){
	MSG  *pmsg =(MSG*)lParam;
	if (code < 0){
		goto end;	
	}


	if(pmsg->message == WM_KEYDOWN  ){ // && LOWORD(wParam)==12324				
		if( pmsg->wParam ==	ckey){			
			if( fctrl && !(GetKeyState(VK_CONTROL)&0x800 ) ){
				goto end;
			}
			if( fshift && !(GetKeyState(VK_CONTROL)&0x800) ){
				goto end;
			}
			//MessageBox(0,"dd","",MB_OK);
			log.Debug("thread:%x,msg:%d",backThread,backMsg);
			PostThreadMessage(backThread,backMsg,0,0);
		}
		
	}
end :
	return CallNextHookEx(hhk,code,wParam,lParam);

}


extern "C" bool  __declspec(dllexport)  UnSet(){
	if ( hhk ){
		::UnhookWindowsHookEx(hhk);
		hhk = NULL;
		backThread = 0;
	}
	return true;
}

extern "C" bool   __declspec(dllexport)  SetCaptureKey(DWORD msg,DWORD thread,int key,int shift,int ctrl,int alt){
	UnSet();
	backThread = thread;
	fshift = shift;
	fctrl = ctrl;
	falt = alt;
	ckey = key;
	backMsg = msg;	
	HINSTANCE hdll = GetModuleHandle("fpchook.dll");	
	hhk = SetWindowsHookEx(WH_GETMESSAGE,HOOKPROC(GetMsgProc) ,hdll,0);
	if(!hhk)	return false;


	NVLog::WindowWriter * w = new NVLog::WindowWriter("fpchook",true);
	w->Open();
	log.SetWriter(w);
	return true;
}

//-- genius done !
extern "C" bool   __declspec(dllexport)  IeToolbar_Clicked( DWORD backMsg,IeToolbarCallbackInfo* info ){
    //if( backThread){
        //ieTbBackInfo = *info;
        PostThreadMessage(backThread,backMsg,0,(LPARAM)&ieTbBackInfo);
	//}else{
		//MessageBox(0,"no backcall thread defined!","",MB_OK);
	//}
    return true;    
}



