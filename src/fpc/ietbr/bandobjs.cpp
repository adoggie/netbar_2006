/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 - 1998 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          BandObjs.cpp
   
   Description:   Contains DLLMain and standard OLE COM object creation stuff.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include <ole2.h>
#include <comcat.h>
#include <olectl.h>
#include "ClsFact.h"

/**************************************************************************
   GUID stuff
**************************************************************************/

//this part is only done once
//if you need to use the GUID in another file, just include Guid.h
#pragma data_seg(".text")
#define INITGUID
#include <initguid.h>
#include <shlguid.h>
#include "Guid.h"
#pragma data_seg()

/**************************************************************************
   private function prototypes
**************************************************************************/

extern "C" BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID);
BOOL RegisterServer(CLSID, LPTSTR);
BOOL RegisterComCat(CLSID, CATID);

/**************************************************************************
   global variables
**************************************************************************/

HINSTANCE   g_hInst;
UINT        g_DllRefCount;

#include "../hook/hook.h"

HMODULE		g_dulex = 0;
IeToolbar_Clicked_T IeToolbar_Clicked;


/**************************************************************************

   DllMain

**************************************************************************/

extern "C" BOOL WINAPI DllMain(  HINSTANCE hInstance, 
                                 DWORD dwReason, 
                                 LPVOID lpReserved)
{
switch(dwReason)
   {
   case DLL_PROCESS_ATTACH:
      g_hInst = hInstance;
	  g_dulex = LoadLibrary("fpchook.dll");
	  if( g_dulex ){	
			IeToolbar_Clicked = (IeToolbar_Clicked_T)GetProcAddress(g_dulex,"IeToolbar_Clicked");
			if( IeToolbar_Clicked)
	;	//	MessageBox(0,"load IeToolbar_Clicked ok","",MB_OK);	
			else
		;	//	MessageBox(0,"load IeToolbar_Clicked FAILED","",MB_OK);	
	  }else{
			MessageBeep(1000);
			MessageBox(0,"hook can't be loaded","",MB_OK);			
	  }
      break;

   case DLL_PROCESS_DETACH:
			if( g_dulex)
				FreeLibrary(g_dulex);
      break;
   }
   
return TRUE;
}                                 

/**************************************************************************

   DllCanUnloadNow

**************************************************************************/

STDAPI DllCanUnloadNow(void)
{
return (g_DllRefCount ? S_FALSE : S_OK);
}

/**************************************************************************

   DllGetClassObject

**************************************************************************/

STDAPI DllGetClassObject(  REFCLSID rclsid, 
                           REFIID riid, 
                           LPVOID *ppReturn)
{
*ppReturn = NULL;

//if we don't support this classid, return the proper error code
if(   !IsEqualCLSID(rclsid, CLSID_SampleDeskBand) &&
      !IsEqualCLSID(rclsid, CLSID_SampleExplorerBar) &&
      !IsEqualCLSID(rclsid, CLSID_SampleCommBand))
   return CLASS_E_CLASSNOTAVAILABLE;
   
//create a CClassFactory object and check it for validity
CClassFactory *pClassFactory = new CClassFactory(rclsid);
if(NULL == pClassFactory)
   return E_OUTOFMEMORY;
   
//get the QueryInterface return for our return value
HRESULT hResult = pClassFactory->QueryInterface(riid, ppReturn);

//call Release to decement the ref count - creating the object set it to one 
//and QueryInterface incremented it - since its being used externally (not by 
//us), we only want the ref count to be 1
pClassFactory->Release();

//return the result from QueryInterface
return hResult;
}

#include <string>
bool	RegWriteString(HKEY  root,std::string sub,std::string key,std::string value){
	HKEY subkey;
	DWORD dw;
	LONG ReturnValue = ::RegCreateKeyEx (root, sub.c_str(), NULL, NULL,
		REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL,
		&subkey, &dw);

	if(ReturnValue != ERROR_SUCCESS){
		return false;
	}
	ReturnValue =(LONG) RegSetValueEx(subkey,key.c_str(),0,REG_BINARY,(CONST BYTE*)NULL,(LONG)NULL);
	if(ReturnValue != ERROR_SUCCESS){
		return false;
	}

	RegCloseKey(subkey);
	return true;
}
/**************************************************************************

   DllRegisterServer

**************************************************************************/

STDAPI DllRegisterServer(void)
{
	/*
//Register the desk band object.
if(!RegisterServer(CLSID_SampleDeskBand, TEXT("Sample &Desk Band")))
   return SELFREG_E_CLASS;

//Register the component categories for the desk band object.
if(!RegisterComCat(CLSID_SampleDeskBand, CATID_DeskBand))
   return SELFREG_E_CLASS;
*/
//Register the explorer bar object.
if(!RegisterServer(CLSID_SampleExplorerBar, TEXT("Sample &Explorer Bar")))
   return SELFREG_E_CLASS;
//--ע��ie ������
RegWriteString(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Internet Explorer\\Toolbar","{0F644541-1228-47e6-898F-F36AC69196B4}","");

//Register the component categories for the explorer bar object.
if(!RegisterComCat(CLSID_SampleExplorerBar, CATID_InfoBand))
   return SELFREG_E_CLASS;
/*
//Register the comm band object.
if(!RegisterServer(CLSID_SampleCommBand, TEXT("Sample &Comm Band")))
   return SELFREG_E_CLASS;

//Register the component categories for the comm band object.
if(!RegisterComCat(CLSID_SampleCommBand, CATID_CommBand))
   return SELFREG_E_CLASS;
*/
return S_OK;
}

/**************************************************************************

   RegisterServer

**************************************************************************/

typedef struct{
   HKEY  hRootKey;
   LPTSTR szSubKey;//TCHAR szSubKey[MAX_PATH];
   LPTSTR lpszValueName;
   LPTSTR szData;//TCHAR szData[MAX_PATH];
}DOREGSTRUCT, *LPDOREGSTRUCT;

BOOL RegisterServer(CLSID clsid, LPTSTR lpszTitle)
{
int      i;
HKEY     hKey;
LRESULT  lResult;
DWORD    dwDisp;
TCHAR    szSubKey[MAX_PATH];
TCHAR    szCLSID[MAX_PATH];
TCHAR    szModule[MAX_PATH];
LPWSTR   pwsz;

//get the CLSID in string form
StringFromIID(clsid, &pwsz);

if(pwsz)
   {
#ifdef UNICODE
   lstrcpy(szCLSID, pwsz);
#else
   WideCharToMultiByte( CP_ACP,
                        0,
                        pwsz,
                        -1,
                        szCLSID,
                        ARRAYSIZE(szCLSID),
                        NULL,
                        NULL);
#endif

   //free the string
   LPMALLOC pMalloc;
   CoGetMalloc(1, &pMalloc);
   pMalloc->Free(pwsz);
   pMalloc->Release();
   }

//get this app's path and file name
GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule));

DOREGSTRUCT ClsidEntries[] = {HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s"),                  NULL,                   lpszTitle,
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),  NULL,                   szModule,
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),  TEXT("ThreadingModel"), TEXT("Apartment"),
                              NULL,                NULL,                               NULL,                   NULL};

//register the CLSID entries
for(i = 0; ClsidEntries[i].hRootKey; i++)
   {
   //create the sub key string - for this case, insert the file extension
   wsprintf(szSubKey, ClsidEntries[i].szSubKey, szCLSID);

   lResult = RegCreateKeyEx(  ClsidEntries[i].hRootKey,
                              szSubKey,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hKey,
                              &dwDisp);
   
   if(NOERROR == lResult)
      {
      TCHAR szData[MAX_PATH];

      //if necessary, create the value string
      wsprintf(szData, ClsidEntries[i].szData, szModule);
   
      lResult = RegSetValueEx(   hKey,
                                 ClsidEntries[i].lpszValueName,
                                 0,
                                 REG_SZ,
                                 (LPBYTE)szData,
                                 lstrlen(szData) + 1);
      
      RegCloseKey(hKey);
      }
   else
      return FALSE;
   }

return TRUE;
}

/**************************************************************************

   RegisterComCat

**************************************************************************/

BOOL RegisterComCat(CLSID clsid, CATID CatID)
{
ICatRegister   *pcr;
HRESULT        hr = S_OK ;
    
CoInitialize(NULL);

hr = CoCreateInstance(  CLSID_StdComponentCategoriesMgr, 
                        NULL, 
                        CLSCTX_INPROC_SERVER, 
                        IID_ICatRegister, 
                        (LPVOID*)&pcr);

if(SUCCEEDED(hr))
   {
   hr = pcr->RegisterClassImplCategories(clsid, 1, &CatID);

   pcr->Release();
   }
        
CoUninitialize();

return SUCCEEDED(hr);
}

