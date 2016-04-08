
#ifndef _HOOK_H
#define _HOOK_H


#include <windows.h>

#pragma  pack(1)
struct IeToolbarCallbackInfo{
	char    name[512];
	char    url[512];
	char    player[128];
	int     width;
	int     height;
};

typedef bool (*UnSet_T)();
typedef bool (*SetCaptureKey_T)(DWORD msg,DWORD thread,int key,int shift,int ctrl,int alt);
typedef bool (*IeToolbar_Clicked_T)( DWORD backMsg,IeToolbarCallbackInfo* info );

struct HookProcs{
	UnSet_T				UnSet;
	SetCaptureKey_T		SetCaptureKey;
	IeToolbar_Clicked_T	IeToolbar_Clicked;
};

#pragma  pack(8)
typedef bool   (*IeToolbar_Clicked_T)( DWORD msg,IeToolbarCallbackInfo* info );

#endif
