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
 *  mdt_efusewriter_cefusewriterfilereader.h
 *
 * Project:
 * --------
 *  MDT EFuseWriter
 *
 * Description:
 * ------------
 *  MDT EFuseWriter Config/Lock file base class
 *
 * Author:
 * -------
 *  Dongguo Jiang (mtk70823)
 *
 ****************************************************************************/
#ifndef MDT_EFUSEWRITER_CEFUSEWRITERCONFIGFILE_H_
#define MDT_EFUSEWRITER_CEFUSEWRITERCONFIGFILE_H_
#include "efusewriter/inc/mdt_efusewriter_cefusewriterfilereader.h"
#include "brom_dll/inc/brom.h"
class CEFuseWriterConfigFile:public CEFuseWriterFileReader {
public:
  CEFuseWriterConfigFile();
  virtual ~CEFuseWriterConfigFile();
  virtual MDT_ERROR_STATUS parsefile(); 
  virtual MDT_ERROR_STATUS reset();
 /*******************************************************************************
  *  get_write_parameter : Get EFuse write parameter from parser~
  *  --------------------
  *  Caution: Parameter must be valid and this function will allocate memory for key_buffer.  
  *              You must handle it carefully because of memory leaking.
  ******************************************************************************/
  virtual MDT_ERROR_STATUS get_write_parameter(Efuse_Common_Arg* p_common_art,
  	                                                Efuse_Secure_Arg* p_secure_arg)const; 
  
private:
  virtual MDT_ERROR_STATUS parse_common_arg();
  virtual MDT_ERROR_STATUS parse_secure_arg();
  virtual bool parse_usb_pid(uint16* p_PID)const;
  virtual bool parse_usb_vid(uint16* p_VID)const;


  Efuse_Common_Arg m_common_arg;
  Efuse_Secure_Arg m_secure_arg;

};




#endif
