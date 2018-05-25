//---------------------------------------------------------------------------

#ifndef Form_ChangepwH
#define Form_ChangepwH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm_Chgpasswd : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label_Oldpasswd;
        TLabel *Label_Newpasswd;
        TLabel *Label_Confpasswd;
        TEdit *Edit_Oldpasswd;
        TEdit *Edit_Newpasswd;
        TEdit *Edit_Confpasswd;
        TButton *btnCancel;
        TButton *btnOK;
        TLabel *Label1;
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Edit_OldpasswdKeyPress(TObject *Sender, char &Key);
        void __fastcall Edit_NewpasswdKeyPress(TObject *Sender, char &Key);
        void __fastcall Edit_ConfpasswdKeyPress(TObject *Sender,
          char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Chgpasswd(TComponent* Owner);
		bool __fastcall VerifyOldpasswd(BYTE* pOldpassword);
		bool __fastcall ConfirmNewpasswd(BYTE* pNewPassword, BYTE* pConfPassword);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Chgpasswd *Form_Chgpasswd;
//---------------------------------------------------------------------------
#endif
