

#ifndef  _NVPLAT_H
#define _NVPLAT_H

#ifdef WIN32
#define SLEEP_SEC(x)	::Sleep((x)*1000)
#define SLEEP_MSEC(x)	::Sleep(x)
#define SLEEP_USEC(x)	::Sleep((x/1000))
#endif

#ifdef _UNIX

	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	
	#include <netdb.h>
	#include <string.h>
	#include <stdio.h>
	#include <fcntl.h>
	
	#define SLEEP_SEC(x)	sleep(x)
	#define SLEEP_MSEC(x)	usleep((x)*1000)
	#define SLEEP_USEC(x)	usleep(x)
#endif

#endif
//-- end file
