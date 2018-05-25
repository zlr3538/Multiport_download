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
 *   T_GPS.cpp
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  Backup and restore calibration data thread source file
 *
 * Author:
 * -------
 *  Andy Ueng (mtk00490)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 *
 * Sep 8 2008 MTK02172
 * [STP100001803] [Multiport download tool] Multiport download tool ver 3.0836.0
 *
 *
 * Aug 13 2008 mtk00490
 * [STP100001788] [Multiport download tool] Multiport download tool ver 3.0832.0
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
// form

#pragma hdrstop

#ifndef _MUTLIPORTFLASHDOWNLOADTOOL_H_
#include "MultiPortFlashDownloadTool.h"
#endif

#ifndef META_DLL_H
#include "meta.h"
#endif

#ifndef _SLA_CHALLENGE_H_
#include "sla_challenge/inc/sla_challenge.h"
#endif

#ifndef _FLASHDOWNLOAD_H_
#include "mdt_component/thread/inc/FlashDownload.h"
#endif

#ifndef _MD_MSG_
#include "md_msg.h"
#endif

#ifndef _FACTORY_COMMON_H_
#include "common/factory_common.h"
#endif

#include "mdt_component/error_handler/inc/GCTrace.h"

//==============================================================================
extern AUTH_HANDLE_T g_AUTH_HANDLE;
extern int __stdcall cb_PowerOnOxford(HANDLE hCOM, void *usr_arg);
extern int g_iStopFlag[MAX_SUPPORT_PORT_NUM];
extern bool isStopTrigger[MAX_SUPPORT_PORT_NUM];
// access
extern HANDLE hSemaphore;
//==============================================================================
static int __stdcall cb_boot_meta_in_brom_stage(unsigned int brom_handle, HANDLE hCOM, void *usr_arg)
{
  /*  TBOOT1 *t=(TBOOT1 *)usr_arg;

    t->m_ucProgressPercentage = 0;
    METAAPP_OP_T op = t->Get_MetaAppOp();
    switch (op)
    {
        case METAAPP_OP_BACKUP_CAL_DATA:
        {
            t->SyncStartBackupCalDataProgress();
        }
        break;

        case METAAPP_OP_RESTORE_CAL_DATA:
        {
            t->SyncStartRestoreCalDataProgress();
        }
        break;

        case METAAPP_OP_UPLOAD_USER_DATA:
        {
            t->SyncStartUploadUserDataProgress();
        }
        break;

        case METAAPP_OP_RESET_TO_FACTORY_DEFAULT:
        {
            t->SyncStartFactoryDefaultProgress();
        }
        break;
    }    */

	Sleep(1000);
    return 0;
}


int _fastcall TBOOT1::boot_meta_in_brom_stage()
{

    m_ucProgressPercentage = 0;
    METAAPP_OP_T op = Get_MetaAppOp();

    switch (op)
    {
        case METAAPP_OP_BACKUP_CAL_DATA:
        {
            SyncStartBackupCalDataProgress();
        }
        break;

        case METAAPP_OP_RESTORE_CAL_DATA:
        {
            SyncStartRestoreCalDataProgress();
        }
        break;

        case METAAPP_OP_UPLOAD_USER_DATA:
        {
            SyncStartUploadUserDataProgress();
        }
        break;

        case METAAPP_OP_RESET_TO_FACTORY_DEFAULT:
        {
            SyncStartFactoryDefaultProgress();
        }
        break;

        case METAAPP_OP_RESTORE_CHECK_DATA:
        {
            SyncStartCheckDataProgress();
        }
        break;

    }

    return 0;
}

//==============================================================================
////////////////////////////// META mode error handling ////////////////////////
//==============================================================================
void _fastcall TBOOT1::UpdateMetaResultOk()
{
    if (m_bInMetaMode)
    {
        Exit_META_Mode();
        m_bInMetaMode = false;
    }

    AnsiString s_ok = prefix + "OK";

    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

    // access
    if (MainForm->Get_EnableFactoryDatabaseLog())
    {
        TDateTime datetime;
        TDateTime time = datetime.CurrentTime();
        sTime     stime;
        time.DecodeTime( &stime.hour, &stime.min, &stime.sec, &stime.msec);
        MainForm->SetPassFail( i, TEST_RESULT_PASS);
        MainForm->SetFailReason( i, 0 );
        MainForm->SetDnEndsTime( i, stime );
        MainForm->SetDnTime( i );
        MainForm->SetThroughput( i );
        WaitForSingleObject( hSemaphore, 5000 );
        MainForm->AddDnResultToAccess( i );
    }

    MainForm->COMPercentageArray[i]->Caption = s_ok;
    MainForm->Set_COMPercentageCaption(i, s_ok);
    SyncStopTimer();
    MainForm->btnCOMStartArray[i]->Enabled = true;
    MainForm->cbCOMArray[i]->Enabled = true;
    MainForm->cbAutoPollingArray[i]->Enabled = true;
    MainForm->Set_shpCOMColor( i, clGreen );
    MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;

    //comment this
    //PostMessage( hPostMsgDestHandle, WM_MD_DOWNLOAD_SUCCESSFUL,  i, 0);

}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::SyncUpdateMetaResultOk()
{
    Synchronize(UpdateMetaResultOk);
}
//---------------------------------------------------------------------------

void _fastcall TBOOT1::UpdateCheckSDSResultOk()
{
	if (m_bInMetaMode)
		{
			Exit_META_Mode();
			m_bInMetaMode = false;
		}
	
		AnsiString s_ok = "SDS OK";
	
		int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
	MainForm->COMPercentageArray[i]->Caption = s_ok;
    MainForm->Set_COMPercentageCaption(i, s_ok);
    SyncStopTimer();
    MainForm->btnCOMStartArray[i]->Enabled = true;
    MainForm->cbCOMArray[i]->Enabled = true;
    MainForm->cbAutoPollingArray[i]->Enabled = true;
    MainForm->Set_shpCOMColor( i, clGreen );
	MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComProgress(i, 100);
    MainForm->SetPbComForeColor(i, clGreen);
	m_asMsg = "Success: CheckSDS OK";//check sds result
	Synchronize(ShowMsg);

}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::SyncCheckSDSResultOk()
{
    Synchronize(UpdateCheckSDSResultOk);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::UpdateCheckSDSResultError(int ret)
{
	if (m_bInMetaMode)
    {
        Exit_META_Mode(true);
        m_bInMetaMode = false;
    }
	AnsiString s_error;
	AnsiString error_msg="";
	s_error = "SDS ERROR";
	int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    if (isStopTrigger[i])
    {  s_error = prefix + "STOP"; };
	MainForm->COMPercentageArray[i]->Caption = s_error;
    MainForm->Set_COMPercentageCaption(i, s_error);
	m_iComPortIdx = i;
    SyncStopTimer();
    MainForm->btnCOMStartArray[i]->Enabled = true;
    MainForm->cbCOMArray[i]->Enabled = true;
    MainForm->cbAutoPollingArray[i]->Enabled = true;
    MainForm->Set_shpCOMColor(i, clRed);
	MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComProgress(i, 100);
    MainForm->SetPbComForeColor(i, clRed);
	switch(ret)
		{
		  
		  case 1:
		  	error_msg="FAT has no calibration flag";
			break;
		  case 2:
		  	error_msg="SDS has no calibration flag";
			break;
		  case 3:
		  	error_msg="restore SDS failed";
			break;
		  case 4:
		  	error_msg="target not support SDS";
			break;
		  case 5:
		  	error_msg="Failed to Enter META mode for CheckSDS";
			break;
			case 6:
			error_msg="target not support ReadBarcode";
		  default:
			break;
				
		}
	m_asMsg = "ERROR: " +error_msg;//check sds result
	MainForm->m_stBkStatus[i]->Caption=error_msg;
	Synchronize(ShowMsg);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::UpdateMetaResultError()
{
    if (m_bInMetaMode)
    {
        Exit_META_Mode();
        m_bInMetaMode = false;
    }

    AnsiString	s1, s2;
    AnsiString s_error;
    int i;
    s_error = prefix + "ERROR";

    i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    if (isStopTrigger[i])
    {  s_error = prefix + "STOP"; };

    MainForm->COMPercentageArray[i]->Caption = s_error;
    MainForm->Set_COMPercentageCaption(i, s_error);

    m_iComPortIdx = i;
    SyncStopTimer();
    MainForm->btnCOMStartArray[i]->Enabled = true;
    MainForm->cbCOMArray[i]->Enabled = true;
    MainForm->cbAutoPollingArray[i]->Enabled = true;
    MainForm->Set_shpCOMColor(i, clRed);
    MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;

    // access
    if( MainForm->Get_EnableFactoryDatabaseLog() )
    {
        MainForm->SetPassFail( i, TEST_RESULT_FAIL);
        MainForm->SetFailReason( i, ret );
        WaitForSingleObject( hSemaphore, 5000 );
        MainForm->AddDnResultToAccess( i );
    }

    if(check_meta_extra_result !=  CHECK_META_OK)
    {
      if(check_meta_extra_result ==  CHECK_META_FOLDER_ALREADY_EXIST)
      {
          m_asMsg.printf("ERROR:  Backup folder already exist. Please remove the folder before backup.");
      }
      else if(check_meta_extra_result ==  CHECK_META_CREATE_FOLDER_FAIL)
      {
          m_asMsg.printf("ERROR: Can not create backup folder.");
      }
      else if(check_meta_extra_result ==  CHECK_META_FOLDER_DO_NOT_EXIST)
      {
          m_asMsg.printf("ERROR: Can not find backup folder when restore.");
      }
      else if(check_meta_extra_result = CHECK_META_NOT_SUPPORT_GET_RID_ERROR)
      {
           m_asMsg.printf("ERROR: the load can't get RID, please update this load or use comport as backup folder!");
      }
      check_meta_extra_result = CHECK_META_OK;//reset
    }
    else
    {
        m_asMsg = "ERROR: " + AnsiString(META_GetErrorString(m_eMetaResult));
     }
    Synchronize(ShowMsg);

}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::SyncUpdateMetaResultError()
{
    Synchronize(UpdateMetaResultError);
}
//----------------------------------------------------------------------------
void _fastcall TBOOT1::SyncCheckSDSResultError(int ret)
{
    UpdateCheckSDSResultError(ret);
}


META_RESULT  _fastcall TBOOT1::ArgMETAConnectWithTargetViaUSB(
                        META_ConnectByUSB_Req &meta_con_req,
                        META_ConnectByUSB_Report &meta_con_report)
{
    memset(&meta_con_req,    0, sizeof(meta_con_req));
    memset(&meta_con_report, 0, sizeof(meta_con_report));

    meta_con_req.com_port           = m_sComPortSetting.com.number;
    meta_con_req.ms_connect_timeout = 40000;

    meta_con_req.boot_meta_arg.m_bbchip_type = m_sDnParam.e_bbchip_type;
    meta_con_req.boot_meta_arg.m_ext_clock   = m_sDnParam.e_ext_clock;

    meta_con_req.boot_meta_arg.m_ms_boot_timeout           = BOOT_INFINITE;
    meta_con_req.boot_meta_arg.m_max_start_cmd_retry_count = DEFAULT_BROM_START_CMD_RETRY_COUNT;

    // This callback function will be invoke after COM port is opened
    // You can do some initialization by using this callback function.
    //meta_con_req.boot_meta_arg.m_cb_com_init_stage     = cb_com_init_stage;
    //meta_con_req.boot_meta_arg.m_cb_com_init_stage_arg = this;

    // This callback function will be invoke after BootROM start cmd is passed.
    // You can issue other BootROM command by brom_handle and hCOM which provides callback arguments,
    // or do whatever you want otherwise.
    meta_con_req.boot_meta_arg.m_cb_in_brom_stage      = cb_boot_meta_in_brom_stage;
    meta_con_req.boot_meta_arg.m_cb_in_brom_stage_arg  = this;

    // speed-up BootROM stage baudrate
    meta_con_req.boot_meta_arg.m_speedup_brom_baudrate = _TRUE;

    // WM_BROM_READY_TO_POWER_ON_TGT
    meta_con_req.boot_meta_arg.m_ready_power_on_wnd_handle = NULL;
    meta_con_req.boot_meta_arg.m_ready_power_on_wparam     = NULL;
    meta_con_req.boot_meta_arg.m_ready_power_on_lparam     = NULL;

    // serial link authentication arg
    meta_con_req.boot_meta_arg.m_auth_handle              = g_AUTH_HANDLE;
    meta_con_req.boot_meta_arg.m_cb_sla_challenge         = SLA_Challenge;
    meta_con_req.boot_meta_arg.m_cb_sla_challenge_arg     = this;
    meta_con_req.boot_meta_arg.m_cb_sla_challenge_end     = SLA_Challenge_END;
    meta_con_req.boot_meta_arg.m_cb_sla_challenge_end_arg = this;

    meta_con_req.boot_meta_arg.m_usb_enable = _TRUE;

	// META Without Battery,add by wuxiong in 2012/02/20
    meta_con_req.boot_meta_arg.m_enable_without_battery     = MainForm->USBDownloadWOBattery->Checked;
    return META_SUCCESS;
 }

META_RESULT  _fastcall TBOOT1::ArgMETAConnectWithTarget( META_Connect_Req	     &meta_con_req,
                                       META_Connect_Report   &meta_con_report)
{
   static META_COMM_BAUDRATE  meta_com_baudrate[11]=
    {
        META_BAUD115200,
        META_BAUD230400,
        META_BAUD460800,
        META_BAUD921600,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END
    };
   /*
    m_bInMetaMode = false;
    META_RESULT         meta_ret;
    META_Connect_Req	meta_req;
    META_Connect_Report	meta_report;
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    meta_req.com_port = m_sComPortSetting.com.number;
    memcpy(meta_req.baudrate, meta_com_baudrate, sizeof(meta_req.baudrate));
    //meta_req.flowctrl                                  = META_SW_FLOWCTRL;
    //meta_req.ms_connect_timeout                        = 40000;
    meta_req.boot_meta_arg.m_bbchip_type               = bbchip;
    meta_req.boot_meta_arg.m_ext_clock                 = ext_clock;
    meta_req.boot_meta_arg.m_ms_boot_timeout           = 1000*60*3; //BOOT_INFINITE;
    meta_req.boot_meta_arg.m_max_start_cmd_retry_count = DEFAULT_BROM_START_CMD_RETRY_COUNT;
    meta_req.boot_meta_arg.m_cb_in_brom_stage          = ::cb_boot_meta_in_brom_stage;
    meta_req.boot_meta_arg.m_cb_in_brom_stage_arg      = this;
    meta_req.boot_meta_arg.m_speedup_brom_baudrate     = _TRUE;

    meta_req.boot_meta_arg.m_ready_power_on_wnd_handle = NULL;
    meta_req.boot_meta_arg.m_ready_power_on_wparam		= NULL;
    meta_req.boot_meta_arg.m_ready_power_on_lparam		= NULL;

    // serial link authentication argument
    meta_req.boot_meta_arg.m_auth_handle              = g_AUTH_HANDLE;
    meta_req.boot_meta_arg.m_cb_sla_challenge         = SLA_Challenge;
    meta_req.boot_meta_arg.m_cb_sla_challenge_arg     = this;
    meta_req.boot_meta_arg.m_cb_sla_challenge_end     = SLA_Challenge_END;
    meta_req.boot_meta_arg.m_cb_sla_challenge_end_arg = this;

    // EDGE card
    meta_req.boot_meta_arg.m_cb_com_init_stage = ::cb_PowerOnOxford;
    meta_req.boot_meta_arg.m_cb_com_init_stage_arg = this;

    // USB COM
    meta_req.boot_meta_arg.m_usb_enable = _FALSE;

   // SyncResetFactoryDefaultProgress();

    meta_ret = META_ConnectWithTarget_r(m_sDnParam.i_meta_handle, &meta_req, &g_iStopFlag[i], &meta_report);
    if (meta_ret != META_SUCCESS)
    {
        return meta_ret;
    }

    boot_meta_in_brom_stage();

    m_bInMetaMode = true;
    return META_SUCCESS;
    */


    memset(&meta_con_req,    0, sizeof(meta_con_req));
    memset(&meta_con_report, 0, sizeof(meta_con_report));

    meta_con_req.com_port = m_sComPortSetting.com.number;

    memcpy(meta_con_req.baudrate, meta_com_baudrate, sizeof(meta_con_req.baudrate));

    meta_con_req.flowctrl           = META_SW_FLOWCTRL;
    meta_con_req.ms_connect_timeout = 40000;

    meta_con_req.boot_meta_arg.m_bbchip_type = m_sDnParam.e_bbchip_type;
    meta_con_req.boot_meta_arg.m_ext_clock   = m_sDnParam.e_ext_clock;

    meta_con_req.boot_meta_arg.m_ms_boot_timeout           = BOOT_INFINITE;
    meta_con_req.boot_meta_arg.m_max_start_cmd_retry_count = DEFAULT_BROM_START_CMD_RETRY_COUNT;

    // This callback function will be invoke after COM port is opened
	// You can do some initialization by using this callback function.
    //meta_con_req.boot_meta_arg.m_cb_com_init_stage     = cb_com_init_stage;
    //meta_con_req.boot_meta_arg.m_cb_com_init_stage_arg = this;

    // This callback function will be invoke after BootROM start cmd is passed.
	// You can issue other BootROM command by brom_handle and hCOM which provides callback arguments,
	// or do whatever you want otherwise.
    meta_con_req.boot_meta_arg.m_cb_in_brom_stage      = cb_boot_meta_in_brom_stage;
    meta_con_req.boot_meta_arg.m_cb_in_brom_stage_arg  = this;

    // speed-up BootROM stage baudrate
    meta_con_req.boot_meta_arg.m_speedup_brom_baudrate =  _TRUE;

	// WM_BROM_READY_TO_POWER_ON_TGT
    meta_con_req.boot_meta_arg.m_ready_power_on_wnd_handle	= NULL;
    meta_con_req.boot_meta_arg.m_ready_power_on_wparam		= NULL;
	meta_con_req.boot_meta_arg.m_ready_power_on_lparam		= NULL;

	// serial link authentication arg
	meta_con_req.boot_meta_arg.m_auth_handle = g_AUTH_HANDLE;
	meta_con_req.boot_meta_arg.m_cb_sla_challenge         = SLA_Challenge;
	meta_con_req.boot_meta_arg.m_cb_sla_challenge_arg     = this;
	meta_con_req.boot_meta_arg.m_cb_sla_challenge_end     = SLA_Challenge_END;
	meta_con_req.boot_meta_arg.m_cb_sla_challenge_end_arg = this;

    // EDGE card
    meta_con_req.boot_meta_arg.m_cb_com_init_stage = ::cb_PowerOnOxford;
    meta_con_req.boot_meta_arg.m_cb_com_init_stage_arg = this;


    // Boot META, usb flag, must to set false, since call the META_ConnectWithTarget() API
    meta_con_req.boot_meta_arg.m_usb_enable = _FALSE;

	// META Without Battery,add by wuxiong in 2012/02/20
    meta_con_req.boot_meta_arg.m_enable_without_battery     = MainForm->USBDownloadWOBattery->Checked;

    return META_SUCCESS;

}

//==============================================================================
META_RESULT _fastcall TBOOT1::Enter_META_Mode(BOOT_RESULT& boot_result,const BBCHIP_TYPE  bbchip, const EXT_CLOCK  ext_clock)
{
     META_RESULT         meta_ret;
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

    GC_TRACE("====== Tboot::Enter_META_Mode:: Begin Enter_META_Mode ========");

    //if two station usb download
    if (USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
    {
        META_ConnectByUSB_Req meta_con_req;
        META_ConnectByUSB_Report meta_con_report;

		    m_bInMetaMode = false;
		    ArgMETAConnectWithTargetViaUSB(meta_con_req, meta_con_report);

		    WaitForComPortReadyAfterRegisterReady(meta_con_req.com_port);

        GC_TRACE("====== Tboot::Enter_META_Mode:: Begin META_ConnectWithTargetByUSB_r() ========");
        meta_ret =  META_ConnectWithTargetByUSB_r(m_sDnParam.i_meta_handle, &meta_con_req, &g_iStopFlag[i], &meta_con_report);
        boot_result  = meta_con_report.boot_result;
        GC_TRACE("====== Tboot::Enter_META_Mode:: End META_ConnectWithTargetByUSB_r() ========");

    }
    else //uart mode or one station usb download
    {
        META_Connect_Req meta_con_req;
		    META_Connect_Report meta_con_report;


        m_bInMetaMode = false;
        ArgMETAConnectWithTarget(meta_con_req, meta_con_report);

        //return META_ConnectWithTarget(&meta_con_req, &g_stopflag,  &meta_con_report);
        GC_TRACE("====== Tboot::Enter_META_Mode:: Begin META_ConnectWithTarget_r() ========");
        meta_ret = META_ConnectWithTarget_r(m_sDnParam.i_meta_handle, &meta_con_req, &g_iStopFlag[i], &meta_con_report);
        boot_result  = meta_con_report.boot_result;

        GC_TRACE("====== Tboot::Enter_META_Mode:: End META_ConnectWithTarget_r() ========");
    }

    if (meta_ret != META_SUCCESS)
    {
        return meta_ret;
    }
    //set progress bar
    boot_meta_in_brom_stage();

    m_bInMetaMode = true;

    GC_TRACE("====== Tboot::Enter_META_Mode:: End Enter_META_Mode, success ========");

    return META_SUCCESS;
}
//---------------------------------------------------------------------------
META_RESULT _fastcall TBOOT1::Enter_META_Mode_ForOneStationUSBMeta(const BBCHIP_TYPE bbchip,
															const EXT_CLOCK  ext_clock,
															unsigned char com_port)
{
  META_RESULT         meta_ret;
  int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

  GC_TRACE("====== Tboot::Enter_META_Mode:: Begin Enter_META_Mode ========");

  META_ConnectByUSB_Req meta_con_req;
  META_ConnectByUSB_Report meta_con_report;

  m_bInMetaMode = false;
  ArgMETAConnectWithTargetViaUSB(meta_con_req, meta_con_report);

  meta_con_req.com_port = com_port;

  WaitForComPortReadyAfterRegisterReady(com_port);

  GC_TRACE("====== Tboot::Enter_META_Mode:: Begin META_ConnectWithTargetByUSB_r() ========");
  meta_ret =  META_ConnectWithTargetByUSB_r(m_sDnParam.i_meta_handle, &meta_con_req, &g_iStopFlag[i], &meta_con_report);
  GC_TRACE("====== Tboot::Enter_META_Mode:: End META_ConnectWithTargetByUSB_r() ========");

  if (meta_ret != META_SUCCESS)
  {
      return meta_ret;
  }

  //set progress bar
  boot_meta_in_brom_stage();

  m_bInMetaMode = true;

  GC_TRACE("====== Tboot::Enter_META_Mode:: End Enter_META_Mode, success ========");

  return META_SUCCESS;

}
//---------------------------------------------------------------------------
META_RESULT _fastcall TBOOT1::Exit_META_Mode(bool IsShutdownTarget)
{
    META_RESULT MetaResult;

	if(IsShutdownTarget)
	{
	  GC_TRACE("====== Tboot::Exit_META_Mode:: Use META_DisconnectWithTarget_r() fuction ========");
		MetaResult = META_DisconnectWithTarget_r(m_sDnParam.i_meta_handle);
	}
	else
	{
	    GC_TRACE("====== Tboot::Exit_META_Mode:: Use META_DisconnectInMetaMode_r() fuction ========");
		MetaResult = META_DisconnectInMetaMode_r(m_sDnParam.i_meta_handle);
	}

    if (MetaResult == META_SUCCESS)
    {
        m_bInMetaMode = false;
    }

    return MetaResult;
}

//==============================================================================
//////////////////////////// export information  ///////////////////////////////
//==============================================================================
METAAPP_OP_T _fastcall TBOOT1::Get_MetaAppOp(void)
{
    return m_eMetaappOp;
}
//==============================================================================
void _fastcall TBOOT1::UpdateProgressStatus(const int index,const AnsiString& Content,const unsigned char per)
{
  if (index <0 || index>MAX_SUPPORT_PORT_NUM)
  {
    return;
  }

  prefix = Content;
  if(per>=0 && per<=100)
  {
    m_ucProgressPercentage = per;
  }
  Synchronize(UpdateProgress);
}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::UpdateEfuseOperationProgressBarSetting()
{
  int i;
  i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

  MainForm->Set_shpCOMColor(i, clBlue);
  MainForm->SetPbComBackColor(i, clWhite);
  MainForm->SetPbComForeColor(i, clBlue);
}

