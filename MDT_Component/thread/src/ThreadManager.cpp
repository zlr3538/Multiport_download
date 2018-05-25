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
*   ThreadManager.cpp
*
* Project:
* --------
*   Multiport download
*
* Description:
* ------------
*  ThreadManager  source
*
* Author:
* -------
*  Maobin Guo (mtk80061)
*
* 
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*============================================================================
****************************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <inifiles.hpp>
#include <fcntl.h>
#include <io.h>


#include "com_enum.h"
#include "meta.h"
#include "ThreadManager.h"


// form
#ifndef form_AboutH
#include "form_About.h"
#endif

//#ifndef _FORM_MULTILOAD_H_
//#include "form_MultiLoad.h"
//#endif

#include "Multiport_Common.h"

#ifndef _MD_MSG_
#include "MD_msg.h"
#endif


#ifndef _FLASHDOWNLOAD_H_
#include "FlashDownLoad.h"
#endif

// database
#ifndef _FACTORY_COMMON_H_
#include "factory_common.h"
#endif

#include "INIFileHandle\INIFileHandle.h"

// misc
#ifndef  _FILE_UTILS_H_
#include "file_utils.h"
#endif

#include "Eboot\interface.h"

//---------------------------------------------------------------------------
ThreadManager::ThreadManager()
{
    _p_enter_mpdl_queue = new Enter_mpdl_queue(FALSE);
    if(NULL != _p_enter_mpdl_queue)
    {
        _p_enter_mpdl_queue->FreeOnTerminate = true;
    }
    
    
    
    for( int i=0; i<MAX_SUPPORT_PORT_NUM; i++ )
    {
        _threads[i] = NULL;
        _stop_flag[i] = 0;
        _usb_protected_flag[i] = false;
    }
    
    InitializeCriticalSection(&_threads_cs);
}

ThreadManager::~ThreadManager()
{
    _p_enter_mpdl_queue->Terminate();
    DeleteCriticalSection(&_threads_cs);
}


//---------------------------------------------------------------------------
bool ThreadManager::Start(unsigned long index, HANDLE hMsgHandle,
                          COM_PORT_SETTING com_setting, S_DN_PARAM_T dn_param)
{
    bool ret;
    
    try
    {
        EnterCriticalSection(&_threads_cs);
        
        if(NULL != _threads[index])
        {
            ret = false;
            goto leave;
        }
        
        //Reset some flag
        _stop_flag[index] = 0;
        Release_usb_protected_flag(index);
        
        _threads[index] = new TBOOT1(FALSE, hMsgHandle, com_setting, dn_param);
        
        if(NULL != _threads[index])
        {
            _threads[index]->FreeOnTerminate = true;
            ret = true;
            goto leave;
        }
        else
        {
            ret = false;
            goto leave;
        }
    }
    catch(...)
    {
        ret = false;
        goto leave;
    }
    
    
leave:
    LeaveCriticalSection(&_threads_cs);
    return ret;
}

//---------------------------------------------------------------------------
void ThreadManager::Terminate(index)
{
    EnterCriticalSection(&_threads_cs);
    
    if(NULL == _threads[index])
        goto leave;
    
    _threads[index]->Terminate();
    
leave:
    LeaveCriticalSection(&_threads_cs);
}

//---------------------------------------------------------------------------
void ThreadManager::Mark_finish(index)
{
    EnterCriticalSection(&_threads_cs);
    
    Release_usb_protected_flag(index);
    _threads[index] = NULL;
    
    LeaveCriticalSection(&_threads_cs);
}

//---------------------------------------------------------------------------
bool ThreadManager::Is_running(index)
{
    return  (NULL != _threads[index]);
}

AnsiString ThreadManager::Print_usb_protected_flag( void )
{
    AnsiString   log;
    
    for( int i=0; i<MAX_SUPPORT_PORT_NUM; i++ )
    {
        if(_usb_protected_flag[i])
        {
            log += "[True] ";
        }
        else
        {
            log += "[False] ";
        }
    }
    
    return   log;
}


//---------------------------------------------------------------------------
bool ThreadManager::Is_any_other_in_usb_protected_mode(int index)
{
    for( int i=0; i<MAX_SUPPORT_PORT_NUM; i++ )
    {
        if((index != i) && (true == _usb_protected_flag[i]))
        {
            return true;
        }
    }
    
    return false;
}

//---------------------------------------------------------------------------
bool ThreadManager::Is_usb_protected_flag_setted(int index)
{
    return _usb_protected_flag[index];
}

//---------------------------------------------------------------------------
void ThreadManager::Set_usb_protected_flag(int index)
{
    _usb_protected_flag[index] = true;
}

//---------------------------------------------------------------------------
void ThreadManager::Release_usb_protected_flag(int index)
{
    _usb_protected_flag[index] = false;
}

//---------------------------------------------------------------------------
void ThreadManager::Stop(index)
{
    EnterCriticalSection(&_threads_cs);
    
    _stop_flag[index] = BOOT_STOP;
    
    LeaveCriticalSection(&_threads_cs);
}

//---------------------------------------------------------------------------
int * ThreadManager::Get_stop_flag_addr(index)
{
    return &(_stop_flag[index]);
}

//---------------------------------------------------------------------------
bool ThreadManager::Is_stopped(index)
{
    return (BOOT_STOP == _stop_flag[index]);
}

//---------------------------------------------------------------------------
bool ThreadManager::Is_all_finish()
{
    int count = 0;
    
    for( int i=0; i<MAX_SUPPORT_PORT_NUM; i++ )
    {
        if(!Is_running(i))
        {
            count++;
        }
    }
    
    return (MAX_SUPPORT_PORT_NUM == count);
}

//---------------------------------------------------------------------------
bool ThreadManager::Is_all_running()
{
    int count = 0;
    
    for( int i=0; i<MAX_SUPPORT_PORT_NUM; i++ )
    {
        if(Is_running(i))
        {
            count++;
        }
    }
    
    return (MAX_SUPPORT_PORT_NUM == count);
}

//---------------------------------------------------------------------------
bool * ThreadManager::Get_enter_mpdl_flag_addr(index)
{
    return &(_p_enter_mpdl_queue->_enter_mpdl_flag[index]);
}

//---------------------------------------------------------------------------
void ThreadManager::Apply_enter_mpdl_queue(index)
{
    _p_enter_mpdl_queue->Apply(index);
}

//---------------------------------------------------------------------------
void ThreadManager::Enter_mpdl_finish(index)
{
    _p_enter_mpdl_queue->Finish(index);
}


//---------------------------------------------------------------------------
//   Enter_mpdl_queue  
//---------------------------------------------------------------------------
Enter_mpdl_queue::Enter_mpdl_queue(bool CreateSuspended): TThread(CreateSuspended)
{
    InitializeCriticalSection(&g_cs);
    
    for( int i=0; i<MAX_SUPPORT_PORT_NUM; i++ )
    {
        _enter_mpdl_flag[i] = false;
    }
}


//---------------------------------------------------------------------------
void Enter_mpdl_queue::Apply(int index)
{
    EnterCriticalSection(&g_cs);
    
    try
    {
        if(!_enter_mpdl_queue.empty())
        {
            if(index == _enter_mpdl_queue.front())
            {
                LeaveCriticalSection(&g_cs);
                Finish(index);
                return;
            }
        }
        
        
        _enter_mpdl_queue.push(index);
    }
    catch(...)
    {
        goto leave;
    }
    
leave:
    LeaveCriticalSection(&g_cs);
}

//---------------------------------------------------------------------------
void Enter_mpdl_queue::Finish(int index)
{
    EnterCriticalSection(&g_cs);
    
    try
    {
        if(!_enter_mpdl_queue.empty())
        {
            if(index == _enter_mpdl_queue.front())
            {
                _enter_mpdl_flag[_enter_mpdl_queue.front()] = false;
                _enter_mpdl_queue.pop();
            }
        }
    }
    catch(...)
    {
        goto leave;
    }
    
leave:
    LeaveCriticalSection(&g_cs);
}


//---------------------------------------------------------------------------
void __fastcall Enter_mpdl_queue::Execute()
{
    try
    {
        do
        {
            Sleep(100);
            
            if( this->Terminated )
            {
                goto finish;
            }
            
            Updata_queue();
        }
        while(1);
    }
    catch(...)
    {
        goto finish;
    }
    
finish:
    DeleteCriticalSection(&g_cs);
    return;
}

void _fastcall Enter_mpdl_queue::Updata_queue()
{
    EnterCriticalSection(&g_cs);
    
    try
    {
        if(!_enter_mpdl_queue.empty())
        {
            if(false == _enter_mpdl_flag[_enter_mpdl_queue.front()])
            {
                _enter_mpdl_flag[_enter_mpdl_queue.front()] = true;
            }
        }
    }
    catch(...)
    {
        goto leave;
    }
    
leave:
    LeaveCriticalSection(&g_cs);
}



