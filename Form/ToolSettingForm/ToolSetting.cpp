//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ToolSetting.h"
#include "MultiPortFlashDownloadTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Ttool_setting *tool_setting;

extern PACKAGE TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall Ttool_setting::Ttool_setting(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Ttool_setting::FormShow(TObject *Sender)
{
    Show_Format_FAT_page();
    Show_Com_Port_page();
    Show_Backup_Calibration_page();
    //deal with other page, for extension
    //...
}
//---------------------------------------------------------------------------

void __fastcall Ttool_setting::Show_Backup_Calibration_page(void)
{
    AnsiString folder_naming;
    folder_naming = MainForm->INIFileH.read_CalibrationFolderNamingRule("MultiPortFlashDownloadProject.ini", Application->ExeName);
     if(folder_naming=="RID")
    {
        this->checkbox_use_comport->Checked = false;
    }
    else
    {
        this->checkbox_use_comport->Checked = true;
    }

    //
    bool delete_flag = false ;
    delete_flag = MainForm->INIFileH.read_Delete_Calibration_After_RS( "MultiPortFlashDownloadProject.ini", Application->ExeName);
    if(delete_flag)
    {
        this->checkbox_delete_calibration->Checked = true;
    }
    else
    {
        this->checkbox_delete_calibration->Checked = false;
    }

    //
//    checkbox_delete_calibration
    if(checkbox_use_comport->Checked == false)
    {
      this->checkbox_delete_calibration->Enabled = true;
      this->Label_calibrationSetting->Enabled = true;
    }
    else
    {
      this->checkbox_delete_calibration->Enabled = false;
      this->Label_calibrationSetting->Enabled = false;
    }
}


void __fastcall Ttool_setting::Show_Com_Port_page(void)
{
    bool flag = MainForm->INIFileH.read_Disconnect_Comport_After_DL( "MultiPortFlashDownloadProject.ini", Application->ExeName );

    if(flag)
    {
        this->checkbox_disconnect_comport->Checked = true;
    }
    else
    {
        this->checkbox_disconnect_comport->Checked = false;
    }
}

void __fastcall Ttool_setting::Show_Format_FAT_page(void)
{
     AnsiString str;

    // get each value from ini and show

    str = MainForm->INIFileH.read_Format_FAT_Begin_Address( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    (str == "") ? str="0" : str;
    str = str.sprintf("%08X", str.ToInt());
    this->Edit_Begin_Address_NOR->Text = str;

    str = MainForm->INIFileH.read_Format_FAT_length( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    (str == "") ? str="0" : str;
    str = str.sprintf("%08X", str.ToInt());
    this->Edit_Length_NOR->Text = str;

    str = MainForm->INIFileH.read_NAND_Format_FAT_Begin_Address( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    (str == "") ? str="0" : str;
    str = str.sprintf("%08X", str.ToInt());
    this->Edit_Begin_Address_NAND->Text = str;

    str = MainForm->INIFileH.read_NAND_Format_FAT_length( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    (str == "") ? str="0" : str;
    str = str.sprintf("%08X", str.ToInt());
    this->Edit_Length_NAND->Text = str;

}

void __fastcall Ttool_setting::Deal_with_Format_FAT_page(void)
{
    AnsiString str;

    if(Edit_Begin_Address_NOR->Text == "")
    {
        Edit_Begin_Address_NOR->Text = "0";
    }
    if(Edit_Length_NOR->Text == "")
    {
        Edit_Length_NOR->Text = "0";
    }
    if(Edit_Begin_Address_NAND->Text == "")
    {
        Edit_Begin_Address_NAND->Text = "0";
    }
    if(Edit_Length_NAND->Text == "")
    {
        Edit_Length_NAND->Text = "0";
    }

    // I save nor begin address
    // 1 format to 8 char length string    //    3C000000 --> 03C00000  --> 0x03C00000
    str = "0x" + Edit_Begin_Address_NOR->Text;
    str = str.sprintf("0x%08X", str.ToInt());
    // 2 save to ini
    MainForm->INIFileH.write_Format_FAT_Begin_Address( "MultiPortFlashDownloadProject.ini", Application->ExeName,  str);

    // II save nor length
    str = "0x" + Edit_Length_NOR->Text;
    str = str.sprintf("0x%08X", str.ToInt());
    MainForm->INIFileH.write_Format_FAT_length( "MultiPortFlashDownloadProject.ini", Application->ExeName,  str);

    // III
    str = "0x" + Edit_Begin_Address_NAND->Text;
    str = str.sprintf("0x%08X", str.ToInt());
    MainForm->INIFileH.write_NAND_Format_FAT_Begin_Address( "MultiPortFlashDownloadProject.ini", Application->ExeName,  str);


    // IV save nand length
    str = "0x" + Edit_Length_NAND->Text;
    str = str.sprintf("0x%08X", str.ToInt());
    MainForm->INIFileH.write_NAND_Format_FAT_length( "MultiPortFlashDownloadProject.ini", Application->ExeName,  str);

    //// set to current data structure
    //  to avoid restart tool to take effect
    MainForm->Update_FormatFatAddressLength();
}

void __fastcall Ttool_setting::Deal_with_Com_Port_page(void)
{
    bool disconnect_flag = false ; //default

    // 1 get checked
    if(checkbox_disconnect_comport->Checked )
    {
        disconnect_flag = true;
    }
    // 2 save to ini
    MainForm->INIFileH.write_Disconnect_Comport_After_DL( "MultiPortFlashDownloadProject.ini", Application->ExeName, disconnect_flag);
    // 3 set to current data structure
    MainForm->Read_Disconnect_Comport_option();
}

void __fastcall Ttool_setting::Deal_with_Backup_Calibration_page(void)
{
	//rb_foldername1
	//rb_foldername2
       //calibration_folder_naming
    AnsiString folder_naming="RID";
    if(checkbox_use_comport->Checked)
    {
         folder_naming="COMPORT";
    }
     MainForm->INIFileH.write_CalibrationFolderNamingRule("MultiPortFlashDownloadProject.ini", Application->ExeName, folder_naming);

    //
    bool delete_flag = false ; //default
    if(checkbox_delete_calibration->Checked )
    {
        delete_flag = true;
    }
    MainForm->INIFileH.write_Delete_Calibration_After_RS( "MultiPortFlashDownloadProject.ini", Application->ExeName, delete_flag);

    MainForm->Read_CalibrationFolder_option();

}

void __fastcall Ttool_setting::setting_OKClick(TObject *Sender)
{
    Deal_with_Format_FAT_page();
    Deal_with_Com_Port_page();
    Deal_with_Backup_Calibration_page();

    //deal with other page, for extension
    //...

    Close();
}
//---------------------------------------------------------------------------

void __fastcall Ttool_setting::setting_CancelClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall Ttool_setting::On_Filter_Key_Press(TObject *Sender, char &Key)
{
    if(Key >= '0' && Key <= '9' ||  Key >= 'A' && Key <= 'F'
        ||  Key == '\b' )
    {
        //limit  the input to hex number
        //OK
    }
    else if(Key >= 'a' && Key <= 'f' )
    {
        Key -= 32;  //convert to upper case
    }
    else
    {
        Key = 0;    //invalid key, filter it
    }
    return;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall Ttool_setting::checkbox_use_comportClick(TObject *Sender)
{
 //ff
    if(checkbox_use_comport->Checked == false)
    {
      this->checkbox_delete_calibration->Enabled = true;
      this->Label_calibrationSetting->Enabled = true;
    }
    else
    {
      this->checkbox_delete_calibration->Enabled = false;
      this->Label_calibrationSetting->Enabled = false;
    }
}
//---------------------------------------------------------------------------


