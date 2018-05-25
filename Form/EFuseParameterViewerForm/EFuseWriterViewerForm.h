//---------------------------------------------------------------------------

#ifndef EFuseWriterViewerFormH
#define EFuseWriterViewerFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include "Brom_dll/inc/brom.h"
#include "MDT_Component/error_handler/inc/MDT_ErrorTypes.h"
#include "efusewriter/inc/EFuseWriter.h"
#include "efusewriter/inc/cmdtefusereaderhandle.h"

//---------------------------------------------------------------------------
class TEFuseWriterViewer : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *EFuseSetting;
        TTabSheet *EFuseLock;
        TGroupBox *Common_ControlGroup;
        TCheckBox *CheckBoxDisable_EMMC_boot;
        TCheckBox *CheckBoxDisable_NAND_boot;
        TCheckBox *CheckBoxDisable_NAND_boot_speedup;
        TGroupBox *USB_ID_Group;
        TCheckBox *CheckBoxEnable_ID;
        TGroupBox *SpareGroupBox;
        TCheckBox *CheckBoxEnable_spare;
        TGroupBox *Security_controlGroupBox;
        TCheckBox *CheckBoxEnable_ACC;
        TCheckBox *CheckBoxEnable_SBC;
        TCheckBox *CheckBoxEnable_DAA;
        TCheckBox *CheckBoxEnable_SLA;
        TCheckBox *CheckBoxEnable_ACK;
        TCheckBox *CheckBoxDisable_JTAG;
        TCheckBox *CheckBoxEnable_Root_Cert;
        TGroupBox *AC_keyGroupBox;
        TCheckBox *CheckBoxEnable_ackey;
        TLabel *Labelac_key;
        TGroupBox *SBC_public_keyGroupBox;
        TLabel *Labelpublic_key_e;
        TCheckBox *CheckBoxEnable_sbc_pubK_hash;
        TLabel *Labelpublic_key_n;
        TLabel *Labelspare_byte;
        TLabel *Labelspare_data;
        TLabel *LabelUSB_PID;
        TLabel *LabelUSB_VID;
        TLabel *USB_PID_Display;
        TLabel *USB_VIDDisplay;
        TLabel *SpareDataDisplay;
        TLabel *SpareBytesDisplay;
        TLabel *ACKeyDisplayLabel;
        TLabel *PublicKeyEDisplayLabel;
        TLabel *PublicKeyNDisplayLabel;
        TGroupBox *CommonRegisterLockSettingGroupBox;
        TCheckBox *CheckBoxcom_ctrl_lock;
        TCheckBox *CheckBoxusb_id_lock;
        TCheckBox *CheckBoxspare_lock;
        TLabel *SettingFileDisplayLabel;
        TLabel *LockFileDisplayLabel;
        TLabel *SettingFilePathLabel;
        TLabel *LockFilePathLabel;
        TGroupBox *SecureLockSettingGroupBox;
        TCheckBox *CheckBoxsec_attr_lock;
        TCheckBox *CheckBoxackey_lock;
        TCheckBox *CheckBoxsbc_pubk_hash_lock;
        TComboBox *com_port_number_ComboBox;
        TLabel *Disable_USB_AutoDetect_Display_Label;
        TLabel *Disable_USB_AutoDetect_Label;
        TLabel *SBC_PublicKey_Hash_Display_Label;
        TLabel *EfuseReaderComPort;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall com_port_number_ComboBoxChange(TObject *Sender);
private:	// User declarations
	AnsiString m_SettingFilePath;
	AnsiString m_LockFilePath;
	
	const Efuse_Common_Arg* m_p_common_arg;
	const Efuse_Secure_Arg* m_p_secure_arg;
	const Efuse_Lock_Arg* m_p_lock_arg;

	const CMDT_Efuse_Writer_Handle* p_efuse_writer_handle;
	const CMDT_Efuse_Reader_Handle_List* p_efuse_reader_handle_list;
public:		// User declarations
    __fastcall TEFuseWriterViewer(TComponent* Owner);

	virtual void __fastcall SetEfuseSettingLockFile(
					const AnsiString& SettingFile,
					const AnsiString& LockFile
					);
	virtual MDT_ERROR_STATUS __fastcall set_efuse_writer_parameter(
                                        const CMDT_Efuse_Writer_Handle* p_handle
                                        );
	virtual MDT_ERROR_STATUS __fastcall set_efuse_reader_parameter(
                                        const CMDT_Efuse_Reader_Handle_List* p_handle
                                        );

protected:
  virtual void __fastcall ShowEFuseCommonSetting();
  virtual void __fastcall ShowEFuseSecureSetting();
  virtual void __fastcall ShowEFuseLock();
  
  virtual void __fastcall DisableEFuseCommonSetting();
  virtual void __fastcall DisableEFuseSecureSetting();
  virtual void __fastcall DisableEFuseLock();

  virtual void __fastcall ShowEFuseSettingACKey();
  virtual void __fastcall ShowEFuseSettingCommonControl();
  virtual void __fastcall ShowEFuseSettingUSBID();
  virtual void __fastcall ShowEFuseSettingSpare();
  virtual void __fastcall ShowEFuseSettingSecurityControl();
  virtual void __fastcall ShowEFuseSettingSBCPublicKey();
  virtual void __fastcall ShowEFuseLockSecureRegisterLock();
  virtual void __fastcall ShowEFuseLockSecureRegisterLockForNonSecureChipUser();
  virtual void __fastcall ShowEFuseLockCommonRegisterLock();

  virtual void __fastcall ShowWriterFileName();
  virtual void __fastcall ShowWriterSecureSetting();
  virtual void __fastcall ShowWriterNonSecureSetting();

  virtual bool __fastcall is_common_user_setting(const CMDT_Efuse_Writer_Handle* p_wrier_handle);
  virtual bool __fastcall is_common_user_setting(const CMDT_Efuse_Reader_Handle_List* p_reader_handle_list);

  void select_efuse_reader_item(int index);	
  virtual void __fastcall ShowEfuseReaderItem(const CMDT_Efuse_Reader_Handle* Item);
  virtual void __fastcall ShowEFuseReaderSettingACKey();
  virtual void __fastcall ShowEFuseReaderSettingSpare();
  virtual void __fastcall ShowEFuseSettingSBCHash();
  
};
//---------------------------------------------------------------------------
extern PACKAGE TEFuseWriterViewer *EFuseWriterViewer;
//---------------------------------------------------------------------------
#endif
