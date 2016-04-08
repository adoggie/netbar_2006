
/*
@revision:
    2006.05.17  scott   增加处理回调事件、开始和结束时间

*/

//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "play.h"
#include "paramcfg.h"
#include "dulex.h"
#include <string>
#include <stdio.h>


#define RegKey_FPC_PlayCurrent	"SOFTWARE\\MPMS\\fpc\\current"



#pragma hdrstop

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
    
    return 1;
}

bool	RegWriteString(HKEY  root,std::string sub,std::string key,std::string value){
	HKEY subkey;
	DWORD dw;
	LONG ReturnValue = ::RegCreateKeyEx (root, sub.c_str(), NULL, NULL,
		REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL,
		&subkey, &dw);

	if(ReturnValue != ERROR_SUCCESS){
		return false;
	}
	ReturnValue =(LONG) RegSetValueEx(subkey,key.c_str(),0,REG_SZ,(CONST BYTE*)value.c_str(),(LONG)(value.size()+1));
	if(ReturnValue != ERROR_SUCCESS){
		return false;
	}

	RegCloseKey(subkey);
	return true;
}

std::string GetSystemDir(){
	char buff[1024];
	GetSystemDirectory(	buff,sizeof(buff));
	return buff;
}
//---------------------------------------------------------------------------
std::string SaveTempFile(char * html){
    FILE * fp;
	std::string fname;
	char rand[32];
    std::string dir = GetSystemDir();
	sprintf(rand,"%u",time(0));
	fname =dir+"/"+std::string(rand)+".html";
	fp = fopen(fname.c_str(),"w");
	if( fp ){
		fwrite(html,strlen(html),1,fp);
		fclose(fp);
	}
    return fname;

}
DWORD ThreadPlay(LPVOID p){
    TFormPlay *form;
	char *buff = NULL ;
    std::string player;

    PlayTraits * pt =(PlayTraits*) p;
    if( pt->url ){
        CoInitialize(0);
        form = new TFormPlay(0);
        pt->stime = time(0);
        player = pt->player;
        std::string file;
        if( player == "mp"){
            buff = new char[strlen(Html_Format_MediaPlayer)+1024];
            sprintf(buff,Html_Format_MediaPlayer,pt->width,pt->height,pt->url);
        }else if(player=="rm"){
            buff = new char[strlen(Html_Format_RealPlayer)+1024];
            sprintf(buff,Html_Format_RealPlayer,pt->width,pt->height,pt->url);
        }else if(player=="fl"){
            buff = new char[strlen(Html_Format_Flash)+1024];
            sprintf(buff,Html_Format_Flash,pt->width,pt->height,pt->url);
        }else{
            file = pt->url;
        }
        if( buff ){
            file = SaveTempFile(buff);
            delete[] buff;
        }
        form->wb->Navigate(WideString(file.c_str()));
        form->SetBound(pt->width,pt->height);
        form->ShowModal();
        form->Close();;
        pt->etime = time(0);
        delete form;
        CoUninitialize();
    }
    PostThreadMessage(pt->thread,pt->backMsg,NULL,(LPARAM) pt);
    return 0;
}


extern "C"   __declspec(dllexport) __cdecl void PlayMedia(PlayTraits* tr){
    DWORD thrid;

//    PlayTraits * pt = new PlayTraits;
//    *pt = *tr;
//    pt->mid = new char[strlen(tr->mid)+1];
//    strcpy(pt->mid,tr->mid);
//    pt->url = new char[ strlen(tr->url)+1];
//    strcpy(pt->url,tr->url);
//    pt->player = new char[ strlen(tr->player)+1];
//    strcpy(pt->player,tr->player);

    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ThreadPlay,(void*)tr,0,&thrid);
}

DWORD _notifyThread = NULL;
DWORD _MsgChanged = NULL;

DWORD ThreadConfig(LPVOID p){
    if( !FormParam ){
        FormParam = new TFormParam(0);
        FormParam->ShowModal();
        delete FormParam;
        FormParam=0;
        //--发送配置更改消息到处理主线程
        PostThreadMessage(_notifyThread,_MsgChanged,NULL,NULL);
    }
    return 0;
}


extern "C"   __declspec(dllexport) __cdecl void ParamConfig(DWORD notifyThread,DWORD MsgChanged){
    DWORD  thrid;
    _notifyThread = notifyThread;
    _MsgChanged = MsgChanged;
    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ThreadConfig,(void*)0,0,&thrid);
}
