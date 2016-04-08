
#ifndef _NVDLL_H
#define _NVDLL_H

#ifdef _UNIX
	#include <unistd.h>
	#include <signal.h>
	#include <sys/socket.h>
	#include <dlfcn.h>
	#define getsymaddr	dlsym
	typedef void	*	HMODULE;
#endif

#ifdef  WIN32
	#include <windows.h>
	#define getsymaddr	GetProcAddress
#endif

#include <string>
#include "nvobject.h"

class NVDll:public NVObject{
public:
	bool 	LoadDll(const char * dll);
	void *	LoadSymbol(const char *proc);
	void	FreeDll();	
	HMODULE GetModule();
	std::string & 	GetFileName(){
		return filename;
	}
private:	
	HMODULE				libmodule;	
	std::string	filename;
};

inline 
HMODULE NVDll::GetModule(){
	return libmodule;
}

inline 
bool 	NVDll::LoadDll(const char * dll){
	filename = dll;
	#ifdef _UNIX		
		libmodule = dlopen(dll,RTLD_NOW);
	#endif
	#ifdef _WIN32
		libmodule = LoadLibrary(dll);
	#endif
	if( !libmodule){
		return false;
	}
	return true;
}

inline 
void *	NVDll::LoadSymbol(const char *proc){
	return getsymaddr(libmodule,proc);
}

inline 
void	NVDll::FreeDll(){
	#ifdef _UNIX		
		dlclose(libmodule);
	#endif
	#ifdef _WIN32
		FreeLibrary(libmodule);
	#endif	
}

#endif
