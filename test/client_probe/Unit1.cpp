//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

/*
判别msn是否成功登录
1.查询msn的主窗体标题
2.获取主菜单
3.检测主菜单的第一个下拉菜单的第2项注销项的菜单状态，如果
  enable表示登录成功，否则认为登录失败
*/


/*
判别QQ是否启动
1.enumwindow枚举窗体是否在类名为#32770的窗体
2.findwidnow查找此窗体中类名为    Tencent_QQBar
*/
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    HWND hwnd;
    if( hwnd=FindWindow(0,"MSN Messenger")){
        HMENU hm = GetMenu(hwnd);
        if( hm ){
            //ShowMessage(AnsiString("items:")+GetMenuItemCount(hm));
            hm = GetSubMenu(hm,0);
            MENUINFO  mi;
            mi.cbSize = sizeof(mi);
            //GetMenuInfo(hm, &mi);
            char str[125];
            SendMessage(hwnd,WM_INITMENUPOPUP,(WPARAM)hm,1);
            if( GetMenuState(hm,1,MF_BYPOSITION) & MF_GRAYED){
                ShowMessage("msn offline");
            }else{
                ShowMessage("msn online");
            }
            //GetMenuString(hm,1,str,sizeof(str),MF_BYPOSITION);

        }
        //ShowMessage(" found msn");
    }
}
//---------------------------------------------------------------------------

TForm1 * f ;
BOOL CALLBACK enumproc(HWND hwnd,LPARAM lParam ){
    char str[256];
    GetClassName(hwnd,str,sizeof(str));
    HWND hchild;

    if( AnsiString(str) ==  "#32770"){
        hchild = GetWindow( hwnd,   GW_CHILD );
        while( hchild ){

            GetClassName(hchild,str,sizeof(str));
            if( AnsiString(str) == "Tencent_QQBar"){
                ShowMessage(" found QQ ");
                return false;
            }
            hchild = GetWindow( hchild,GW_HWNDNEXT );
        }


    }
        //f->Memo1->Lines->Add(str);
    return true;
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    f = this;
    EnumWindows( (WNDENUMPROC )enumproc,0);
}
//---------------------------------------------------------------------------
