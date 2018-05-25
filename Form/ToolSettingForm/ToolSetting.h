//---------------------------------------------------------------------------

#ifndef ToolSettingH
#define ToolSettingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Ttool_setting : public TForm
{
__published:	// IDE-managed Components
        TPageControl *pc_setting_for_tool;
        TTabSheet *ts_FormatFAT;
        TButton *setting_OK;
        TGroupBox *GroupBox_NOR_Flash_FAT;
        TEdit *Edit_Begin_Address_NOR;
        TLabel *Label_Begin_Address_NOR;
        TLabel *Label_Length_NOR;
        TEdit *Edit_Length_NOR;
        TLabel *Label_0x_NOR1;
        TLabel *Label_0x_NOR2;
        TLabel *Label1_Hex_NOR1;
        TLabel *Label1_Hex_NOR2;
        TGroupBox *GroupBox_NAND_Flash_FAT;
        TLabel *Label_Begin_Address_NAND;
        TLabel *Label_Length_NAND;
        TLabel *Label_0x_NAND1;
        TLabel *Label_0x_NAND2;
        TLabel *Label1_Hex_NAND1;
        TLabel *Label1_Hex_NAND2;
        TEdit *Edit_Begin_Address_NAND;
        TEdit *Edit_Length_NAND;
        TButton *setting_Cancel;
        TTabSheet *ts_ComPort;
        TCheckBox *checkbox_disconnect_comport;
        TGroupBox *comport_usb_comport;
        TLabel *comport_description;
        TTabSheet *ts_Backup;
        TGroupBox *gb_calibration_setting;
        TGroupBox *GroupBox1;
        TLabel *Label_calibrationSetting;
        TCheckBox *checkbox_delete_calibration;
        TCheckBox *checkbox_use_comport;

		
        void __fastcall setting_OKClick(TObject *Sender);
        void __fastcall setting_CancelClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);

        void __fastcall Show_Format_FAT_page(void);
        void __fastcall Deal_with_Format_FAT_page(void);

        void __fastcall Show_Com_Port_page(void);
        void __fastcall Deal_with_Com_Port_page(void);

        void __fastcall Show_Backup_Calibration_page(void);
        void __fastcall Deal_with_Backup_Calibration_page(void);

        void __fastcall On_Filter_Key_Press(TObject *Sender, char &Key);
        //void __fastcall rb_foldername_ridClick(TObject *Sender);
        //void __fastcall rb_foldername_comClick(TObject *Sender);
        void __fastcall checkbox_use_comportClick(TObject *Sender);


private:	// User declarations
public:		// User declarations 
        __fastcall Ttool_setting(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Ttool_setting *tool_setting;
//---------------------------------------------------------------------------
#endif
