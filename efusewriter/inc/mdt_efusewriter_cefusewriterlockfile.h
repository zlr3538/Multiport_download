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
#ifndef MDT_EFUSEWRITER_CEFUSEWRITERLOCKFILE_H_
#define MDT_EFUSEWRITER_CEFUSEWRITERLOCKFILE_H_

#include "brom_dll/inc/brom.h"
#include "efusewriter/inc/mdt_efusewriter_cefusewriterfilereader.h"

class CEFuseWriterLockFile:public CEFuseWriterFileReader
{
public:
  CEFuseWriterLockFile();
  virtual ~CEFuseWriterLockFile();
  virtual MDT_ERROR_STATUS parsefile();
  virtual MDT_ERROR_STATUS get_lock_parameter(Efuse_Lock_Arg* p_lock_arg)const;
  virtual MDT_ERROR_STATUS reset()
  {
    m_lock_arg.ackey_lock = EFUSE_NONE;
    m_lock_arg.common_ctrl_lock = EFUSE_NONE;
    m_lock_arg.sbc_pubk_hash_lock = EFUSE_NONE;
    m_lock_arg.sec_ctrl_lock = EFUSE_NONE;
    m_lock_arg.spare_lock = EFUSE_NONE;
    m_lock_arg.usb_id_lock = EFUSE_NONE;
    return MDT_OK;
  }
  
private:
  Efuse_Lock_Arg m_lock_arg;
  virtual MDT_ERROR_STATUS parse_lock_arg();
};



#endif
