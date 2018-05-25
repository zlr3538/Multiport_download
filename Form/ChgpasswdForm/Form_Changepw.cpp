//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Form_Changepw.h"
#include "Des/inc/des.h"

#ifndef _MUTLIPORTFLASHDOWNLOADTOOL_H_
#include "MultiPortFlashDownloadTool.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Chgpasswd *Form_Chgpasswd;
//---------------------------------------------------------------------------
__fastcall TForm_Chgpasswd::TForm_Chgpasswd(TComponent* Owner)
        : TForm(Owner)
{
}


//---------------------------------------------------------------------------
void __fastcall TForm_Chgpasswd::btnCancelClick(TObject *Sender)
{
    Close();        
}

bool __fastcall TForm_Chgpasswd::VerifyOldpasswd(BYTE* pOldassword)
{
    bool bRet = false;
    BYTE key[10]="03055030";
    int iDatalen=0;
    BYTE password[LOGIN_PASSWORD_MAX];
    
    if(ReadDataFromFile(password,LOGIN_PASSWORD_MAX, key, MainForm->m_asPasswdFilePath.c_str()) == S_DES_SUCCESS)
    {
        if(strcmp(password+2, pOldassword)== 0)
        {
            bRet = true;
        }
    }

    return bRet;
}

bool __fastcall TForm_Chgpasswd::ConfirmNewpasswd(BYTE* pNewPassword, BYTE* pConfPassword)
{
    if(strcmp(pNewPassword, pConfPassword)== 0)
    {
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------

void __fastcall TForm_Chgpasswd::btnOKClick(TObject *Sender)
{
    int iLen=0;
	BYTE key[10]="03055030";
	BYTE pOldpasswd[LOGIN_PASSWORD_MAX] = {0};
	BYTE pNewpasswd[LOGIN_PASSWORD_MAX] = {0};
	BYTE pConfpasswd[LOGIN_PASSWORD_MAX] = {0};	
	BYTE pPasswd[LOGIN_PASSWORD_MAX] = {0};

	strncpy(pOldpasswd, Edit_Oldpasswd->Text.c_str(), strlen(Edit_Oldpasswd->Text.c_str()));
	strncpy(pNewpasswd, Edit_Newpasswd->Text.c_str(), strlen(Edit_Newpasswd->Text.c_str()));
	strncpy(pConfpasswd, Edit_Confpasswd->Text.c_str(), strlen(Edit_Confpasswd->Text.c_str()));
	
    if( strlen(pOldpasswd) > 0)
	{
         if(VerifyOldpasswd(pOldpasswd))
         {
            if(ConfirmNewpasswd(pNewpasswd,pConfpasswd))
            {         
			   strncpy(pPasswd+2, pConfpasswd, strlen(pConfpasswd));
			   pPasswd[0] = '0';
			   pPasswd[1] = '1';
			   iLen = strlen(pPasswd);
               if(WriteDataToFile(pPasswd,iLen, key, MainForm->m_asPasswdFilePath.c_str()) == S_DES_SUCCESS)
               	{
                    ShowMessage(AnsiString("Set password success!"));				
                    Close();
               	}
            }
			else
			{
			    Edit_Newpasswd->Text = "";
			    Edit_Confpasswd->Text = "";
			    ShowMessage(AnsiString("New password and confirm password is not the same!"));
			}
         }
		 else
	     {
	         Edit_Oldpasswd->Text = "";
			 Edit_Newpasswd->Text = "";
			 Edit_Confpasswd->Text = "";
             ShowMessage(AnsiString("The password is not correct, please input correct engineer password!"));
             Edit_Oldpasswd->SetFocus();
         }

     }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Chgpasswd::FormShow(TObject *Sender)
{
    Edit_Oldpasswd->Text = "";
    Edit_Newpasswd->Text = "";
    Edit_Confpasswd->Text = "";
    Edit_Oldpasswd->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TForm_Chgpasswd::Edit_OldpasswdKeyPress(TObject *Sender,
      char &Key)
{
    if( Key == 0x0D )
    {
       Edit_Newpasswd->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Chgpasswd::Edit_NewpasswdKeyPress(TObject *Sender,
      char &Key)
{
    if( Key == 0x0D )
    {
       Edit_Confpasswd->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Chgpasswd::Edit_ConfpasswdKeyPress(TObject *Sender,
      char &Key)
{
    if( Key == 0x0D )
    {
        btnOKClick(Sender);
    }
}
//---------------------------------------------------------------------------

