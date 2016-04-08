//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "play.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TFormPlay *FormPlay;
//---------------------------------------------------------------------------
__fastcall TFormPlay::TFormPlay(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void    TFormPlay::ShowHtml(char * html){
    IPersistStreamInit *psi;
    wb->Navigate(WideString("about:blank"));
    wb->Document->QueryInterface(IID_IPersistStreamInit,(void**)&psi);
    HGLOBAL  gdata;
    IStream *istream;
    gdata = GlobalAlloc(GPTR,strlen( html)+1);
    strcpy( (char*)gdata,html);
    CreateStreamOnHGlobal(gdata,TRUE,&istream);
    psi->InitNew();
    psi->Load(istream);
    //GlobalFree(gdata);
}

void __fastcall TFormPlay::FormShow(TObject *Sender)
{
    ClientWidth = width;
    ClientHeight = height;
    int cx,cy;
    cx=GetSystemMetrics(SM_CXFULLSCREEN);
    cy=GetSystemMetrics(SM_CYFULLSCREEN);
  //  ShowMessage(AnsiString(cx)+"."+AnsiString(cy));
 //   ShowMessage(AnsiString(Width)+"."+AnsiString(Height));
    ShowWindow(this->Handle,SW_SHOW);
    SetWindowPos(this->Handle,HWND_TOPMOST,(cx-this->Width)/2,(cy-this->Height)/2,width,this->Height,SWP_SHOWWINDOW);

   // BringWindowToTop(this->Handle);
}
//---------------------------------------------------------------------------

