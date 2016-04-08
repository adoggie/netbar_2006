#ifndef _BASE_H
#define _BASE_H

#include "nvpack/nv.h"

 

#define SIGNAL_SYSLOGIN 	"signal of system user login  for fpc"


#include "dulex/dulex.h"
#include "hook/hook.h"

#define RegKey_AfterLoginAdvertisement	"loginAdvertisement"
#define RegKey_AfterLoginNotification	"loginNotification"
#define RegKey_FPC	"SOFTWARE\\MPMS\\fpc"
#define RegKey_IEBar_SlideText "SOFTWARE\\MPMS\\fpc\\slidetext"

#define EVENT_IE_TOOLBAR	"ietbr"
#define EVENT_MSN	"msn"
#define EVENT_QQ	"qq"
#define EVENT_LOGIN	"login"


#define WM_FPC_CONFIG			WM_USER+100
#define WM_FPC_CONFIG_CHANGED	WM_USER+102
#define WM_FPC_TOOLBAR_CLICKED	WM_USER+101
#define WM_FPC_DULEX_PLAY		WM_USER+104



#endif

