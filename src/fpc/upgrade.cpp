
#include "upgrade.h"
#include "base.h"

#include "util.h"

typedef int (*ftp_login_t)(const char * ip,int port,const char * user,const char * passwd);
typedef void (*ftp_logoff_t)();
typedef int (*ftp_cwd_t)(const char * path);
typedef int (*ftp_getfile_t)(const char* from ,const char * to);


SystemSync::SystemSync(NVLog * log){
	_log = log;
}

int SystemSync::run(int, char**){
	CentreMangementSystemPrx cms;
	std::string str,server;
	if( !Util::RegReadString(HKEY_LOCAL_MACHINE,RegKey_FPC,"version",str)){
		str ="0.0.0";	// default value
	}
	try{	
		Util::RegReadString(HKEY_LOCAL_MACHINE,RegKey_FPC,"cms_servant",server)	;	
		cms = CentreMangementSystemPrx::checkedCast(communicator()->stringToProxy(server));
		SystemDistribution dist;
		dist = cms->SyncSystem("fpc",str);
		FtpServer ftps = cms->GetFtpServer();
		NetFileList &list = dist.fileList;
		//-- 
		if( !_dll.LoadDll("ftpsync.dll") ){
			return -1;
		}
		ftp_login_t	ftp_login = (ftp_login_t)_dll.LoadSymbol("_ftp_login");
		ftp_logoff_t ftp_logoff = (ftp_logoff_t)_dll.LoadSymbol("_ftp_logoff");
		ftp_cwd_t	ftp_cwd = (ftp_cwd_t)_dll.LoadSymbol("_ftp_cwd");
		ftp_getfile_t	ftp_getfile = (ftp_getfile_t)_dll.LoadSymbol("_ftp_getfile");
		if( !ftp_login){
			return -1;
		}
		if( list.size()){
			if( ftp_login(ftps.host.c_str(),atoi(ftps.port.c_str()),ftps.user.c_str(),ftps.passwd.c_str()) ){
				_log->Debug("����ftp_server(%s:%s)ʧ��!",ftps.host.c_str(),ftps.port.c_str());
				return -1;
			}
		}		
		for(NetFileList::iterator itr = list.begin();itr!=list.end();itr++){
			//--д���ļ�
			str = (*itr).instdir+"/"+(*itr).file;
			if( ftp_getfile( (*itr).file.c_str(),str.c_str()) ){
				_log->Debug("ͬ��ftp�ļ���%s��%sʧ��!",(*itr).file.c_str(),str.c_str());
			}
		}
		//--��¼���°汾
		if( list.size()){
			Util::RegWriteString(HKEY_LOCAL_MACHINE,RegKey_FPC,"version",dist.version);
			ftp_logoff();
			_log->Debug("���ϵͳ���£�Ŀǰ�汾version:%s",dist.version.c_str());	
		}
	}catch(...){
		_log->Debug("ͬ��ϵͳ���ʧ��! ��������CMSʧ��");
	}
	return 0;
}