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
 *  EFuseReader.h.h
 *
 * Project:
 * --------
 *  MDT EFuseWriter Thread
 *
 * Description:
 * ------------
 *
 * Author:
 * -------
 *  Dongguo Jiang (mtk70823)
 *
 ****************************************************************************/
#ifndef MDT_EFUSEWRITER_EFUSE_READER_H_
#define MDT_EFUSEWRITER_EFUSE_READER_H_

#include "MDT_Component/thread/inc/FlashDownLoad.h"
#include "MDT_Component/error_handler/inc/GCTrace.h"
#include "MDT_Component/error_handler/inc/MDT_ErrorTypes.h"
#include "Form/MainForm/MultiPortFlashDownloadTool.h"
#include "brom_dll/inc/brom.h"
#include "efusewriter/inc/cmdtefusereaderhandle.h"

class TEFuseReader:public TBOOT1
{
protected:
  virtual void __fastcall Execute();
  virtual void __fastcall printProcessInfo();
public:  
  __fastcall TEFuseReader(
  		bool CreateSuspended, 
  		HANDLE hMsgHandle, 
  		COM_PORT_SETTING com_port_setting, 
  		S_DN_PARAM_T dn_param
  );
  virtual MDT_ERROR_STATUS __fastcall setefusereadhandle(CMDT_Efuse_Reader_Handle_List* p_handle);
  virtual MDT_ERROR_STATUS __fastcall checkparameter();
  
 protected:
   CMDT_Efuse_Reader_Handle_List* m_p_handle_list;

   CMDT_Efuse_Reader_Handle m_EFuseReaderItem;
   
};


#endif
