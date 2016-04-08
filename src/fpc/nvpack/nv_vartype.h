
#ifndef _NV_VARTYPE_H
#define _NV_VARTYPE_H

#include <string>
#include <list>
#include <algorithm>
#include <functional>


typedef std::string NVString;

typedef char NVInt8;
typedef int NVInt32;
typedef short NVInt16;

typedef unsigned char NVUInt8;
typedef unsigned short NVUInt16;
typedef unsigned int NVUInt32;

typedef  NVInt8 NVByte;

#ifdef _UNIX
	typedef long long NVINT64;
#endif
#ifdef WIN32
	typedef __int16		NVINT64;
#endif

#define NVNULL 0 

#endif
