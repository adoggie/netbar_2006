//---------------------------------------------------------------------------

#ifndef paramcfgH
#define paramcfgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormParam : public TForm
{
__published:	// IDE-managed Components
    TStaticText *StaticText1;
    TEdit *edtServer1;
    TEdit *edtPwd;
    TStaticText *StaticText2;
    TButton *Button1;
    TButton *Button2;
    TStaticText *StaticText3;
    TEdit *edtServer2;
    TStaticText *StaticText4;
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormParam(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormParam *FormParam;
//---------------------------------------------------------------------------
#endif
