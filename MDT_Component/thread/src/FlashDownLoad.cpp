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
*   FlashDownload.cpp
*
* Project:
* --------
*   Multiport download
*
* Description:
* ------------
*  Flash download/format thread source file
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
* Oct 7 2008 MTK02172
* [STP100001827] [Multiport download tool] Multiport download tool ver 3.0840.0
*
*
* Oct 7 2008 MTK02172
* [STP100001827] [Multiport download tool] Multiport download tool ver 3.0840.0
*
*
* Sep 10 2008 MTK02172
* [STP100001803] [Multiport download tool] Multiport download tool ver 3.0836.0
*
*
* Aug 12 2008 mtk00490
* [STP100001788] [Multiport download tool] Multiport download tool ver 3.0832.0
*
*
* May 21 2008 mtk00490
* [STP100001729] [Multiport download tool] Multiport download tool ver 3.0820.0
*
*
* Dec 3 2007 mtk00490
* [STP100001572] [Multiport download tool] Multiport download tool ver 3.0748.0
*
*
* Nov 29 2006 mtk00490
* [STP100001239] [Multiport download tool] Multiport download tool ver 3.1.02
*
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*============================================================================
****************************************************************************/

//---------------------------------------------------------------------------

#pragma hdrstop
#pragma package(smart_init)

#include <vcl.h>
#include <dir.h>
#include <setupapi.h>
#include <Registry.hpp>
#include "meta_dll/inc/meta.h"
#include "sla_challenge/inc/sla_challenge.h"
#include "common/Multiport_Common.h"
#include "common/MD_msg.h"
#include "mdt_component/thread/inc/FlashDownLoad.h"
#include "form/mainform/MultiPortFlashDownloadTool.h"
#include "common/factory_common.h"
#include "comm/pcmcia/t_pcmcia.h"
#include "mdt_component/error_handler/inc/GCTrace.h"
#include "comm/com_util.h"
#include "mdt_component/thread/inc/OSD_com_port_manager.h"
#include "mdt_component/thread/inc/CriticalSectionManager.h"
#include "brom_dll/inc/flashtool_api.h"



extern AUTH_HANDLE_T	g_AUTH_HANDLE;
extern bool g_AUTH_HANDLE_Loaded;
extern DL_HANDLE_LIST_T        g_DL_HANDLE_LIST;
//extern int AutoPullTimes;

//bool isShowNoFormatInfo = false;
//bool isShowFileNotLoaded = false;
//BBCHIP_TYPE gbb_chip_type;
//int boot_stop = 0;
HANDLE Flash_Download_Event[MAX_SUPPORT_PORT_NUM];

HANDLE Wait_USB_Insert_Event[MAX_SUPPORT_PORT_NUM];
HANDLE User_Stop_Event[MAX_SUPPORT_PORT_NUM];
CriticalSectionManager critical_section_manager;
//HANDLE One_Station_Download_USB_Insert_Event;


int g_iStopFlag[MAX_SUPPORT_PORT_NUM];

bool UpdateDownloadProgress[MAX_SUPPORT_PORT_NUM];

extern bool isStopTrigger[MAX_SUPPORT_PORT_NUM];
extern bool isFirstTwoStationUSBDownload[MAX_SUPPORT_PORT_NUM];
extern ROOTCERT_HANDLE_T  g_ROOTCERT_HANDLE;
extern bool g_is_Root_Cert_File_Loaded;
extern ROOTCERT_HANDLE_T  g_ROOTCERT_HANDLE_DL ;
extern bool g_is_Root_Cert_File_In_Download_Handle ;
extern SCERT_HANDLE_T  g_SCERT_HANDLE ;
extern bool g_is_Certificate_File_Loaded ;
extern bool g_is_Send_Root_Cert_Forcely ;

DWORD ThreadBootUpTimeTable[MAX_SUPPORT_PORT_NUM];
HANDLE ThreadBootUpTimeTableMutex;

// access
extern HANDLE hSemaphore;

//extern HANDLE g_hDisableBLMutex;




//=============================================================================
////////////////////////   call back   ////////////////////////////////////////
//=============================================================================
int __stdcall cb_PowerOnOxford(HANDLE hCOM, void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;

    t->m_ptPCMCIA = new TPCMCIA(FALSE, hCOM);
    t->m_ptPCMCIA->FreeOnTerminate = true;

    return 0;
}

//---------------------------------------------------------------------------
int __stdcall cb_download_da_init(void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;
    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;
    MainForm->DownLoadTimeSec[i]=0;

    // access
    if (MainForm->Get_EnableFactoryDatabaseLog())
    {
        TDateTime datetime;
        TDateTime date = datetime.CurrentDate();
        TDateTime time = datetime.CurrentTime();
        sTime     stime;
        time.DecodeTime( &stime.hour, &stime.min, &stime.sec, &stime.msec);
        MainForm->SetDnDate( i, date );
        MainForm->SetDnStartTime( i, time );
        MainForm->SetDnStartsTime( i, stime );
    }
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComProgress(i, 0);
    MainForm->SetPbComForeColor(i, clRed);
    t->m_ucProgressPercentage = 0;
    t->prefix = "DA ";
    t->SyncInitProgress();

    //Next block is added by dongguo for debug Multiport_download_tool multi-thread resource share issue.
	  if(BROM_USB_DOWNLOAD_SUPPORT==t->USB_DL_Support_Status)
	  {
		    Sleep(1000);
	  }
    return 0;
}

//---------------------------------------------------------------------------
int __stdcall cb_download_da(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg)
{

    TBOOT1 *t=(TBOOT1 *)usr_arg;

    t->m_ucProgressPercentage = percent;
    t->prefix = "DA ";
    t->SyncUpdateProgress();
	  if(BROM_USB_DOWNLOAD_SUPPORT==t->USB_DL_Support_Status)
	  {
		    Sleep(20);
	  }
    return 0;
}

//---------------------------------------------------------------------------
int __stdcall cb_download_flash_init(void *usr_arg)
{

    TBOOT1 *t=(TBOOT1 *)usr_arg;
    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;

    t->m_ucProgressPercentage = 0;
    t->prefix = "DL ";
    t->SyncInitProgress();

    MainForm->Set_shpCOMColor(i, clBlue);

    return 0;
}

//---------------------------------------------------------------------------
int __stdcall cb_download_flash(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;

    t->m_ucProgressPercentage = percent;
    t->prefix = "DL ";
    t->SyncUpdateProgress();


    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;
    MainForm->Set_shpCOMColor(i, clBlue);
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComForeColor(i, clBlue);

	  if(100==percent)
	  {
		   if(BROM_USB_DOWNLOAD_SUPPORT==t->USB_DL_Support_Status)
	   	{
			   if(DISABLE_FORMAT==t->m_sDnParam.e_format_op)
		     {
			   	  t->WatchDogTimeOutInterval=t->GetWatchDogTimeOutInterval();
				    t->m_sFtDlArg.m_ms_wdt_timeout_interval=t->WatchDogTimeOutInterval;
			   }
		  }
  	}
    return 0;
}


//---------------------------------------------------------------------------
int __stdcall cb_pre_format_flash_init(void *usr_arg)
{
    TBOOT1 *t = (TBOOT1 *)usr_arg;
    TColor cl_yellow;
	  cl_yellow   = (TColor)0x0000FFFF;
	  int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;

    t->m_ucProgressPercentage = 0;
    t->prefix = "Format ";
    t->SyncInitProgress();

    MainForm->Set_shpCOMColor(i, cl_yellow);
    return 0;
}

//---------------------------------------------------------------------------
int __stdcall cb_pre_format_flash(unsigned char percent, void *usr_arg)
{
     TBOOT1 *t=(TBOOT1 *)usr_arg;
	  TColor cl_yellow;
     cl_yellow   = (TColor)0x0000FFFF;
    t->m_ucProgressPercentage = percent;
    t->prefix = "Format ";
    t->SyncUpdateProgress();

    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;
    MainForm->Set_shpCOMColor(i, cl_yellow);
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComForeColor(i, cl_yellow);

    return 0;
}

/*
function: cb_readback_flash_init
*/
int __stdcall cb_readback_flash_init( HW_StorageType_E  storage_type, unsigned int rb_addr, unsigned int rb_length, const char *rb_filepath, void *usr_arg)
{
    TBOOT1 *t = (TBOOT1 *)usr_arg;
 //   TColor cl_yellow;
    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;
    AnsiString s_type;
    unsigned long long read_addr = rb_addr;
    unsigned long long read_size = rb_length;

    AnsiString s;
    AnsiString s2;
    switch(storage_type)
    {
    case HW_STORAGE_NOR:
        s_type = "NOR";
        break;
    case HW_STORAGE_NAND:
        s_type = "NAND";
        break;
    case HW_STORAGE_EMMC:
        s_type = "eMMC";
        read_addr *= 512;
        read_size *= 512;
        break;
    }

  //  cl_yellow   = (TColor)0x0000FFFF;
    t->m_ucProgressPercentage = 0;
    t->prefix = "RB Nvram ";
    t->SyncUpdateProgress();
    MainForm->Set_shpCOMColor(i, clBlue);
    return 0;
}

int __stdcall cb_readback_flash(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;
	//  TColor cl_yellow;
 //   cl_yellow   = (TColor)0x0000FFFF;
    t->m_ucProgressPercentage = percent;
    t->prefix = "RB Nvram ";
    t->SyncUpdateProgress();

    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;
    MainForm->Set_shpCOMColor(i, clBlue);
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComForeColor(i, clBlue);

    return 0;
}

/*
function: download partition
*/
int __stdcall cb_download_partition_init(void *usr_arg)
{
    TBOOT1 *t = (TBOOT1 *)usr_arg;
    TColor cl_yellow;
    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;

    t->m_ucProgressPercentage = 0;
    t->prefix = "DL Partition ";
    t->SyncInitProgress();

    MainForm->Set_shpCOMColor(i, clAqua);
    return 0;
}

/*
*/
int __stdcall cb_download_partition(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;
//	  TColor cl_yellow;
//    cl_yellow   = (TColor)0x0000FFFF;
    t->m_ucProgressPercentage = percent;
    t->prefix = "DL Partition ";
    t->SyncUpdateProgress();

    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;
    MainForm->Set_shpCOMColor(i, clAqua);
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComForeColor(i, clAqua);

    return 0;
}


//-----------------------------------------------------------------------------
int __stdcall cb_download_bloader_init(void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;
    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;

    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComProgress(i, 0);
    MainForm->SetPbComForeColor(i, clPurple);

    t->m_ucProgressPercentage = 0;
    t->prefix = "BL ";
    t->SyncInitProgress();

    return 0;
}

//-----------------------------------------------------------------------------
int __stdcall cb_download_bloader(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;

    t->m_ucProgressPercentage = percent;
    t->prefix = "BL ";
    t->SyncUpdateProgress();

    return 0;
}

//==============================================================================
int __stdcall cb_format_report_init(HW_StorageType_E storage_type, unsigned int begin_addr, unsigned int length, void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;
    int i;

    t->m_asMsg.printf("Format %s flash:  begin_addr(0x%08X), length(0x%08X). ", (HW_STORAGE_NOR==storage_type)?"NOR":"NAND", begin_addr, length);
    t->SyncShowMsg();
    t->m_ucProgressPercentage = 0;
    t->prefix = "FR ";
    t->SyncInitProgress();

    return 0;
}

//------------------------------------------------------------------------------
int __stdcall cb_format_report(unsigned char percent, void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;

    t->m_ucProgressPercentage = percent;
    t->prefix = "FR ";
    t->SyncUpdateProgress();

    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComForeColor(i, clGreen);

	if(percent==100)
	{
		if(BROM_USB_DOWNLOAD_SUPPORT==t->USB_DL_Support_Status)
		{
			if(DISABLE_FORMAT!=t->m_sDnParam.e_format_op)
			{
				t->WatchDogTimeOutInterval=t->GetWatchDogTimeOutInterval();
				t->m_sFtDlArg.m_ms_wdt_timeout_interval=t->WatchDogTimeOutInterval;
			}
		}
	}

    return 0;
}

//-----------------------------------------------------------------------------------
int __stdcall cb_before_process(const DA_REPORT_T  *p_da_report, void *usr_arg)
{

    return 0;
}

//------------------------------------------------------------------------------
int __stdcall cb_in_brom_stage(unsigned int brom_handle, HANDLE hCOM, void *usr_arg)
{
#if 0
    int ret;
    unsigned short	value16;
    TBOOT1 *t=(TBOOT1 *)usr_arg;

    if( t->m_sDnParam.b_PullDownGPIO17 && (MT6218B == t->m_sDnParam.e_bbchip_type) )
    {
        // configure GPIO17 mode to GPIO
        value16 = 0x000C;
        ret = Brom_Write16Cmd(brom_handle, hCOM, (0x80120000+0x0120+0x08)/*GPIO_MODE3_CLR*/, &value16, 1);

        // configure GPIO17 direction as output
        value16 = 0x0002;
        ret = Brom_Write16Cmd(brom_handle, hCOM, (0x80120000+0x0010+0x04)/*GPIO_DIR2_SET*/, &value16, 1);

        // pull down GPIO17 to disable vibrator
        value16 = 0x0002;
        ret = Brom_Write16Cmd(brom_handle, hCOM, (0x80120000+0x00a0+0x08)/*GPIO_DOUT2_CLR*/, &value16, 1);
        return ret;
    }
#endif
	//Next block is added by dongguo for debug Multiport_download_tool multi-thread resource share issue.
	//Pause this thread.
	Sleep(1000);
    return 0;

}

//---------------------------------------------------------------------------
int __stdcall cb_format_statistics(const FormatStatisticsReport_T  *p_report, void *usr_arg)
{
    return 0;
}

//--------------------------------------------------------------------------
int __stdcall cb_update_param_init(void *usr_arg)
{
    return 0;
}

//--------------------------------------------------------------------------
static int __stdcall cb_update_param(unsigned char percent, void *usr_arg)
{
    return 0;
}

//--------------------------------------------------------------------------
static int __stdcall cb_post_process_init(void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;

    t->m_ucProgressPercentage = 0;
    t->prefix = "Generate MAC";
    t->SyncInitProgress();

    return 0;
}

//--------------------------------------------------------------------------
static int __stdcall cb_post_process(unsigned char percent, void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;
    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;

    t->m_ucProgressPercentage = percent;
    t->prefix = "Generate MAC ";
    t->SyncUpdateProgress();

    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComForeColor(i, clNavy);

    return 0;

}

//---------------------------------------------------------------------------
static int __stdcall cb_security_pre_process_notify(void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;

    t->m_asMsg.printf("Proceed 1st time download pre-process ... (it takes about 10~15 seconds)\n\nPlease press OK to continue!");
    t->SyncShowMsg();

    return 0;
}

//--------------------------------------------------------------------------
static int __stdcall cb_security_post_process_notify(void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;

    t->m_asMsg.printf("Proceed 1st time download post-process ... (it takes about 10~15 seconds)\n\nPlease press OK to continue!");
    t->SyncShowMsg();

    return 0;
}
//==============================================================================
__fastcall TBOOT1::TBOOT1(bool CreateSuspended, HANDLE hMsgHandle, COM_PORT_SETTING com_port_setting, S_DN_PARAM_T dn_param)
: TThread(CreateSuspended)
{
    hPostMsgDestHandle = hMsgHandle;

    m_sComPortSetting = com_port_setting;
    m_sDnParam       = dn_param;

    checkusbresult = CHECKUSB_OK;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::StopTimer()
{
    MainForm->Stop_Timer(m_iComPortIdx);
}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::SyncStopTimer()
{
    Synchronize(StopTimer);
}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::ShowMsg()
{
    MainForm->sbMPDT->Panels->Items[0]->Text = m_asMsg;
}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::SyncShowMsg()
{
    Synchronize(ShowMsg);
}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::Start()
{
    int i;
    char captionShowBuf[512];
    i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    if(m_eWithoutBatteryKey == FLASHTOOL_WITHOUT_BATTERY_ON & m_RetryTimes>0)
    {
       sprintf(captionShowBuf, "RetryTimes: %d", m_RetryTimes);
       MainForm->Set_COMPercentageCaption(i, captionShowBuf);
	   m_asMsg = "";
	   MainForm->Clear_BackupRestoreStatus(i);
    }
	if(m_RetryFlag==1)
	{
       sprintf(captionShowBuf, "Retry");
       MainForm->Set_COMPercentageCaption(i, captionShowBuf);
	   m_asMsg = "";
	   MainForm->Clear_BackupRestoreStatus(i);
    }
	else if(m_RetryFlag==2)//Linux retry to enter restore only flow
	{
		sprintf(captionShowBuf, "Retry");
        MainForm->Set_COMPercentageCaption(i, captionShowBuf);
		m_asMsg = "NV data existed on PC,Please Re-Plug the target to restore it.";		
		//MainForm->m_stBkStatus[i]->Caption="Please Re-Plug the target!";
	}
		
    else
    {
       MainForm->Set_COMPercentageCaption(i, "START");
	   m_asMsg = "";
	   MainForm->Clear_BackupRestoreStatus(i);
    }

    MainForm->Set_shpCOMColor(i, clBlue);
    MainForm->SetPbComProgress(i, 0);
    
	//m_asMsg.printf("TotalRuningTimes: %d", AutoPullTimes);// for record total run times
    SyncShowMsg();
    //MainForm->Clear_BackupRestoreStatus(i);
}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::SyncStart()
{
    Synchronize(Start);
}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::InitProgress()
{
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    MainForm->Set_COMPercentageCaption(i, prefix);
}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::SyncInitProgress()
{
    Synchronize(InitProgress);
}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::UpdateProgress()
{
    AnsiString s;
    int i;

    s = prefix;
    i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    MainForm->Set_COMPercentageCaption(i, s);
    MainForm->pbCOMArray[i]->Progress = m_ucProgressPercentage;
}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::SyncUpdateProgress()
{
    Synchronize(UpdateProgress);
}

//---------------------------------------------------------------------------
//void _fastcall TBOOT1::SyncUpdateMETAHandle()
//{
//	Synchronize(UpdateMETAHandle);
//}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::UpdateResultError()
{
    AnsiString	s1, s2;
    AnsiString s_error;
    int i;
    s_error = prefix + "ERROR";

    i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    if( isStopTrigger[i] )
    {
        s_error = prefix + "STOP";
    };

    MainForm->COMPercentageArray[i]->Caption = s_error;
    MainForm->Set_COMPercentageCaption( i, s_error );


    SyncStopTimer();
    MainForm->btnCOMStartArray[i]->Enabled = true;
    MainForm->cbCOMArray[i]->Enabled = true;
    MainForm->cbAutoPollingArray[i]->Enabled = true;
    MainForm->Set_shpCOMColor( i, clRed );
    MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;

    // access
    if( MainForm->Get_EnableFactoryDatabaseLog() )
    {
        MainForm->SetPassFail( i, TEST_RESULT_FAIL);
        MainForm->SetFailReason( i, ret );
        WaitForSingleObject( hSemaphore, 5000 );
        MainForm->AddDnResultToAccess( i );
    }

    if (m_bBackup)
    {
        m_asMsg.printf("Already Backup!! Watch dog reset might not work. Please try to download and Restore calibration data. Call for help if fail.");
    }
    else if(checkusbresult != CHECKUSB_OK)
    {
        m_asMsg.printf("Error:  CHECKUSB_PID_VID_NOT_MATCH");
    }
    else
    {
        switch (ret)
        {
        case S_DA_NOR_UNSUPPORTED_DEV_ID:
        case S_DA_NAND_UNSUPPORTED_DEV_ID:
            {
                m_asMsg.printf("Error: Flash not support, please refer to Memory_Validation_List_External.xls for current support flash list.");
            }
            break;

        default:
            {
                if (S_SECURITY_ERROR_BEGIN <= ret)
                {
                    m_asMsg.printf("Error: %s(%d) \n\nMSP Error Code: 0x%02X", StatusToString(ret), ret, m_sFtResult.m_da_report.m_msp_err_code);
                }
                else if(ret>=0)
                {
                    m_asMsg.printf("Error: %s(%d) ", StatusToString(ret), ret);
                }
            }
            break;
        }
    }

    Synchronize(ShowMsg);

    SyncEnableUI();
    //EnableUI();

}

void _fastcall TBOOT1::SyncEnableUI()
{
    Synchronize(EnableUI);
}
void _fastcall TBOOT1::EnableUI()
{
    for(int j=0; j<MAX_SUPPORT_PORT_NUM; j++)
    {
        if( MainForm->DownloadStatus[j] == DOWNLOAD_STATUS_RUNNING ) return;
    }
    MainForm->Enable_UIComponent();

}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::SyncUpdateResultError()
{
    Synchronize(UpdateResultError);
}


//---------------------------------------------------------------------------
void _fastcall TBOOT1::UpdateResultOk()
{
    AnsiString s_ok;
    int i;

    s_ok = prefix + "OK";

    i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    if(i<0 || i>MAX_SUPPORT_PORT_NUM)
    {
      return ;
    }
    // access
    if( MainForm->Get_EnableFactoryDatabaseLog() )
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
    MainForm->Set_COMPercentageCaption( i, s_ok );
    SyncStopTimer();
    MainForm->btnCOMStartArray[i]->Enabled = true;
    MainForm->cbCOMArray[i]->Enabled = true;
    MainForm->cbAutoPollingArray[i]->Enabled = true;
    MainForm->Set_shpCOMColor( i, clGreen );
    MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;
    PostMessage(
        hPostMsgDestHandle,
        WM_MD_DOWNLOAD_SUCCESSFUL,
        i,
        0
        );

}

//---------------------------------------------------------------------------
void _fastcall TBOOT1::SyncUpdateResultOk()
{
    Synchronize(UpdateResultOk);
}

//--------------------------------------------------------------------------
/*
void _fastcall TBOOT1::SyncUpdateMainFormAfterFinishOk(void)
{
Synchronize(UpdateMainFormAfterFinishOk);
}*/

void _fastcall TBOOT1::Set_FlashTool_arg(void)
{

  // FLASHTOOL_ARG setting
  m_sFtArg.m_boot_arg.m_bbchip_type = AUTO_DETECT_BBCHIP;
  m_sFtArg.m_boot_arg.m_ext_clock = m_sDnParam.e_ext_clock;
  m_sFtArg.m_boot_arg.m_ms_boot_timeout = BOOT_INFINITE;
  m_sFtArg.m_boot_arg.m_max_start_cmd_retry_count = DEFAULT_BROM_START_CMD_RETRY_COUNT;
  m_sFtArg.m_boot_arg.m_p_bank0_mem_cfg = m_sDnParam.s_emi_param.b_bank0_auto?NULL:&(m_sDnParam.s_emi_param.ui_bank0_cfg);
  m_sFtArg.m_boot_arg.m_p_bank1_mem_cfg = m_sDnParam.s_emi_param.b_bank1_auto?NULL:&(m_sDnParam.s_emi_param.ui_bank1_cfg);
  m_sFtArg.m_boot_arg.m_da_handle = g_DA_HANDLE;
  m_sFtArg.m_boot_arg.m_cb_download_da_init = ::cb_download_da_init;
  m_sFtArg.m_boot_arg.m_cb_download_da_init_arg = this;
  m_sFtArg.m_boot_arg.m_cb_download_da = ::cb_download_da;
  m_sFtArg.m_boot_arg.m_cb_download_da_arg = this;
  m_sFtArg.m_cb_set_high_speed_baudrate = NULL;
  m_sFtArg.m_cb_set_high_speed_baudrate_arg = NULL;
  m_sFtArg.m_nor_chip_select[0] = CS0;
  m_sFtArg.m_nor_chip_select[1] = CS_WITH_DECODER;
  m_sFtArg.m_nand_chip_select   = m_sDnParam.s_bbchip_op.b_enable_nfi_cs1?CS1:CS0;
  m_sFtArg.m_p_nand_acccon      = NULL;

  m_sFtArg.m_boot_arg.m_cb_in_brom_stage = ::cb_in_brom_stage;
  m_sFtArg.m_boot_arg.m_cb_in_brom_stage_arg = this;
  m_sFtArg.m_baudrate_full_sync_count = 0;
  m_sFtArg.m_boot_arg.m_speedup_brom_baudrate = _TRUE;

  //if customer want to disconnect com port after download, they could setting it on menu
    if(m_sDnParam.b_disconnect_comport_option)
    {
        m_sFtArg.m_boot_arg.m_usb_com_port_control=USB_COM_PORT_CONTROL_REMOVE_PORT_UPON_DISCONNECTION;
    }
    else
    {
        m_sFtArg.m_boot_arg.m_usb_com_port_control= USB_COM_PORT_CONTROL_NO_OPERATION;
    }

    if( MainForm->USBDownloadWOBattery->Checked == true)
    {
  	   m_sFtArg.m_enable_download_without_battery = _TRUE;
    }
    else
    {
  	   m_sFtArg.m_enable_download_without_battery = _FALSE;
    }
    // enable DRAM setting from UI thread
    m_sFtArg.m_enable_ui_dram_cfg = _FALSE;

    // WM_BROM_READY_TO_POWER_ON_TGT
    m_sFtArg.m_boot_arg.m_ready_power_on_wnd_handle	= NULL;
    m_sFtArg.m_boot_arg.m_ready_power_on_wparam		= NULL;
    m_sFtArg.m_boot_arg.m_ready_power_on_lparam		= NULL;

    // serial link authentication arg
    m_sFtArg.m_boot_arg.m_auth_handle              = g_AUTH_HANDLE_Loaded ? g_AUTH_HANDLE : NULL;//g_AUTH_HANDLE;  mingxue2012-12-12
    m_sFtArg.m_boot_arg.m_cb_sla_challenge         = SLA_Challenge;
    m_sFtArg.m_boot_arg.m_cb_sla_challenge_arg     = this;
    m_sFtArg.m_boot_arg.m_cb_sla_challenge_end     = SLA_Challenge_END;
    m_sFtArg.m_boot_arg.m_cb_sla_challenge_end_arg = this;

    // EDGE card
    m_sFtArg.m_boot_arg.m_cb_com_init_stage = ::cb_PowerOnOxford;
    m_sFtArg.m_boot_arg.m_cb_com_init_stage_arg = this;
    MainForm->m_p_LinkMapFileManager->loadExternalMemorySetting(&m_sFtArg.m_boot_arg.m_external_memory_setting[0]);
    m_sFtArg.m_boot_arg.m_enable_usb_2_0 =MainForm->m_bEnableUSB1_1To2_0;//huifen;

    //get bad block manage pool addr--by wuxiong
    Get_BMTPoolAddress(&m_sFtArg.m_bmt_pool_address);

    // USB COM
    if((USB_COM == m_sDnParam.e_com_type) && IsUSBDownloadWithTwoSite())
    {
        m_sFtArg.m_boot_arg.m_usb_enable = _TRUE;
    }
    else
    {
        m_sFtArg.m_boot_arg.m_usb_enable = _FALSE;
    }

    m_sFtArg.m_disable_flashID_comparison = _FALSE;

    if(true == g_is_Root_Cert_File_Loaded)
    {
        m_sFtArg.m_boot_arg.m_rootcert_handle = g_ROOTCERT_HANDLE;
        m_sFtArg.m_boot_arg.m_rootcert_force_assign = g_is_Send_Root_Cert_Forcely;
        GC_TRACE_EX("Use Config Root Cert File:0x%08X",&g_ROOTCERT_HANDLE);
    }
    else if(true == g_is_Root_Cert_File_In_Download_Handle)
    {
        m_sFtArg.m_boot_arg.m_rootcert_handle = g_ROOTCERT_HANDLE_DL;
        m_sFtArg.m_boot_arg.m_rootcert_force_assign = g_is_Send_Root_Cert_Forcely;
        GC_TRACE_EX("Use Certificate File in Download Handle:0x%08X",&g_ROOTCERT_HANDLE_DL);
    }
    else
    {
        m_sFtArg.m_boot_arg.m_rootcert_handle = NULL;
        m_sFtArg.m_boot_arg.m_rootcert_force_assign = false;
        GC_TRACE_EX("Root Cert is NULL");
    }

    if(true == g_is_Certificate_File_Loaded)
    {
        m_sFtArg.m_boot_arg.m_scert_handle = g_SCERT_HANDLE;
        GC_TRACE_EX("Use Certificate File:0x%08X",&g_SCERT_HANDLE);
    }
    else
    {
        m_sFtArg.m_boot_arg.m_scert_handle = NULL;
        GC_TRACE_EX("Certificate is NULL");
    }

}

/*
Function: Since MT6280 has the Bad block manage region,so we should get the pool addr of bad block
          manage region.
History:
       2012/12/04: add by wuxiong
*/
bool _fastcall TBOOT1::Get_BMTPoolAddress(unsigned int * iBmt_Pool_Address)
{

    DL_HANDLE_T dl_handle=NULL;
    unsigned int BmtPoolAddress = 0;
    int iHandleNum=0;
    int iCycle = 0;
    bool bBmtPoolAddrret = false;

    //get dl handle from g_DL_HANDLE_LIST
    DL_GetHandleNumber(g_DL_HANDLE_LIST, &iHandleNum);
    GC_TRACE_EX("dl_handle num of g_DL_HANDLE_LISTis is %d.",&iHandleNum);
    if(NULL!=g_DL_HANDLE_LIST)
    {
        for(iCycle = 0; iCycle < iHandleNum; iCycle++)
        {
            if(S_DONE==DL_GetHandle(g_DL_HANDLE_LIST,iCycle,&dl_handle))
            {
                DL_GetBMTPoolAddress(dl_handle, &BmtPoolAddress);
                bBmtPoolAddrret = true;
                if( 0 != BmtPoolAddress)
                {
                    break;
                }
            }
        }
    }
    *iBmt_Pool_Address = BmtPoolAddress;
    GC_TRACE_EX("Bad block manage pool addr is %d.",BmtPoolAddress);
    return bBmtPoolAddrret;
}

//--------------------------------------------------------------------------
int __stdcall cb_flashtool_EnableBootCert_init(void *usr_arg)
{
  TBOOT1 *t=(TBOOT1 *)usr_arg;
  int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;

  t->m_ucProgressPercentage = 0;
  t->prefix = "BootCert";
  t->SyncInitProgress();

  MainForm->Set_shpCOMColor(i, clBlue);
  MainForm->SetPbComBackColor(i, clWhite);
  MainForm->SetPbComForeColor(i, 0x008A28E5);

  return 0;
}
//--------------------------------------------------------------------------
int __stdcall cb_flashtool_EnableBootCert(unsigned char finished_percentage, void *usr_arg)
{
  TBOOT1 *t=(TBOOT1 *)usr_arg;

  t->m_ucProgressPercentage = finished_percentage;
  t->SyncUpdateProgress();

  int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;
  MainForm->Set_shpCOMColor(i, clBlue);
  MainForm->SetPbComBackColor(i, clWhite);
  MainForm->SetPbComForeColor(i, 0x008A28E5);

  return 0;
}
//--------------------------------------------------------------------------
void _fastcall TBOOT1::Set_FlashTool_EnableBootCert_arg(void)
{
  if(NULL != MainForm->m_boot_Cert.m_data
    && MainForm->m_boot_Cert.m_len>0)
  {
    m_sEnableBoot_Arg.m_boot_cert = MainForm->m_boot_Cert;
  }
  else
  {
    memset(&m_sEnableBoot_Arg.m_boot_cert,0x00,sizeof(m_sEnableBoot_Arg.m_boot_cert));
  }

  m_sEnableBoot_Arg.m_cb_enable_boot_process_init = cb_flashtool_EnableBootCert_init;
  m_sEnableBoot_Arg.m_cb_enable_boot_process_init_arg = this;
  m_sEnableBoot_Arg.m_cb_enable_boot_process = cb_flashtool_EnableBootCert;
  m_sEnableBoot_Arg.m_cb_enable_boot_process_arg = this;
}

//--------------------------------------------------------------------------
void _fastcall TBOOT1::Set_FlashTool_download_arg(void)
{
    //FLASHTOOL_DOWNLOAD_ARG settings
    m_sFtDlArg.m_dl_handle_list                      = g_DL_HANDLE_LIST;
    m_sFtDlArg.m_dl_handle                           = NULL;
    m_sFtDlArg.m_download_accuracy                   = ACCURACY_AUTO;
    m_sFtDlArg.m_cb_download_flash_init              = ::cb_download_flash_init;
    m_sFtDlArg.m_cb_download_flash_init_arg          = this;
    m_sFtDlArg.m_cb_download_flash                   = cb_download_flash;
    m_sFtDlArg.m_cb_download_flash_arg               = this;

    m_sFtDlArg.m_cb_security_post_process_notify     = ::cb_security_post_process_notify;
    m_sFtDlArg.m_cb_security_post_process_notify_arg = this;

	  m_sFtDlArg.m_cb_pre_format_flash_init			       = ::cb_pre_format_flash_init;
	  m_sFtDlArg.m_cb_pre_format_flash_init_arg 		   = this;
	  m_sFtDlArg.m_cb_pre_format_flash				         = ::cb_pre_format_flash;
	  m_sFtDlArg.m_cb_pre_format_flash_arg			       = this;

    m_sFtDlArg.m_cb_download_partition_init          = ::cb_download_partition_init;
    m_sFtDlArg.m_cb_download_partition_init_arg      = this;
    m_sFtDlArg.m_cb_download_partition               = ::cb_download_partition;
    m_sFtDlArg.m_cb_download_partition_arg           = this;

    m_sFtDlArg.m_cb_nvram_backup_init               = cb_readback_flash_init;
    m_sFtDlArg.m_cb_nvram_backup_init_arg           = this;
    m_sFtDlArg.m_cb_nvram_backup                    = cb_readback_flash;
    m_sFtDlArg.m_cb_nvram_backup_arg                = this;

    m_sFtDlArg.m_enable_tgt_res_layout_check         = _TRUE;

    m_sFtDlArg.m_enable_bbchip_ver_check             = (_BOOL)(m_sDnParam.s_bbchip_op.b_check_bbchip_version);

    m_sFtDlArg.m_cb_format_statistics                = ::cb_format_statistics;
    m_sFtDlArg.m_cb_format_statistics_arg            = this;

    //mingxue flash safe mode
    if(MainForm->FlashSafeMode->Checked==TRUE)
    {
    	m_sFtDlArg.m_nor_flash_erase_mode			= NOR_FLASH_ERASE_SAFE_MODE;
    }
    else
    {
        m_sFtDlArg.m_nor_flash_erase_mode			= NOR_FLASH_ERASE_FAST_MODE;
    }

	//end
    switch (m_sDnParam.e_format_op)
    {
    case RESET_TO_FACTORY:
        {
            m_sFtDlArg.m_format_enable = _FALSE;
            m_sFtDlArg.m_format_cfg.m_auto_format_fat = _FALSE;
            m_sFtDlArg.m_enable_wdt_timeout = _TRUE;
            m_sFtDlArg.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
			//add 2013-05-23,mtk71518
			m_sFtDlArg.m_enable_reset_to_download_mode = _TRUE;
            m_sFtDlArg.m_download_mode_op = RESET_DOWNLOAD_OPERATION_BY_BOOTLOADER; //for usbdl 2.0 feature
        }
        break;

    case AUTO_FORMAT:
        {
            m_sFtDlArg.m_format_enable = _TRUE;
            m_sFtDlArg.m_format_cfg.m_auto_format_fat = _TRUE;
            m_sFtDlArg.m_enable_wdt_timeout = _FALSE;
            m_sFtDlArg.m_ms_wdt_timeout_interval = 0;
        }
        break;

    case MANUAL_FORMAT:
        {
            m_sFtDlArg.m_format_enable = _TRUE;
            m_sFtDlArg.m_format_cfg.m_auto_format_fat   = _FALSE;
            if( OPERATION_NOR == m_sDnParam.e_Operation )
            {
                m_sFtDlArg.m_format_cfg.m_format_begin_addr = m_sDnParam.s_nor_param.ui_fat_begin_addr;
                m_sFtDlArg.m_format_cfg.m_format_length     = m_sDnParam.s_nor_param.ui_fat_length;
            }
            else
            {
                m_sFtDlArg.m_format_cfg.m_format_begin_addr = m_sDnParam.s_nfb_param.ui_nand_fat_begin_addr;
                m_sFtDlArg.m_format_cfg.m_format_length     = m_sDnParam.s_nfb_param.ui_nand_fat_length;
            }
            m_sFtDlArg.m_enable_wdt_timeout = _FALSE;
            m_sFtDlArg.m_ms_wdt_timeout_interval = 0;
        }
        break;

    case DISABLE_FORMAT:
    default:
        {
            m_sFtDlArg.m_format_enable = _FALSE;
            m_sFtDlArg.m_format_cfg.m_auto_format_fat = _FALSE;
            m_sFtDlArg.m_enable_wdt_timeout = _FALSE;
            m_sFtDlArg.m_ms_wdt_timeout_interval = 0;
        }
        break;
    }

    if (DN_WITHOUT_BK_AND_RS_CAL_DATA != m_sDnParam.e_backup_cal_data_op)
    {
        m_sFtDlArg.m_enable_wdt_timeout = _TRUE;
        m_sFtDlArg.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
		//add 2013-05-23,mtk71518
		m_sFtDlArg.m_enable_reset_to_download_mode = _TRUE;
        m_sFtDlArg.m_download_mode_op = RESET_DOWNLOAD_OPERATION_BY_BOOTLOADER; //for usbd
    }
    else if(RESET_TO_FACTORY == m_sDnParam.e_format_op)
    {
        m_sFtDlArg.m_enable_wdt_timeout = _TRUE;
        m_sFtDlArg.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
		//add 2013-05-23,mtk71518
		m_sFtDlArg.m_enable_reset_to_download_mode = _TRUE;
        m_sFtDlArg.m_download_mode_op = RESET_DOWNLOAD_OPERATION_BY_BOOTLOADER; //for usbd
    }
    else if( IsEnterMetaModeAfterDLMFT() ) //enter meta mode
    {
        m_sFtDlArg.m_enable_wdt_timeout = _TRUE;
        m_sFtDlArg.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
		//add 2013-05-23,mtk71518
		m_sFtDlArg.m_enable_reset_to_download_mode = _TRUE;
        m_sFtDlArg.m_download_mode_op = RESET_DOWNLOAD_OPERATION_BY_BOOTLOADER; //for usbd
    }
    else
    {
        m_sFtDlArg.m_enable_wdt_timeout      = _FALSE;
        m_sFtDlArg.m_ms_wdt_timeout_interval = 0;
    }
    //////
    //if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
    //{
    //    m_sFtDlArg.m_enable_wdt_timeout = _TRUE;
    //   m_sFtDlArg.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
    //}
    //////

    // parameter
    m_sFtDlArg.m_otp_enable = _FALSE;
    m_sFtDlArg.m_otp_op = m_sDnParam.s_param.m_otp_op;
    m_sFtDlArg.m_otp.m_addr = m_sDnParam.s_param.m_otp.m_addr;
    m_sFtDlArg.m_otp.m_data = m_sDnParam.s_param.m_otp.m_data;
    m_sFtDlArg.m_otp.m_len = m_sDnParam.s_param.m_otp.m_len;
    m_sFtDlArg.m_ft_cfg_enable = _FALSE;
    m_sFtDlArg.m_ft_cfg.m_security_cfg.m_uint32 = m_sDnParam.s_param.m_ft_cfg.m_security_cfg.m_uint32;

    /*m_sFtDlArg.m_sec_ro_enable = m_sDnParam.s_param.m_sec_ro_enable;
    m_sFtDlArg.m_sec_ro.m_data = m_sDnParam.s_param.m_sec_ro.m_data;
    m_sFtDlArg.m_sec_ro.m_len = m_sDnParam.s_param.m_sec_ro.m_len;
   */

    //Caution:  not support Secure Chip Temporary.

    /*
    m_sFtDlArg.m_sec_ro_enable = (_BOOL)(!MainForm->m_scatter_manager.get_sec_ro().empty());
    m_sFtDlArg.m_sec_ro.m_data = MainForm->m_scatter_manager.get_sec_ro().get_buf();
    m_sFtDlArg.m_sec_ro.m_len  = MainForm->m_scatter_manager.get_sec_ro().get_len();
    */

    if(MainForm->m_p_LinkMapFileManager->IsWithSecureRO())
    {
      m_sFtDlArg.m_sec_ro_enable = (_BOOL)(!MainForm->m_p_LinkMapFileManager->get_sec_ro()->empty());
      m_sFtDlArg.m_sec_ro.m_data = MainForm->m_p_LinkMapFileManager->get_sec_ro()->get_buf();
      m_sFtDlArg.m_sec_ro.m_len  = MainForm->m_p_LinkMapFileManager->get_sec_ro()->get_len();
    }
    else
    {
      m_sFtDlArg.m_sec_ro_enable = _FALSE;
      m_sFtDlArg.m_sec_ro.m_data = NULL;
      m_sFtDlArg.m_sec_ro.m_len  = 0;
    }
    m_sFtDlArg.m_cust_para_enable = _FALSE;
    m_sFtDlArg.m_cust_para.m_data = m_sDnParam.s_param.m_cust_para.m_data;
    m_sFtDlArg.m_cust_para.m_len = m_sDnParam.s_param.m_cust_para.m_len;

    m_sFtDlArg.m_cb_param_process_init     = ::cb_update_param_init;
    m_sFtDlArg.m_cb_param_process_init_arg = this;
    m_sFtDlArg.m_cb_param_process	       = ::cb_update_param;
    m_sFtDlArg.m_cb_param_process_arg      = this;

    m_sFtDlArg.m_cb_post_process_init      = ::cb_post_process_init;
    m_sFtDlArg.m_cb_post_process_init_arg  = this;
    m_sFtDlArg.m_cb_post_process	       = ::cb_post_process;
    m_sFtDlArg.m_cb_post_process_arg       = this;

    m_sFtDlArg.m_cb_format_report_init       = ::cb_format_report_init;
    m_sFtDlArg.m_cb_format_report_init_arg   = this;
    m_sFtDlArg.m_cb_format_report            = ::cb_format_report;
    m_sFtDlArg.m_cb_format_report_arg        = this;
    m_sFtDlArg.m_enable_tgt_res_layout_check = _TRUE;
    m_sFtDlArg.m_enable_bbchip_ver_check     = (_BOOL)(m_sDnParam.s_bbchip_op.b_check_bbchip_version);
    m_sFtDlArg.m_cb_format_statistics        = ::cb_format_statistics;
    m_sFtDlArg.m_cb_format_statistics_arg    = this;



    if( /*OPERATION_NFB == m_sDnParam.e_Operation*/  MainForm->Get_Operation())
    {
        // for NFB bloader
        m_sFtDlArg.m_format_cfg.m_validation      = m_sDnParam.s_nfb_param.b_validation;
        m_sFtDlArg.m_cb_download_bloader_init     = ::cb_download_bloader_init;
        m_sFtDlArg.m_cb_download_bloader_init_arg = this;
        m_sFtDlArg.m_cb_download_bloader          = ::cb_download_bloader;
        m_sFtDlArg.m_cb_download_bloader_arg      = this;
    }
    else
    {
        // m_sFtDlArg.m_nfb_enable = _FALSE;
        m_sFtDlArg.m_format_cfg.m_validation      = m_sDnParam.s_nor_param.b_validation;
        m_sFtDlArg.m_cb_download_bloader_init     = NULL;
        m_sFtDlArg.m_cb_download_bloader_init_arg = NULL;
        m_sFtDlArg.m_cb_download_bloader          = NULL;
        m_sFtDlArg.m_cb_download_bloader_arg      = NULL;
    }

    // GPS
    /*
    m_sFtDlArg.m_relay_da_enable           = m_sDnParam.s_param.m_gps_enable;
    m_sFtDlArg.m_gpio_gps.m_power_pin      = m_sDnParam.s_param.m_gps_power_pin;
    m_sFtDlArg.m_gpio_gps.m_reset_pin      = m_sDnParam.s_param.m_gps_reset_pin;
    m_sFtDlArg.m_gpio_gps.m_standby_pin    = m_sDnParam.s_param.m_gps_standby_pin;
    m_sFtDlArg.m_gpio_gps.m_32k_pin        = m_sDnParam.s_param.m_gps_32k_pin;
    */
    //backup nvram partition
     m_sFtDlArg.m_nvram_partition_backup = MainForm->m_bEnableBackupNvramPartition;
	   USB_DL_Support_Status=Is_Support_BROM_USB_DL();
}

/*
Function: check if it need meta action before download
History:
1. 2012/10/11 by wuxiong: Mask DN_WITH_RS_CAL_DATA case,
   if it fails in download step when doing backup->download->restore,it can't enter into
   meta mode to check nvram info,so we should mask this case to avoid the risk of checking
    nvram info in meta mode.
*/
bool _fastcall TBOOT1::is_have_meta_action_before_download()
{
    switch (m_sDnParam.e_backup_cal_data_op)
    {
    case DN_WITH_BK_AND_RS_CAL_DATA:
    /*if it fails in download step when doing backup->download->restore,
      it can't enter into meta mode to check nvram info,so we should mask
      this code to avoid the risk of checking nvram info in meta mode.*/
    //case DN_WITH_RS_CAL_DATA:
    case RS_CAL_DATA_ONLY:
	case CHECK_SDS_ONLY:
    case UPLOAD_USER_DATA_ONLY:
        {
            return true;
        }
    }
    return false;
}

//if fail, return STATUS_FAIL
//if success, and need go on, return SUCCESS_AND_GOON
//if success, bug not go on, return SUCCESS_BUT_NOT_GOON

E_ResultAndAction _fastcall TBOOT1::Meta_action_before_download()
{
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    m_bBackup = false;
	int ret;

    switch (m_sDnParam.e_backup_cal_data_op)
    {
    case DN_WITH_BK_AND_RS_CAL_DATA:
        {
            m_eMetaResult = BackupCalData();
            if (m_eMetaResult != META_SUCCESS)
            {
                SyncUpdateMetaResultError();
                SetEvent(Flash_Download_Event[i]);
                return STATUS_FAIL;
            }
        }
        break;

/*this case of DN_WITH_RS_CAL_DATA will never use again,because we have mask this case in this function:
  is_have_meta_action_before_download() ---add by wuxiong*/
    case DN_WITH_RS_CAL_DATA:
        {
            m_eMetaResult = CheckBackupResultInfo();
            if (m_eMetaResult != META_SUCCESS)
            {
                SyncUpdateMetaResultError();
                SetEvent(Flash_Download_Event[i]);
                return STATUS_FAIL;
            }
        }
        break;

    case RS_CAL_DATA_ONLY:
        {
            m_eMetaResult = RestoreCalData();
            if (m_eMetaResult != META_SUCCESS)
            {
                SyncUpdateMetaResultError();
                SetEvent(Flash_Download_Event[i]);
                return STATUS_FAIL;
            }
            SyncUpdateMetaResultOk();
            SetEvent(Flash_Download_Event[i]);
            return SUCCESS_BUT_NOT_GOON;
        }
		break;
     case UPLOAD_USER_DATA_ONLY:
        {
            m_eMetaResult = UploadUserData();
            if (m_eMetaResult != META_SUCCESS)
            {
                SyncUpdateMetaResultError();
                SetEvent(Flash_Download_Event[i]);
                return STATUS_FAIL;
            }
            SyncUpdateMetaResultOk();
            SetEvent(Flash_Download_Event[i]);
            return SUCCESS_BUT_NOT_GOON;
        }
	 	break;
	 case CHECK_SDS_ONLY:
	 	{
		   	MainForm->SetPbComBackColor(i, clWhite);
            MainForm->SetPbComProgress(i, 0);
            MainForm->SetPbComForeColor(i, clGreen);
	
			MainForm->COMPercentageArray[i]->Caption = "CheckSDS";
    		MainForm->Set_COMPercentageCaption(i, "CheckSDS");
			m_eMetaResult = CheckSDS(&ret);
			if (m_eMetaResult != META_SUCCESS || (m_eMetaResult==META_SUCCESS && (ret!=0)))
            {
                SyncCheckSDSResultError(ret);
                SetEvent(Flash_Download_Event[i]);
                return STATUS_FAIL;
            }
            SyncCheckSDSResultOk();
            SetEvent(Flash_Download_Event[i]);
            //return SUCCESS_BUT_NOT_GOON;
	 	}
	 break;
    }

    return SUCCESS_AND_GOON;
}

void _fastcall TBOOT1::Initial_download_arg_memory()
{
	memset(&m_sFtArg, 0, sizeof(m_sFtArg));
	memset(&m_sFtDlArg, 0, sizeof(m_sFtDlArg));
	memset(&m_sFtResult, 0, sizeof(m_sFtResult));
	memset(&m_sFmtArg, 0, sizeof(m_sFmtArg));
	memset(&m_sFmtResult, 0, sizeof(m_sFmtResult));
  memset(&m_sEnableBoot_Arg,0x00,sizeof(m_sEnableBoot_Arg));
}

bool _fastcall TBOOT1::is_have_action_after_download()
{
    if (RESET_TO_FACTORY == m_sDnParam.e_format_op)
    {
        return true;
    }

    switch (m_sDnParam.e_backup_cal_data_op)
    {
    case DN_WITHOUT_BK_AND_RS_CAL_DATA:
        {
            if(IsEnterMetaModeAfterDLMFT())
            {
                return true;
            }

        }
        break;

    case DN_WITH_BK_AND_RS_CAL_DATA:
    case DN_WITH_RS_CAL_DATA:
    case DN_WITH_UL_USER_DATA:
    //case UPLOAD_USER_DATA_ONLY:
        return true;


    default:
        break;
    }

    return false;

}

//If need go on return ture
//else return false;
E_ResultAndAction _fastcall TBOOT1::Action_after_download()
{
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

	  E_WAIT_FOR_USB_INSERT_STATUS E_Wait_USB_Insert_Status;

    if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
    {
        //two station usb download
		    E_Wait_USB_Insert_Status=WaitForUSBInsertByOpenComport(i);
		    if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
		    {
			      return STATUS_FAIL;
		    }
    }
    else if(USB_COM == m_sDnParam.e_com_type && !IsUSBDownloadWithTwoSite())
    {  //one station usb download
        m_sFtArg.m_boot_arg.m_usb_enable = _FALSE;
    }

    // GPS download relay mode
    /* //gps download is phase out now
    if (m_sDnParam.s_param.m_gps_enable)
    {
        ret = GPSDownload();
        if (S_DONE != ret)
        {
            // stop timer
            SyncStopTimer();
            MainForm->btnCOMStartArray[i]->Enabled = true;
            MainForm->cbCOMArray[i]->Enabled = true;
            MainForm->cbAutoPollingArray[i]->Enabled = true;
            GetGPSErrorMessag((WRAPPER_RETURN) ret);
            SyncShowMsg();
            SetEvent(Flash_Download_Event[i]);
            return STATUS_FAIL;
        }
     }*/
#ifndef SERVICE_CENTER
    //-----------------------------------------------------------------------
    // reset to factory default
    if (RESET_TO_FACTORY == m_sDnParam.e_format_op)
    {
        //SyncStartFormat();
        m_eMetaResult = Reset_To_Factory_Default_Procedure(m_sDnParam.e_bbchip_type, m_sDnParam.e_ext_clock);
        if (m_eMetaResult != META_SUCCESS)
        {
            SyncUpdateMetaResultError();
            SetEvent(Flash_Download_Event[i]);
            return STATUS_FAIL;
        }
    }
#endif

    // Owen
    switch (m_sDnParam.e_backup_cal_data_op)
    {
    case DN_WITHOUT_BK_AND_RS_CAL_DATA:
        {
            if(IsEnterMetaModeAfterDLMFT())
            {
                m_eMetaResult = EnterMetaModeOnly();
                if (m_eMetaResult != META_SUCCESS)
                {
                    SyncUpdateMetaResultError();
                    SetEvent(Flash_Download_Event[i]);
                    return STATUS_FAIL;
                }
            }

        }
        break;

    case DN_WITH_BK_AND_RS_CAL_DATA:
    case DN_WITH_RS_CAL_DATA:
        m_eMetaResult = RestoreCalData();
        if (m_eMetaResult != META_SUCCESS)
        {
            SyncUpdateMetaResultError();
            SetEvent(Flash_Download_Event[i]);
            return STATUS_FAIL;
        }
        return SUCCESS_AND_GOON;

    case DN_WITH_UL_USER_DATA:
        if(IsUSBModeUploadUserDataAfterOneStationDownload())
        {
            m_eMetaResult = UploadUserData_ForOneStationDownloadViaUSB();
        }
        else
        {
            m_eMetaResult = UploadUserData();
        }
        if (m_eMetaResult != META_SUCCESS)
        {
            SyncUpdateMetaResultError();
            SetEvent(Flash_Download_Event[i]);
            return STATUS_FAIL;
        }
        SetEvent(Flash_Download_Event[i]);
       // SyncUpdateMetaResultOk();
        return SUCCESS_AND_GOON;

    default:
        break;
    }

    return SUCCESS_AND_GOON;
}


META_RESULT _fastcall TBOOT1::EnterMetaModeOnly(void)
{
    GC_TRACE("====== Tboot::EnterMetaModeOnly========");
    BOOT_RESULT boot_result;
    META_RESULT metaResult = Enter_META_Mode(boot_result,m_sDnParam.e_bbchip_type, m_sDnParam.e_ext_clock);

    prefix = "PW ";

    if (metaResult != META_SUCCESS)
    {
        return metaResult;
    }

    //
    metaResult = META_NVRAM_ResetToFactoryDefault_r(m_sDnParam.i_meta_handle, 40000);
    if (metaResult != META_SUCCESS)
    {
        SyncStopFactoryDefaultProgress();
        return metaResult;
    }

    m_asMsg = "Enter meta mode after download succesfully ";
    Synchronize(ShowMsg);
    SyncFinishFactoryDefaultProgress();


    return Exit_META_Mode();

}

E_ResultAndAction _fastcall TBOOT1::Format()
{
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    E_WAIT_FOR_USB_INSERT_STATUS E_Wait_USB_Insert_Status;

    //add by Changshun
    if(USB_COM == m_sDnParam.e_com_type  && IsUSBDownloadWithTwoSite())
    {
        if(is_have_meta_action_before_download())
        {
			E_Wait_USB_Insert_Status=WaitForUSBInsert(i);
			if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
			{
				return STATUS_FAIL;
			}
			WaitForComPortReadyAfterRegisterReady(m_sComPortSetting.com.number);
	  }
    }

    if (RESET_TO_FACTORY == m_sDnParam.e_format_op)
    {
        g_iStopFlag[i] = 0;

        m_eMetaResult = Reset_To_Factory_Default_Procedure(m_sDnParam.e_bbchip_type, m_sDnParam.e_ext_clock);
        if (m_eMetaResult != META_SUCCESS)
        {
            SyncUpdateMetaResultError();
            SetEvent(Flash_Download_Event[i]);
            return STATUS_FAIL;
        }

        if (m_sDnParam.e_backup_cal_data_op == DN_WITH_BK_AND_RS_CAL_DATA)
        {
            m_eMetaResult = RestoreCalData();
            if (m_eMetaResult == META_SUCCESS)
            {
                //SyncUpdateMetaResultOk();
            }
            else
            {
                SyncUpdateMetaResultError();
                SetEvent(Flash_Download_Event[i]);
		  return STATUS_FAIL;
            }
        }
        else
        {
            //SyncUpdateMetaResultOk();
        }

        //SetEvent(Flash_Download_Event[i]);
        return SUCCESS_AND_GOON;
    }
    else // manual format
    {
        //SyncStartFormat();
        // storage type
        switch(/*m_sDnParam.e_Operation*/ MainForm->Get_Operation())
        {
        case OPERATION_NFB:
            {
                m_sFmtArg.m_storage_type = HW_STORAGE_NAND;
                m_sFmtArg.m_format_cfg.m_format_begin_addr = m_sDnParam.s_nfb_param.ui_nand_fat_begin_addr;
                m_sFmtArg.m_format_cfg.m_format_length     = m_sDnParam.s_nfb_param.ui_nand_fat_length;
                m_sFmtArg.m_format_cfg.m_validation        = m_sDnParam.s_nfb_param.b_validation;
            }
            break;

        case OPERATION_NOR:
        default:
            {
                m_sFmtArg.m_storage_type = HW_STORAGE_NOR;
                m_sFmtArg.m_format_cfg.m_format_begin_addr = m_sDnParam.s_nor_param.ui_fat_begin_addr;
                m_sFmtArg.m_format_cfg.m_format_length     = m_sDnParam.s_nor_param.ui_fat_length;
                m_sFmtArg.m_format_cfg.m_validation        = m_sDnParam.s_nor_param.b_validation;
            }
        } // switch()

        // m_format_cfg
        //mingxue flash safe mode
		if(MainForm->FlashSafeMode->Checked==TRUE)
		{
			m_sFmtArg.m_nor_flash_erase_mode 			= NOR_FLASH_ERASE_SAFE_MODE;
		}
		else
		{
			m_sFmtArg.m_nor_flash_erase_mode			=NOR_FLASH_ERASE_FAST_MODE;
		}
		//end
        m_sFmtArg.m_format_cfg.m_auto_format_fat   = _FALSE;
        m_sFmtArg.m_erase_flag                     = NUTL_ERASE;
        m_sFmtArg.m_cb_format_report_init          = ::cb_format_report_init;
        m_sFmtArg.m_cb_format_report_init_arg      = this;
        m_sFmtArg.m_cb_format_report               = ::cb_format_report;
        m_sFmtArg.m_cb_format_report_arg           = this;
        m_sFmtArg.m_cb_format_statistics           = ::cb_format_statistics;
        m_sFmtArg.m_cb_format_statistics_arg       = this;

        if (m_sDnParam.e_backup_cal_data_op == DN_WITH_BK_AND_RS_CAL_DATA)
        {
            m_sFmtArg.m_enable_wdt_timeout      = _TRUE;
            m_sFmtArg.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
        }
	 else if (IsEnterMetaModeAfterDLMFT())
        {
            m_sFmtArg.m_enable_wdt_timeout      = _TRUE;
            m_sFmtArg.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
        }
        else
        {
            m_sFmtArg.m_enable_wdt_timeout      = _FALSE;
            m_sFmtArg.m_ms_wdt_timeout_interval = 0;
        }
        ret = FlashFormat(&m_sComPortSetting, &m_sFtArg, &m_sFtResult, &m_sFmtArg, &m_sFmtResult, &g_iStopFlag[i]);
        if (S_DONE != ret)
        {
            GC_TRACE("Tboot::Execute Format fail");
            SyncUpdateResultError();
            return STATUS_FAIL;
        }


	if(is_have_action_after_download())
	{
		if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
		{  //two station usb download

			E_Wait_USB_Insert_Status=WaitForUSBInsert(i);
			if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
			{
				return STATUS_FAIL;
			}
		}
		else if(USB_COM == m_sDnParam.e_com_type && !IsUSBDownloadWithTwoSite())
		{  //one station usb download
			m_sFtArg.m_boot_arg.m_usb_enable = _FALSE;
		}
	}


        /////meta action after format
        if(m_sDnParam.e_backup_cal_data_op == DN_WITHOUT_BK_AND_RS_CAL_DATA)
        {
            if(IsEnterMetaModeAfterDLMFT())
            {
                m_eMetaResult = EnterMetaModeOnly();
                if (m_eMetaResult != META_SUCCESS)
                {
                    SyncUpdateMetaResultError();
                    SetEvent(Flash_Download_Event[i]);
                    return STATUS_FAIL;
                }
            }
        }
        else if (m_sDnParam.e_backup_cal_data_op == DN_WITH_BK_AND_RS_CAL_DATA)
        {
            m_eMetaResult = RestoreCalData();
            if (m_eMetaResult == META_SUCCESS)
            {
                 //SyncUpdateMetaResultOk();
                 return SUCCESS_AND_GOON;
            }
            else
            {
                  SyncUpdateMetaResultError();
                  SetEvent(Flash_Download_Event[i]);
                  return STATUS_FAIL;
            }

            //SetEvent(Flash_Download_Event[i]);

        }


    } // manual or auto format()

    return SUCCESS_AND_GOON;
}


bool __fastcall TBOOT1::is_roms_include_bootloader(ROM_INFO *p_rom_info,
                                                   int rom_count)
{
    for (int i=0; i<rom_count; i++)
    {
        if (   strcmpi(p_rom_info[i].name, "BOOTLOADER") == 0
            || strcmpi(p_rom_info[i].name, "ExtBootLoader") == 0)
        {
            return true;
        }
    }

    return false;
}

E_USB_Download_Support_Status  __fastcall TBOOT1::Is_Support_BROM_USB_DL()
{
	E_USB_Download_Support_Status USB_Download_Status=USB_DOWNLOAD_SUPPORT_NONE;
	DL_HANDLE_T dl_handle=NULL;
	//Modified by dongguo for debug on Feb 24
	//DL_INFO dl_info;
	DL_INFO_EX dl_info;
	memset(&dl_info,0x00,sizeof(DL_INFO));

	if(NULL!=m_sFtDlArg.m_dl_handle)
	{
		dl_handle=m_sFtDlArg.m_dl_handle;
	}
	else if(NULL!=m_sFtDlArg.m_dl_handle_list)
	{
	    if(S_DONE!=DL_GetHandle(m_sFtDlArg.m_dl_handle_list,0,&dl_handle))
		  {
			    return USB_Download_Status;
		  }
	}
	else
	{
		  return USB_Download_Status;
	}

	//DL_GetInfo(dl_handle, &dl_info);
  DL_GetInfo_Ex(dl_handle, &dl_info);

//	if(dl_info.m_config.m_brom_usb_supported)
//	{
//		USB_Download_Status=BROM_USB_DOWNLOAD_SUPPORT;
//	}
//	else if(dl_info.m_config.m_bootloader_usb_supported)
//	{
//		USB_Download_Status=USB_DOWNLOAD_SUPPORT;
//	}

	if(dl_info.brom_usb_supported)
	{
		USB_Download_Status=BROM_USB_DOWNLOAD_SUPPORT;
	}
	else if(dl_info.bootloader_usb_supported)
	{
		USB_Download_Status=USB_DOWNLOAD_SUPPORT;
	}

	return USB_Download_Status;
}

#if 0
bool __fastcall TBOOT1::Unload_all_rom_except_bootloader()
{
    DL_HANDLE_T *p_dl_handle;
    unsigned short rom_count;

    for(int i=0; i<MAX_SUPPORT_LOAD_NUM; i++)
    {
        p_dl_handle = MainForm->Get_DlHandle(i);

        if(NULL == p_dl_handle)
        {
            continue;
        }

        if(S_DONE == DL_GetCount(*p_dl_handle, &rom_count))
        {
            ROM_INFO	 rom_info[MAX_LOAD_SECTIONS];

            if(S_DONE == DL_Rom_GetInfoAll(*p_dl_handle, rom_info, MAX_LOAD_SECTIONS))
            {
                //if(!is_roms_include_bootloader(rom_info, rom_count))
                //{
                //  continue;
                //}

                for (int i=0; i<rom_count; i++)
                {
                    if (   strcmpi(rom_info[i].name, "BOOTLOADER") == 0
                        || strcmpi(rom_info[i].name, "ExtBootLoader") == 0)
                    {
                        //Do nothing, download
                    }
                    else
                    {
                        DL_Rom_SetEnableAttr(*p_dl_handle, i, _FALSE);
                    }
                }
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }
    }

    return true;
}
#endif


#if 0
bool __fastcall TBOOT1::Load_all_rom_except_bootloader()
{
    DL_HANDLE_T *p_dl_handle;
    unsigned short rom_count;

    for(int i=0; i<MAX_SUPPORT_LOAD_NUM; i++)
    {
        p_dl_handle = MainForm->Get_DlHandle(i);

        if(NULL == p_dl_handle)
        {
            continue;
        }

        if(S_DONE == DL_GetCount(*p_dl_handle, &rom_count))
        {
            ROM_INFO	 rom_info[MAX_LOAD_SECTIONS];

            if(S_DONE == DL_Rom_GetInfoAll(*p_dl_handle, rom_info, MAX_LOAD_SECTIONS))
            {
                //if(!is_roms_include_bootloader(rom_info, rom_count))
                //{
                //   continue;
                //}

                for (int i=0; i<rom_count; i++)
                {
                    if (   strcmpi(rom_info[i].name, "BOOTLOADER") == 0
                        || strcmpi(rom_info[i].name, "ExtBootLoader") == 0)
                    {
                        //Do nothing, download
                    }
                    else
                    {
                        DL_Rom_SetEnableAttr(*p_dl_handle, i, _TRUE);
                    }
                }
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }
    }

    return true;
}
#endif

bool __fastcall TBOOT1::Load_all_bootloader()
{
    DL_HANDLE_T *p_dl_handle;

    try
    {
        for(int i=0; i<MAX_SUPPORT_LOAD_NUM; i++)
        {
            p_dl_handle = MainForm->Get_DlHandle(i);

            if(NULL != p_dl_handle)
            {
                if(S_DONE != DL_BL_SetEnableAttr(*p_dl_handle, _TRUE))
                {
                    return false;
                }
                else
                {
                    //Success? that's good, go on
                }
            }
        }
    }
    catch(...)
    {
        GC_TRACE("Load_all_bootloader unexception.");
    }

    return true;
}

bool __fastcall TBOOT1::Unload_all_bootloader()
{
    DL_HANDLE_T *p_dl_handle;

    try
    {
        for(int i=0; i<MAX_SUPPORT_LOAD_NUM; i++)
        {
            p_dl_handle = MainForm->Get_DlHandle(i);

            if(p_dl_handle != NULL)
            {
                if(S_DONE != DL_BL_SetEnableAttr(*p_dl_handle, _FALSE))
                {
                    return false;
                }
                else
                {
                    //Success? that's good, go on
                }
            }

        }
    }
    catch(...)
    {
        GC_TRACE("Unload_all_bootloader unexception.");
    }


    //frmMultiLoad->Disable_BL();

    return true;
}

int TBOOT1::get_new_created_com_port()
{
	std::set<int>		current_exist_com_port;
	std::vector<int>	result_port(255);
	std::vector<int>::iterator	it_last_result;

	//Get current exist com port
	scan_exist_com_port(current_exist_com_port);

	it_last_result = set_difference(current_exist_com_port.begin(), current_exist_com_port.end(),
		m_exist_com_port.begin(), m_exist_com_port.end(),
		result_port.begin());

	if(result_port.begin() == it_last_result)
	{
		return false;
	}

	return *result_port.begin();
}


void TBOOT1::scan_exist_com_port(std::set<int>  &exist_com_ports /*out*/)
{
    HANDLE     h_Com;
    char strCom[64];
    char log[128];

    //Insert now using com port
    exist_com_ports.insert(m_sComPortSetting.com.number);

    for(int nCom = 3; nCom<256; nCom++)
    {
        sprintf(strCom, "\\\\.\\COM%d", nCom);

        h_Com = CreateFile(strCom, GENERIC_READ | GENERIC_WRITE,
            0, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        if(INVALID_HANDLE_VALUE == h_Com)
        {
            continue;
        }

        if(m_sComPortSetting.com.number == nCom)
        {
            CloseHandle(h_Com);
            continue;
        }

        GC_TRACE("scan_exist_com_port ==> Find com port %d", nCom);
        exist_com_ports.insert(nCom);

        CloseHandle(h_Com);
    }
}

//DL_ROM_Download --> DL_BootLoader
int __fastcall TBOOT1::DL_BootLoader(FLASHTOOL_API_HANDLE_T &ft_api_handle)
{

    FlashTool_Download_Result  dl_result;
    FlashTool_Download_Arg     dl_arg;

	memset(&dl_arg,0x00,sizeof(dl_arg));
	memset(&dl_result,0x00,sizeof(dl_result));

    //dl_arg.m_dl_handle       = m_sFtDlArg.m_dl_handle;
    dl_arg.m_dl_handle = NULL;
    dl_arg.m_dl_handle_list  = g_DL_HANDLE_LIST; //m_sFtDlArg.m_dl_handle_list;

    dl_arg.m_cb_da_report        = NULL;
    dl_arg.m_cb_da_report_arg    = NULL;

    dl_arg.m_download_accuracy   =   m_sFtDlArg.m_download_accuracy;
    dl_arg.m_cb_download_flash_init =  m_sFtDlArg.m_cb_download_flash_init;
    dl_arg.m_cb_download_flash_init_arg =  m_sFtDlArg.m_cb_download_flash_init_arg;
    dl_arg.m_cb_download_flash         =   m_sFtDlArg.m_cb_download_flash;
    dl_arg.m_cb_download_flash_arg     = m_sFtDlArg.m_cb_download_flash_arg;

    dl_arg.m_cb_download_bloader_init     = m_sFtDlArg.m_cb_download_bloader_init;
    dl_arg.m_cb_download_bloader_init_arg = m_sFtDlArg.m_cb_download_bloader_init_arg;
    dl_arg.m_cb_download_bloader          = m_sFtDlArg.m_cb_download_bloader;
    dl_arg.m_cb_download_bloader_arg      = m_sFtDlArg.m_cb_download_bloader_arg;
    dl_arg.m_cb_security_post_process_notify = m_sFtDlArg.m_cb_security_post_process_notify;
    dl_arg.m_cb_security_post_process_notify_arg = m_sFtDlArg.m_cb_security_post_process_notify_arg;

    dl_arg.m_enable_tgt_res_layout_check   = _TRUE;
    dl_arg.m_enable_bbchip_ver_check       = _TRUE;
    dl_arg.m_downloadstyle_sequential      = _TRUE;
	//Must do it~
	dl_arg.m_enable_ui_dram_cfg= _FALSE;


    if (dl_arg.m_dl_handle != NULL)
    {
        DL_HANDLE_T dl_handle = NULL;

        DL_Clone(&dl_handle, dl_arg.m_dl_handle);
        DisableROM(dl_handle);
        dl_arg.m_dl_handle = dl_handle;
    }
    else if (dl_arg.m_dl_handle_list != NULL)
    {
        DL_HANDLE_LIST_T dl_handle_list = NULL;

        DL_CloneList(&dl_handle_list, dl_arg.m_dl_handle_list);
        DisableROM(dl_handle_list);
        dl_arg.m_dl_handle_list = dl_handle_list;
    }
    else
    {
        //assert(0);
        return 1;
    }

    int ret = FlashTool_Download(ft_api_handle, &dl_arg, &dl_result);

    //
    // Destroy the copy
    //
    if (dl_arg.m_dl_handle != NULL)
    {
        DL_Destroy(& (dl_arg.m_dl_handle) );
    }
    else if (dl_arg.m_dl_handle_list != NULL)
    {
        DL_DestroyList(& (dl_arg.m_dl_handle_list) );
    }
    else
    {
        // assert(0);
        return 1;
    }

    return ret;
}

void _fastcall TBOOT1::Boot_Arg_Setting(BOOT_FLASHTOOL_ARG	&boot_arg,_BOOL isUSBMode)
{
    boot_arg.m_bbchip_type = m_sDnParam.e_bbchip_type;
    boot_arg.m_ext_clock = AUTO_DETECT_EXT_CLOCK; //m_sDnParam.e_ext_clock;
    boot_arg.m_ms_boot_timeout = BOOT_INFINITE;
    boot_arg.m_max_start_cmd_retry_count = DEFAULT_BROM_START_CMD_RETRY_COUNT;
    boot_arg.m_p_bank0_mem_cfg = m_sDnParam.s_emi_param.b_bank0_auto?NULL:&(m_sDnParam.s_emi_param.ui_bank0_cfg);
    boot_arg.m_p_bank1_mem_cfg = m_sDnParam.s_emi_param.b_bank1_auto?NULL:&(m_sDnParam.s_emi_param.ui_bank1_cfg);
    boot_arg.m_da_handle = g_DA_HANDLE;
    boot_arg.m_cb_download_da_init = ::cb_download_da_init;
    boot_arg.m_cb_download_da_init_arg = this;
    boot_arg.m_cb_download_da = ::cb_download_da;
    boot_arg.m_cb_download_da_arg = this;

    boot_arg.m_cb_in_brom_stage = ::cb_in_brom_stage;
    boot_arg.m_cb_in_brom_stage_arg = this;
    boot_arg.m_speedup_brom_baudrate = _TRUE;

    // WM_BROM_READY_TO_POWER_ON_TGT
    boot_arg.m_ready_power_on_wnd_handle	= NULL;
    boot_arg.m_ready_power_on_wparam		= NULL;
    boot_arg.m_ready_power_on_lparam		= NULL;

    // serial link authentication arg
    boot_arg.m_auth_handle              = g_AUTH_HANDLE_Loaded ? g_AUTH_HANDLE : NULL;//g_AUTH_HANDLE;mingxue2012-12-12
    boot_arg.m_cb_sla_challenge         = SLA_Challenge;
    boot_arg.m_cb_sla_challenge_arg     = this;
    boot_arg.m_cb_sla_challenge_end     = SLA_Challenge_END;
    boot_arg.m_cb_sla_challenge_end_arg = this;

    // EDGE card
    boot_arg.m_cb_com_init_stage = ::cb_PowerOnOxford;
    boot_arg.m_cb_com_init_stage_arg = this;

    // EMI Control for bank0 and bank1
    boot_arg.m_p_bank0_mem_cfg            = NULL;
    boot_arg.m_p_bank1_mem_cfg            = NULL;

    boot_arg.m_usb_enable = isUSBMode;
	boot_arg.m_enable_usb_2_0 =MainForm->m_bEnableUSB1_1To2_0;//huifen;

    memcpy(boot_arg.m_external_memory_setting,
            m_sFtArg.m_boot_arg.m_external_memory_setting,
            sizeof(boot_arg.m_external_memory_setting));

}

//==============================================================================
int __fastcall TBOOT1::DL_Connect(FLASHTOOL_API_HANDLE_T &ft_api_handle,_BOOL isUSBMode,unsigned char com_port)
{
    int ret;
    int index = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

    FlashTool_Connect_Result   ft_connect_result;
    FlashTool_Connect_Arg      ft_connect_arg;

    memset(&ft_connect_result,0x00,sizeof(ft_connect_result));
    memset(&ft_connect_arg,0x00,sizeof(ft_connect_arg));

    /* set FlashTool_Connect_Arg */
    ft_connect_arg.m_com_ms_read_timeout  =  COM_DEFAULT_TIMEOUT;
    ft_connect_arg.m_com_ms_write_timeout =  COM_DEFAULT_TIMEOUT;
    Boot_Arg_Setting(ft_connect_arg.m_boot_arg,isUSBMode);
    ft_connect_arg.m_cb_security_pre_process_notify = NULL;
    ft_connect_arg.m_cb_security_pre_process_notify_arg = NULL;
    ft_connect_arg.m_nor_chip_select[0] = CS0;
    ft_connect_arg.m_nor_chip_select[1] = CS_WITH_DECODER;
    ft_connect_arg.m_nand_chip_select   = m_sDnParam.s_bbchip_op.b_enable_nfi_cs1?CS1:CS0;
    ft_connect_arg.m_p_nand_acccon      = NULL  ;


    /* connect to target */
    ret = FlashTool_Connect(com_port,
        &ft_connect_arg,
        &ft_connect_result,
        &g_iStopFlag[index],
        &ft_api_handle);
    if(S_DONE != ret)
    {
        return ret;
    }
    /*
    ///enable sram and dram
    GC_TRACE("Enable SRAM");
    FlashTool_EnableSRAM_Result sram_result;
    ret = FlashTool_EnableSRAM(ft_api_handle, &sram_result);
    if(S_DONE != ret)
    {
    return ret;
    }

      GC_TRACE("Enable DRAM");
      FlashTool_EnableDRAM_Result dram_result;
      DRAM_SETTING  dram_setting;

        ret = FlashTool_EnableDRAM(ft_api_handle, dram_setting, &dram_result);
        if(S_DONE != ret)
        {
        return ret;
        }
        ///
    */
    return ret;

}

//==============================================================================
int __fastcall TBOOT1::DL_Change_Baudrate(FLASHTOOL_API_HANDLE_T &ft_api_handle)
{
    FlashTool_ChangeBaudrate_Arg  ft_cb_arg;

    ft_cb_arg.m_baudrate                       = MainForm->Get_Baudrate();
    ft_cb_arg.m_baudrate_full_sync_count       = 1;
    ft_cb_arg.m_cb_set_high_speed_baudrate     = NULL;
    ft_cb_arg.m_cb_set_high_speed_baudrate_arg = NULL;

    return FlashTool_ChangeBaudrate(ft_api_handle, &ft_cb_arg);
}


//==============================================================================
int __fastcall TBOOT1::DL_Enable_WatchDogTimeout(FLASHTOOL_API_HANDLE_T &ft_api_handle)
{
    return FlashTool_EnableWatchDogTimeout(ft_api_handle, 1000);
}

int __fastcall TBOOT1::DisableBootloader(DL_HANDLE_T &dl_handle)
{
	int ret;
  DL_INFO dl_info;
  DL_GetInfo(dl_handle, &dl_info);
   unsigned short romNum = 0;
 //  DL_INFO_EX dl_info = {};
  // DL_GetInfo_Ex(dl_handle, &dl_info);
    if (dl_info.m_config.m_is_nfb)
    {
      /*  if( (S_DONE == DL_GetCount_Ex(dl_handle, &romNum) ) && (0 < romNum) )
            {

                for(int i = 0; i < romNum; i++)
                {
                    ROM_INFO_EX romInfoEx = {};
                    if(S_DONE == DL_Rom_GetInfo_Ex(dl_handle, i, &romInfoEx) )
                    {
                        if( ARM_BL_ROM == romInfoEx.rom_type)
                    {
                            DL_Rom_SetEnableAttr_Ex(dl_handle, i, _FALSE);
                        }
                        else if(EXT_BL_ROM == romInfoEx.rom_type &&
                                !dl_info.m_config.m_bootloader_self_update_supported)
                        {
                            DL_Rom_SetEnableAttr_Ex(dl_handle, i, _FALSE);
                        }
                    }
                }
            } */
        if(S_DONE!=(ret=DL_BL_SetEnableAttr(dl_handle, _FALSE)))
        {
			       return ret;
		    }
    }
    else
    {
        ROM_INFO rom_info;

        if ((DL_Rom_GetInfo(dl_handle, 0, &rom_info) == S_DONE) &&
            (strcmp(rom_info.name, "BOOTLOADER") == 0))
        {
            if(S_DONE!=(ret=DL_Rom_SetEnableAttr(dl_handle, 0, _FALSE)))
            {
				return ret;
			}
        }
    }
	return S_DONE;
}

int __fastcall TBOOT1::DisableBootloader(DL_HANDLE_LIST_T &dl_handle_list)
{
	int handle_count = 0;
	int ret;

	if(S_DONE!=(ret=DL_GetHandleNumber(dl_handle_list, &handle_count)))
	{
		return ret;
	}

	for (int handle_index=0; handle_index<handle_count; ++handle_index)
	{
	    DL_HANDLE_T dl_handle = NULL;

	    if(S_DONE!=(ret=DL_GetHandle(dl_handle_list, handle_index, &dl_handle)))
	    {
			return ret;
		}
	    if(S_DONE!=(ret=DisableBootloader(dl_handle)))
	    {
			return ret;
		}
	}
	return S_DONE;
}
void __fastcall TBOOT1::DisableROM(DL_HANDLE_T &dl_handle)
{
    DL_INFO dl_info;
    DL_GetInfo(dl_handle, &dl_info);

    unsigned short rom_count = 0;
    DL_GetCount(dl_handle, &rom_count);

    if (dl_info.m_config.m_is_nfb)
    {
        for (int rom_index=0; rom_index<rom_count; ++rom_index)
        {
            DL_Rom_SetEnableAttr(dl_handle, rom_index, _FALSE);
        }
    }
    else
    {
        for (int rom_index=0; rom_index<rom_count; ++rom_index)
        {
            if (rom_index == 0)
            {
                ROM_INFO rom_info;

                if ((DL_Rom_GetInfo(dl_handle, 0, &rom_info) == S_DONE) &&
                    (strcmp(rom_info.name, "BOOTLOADER") != 0))
                {
                    DL_Rom_SetEnableAttr(dl_handle, 0, _FALSE);
                }
            }
            else
            {
                DL_Rom_SetEnableAttr(dl_handle, rom_index, _FALSE);
            }
        }
    }
}
void __fastcall TBOOT1::DisableROM(DL_HANDLE_LIST_T &dl_handle_list)
{
    int handle_count = 0;
    DL_GetHandleNumber(dl_handle_list, &handle_count);

    for (int handle_index=0; handle_index<handle_count; ++handle_index)
    {
        DL_HANDLE_T dl_handle = NULL;

        DL_GetHandle(dl_handle_list, handle_index, &dl_handle);
        DisableROM(dl_handle);
    }
}




int __fastcall TBOOT1::FlashDownload_OnlyROM(COM_PORT_SETTING *p_com_setting,
                                             const FLASHTOOL_ARG *p_arg,
                                             FLASHTOOL_RESULT *p_result,
                                             FLASHTOOL_DOWNLOAD_ARG *p_dl_arg,
                                             FLASHTOOL_DOWNLOAD_RESULT *p_dl_result,
                                             int *p_stopflag)
{
    //
    // Make a copy of the original DL handle (list), disable all the copy's
    // bootloader entries, and invoke download API with this modified copy
    //
    int ret =0;
    DL_HANDLE_T backup_handle = NULL;
    DL_HANDLE_LIST_T backup_handle_list = NULL;


    if (p_dl_arg->m_dl_handle != NULL)
    {
        DL_HANDLE_T dl_handle = NULL;

        if(S_DONE!=(ret=DL_Clone(&dl_handle, p_dl_arg->m_dl_handle)))
        {
			return ret;
		}

		if(S_DONE!=(ret=DisableBootloader(dl_handle)))
		{
			return ret;
		}
        backup_handle = p_dl_arg->m_dl_handle ;
        p_dl_arg->m_dl_handle = dl_handle;
    }
    else if (p_dl_arg->m_dl_handle_list != NULL)
    {
		DL_HANDLE_LIST_T dl_handle_list = NULL;

		if(S_DONE!=(ret=DL_CloneList(&dl_handle_list, p_dl_arg->m_dl_handle_list)))
		{
			return ret;
		}
		if(S_DONE!=(ret=DisableBootloader(dl_handle_list)))
		{
			return ret;
		}
        backup_handle_list = p_dl_arg->m_dl_handle_list;
		p_dl_arg->m_dl_handle_list = dl_handle_list;
    }
    else
    {
        // assert(0);
        return S_STOP;
    }
//    WaitForComPortReadyAfterRegisterReady(p_com_setting->com.number);

    ret = FlashDownload(p_com_setting, p_arg, p_result, p_dl_arg, p_dl_result, p_stopflag);

    if (p_dl_arg->m_dl_handle != NULL)
    {
        DL_Destroy(&p_dl_arg->m_dl_handle);

        p_dl_arg->m_dl_handle = backup_handle;
    }
    else if (p_dl_arg->m_dl_handle_list != NULL)
    {
        DL_DestroyList(&p_dl_arg->m_dl_handle_list);

        p_dl_arg->m_dl_handle_list = backup_handle_list ;
    }

    return ret;
}
//==============================================================================
int __fastcall TBOOT1::FlashDownload_OnlyROM_ForUploadUserDataViaUSB(
	      COM_PORT_SETTING *p_com_setting,
          const FLASHTOOL_ARG *p_arg,
          FLASHTOOL_RESULT *p_result,
          FLASHTOOL_DOWNLOAD_ARG *p_dl_arg,
          FLASHTOOL_DOWNLOAD_RESULT *p_dl_result,
          int *p_stopflag)
{
    //
    // Make a copy of the original DL handle (list), disable all the copy's
    // bootloader entries, and invoke download API with this modified copy
    //
    int ret =0;
    DL_HANDLE_T backup_handle = NULL;
    DL_HANDLE_LIST_T backup_handle_list = NULL;
    FLASHTOOL_API_HANDLE_T flashtool_api_handle = NULL;
	int index = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    FlashTool_Download_Result  dl_result;
    FlashTool_Download_Arg     dl_arg;

    FlashTool_Format_Arg_Ex format_arg;
    FlashTool_Format_Result format_result;

    //dl_arg.m_dl_handle       = m_sFtDlArg.m_dl_handle;
    dl_arg.m_dl_handle = NULL;
    dl_arg.m_dl_handle_list  = g_DL_HANDLE_LIST; //m_sFtDlArg.m_dl_handle_list;

    dl_arg.m_cb_da_report        = NULL;
    dl_arg.m_cb_da_report_arg    = NULL;

    dl_arg.m_download_accuracy   =   m_sFtDlArg.m_download_accuracy;
    dl_arg.m_cb_download_flash_init =  m_sFtDlArg.m_cb_download_flash_init;
    dl_arg.m_cb_download_flash_init_arg =  m_sFtDlArg.m_cb_download_flash_init_arg;
    dl_arg.m_cb_download_flash         =   m_sFtDlArg.m_cb_download_flash;
    dl_arg.m_cb_download_flash_arg     = m_sFtDlArg.m_cb_download_flash_arg;

    dl_arg.m_cb_download_bloader_init     = m_sFtDlArg.m_cb_download_bloader_init;
    dl_arg.m_cb_download_bloader_init_arg = m_sFtDlArg.m_cb_download_bloader_init_arg;
    dl_arg.m_cb_download_bloader          = m_sFtDlArg.m_cb_download_bloader;
    dl_arg.m_cb_download_bloader_arg      = m_sFtDlArg.m_cb_download_bloader_arg;
    dl_arg.m_cb_security_post_process_notify = m_sFtDlArg.m_cb_security_post_process_notify;
    dl_arg.m_cb_security_post_process_notify_arg = m_sFtDlArg.m_cb_security_post_process_notify_arg;

    dl_arg.m_enable_tgt_res_layout_check   = _TRUE;
    dl_arg.m_enable_bbchip_ver_check       = _TRUE;
    dl_arg.m_downloadstyle_sequential      = _TRUE;
	//Must do it~
	dl_arg.m_enable_ui_dram_cfg= _FALSE;

    format_arg.m_cb_format_report_init = p_dl_arg->m_cb_format_report_init;
    format_arg.m_cb_format_report_init_arg = p_dl_arg->m_cb_format_report_init_arg;
    format_arg.m_cb_format_report = p_dl_arg->m_cb_format_report;
    format_arg.m_cb_format_report_arg = p_dl_arg->m_cb_format_report_arg;
    format_arg.m_cb_format_statistics = p_dl_arg->m_cb_format_statistics;
    format_arg.m_cb_format_statistics_arg = p_dl_arg->m_cb_format_statistics_arg;
    //for MT6276M Format FAT Only...
    format_arg.m_format_cfg.formatAction.type = FAT_FORMAT;
    format_arg.m_format_cfg.storageType = HW_STORAGE_NAND;
    format_arg.m_format_cfg.validation = _FALSE;

    try
   {

    if (dl_arg.m_dl_handle != NULL)
    {
        DL_HANDLE_T dl_handle = NULL;

        if(S_DONE!=(ret=DL_Clone(&dl_handle, dl_arg.m_dl_handle)))
        {
			return ret;
		}

		if(S_DONE!=(ret=DisableBootloader(dl_handle)))
		{
			return ret;
		}
        backup_handle = dl_arg.m_dl_handle ;
        dl_arg.m_dl_handle = dl_handle;
    }
    else if (dl_arg.m_dl_handle_list != NULL)
    {
		DL_HANDLE_LIST_T dl_handle_list = NULL;

		if(S_DONE!=(ret=DL_CloneList(&dl_handle_list, dl_arg.m_dl_handle_list)))
		{
			return ret;
		}
		if(S_DONE!=(ret=DisableBootloader(dl_handle_list)))
		{
			return ret;
		}
        backup_handle_list = dl_arg.m_dl_handle_list;
		dl_arg.m_dl_handle_list = dl_handle_list;
    }
    else
    {
        // assert(0);
        return S_STOP;
    }
//    WaitForComPortReadyAfterRegisterReady(p_com_setting->com.number);

    //ret = FlashDownload(p_com_setting, p_arg, p_result, p_dl_arg, p_dl_result, p_stopflag);

    if(S_DONE !=( ret = DL_Connect(flashtool_api_handle,_TRUE,p_com_setting->com.number)))
    {
    /*
      if(critical_section_manager.is_in_critic_process(this))
      {
          critical_section_manager.leave_critic_usb_dl(this);
      }
    */
      FlashTool_Disconnect(&flashtool_api_handle);
      return ret;
    }

    if(S_DONE !=( ret = FlashTool_Download(flashtool_api_handle,&dl_arg,&dl_result)))
    {
    /*
      if(critical_section_manager.is_in_critic_process(this))
      {
          critical_section_manager.leave_critic_usb_dl(this);
      }
    */
      FlashTool_Disconnect(&flashtool_api_handle);
      return ret;
    }


    if( _TRUE == p_dl_arg->m_format_enable)
    {
      if(S_DONE !=( ret = FlashTool_Format_Ex(flashtool_api_handle,
                                                &format_arg,
                                                &format_result)))
      {
        FlashTool_Disconnect(&flashtool_api_handle);
        return ret;
      }
    }

  {//Enter Critical Section
      do
      {
          if(BOOT_STOP == g_iStopFlag[index])
          {
              return false;
          }

          if(critical_section_manager.can_entry_critic_usb_dl(this))
          {
              break;
          }

          Sleep(500);

      }while(1);

      Sleep(1000);

      scan_exist_com_port(m_exist_com_port);

      GC_TRACE_EX("Enable Watch Dog...");
      ret  = DL_Enable_WatchDogTimeout(flashtool_api_handle);
      if(S_DONE != ret)
      {
          FlashTool_Disconnect(&flashtool_api_handle);
          if(critical_section_manager.is_in_critic_process(this))
          {
              critical_section_manager.leave_critic_usb_dl(this);
          }
          return ret;
      }
  }
    //Critical Section Handle

      ret = FlashTool_Disconnect(&flashtool_api_handle);

    if (dl_arg.m_dl_handle != NULL)
    {
        DL_Destroy(&dl_arg.m_dl_handle);

        dl_arg.m_dl_handle = backup_handle;
    }
    else if (dl_arg.m_dl_handle_list != NULL)
    {
        DL_DestroyList(&dl_arg.m_dl_handle_list);

        dl_arg.m_dl_handle_list = backup_handle_list ;
    }

    return ret;
  }
  catch(...)
  {
    if(critical_section_manager.is_in_critic_process(this))
    {
        critical_section_manager.leave_critic_usb_dl(this);
    }

    return -1;
  }
}

//==============================================================================
//DL_ROM --> uart_download_bootloader() for meaningful
int __fastcall TBOOT1::uart_download_bootloader()
{
    int ret=0;
    FLASHTOOL_API_HANDLE_T     ft_api_handle;
    int index = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    bool is_connect_OK = false;

    try
    {
        GC_TRACE("====== Tboot::uart_download_bootloader: Begin DL_Connect ===");
        ret  = DL_Connect(ft_api_handle,_FALSE,index + m_sDnParam.i_FirstComNo);
        if(S_DONE != ret)
        {
            goto clean;
        }

        is_connect_OK = true;

        ret  = DL_Change_Baudrate(ft_api_handle);
        if(S_DONE != ret)
        {
            FlashTool_Disconnect(&ft_api_handle);
            goto clean;
        }

        //this block is modified On May 25
      {
        GC_TRACE("====== Tboot::uart_download_bootloader:  Begin DL_BootLoader ===");
        ret  = DL_BootLoader(ft_api_handle);
        GC_TRACE("====== Tboot::uart_download_bootloader:  Finish DL_BootLoader : %d===",ret);
        if(S_DONE != ret)
        {
            FlashTool_Disconnect(&ft_api_handle);
            if(critical_section_manager.is_in_critic_process(this))
            {
                critical_section_manager.leave_critic_usb_dl(this);
            }
            goto clean;
        }
      }
        GC_TRACE_EX("Waiting for enter critical section...");
        do
        {
            if(BOOT_STOP == g_iStopFlag[index])
            {
                return false;
            }

            if(critical_section_manager.can_entry_critic_usb_dl(this))
            {
                break;
            }

            Sleep(500);

        }while(1);

        GC_TRACE_EX("Enter Critical Section===>");
        Sleep(1000);

        scan_exist_com_port(m_exist_com_port);

        ret  = DL_Enable_WatchDogTimeout(ft_api_handle);
        if(S_DONE != ret)
        {
            FlashTool_Disconnect(&ft_api_handle);
            if(critical_section_manager.is_in_critic_process(this))
            {
                critical_section_manager.leave_critic_usb_dl(this);
            }
            goto clean;
        }

        ret = FlashTool_Disconnect(&ft_api_handle);
        if(S_DONE != ret)
        {
            if(critical_section_manager.is_in_critic_process(this))
            {
                critical_section_manager.leave_critic_usb_dl(this);
            }
            goto clean;
        }
    }
    catch(...)
    {
        if(is_connect_OK)
        {
            FlashTool_Disconnect(&ft_api_handle);
        }

        if(critical_section_manager.is_in_critic_process(this))
        {
            critical_section_manager.leave_critic_usb_dl(this);
        }

        return -1;
    }

clean:

    return ret;
}



bool __fastcall TBOOT1::Download_bootloader_for_usb_download()
{
    //    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

    try
    {
        m_sFtDlArg.m_enable_wdt_timeout = _TRUE;
        m_sFtDlArg.m_ms_wdt_timeout_interval = 1000;

        //Use uart to download bootloader, then usb download ability should be disabled
        m_sFtArg.m_boot_arg.m_usb_enable = _FALSE;

        m_exist_com_port.clear();

        ret = uart_download_bootloader();

        return (ret == S_DONE);
    }
    catch(...)
    {
        if(critical_section_manager.is_in_critic_process(this))
        {
            critical_section_manager.leave_critic_usb_dl(this);
        }
    }
    return false;//for clear compile warning

}

bool __fastcall TBOOT1::Download_rom_for_usb_download()
{
    COM_PORT_SETTING temp_com_setting;
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    time_t	 start, finish;
    GC_TRACE_EX("critical_section_manager:0x%08X",&critical_section_manager);

	try
	{
    GC_TRACE("====== Tboot::download_rom_for _usb_download ===");
    //Load_all_rom_except_bootloader();
    //Unload_all_bootloader();

    ///// for usb bk and rs
    //if need meta action after download, must set the flag for restart the target
    if (m_sDnParam.e_backup_cal_data_op != DN_WITHOUT_BK_AND_RS_CAL_DATA)
    {
        m_sFtDlArg.m_enable_wdt_timeout 	 = _TRUE;
        m_sFtDlArg.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
    }
    else if(RESET_TO_FACTORY == m_sDnParam.e_format_op)
    {
        m_sFtDlArg.m_enable_wdt_timeout = _TRUE;
        m_sFtDlArg.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
    }
    else if( IsEnterMetaModeAfterDLMFT() ) //enter meta mode
    {
        m_sFtDlArg.m_enable_wdt_timeout = _TRUE;
        m_sFtDlArg.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
    }
    else
    {
        m_sFtDlArg.m_enable_wdt_timeout 	 = _FALSE;
        m_sFtDlArg.m_ms_wdt_timeout_interval = 0;
    }
		//m_sFtDlArg.m_enable_wdt_timeout = _FALSE;
		//m_sFtDlArg.m_ms_wdt_timeout_interval = 1000;
		//////

		//USB DL ROM
		m_sFtArg.m_boot_arg.m_usb_enable = _TRUE;

		m_sFtDlArg.m_dl_handle_list 					 = g_DL_HANDLE_LIST;
		m_sFtDlArg.m_dl_handle							 = NULL;

		temp_com_setting  = m_sComPortSetting;

		//Get start time
		time(&start);

    do
    {
        if(BOOT_STOP == g_iStopFlag[i])
        {
            if(critical_section_manager.is_in_critic_process(this))
            {
                critical_section_manager.leave_critic_usb_dl(this);
            }
				    ret = S_STOP;
				    return false;
        }

        temp_com_setting.com.number = get_new_created_com_port();

        if(temp_com_setting.com.number != 0)
        {
            //find usb_com port
				    break;
        }

        //Get current time
        time( &finish );

        //wait 10s if there still not found a new usb com port
        //then we quite
        if(difftime( finish, start ) > 30 /* 30s */)
        {
            if(critical_section_manager.is_in_critic_process(this))
            {
                critical_section_manager.leave_critic_usb_dl(this);
            }
            ret = S_COM_PORT_OPEN_FAIL;
            return false;
        }
		}while(1);

		if(critical_section_manager.is_in_critic_process(this))
		{
			critical_section_manager.leave_critic_usb_dl(this);
		}

		GC_TRACE("====== Tboot::temp_com_setting %d===", temp_com_setting.com.number);

		//ret = FlashDownload(&temp_com_setting, &m_sFtArg, &m_sFtResult,
		//					   &m_sFtDlArg, &m_sFtDnResult, &g_iStopFlag[i]);
		if(IsUSBModeUploadUserDataAfterOneStationDownload())
    {
        ret = FlashDownload_OnlyROM_ForUploadUserDataViaUSB(&temp_com_setting, &m_sFtArg, &m_sFtResult,
          			&m_sFtDlArg, &m_sFtDnResult, &g_iStopFlag[i]);
    }
    else
    {
        ret = FlashDownload_OnlyROM(&temp_com_setting, &m_sFtArg, &m_sFtResult,
          			&m_sFtDlArg, &m_sFtDnResult, &g_iStopFlag[i]);
    }

		return (ret == S_DONE);
	}
	catch(...)
	{
    if(critical_section_manager.is_in_critic_process(this))
    {
			critical_section_manager.leave_critic_usb_dl(this);
    }
	}

	return false; //for clear compile warning
}



bool __fastcall TBOOT1::WaitForUSBCOMPortReady(unsigned short comPortNum)
{
#if 1
	bool isCanNotBeOpen=false;
	bool isCanBeOpen=false;

	while(!isCanNotBeOpen)
	{
		if(!IsUSBCOMPortCanBeOpen(comPortNum))
		{
			isCanNotBeOpen=true;
		}
		else
		{
			Sleep(10);
		}
	}

	while(!isCanBeOpen)
	{
		if(IsUSBCOMPortCanBeOpen(comPortNum))
		{
			isCanBeOpen=true;
		}
		else
		{
			Sleep(50);
		}
	}

	return true;
#else
	TCHAR	com_name[64];
	_stprintf(com_name, _T("\\\\.\\COM%hu"), comPortNum);
	HANDLE hPort;
	GC_TRACE("Checking Com Port: %d  ",comPortNum);

	while(1)
	{
		hPort= ::CreateFile(com_name, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		if( INVALID_HANDLE_VALUE == hPort )
		{
			DWORD dwError = GetLastError();
			/*
			if(dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE) {
				// assume it's legal com port if CreateFile() access denied
			}
			*/
			GC_TRACE("Open ComPort: %d Error,Error Code: %d",comPortNum,dwError);
			Sleep(50);
		}
		else if(true==isStopTrigger[comPortNum])
		{
			GC_TRACE("User Stop Operating Progress!");
			return ;
		}
		else
		{
			GC_TRACE("Open ComPort: %d OK!",comPortNum);
			::CloseHandle(hPort);
			Sleep(50);
			return ;
		}
	}

#endif
}



void __fastcall TBOOT1::printProcessInfo()
{
    GC_TRACE("");
    GC_TRACE("==================== Begin Download ====================");
    GC_TRACE("COM Port: %d", m_sComPortSetting.com.number);
    GC_TRACE("Cable Type: %s", (USB_COM == m_sDnParam.e_com_type ? "USB": "UART"));
    GC_TRACE("UART Baud Rate Class: %d [1-921600][2-460800][3-230400][4-115200]", m_sDnParam.e_baud_rate);
    GC_TRACE("Function: %d [0-DL][1-RB][2-FR]", m_sDnParam.e_Function);
    GC_TRACE("Extern Clock: %d [1-13M][2-26M][3-39M][4-52M][254-AUTO][255-Unkonw]", m_sDnParam.e_ext_clock);
    GC_TRACE("BBChip Version Check [%s]", (m_sDnParam.s_bbchip_op.b_check_bbchip_version? "Enable":"Disable"));
    GC_TRACE("BK CAL DATA OP %d [0-DO NOT BK AND RS][1-BK AND RS][2-RS][3-DL USER DATA][4 RS CAL NOLY]", m_sDnParam.e_backup_cal_data_op);
    GC_TRACE("Is USB Two Site USB DL %s", IsUSBDownloadWithTwoSite() ? "yes" : "no");
}

/*
*   This function is used for two station usb download.
*   To judge whether the current comport is mtk usb cable.
*     the device id is saved in ini config file, the function read the current comport device id,
*     then compare with the ini device id, if no match, report "USB ERROR"
*   Notice that if modify the ini device id, then the tool should be restarted for take effect
*/



E_CheckUSBResult __fastcall TBOOT1::check_is_usb_cable(void)
{
    //int j = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    //////////////
    if( MainForm->m_usbdeviceid == "")
    {  //if no setting in ini, default OK
        return CHECKUSB_OK;
    }

    prefix = "USB ";

    DWORD i;
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA DeviceInfoData;
    AnsiString KeyPath;

    //	GUID_SERENUM_BUS_ENUMERATOR
    //	{4D36E978-E325-11CE-BFC1-08002BE10318};
    GUID guidPortClass =
    {
        0x4D36E978L, 0xE325, 0x11CE,
        { 0xBF, 0xC1,  0x08,  0x00,  0x2B,	0xE1,  0x03,  0x18 }
    };

    // Create a HDEVINFO with all present devices.
    hDevInfo = SetupDiGetClassDevs((GUID*)&guidPortClass,
        0, 0,  DIGCF_PRESENT/*|DIGCF_ALLCLASSES*/ );

    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        return CHECKUSB_PRESENT_DEVICE_FAIL;
    }

    // Enumerate through all devices in Set.
    TCHAR rawbuf[256];
    AnsiString comport="";                 //for example:   "COM3"   "LTP1"   ..
    AnsiString comport_type="";        //for example:   "COM"    "LTP"
    AnsiString comport_num="";        //for example:         "3"
    AnsiString DeviceInstanceId="";  //for example:  "USB\\Vid_0e8d&Pid_0003\\5&11339659&0&1"
    TRegistry *Registry = new TRegistry;
    int com_number=0;

    Registry->RootKey = HKEY_LOCAL_MACHINE;
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    for (i=0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
    {
        SetupDiGetDeviceInstanceId(hDevInfo, &DeviceInfoData, rawbuf, sizeof(rawbuf), NULL);
        DeviceInstanceId = rawbuf;
        DeviceInstanceId.Trim();

        // find your specific device here
        KeyPath.sprintf("SYSTEM\\CurrentControlSet\\Enum\\%s\\Device Parameters", DeviceInstanceId);

        if(!Registry->OpenKey(KeyPath.c_str(),false))
        {   //open key fail
            delete Registry;
            return CHECKUSB_OPEN_REGISTRY_FAIL;
        }
        if( !Registry->ValueExists("PortName") )
        {   //PortName not exist
            Registry->CloseKey();
            delete Registry;
            return CHECKUSB_PORT_NOT_EXIST;
        }
        comport = Registry->ReadString("PortName");
        Registry->CloseKey();

        comport = comport.UpperCase();    //COM11
        comport_type = comport.SubString(1, 3);
        if(comport_type != "COM")
        {
            continue;
        }

        //get number
        comport_num = comport.SubString( 4, comport.Length()-3);    // 4 is the begin index
        com_number = comport_num.ToIntDef(0);
        if(com_number == m_sComPortSetting.com.number)
        {  //find the comport
            break;
        }
    }//for

    //Cleanup
    delete Registry;
    SetupDiDestroyDeviceInfoList(hDevInfo);

    //
    if(com_number == m_sComPortSetting.com.number)
    {   // find the comport
        //judge pid and vid, base on "DeviceInstanceId"
        //example:  "USB\\Vid_0e8d&Pid_0003\\5&11339659&0&1"
        //5: the begin index,  17: the length of "Vid_0e8d&Pid_0003"
        //Com port filter=usb\Vid_0e8d&Pid_0004
        AnsiString deviceid = DeviceInstanceId.SubString(1, 21);
        if( ! deviceid.AnsiCompareIC( MainForm->m_usbdeviceid ) )
        {
            prefix = "";
            return CHECKUSB_OK;
        }
        else
        {
            GC_TRACE("====== expected device id: '%s',    target device id : '%s' ========",
                MainForm->m_usbdeviceid.c_str(), deviceid.c_str());

            m_asMsg = "Error:  CHECKUSB_PID_VID_NOT_MATCH";
            Synchronize(ShowMsg);
            return CHECKUSB_PID_VID_NOT_MATCH;
        }
    }
    else
    {   //error, no comport
        return CHECKUSB_NO_COM_PORT;
    }


}

/*
E_WAIT_FOR_USB_INSERT_STATUS __fastcall TBOOT1::WaitForUSBInsert(unsigned short EventIndex)
is used for detect usb cable insert into Personal Computer.

*/
E_WAIT_FOR_USB_INSERT_STATUS __fastcall TBOOT1::WaitForUSBInsert(unsigned short EventIndex)
{
   //the thread block for wait usb insert

	HANDLE lpHandles[2];
	lpHandles[0]=Wait_USB_Insert_Event[EventIndex];
	lpHandles[1]=User_Stop_Event[EventIndex];
	DWORD wait_result;

	ResetEvent(Wait_USB_Insert_Event[EventIndex]);
	ResetEvent(User_Stop_Event[EventIndex]);

	wait_result = WaitForMultipleObjects(2, lpHandles, FALSE,	INFINITE);

	switch(wait_result)
	{
		case WAIT_OBJECT_0:
			//usb insert;
			//Sleep(500); //sleep for wait usb comport finish initial by windows system.
			Sleep(250); //sleep for wait usb comport finish initial by windows system.
			return S_USB_INSERT_READY;

		case WAIT_OBJECT_0+1:
			//user stop event
			SyncUpdateResultError();
			SetEvent(Flash_Download_Event[EventIndex]);
			GC_TRACE("====== user stop when wait for usb insert: %d========", EventIndex);
			return S_USER_STOP_PROGRESS;

		case WAIT_TIMEOUT:
		default:
			//unknown result, error
			SyncUpdateResultError();
			SetEvent(Flash_Download_Event[EventIndex]);
			GC_TRACE("====== unknown error occured when wait usb insert : %d========", EventIndex);
			return S_WAIT_EVENT_UNKNOWN_ERROR;
	}

}

E_WAIT_FOR_USB_INSERT_STATUS __fastcall TBOOT1::WaitForUSBInsertByOpenComport(unsigned short EventIndex)
{
	char pBromComStr[128];
   sprintf(pBromComStr,"\\\\.\\COM%d",m_sComPortSetting.com.number);

   HANDLE hCOM;
   GC_TRACE("[COM%d] WaitForUSBInsert(): Opening USB port......!", m_sComPortSetting.com.number);
   while(g_iStopFlag[EventIndex]!= BOOT_STOP)
   {
        hCOM = CreateFile( pBromComStr, GENERIC_READ |GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        if(INVALID_HANDLE_VALUE == hCOM){
           // GC_TRACE("[COM%d] CheckPortAvailable(): Cannot open bootrom USB port!", m_sComPortSetting.com.number);
        }
        else{
            CloseHandle(hCOM);
            GC_TRACE("[COM%d] Verify comport success! hCOM return value: %d", m_sComPortSetting.com.number,hCOM);
            return S_USB_INSERT_READY;
        }
	   		Sleep(20);
   }

   GC_TRACE("[COM%d] click stop!", m_sComPortSetting.com.number);
   return S_USER_STOP_PROGRESS;

}

E_WAIT_FOR_USB_INSERT_STATUS __fastcall TBOOT1::WaitForUSBDraw(unsigned short EventIndex)
{
   //the thread block for wait usb insert

	 char pBromComStr[128];
   sprintf(pBromComStr,"\\\\.\\COM%d",m_sComPortSetting.com.number);

   HANDLE hCOM;
   GC_TRACE("[COM%d] WaitForUSBDraw(): Opening USB port......!", m_sComPortSetting.com.number);
   while(g_iStopFlag[EventIndex]!= BOOT_STOP)
   {
        hCOM = CreateFile( pBromComStr, GENERIC_READ |GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        if(INVALID_HANDLE_VALUE == hCOM){
            GC_TRACE("[COM%d] WaitForUSBDraw(): bootrom USB port disappears!", m_sComPortSetting.com.number);
            return S_USB_INSERT_READY;
        }
        else{
            CloseHandle(hCOM);
        }
	   		Sleep(500);
   }

   GC_TRACE("[COM%d] click stop!", m_sComPortSetting.com.number);
   return S_USER_STOP_PROGRESS;

}



void __fastcall TBOOT1::WaitForComPortReadyAfterRegisterReady(unsigned short ComPortIndex)
{
					// COM Name
	TCHAR	com_name[64];
	_stprintf(com_name, _T("\\\\.\\COM%hu"), ComPortIndex);
	HANDLE hPort;
	GC_TRACE("Checking Com Port: %d  ",ComPortIndex);
	int LoopIndex;


	GC_TRACE("print Com Port file name in registry: %s  ",com_name);
	//Check usb com port is okay within 2 seconds~
	for(LoopIndex=0;LoopIndex<8;LoopIndex++)
	{
		hPort= ::CreateFile(com_name, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		if( INVALID_HANDLE_VALUE == hPort )
		{
			DWORD dwError = GetLastError();
			/*
			if(dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE) {
				// assume it's legal com port if CreateFile() access denied
			}
			*/
			GC_TRACE("Open ComPort: %d Error    ,   Error Code: %d",ComPortIndex,dwError);
			Sleep(250);
		}
		else if(true==isStopTrigger[ComPortIndex-m_sComPortSetting.com.number])
		{
			GC_TRACE("User Stop Operating Progress!");
			return ;
		}
		else
		{
			GC_TRACE("Open ComPort: %d OK!",ComPortIndex);
			::CloseHandle(hPort);
			//Sleep(50);
			return ;
		}
	}

}

int __fastcall TBOOT1::ExecuteInternal()
{
  Init_FlashTool_arg();
  Flash_Execute();
}

int __fastcall TBOOT1::Init_FlashTool_arg()
{
	
    SyncStart();
    Initial_download_arg_memory();
    Set_FlashTool_arg();
    ret = S_DONE;

    if(FLASHTOOL_ENABLE_BOOT_CERT == m_sDnParam.e_Function)
    {
        Set_FlashTool_EnableBootCert_arg();
    }
    else
    {
        Set_FlashTool_download_arg();
    }

}


int __fastcall TBOOT1::Flash_Execute()
{
    E_WAIT_FOR_USB_INSERT_STATUS E_Wait_USB_Insert_Status;
 
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

    try
    {
		    printProcessInfo();

        // comport setting
        m_iComPortIdx = i;
        if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
        {
            //  MessageBox(NULL,"Before Insert","USB",MB_OK);
			      E_Wait_USB_Insert_Status=WaitForUSBInsert(i);
			      if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
			      {
			          //return -1;
			          ret = -1;
			          goto DOWNLOADERROR;
		      	  }
        }
		//when retry start ,clear the remiding message on status bar
		if(m_RetryFlag==2)
		{
			m_asMsg = "";
			MainForm->m_stBkStatus[i]->Caption="";
			SyncShowMsg();
		}
		//end

        if(is_have_meta_action_before_download())
        {
            E_ResultAndAction result_and_action_before_DL;
            if((m_eWithoutBatteryKey == FLASHTOOL_WITHOUT_BATTERY_ON && m_eFunctionProgress == FLASHTOOL_PROGRESS_BACKUP)
				      || m_eWithoutBatteryKey == FLASHTOOL_WITHOUT_BATTERY_CLOSE)
            {
                m_eFunctionProgress = FLASHTOOL_PROGRESS_BACKUP;
                result_and_action_before_DL = Meta_action_before_download();
                if( STATUS_FAIL == result_and_action_before_DL )
                {
                   GC_TRACE("====== Tboot::Execute Meta Action Before Download : Fail ========");
				   ret = -1;
			       goto DOWNLOADERROR;
                   //if(m_bBackup == TRUE)
                   //{
                   //    SyncUpdateResultError();
                   //}
                   //return -1;
                }
               else if(SUCCESS_BUT_NOT_GOON == result_and_action_before_DL  )
               {
                   GC_TRACE("====== Tboot::Execute Meta Action Before Download :  Success, and return ========");
                   //SyncUpdateResultOk();
                   //return S_DONE;
                   ret = S_DONE;
			       goto METASUCCESS;
               }
               else
               {
                   m_eFunctionProgress = FLASHTOOL_PROGRESS_DOWNLOAD;
				   if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
                   {
                       E_WAIT_FOR_USB_INSERT_STATUS E_Wait_USB_Insert_Status=WaitForUSBDraw(i);
                       if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
                       {
                            ret = -1;
			                goto DOWNLOADERROR;
                       }
                   }
                   GC_TRACE("====== Tboot::Execute Meta Action Before Download :  Success, and go on ========");
               }
		       	}
        }

        if( FLASHTOOL_DOWNLOAD == m_sDnParam.e_Function)
        {
            if((m_eWithoutBatteryKey == FLASHTOOL_WITHOUT_BATTERY_ON && (m_eFunctionProgress == FLASHTOOL_PROGRESS_BACKUP || m_eFunctionProgress == FLASHTOOL_PROGRESS_DOWNLOAD))
				       || m_eWithoutBatteryKey == FLASHTOOL_WITHOUT_BATTERY_CLOSE)
		        {
		            m_eFunctionProgress = FLASHTOOL_PROGRESS_DOWNLOAD;
                if ( UART_COM == m_sDnParam.e_com_type)
                {
                    //UART Download Mode
                    GC_TRACE("====== Tboot::Execute Begin UART DL===");
                    ret = FlashDownload(&m_sComPortSetting, &m_sFtArg, &m_sFtResult,
                        &m_sFtDlArg, &m_sFtDnResult, &g_iStopFlag[i]);
                    GC_TRACE("====== Tboot::Execut UART DL OVER, res : %d========", ret);
                }
	              //This block is for BootROM Download Operation
                else if((USB_COM == m_sDnParam.e_com_type)&&(BROM_USB_DOWNLOAD_SUPPORT==USB_DL_Support_Status))
                {
                    //if backup->download->restore,
                    // two station usb download mode, the second station
                    GC_TRACE("====== Tboot::Execute BROM USB Download========");
                    if(is_have_meta_action_before_download())
                    {
                        E_Wait_USB_Insert_Status=WaitForUSBInsertByOpenComport(i);
		                    if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
		                    {
		    	                  //return -1;
		    	                  ret = -1;
			                       goto DOWNLOADERROR;
		                    }
                    }
                    WaitForComPortReadyAfterRegisterReady(m_sComPortSetting.com.number);
                    ret = FlashDownload(&m_sComPortSetting, &m_sFtArg, &m_sFtResult,
	                   &m_sFtDlArg, &m_sFtDnResult, &g_iStopFlag[i]);

                    if(ret ==S_DONE)
                    {
                        GC_TRACE("====== Tboot::Execut BROM USB DL OVER, res : %d========", ret);
                    }
                    else
                    {
                        GC_TRACE("====== Tboot::Not returen S_Done,Download return: %d========", ret);
                    }
           /*
			    //-------usb wo battery retry ----//
	            int m_RetryTimes = 0;
	            while( ret != S_DONE &&
                    MainForm->USBDownloadWOBattery->Checked == true &&
                    m_RetryTimes < MainForm->g_DownloadRetry )
                {

			     	E_Wait_USB_Insert_Status=WaitForUSBInsert(i);
			        if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
			        {
				       return -1;
			        }
			        GC_TRACE("====== Tboot::Execut BROM USB DL usb wo battery retry = %d========", m_RetryTimes);
                    m_RetryTimes++;

				    Initial_download_arg_memory();
					Set_FlashTool_arg();
				    Set_FlashTool_download_arg();
                  //Synchronize(ClearStatusBar);

                 // progress_hint.printf("Wait for retry [%d], error: %s [%d]", m_RetryTimes, StatusToString(ret), ret);
                  //progress_hidden_hint.printf("Error code [%d]", ret);
                 //  SyncInitProgress();

                   // reset error code mode
                   //g_error_code_mode       = FLASHTOOL;
                   //g_finish_warning_code   = FLASHTOOL_WARNING_NONE;

                   WaitForComPortReadyAfterRegisterReady(m_sComPortSetting.com.number);
                   ret = FlashDownload(&m_sComPortSetting, &m_sFtArg, &m_sFtResult,
	                   &m_sFtDlArg, &m_sFtDnResult, &g_iStopFlag[i]);
               }	//-------usb wo battery retry ----//
             */
                }
                else if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
                {
                   //two station usb download mode, the second station
                   GC_TRACE("====== Tboot::Execute begin Two Station USB DL===");

                   if(is_have_meta_action_before_download())
                   {
                       E_Wait_USB_Insert_Status=WaitForUSBInsertByOpenComport(i);
                       if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
                       {
                       	   ret = -1;
			               goto DOWNLOADERROR;
                           //return -1;
                       }
                   }
                   WaitForComPortReadyAfterRegisterReady(m_sComPortSetting.com.number);
                   ret = FlashDownload_OnlyROM(&m_sComPortSetting, &m_sFtArg, &m_sFtResult,
                         &m_sFtDlArg, &m_sFtDnResult, &g_iStopFlag[i]);
                   if(S_DONE != ret)
                   {
                        GC_TRACE("====== Tboot::Execut Two Station USB DL Error:%s    ====",StatusToString(ret));
                   }
                }
                else if(USB_COM == m_sDnParam.e_com_type && (!IsUSBDownloadWithTwoSite()) )
                {
                    //One Station USB Download Mode
                    GC_TRACE("====== Tboot::Execute: Begin One Station USB DL========");
                    GC_TRACE("====== Tboot::Execute: Begin DL bootloader ===");

                    if(false == Download_bootloader_for_usb_download())
                    {
                        //SyncUpdateResultError();
                        GC_TRACE("====== Tboot::Execute USB DL bootloader fail ========");
                        //return -1;
                        ret =-1;
						goto DOWNLOADERROR;
						
                    }

                    GC_TRACE("====== Tboot::Begin USB DL rom ===");
                    if(false == Download_rom_for_usb_download())
                    {
                        //SyncUpdateResultError();
                        GC_TRACE("====== Tboot::Execute USB DL ROM fail ========");
                        //return -1;
                        ret=-1;
						goto DOWNLOADERROR;
                    }

                    //Only DL use USB mode
                    m_sFtArg.m_boot_arg.m_usb_enable = _FALSE;//no use
                    ret = S_DONE;
                    GC_TRACE("====== Tboot::Execut One Station USB DL OVER, res : %d========", ret);

                }
                else
                {
                    GC_TRACE("====== Tboot::Execute:  Error: No executable download mode ===");
                    //SyncUpdateResultError();
                    //return -1;
                    ret = -1;
					goto DOWNLOADERROR;
                }
        	  }

            if (S_DONE == ret)
            {
                m_eFunctionProgress = FLASHTOOL_PROGRESS_RESTORE;
                if(is_have_action_after_download())
                {
                	int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
                     //query until comport disappears
                     if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
                     {
                         E_WAIT_FOR_USB_INSERT_STATUS E_Wait_USB_Insert_Status=WaitForUSBDraw(i);
                         if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
                         {
                             ret = -1;
			                       goto DOWNLOADERROR;
                         }
                     }
					 
                    GC_TRACE("Tboot::Execute: Begin Action_after_download()");
                    E_ResultAndAction result_and_action_after_DL;
                    result_and_action_after_DL = Action_after_download();
                    if( STATUS_FAIL == result_and_action_after_DL )
                    {
                        GC_TRACE("====== Tboot::Execute Meta Action After Download : Fail ========");
                        return -1;
						goto METAERROR;
                    }
                    else if(SUCCESS_BUT_NOT_GOON == result_and_action_after_DL  )
                    {
                        GC_TRACE("====== Tboot::Execute Meta Action After Download :  Success, and return ========");
                        SetEvent(Flash_Download_Event[i]);
                        //SyncUpdateMetaResultOk();
                        //return S_DONE;
                        ret = S_DONE;
						goto METASUCCESS;
                    }
                    else
                    {
                        GC_TRACE("====== Tboot::Execute Meta Action After Download :  Success========");
                    }

                }
            }

        }
        else if (FLASHTOOL_FORMAT == m_sDnParam.e_Function)
        {
            E_ResultAndAction result_and_action_after_FMT;
            result_and_action_after_FMT = Format();
            if( STATUS_FAIL == result_and_action_after_FMT )
            {
                GC_TRACE("====== Tboot::Execute Format : Fail ========");
                //SyncUpdateResultError();
                //return -1;
				ret = -1;
			    goto DOWNLOADERROR;
            }
            else if(SUCCESS_BUT_NOT_GOON == result_and_action_after_FMT  )
            {
                 GC_TRACE("====== Tboot::Execute Format :  Success, and return ========");
                 SetEvent(Flash_Download_Event[i]);
                 //SyncUpdateMetaResultOk();
                 //return S_DONE;
                 ret = S_DONE;
			     goto METASUCCESS;
            }
            else
            {
                 GC_TRACE("====== Tboot::Execute Format : Success========");
            }

        }
        else if(FLASHTOOL_ENABLE_BOOT_CERT == m_sDnParam.e_Function)
        {
            FLASHTOOL_ENABLE_BOOT_RESULT enable_boot_result;
            ret = FlashEnableBoot(&m_sComPortSetting,
                                  &m_sFtArg,&m_sFtResult,
                                  &m_sEnableBoot_Arg,
                                  &enable_boot_result,
                                  &g_iStopFlag[i]
                                  );
        }
        else
        {
            //wrong
            GC_TRACE("Tboot::Execute : NOT DOWNLOAD OR FORMAT");
            return -1;
			goto DOWNLOADERROR;
        }


        //after download
       if(  is_have_action_after_download() && USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
       {
            //if usb download/fmt, with meta operation, then should wait for phone restart
            //because if phone restart, windows will detect usb insert message,
            //when auto polling, it cannot block tool to wait for user change another phone
            Sleep(2000);
       }

       if (ret != S_DONE)
       {
           GC_TRACE("TBOOT1::Execute():Execute DL/Format fail");
           GC_TRACE("TBOOT1::Execute():%s",RetStatusToString(ret));
		   goto DOWNLOADERROR;

				//SyncUpdateResultError();
		   	
       }
       else
       {
           GC_TRACE("TBOOT1::Execute():Execute DL/Format Success");
		   goto DOWNLOADSUCCESS;
           //SyncUpdateResultOk();
       }
DOWNLOADSUCCESS:
       MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;
       SyncUpdateResultOk();
       return ret;
DOWNLOADERROR:
       SyncUpdateResultError();
       MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;
       return ret;
METAERROR:
       MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;
       return ret;
METASUCCESS:
       MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;
       SyncUpdateMetaResultOk();
       return ret;
	   
    }
    catch(...)
    {
        GC_TRACE("DL work thread %d unexception arise", i);
        MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;
        return -1;
    }

}

//==============================================================================
void __fastcall TBOOT1::Execute()
{

	 int iRetryTimes = 0;
   int portNum = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
	 int iRet = S_DONE;

	 if( MainForm->USBDownloadWOBattery->Checked == true && USB_COM == m_sDnParam.e_com_type)
	 {
	    m_eWithoutBatteryKey = FLASHTOOL_WITHOUT_BATTERY_ON;
		  m_eFunctionProgress = FLASHTOOL_PROGRESS_BACKUP;
	 }
	 else
	 {
	    m_eWithoutBatteryKey = FLASHTOOL_WITHOUT_BATTERY_CLOSE;
	 }

    m_RetryTimes = iRetryTimes;
	  iRet = ExecuteInternal();
    //add the retrying of  backup-> download->restore w/o, by wuxiong in 2012/2/20
    while( iRet != S_DONE  && iRetryTimes < MainForm->g_DownloadRetry
	 	&& m_eWithoutBatteryKey == FLASHTOOL_WITHOUT_BATTERY_ON && !Terminated && MainForm->m_miDnWithBkAndRsCalData->Checked == true)
    {
        GC_TRACE("TBOOT1::Execute():%s",RetStatusToString(iRet));
        GC_TRACE("TBOOT1::Execute():Enter retry action, Retry times = %d ========",++iRetryTimes);
        MainForm->DownloadStatus[portNum] = DOWNLOAD_STATUS_RUNNING;  //update the status of the thread running
        MainForm->Disable_SpecificMsUI(portNum);
        UpdateDownloadProgress[portNum]=true;
        m_RetryTimes = iRetryTimes;
        iRet = ExecuteInternal();
   }
	if(iRet==S_NORMAL_BLUSBDL_AND_CHIP_SUPPORT_BROMUSBV2 || iRet==S_SECURE_BLUSBDL_WITH_UNENCRYPTED_DA_AND_CHIP_SUPPORT_BROMUSBV2)
	{
		GC_TRACE("TBOOT1::Execute():%s",RetStatusToString(iRet));
        GC_TRACE("TBOOT1::Execute():Enter retry action========");
        MainForm->DownloadStatus[portNum] = DOWNLOAD_STATUS_RUNNING;  //update the status of the thread running
        MainForm->Disable_SpecificMsUI(portNum);
        UpdateDownloadProgress[portNum]=true;
		m_RetryFlag=1;
        iRet = ExecuteInternal();
		
	}
	else if(iRet==S_FT_LINUX_NVRAM_FILE_EXIST_WHEN_BACKUP)// Linux backup file has existed  mingxue2013-3-16
	{
		GC_TRACE("TBOOT1::Execute():%s",RetStatusToString(iRet));
        GC_TRACE("TBOOT1::Execute():Enter retry action (Linux restore only)========");
        MainForm->DownloadStatus[portNum] = DOWNLOAD_STATUS_RUNNING;  //update the status of the thread running
        MainForm->Disable_SpecificMsUI(portNum);
        UpdateDownloadProgress[portNum]=true;
		m_RetryFlag=2;
		Init_FlashTool_arg();
		m_sFtDlArg.m_nvram_partition_backup = LNP_RESTORE_ONLY;//set FashTool_download_arg restore only flag
  		iRet =Flash_Execute();  
		
	}
	//record total running times
	/*if(iRet==S_DONE)
		{
			AutoPullTimes++;
		}*/
	//record total running times end
    MainForm->DownloadStatus[portNum] = DOWNLOAD_STATUS_NOTRUNNING;

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::ResetFactoryDefaultProgress()
{
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    MainForm->Set_COMPercentageCaption(i, "FR ");
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComProgress(i, 0);
    MainForm->SetPbComForeColor(i, clGreen);
}

//--------------------------------------------------------------------------
void _fastcall TBOOT1::SyncResetFactoryDefaultProgress()
{
    Synchronize(ResetFactoryDefaultProgress);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::StartFactoryDefaultProgress()
{
    unsigned char uc = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    prefix = "FR ";
    SyncInitProgress();
    MainForm->Set_StartMetaAppFlag(uc, true);
    MainForm->SetPbComBackColor(uc, clWhite);
    MainForm->SetPbComProgress(uc, 0);
    MainForm->SetPbComForeColor(uc, clGreen);
}

//--------------------------------------------------------------------------
void _fastcall TBOOT1::SyncStartFactoryDefaultProgress()
{
    Synchronize(StartFactoryDefaultProgress);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::StopFactoryDefaultProgress()
{
    unsigned char uc = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    MainForm->Set_StartMetaAppFlag(uc, false);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool _fastcall TBOOT1::IsUSBDownloadWithTwoSite()
{
    //return MainForm->miUSBDLWithTwoSteps->Checked;
    if (MainForm->m_rbUSB->Checked)
    {
        return true;
    }
    return false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool __fastcall TBOOT1::IsUSBModeUploadUserDataAfterOneStationDownload()
{
  if((MainForm->USBMetaModeAfterOneStationDownload1->Checked)
    &&(DN_WITH_UL_USER_DATA == m_sDnParam.e_backup_cal_data_op))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool __fastcall TBOOT1::IsEnterMetaModeAfterDLMFT(void )
{
    if( MainForm->miEnterMetaModeafterDLFMT1->Checked )
    {
        return true;
    }

    //unchecked
    return false;
}


//--------------------------------------------------------------------------
void _fastcall TBOOT1::SyncStopFactoryDefaultProgress()
{
    Synchronize(StopFactoryDefaultProgress);
}

//--------------------------------------------------------------------------
void _fastcall TBOOT1::FinishFactoryDefaultProgress()
{
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    MainForm->SetPbComProgress(i, 100);
}

//--------------------------------------------------------------------------
void _fastcall TBOOT1::SyncFinishFactoryDefaultProgress()
{
    Synchronize(FinishFactoryDefaultProgress);
}

//---------------------------------------------------------------------------
void __fastcall TBOOT1::GetErrorMessag(STATUS_E id, unsigned int m_msp_error_code)
{
    AnsiString prefix;

    if( S_SECURITY_ERROR_BEGIN <= id ) {
        prefix.printf("Error: %s(%d) \n\nMSP Error Code: 0x%02X", StatusToString(id), id, m_msp_error_code);
    }
    else {
        prefix.printf("Error: %s(%d) ", StatusToString(id), id);
    }

    m_asMsg = "";

    switch (id)
    {
        // private random error code (1~999)

        // common error code (1000~1999)
    case S_COM_PORT_OPEN_FAIL:
        {
            m_asMsg.printf("[COM] Faile to open COM%d!", m_sComPortSetting.com.number);
        }
        break;

    case S_COM_PORT_SET_TIMEOUT_FAIL:
        {
            m_asMsg.printf("[COM] Fail to set COM%d timeout!", m_sComPortSetting.com.number);
        }
        break;

    case S_UNKNOWN_TARGET_BBCHIP:
        m_asMsg = "[User] Unsupported target baseband chip type!\n\n[ACTION]\nPlease upgrade to the latest FlashTool then try again.";
        break;
        //	    case S_SKIP_BBCHIP_HW_VER_CHECK:
    case S_UNSUPPORTED_VER_OF_BOOT_ROM:
        m_asMsg = "[User] Unsupported Boot ROM !\n\n[ACTION]\nPlease upgrade to the latest FlashTool then try again.";
        break;
    case S_UNSUPPORTED_VER_OF_BOOTLOADER:
        m_asMsg = "[MAUI] Boot Loader Image file contains an unsupported version in its header! Please ask for help.";
        break;
    case S_UNSUPPORTED_VER_OF_DA:
        m_asMsg = "[DA] DA binary file contains an unsupported version in its header! Please ask for help.";
        break;
    case S_UNSUPPORTED_VER_OF_SEC_INFO:
        m_asMsg = "[MAUI] MAUI binary file contains an unsupported security version! Please ask for help.";
        break;
    case S_UNSUPPORTED_VER_OF_ROM_INFO:
        m_asMsg = "[MAUI] MAUI binary file contains an unsupported MAUI version! Please ask for help.";
        break;
    case S_SEC_INFO_NOT_FOUND:
        m_asMsg = "[User] Your ROM files doesn't enable secure!\nSecure-on BB must boot up with secure-on ROM files!\n\n[ACTION]\nPlease use a secure-on ROM file then try again.";
        break;
    case S_ROM_INFO_NOT_FOUND:
        m_asMsg = "[MAUI] There doesn't exist a header in MAUI file! Please ask for help.";
        break;
    case S_CUST_PARA_NOT_SUPPORTED:
        m_asMsg = "[User] The phone doesn't contain Customer Parameter Area!\n\nPlease check it again.";
        break;
    case S_CUST_PARA_WRITE_LEN_INCONSISTENT:
        m_asMsg = "[User] The size of Customer Parameter file is inconsistent with that on the phone!\n\nPlease check it again.";
        break;
        //	    case S_SEC_RO_NOT_SUPPORTED:
        //	    case S_SEC_RO_WRITE_LEN_INCONSISTENT:
        //	    case S_ADDR_N_LEN_NOT_32BITS_ALIGNMENT:
    case S_UART_CHKSUM_ERROR:
        m_asMsg = "[H/W] Read-back SEC_RO or CUST_PARA and its checksum is mismatched with the checksum BROM DLL calculates after receiving through UART!\n\nPlease check your UART cable is stable or not.";
        break;
        //	    case S_NOR_FLASH_BOOT:
        //	    case S_NAND_FLASH_BOOT:
    case S_UNSUPPORTED_VER_OF_EMI_INFO:
        m_asMsg = "[MAUI] MAUI binary file contains an unsupported version of EMI setting! Please ask for help.";
        break;

        // BOOT ROM error code (2000~2999)
        //	    case S_BROM_SET_META_REG_FAIL:
        //	    case S_BROM_SET_FLASHTOOL_REG_FAIL:
        //	    case S_BROM_SET_REMAP_REG_FAIL:
        //	    case S_BROM_SET_EMI_FAIL:
    case S_BROM_DOWNLOAD_DA_FAIL:
        m_asMsg = "[H/W] Fail to download DA to baseband chip's internal SRAM!\n\nPossible reasons:\n1. There's an UART communication problem between FlashTool and BootROM.\n2. Target might be shutdown unexpectedly.\n\n[ACTION]\n1. Try again.\n2. Proceed H/W checking in download cable and target side UART path.\n3. Monitor if power-drop occured in target side.";
        break;
    case S_BROM_CMD_STARTCMD_FAIL:
        m_asMsg = "[BROM] Can not pass bootrom start command! Possibly target power up too early.";
        break;
    case S_BROM_CMD_STARTCMD_TIMEOUT:
        m_asMsg = "[BROM] BootROM start command timeout!";
        break;
        //	    case S_BROM_CMD_JUMP_FAIL:
        //	    case S_BROM_CMD_WRITE16_MEM_FAIL:
        //	    case S_BROM_CMD_READ16_MEM_FAIL:
        //	    case S_BROM_CMD_WRITE16_REG_FAIL:
        //	    case S_BROM_CMD_READ16_REG_FAIL:
        //	    case S_BROM_CMD_CHKSUM16_MEM_FAIL:
        //	    case S_BROM_CMD_WRITE32_MEM_FAIL:
        //	    case S_BROM_CMD_READ32_MEM_FAIL:
        //	    case S_BROM_CMD_WRITE32_REG_FAIL:
        //	    case S_BROM_CMD_READ32_REG_FAIL:
        //	    case S_BROM_CMD_CHKSUM32_MEM_FAIL:
        //	    case S_BROM_JUMP_TO_META_MODE_FAIL:
        //	    case S_BROM_WR16_RD16_MEM_RESULT_DIFF:
    case S_BROM_CHKSUM16_MEM_RESULT_DIFF:
        m_asMsg = "[H/W] Fail to download DA to baseband chip's internal SRAM!\n\nThe internal SRAM has the problem that leads to 16 bits checksum error!";
        break;
    case S_BROM_BBCHIP_HW_VER_INCORRECT:
        m_asMsg = "[H/W] Target baseband chip is inconsistent with bin files!\n\n[ACTION]\nPlease select the suitable bin files for the target's baseband chip.";
        break;
    case S_BROM_FAIL_TO_GET_BBCHIP_HW_VER:
        m_asMsg = "[H/W] Fail to get target baseband chip H/W version!\n\nPossible reasons:\n1. There's an UART communication problem between FlashTool and BootROM.\n2. Target might be shutdown unexpectedly.\n\n[ACTION]\n1. Try again.\n2. Proceed H/W checking in download cable and target side UART path.\n3. Monitor if power-drop occured in target side.";
        break;
    case S_BROM_AUTOBAUD_FAIL:
        m_asMsg = "[H/W] BootROM start command passed but fail to multiple BootROM baudrate!\n\nPossible reasons:\n1. There's an UART communication problem between FlashTool and BootROM.\n2. Target might be shutdown unexpectedly.\n\n[ACTION]\n1. Try again.\n2. If the problem still exists. Disable \"Options\"->\"Transmission option\"->\"Speed-Up BootROM baudrate\"\n    in advance mode (CTRL+ALT+V) then try again.\n3. Proceed H/W checking in download cable and target side UART path.\n4. Monitor if power-drop occured in target side.";
        break;
    case S_BROM_SPEEDUP_BAUDRATE_FAIL:
        m_asMsg = "[H/W] BootROM start command passed but fail to multiple BootROM baudrate!\n\nPossible reasons:\n1. There's an UART communication problem between FlashTool and BootROM.\n2. Target might be shutdown unexpectedly.\n\n[ACTION]\n1. Try again.\n2. If the problem still exists. Disable \"Options\"->\"Transmission option\"->\"Speed-Up BootROM baudrate\"\n    in advance mode (CTRL+ALT+V) then try again.\n3. Proceed H/W checking in download cable and target side UART path.\n4. Monitor if power-drop occured in target side.";
        break;
        //	    case S_BROM_LOCK_POWERKEY_FAIL:
        //	    case S_BROM_WM_APP_MSG_OUT_OF_RANGE:
        //	    case S_BROM_NOT_SUPPORT_MT6205B:
    case S_BROM_EXCEED_MAX_DATA_BLOCKS:
        m_asMsg = "[MAUI] The number of Multi-Bin files is more than 10!\n\nPlease don't build more than 10 binary files.";
        break;
        //	    case S_BROM_EXTERNAL_SRAM_DETECTION_FAIL:
        //	    case S_BROM_EXTERNAL_DRAM_DETECTION_FAIL:

        // DA error code (3000~3999)
    case S_DA_INT_RAM_ERROR:
        m_asMsg = "[H/W] DA didn't detect internal RAM!\n\nPossible reasons:\n1. It maybe a SMT issue.\n\nPlease ask for help.";
        break;
    case S_DA_EXT_RAM_ERROR:
        m_asMsg = "[H/W] DA didn't detect external RAM!\n\nPossible reasons:\n1. It maybe a SMT issue.\n2. It maybe a EMI issue.\n\nPlease ask for help.";
        break;
        //	    case S_DA_SETUP_DRAM_FAIL:
        //	    case S_DA_SETUP_PLL_ERR:
    case S_DA_DRAM_NOT_SUPPORT:
        m_asMsg = "[H/W] the handset doesn't support DRAM. Please ask for help.";
        break;
    case S_DA_RAM_FLOARTING:
        m_asMsg = "[H/W] DA detects that DRAM is floating!\n\nPossible reasons:\n1. It maybe a SMT issue.\n2. It maybe a EMI issue.\n\nPlease ask for help.";
        break;
    case S_DA_RAM_UNACCESSABLE:
        m_asMsg = "[H/W] DA detects that RAM is un-accessable. It maybe a SMT issue. Please ask for help.";
        break;
    case S_DA_RAM_ERROR:
        m_asMsg = "[H/W] DA detects other access error of RAM! Please ask for help.";
        break;
    case S_DA_DEVICE_NOT_FOUND:
        m_asMsg = "[H/W] DA didn't detect external SRAM or DRAM on the phone.\n\nPossible reasons:\n1. It maybe a SMT issue.\n2. It maybe a EMI issue.\n3. NOR or NAND hasn't been validated.\n Please check Memory_Validation_List_External.xls\n\nPlease ask for help.";
        break;
    case S_DA_NOR_UNSUPPORTED_DEV_ID:
        m_asMsg = "[User] Unsupported NOR Flash type!\n\n[ACTION]\nPlease upgrade to the latest FlashTool then try again.";
        break;
    case S_DA_NAND_UNSUPPORTED_DEV_ID:
        m_asMsg = "[User] Unsupported NAND Flash type!\n\n[ACTION]\nPlease upgrade to the latest FlashTool then try again.";
        break;
    case S_DA_NOR_FLASH_NOT_FOUND:
        m_asMsg = "[H/W] DA didn't detect NOR Flash on the phone.\n\nPossible reasons:\n1. It maybe a SMT issue.\n2. It maybe a EMI issue.\n3. NOR or NAND hasn't been validated.\n Please check Memory_Validation_List_External.xls\n\nPlease ask for help.";
        break;
    case S_DA_NAND_FLASH_NOT_FOUND:
        m_asMsg = "[H/W] DA didn't detect NAND Flash on the phone.\n\nPossible reasons:\n1. It maybe a SMT issue.\n2. It maybe a NFI issue.\n3. NOR or NAND hasn't been validated.\n Please check Memory_Validation_List_External.xls\n\nPlease ask for help.";
        break;
    case S_DA_SOC_CHECK_FAIL:
        m_asMsg = "[User] SOC verification failed!";
        break;
    case S_DA_NOR_PROGRAM_FAILED:
        m_asMsg = "[H/W] DA fails to program NOR Flash!\n\nPossible reasons:\n1. It maybe a SMT issue.\n\nPlease ask for help.";
        break;
    case S_DA_NOR_ERASE_FAILED:
        m_asMsg = "[H/W] DA fails to erase NOR Flash!\n\nPossible reasons:\n1. It maybe a SMT issue.\n\nPlease ask for help.";
        break;
    case S_DA_NAND_PAGE_PROGRAM_FAILED:
        m_asMsg = "[H/W] DA fails to page-program NAND Flash!\n\nPossible reasons:\n1. It maybe a SMT issue.\n\nPlease ask for help.";
        break;
    case S_DA_NAND_SPARE_PROGRAM_FAILED:
        m_asMsg = "[H/W] DA fails to spare-program NAND Flash!\n\nPossible reasons:\n1. It maybe a SMT issue.\n\nPlease ask for help.";
        break;
        //	    case S_DA_NAND_HW_COPYBACK_FAILED:
        //	    case S_DA_NAND_ERASE_FAILED:
        //	    case S_DA_TIMEOUT:
        //	    case S_DA_IN_PROGRESS:
        //	    case S_DA_SUPERAND_ONLY_SUPPORT_PAGE_READ:
        //	    case S_DA_SUPERAND_PAGE_PRGRAM_NOT_SUPPORT:
        //	    case S_DA_SUPERAND_SPARE_PRGRAM_NOT_SUPPORT:
        //	    case S_DA_SUPERAND_COPYBACK_NOT_SUPPORT:
        //	    case S_DA_NOR_CMD_SEQUENCE_ERR:
        //	    case S_DA_NOR_BLOCK_IS_LOCKED:
        //	    case S_DA_NAND_BLOCK_IS_LOCKED:
    case S_DA_NAND_BLOCK_DATA_UNSTABLE:
        m_asMsg = "[H/W] Data of the block is unstable after erasing NAND Flash.!\n\nPossible reasons:\n1. It maybe a SMT issue.\n\nPlease ask for help.";
        break;
    case S_DA_NOR_BLOCK_DATA_UNSTABLE:
        m_asMsg = "[H/W] Data of the block is unstable after erasing NOR Flash.!\n\nPossible reasons:\n1. It maybe a SMT issue.\n\nPlease ask for help.";
        break;
    case S_DA_NOR_VPP_RANGE_ERR:
        m_asMsg = "[H/W] Vpp is out of working range for NOR Flash! Please ask for help.";
        break;
        //	    case S_DA_INVALID_BEGIN_ADDR:
    case S_DA_NOR_INVALID_ERASE_BEGIN_ADDR:
        m_asMsg = "[User] An invalid begging address is given for erase operation on NOR Flash.\n\nPlease check your erase address again.";
        break;
    case S_DA_NOR_INVALID_READ_BEGIN_ADDR:
        m_asMsg = "[User] An invalid begging address is given for read operation on NOR Flash.\n\nPlease check your read address again.";
        break;
    case S_DA_NOR_INVALID_PROGRAM_BEGIN_ADDR:
        m_asMsg = "[User] An invalid begging address is given for program operation on NOR Flash.\n\nPlease check your program address again.";
        break;
    case S_DA_INVALID_RANGE:
        m_asMsg = "[User] DA_MEM_CMD command failed!\n\n 1. One of the download blocks has invalid range.\n 2. Possibly invalid begin address or end address exceeds target flash size.";
        break;
    case S_DA_NOR_PROGRAM_AT_ODD_ADDR:
        m_asMsg = "[User] DA_MEM_CMD command failed!\n\n 1. One of the download blocks has the ODD begin address!";
        break;
    case S_DA_NOR_PROGRAM_WITH_ODD_LENGTH:
        m_asMsg = "[User] DA_MEM_CMD command failed!\n\n 1. One of the download blocks has the EVEN end address! That is download block is in ODD length.";
        break;
        //	    case S_DA_NOR_BUFPGM_NO_SUPPORT:
        //	    case S_DA_NAND_UNKNOWN_ERR:
        //	    case S_DA_NAND_BAD_BLOCK:
        //	    case S_DA_NAND_ECC_1BIT_CORRECT:
        //	    case S_DA_NAND_ECC_2BITS_ERR:
        //	    case S_DA_NAND_SPARE_CHKSUM_ERR:
        //	    case S_DA_NAND_HW_COPYBACK_DATA_INCONSISTENT:
        //	    case S_DA_NAND_INVALID_PAGE_INDEX:
        //	    case S_DA_NFI_NOT_SUPPORT:
        //	    case S_DA_NFI_CS1_NOT_SUPPORT:
        //	    case S_DA_NFI_16BITS_IO_NOT_SUPPORT:
    case S_DA_NFB_BOOTLOADER_NOT_EXIST:
        m_asMsg = "[User] BootLoader doesn't exist on NAND flash! Please download BootLoader first!";
        break;
    case S_DA_NAND_NO_GOOD_BLOCK:
        m_asMsg = "[H/W] There doesn't exist any good block on NAND Flash!";
        break;
    case S_DA_BOOTLOADER_IS_TOO_LARGE:
        m_asMsg = "[MAUI] Boot Loader Image is more than 7 blocks on NAND Flash!\n\nPlease ask for help.";
        break;

    case S_DA_BLANK_FLASH:
        m_asMsg = "[User] There doesn't exist MAUI code and SEC_RO (option) on the flash.\n\nPlease choose MAUI file and SEC_RO file (option) for downloading.";
        break;
    case S_DA_CODE_AREA_IS_BLANK:
        m_asMsg = "[User] There doesn't exist MAUI code on the flash.\n\nPlease choose MAUI file for downloading.";
        break;
    case S_DA_SEC_RO_AREA_IS_BLANK:
        m_asMsg = "[User] There doesn't exist SEC_RO (option) on the flash.\n\nPlease choose SEC_RO file (option) for downloading.";
        break;
        //	    case S_DA_NOR_OTP_UNLOCKED:
    case S_DA_UNSUPPORTED_BBCHIP:
        m_asMsg = "[User] BROM DLL is too old to support this baseband chip on the phone!\n\n[ACTION]\nPlease upgrade to the latest FlashTool then try again.";
        break;
    case S_DA_FAT_NOT_EXIST:
        m_asMsg = "[User] FAT doesn't exist on the phone!";
        break;
    case S_DA_EXT_SRAM_NOT_FOUND:
        m_asMsg = "[H/W] DA didn't detect external SRAM on the phone! Please ask for help.";
        break;
    case S_DA_EXT_DRAM_NOT_FOUND:
        m_asMsg = "[H/W] DA didn't detect external DRAM on the phone! Please ask for help.";
        break;
    case S_DA_MT_PIN_LOW:
        m_asMsg = "[H/W] DA detects that a pin is always low on the phone while memory test! Please ask for help.";
        break;
    case S_DA_MT_PIN_HIGH:
        m_asMsg = "[H/W] DA detects that a pin is always high on the phone while memory test! Please ask for help.";
        break;
    case S_DA_MT_PIN_SHORT:
        m_asMsg = "[H/W] DA detects that two pin is short on the phone while memory test! Please ask for help.";
        break;
    case S_DA_MT_BUS_ERROR:
        m_asMsg = "[H/W] DA detects bus error on the phone while memory test! Please ask for help.";
        break;
    case S_DA_MT_ADDR_NOT_2BYTE_ALIGNMENT:
        m_asMsg = "[User] Input address is not 2-Byte aligned while memory test!\n\nPlease ask for help.";
        break;
    case S_DA_MT_ADDR_NOT_4BYTE_ALIGNMENT:
        m_asMsg = "[User] Input address is not 4-Byte aligned while memory test!\n\nPlease ask for help.";
        break;
    case S_DA_MT_SIZE_NOT_2BYTE_ALIGNMENT:
        m_asMsg = "[User] Input size is not 2-Byte aligned while memory test!\n\nPlease ask for help.";
        break;
    case S_DA_MT_SIZE_NOT_4BYTE_ALIGNMENT:
        m_asMsg = "[User] Input size is not 4-Byte aligned while memory test!\n\nPlease ask for help.";
        break;
    case S_DA_MT_DEDICATED_PATTERN_ERROR:
        m_asMsg = "[H/W] DA detects error on the phone while memory test with dedicated pattern! Please ask for help.";
        break;
    case S_DA_MT_INC_PATTERN_ERROR:
        m_asMsg = "[H/W] DA detects error on the phone while memory test with incremental pattern! Please ask for help.";
        break;
    case S_DA_MT_DEC_PATTERN_ERROR:
        m_asMsg = "[H/W] DA detects error on the phone while memory test with decremental pattern! Please ask for help.";
        break;
    case S_DA_NFB_BLOCK_0_IS_BAD:
        m_asMsg = "[H/W] DA detects Block 0 of NAND Flash is bad! Please ask for help.";
        break;

        // FlashTool error code (4000~4999)
        //	    case S_FT_CALLBACK_DA_REPORT_FAIL:
    case S_FT_DA_NO_RESPONSE:
        m_asMsg = "DA didn't send response data to FlashTool!";
        break;
    case S_FT_DA_SYNC_INCORRECT:
        m_asMsg = "[User] DA sync failed! Possibly download an illegal DA.";
        break;
    case S_FT_DA_VERSION_INCORRECT:
        m_asMsg = "[User] DA version is incorrect!";
        break;
    case S_FT_DA_INIT_SYNC_ERROR:
        m_asMsg.printf("Fail to send sync data to DA in initialization stage!");
        break;

    case S_FT_CHANGE_BAUDRATE_FAIL:
        {
            unsigned int baudrate_tbl[] = {	0, 921600, 460800, 230400, 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300, 110 };
            m_asMsg = "Fail to change baudrate to " + IntToStr(baudrate_tbl[m_sComPortSetting.baudrate]) + ".";
        }
        break;
    case S_FT_SET_DOWNLOAD_BLOCK_FAIL:
        m_asMsg = "DA_MEM_CMD command failed! Possibly the following reason.\n\n 1. Download block exceeds target flash size.\n 2. Download block start address is not WORD alignment.\n 3. Download block length is not multiple of WORD.";
        break;
    case S_FT_DOWNLOAD_FAIL:
        m_asMsg = "Download to flash failed! Please press CTRL+ALT+T to turn on debug log then reproduce again!\n C:\\BROM_DLL.log would be created and record more detail information.";
        break;
    case S_FT_READBACK_FAIL:
        m_asMsg = "Readback from flash failed! Please press CTRL+ALT+T to turn on debug log then reproduce again!\n C:\\BROM_DLL.log would be created and record more detail information.";
        break;
    case S_FT_FORMAT_FAIL:
        m_asMsg = "Format flash error! Possibly given a wrong format range, please check your format setting.";
        break;
    case S_FT_FINISH_CMD_FAIL:
        m_asMsg = "DA_FINISH_CMD command failed!";
        Synchronize(ShowMsg);
        break;
        //	    case S_FT_ENABLE_WATCHDOG_FAIL:
    case S_FT_NFB_DOWNLOAD_BOOTLOADER_FAIL:
        m_asMsg.printf("Fail to download BootLoader to NAND flash!");
        break;
    case S_FT_NFB_DOWNLOAD_CODE_FAIL:
        m_asMsg.printf("Fail to download Image(s) to NAND flash!");
        break;
        //	    case S_FT_NFB_INVALID_BOOTLOADER_DRAM_SETTING:
    case S_FT_NAND_READADDR_NOT_PAGE_ALIGNMENT:
        m_asMsg = "[User] The begging address of read-back operation is not page-aligned on NAND Flash!\n\nPlease check your read address again.";
        break;
    case S_FT_NAND_READLEN_NOT_PAGE_ALIGNMENT:
        m_asMsg = "[User] The length of read-back operation is not page-aligned on NAND Flash!\n\nPlease check your read address again.";
        break;
        //	    case S_FT_READ_REG16_FAIL:
        //	    case S_FT_WRITE_REG16_FAIL:
        //	    case S_FT_CUST_PARA_GET_INFO_FAIL:
        //	    case S_FT_CUST_PARA_READ_FAIL:
        //	    case S_FT_CUST_PARA_WRITE_FAIL:
        //	    case S_FT_INVALID_FTCFG_OPERATION:
        //	    case S_FT_INVALID_CUST_PARA_OPERATION:
        //	    case S_FT_INVALID_SEC_RO_OPERATION:
        //	    case S_FT_INVALID_OTP_OPERATION:
        //	    case S_FT_POST_PROCESS_FAIL:
        //	    case S_FT_FTCFG_UPDATE_FAIL:
        //	    case S_FT_SEC_RO_GET_INFO_FAIL:
        //	    case S_FT_SEC_RO_READ_FAIL:
        //	    case S_FT_SEC_RO_WRITE_FAIL:
        //	    case S_FT_ENABLE_DRAM_FAIL:
        //	    case S_FT_FS_FINDFIRSTEX_FAIL:
        //	    case S_FT_FS_FINDNEXTEX_FAIL:
        //	    case S_FT_FS_FOPEN_FAIL:
        //	    case S_FT_FS_GETFILESIZE_FAIL:
        //	    case S_FT_FS_READ_FAIL:
    case S_FT_FS_FILENAME_INVALID:
        m_asMsg = "[User] The used filename is valid! Please check if your file exists.";
        break;
    case S_FT_FS_FILENAME_TOO_LONG:
        m_asMsg = "[User] The length of used filename is too long! Please check your filename is valid.";
        break;
        //	    case S_FT_FS_ASSERT:
    case S_FT_OTP_ADDR_NOT_WORD_ALIGNMENT:
        m_asMsg = "[User] The address given of OTP operation is not word-aligned! Please check your OTP address again.";
        break;
    case S_FT_OTP_LENGTH_NOT_WORD_ALIGNMENT:
        m_asMsg = "[User] The length given of OTP operation is not word-aligned! Please check your OTP length again.";
        break;
    case S_FT_OTP_INVALID_ADDRESS_RANGE:
        m_asMsg = "[User] The address given of OTP operation is out of range! Please check your OTP address and length again.";
        break;
        //	    case S_FT_NAND_READ_TO_BUFFER_NOT_SUPPORT:
        //	    case S_FT_GET_PROJECT_ID_FAIL:
    case S_FT_ENFB_ROM_FILE_SMALL_THAN_HEADER_DESCRIBE:
        m_asMsg = "[MAUI] The size of E-NFB Rom file is smaller than that described in header of E-NFB Rom file! Please ask for help.";
        break;
        //	    case S_FT_RW_EXTRACT_NFB_FAIL:
        //	    case S_FT_MEMORY_TEST_FAIL:

        // FlashTool Handle error code (5000~5999)
    case S_AUTH_HANDLE_IS_NOT_READY:
        m_asMsg = "[User] This is a secure Base-band Chip! Please select the authentication file first.";
        break;
    case S_INVALID_AUTH_FILE:
        m_asMsg = "[User] This is an invalid authentication file with wrong format! Please ask for help.";
        break;
    case S_INVALID_DA_FILE:
        m_asMsg = "[User] This is an invalid DA file with wrong format! Please ask for help.";
        break;
        //	    case S_DA_HANDLE_IS_NOT_READY:
        //	    case S_FTHND_ILLEGAL_INDEX:
        //	    case S_FTHND_HANDLE_BUSY_NOW:
        //	    case S_FTHND_FILE_IS_UPDATED:
    case S_FTHND_FILE_IS_NOT_LOADED_YET:
        m_asMsg = "There is file not loaded yet!!\n\n";
        m_asMsg.cat_printf(" 1. Please check if the DA path is correct.\n\n");
        m_asMsg.cat_printf(" 2. Please check if all the ROM files exist.\n\n");
        m_asMsg.cat_printf(" 3. Please check if the scatter file description is sync with the exist ROM files.\n\n");
        break;
        //	    case S_FTHND_FILE_LOAD_FAIL:
        //	    case S_FTHND_FILE_UNLOAD_FAIL:
    case S_FTHND_LIST_IS_EMPTY:
        m_asMsg = "Download or Readback list is empty or all disabled!\n\nPlease select at least one entry.";
        break;
    case S_DL_SCAT_INCORRECT_FORMAT:
        m_asMsg = "[MAUI] The scatter file has incorrect format! Please ask for help.";
        break;
    case S_DL_SCAT_ADDR_IS_NOT_WORD_ALIGN:
        m_asMsg = "[MAUI] The address of some Load Region in the scatter file is not word-aligned! Please ask for help.";
        break;
    case S_DL_SCAT_OFFSET_IS_NOT_WORD_ALIGN:
        m_asMsg = "[MAUI] The offset of some Load Region in the scatter file is not word-aligned! Please ask for help.";
        break;
    case S_DL_SCAT_ADDR_IS_NOT_ASCENDING_ORDER:
        m_asMsg = "[MAUI] The addresses of all Load Region in the scatter file are not ascending in order! Please ask for help.";
        break;
    case S_DL_SCAT_JUMPTABLE_IS_NOT_ABSOLUTE_ADDR:
        m_asMsg = "[MAUI] The address of jump table binary file in the scatter file is not absolute address! Please ask for help.";
        break;
    case S_DL_LOAD_REGION_IS_OVERLAP:
        m_asMsg = "[MAUI] the addresses of some Load Regions in the scatter file are overlapped! Please ask for help.";
        break;
        //	    case S_DL_LOAD_REGION_NOT_FOUND:
        //	    case S_DL_NOT_RESOURCE_BIN:
        //	    case S_DL_MULTIBIN_MECHANISM_DISABLED:
    case S_DL_RESOURCE_NOT_MATCH_IN_JUMPTABLE:
        m_asMsg = "[DL_HANDLE] a bin file doesn't match any entry in jump table!";
        break;
    case S_DL_RESOURCE_MUST_DOWNLOAD_WITH_JUMPTABLE:
        m_asMsg = "[User] Resources and jump table are not selected to download together! Please select all resource you wanna download";
        break;
        //	    case S_DL_OVERLAP_WITH_EXISTING_RESOURCE:
        //	    case S_DL_INVALID_RESOURCE_BIN:
    case S_DL_JUMPTABLE_INCONSISTENT_WITH_SCAT:
        m_asMsg = "[DL_HANDLE] jump table is different from scatter!";
        break;
    case S_DL_INVALID_JUMPTABLE:
        m_asMsg = "[MAUI] Jump table is not loaded yet!\nBecause its content is not a correct jump table format.";
        break;
        //	    case S_DL_REGION_ADDR_INCONSISTENT_WITH_SCAT:
    case S_DL_REGION_ADDR_INCONSISTENT_WITH_RESOURCE_ADDR:
        m_asMsg = "[MAUI] The address of resource binary file in scatter file is inconsistent with the address in the header of resource binary file! Please ask for help.";
        break;
    case S_DL_INVALID_BOOTLOADER:
        m_asMsg = "[MAUI] The Boot Loader Image file has invalid information in its header! Please ask for help.";
        break;
        //	    case S_DL_BOOTLOADER_IS_NOT_LOADED_YET:
        //	    case S_DL_BOOTLOADER_NOT_FOUND:
    case S_DL_REMOTE_FILE_UNSUPPORTED_BY_BL_AUTOLOAD:
        m_asMsg = "[User] Boot Loader Image file is in remote server!\n\nPlease use a local Boot Loader Image file in your computer.";
        break;
        //	    case S_DLIST_SAME_BBCHIP_SW_VER:
    case S_DLIST_BBCHIP_HW_VER_NOT_MATCHED:
        m_asMsg = "[H/W] Target baseband chip is inconsistent with bin files!\n\n[ACTION]\nPlease select the suitable bin files for the target's baseband chip.";
        break;
        //	    case S_DLIST_NO_MATCHED_DL_HANDLE_FOUND:
        //	    case S_DLIST_DL_HANDLE_NOT_IN_LIST:
        //	    case S_DLIST_DL_HANDLE_ALREADY_IN_LIST:
        //	    case S_FTHND_CALLBACK_REMOTE_GET_FILE_LEN_FAIL:
        //	    case S_FTHND_CALLBACK_REMOTE_READ_FILE_FAIL:
        //	    case S_FTHND_CALLBACK_FILE_INTEGRITY_CHECK_FAIL:
    case S_UNSUPPORTED_VER_OF_AUTH_FILE:
        m_asMsg = "[User] The authentication file contains an unsupported version!\n\nPlease check the FlashTool is the latest version, or ask for help.";
        break;
    case S_DL_PROJECT_ID_DIFF_BETWEEN_MAIN_CODE_AND_JUMP_TBL:
        m_asMsg = "[MAUI] The project IDs between MAUI code and jump table binary file are different!\n\nPlease check the MAUI and jump table are in the same project.";
        break;
    case S_DL_SCAT_OPEN_FAIL:
        m_asMsg = "[User] The scatter file cannot be opened!\n\nPlease check if your scatter file exists and is not used by other software.";
        break;
        //	    case S_FTHND_CALLBACK_COM_INIT_STAGE_FAIL:
    case S_DL_UNSECURE_MAUI_TO_SECURE_BB:
        m_asMsg = "[User] Un-secure MAUI cannot be downloaded into Secure BB!\n\nPlease use security-enabled MAUI.";
        break;

        // security error code (6000~6999)
        //	    case S_SECURITY_CALLBACK_SLA_CHALLENGE_FAIL:
    case S_SECURITY_SLA_WRONG_AUTH_FILE:
        m_asMsg = "[User] The authentication file with a custom name is different from the custom name in the handset!\n\nPlease ask the owner of this handset for an authentication file with a correct custom name.";
        break;
    case S_SECURITY_SLA_INVALID_AUTH_FILE:
        m_asMsg = "[User] An invalid authentication file is used!\n\nThis error message will occurs with MSP (MTK Secure Platform) code. Please keep up the MSP code and ask for help.";
        break;
        //	    case S_SECURITY_SLA_CHALLENGE_FAIL:
        //	    case S_SECURITY_SLA_FAIL:
        //	    case S_SECURITY_DAA_FAIL:
        //	    case S_SECURITY_SBC_FAIL:
    case S_SECURITY_SF_SECURE_VER_CHECK_FAIL:
        m_asMsg = "[User] The secure version of the secure-MAUI is older than that in the handset!\n\nPlease choose a secure-MAUI with an equal or newer secure version.";
        break;
    case S_SECURITY_SF_HANDSET_SECURE_CUSTOM_NAME_NOT_MATCH:
        m_asMsg = "[User] The custom name of the secure-MAUI is different from that in the handset!\n\nPlease choose a secure-MAUI with the same custom name.";
        break;
    case S_SECURITY_SF_FTCFG_LOCKDOWN:
        m_asMsg = "[User] The Tool configuration is locked down!";
        break;
    case S_SECURITY_SF_CODE_DOWNLOAD_FORBIDDEN:
        m_asMsg = "[User] To download code area is forbidden in this phone!";
        break;
    case S_SECURITY_SF_CODE_READBACK_FORBIDDEN:
        m_asMsg = "[User] To read-back code area is forbidden in this phone!";
        break;
    case S_SECURITY_SF_CODE_FORMAT_FORBIDDEN:
        m_asMsg = "[User] To format code area is forbidden in this phone!";
        break;
    case S_SECURITY_SF_SEC_RO_DOWNLOAD_FORBIDDEN:
        m_asMsg = "[User] To download SEC_RO is forbidden in this phone!";
        break;
    case S_SECURITY_SF_SEC_RO_READBACK_FORBIDDEN:
        m_asMsg = "[User] To read-back SEC_RO is forbidden in this phone!";
        break;
    case S_SECURITY_SF_SEC_RO_FORMAT_FORBIDDEN:
        m_asMsg = "[User] To format SEC_RO is forbidden in this phone!";
        break;
    case S_SECURITY_SF_FAT_DOWNLOAD_FORBIDDEN:
        m_asMsg = "[User] To download FAT area is forbidden in this phone!";
        break;
    case S_SECURITY_SF_FAT_READBACK_FORBIDDEN:
        m_asMsg = "[User] To read-back FAT area is forbidden in this phone!";
        break;
    case S_SECURITY_SF_FAT_FORMAT_FORBIDDEN:
        m_asMsg = "[User] To format FAT area is forbidden in this phone!";
        break;
    case S_SECURITY_SF_RESTRICTED_AREA_ACCESS_FORBIDDEN:
        m_asMsg = "[User] To access restricted area (SEC_RO area and Flash Tool configuration area in the handset) is forbidden in this phone!";
        break;
    case S_SECURITY_SECURE_CUSTOM_NAME_NOT_MATCH_BETWEEN_AUTH_AND_DL_HANDLE:
        m_asMsg = "[User] The custom name in the authentication file is different from that in secure-MAUI!\n\nPlease choose the same custom name between authentication file and secure-MAUI!";
        break;
    case S_SECURITY_DOWNLOAD_FILE_IS_CORRUPTED:
        m_asMsg = "[MAUI] Some information about security in secure-MAUI file is corrupted or broken! Please ask for help.";
        break;
        //	    case S_SECURITY_NOT_SUPPORT:

    default:
        break;
    }

    m_asMsg = prefix + "\n\n" + m_asMsg;
}


int __fastcall TBOOT1::GetWatchDogTimeOutInterval()
{
//m_iComPortIdx
	DWORD CurrentTime=GetTickCount();
	DWORD BootUpTime=CurrentTime;
	DWORD WatchDogTimeOutSetting=(DWORD)DEFAULT_MIN_WATCHDOG_TIMEOUT_SETTING;
	DWORD LatestBootUp=0;

	BootUpTime+=WatchDogTimeOutSetting;	//Watchdog time out >1000ms


	DWORD dwWaitResult;

	GC_TRACE("====== Tboot::begin wait into usb com cirtical section====>");

	dwWaitResult = WaitForSingleObject(ThreadBootUpTimeTableMutex, INFINITE);

	if (BOOT_STOP == g_iStopFlag[m_iComPortIdx])
	{
		ReleaseMutex(ThreadBootUpTimeTableMutex);
		return DEFAULT_MAX_WATCHDOG_TIMEOUT_SETTING;
	}
	GC_TRACE("Table: %d %d %d %d %d  ",ThreadBootUpTimeTable[0],ThreadBootUpTimeTable[1],
				ThreadBootUpTimeTable[2],ThreadBootUpTimeTable[3],ThreadBootUpTimeTable[4]);

	switch (dwWaitResult)
	{
		case WAIT_OBJECT_0:
		{
			//Get latest boot up time.
			for(int i=0;i<MAX_SUPPORT_PORT_NUM;i++)
			{
				if(ThreadBootUpTimeTable[i]>LatestBootUp)
				{
					LatestBootUp=ThreadBootUpTimeTable[i];
				}
			}
			GC_TRACE("LatestBootUp: %d  BootUpTime: %d",LatestBootUp,BootUpTime);

			if((BootUpTime<LatestBootUp)||((BootUpTime-LatestBootUp)<(DWORD)DEFAULT_WATCHDOG_TIMEOUT_SETTING_INTERVAL))
			{
				BootUpTime=LatestBootUp+(DWORD)DEFAULT_WATCHDOG_TIMEOUT_SETTING_INTERVAL;
				WatchDogTimeOutSetting=BootUpTime-CurrentTime;
				GC_TRACE("CurrentTime: %d  BootUpTime: %d WatchDogTimeOutSetting: %d",CurrentTime,BootUpTime,WatchDogTimeOutSetting);
			}
			//Update boot up table
			if(WatchDogTimeOutSetting>(DWORD)DEFAULT_MAX_WATCHDOG_TIMEOUT_SETTING)
			{
				WatchDogTimeOutSetting=(DWORD)DEFAULT_MAX_WATCHDOG_TIMEOUT_SETTING;
			}
			ThreadBootUpTimeTable[m_iComPortIdx]=BootUpTime;
			ReleaseMutex(ThreadBootUpTimeTableMutex);
			GC_TRACE("====== Tboot::Exit crirtical section====>");
			return (int)WatchDogTimeOutSetting;

		}

		case WAIT_TIMEOUT:
		default:
				return DEFAULT_MAX_WATCHDOG_TIMEOUT_SETTING;

			} // switch()

}

/*
Function: change the return status to string.
Histrory:
   1. 2012/10/10 by wuxiong: add this function

*/
AnsiString _fastcall TBOOT1::RetStatusToString(int iRet)
{
    AnsiString strStatus;

    switch (iRet)
    {
    case S_DA_NOR_UNSUPPORTED_DEV_ID:
    case S_DA_NAND_UNSUPPORTED_DEV_ID:
        {
            strStatus = "Error: Flash not support, please refer to Memory_Validation_List_External.xls for current support flash list.";
        }
        break;
    default:
        {
           strStatus.printf("Error: %s(%d) ", StatusToString(iRet), iRet);
        }
        break;
    }
    return strStatus;
}

