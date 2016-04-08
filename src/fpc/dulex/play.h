//---------------------------------------------------------------------------

#ifndef playH
#define playH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------
class TFormPlay : public TForm
{
__published:	// IDE-managed Components
    TCppWebBrowser *wb;
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    int width,height;
public:		// User declarations
    void    SetBound(int w,int h){ width =w ; height = h;}
    void    ShowHtml(char * html);
    __fastcall TFormPlay(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPlay *FormPlay;
//---------------------------------------------------------------------------
#endif
