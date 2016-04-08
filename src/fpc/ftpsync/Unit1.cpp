//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
    return 1;
}

#include <NMFtp.hpp>
#include <Psock.hpp>
/*
extern "C" int __stdcall ftp_login(const char * ip,int port,char * user,char * passwd);
extern "C" void __stdcall ftp_logoff();
extern "C" int __stdcall ftp_cwd(const char * path);
extern "C" int __stdcall ftp_getfile(char* from ,char * to);
 */
//---------------------------------------------------------------------------
TNMFTP *ftpc;
/*
  return: succuss = 0 ,else is failed
*/
extern "C" __declspec(dllexport)  int  ftp_login(const char * ip,int port,char * user,char * passwd){
    ftpc = NULL;
    ftpc = new TNMFTP(0);
    ftpc->Host = ip;
    ftpc->Port = port;
    ftpc->UserID = user;
    ftpc->Password = passwd;
    try{
        ftpc->Connect();
    }catch(...){
        delete ftpc;
        ftpc = NULL;
        return 1;
    }
    return 0;
}

extern "C" __declspec(dllexport) void  ftp_logoff(){
    if ( ftpc ){
        ftpc->Disconnect();
        delete ftpc;
        ftpc = NULL;
    }
}

extern "C" __declspec(dllexport) int  ftp_cwd(const char * path){
    try{
        ftpc->ChangeDir(path);
    }catch(...){
        return 2;
    }
    return 0;
}

extern "C" __declspec(dllexport) int  ftp_getfile(char* from ,char * to){
    if(!ftpc){
        return 3;
    }
    try{
        ftpc->Download(from,to);
    }catch(...){
        return 3;
    }
    return 0;
}