
#ifndef _UTIL_H
#define _UTIL_H

#include <windows.h>
#include <wincon.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Nb30.h>
#include <string>

namespace Util{
	unsigned long GetHostAddress(const char * host);
	
	bool HostReachable(const char * host,unsigned short port);
	
	std::string GetSystemDir();
	std::string GetMacAddress();
	std::string GetLocalIpAdress();
	std::string GetTemporatyDir();
	bool	RegWriteString(HKEY  root,std::string subkey,std::string key,std::string value);
	bool	RegReadString(HKEY root,std::string subkey,std::string key,std::string &value);
	void	RegDeleteKey(HKEY root,std::string path);
	void	SetDesktopBG(std::string url);
	std::string	Int2String(int );
	void	DuplicateString(char** dest,const char * src);
}
#endif

