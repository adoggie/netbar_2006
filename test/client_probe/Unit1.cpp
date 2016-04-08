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
�б�msn�Ƿ�ɹ���¼
1.��ѯmsn�����������
2.��ȡ���˵�
3.������˵��ĵ�һ�������˵��ĵ�2��ע����Ĳ˵�״̬�����
  enable��ʾ��¼�ɹ���������Ϊ��¼ʧ��
*/


/*
�б�QQ�Ƿ�����
1.enumwindowö�ٴ����Ƿ�������Ϊ#32770�Ĵ���
2.findwidnow���Ҵ˴���������Ϊ    Tencent_QQBar
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
