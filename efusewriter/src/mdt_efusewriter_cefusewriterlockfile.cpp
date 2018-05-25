/*****************************************************************************
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of MediaTek Inc. (C) 2011
 *
 ****************************************************************************/

/*****************************************************************************
 * Filename:
 * ---------
 *  mdt_efusewriter_cefusewriterfilereader.cpp
 *
 * Project:
 * --------
 *  MDT EFuseWriter
 *
 * Description:
 * ------------
 *  MDT EFuseWriter Config/Lock file base class member function implementation
 *
 * Author:
 * -------
 *  Dongguo Jiang (mtk70823)
 *
 ****************************************************************************/
#include "efusewriter/inc/mdt_efusewriter_cefusewriterlockfile.h"
#include "mdt_component/error_handler/inc/gctrace.h"
CEFuseWriterLockFile::CEFuseWriterLockFile()
{
  memset(&m_lock_arg,0x00,sizeof(m_lock_arg));
  reset();
}
//-----------------------------------------------------------------------------
CEFuseWriterLockFile::~CEFuseWriterLockFile()
{
  
}
//-----------------------------------------------------------------------------
MDT_ERROR_STATUS CEFuseWriterLockFile::parse_lock_arg()
{
  try
  {
    //-----------------------
    m_lock_arg.common_ctrl_lock = read_attribute("Common Lock Setting", "com_ctrl_lock", EFUSE_WEIRD_CODE);
	//-----------------------
    m_lock_arg.usb_id_lock = read_attribute("Common Lock Setting", "usb_id_lock", EFUSE_WEIRD_CODE);
    //-----------------------
    m_lock_arg.spare_lock = read_attribute("Common Lock Setting", "spare_lock",EFUSE_WEIRD_CODE);
    //-----------------------
    m_lock_arg.sec_ctrl_lock = read_attribute("Secure Lock Setting", "sec_attr_lock", EFUSE_WEIRD_CODE);
    //-----------------------
    m_lock_arg.ackey_lock = read_attribute("Secure Lock Setting", "ackey_lock", EFUSE_WEIRD_CODE);
    //-----------------------
    m_lock_arg.sbc_pubk_hash_lock = read_attribute("Secure Lock Setting", "sbc_pubk_hash_lock", EFUSE_WEIRD_CODE);
  }
  catch(...)
  {
    return MDT_SV5_UNKNOWN_ERROR;
  }
  return MDT_OK;
}
//-----------------------------------------------------------------------------
MDT_ERROR_STATUS CEFuseWriterLockFile::parsefile()
{
  MDT_ERROR_STATUS mdt_status;
  if ( m_file_name == "" )
  {
    return MDT_SV5_EFUSE_WRITER_LOCK_FILE_IS_NULL;
  }
  m_is_parameter_ready = false;

  reset();
  if ( MDT_OK != ( mdt_status = parse_lock_arg() ) )
  {
    reset();
  	GC_TRACE_EX("Parse Lock Arg Error");
    return mdt_status;
  }
  m_is_parameter_ready = true;

  return MDT_OK;
}
//-----------------------------------------------------------------------------
MDT_ERROR_STATUS CEFuseWriterLockFile::get_lock_parameter(Efuse_Lock_Arg* p_lock_arg)const
{
  if( NULL == p_lock_arg )
  {
    return MDT_SV5_EFUSE_WRITER_INVALID_PARAMETER;
  }
  if( false == m_is_parameter_ready)
  {
    return MDT_SV5_EFUSE_WRITER_LOCK_SETTING_IS_NOT_READY;
  }
  memcpy(p_lock_arg,&m_lock_arg,sizeof(m_lock_arg)) ;

  return MDT_OK;
}


