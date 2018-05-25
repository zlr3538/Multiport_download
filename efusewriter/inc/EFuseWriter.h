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
#ifndef EFUSE_WRITER_H__
#define EFUSE_WRITER_H__

#include "MDT_Component/thread/inc/FlashDownLoad.h"
#include "MDT_Component/error_handler/inc/GCTrace.h"
#include "MDT_Component/error_handler/inc/MDT_ErrorTypes.h"
#include "Form/MainForm/MultiPortFlashDownloadTool.h"
#include "brom_dll/inc/brom.h"
#include "efusewriter/inc/cmdtefusewriterhandle.h"

//========================================================
class TEFuseWriter:public TBOOT1
{
protected:
  virtual void __fastcall Execute();
  virtual void __fastcall printProcessInfo();  

public:  
  __fastcall TEFuseWriter(
  		bool CreateSuspended, 
  		HANDLE hMsgHandle, 
  		COM_PORT_SETTING com_port_setting, 
  		S_DN_PARAM_T dn_param
  );
public:
  virtual MDT_ERROR_STATUS __fastcall SetEFuseWriteHandle(const CMDT_Efuse_Writer_Handle* p_handle);
  virtual MDT_ERROR_STATUS __fastcall checkparameter();
  
  virtual void __fastcall SetEFuseWriteAction(bool EFuseWriteAction);
  virtual void __fastcall SetEFuseLockAction(bool EFuseLockAction);
private:
  bool m_EFuseWriteAction;
  bool m_EFuseLockAction;

  const CMDT_Efuse_Writer_Handle* p_writer_handle;
};


#endif

