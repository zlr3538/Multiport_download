//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "INIFileHandle/inc/INIFileHandle.h"
#include "SetBeginComPort.h"
#include "MultiPortFlashDownloadTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdlgSetBeginComPort *dlgSetBeginComPort;

extern PACKAGE TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TdlgSetBeginComPort::TdlgSetBeginComPort(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TdlgSetBeginComPort::FormShow(TObject *Sender)
{
    ed_begin_com_port->Text = MainForm->INIFileH.read_TheFirstComPortNo( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    this->SetFocusedControl(ed_begin_com_port);
}
//---------------------------------------------------------------------------

void __fastcall TdlgSetBeginComPort::cbBCPApplyClick(TObject *Sender)
{
   try
   {
       int old_begin_com_port, new_begin_com_port;

       old_begin_com_port = MainForm->INIFileH.read_TheFirstComPortNo( "MultiPortFlashDownloadProject.ini", Application->ExeName ).ToInt();

       new_begin_com_port = ed_begin_com_port->Text.ToInt();

       if(new_begin_com_port < 1 || new_begin_com_port > 80)
       {
          this->SetFocusedControl(ed_begin_com_port);
          throw EConvertError("Please input again!");
       }

       if(new_begin_com_port == old_begin_com_port)
       {
          dlgSetBeginComPort->Close();
          return;
       }

       MainForm->INIFileH.write_TheFirstComPortNo( "MultiPortFlashDownloadProject.ini", Application->ExeName,  ed_begin_com_port->Text);

       //Application->MessageBox("Setting has been applied, please reopen tool.", "Set begin COM port", MB_OK);

       dlgSetBeginComPort->Close();
   }
   catch(...)
   {
       this->SetFocusedControl(ed_begin_com_port);
       Application->MessageBox("Please input a valid value (1-80)! ", "Set begin COM port", MB_OK);
       return;
   }
}
//---------------------------------------------------------------------------

