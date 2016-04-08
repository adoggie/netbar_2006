
#ifndef _MONITOR_H
#define _MONITOR_H

#include "base.h"
#include <windows.h>

class Monitor:public NVThread{
public:	
	Monitor();
	virtual ~Monitor(){};
	void 	SetInterval(int msleep);
	std::string	Type(){	return _type;}
	virtual void	Start();
	virtual void	Stop();
protected:
	void 	Run(void*);	
	virtual bool IsTriggered()=0;	
	std::string 	_type;
	int				_msleep;
	bool			_last;

};

class MsnMonitor: public Monitor{
public:
	MsnMonitor();
	bool IsTriggered();
};

class QQMonitor: public Monitor{
public:
	QQMonitor();
	bool IsTriggered();
	static BOOL  CALLBACK	enumproc(HWND hwnd,LPARAM lParam );
private:
	bool	_found;	
};

class SysLoginMonitor: public Monitor{
public:
	SysLoginMonitor();
	void	Run(void*);
	bool 	IsTriggered(){ return false;}
	static void SignalLogin();
	void	Stop();	
private:	

};

typedef std::list<Monitor*> Monitor_List;

#endif
