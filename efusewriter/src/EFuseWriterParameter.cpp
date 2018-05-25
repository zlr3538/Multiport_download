#include "efusewriter/inc/EFuseWriterParameter.h"

//===============================================================================================
//For eFuse Writer
TEFuseWriterParameterReader* G_EFuseWriterReader=NULL;


//==============*********Next Block is for class TEFuseWriterParameterReader***********======================

TEFuseWriterParameterReader::TEFuseWriterParameterReader(
)
{
	m_IsSettingParameterReady=false;
	m_IsLockParameterReady=false;
	
	m_IsAllParameterReady=false;
	m_SettingFile="";
	m_LockFile="";

	memset(&m_common_arg,0x00,sizeof(m_common_arg));
	memset(&m_secure_arg,0x00,sizeof(m_secure_arg));
	memset(&m_lock_arg,0x00,sizeof(m_lock_arg));	

	memset(ReadStringBuffer,0x00,sizeof(ReadStringBuffer));
}

TEFuseWriterParameterReader::~TEFuseWriterParameterReader()
{

}



unsigned short TEFuseWriterParameterReader::ReadUSBPID()
{
	AnsiString USBPID_String="";;
	unsigned short USB_PID=0x00;
	int USBPIDStringLength;

	memset(ReadStringBuffer,0x00,EFUSE_READ_BUFFERSIZE);
	
	USBPIDStringLength=GetPrivateProfileString("USB ID", "USB_PID","USB_PID_String",ReadStringBuffer,EFUSE_READ_BUFFERSIZE,m_SettingFile.c_str());
	if(0>=USBPIDStringLength)
	{
		GC_TRACE("USB ID==>USB_PID is Invalid.");
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;

	}

	USBPID_String=(char*)ReadStringBuffer;
	
	if(USBPID_String== "USB_PID_String")
	{
		GC_TRACE("USB ID==>USB_PID is Invalid.");	
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
	}

	USBPID_String=USBPID_String.Trim();
	//Hex format
	if((USBPID_String.SubString(0,2)).UpperCase()=="0X")
	{
		USBPID_String=USBPID_String.SubString(0,6);
	}
	else
	{
		USBPID_String=USBPID_String.SubString(0,5);		
	}
	USBPID_String=USBPID_String.Trim();

	USB_PID=0xFFFF&StrToInt(USBPID_String);
	GC_TRACE("USB ID==>USB_PID is 0x%04X",USB_PID);

	return USB_PID;
}

unsigned short TEFuseWriterParameterReader::ReadUSBVID()
{
	AnsiString USBVID_String;
	unsigned short USB_VID=0x00;
	int USBVID_Length=0;
	memset(ReadStringBuffer,0x00,EFUSE_READ_BUFFERSIZE);
	

	USBVID_Length=GetPrivateProfileString("USB ID", "USB_VID","USB_VID_String",ReadStringBuffer,EFUSE_READ_BUFFERSIZE,m_SettingFile.c_str());
	if(0>=USBVID_Length)
	{
		GC_TRACE("USB ID==>USB_VID is Invalid.");	
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
	}

	USBVID_String =(char*)ReadStringBuffer;
	if( USBVID_String=="USB_VID_String")
	{
		GC_TRACE("USB ID==>USB_VID is Invalid.");	
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
	}

	USBVID_String=USBVID_String.Trim();
	//Hex format
	if(USBVID_String.SubString(0,2).UpperCase()=="0X")
	{
		USBVID_String=USBVID_String.SubString(0,6);
	}
	else
	{
		USBVID_String=USBVID_String.SubString(0,5);		
	}
	USBVID_String=USBVID_String.Trim();

	USB_VID=0xFFFF&StrToInt(USBVID_String);
	GC_TRACE("USB ID==>USB_VID is 0x%04X",USB_VID);
	
	return USB_VID;

}



unsigned char* TEFuseWriterParameterReader::ReadStringFromSettingFile(
	const AnsiString Section, 
	const AnsiString Ident, 
	AnsiString Default,
	unsigned int* p_ReadLength
)
{
	unsigned int ReadStringLenth;
	unsigned char* pReadString=NULL;
	AnsiString TempString;
	
	memset(ReadStringBuffer,0x00,EFUSE_READ_BUFFERSIZE);

	ReadStringLenth=GetPrivateProfileString(Section.c_str(),Ident.c_str(),Default.c_str(),ReadStringBuffer,EFUSE_READ_BUFFERSIZE,m_SettingFile.c_str());
	if((0>=ReadStringLenth)||(EFUSE_READ_BUFFERSIZE<=ReadStringLenth))
	{
		GC_TRACE("%s==>%s data is invalid.",Section.c_str(),Ident.c_str());
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;		
	}
	TempString=(char*)ReadStringBuffer;
	if(TempString==Default)
	{
		GC_TRACE("%s==>%s data is invalid.",Section.c_str(),Ident.c_str());
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;		
	}

	*p_ReadLength=ReadStringLenth;
	pReadString=new char[ReadStringLenth+1];
	memset(pReadString,0x00,ReadStringLenth+1);
	memcpy(pReadString,ReadStringBuffer,ReadStringLenth);
	
	return pReadString;
}

unsigned char* TEFuseWriterParameterReader::ReadStringFromLockFile(
	const AnsiString Section, 
	const AnsiString Ident, 
	AnsiString Default,
	unsigned int* p_ReadLength

)
{
	unsigned int ReadStringLenth;
	unsigned char* pReadString=NULL;
	AnsiString TempString;
	
	memset(ReadStringBuffer,0x00,EFUSE_READ_BUFFERSIZE);

	ReadStringLenth=GetPrivateProfileString(Section.c_str(),Ident.c_str(),Default.c_str(),ReadStringBuffer,EFUSE_READ_BUFFERSIZE,m_LockFile.c_str());
	if((0>=ReadStringLenth)||(EFUSE_READ_BUFFERSIZE<=ReadStringLenth))
	{
		GC_TRACE("%s==>%s data is invalid.",Section.c_str(),Ident.c_str());
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;		
	}
	TempString=(char*)ReadStringBuffer;
	if(TempString==Default)
	{
		GC_TRACE("%s==>%s data is invalid.",Section.c_str(),Ident.c_str());
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;		
	}
	
	*p_ReadLength=ReadStringLenth;
	pReadString=new char[ReadStringLenth+1];
	memset(pReadString,0x00,ReadStringLenth+1);
	memcpy(pReadString,ReadStringBuffer,ReadStringLenth);
	
	return pReadString;

}




int TEFuseWriterParameterReader::ReadIntegerFromSettingFile(const AnsiString Section, const AnsiString Ident, int Default)
{
	int attribute_value;

	// Common Attribute
	attribute_value = GetPrivateProfileInt(Section.c_str(), Ident.c_str(),Default,m_SettingFile.c_str());
	if( 1 == attribute_value)
	{
		return EFUSE_ACTIVE;
	}
	else if(0 == attribute_value)
	{
		return EFUSE_NONE;
	}
	else
	{
		GC_TRACE("ReadIntegerFromSettingFile:  %s==>%s is Invalid.Read Value: 0x%08X",Section.c_str(),Ident.c_str(),attribute_value);
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
	}
	
}

int TEFuseWriterParameterReader::ReadIntegerFromLockFile(const AnsiString Section, const AnsiString Ident, int Default)
{
	int attribute_value;

	attribute_value = GetPrivateProfileInt(Section.c_str(), Ident.c_str(),Default,m_LockFile.c_str());

	if(1 == attribute_value)
	{
		return EFUSE_ACTIVE;
	}
	else if(0 == attribute_value)
	{
		return EFUSE_NONE;
	}
	else
	{
		GC_TRACE("ReadIntegerFromLockFile:  %s==>%s is Invalid.Read Value: 0x%08X",Section.c_str(),Ident.c_str(),attribute_value);
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_LOCK_FILE;
	}

}


MDT_ERROR_STATUS TEFuseWriterParameterReader::SetEFuseWriterSettingFile(const AnsiString& SettingFile)
{
	this->m_IsAllParameterReady=false;
	
	try
	{
		if(!FileExists(SettingFile))
		{
			throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
		}
		m_SettingFile=SettingFile;
		
	}
	catch(...)
	{
		throw;
	}
	
	return MDT_OK;
}
MDT_ERROR_STATUS TEFuseWriterParameterReader::CheckSettingLockFile()
{
	if(m_SettingFile=="")
	{
		return MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
	}
	if(m_LockFile=="")
	{
		return MDT_SV5_EFUSE_WRITER_INVALID_LOCK_FILE;
	}
	return MDT_OK;
}

MDT_ERROR_STATUS TEFuseWriterParameterReader::SetEFuseWriterLockFile(const AnsiString& LockFile)
{
	this->m_IsAllParameterReady=false;

	try
	{
		if(!FileExists(LockFile))
		{
			throw (int)MDT_SV5_EFUSE_WRITER_INVALID_LOCK_FILE;
		}
		m_LockFile=LockFile;

	}
	catch(...)
	{
		throw;
	}
	
	return MDT_OK;

}

MDT_ERROR_STATUS TEFuseWriterParameterReader::GetEfuseCommonArg()
{
	int attribute_value;
	
	try
	{

		m_common_arg.emmc_boot_dis=ReadIntegerFromSettingFile("Common control", "Disable_EMMC_boot",EFUSE_WEIRD_CODE);
		
		m_common_arg.nand_boot_dis=ReadIntegerFromSettingFile("Common control", "Disable_NAND_boot", EFUSE_WEIRD_CODE);

		m_common_arg.nand_boot_speedup_dis=ReadIntegerFromSettingFile("Common control", "Disable_NAND_boot_speedup", EFUSE_WEIRD_CODE);

		//This line is modified on Mar_31
//		m_common_arg.usbdl_type=ReadIntegerFromSettingFile("Common control", "Disable_USB_AutoDetect", EFUSE_WEIRD_CODE);
		m_common_arg.usbdl_type=ReadIntegerFromSettingFile("Common control", "USB_download_type", EFUSE_WEIRD_CODE);

		//Read USB PID
		/*
		m_common_arg.usb_pid_blow=ReadIntegerFromSettingFile("USB ID", "Enable_PID", EFUSE_WEIRD_CODE);
		if(EFUSE_ACTIVE==m_common_arg.usb_pid_blow)
		{
			m_common_arg.usb_pid=ReadUSBPID();
		}

		//Read USB VID
		m_common_arg.usb_vid_blow=ReadIntegerFromSettingFile("USB ID", "Enable_VID", EFUSE_WEIRD_CODE);
		if(EFUSE_ACTIVE==m_common_arg.usb_vid_blow)
		{
			m_common_arg.usb_vid=ReadUSBVID();
		}
		*/
		//Read Spare Data
		m_common_arg.spare_blow=ReadIntegerFromSettingFile("Spare", "Enable_spare", EFUSE_WEIRD_CODE);		
		if(EFUSE_ACTIVE==m_common_arg.spare_blow)
		{
			m_common_arg.spare_num_of_byte=GetPrivateProfileInt("Spare", "spare_byte", EFUSE_WEIRD_CODE,m_SettingFile.c_str());	
			if(EFUSE_WEIRD_CODE==m_common_arg.spare_num_of_byte)
			{
				throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
			}
			m_common_arg.spare.buf=ReadStringFromSettingFile("Spare","spare data","Spare_String",&m_common_arg.spare.buf_len);
		}
		
	}
	catch(...)
	{
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
	}
	return MDT_OK;

}
MDT_ERROR_STATUS TEFuseWriterParameterReader::GetEfuseSecureArg()
{
	try
	{
		// Secure Attribute
		m_secure_arg.acc_en= ReadIntegerFromSettingFile("Security control", "Enable_ACC", EFUSE_WEIRD_CODE);
		m_secure_arg.sbc_en= ReadIntegerFromSettingFile("Security control", "Enable_SBC", EFUSE_WEIRD_CODE);
		m_secure_arg.daa_en= ReadIntegerFromSettingFile("Security control", "Enable_DAA", EFUSE_WEIRD_CODE);
		m_secure_arg.sla_en= ReadIntegerFromSettingFile("Security control", "Enable_SLA", EFUSE_WEIRD_CODE);
		m_secure_arg.ack_en= ReadIntegerFromSettingFile("Security control", "Enable_ACK", EFUSE_WEIRD_CODE);
		m_secure_arg.jtag_dis= ReadIntegerFromSettingFile("Security control", "Disable_JTAG", EFUSE_WEIRD_CODE);
		m_secure_arg.root_cert_en= ReadIntegerFromSettingFile("Security control", "Enable_Root_Cert", EFUSE_WEIRD_CODE);
/*
		m_secure_arg.sbc_pubk_hash_blow= ReadIntegerFromSettingFile("SBC public key", "Enable_sbc_pubK_hash", EFUSE_WEIRD_CODE);
		if(EFUSE_ACTIVE==m_secure_arg.sbc_pubk_hash_blow)
		{
			m_secure_arg.sbc_pub_key.key_e.buf=ReadStringFromSettingFile(
														"SBC public key",
														"public_key_e",
														"public_key_E",
														&m_secure_arg.sbc_pub_key.key_e.buf_len
													);
			m_secure_arg.sbc_pub_key.key_n.buf=ReadStringFromSettingFile(
														"SBC public key",
														"public_key_n",
														"public_key_N",
														&m_secure_arg.sbc_pub_key.key_n.buf_len
													);
		}
*/		
		m_secure_arg.ac_key_blow= ReadIntegerFromSettingFile("AC key", "Enable_ackey", EFUSE_WEIRD_CODE);
		if(EFUSE_ACTIVE==m_secure_arg.ac_key_blow)
		{
			m_secure_arg.ac_key.buf=ReadStringFromSettingFile(
														"AC key",
														"ac_key",
														"ac_key_Value",
														&m_secure_arg.ac_key.buf_len
													);
		}		
		
	}
	catch(...)
	{
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
	}
	return MDT_OK;

}

MDT_ERROR_STATUS TEFuseWriterParameterReader::GetEfuseLockArg()
{
#if 0
	int IsLockAllCommonRegister=0;
	int IsLockAllSecureRegister=0;
	
	try
	{
		IsLockAllCommonRegister=ReadIntegerFromLockFile("Common Lock","lock_regsiter_common",EFUSE_WEIRD_CODE);
		IsLockAllSecureRegister=ReadIntegerFromLockFile("Secure Lock", "lock_register_secure",EFUSE_WEIRD_CODE);

		//Read Common Lock Region
		m_p_lock_arg->common_ctrl_lock=ReadIntegerFromLockFile("Common Lock","com_ctrl_lock",EFUSE_WEIRD_CODE);
		if(EFUSE_ACTIVE==m_p_lock_arg->common_ctrl_lock)
		{
			if(EFUSE_NONE==IsLockAllCommonRegister)
			{
				throw MDT_SV5_EFUSE_WRITER_INVALID_LOCK_SETTING;
			}
		}
		
		m_p_lock_arg->usb_id_lock=ReadIntegerFromLockFile("Common Lock","usb_id_lock",EFUSE_WEIRD_CODE);
		if(EFUSE_ACTIVE==m_p_lock_arg->usb_id_lock)
		{
			if(EFUSE_NONE==IsLockAllCommonRegister)
			{
				throw MDT_SV5_EFUSE_WRITER_INVALID_LOCK_SETTING;
			}
		}
		
		m_p_lock_arg->spare_lock=ReadIntegerFromLockFile("Common Lock","spare_lock",EFUSE_WEIRD_CODE);
		if(EFUSE_ACTIVE==m_p_lock_arg->spare_lock)
		{
			if(EFUSE_NONE==IsLockAllCommonRegister)
			{
				throw MDT_SV5_EFUSE_WRITER_INVALID_LOCK_SETTING;
			}
		}

		//Read Secure Lock Region
		m_p_lock_arg->sec_ctrl_lock=ReadIntegerFromLockFile("Common Lock","sec_attr_lock",EFUSE_WEIRD_CODE);
		if(EFUSE_ACTIVE==m_p_lock_arg->sec_ctrl_lock)
		{
			if(EFUSE_NONE==IsLockAllCommonRegister)
			{
				throw MDT_SV5_EFUSE_WRITER_INVALID_LOCK_SETTING;
			}
		}
		m_p_lock_arg->ackey_lock=ReadIntegerFromLockFile("Common Lock","ackey_lock",EFUSE_WEIRD_CODE);
		if(EFUSE_ACTIVE==m_p_lock_arg->ackey_lock)
		{
			if(EFUSE_NONE==IsLockAllCommonRegister)
			{
				throw MDT_SV5_EFUSE_WRITER_INVALID_LOCK_SETTING;
			}
		}
		m_p_lock_arg->sbc_pubk_hash_lock=ReadIntegerFromLockFile("Common Lock","sbc_pubk_hash_lock",EFUSE_WEIRD_CODE);
		if(EFUSE_ACTIVE==m_p_lock_arg->sbc_pubk_hash_lock)
		{
			if(EFUSE_NONE==IsLockAllCommonRegister)
			{
				throw MDT_SV5_EFUSE_WRITER_INVALID_LOCK_SETTING;
			}
		}		
		
	}
	catch(...)
	{
		throw;
	}
	return MDT_OK;
#else
	try
	{
		// lock_all_common_register will lock common_ctrl, usb id , spare ergister
		int attribute_value = GetPrivateProfileInt("Common Lock", "lock_regsiter_common", -1, m_LockFile.c_str());
		if(attribute_value == 1)
		{
			m_lock_arg.common_ctrl_lock = EFUSE_ACTIVE;
			m_lock_arg.usb_id_lock = EFUSE_ACTIVE;
			m_lock_arg.spare_lock = EFUSE_ACTIVE;
		}
		else if(attribute_value == 0)
		{
			m_lock_arg.common_ctrl_lock = EFUSE_NONE;
			m_lock_arg.usb_id_lock = EFUSE_NONE;
			m_lock_arg.spare_lock = EFUSE_NONE;	
		}
		else
		{
			GC_TRACE("Common Lock==>lock_all_common_register: Value is 0x%08X",attribute_value);
			throw (int)MDT_SV5_EFUSE_WRITER_ALL_COMMON_REGISTER_SETTING_ERROR;
		}
		
		// lock_all_secure_register will lock sec_ctrl, ackey, sbc_pubk_hash
		attribute_value = GetPrivateProfileInt("Secure Lock", "lock_register_secure", -1, m_LockFile.c_str());
		if(attribute_value == 1)
		{
			m_lock_arg.sec_ctrl_lock = EFUSE_ACTIVE;
			m_lock_arg.ackey_lock = EFUSE_ACTIVE;
			m_lock_arg.sbc_pubk_hash_lock = EFUSE_ACTIVE;
		}
		else if(attribute_value == 0)
		{
			m_lock_arg.sec_ctrl_lock = EFUSE_NONE;
			m_lock_arg.ackey_lock = EFUSE_NONE;
			m_lock_arg.sbc_pubk_hash_lock = EFUSE_NONE;
		}
		else
		{
			GC_TRACE("Secure Lock==>lock_all_secure_register: Value is 0x%08X",attribute_value);
			throw (int)MDT_SV5_EFUSE_WRITER_ALL_SECURE_REGISTER_SETTING_ERROR;
		}
	
		
		attribute_value = GetPrivateProfileInt("Common Lock", "com_ctrl_lock", -1, m_LockFile.c_str());
		if(attribute_value == 1)
		{
			if(m_lock_arg.common_ctrl_lock == EFUSE_NONE)  // not match lock_all_common_register, send error
			{
				GC_TRACE("Common Lock==>com_ctrl_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_COMMON_LOCK_REGISTER_NOT_MATCH;
			}

			m_lock_arg.common_ctrl_lock = EFUSE_ACTIVE;			
		}
		else
		{
			if(attribute_value == 0 && m_lock_arg.common_ctrl_lock == EFUSE_ACTIVE)	// not match lock_all_common_register, send error
			{
				GC_TRACE("Common Lock==>com_ctrl_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_COMMON_LOCK_REGISTER_NOT_MATCH;
			}
			if(m_lock_arg.common_ctrl_lock == 0)
			{
				m_lock_arg.common_ctrl_lock = EFUSE_NONE;
			}
		}
	
		attribute_value = GetPrivateProfileInt("Common Lock", "usb_id_lock", -1, m_LockFile.c_str());
		if(attribute_value == 1)
		{
			if(m_lock_arg.usb_id_lock == EFUSE_NONE)		// not match lock_all_common_register, send error
			{
				GC_TRACE("Common Lock==>usb_id_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_COMMON_LOCK_REGISTER_NOT_MATCH;
			}

			m_lock_arg.usb_id_lock = EFUSE_ACTIVE;
			
		}
		else
		{
			if(attribute_value == 0 && m_lock_arg.usb_id_lock == EFUSE_ACTIVE)	// not match lock_all_common_register, send error
			{
				GC_TRACE("Common Lock==>usb_id_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_COMMON_LOCK_REGISTER_NOT_MATCH;
			}

			if(m_lock_arg.usb_id_lock == 0)
			{
				m_lock_arg.usb_id_lock = EFUSE_NONE;
			}
		}
	
		attribute_value = GetPrivateProfileInt("Common Lock", "spare_lock", -1, m_LockFile.c_str());
		if(attribute_value == 1)
		{
			if(m_lock_arg.spare_lock == EFUSE_NONE)		// not match lock_all_common_register, send error
			{
				GC_TRACE("Common Lock==>spare_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_COMMON_LOCK_REGISTER_NOT_MATCH;
			}

			m_lock_arg.spare_lock = EFUSE_ACTIVE;
			
		}
		else
		{
			if(attribute_value == 0 && m_lock_arg.spare_lock == EFUSE_ACTIVE) 	// not match lock_all_common_register, send error
			{
				GC_TRACE("Common Lock==>spare_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_COMMON_LOCK_REGISTER_NOT_MATCH;
			}

			if(m_lock_arg.spare_lock == 0)
			{
				m_lock_arg.spare_lock = EFUSE_NONE;
			}
		}
	
		attribute_value = GetPrivateProfileInt("Secure Lock", "sec_attr_lock", -1, m_LockFile.c_str());
		if(attribute_value == 1)
		{
			if(m_lock_arg.sec_ctrl_lock == EFUSE_NONE)	// not match lock_all_secure_register, send error
			{
				GC_TRACE("Secure Lock==>sec_attr_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_SECURE_LOCK_REGISTER_NOT_MATCH;
			}

			m_lock_arg.sec_ctrl_lock = EFUSE_ACTIVE;
			
		}
		else
		{
			if(attribute_value == 0 && m_lock_arg.sec_ctrl_lock == EFUSE_ACTIVE)		 // not match lock_all_secure_register, send error
			{
				GC_TRACE("Secure Lock==>sec_attr_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_SECURE_LOCK_REGISTER_NOT_MATCH;
			}

			if(m_lock_arg.sec_ctrl_lock == 0)
			{
				m_lock_arg.sec_ctrl_lock = EFUSE_NONE;
			}
		}
	
		attribute_value = GetPrivateProfileInt("Secure Lock", "ackey_lock", -1, m_LockFile.c_str());
		if(attribute_value == 1)
		{
			if(m_lock_arg.ackey_lock == EFUSE_NONE)		 // not match lock_all_secure_register, send error
			{
				GC_TRACE("Secure Lock==>ackey_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_SECURE_LOCK_REGISTER_NOT_MATCH;
			}

			m_lock_arg.ackey_lock = EFUSE_ACTIVE;
			
		}
		else
		{
			if(attribute_value == 0 &&m_lock_arg.ackey_lock == EFUSE_ACTIVE)		 // not match lock_all_secure_register, send error
			{
				GC_TRACE("Secure Lock==>ackey_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_SECURE_LOCK_REGISTER_NOT_MATCH;
			}

			if(m_lock_arg.ackey_lock == 0)					// If no assign the value of "lock_all_secure_register", set disable
				m_lock_arg.ackey_lock = EFUSE_NONE;
			
		}
	
		attribute_value = GetPrivateProfileInt("Secure Lock", "sbc_pubk_hash_lock", -1, m_LockFile.c_str());
		if(attribute_value == 1)
		{
			if(m_lock_arg.sbc_pubk_hash_lock == EFUSE_NONE)		 // not match lock_all_secure_register, send error
			{
				GC_TRACE("Secure Lock==>sbc_pubk_hash_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_SECURE_LOCK_REGISTER_NOT_MATCH;
			}

			m_lock_arg.sbc_pubk_hash_lock = EFUSE_ACTIVE;
			
		}
		else
		{
			if(attribute_value == 0 && m_lock_arg.sbc_pubk_hash_lock == EFUSE_ACTIVE)  // not match lock_all_secure_register, send error
			{
				GC_TRACE("Secure Lock==>sbc_pubk_hash_lock Not Match: Value is 0x%08X",attribute_value);
				throw (int)MDT_SV5_EFUSE_WRITER_SECURE_LOCK_REGISTER_NOT_MATCH;
			}

			if(m_lock_arg.sbc_pubk_hash_lock == 0)				// If no assign the value of "lock_all_secure_register", set disable
				m_lock_arg.sbc_pubk_hash_lock = EFUSE_NONE;
			
		}
	}
	catch(...)
	{
		throw ;
	}
	
	return MDT_OK;
	
#endif

}

MDT_ERROR_STATUS TEFuseWriterParameterReader::ParseEFuseWriteParameter()
{
	m_IsSettingParameterReady=false;
	
	if(m_SettingFile=="")
	{
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
	}
	GetEfuseCommonArg();
	GetEfuseSecureArg();
	
	m_IsSettingParameterReady=true;
	if(m_IsLockParameterReady==true)
	{
		m_IsAllParameterReady=true;
	}
	return MDT_OK;
}

MDT_ERROR_STATUS TEFuseWriterParameterReader::ParseEFuseLockParameter()
{
	m_IsLockParameterReady=false;
	if(m_LockFile=="")
	{
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_LOCK_FILE;
	}
	

	GetEfuseLockArg();	


	m_IsLockParameterReady=true;
	if(m_IsSettingParameterReady==true)
	{
		m_IsAllParameterReady=true;
	}
	return MDT_OK;
}




MDT_ERROR_STATUS TEFuseWriterParameterReader::ParseEFuseWriteLockParameter()
{
	this->m_IsAllParameterReady=false;

	ParseEFuseWriteParameter();
	ParseEFuseLockParameter();
	
	this->m_IsAllParameterReady=true;
	return MDT_OK;
}


MDT_ERROR_STATUS TEFuseWriterParameterReader::GetEFuseWriteParameter(
					Efuse_Common_Arg* p_common_arg,
					Efuse_Secure_Arg* p_secure_arg
)
{
	if(NULL==p_common_arg || NULL==p_secure_arg )
	{
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_PARAMETER;
	}
	if(m_SettingFile=="")
	{
		throw (int)MDT_SV5_EFUSE_WRITER_SETTING_FILE_IS_NULL;
	}
	if(	m_IsSettingParameterReady==false)
	{
		throw (int)MDT_SV5_EFUSE_WRITER_WRITE_SETTING_IS_NOT_READY;
	}
	memcpy(p_common_arg,&m_common_arg,sizeof(m_common_arg));
	memcpy(p_secure_arg,&m_secure_arg,sizeof(m_secure_arg));
	
	return MDT_OK;

}


MDT_ERROR_STATUS TEFuseWriterParameterReader::GetEFuseLockParameter( Efuse_Lock_Arg* p_lock_arg)
{
	if( NULL==p_lock_arg)
	{
		throw (int)MDT_SV5_EFUSE_WRITER_INVALID_PARAMETER;
	}

	if(	m_IsLockParameterReady==false)
	{
		throw (int)MDT_SV5_EFUSE_WRITER_LOCK_SETTING_IS_NOT_READY;
	}

	if(m_LockFile=="")
	{
		throw (int)MDT_SV5_EFUSE_WRITER_LOCK_FILE_IS_NULL;
	}
	memcpy(p_lock_arg,&m_lock_arg,sizeof(Efuse_Lock_Arg));
	
	return MDT_OK;
}


MDT_ERROR_STATUS TEFuseWriterParameterReader::GetEFuseWriteLockParameter(
					Efuse_Common_Arg* p_common_arg,		  
					Efuse_Secure_Arg* p_secure_arg,
					Efuse_Lock_Arg* p_lock_arg
)
{
	if(false==this->m_IsAllParameterReady)
	{
		throw (int)MDT_SV5_EFUSE_WRITER_IS_NOT_READY;
	}
	GetEFuseWriteParameter(p_common_arg,p_secure_arg);
	GetEFuseLockParameter(p_lock_arg);

	return MDT_OK;
}

MDT_ERROR_STATUS TEFuseWriterParameterReader::GetSettingLockFilePath(
					AnsiString& SettingFile,
					AnsiString& LockFile
)
{
	if(m_SettingFile=="" && m_LockFile=="")
	{
		throw string("You should select at least one Ini File.");
	}
	SettingFile=this->m_SettingFile;
	LockFile=this->m_LockFile;

        return MDT_OK;
}


MDT_ERROR_STATUS TEFuseWriterParameterReader::Clear()
{
	ClearSettingParameter();
	ClearLockParameter();
	return MDT_OK;
}
MDT_ERROR_STATUS TEFuseWriterParameterReader::ClearSettingParameter()
{
	this->m_SettingFile="";
	memset(&m_common_arg,0x00,sizeof(m_common_arg));
	memset(&m_secure_arg,0x00,sizeof(m_secure_arg));
	memset(ReadStringBuffer,0x00,sizeof(ReadStringBuffer));

	return MDT_OK;
}
MDT_ERROR_STATUS TEFuseWriterParameterReader::ClearLockParameter()
{
	this->m_LockFile="";
	memset(&m_lock_arg,0x00,sizeof(m_lock_arg));
	memset(ReadStringBuffer,0x00,sizeof(ReadStringBuffer));
	return MDT_OK;

}

#if 0
MDT_ERROR_STATUS TEFuseWriterParameterReader::GetEFuseSettingLockParameter(
					Efuse_Common_Arg** p_p_common_arg,		  
					Efuse_Secure_Arg** p_p_secure_arg,
					Efuse_Lock_Arg** p_p_lock_arg
)
{
	GetEFuseSettingParameter(p_p_common_arg,p_p_secure_arg);
	GetEFuseLockParameter(p_p_lock_arg);
	return MDT_OK;
}

MDT_ERROR_STATUS TEFuseWriterParameterReader::GetEFuseSettingParameter(
					Efuse_Common_Arg** p_p_common_arg,		  
					Efuse_Secure_Arg** p_p_secure_arg
)
{
	*p_p_common_arg=&m_common_arg;
	*p_p_secure_arg=&m_secure_arg;
	return MDT_OK;
}

MDT_ERROR_STATUS TEFuseWriterParameterReader::GetEFuseLockParameter( Efuse_Lock_Arg** p_p_lock_arg)
{
	*p_p_lock_arg=&m_lock_arg;
	return MDT_OK;
}
#endif





