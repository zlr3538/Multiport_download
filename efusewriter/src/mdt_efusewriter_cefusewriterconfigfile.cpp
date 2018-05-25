#include "efusewriter/inc/mdt_efusewriter_cefusewriterconfigfile.h"
#include "MDT_Component/error_handler/inc/Gctrace.h"
CEFuseWriterConfigFile::CEFuseWriterConfigFile()
{
  memset(&m_common_arg,0x00,sizeof(m_common_arg));
  memset(&m_secure_arg,0x00,sizeof(m_secure_arg));
  reset();
}
CEFuseWriterConfigFile::~CEFuseWriterConfigFile()
{
  reset();
}


//-----------------------------------------------------------------------------
MDT_ERROR_STATUS CEFuseWriterConfigFile::parse_common_arg()
{
  int attribute_value;
  
  bool l_usb_pid_read_status;
  bool l_usb_vid_read_status;
  
  try
  {
    m_common_arg.emmc_boot_dis = read_attribute("Common control", "Disable_EMMC_boot",EFUSE_WEIRD_CODE);		
	//=======================================
    m_common_arg.nand_boot_dis = read_attribute("Common control", "Disable_NAND_boot", EFUSE_WEIRD_CODE);
	//=======================================
    m_common_arg.nand_boot_speedup_dis = read_attribute("Common control", "Disable_NAND_boot_speedup", EFUSE_WEIRD_CODE);
	//=======================================
	m_common_arg.usbdl_type = read_integer("Common control", "Disable_USB_AutoDetect", 0);
    if ( 1 == m_common_arg.usbdl_type)
    {
      m_common_arg.usbdl_type_blow = EFUSE_ACTIVE;
    }
    else
    {
      m_common_arg.usbdl_type_blow = EFUSE_NONE;
    }
	//======  Read USB PID ====================	
    l_usb_pid_read_status = parse_usb_pid(&m_common_arg.usb_pid);
    //======  Read USB VID ====================	
    l_usb_vid_read_status = parse_usb_vid(&m_common_arg.usb_vid);
    if ( true == l_usb_pid_read_status
    	&& true == l_usb_vid_read_status)
    {
      m_common_arg.usb_id_blow = EFUSE_ACTIVE;
    }
    else if(true == l_usb_pid_read_status
    	|| true == l_usb_vid_read_status)
    {
      GC_TRACE_EX("USB Id Setting is Invalid in %s",m_file_name.c_str());
      return MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
    }
    else
    {
    	m_common_arg.usb_id_blow = EFUSE_NONE;
    }

    //======  Read Spare Data ====================
    m_common_arg.spare_num_of_byte = read_integer("Spare", "spare_byte", 0);
	m_common_arg.spare.buf = read_string("Spare","spare data","",&m_common_arg.spare.buf_len);
    if( m_common_arg.spare_num_of_byte > 0
		&& m_common_arg.spare.buf_len>0
		&& NULL != m_common_arg.spare.buf)
    {
      m_common_arg.spare_blow = EFUSE_ACTIVE;
    }
    else if (m_common_arg.spare_num_of_byte > 0
		|| m_common_arg.spare.buf_len>0
		|| NULL != m_common_arg.spare.buf)
    {
		if ( NULL != m_common_arg.spare.buf)
		{
		  delete m_common_arg.spare.buf;
		  m_common_arg.spare.buf=NULL;
		}	
      GC_TRACE_EX("Spare Data Setting is Invalid in %s",m_file_name.c_str());
      return MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;      
	}
	else
	{
      m_common_arg.spare_blow = EFUSE_NONE;
	  m_common_arg.spare_num_of_byte = 0;
	  if ( NULL != m_common_arg.spare.buf)
	  {
        delete m_common_arg.spare.buf;
        m_common_arg.spare.buf=NULL;
	  }	  
	}
  }
  catch(...)
  {
    return MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
  }
  return MDT_OK;

}
//-----------------------------------------------------------------------------
MDT_ERROR_STATUS CEFuseWriterConfigFile::parse_secure_arg()
{
  try
  {
    //=======================================
    m_secure_arg.acc_en = read_attribute("Security control", "Enable_ACC", EFUSE_WEIRD_CODE);
    //=======================================
    m_secure_arg.sbc_en = read_attribute("Security control", "Enable_SBC", EFUSE_WEIRD_CODE);
    //=======================================
    m_secure_arg.daa_en = read_attribute("Security control", "Enable_DAA", EFUSE_WEIRD_CODE);
    //=======================================
    m_secure_arg.sla_en = read_attribute("Security control", "Enable_SLA", EFUSE_WEIRD_CODE);
    //=======================================
    m_secure_arg.ack_en = read_attribute("Security control", "Enable_ACK", EFUSE_WEIRD_CODE);
    //=======================================
    m_secure_arg.jtag_dis = read_attribute("Security control", "Disable_JTAG", EFUSE_WEIRD_CODE);
    //=======================================
    m_secure_arg.root_cert_en = read_attribute("Security control", "Enable_Root_Cert", EFUSE_WEIRD_CODE);
    //=======================================
	m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf=read_string(
                                                   "SBC public key",
                                                   "public_key_e",
                                                   "",
                                                   &m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf_len
                                                   );
	m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf=read_string(
												"SBC public key",
												"public_key_n",
												"",
												&m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf_len
											);
    if( m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf_len > 0
       && NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf
       && m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf_len > 0
       && NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf
      )
    {
      m_secure_arg.sbc_pubk_blow=EFUSE_ACTIVE;
    }
	else if ( m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf_len > 0
       || NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf
       || m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf_len > 0
       || NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf
    )
	{
		m_secure_arg.sbc_pubk_blow=EFUSE_NONE;
		m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf_len=0;
		m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf_len=0;	
		if ( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf)
		{
		  delete m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf;
		  m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf=NULL;
		}
		if ( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf)
		{
		  delete m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf;
		  m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf=NULL;
		}
		GC_TRACE_EX("SBC Key Setting is Invalid in %s",m_file_name.c_str());
		return MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
	}
	else
	{
	  m_secure_arg.sbc_pubk_blow=EFUSE_NONE;
	  m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf_len=0;
      m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf_len=0;	  
	  if ( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf)
      {
        delete m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf;
		m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf=NULL;
	  }
	  if ( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf)
      {
        delete m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf;
        m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf=NULL;
	  }
	}
    //=======================================
	m_secure_arg.ac_key.buf=read_string(
                                       "AC key",
                                       "ac_key",
                                       "",
                                       &m_secure_arg.ac_key.buf_len
                                       );
    if ( m_secure_arg.ac_key.buf_len>0
    	&& NULL != m_secure_arg.ac_key.buf)
    {
      m_secure_arg.ac_key_blow=EFUSE_ACTIVE;
    }
	else if (m_secure_arg.ac_key.buf_len>0
    	|| NULL != m_secure_arg.ac_key.buf)
	{
      if ( NULL != m_secure_arg.ac_key.buf)
      {
        delete m_secure_arg.ac_key.buf;
        m_secure_arg.ac_key.buf=NULL;
      }
		GC_TRACE_EX("AC Key Setting is Invalid in %s",m_file_name.c_str());
		return MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;	  
	}
    else
    {
      m_secure_arg.ac_key_blow=EFUSE_NONE;
	  m_secure_arg.ac_key.buf_len=0;
      if ( NULL != m_secure_arg.ac_key.buf)
      {
        delete m_secure_arg.ac_key.buf;
        m_secure_arg.ac_key.buf=NULL;
      }
    }
  }
  catch(...)
  {
  	return MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
  }
  return MDT_OK;
  
}
//-----------------------------------------------------------------------------
MDT_ERROR_STATUS CEFuseWriterConfigFile::get_write_parameter(
                                     Efuse_Common_Arg* p_common_arg,
                                     Efuse_Secure_Arg* p_secure_arg)const
{
  if( NULL == p_common_arg || NULL == p_secure_arg )
  {
    return MDT_SV5_EFUSE_WRITER_INVALID_PARAMETER;
  }
  if( false == m_is_parameter_ready )
  {
    return MDT_SV5_EFUSE_WRITER_WRITE_SETTING_IS_NOT_READY;
  }
  memcpy(p_common_arg,&m_common_arg,sizeof(m_common_arg));
  //========= Copy spare data buffer =============
  if( EFUSE_ACTIVE == m_common_arg.spare_blow)
  {
    if( NULL != m_common_arg.spare.buf)
    {
      p_common_arg->spare.buf = new char[p_common_arg->spare.buf_len+1];
	  memset(p_common_arg->spare.buf,0x00,p_common_arg->spare.buf_len+1);
	  memcpy(p_common_arg->spare.buf,m_common_arg.spare.buf,m_common_arg.spare.buf_len);
	}
  }
  memcpy(p_secure_arg,&m_secure_arg,sizeof(m_secure_arg));
  //========= Copy key buffer =============
  if( EFUSE_ACTIVE == m_secure_arg.ac_key_blow)
  {
    if( NULL != m_secure_arg.ac_key.buf)
    {
      p_secure_arg->ac_key.buf = new char[p_secure_arg->ac_key.buf_len+1];
	  memset(p_secure_arg->ac_key.buf,
	  	     0x00,
	  	     p_secure_arg->ac_key.buf_len+1);
	  memcpy(p_secure_arg->ac_key.buf,
	  	     m_secure_arg.ac_key.buf,
	  	     m_secure_arg.ac_key.buf_len);
    }
  }
  //========= Copy public key E buffer =============
  if( EFUSE_ACTIVE == m_secure_arg.sbc_pubk_blow)
  {
	  if( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf)
	  {
		p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_e.buf = new char[p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_e.buf_len+1];
		memset(p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_e.buf, 0x00, p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_e.buf_len+1);
		memcpy(p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_e.buf,
			   m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf,
			   m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf_len
			  );
	  }    
  }
  //========= Copy public key N buffer =============
  if( EFUSE_ACTIVE == m_secure_arg.sbc_pubk_blow)
  {
	  if( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf)
	  {
		p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_n.buf = new char[p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_n.buf_len+1];
		memset(p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_n.buf, 0x00, p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_n.buf_len+1);
		memcpy(p_secure_arg->sbc_pub_key_u.w_sbc_pub_key.key_n.buf,
			   m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf,
			   m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf_len
			  );
	  }    
  }  
  return MDT_OK;
}
//-----------------------------------------------------------------------------
MDT_ERROR_STATUS CEFuseWriterConfigFile::reset()
{
  //Release buffer avoid memory leaking~
  //Caution: this function will release key buffer.~
  if ( NULL != m_common_arg.spare.buf )
  {
    delete m_common_arg.spare.buf;
	m_common_arg.spare.buf = NULL;
  }
  if ( NULL != m_secure_arg.ac_key.buf)
  {
    delete m_secure_arg.ac_key.buf;
	m_secure_arg.ac_key.buf = NULL ;
  }
  if( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf )
  {
    delete m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf;
    m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf = NULL;
  }
  if( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf)
  {
    delete m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf;
    m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf = NULL;
  }
  memset(&m_common_arg,0x00,sizeof(m_common_arg));
  memset(&m_secure_arg,0x00,sizeof(m_secure_arg));

  m_common_arg.emmc_boot_dis = EFUSE_NONE;
  m_common_arg.nand_boot_dis = EFUSE_NONE;
  m_common_arg.nand_boot_speedup_dis = EFUSE_NONE;
  m_common_arg.usbdl_type_blow = EFUSE_NONE;
  m_common_arg.usbdl_type = 0x00;
  m_common_arg.usb_id_blow = EFUSE_NONE;
  m_common_arg.spare_blow = EFUSE_NONE;
  
  m_secure_arg.acc_en = EFUSE_NONE;
  m_secure_arg.ack_en = EFUSE_NONE;
  m_secure_arg.sbc_en = EFUSE_NONE;
  m_secure_arg.daa_en = EFUSE_NONE;
  m_secure_arg.sla_en = EFUSE_NONE;
  m_secure_arg.root_cert_en = EFUSE_NONE;
  m_secure_arg.jtag_dis = EFUSE_NONE;
  m_secure_arg.ac_key_blow = EFUSE_NONE;
  m_secure_arg.sbc_pubk_blow = EFUSE_NONE;

  return MDT_OK;
}
//-----------------------------------------------------------------------------
MDT_ERROR_STATUS CEFuseWriterConfigFile::parsefile()
{
  MDT_ERROR_STATUS mdt_status;
  
  m_is_parameter_ready = false;
  reset();

  if( m_file_name == "" )
  {
    return MDT_SV5_EFUSE_WRITER_INVALID_SETTING_FILE;
  }
  if ( MDT_OK != (mdt_status = parse_common_arg()) )
  {
    GC_TRACE_EX("Parse Common Parameter Error");
    reset();
    return mdt_status;
  }
  if ( MDT_OK != (mdt_status = parse_secure_arg()) )
  {
    GC_TRACE_EX("Parse Secure Parameter Error");
    reset();
    return mdt_status;
  }
  m_is_parameter_ready=true;
 
  return MDT_OK;
}
//-----------------------------------------------------------------------------
bool CEFuseWriterConfigFile::parse_usb_pid(uint16* p_PID)const
{
  AnsiString USBPID_String = "";;
  uint16 USB_PID = 0x00;
  int USBPIDStringLength;
  
  memset(m_p_read_string_buffer,0x00,EFUSE_READ_BUFFERSIZE);
  
  USBPIDStringLength = GetPrivateProfileString("USB ID", "USB_PID",NULL,m_p_read_string_buffer,EFUSE_READ_BUFFERSIZE,m_file_name.c_str());
  if(0 >= USBPIDStringLength)
  {
  	GC_TRACE_EX("USB ID==>USB_PID is Invalid.");
  	*p_PID=0x0000;
  	return false;
  }
  
  USBPID_String = (char*)m_p_read_string_buffer;
  
  if(USBPID_String == "USB_PID_String")
  {
  	GC_TRACE_EX("USB ID==>USB_PID is Invalid.");
  	*p_PID=0x0000;
  	return false;
  }
  
  USBPID_String = USBPID_String.Trim();
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
  
  USB_PID = 0xFFFF&StrToInt(USBPID_String);
  *p_PID = USB_PID;
  GC_TRACE_EX("USB ID==>USB_PID is 0x%04X From File: %s ",USB_PID,m_file_name.c_str());
  
  return true;
}
//-----------------------------------------------------------------------------
bool CEFuseWriterConfigFile::parse_usb_vid(uint16* p_VID)const
{
	AnsiString USBVID_String;
	uint16 USB_VID=0x00;
	int USBVID_Length=0;
	memset(m_p_read_string_buffer,0x00,EFUSE_READ_BUFFERSIZE);	

	USBVID_Length=GetPrivateProfileString("USB ID", "USB_VID",NULL,m_p_read_string_buffer,EFUSE_READ_BUFFERSIZE,m_file_name.c_str());
	if( 0 >= USBVID_Length )
	{
		GC_TRACE_EX("USB ID==>USB_VID is Invalid.");	
		*p_VID=0x0000;
		return false;
	}

	USBVID_String = (char*)m_p_read_string_buffer;
	if( USBVID_String == "USB_VID_String")
	{
		GC_TRACE_EX("USB ID==>USB_VID is Invalid.");	
		*p_VID=0x0000;
		return false;
	}
	USBVID_String = USBVID_String.Trim();
	//USB VID is Hex format
	if(USBVID_String.SubString(0,2).UpperCase() == "0X" )
	{
		USBVID_String = USBVID_String.SubString(0,6);
	}
	else
	{
		USBVID_String = USBVID_String.SubString(0,5); 	
	}
	USBVID_String=USBVID_String.Trim();
	USB_VID=0xFFFF&StrToInt(USBVID_String);
	GC_TRACE_EX("USB ID==>USB_VID is 0x%04X",USB_VID);
	*p_VID=USB_VID;	
	return true;
}

