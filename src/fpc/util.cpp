
#include "util.h"

#include <Wininet.h>
#include <Shlobj.h>
#include <atlbase.h>


namespace Util{

unsigned long GetHostAddress(const char * host){
	unsigned long ret;
	ret  = inet_addr(host);
	if ( ret == INADDR_NONE ){
		hostent *pht = gethostbyname(host);
        if(pht==0){
        	ret = 0;
        }else
            ret =  *(unsigned long*)(pht->h_addr_list[0]) ;
	}
	return ret;
}


bool HostReachable(const char * host,unsigned short port){
	return true;
}


std::string GetSystemDir(){
	char buff[1024];
	GetSystemDirectory(	buff,sizeof(buff));
	return buff;
}

std::string GetLocalIpAdress(){
	char  name[128];
	in_addr in;
	
	gethostname(name,sizeof(name));
	hostent *pht = gethostbyname(name);		
	in.s_addr =  *(unsigned long*)(pht->h_addr_list[0]) ;	 
	return inet_ntoa(in);
}

typedef struct _ASTAT_
{
	ADAPTER_STATUS adapt;
	NAME_BUFFER    NameBuff [30];
}ASTAT, * PASTAT;

std::string GetMacAddress(){
	ASTAT Adapter;
	NCB ncb;
	UCHAR uRetCode;
	char NetName[50];

	memset( &ncb, 0, sizeof(ncb) );
	ncb.ncb_command = NCBRESET;
	ncb.ncb_lana_num = 0;
	uRetCode = Netbios( &ncb );
	//printf( "The NCBRESET return code is: 0x%x \n", uRetCode );
	memset( &ncb, 0, sizeof(ncb) );
	ncb.ncb_command = NCBASTAT;
	ncb.ncb_lana_num = 0;
	strcpy( (char*)ncb.ncb_callname,  "*               " );
	ncb.ncb_buffer = (PUCHAR) &Adapter;
	ncb.ncb_length = sizeof(Adapter);
	uRetCode = Netbios( &ncb );
	//printf( "The NCBASTAT return code is: 0x%x \n", uRetCode );
	if ( uRetCode == 0 ){
		sprintf( NetName,"%02x%02x%02x%02x%02x%02x",
			Adapter.adapt.adapter_address[0],
			Adapter.adapt.adapter_address[1],
			Adapter.adapt.adapter_address[2],
			Adapter.adapt.adapter_address[3],
			Adapter.adapt.adapter_address[4],
			Adapter.adapt.adapter_address[5] );
	}
	return NetName;
}


std::string GetTemporatyDir(){
	char dir[512];
	GetWindowsDirectory(dir,sizeof(dir));
	return dir;
}


bool	RegWriteString(HKEY  root,std::string sub,std::string key,std::string value){
	HKEY subkey;
	DWORD dw;
	LONG ReturnValue = ::RegCreateKeyEx (root, sub.c_str(), NULL, NULL,
		REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL,
		&subkey, &dw);

	if(ReturnValue != ERROR_SUCCESS){
		return false;
	}
	ReturnValue =(LONG) RegSetValueEx(subkey,key.c_str(),0,REG_SZ,(CONST BYTE*)value.c_str(),(LONG)(value.size()+1));
	if(ReturnValue != ERROR_SUCCESS){
		return false;
	}

	RegCloseKey(subkey);
	return true;
}

/*
void	SetDesktopBG(std::string url){
	//--更改壁纸必须是.bmp格式，否则无法设置1！！！！
	SystemParametersInfo(SPI_SETDESKWALLPAPER,0,(void*)url.c_str(),SPIF_UPDATEINIFILE);
	SystemParametersInfo(SPI_SETDESKWALLPAPER,0,(void*)0,SPIF_SENDCHANGE);	
}*/


void	SetDesktopBG(std::string url){
	HRESULT hr;
	IActiveDesktop *pActiveDesktop;
	CoInitialize ( NULL );

	//Create an instance of the Active Desktop
	hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,
		IID_IActiveDesktop, (void**)&pActiveDesktop);
	USES_CONVERSION;
	LPWSTR x = A2W(url.c_str());
	//Insert code to call the IActiveDesktop methods
	pActiveDesktop->SetWallpaper(x,NULL);
	pActiveDesktop->ApplyChanges(AD_APPLY_ALL);
	// Call the Release method
	pActiveDesktop->Release();
	CoUninitialize();

}



bool	RegReadString(HKEY root,std::string subdir,std::string key,std::string &value){
	char buff[1024];
	DWORD size=sizeof(buff);
	HKEY subkey= NULL;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,subdir.c_str(),0,KEY_ALL_ACCESS,&subkey)!=ERROR_SUCCESS){
		return false;
	}
	memset(buff,0,sizeof(buff));
	DWORD type = REG_SZ;
	if( RegQueryValueEx(  subkey,key.c_str(),(LPDWORD)NULL,(LPDWORD )&type,(LPBYTE)buff,(LPDWORD)&size) !=ERROR_SUCCESS){
		RegCloseKey(subkey);
		return false;
	}
	value = buff;
	RegCloseKey(subkey);
	return true;
}
 

void RegDeleteKey(HKEY root,std::string path){
	HKEY key= NULL;
	if(RegOpenKeyEx(root,path.c_str(),0,KEY_ALL_ACCESS,&key)!=ERROR_SUCCESS){
		return ;
	}
	int index;
	DWORD size;
	char buff[512];
	index =200;
	size = sizeof(buff);
	while( index >=0){
		RegEnumKey(key,index,buff,sizeof(buff));// == ERROR_SUCCESS
		::RegDeleteKey(key,buff);
		index--;
	}
	RegCloseKey(key);
}

std::string	Int2String(int n){
	char buff[32];
	sprintf(buff,"%d",n);
	return buff;
}

void	DuplicateString(char** dest,const char * src){
	*dest = new char[strlen(src)+1];
	strcpy(*dest,src);
}

//-- end 
}

