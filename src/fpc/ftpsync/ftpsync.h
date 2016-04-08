//---------------------------------------------------------------------------

#ifndef ftpsyncH
#define ftpsyncH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <NMFtp.hpp>
#include <Psock.hpp>
//---------------------------------------------------------------------------
class Tdmftp : public TDataModule
{
__published:	// IDE-managed Components
    TNMFTP *ftpc;
private:	// User declarations
public:		// User declarations
    __fastcall Tdmftp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tdmftp *dmftp;
//---------------------------------------------------------------------------
#endif
