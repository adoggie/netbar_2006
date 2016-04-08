
#ifndef  _NV_CALENDAR_H
#define _NV_CALENDAR_H

#include "nv_vartype.h"
#include <time.h>
#include <stdio.h>


class NVCalendar{
public:
	static unsigned int GetTimeStamp();
	static NVString GetCurTimeStr();
	
};

inline 
unsigned int NVCalendar::GetTimeStamp(){
	return (unsigned int)time(0);
}

inline 
NVString NVCalendar::GetCurTimeStr(){
	char buff[100];	
	time_t tv;
	tm *ptm;
	time(&tv);
	ptm =localtime(&tv);	
	sprintf(buff,"%d-%d-%d %02d:%02d:%02d",ptm->tm_year+1900 ,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec);	
	return NVString(buff);
}

#endif

