//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Form_EngineerPasswd.h"
#include "Des/inc/des.h"

#ifndef _MUTLIPORTFLASHDOWNLOADTOOL_H_
#include "MultiPortFlashDownloadTool.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Engineerpw *Form_Engineerpw;
//---------------------------------------------------------------------------
__fastcall TForm_Engineerpw::TForm_Engineerpw(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm_Engineerpw::btnCancelClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

bool __fastcall TForm_Engineerpw::VerifyPassWord(BYTE* pPassword)
{
    bool bRet = false;
    BYTE key[10]="03055030";
    int iDatalen=0;
    BYTE password[LOGIN_PASSWORD_MAX];

    if(ReadDataFromFile(password,LOGIN_PASSWORD_MAX, key, MainForm->m_asPasswdFilePath.c_str()) == S_DES_SUCCESS)
    {
        if(strcmp(password+2, pPassword)== 0)
        {            
	        password[0] = '0';
		    password[1] = '1';
		    if(WriteDataToFile(password, LOGIN_PASSWORD_MAX, key, MainForm->m_asPasswdFilePath.c_str())  == S_DES_SUCCESS)
		    {
		        MainForm->m_LoginIdentify = LOGIN_ENGINEER;
		        bRet = true;
		    }            
        }
    }

    return bRet;
}

void __fastcall TForm_Engineerpw::btnOKClick(TObject *Sender)
{
    if( VerifyPassWord(Edit_Passwd->Text.c_str()))
    {
         MainForm->Enable_UIComponent();
         Close();
    }
    else
    {
         Edit_Passwd->Text = "";
         Edit_Passwd->SetFocus();
         Application->MessageBox("Warning,the password is not correct, please try again!.", "Login mode", MB_OK);
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_Engineerpw::FormShow(TObject *Sender)
{
    Edit_Passwd->Text = "";
    Edit_Passwd->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm_Engineerpw::Edit_PasswdKeyPress(TObject *Sender,
      char &Key)
{
    if( Key == 0x0D )
    {
        btnOKClick(Sender);
    }
}
//---------------------------------------------------------------------------

