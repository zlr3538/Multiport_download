/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   ThreadManager.h
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *
 *
 * Author:
 * -------
 *  Maobin Guo (mtk80061)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 *

 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

//---------------------------------------------------------------------------
#ifndef _THREAD_MANAGER_H_
#define _THREAD_MANAGER_H_
//---------------------------------------------------------------------------
#include <Classes.hpp>

#ifndef _FLASHTOOL_H_
#include "flashtool.h"
#endif

#ifndef _BROM_H_
#include "brom.h"
#endif

#ifndef _EBOOT_INTERFACE_H_
#include "Eboot\interface.h"
#endif

#ifndef	_FLASHTOOL_HANDLE_H_
#include "flashtool_handle.h"
#endif

#ifndef	_MTK_MCU_H_
#include "mtk_mcu.h"
#endif

#ifndef _DOWNLOAD_H_
#include "DOWNLOAD.h"
#endif

#ifndef _MULTIPORT_COMMON_H_
#include "multiport_common.h"
#endif

// GPS
#ifndef	_BROM_DLL_WRAPPER_H_
#include "BromDllWrapper.h"
#endif

// META
#ifndef  _METAAPP_COMMON_H_
#include "metaapp_common.h"
#endif

//STL
#include <vector>
#include <queue>

using namespace std;
//---------------------------------------------------------------------------

class Enter_mpdl_queue;

class  ThreadManager
{
public:

     friend class TBOOT1;

     ThreadManager();
     ~ThreadManager();

     bool Start(unsigned long index, HANDLE hMsgHandle,
                COM_PORT_SETTING com_setting, S_DN_PARAM_T dn_param);

     void Terminate(int index);

     bool Is_running(int index);

     void Stop(int index);

     bool Is_stopped(int index);

     bool Is_all_finish();

     bool Is_all_running();

     int * Get_stop_flag_addr(int index);

     bool * Get_enter_mpdl_flag_addr(int index);

     void Apply_enter_mpdl_queue(int index);

     void Enter_mpdl_finish(int index);

     bool Is_usb_protected_flag_setted(int index);

     bool Is_any_other_in_usb_protected_mode(int index);

     void Set_usb_protected_flag(int index);

     void Release_usb_protected_flag(int index);

     AnsiString Print_usb_protected_flag( void );

private:

     void Mark_finish(int index);

private:

     TThread * _threads[MAX_SUPPORT_PORT_NUM];
     int       _stop_flag[MAX_SUPPORT_PORT_NUM];
     bool      _usb_protected_flag[MAX_SUPPORT_PORT_NUM];


     Enter_mpdl_queue  *_p_enter_mpdl_queue;


     CRITICAL_SECTION _threads_cs;

};


class Enter_mpdl_queue : public TThread
{
  friend class ThreadManager;

  Enter_mpdl_queue(bool CreateSuspended);

  void __fastcall Execute();

  void Apply(int index);
  void Finish(int index);

private:

  CRITICAL_SECTION g_cs;

  void _fastcall Updata_queue();

  bool _enter_mpdl_flag[MAX_SUPPORT_PORT_NUM];
  queue<int>        _enter_mpdl_queue;
};









//---------------------------------------------------------------------------
#endif    //_THREAD_MANAGER_H_
