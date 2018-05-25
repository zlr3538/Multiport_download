#include "efusewriter/inc/cmdtefuseparameterhandle.h"
#include "efusewriter/inc/mdt_efusewriter_cefusewriterfilereader.h"

CMDT_Efuse_Parameter_Handle::CMDT_Efuse_Parameter_Handle()
{
  memset(&m_common_arg,0x00,sizeof(m_common_arg));
  memset(&m_secure_arg,0x00,sizeof(m_common_arg));
  memset(&m_lock_arg,0x00,sizeof(m_lock_arg));
  
  reset_setting();
}
CMDT_Efuse_Parameter_Handle::~CMDT_Efuse_Parameter_Handle()
{

}
void CMDT_Efuse_Parameter_Handle::reset_write_setting()
{
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

}
void CMDT_Efuse_Parameter_Handle::reset_lock_setting()
{
	m_lock_arg.common_ctrl_lock = EFUSE_NONE;
	m_lock_arg.usb_id_lock = EFUSE_NONE;
	m_lock_arg.spare_lock = EFUSE_NONE;
	m_lock_arg.sec_ctrl_lock = EFUSE_NONE;
	m_lock_arg.ackey_lock = EFUSE_NONE;
	m_lock_arg.sbc_pubk_hash_lock = EFUSE_NONE;
}

void CMDT_Efuse_Parameter_Handle::reset_setting()
{
  reset_write_setting();
  reset_lock_setting();
}
void CMDT_Efuse_Parameter_Handle::PrintWriteParameterLog()const
{
  GC_TRACE_EX("m_common_arg: Address: 0x%08X",&m_common_arg);
  GC_TRACE_EX("m_common_arg.emmc_boot_dis: 0x%08X",m_common_arg.emmc_boot_dis);
  GC_TRACE_EX("m_common_arg.nand_boot_dis: 0x%08X",m_common_arg.nand_boot_dis);
  GC_TRACE_EX("m_common_arg.nand_boot_speedup_dis: 0x%08X",m_common_arg.nand_boot_speedup_dis);
  GC_TRACE_EX("m_common_arg.usbdl_type: 0x%08X",m_common_arg.usbdl_type);
  GC_TRACE_EX("m_common_arg.usb_id_blow: 0x%08X",m_common_arg.usb_id_blow);
  GC_TRACE_EX("m_common_arg.spare_blow: 0x%08X",m_common_arg.spare_blow);
  GC_TRACE_EX("m_common_arg.spare.buf_len: 0x%08X",m_common_arg.spare.buf_len);
  if( NULL != m_common_arg.spare.buf 
  	&& m_common_arg.spare.buf_len>0)
  {
    PrintSpareDataLog();
  }
  GC_TRACE_EX("m_secure_arg: Address: 0x%08X",&m_secure_arg);
  GC_TRACE_EX("m_secure_arg.acc_en: 0x%08X",m_secure_arg.acc_en);
  GC_TRACE_EX("m_secure_arg.ack_en: 0x%08X",m_secure_arg.ack_en);
  GC_TRACE_EX("m_secure_arg.sbc_en: 0x%08X",m_secure_arg.sbc_en);
  GC_TRACE_EX("m_secure_arg.daa_en: 0x%08X",m_secure_arg.daa_en);
  GC_TRACE_EX("m_secure_arg.sla_en: 0x%08X",m_secure_arg.sla_en);
  GC_TRACE_EX("m_secure_arg.root_cert_en: 0x%08X",m_secure_arg.root_cert_en);
  GC_TRACE_EX("m_secure_arg.jtag_dis: 0x%08X",m_secure_arg.jtag_dis);
  GC_TRACE_EX("m_secure_arg.ac_key_blow: 0x%08X",m_secure_arg.ac_key_blow);
  GC_TRACE_EX("m_secure_arg.ac_key.buf_len: 0x%08X",m_secure_arg.ac_key.buf_len);
  if( NULL != m_secure_arg.ac_key.buf
  	&& m_secure_arg.ac_key.buf_len>0)
  {
    PrintAcKeyLog();
  }
  GC_TRACE_EX("m_secure_arg.sbc_pubk_blow: 0x%08X",m_secure_arg.sbc_pubk_blow);
  if( EFUSE_ACTIVE == m_secure_arg.sbc_pubk_blow)
  {
    PrintPublicKeyDataLog();
  }
}
void CMDT_Efuse_Parameter_Handle::PrintLockParameterLog()const
{
  GC_TRACE_EX("m_lock_arg: Address: 0x%08X",&m_lock_arg);
  GC_TRACE_EX("m_lock_arg.common_ctrl_lock: 0x%08X",m_lock_arg.common_ctrl_lock);
  GC_TRACE_EX("m_lock_arg.usb_id_lock: 0x%08X",m_lock_arg.usb_id_lock);
  GC_TRACE_EX("m_lock_arg.spare_lock: 0x%08X",m_lock_arg.spare_lock);
  GC_TRACE_EX("m_lock_arg.sec_ctrl_lock: 0x%08X",m_lock_arg.sec_ctrl_lock);
  GC_TRACE_EX("m_lock_arg.ackey_lock: 0x%08X",m_lock_arg.ackey_lock);
  GC_TRACE_EX("m_lock_arg.sbc_pubk_hash_lock: 0x%08X",m_lock_arg.sbc_pubk_hash_lock);
}
void CMDT_Efuse_Parameter_Handle::PrintSpareDataLog()const
{
	GC_TRACE_EX("Do nothing...");
}
void CMDT_Efuse_Parameter_Handle::PrintAcKeyLog()const
{
	GC_TRACE_EX("Do nothing...");
}
void CMDT_Efuse_Parameter_Handle::PrintPublicKeyDataLog()const
{
	GC_TRACE_EX("Do nothing...");
}


bool CMDT_Efuse_Parameter_Handle::is_non_secure_user_setting()const
{
  //m_common_arg
  if(EFUSE_ACTIVE == m_common_arg.emmc_boot_dis)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_common_arg.nand_boot_dis)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_common_arg.nand_boot_speedup_dis)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_common_arg.spare_blow)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_common_arg.usbdl_type_blow)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_common_arg.usb_id_blow)
  {
    return false;
  }
  //m_secure_arg
  if(EFUSE_ACTIVE == m_secure_arg.ack_en)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_secure_arg.daa_en)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_secure_arg.jtag_dis)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_secure_arg.root_cert_en)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_secure_arg.sbc_en)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_secure_arg.sbc_pubk_blow)
  {
    return false;
  }
  //secure lock
  if(EFUSE_ACTIVE == m_lock_arg.common_ctrl_lock)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_lock_arg.sbc_pubk_hash_lock)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_lock_arg.sec_ctrl_lock)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_lock_arg.spare_lock)
  {
    return false;
  }
  if(EFUSE_ACTIVE == m_lock_arg.usb_id_lock)
  {
    return false;
  }
  return true;
}


