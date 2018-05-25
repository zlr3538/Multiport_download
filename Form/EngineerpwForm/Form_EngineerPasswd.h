//---------------------------------------------------------------------------

#ifndef Form_EngineerPasswdH
#define Form_EngineerPasswdH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm_Engineerpw : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label_Passwd;
        TEdit *Edit_Passwd;
        TButton *btnCancel;
        TButton *btnOK;
        TLabel *Label_Info;
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Edit_PasswdKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Engineerpw(TComponent* Owner);
		bool __fastcall VerifyPassWord(BYTE* pPassword);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Engineerpw *Form_Engineerpw;
//---------------------------------------------------------------------------
#endif
