//---------------------------------------------------------------------------
#include <string>
#include <vcl.h>
#pragma hdrstop

#include "paramcfg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormParam *FormParam = NULL;
std::string passwd;
#define RegKey_FPC	"SOFTWARE\\MPMS\\fpc"
//---------------------------------------------------------------------------
__fastcall TFormParam::TFormParam(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormParam::Button2Click(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------

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

void __fastcall TFormParam::Button1Click(TObject *Sender)
{
    std::string value;
    if( passwd=="" || edtPwd->Text.c_str() != passwd){
        ShowMessage("无效的管理口令!");
        return;
    }
    value =edtServer1->Text.c_str();
    RegWriteString(HKEY_LOCAL_MACHINE, RegKey_FPC,"fdc_servant",value);
    value =edtServer2->Text.c_str();
    RegWriteString(HKEY_LOCAL_MACHINE, RegKey_FPC,"cms_servant",value);
    Close();

}
//---------------------------------------------------------------------------

void __fastcall TFormParam::FormShow(TObject *Sender)
{
    std::string value;
    RegReadString(HKEY_LOCAL_MACHINE,RegKey_FPC,"fdc_servant",value);
    edtServer1->Text = value.c_str();
    RegReadString(HKEY_LOCAL_MACHINE,RegKey_FPC,"cms_servant",value);
    edtServer2->Text = value.c_str();

    RegReadString(HKEY_LOCAL_MACHINE,RegKey_FPC,"admpwd",passwd);

}
//---------------------------------------------------------------------------

