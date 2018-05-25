//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EFuseWriterViewerForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEFuseWriterViewer *EFuseWriterViewer;



//---------------------------------------------------------------------------
__fastcall TEFuseWriterViewer::TEFuseWriterViewer(TComponent* Owner)
        : TForm(Owner)
{
  m_p_common_arg = NULL;
  m_p_secure_arg = NULL;
  m_p_lock_arg = NULL;
  
  p_efuse_writer_handle = NULL;
  p_efuse_reader_handle_list = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::SetEfuseSettingLockFile(
				const AnsiString& SettingFile,
				const AnsiString& LockFile
				)
{
	this->m_SettingFilePath=SettingFile;
	this->m_LockFilePath=LockFile;
}
//---------------------------------------------------------------------------
MDT_ERROR_STATUS __fastcall TEFuseWriterViewer::set_efuse_reader_parameter(
									const CMDT_Efuse_Reader_Handle_List* p_handle
									)
{
  if ( NULL == p_handle)
  {
    return MDT_SV5_EFUSE_WRITER_INVALID_PARAMETER;
  }
  p_efuse_reader_handle_list = p_handle;

  return MDT_OK;
}
//---------------------------------------------------------------------------
MDT_ERROR_STATUS __fastcall TEFuseWriterViewer::set_efuse_writer_parameter(
				const CMDT_Efuse_Writer_Handle* p_handle
				)
{
  if ( NULL == p_handle)
  {
    return MDT_SV5_EFUSE_WRITER_INVALID_PARAMETER;
  }
  p_efuse_writer_handle = p_handle;
  return MDT_OK;
}

void __fastcall TEFuseWriterViewer::FormShow(TObject *Sender)
{
  try
  {
    if( NULL != p_efuse_reader_handle_list)
    {
      if(p_efuse_reader_handle_list->m_efuse_reader_list.size() <=0 )
      {
        return ;
      }
      this->EfuseReaderComPort->Visible = true;
      this->com_port_number_ComboBox->Visible = true;
      this->com_port_number_ComboBox->Clear();
      map<int,CMDT_Efuse_Reader_Handle>::const_iterator Iter;
      for(Iter  = p_efuse_reader_handle_list->m_efuse_reader_list.begin();
          Iter != p_efuse_reader_handle_list->m_efuse_reader_list.end();
          Iter++
          )
      {
        AnsiString ComPortString = IntToStr(Iter->first);
        this->com_port_number_ComboBox->Items->Add(ComPortString);
      }
        select_efuse_reader_item(0);
    }
    else if( NULL != p_efuse_writer_handle )
    {
      //non_secure customer
 	  m_p_common_arg = &p_efuse_writer_handle->m_common_arg;
	  m_p_secure_arg = &p_efuse_writer_handle->m_secure_arg;
	  m_p_lock_arg = &p_efuse_writer_handle->m_lock_arg;
	  
      if( is_common_user_setting(p_efuse_writer_handle))
      {
        ShowWriterNonSecureSetting();
	  }
	  else
	  {
        ShowWriterSecureSetting();
      }
    }
    else
    {
      
    }
  }
  catch(int e)
  {
  	Close();
  	Application->MessageBox(MDT_ErrorStatusToString(e),"EFuseParameterError",MB_ICONERROR);
  }
  catch(...)
  {
  	Close();
  	Application->MessageBox("Unknown Error","EFuseParameterError",MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowWriterFileName()
{
  if( m_SettingFilePath != "")
  {
    this->SettingFileDisplayLabel->Visible = true;
    this->SettingFilePathLabel->Caption = m_SettingFilePath;
    this->SettingFilePathLabel->Visible = true;
  }
  else
  {
    this->SettingFileDisplayLabel->Visible = false;
    this->SettingFilePathLabel->Visible = false;
  }
  
  if( m_LockFilePath != "")
  {
    this->LockFileDisplayLabel->Visible = true;
    this->LockFilePathLabel->Caption = m_LockFilePath;
    this->LockFilePathLabel->Visible = true;         
  }
  else
  {
    this->LockFileDisplayLabel->Visible = false;
    this->LockFilePathLabel->Visible = false;	 
  }
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowWriterSecureSetting()
{
  ShowWriterFileName();
  if( m_SettingFilePath != "")
  {
    this->EFuseSetting->TabVisible = true;
    ShowEFuseSettingACKey();
    ShowEFuseSettingCommonControl();
    ShowEFuseSettingUSBID();
    ShowEFuseSettingSpare();
    ShowEFuseSettingSecurityControl();
    ShowEFuseSettingSBCPublicKey();
  }
  else
  {
	  this->EFuseSetting->TabVisible = false;    
  }

  if( m_LockFilePath!= "")
  {
    this->EFuseLock->TabVisible = true;
    ShowEFuseLockSecureRegisterLock();
    ShowEFuseLockCommonRegisterLock();
  }
  else
  {
	  this->EFuseLock->TabVisible = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowWriterNonSecureSetting()
{
  ShowWriterFileName();
    if( m_SettingFilePath != "")
  {
    this->EFuseSetting->TabVisible = true;
    ShowEFuseSettingACKey();
  }
  else
  {
    this->EFuseSetting->TabVisible = false;
  }
  
  if( m_LockFilePath != "")
  {
    this->EFuseLock->TabVisible = true;
    ShowEFuseLockSecureRegisterLockForNonSecureChipUser();  
  }
  else
  {
    this->EFuseLock->TabVisible = false;
  }
  
}
//---------------------------------------------------------------------------

void __fastcall TEFuseWriterViewer::ShowEFuseCommonSetting()
{
  //Common Control
  this->Common_ControlGroup->Visible = true;
  
  this->CheckBoxDisable_EMMC_boot->Checked = (EFUSE_ACTIVE==this->m_p_common_arg->emmc_boot_dis);
  this->CheckBoxDisable_NAND_boot->Checked = (EFUSE_ACTIVE==this->m_p_common_arg->nand_boot_dis);
  this->CheckBoxDisable_NAND_boot_speedup->Checked = (EFUSE_ACTIVE==this->m_p_common_arg->nand_boot_speedup_dis);
  this->Disable_USB_AutoDetect_Label->Caption = IntToStr(m_p_common_arg->usbdl_type);
  
  //Spare
  this->SpareGroupBox->Visible = true;
  if(EFUSE_ACTIVE==this->m_p_common_arg->spare_blow)
  {
    AnsiString SpareDataString=(char*)this->m_p_common_arg->spare.buf;
    this->CheckBoxEnable_spare->Checked=true;
    this->Labelspare_byte->Caption=IntToStr(this->m_p_common_arg->spare_num_of_byte);
    this->Labelspare_data->Caption=SpareDataString;		
  }
	
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseSecureSetting()
{
  //Secure Common Setting
  this->Security_controlGroupBox->Visible = true;
  this->CheckBoxEnable_ACC->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->acc_en);
  this->CheckBoxEnable_SBC->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->sbc_en);
  this->CheckBoxEnable_DAA->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->daa_en);
  this->CheckBoxEnable_SLA->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->sla_en);
  this->CheckBoxEnable_ACK->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->ack_en);
  this->CheckBoxDisable_JTAG->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->jtag_dis);
  this->CheckBoxEnable_Root_Cert->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->root_cert_en);
  
  //Secure AC Key Setting
  this->AC_keyGroupBox->Visible = true;
  if(EFUSE_ACTIVE==this->m_p_secure_arg->ac_key_blow)
  {
  	this->CheckBoxEnable_ackey->Checked=true;
  	AnsiString ACKeyString=(char*)this->m_p_secure_arg->ac_key.buf;
  	this->Labelac_key->Caption=ACKeyString;
  }

/*
	if(EFUSE_ACTIVE==this->m_p_secure_arg->sbc_pubk_hash_blow)
	{
		this->CheckBoxEnable_sbc_pubK_hash->Checked=true;
		AnsiString PublicKeyE=(char*)this->m_p_secure_arg->sbc_pub_key.key_e.buf;
		AnsiString PublicKeyN=(char*)this->m_p_secure_arg->sbc_pub_key.key_n.buf;
		this->Labelpublic_key_e->Caption=PublicKeyE;
		this->Labelpublic_key_n->Caption=PublicKeyN;		
	}
*/
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseLock()
{
	//Common Register Lock Setting
	if(EFUSE_ACTIVE==this->m_p_lock_arg->common_ctrl_lock)
	{
		this->CheckBoxcom_ctrl_lock->Checked=true;
		this->CheckBoxcom_ctrl_lock->Font->Color=clRed;
	}
	else
	{
		this->CheckBoxcom_ctrl_lock->Checked=false;
		this->CheckBoxcom_ctrl_lock->Font->Color=clBlack;
	}
	if(EFUSE_ACTIVE==this->m_p_lock_arg->usb_id_lock)
	{
		this->CheckBoxusb_id_lock->Checked=true;
		this->CheckBoxusb_id_lock->Font->Color=clRed;
	}
	else
	{
		this->CheckBoxusb_id_lock->Checked=false;
		this->CheckBoxusb_id_lock->Font->Color=clBlack;
	}
	if(EFUSE_ACTIVE==this->m_p_lock_arg->spare_lock)
	{
		this->CheckBoxspare_lock->Checked=true;
		this->CheckBoxspare_lock->Font->Color=clRed;
	}
	else
	{
		this->CheckBoxspare_lock->Checked=false;
		this->CheckBoxspare_lock->Font->Color=clBlack;
	}

	//Secure Register Lock Setting
	if(EFUSE_ACTIVE==this->m_p_lock_arg->sec_ctrl_lock)
	{
		this->CheckBoxsec_attr_lock->Checked=true;
		this->CheckBoxsec_attr_lock->Font->Color=clRed;
	}
	else
	{
		this->CheckBoxsec_attr_lock->Checked=false;
		this->CheckBoxsec_attr_lock->Font->Color=clBlack;
	}
	if(EFUSE_ACTIVE==this->m_p_lock_arg->ackey_lock)
	{
		this->CheckBoxackey_lock->Checked=true;
		this->CheckBoxackey_lock->Font->Color=clRed;
	}
	else
	{
		this->CheckBoxackey_lock->Checked=false;
		this->CheckBoxackey_lock->Font->Color=clBlack;
	}
	if(EFUSE_ACTIVE==this->m_p_lock_arg->sbc_pubk_hash_lock)
	{
		this->CheckBoxsbc_pubk_hash_lock->Checked=true;
		this->CheckBoxsbc_pubk_hash_lock->Font->Color=clRed;
	}
	else
	{
		this->CheckBoxsbc_pubk_hash_lock->Checked=false;
		this->CheckBoxsbc_pubk_hash_lock->Font->Color=clBlack;
	}

}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::DisableEFuseCommonSetting()
{
	//Common Control
	this->CheckBoxDisable_EMMC_boot->Checked=false;
	this->CheckBoxDisable_EMMC_boot->Enabled=false;
	
	this->CheckBoxDisable_NAND_boot->Checked=false;
	this->CheckBoxDisable_NAND_boot->Enabled=false;
	
	this->CheckBoxDisable_NAND_boot_speedup->Checked=false;
	this->CheckBoxDisable_NAND_boot_speedup->Enabled=false;
	
	this->Disable_USB_AutoDetect_Label->Caption="";
//	this->CheckBoxDisable_USB_AutoDetect->Enabled=false;
	
	//USB ID
	this->CheckBoxEnable_ID->Checked=false;
	this->CheckBoxEnable_ID->Enabled=false;
	
	this->LabelUSB_PID->Visible=false;
	this->LabelUSB_VID->Visible=false;
	
	//Spare
	this->CheckBoxEnable_spare->Checked=false;
	this->CheckBoxEnable_spare->Enabled=false;

	this->Labelspare_byte->Visible=false;
	this->Labelspare_data->Visible=false;

}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::DisableEFuseSecureSetting()
{
	//Secure Common Setting
	this->CheckBoxEnable_ACC->Checked=false;
	this->CheckBoxEnable_ACC->Enabled=false;
	
	this->CheckBoxEnable_SBC->Checked=false;
	this->CheckBoxEnable_SBC->Enabled=false;
	
	this->CheckBoxEnable_DAA->Checked=false;
	this->CheckBoxEnable_DAA->Enabled=false;
	
	this->CheckBoxEnable_SLA->Checked=false;
	this->CheckBoxEnable_SLA->Enabled=false;

	this->CheckBoxEnable_ACK->Checked=false;
	this->CheckBoxEnable_ACK->Enabled=false;
		
	this->CheckBoxDisable_JTAG->Checked=false;
	this->CheckBoxDisable_JTAG->Enabled=false;

	this->CheckBoxEnable_Root_Cert->Checked=false;
	this->CheckBoxEnable_Root_Cert->Enabled=false;

	//Secure AC Key Setting
	this->CheckBoxEnable_ackey->Checked=false;
	this->CheckBoxEnable_ackey->Enabled=false;
	
	this->Labelac_key->Visible=false;
	
	//Secure AC Key Setting
	this->CheckBoxEnable_sbc_pubK_hash->Checked=false;
	this->CheckBoxEnable_sbc_pubK_hash->Enabled=false;
	
	this->Labelpublic_key_e->Visible=false;

	this->Labelpublic_key_n->Visible=false;		
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::DisableEFuseLock()
{
	//Common Register Lock Setting
	this->CheckBoxcom_ctrl_lock->Checked=false;
	this->CheckBoxcom_ctrl_lock->Enabled=false;
	
	this->CheckBoxusb_id_lock->Checked=false;
	this->CheckBoxusb_id_lock->Enabled=false;

	this->CheckBoxspare_lock->Checked=false;
	this->CheckBoxspare_lock->Enabled=false;

	this->CheckBoxsec_attr_lock->Checked=false;
	this->CheckBoxsec_attr_lock->Enabled=false;

	this->CheckBoxackey_lock->Checked=false;
	this->CheckBoxackey_lock->Enabled=false;

	this->CheckBoxsbc_pubk_hash_lock->Checked=false;
	this->CheckBoxsbc_pubk_hash_lock->Enabled=false;

}
//---------------------------------------------------------------------------
bool __fastcall TEFuseWriterViewer::is_common_user_setting(const CMDT_Efuse_Writer_Handle* p_wrier_handle)
{
  if( NULL == p_wrier_handle)
  {
    return true;
  }
  return p_wrier_handle->is_non_secure_user_setting();
}
//---------------------------------------------------------------------------
bool __fastcall TEFuseWriterViewer::is_common_user_setting(
	                                          const CMDT_Efuse_Reader_Handle_List* p_reader_handle_list)
{
  if( NULL == p_reader_handle_list)
  {
    return true;
  }
  else
  {
    return false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseSettingACKey()
{
  this->AC_keyGroupBox->Visible = true;

  if( EFUSE_ACTIVE == this->m_p_secure_arg->ac_key_blow)
  {
    this->Labelac_key->Caption = this->m_p_secure_arg->ac_key.buf;
	this->CheckBoxEnable_ackey->Checked = true;
  }
  else
  {
	  this->CheckBoxEnable_ackey->Checked = false;
  }

}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseSettingCommonControl()
{
  this->Common_ControlGroup->Visible = true;
  
  this->CheckBoxDisable_EMMC_boot->Checked = (EFUSE_ACTIVE==this->m_p_common_arg->emmc_boot_dis);
  this->CheckBoxDisable_NAND_boot->Checked = (EFUSE_ACTIVE==this->m_p_common_arg->nand_boot_dis);
  this->CheckBoxDisable_NAND_boot_speedup->Checked = (EFUSE_ACTIVE==this->m_p_common_arg->nand_boot_speedup_dis);
  this->Disable_USB_AutoDetect_Label->Caption = IntToStr(m_p_common_arg->usbdl_type);

}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseSettingUSBID()
{
  this->USB_ID_Group->Visible = true;
  if( EFUSE_ACTIVE == m_p_common_arg->usb_id_blow)
  {
    this->CheckBoxEnable_ID->Checked = true;
    this->LabelUSB_PID->Caption = "0x"+IntToHex((int)m_p_common_arg->usb_pid,4);
	this->LabelUSB_VID->Caption = "0x"+IntToHex((int)m_p_common_arg->usb_vid,4);        
  }
  else
  {
    this->CheckBoxEnable_ID->Checked = false;
    this->USB_PID_Display->Visible = false;
    this->USB_VIDDisplay->Visible = false;
    this->LabelUSB_PID->Visible = false;
	this->LabelUSB_VID->Visible = false;
  }
  
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseSettingSpare()
{
  this->SpareGroupBox->Visible = true;
  if( EFUSE_ACTIVE == m_p_common_arg->spare_blow)
  {
    this->CheckBoxEnable_spare->Checked = true;
	this->Labelspare_byte->Caption = IntToStr(m_p_common_arg->spare_num_of_byte);
	this->Labelspare_data->Caption = m_p_common_arg->spare.buf;
  }
  else
  {
    this->CheckBoxEnable_spare->Checked = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseSettingSecurityControl()
{
  this->Security_controlGroupBox->Visible = true;
  
  this->CheckBoxEnable_ACC->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->acc_en);
  this->CheckBoxEnable_SBC->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->sbc_en);
  this->CheckBoxEnable_DAA->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->daa_en);
  this->CheckBoxEnable_SLA->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->sla_en);
  this->CheckBoxEnable_ACK->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->ack_en);
  this->CheckBoxDisable_JTAG->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->jtag_dis);
  this->CheckBoxEnable_Root_Cert->Checked=(EFUSE_ACTIVE==this->m_p_secure_arg->root_cert_en);
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseSettingSBCPublicKey()
{
  this->SBC_public_keyGroupBox->Visible = true;
  if( EFUSE_ACTIVE == m_p_secure_arg->sbc_pubk_blow)
  {
    this->PublicKeyEDisplayLabel->Visible = true;
    this->PublicKeyNDisplayLabel->Visible = true;
    this->Labelpublic_key_e->Visible = true;
    this->Labelpublic_key_n->Visible = true;
    
    this->CheckBoxEnable_sbc_pubK_hash->Checked = true;
    this->Labelpublic_key_e->Caption = m_p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_e.buf;
    this->Labelpublic_key_n->Caption = m_p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_n.buf;
  }
  else
  {
    this->CheckBoxEnable_sbc_pubK_hash->Checked = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseSettingSBCHash()
{
  int length = 0;
  int index = 0 ;
  AnsiString Key = "";
  
  this->SBC_public_keyGroupBox->Visible = true;
  if( EFUSE_ACTIVE == m_p_secure_arg->sbc_pubk_blow)
  {
    length = m_p_secure_arg->sbc_pub_key_u.r_sbc_pub_key_hash.buf_len;
    Key = "";
    for(index=0 ; index<length ;index++)
    {
      Key = Key + IntToHex(m_p_secure_arg->sbc_pub_key_u.r_sbc_pub_key_hash.buf[index],2) +" ";
    }

    this->SBC_PublicKey_Hash_Display_Label->Visible = true;
    this->Labelpublic_key_n->Visible = true;
    this->Labelpublic_key_n->Caption = Key;    
  }
  else
  {
    this->CheckBoxEnable_sbc_pubK_hash->Checked = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseLockSecureRegisterLock()
{
  this->SecureLockSettingGroupBox->Visible = true;
  
  this->CheckBoxackey_lock->Visible = true;
  this->CheckBoxsec_attr_lock->Visible = true;
  this->CheckBoxsbc_pubk_hash_lock->Visible = true;
  
  
  //Secure Register Lock Setting
  if(EFUSE_ACTIVE==this->m_p_lock_arg->sec_ctrl_lock)
  {
    this->CheckBoxsec_attr_lock->Checked=true;
    this->CheckBoxsec_attr_lock->Font->Color=clRed;
  }
  else
  {
    this->CheckBoxsec_attr_lock->Checked=false;
    this->CheckBoxsec_attr_lock->Font->Color=clBlack;
  }
  if(EFUSE_ACTIVE==this->m_p_lock_arg->ackey_lock)
  {
    this->CheckBoxackey_lock->Checked=true;
    this->CheckBoxackey_lock->Font->Color=clRed;
  }
  else
  {
    this->CheckBoxackey_lock->Checked=false;
    this->CheckBoxackey_lock->Font->Color=clBlack;
  }
  if(EFUSE_ACTIVE==this->m_p_lock_arg->sbc_pubk_hash_lock)
  {
    this->CheckBoxsbc_pubk_hash_lock->Checked=true;
    this->CheckBoxsbc_pubk_hash_lock->Font->Color=clRed;
  }
  else
  {
    this->CheckBoxsbc_pubk_hash_lock->Checked=false;
    this->CheckBoxsbc_pubk_hash_lock->Font->Color=clBlack;
  }

}
void __fastcall TEFuseWriterViewer::ShowEFuseLockSecureRegisterLockForNonSecureChipUser()
{
	this->SecureLockSettingGroupBox->Visible = true;
	
	this->CheckBoxackey_lock->Visible = true;
	
	//Secure Register Lock Setting
	if(EFUSE_ACTIVE==this->m_p_lock_arg->ackey_lock)
	{
	  this->CheckBoxackey_lock->Checked=true;
	  this->CheckBoxackey_lock->Font->Color=clRed;
	}
	else
	{
	  this->CheckBoxackey_lock->Checked=false;
	  this->CheckBoxackey_lock->Font->Color=clBlack;
	}

}

//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseLockCommonRegisterLock()
{
  this->CommonRegisterLockSettingGroupBox->Visible = true;
  
  //Common Register Lock Setting
  if(EFUSE_ACTIVE==this->m_p_lock_arg->common_ctrl_lock)
  {
    this->CheckBoxcom_ctrl_lock->Checked=true;
    this->CheckBoxcom_ctrl_lock->Font->Color=clRed;
  }
  else
  {
    this->CheckBoxcom_ctrl_lock->Checked=false;
    this->CheckBoxcom_ctrl_lock->Font->Color=clBlack;
  }
  if(EFUSE_ACTIVE==this->m_p_lock_arg->usb_id_lock)
  {
    this->CheckBoxusb_id_lock->Checked=true;
    this->CheckBoxusb_id_lock->Font->Color=clRed;
  }
  else
  {
    this->CheckBoxusb_id_lock->Checked=false;
    this->CheckBoxusb_id_lock->Font->Color=clBlack;
  }
  if(EFUSE_ACTIVE==this->m_p_lock_arg->spare_lock)
  {
    this->CheckBoxspare_lock->Checked=true;
    this->CheckBoxspare_lock->Font->Color=clRed;
  }
  else
  {
    this->CheckBoxspare_lock->Checked=false;
    this->CheckBoxspare_lock->Font->Color=clBlack;
  }

}

//---------------------------------------------------------------------------
void TEFuseWriterViewer::select_efuse_reader_item(int index)
{
  AnsiString ComPortName = "";
  int ComPortNumber = 0;
  map<int,CMDT_Efuse_Reader_Handle>::const_iterator Iter;
  const CMDT_Efuse_Reader_Handle* p_efuse_reader_handle = NULL;
  
  if( NULL == p_efuse_reader_handle_list)
  {
    GC_TRACE_EX("p_efuse_reader_handle_list is NULL");
    return ;
  }
  if( index < 0 || index > (int)p_efuse_reader_handle_list->m_efuse_reader_list.size())
  {
    GC_TRACE_EX("index: %d  reader list size: %d"
                ,index,p_efuse_reader_handle_list->m_efuse_reader_list.size());
    return ;
  }
  com_port_number_ComboBox->ItemIndex = index;
  ComPortName = com_port_number_ComboBox->Items[0].Strings[index].c_str(); 
  ComPortNumber = StrToInt(ComPortName);

  Iter = p_efuse_reader_handle_list->m_efuse_reader_list.find(ComPortNumber);

  if(Iter == p_efuse_reader_handle_list->m_efuse_reader_list.end())
  {
    GC_TRACE_EX("can not find com port: %d",ComPortNumber);
  }
  p_efuse_reader_handle = &(Iter->second);

  ShowEfuseReaderItem(p_efuse_reader_handle);
}

//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEfuseReaderItem(const CMDT_Efuse_Reader_Handle* Item)
{
  if(NULL == Item)
  {
    return ;
  }
  m_p_common_arg = &(Item->m_common_arg);
  m_p_secure_arg= &(Item->m_secure_arg);
  m_p_lock_arg= &(Item->m_lock_arg);


  this->EFuseSetting->TabVisible = true;
  ShowEFuseReaderSettingACKey();
  ShowEFuseSettingCommonControl();
  ShowEFuseSettingUSBID();
  ShowEFuseReaderSettingSpare();
  ShowEFuseSettingSecurityControl();
  ShowEFuseSettingSBCHash();
  
  this->EFuseLock->TabVisible = true;
  ShowEFuseLockSecureRegisterLock();
  ShowEFuseLockCommonRegisterLock();

}

//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseReaderSettingACKey()
{
  int length = 0;
  int index = 0 ;
  AnsiString Key = "";
  this->AC_keyGroupBox->Visible = true;

  if( EFUSE_NONE == this->m_p_secure_arg->acc_en
    || EFUSE_ACTIVE == this->m_p_secure_arg->ac_key_blow)
  {
    this->CheckBoxEnable_ackey->Checked = false;
    this->Labelac_key->Visible = false;
    this->ACKeyDisplayLabel->Visible = false;
    return;
  }
  this->Labelac_key->Visible = true;
  this->ACKeyDisplayLabel->Visible = true;
  length = m_p_secure_arg->ac_key.buf_len;
  for(index = 0 ; index < length ;index++)
  {
    int temp_integer = (int)((unsigned char)m_p_secure_arg->ac_key.buf[index]&0xFF);
    Key = Key + IntToHex(temp_integer,2) +" ";
  }

  this->Labelac_key->Caption = Key;
  this->CheckBoxEnable_ackey->Checked = true; 

}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriterViewer::ShowEFuseReaderSettingSpare()
{
  int length = 0;
  int index = 0 ;
  AnsiString Key = "";
  
  this->SpareGroupBox->Visible = true;
  if( EFUSE_ACTIVE == m_p_common_arg->spare_blow)
  {
    length = m_p_common_arg->spare.buf_len;
    Key = "";
    for(index=0 ; index<length ;index++)
    {
      Key = Key + IntToHex(m_p_common_arg->spare.buf[index],2) +" ";
    }    
    this->CheckBoxEnable_spare->Checked = true;
	this->Labelspare_byte->Caption = IntToStr(m_p_common_arg->spare_num_of_byte);
	this->Labelspare_data->Caption = Key;   
  }
  else
  {
    this->CheckBoxEnable_spare->Checked = false;
    this->Labelspare_byte->Visible = false;
    this->Labelspare_data->Visible = false;    
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


void __fastcall TEFuseWriterViewer::com_port_number_ComboBoxChange(
      TObject *Sender)
{
   select_efuse_reader_item(com_port_number_ComboBox->ItemIndex);      
}
//---------------------------------------------------------------------------

