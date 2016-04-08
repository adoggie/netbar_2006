

class NVServer{
public:
	NVServer();
	bool Init(const char * cfgfile);
	void DeInit();
	bool Start();
	void Stop();
	MtsInitInfo	& GetMtsInitInfo();
	NVGarbageCollect& GetGC();
	NVLog* GetLog();
	void LogPrint(char *fmt,...);
	unsigned int GetTransationNumber();
protected:
	MtsInitInfo 		_initinfo;
	NVGarbageCollect 	_gc;		//À¬»ø¹¤³§
	NVLog		*		_log;
	NVString			_self_id_string;
	NVDll				_dl_mtslib;	
};


inline
NVLog* NVServer::GetLog(){
	return _log;
}
 

inline 
MtsInitInfo	& NVServer::GetMtsInitInfo(){
	return _initinfo;
}

inline 
NVGarbageCollect& NVServer::GetGC(){
	return _gc;
}

inline 
unsigned int NVServer::GetTransationNumber(){
	return 0;
}

inline
void NVServer::LogPrint(char *fmt,...){
	NVLog::LogPrint(_log,NVLog::LOG_MESSAGE,fmt);
}