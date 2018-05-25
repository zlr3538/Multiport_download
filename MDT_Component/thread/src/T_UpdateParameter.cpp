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
#pragma hdrstop

#ifndef _FLASHDOWNLOAD_H_
#include "mdt_component/thread/inc/FlashDownload.h"
#endif

// form
#ifndef _MUTLIPORTFLASHDOWNLOADTOOL_H_
#include "form/mainform/MultiportFlashDownloadTool.h"
#endif

#include "mdt_component/error_handler/inc/GCTrace.h"
#include "mdt_component/thread/inc/CriticalSectionManager.h"
//===========================================================================
extern int g_iStopFlag[MAX_SUPPORT_PORT_NUM];
extern CriticalSectionManager critical_section_manager;
static int __stdcall cb_meta_upload_progress( unsigned char percent, int sent_bytes, int total_bytes, const short token, void* usr_arg);

//===========================================================================
static __stdcall void cb_backup_progress(unsigned char m_ucTotalNum, unsigned char m_ucBackupNum, void *usr_arg)
{
     TBOOT1 *t = (TBOOT1 *) usr_arg;

     t->_ucBackUpTotalNum =  m_ucTotalNum;
     t->_ucBackupNum      =  m_ucBackupNum;

     t->Sync_refresh_backup_progress();
}

void _fastcall TBOOT1::Sync_refresh_backup_progress( void )
{
     Synchronize(Refresh_backup_progress);
}

void _fastcall TBOOT1::Refresh_backup_progress( void )
{
    unsigned char uc = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

    MainForm->Display_BackupRestoreStatus(uc, _ucBackUpTotalNum, _ucBackupNum);
    if ((_ucBackUpTotalNum - _ucBackupNum) % 3 == 0)
    {
        MainForm->SetPbComProgress(uc, 100*_ucBackupNum/_ucBackUpTotalNum);
    }
//	Sleep(5);
}

//---------------------------------------------------------------------------
static __stdcall void cb_restore_progress(unsigned char m_ucTotalNum, unsigned char m_ucRestoreNum, void *usr_arg)
{
    TBOOT1 *t = (TBOOT1 *) usr_arg;

    t->_ucRestoreTotalNum = m_ucTotalNum;
    t->_ucRestoreNum = m_ucRestoreNum;

    t->Sync_refresh_restore_progress();
}

void _fastcall TBOOT1::Sync_refresh_restore_progress( void )
{
     Synchronize(Refresh_restore_progress);
}

void _fastcall TBOOT1::Refresh_restore_progress( void )
{
    unsigned char uc = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

    MainForm->Display_BackupRestoreStatus(uc, _ucRestoreTotalNum, _ucRestoreNum);
    if ((_ucRestoreTotalNum - _ucRestoreNum) % 3 == 0)
    {
        MainForm->SetPbComProgress(uc, 100*_ucRestoreNum/_ucRestoreTotalNum);
    }
	Sleep(20);
}

//---------------------------------------------------------------------------
static __stdcall void cb_upload_progress(unsigned char m_ucTotalNum,
                                         unsigned char m_ucUploadNum,
                                         void *usr_arg)
{
    TBOOT1 *t = (TBOOT1 *) usr_arg;

    t->_ucUploadTotalNum = m_ucTotalNum;
    t->_ucUploadNum = m_ucUploadNum;

    t->Sync_refresh_upload_progress();
}

void _fastcall TBOOT1::Sync_refresh_upload_progress( void )
{
     Synchronize(Refresh_upload_progress);
}

void _fastcall TBOOT1::Refresh_upload_progress( void )
{
    unsigned char uc = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

    MainForm->Display_BackupRestoreStatus(uc, _ucUploadTotalNum, _ucUploadNum);
    MainForm->SetPbComProgress(uc, 100*_ucUploadNum/_ucUploadTotalNum);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::StartBackupCalDataProgress()
{
    prefix = "BK ";
    SyncInitProgress();
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComProgress(i, 0);
    MainForm->SetPbComForeColor(i, (TColor)0x00DBB0CC);
}

//--------------------------------------------------------------------------
void _fastcall TBOOT1::SyncStartBackupCalDataProgress()
{
    Synchronize(StartBackupCalDataProgress);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::StartRestoreCalDataProgress()
{
    prefix = "RS ";
    SyncInitProgress();
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComProgress(i, 0);
    MainForm->SetPbComForeColor(i, (TColor) 0x00FFCCCC);
}

//--------------------------------------------------------------------------
void _fastcall TBOOT1::SyncStartRestoreCalDataProgress()
{
    Synchronize(StartRestoreCalDataProgress);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::StartCheckDataProgress()
{
    prefix = "CK ";
    SyncInitProgress();
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComProgress(i, 0);
    MainForm->SetPbComForeColor(i, (TColor) 0x00FFCCCC);
}
//--------------------------------------------------------------------------
void _fastcall TBOOT1::SyncStartCheckDataProgress()
{
    Synchronize(StartCheckDataProgress);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void _fastcall TBOOT1::StartUploadUserDataProgress()
{
    prefix = "Upload";
    SyncInitProgress();
    int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComProgress(i, 0);
    MainForm->SetPbComForeColor(i, (TColor) 0x00AABBAA);
}

//--------------------------------------------------------------------------
void _fastcall TBOOT1::SyncStartUploadUserDataProgress()
{
    Synchronize(StartUploadUserDataProgress);
}

//===========================================================================
///////////////////////////////// Query  ////////////////////////////////////
//===========================================================================
bool _fastcall TBOOT1::Query_BackupCalData_Support(void)
{
    META_RESULT MetaResult = META_QueryIfFunctionSupportedByTarget_r(m_sDnParam.i_meta_handle, 500, "META_MISC_GetIMEILocation_r");
    if (MetaResult != META_SUCCESS)
    {
        return false;
    }
    return true;
}

//===========================================================================
META_RESULT _fastcall TBOOT1::CheckBackupResultInfo(void)
{
    m_eMetaappOp = METAAPP_OP_RESTORE_CHECK_DATA;
    META_RESULT MetaResult;
    bool use_com_as_folder = false;
    unsigned char RID_HEX_value[33];
    BOOT_RESULT boot_result;
    //query use comport as folder name or use rid as folder name
    if(MainForm->m_CalibrationFolderNamingRule=="COMPORT")
    {
        use_com_as_folder = true;
    }
    else
    {
        GC_TRACE("====== CheckBackupResultInfo: Enter_MeTa_Mode ========");
        MetaResult = Enter_META_Mode(boot_result,m_sDnParam.e_bbchip_type, m_sDnParam.e_ext_clock);
        if (MetaResult != META_SUCCESS)
        {
            return MetaResult;
        }
      	GC_TRACE("====== CheckBackupResultInfo: Enter_MetA_Mode OK========");

        use_com_as_folder = false;
        MetaResult = META_QueryIfFunctionSupportedByTarget_r(m_sDnParam.i_meta_handle, 1000, "META_MISC_GetRID");
        if (MetaResult == META_FUNC_NOT_IMPLEMENT_YET)
        {
            GC_TRACE("====== CheckBackupResultInfo: support RID function not impliment yet, check com port folder ========");
            //load do not support query RID, please use comport to backup //?????
		        //return MetaResult;
            use_com_as_folder = true;
        }
        else if (MetaResult == META_SUCCESS)
        {
		        //support rid query, then query
            MetaResult = META_MISC_GetRID_r(m_sDnParam.i_meta_handle, 1000, RID_HEX_value, 16);
            if (MetaResult == META_SUCCESS)
            {
                GC_TRACE("==CheckBackupResultInfo: query RID: %s ", RID_HEX_value);
                if(RID_HEX_value[0] == 0)
                {
                   check_meta_extra_result = CHECK_META_NOT_SUPPORT_GET_RID_ERROR;
                   GC_TRACE("TBOOT1::BackupCalData: The RID is Null,Please check this load or use comport as backup folder!");
                   return -1;
                }
            }
            else
            {
                GC_TRACE("==CheckBackupResultInfo: Query RID failed,  the target do not support query");
                return MetaResult;
            }
        }
        else
        {
            //unknown error
            GC_TRACE("==CheckBackupResultInfo: unknown error occured when query RID, meta result:  %d", MetaResult);
            return MetaResult;
        }
    }

   if(use_com_as_folder)
   {

    AnsiString as_backup_dir = m_sDnParam.as_working_dir + "backup_and_restore_data\\" + IntToStr(m_sDnParam.i_meta_handle) + "\\";
    BACKUP_RESULT_T cnf;
    MetaResult = META_GetBackupResultInfo_r(m_sDnParam.i_meta_handle, as_backup_dir.c_str(), &cnf);
    if (MetaResult != META_SUCCESS)
    {
        return MetaResult;
    }

    m_CurrentbackupFolderRule = "COMPORT";
    m_CurrentbackupFolder = as_backup_dir;

   }
   else
   {
       // AnsiString as_backup_dir = m_sDnParam.as_working_dir + "backup_and_restore_data\\" + IntToStr(m_sDnParam.i_meta_handle) + "\\";
	AnsiString temp_rid_string ;
	temp_rid_string= (char   * )RID_HEX_value;
	AnsiString as_backup_dir = m_sDnParam.as_working_dir + "backup_and_restore_data\\" + temp_rid_string + "\\";

	BACKUP_RESULT_T cnf;
       MetaResult = META_GetBackupResultInfo_r(m_sDnParam.i_meta_handle, as_backup_dir.c_str(), &cnf);
      	if (MetaResult != META_SUCCESS)
	{
		return MetaResult;
	}

       m_CurrentbackupFolderRule = "RID";
       m_CurrentbackupFolder = as_backup_dir;

   }


    if(m_bInMetaMode)
    {

	FtWatchDog watch_dog_req;
	memset(&watch_dog_req,    0, sizeof(watch_dog_req));
	watch_dog_req.ms_timeout_interval = 2000;//WATCH_DOG_TIMEOUT_INTERVAL;
	GC_TRACE("====== TBOOT1::BackupCalData: META_EnableWatchDogTimer_r ========");
	MetaResult = META_EnableWatchDogTimer_r(m_sDnParam.i_meta_handle, 2000, &watch_dog_req);
	if (MetaResult != META_SUCCESS)
	{
		return MetaResult;
	}

       GC_TRACE("====== TBOOT1::CheckBackupResultInfo: Exit_META_Mode ========");
	MetaResult = Exit_META_Mode();
	if (MetaResult != META_SUCCESS)
	{
		return MetaResult;
	}
    }

    return MetaResult;
}

//===========================================================================
/*
Function: backup Calibration data
History :
1. 2012/10/11 by wuxiong: Set RTC to download mode for next download for data card
   for example:
      ret = META_MISC_EX_SetCommandToSystem_r( m_sDnParam.i_meta_handle,5000, meta_system_ex_command)
2. 2012/11/07 by wuxiong: if backup fail,the backup folder should be delete, then the operator can do backup again!
   for example:
        if (MetaResult != META_SUCCESS)
        {
           // empty backup folder
            GC_TRACE("Error:backup fail,delete backup folder!begin to delete all file in backup folder!");
            META_RESULT MetaResultTmp;
            MetaResultTmp = META_DeleteAllFilesInBackupFolder_r(m_sDnParam.i_meta_handle, s_backup_req.m_pBackupFolderPath);
            if (MetaResultTmp != META_SUCCESS)
            {
                GC_TRACE("Error:META_DeleteAllFilesInBackupFolder_r fail when backup fail!");
            }

            if(RemoveDirectory(s_backup_req.m_pBackupFolderPath) == FALSE)
            {
                GC_TRACE("Error:remove backup folder fail!folder path:%s",s_backup_req.m_pBackupFolderPath);
            }
            return MetaResult;
        }
*/
META_RESULT _fastcall TBOOT1::BackupCalData(void)
{
    m_eMetaappOp = METAAPP_OP_BACKUP_CAL_DATA;
    META_RESULT MetaResult;
    bool use_com_as_folder=false;
    unsigned char RID_HEX_value[33]={0};
    BOOT_RESULT boot_result;

    GC_TRACE("TBOOT1::BackupCalData():Begin Backup Calibration data!");
    MetaResult = Enter_META_Mode(boot_result,m_sDnParam.e_bbchip_type, m_sDnParam.e_ext_clock);
    if (MetaResult != META_SUCCESS)
    {
        GC_TRACE("TBOOT1::BackupCalData: Enter_MetA_Mode Fail!");
		    return MetaResult;
    }

    GC_TRACE("TBOOT1::BackupCalData: Enter_MetA_Mode OK!");
    //query use comport as folder name or use rid as folder name
    if(MainForm->m_CalibrationFolderNamingRule=="COMPORT")
    {
        use_com_as_folder = true;
    }
    else
    {
        use_com_as_folder = false;
        MetaResult = META_QueryIfFunctionSupportedByTarget_r(m_sDnParam.i_meta_handle, 1000, "META_MISC_GetRID");
        if (MetaResult == META_FUNC_NOT_IMPLEMENT_YET)
        {
		        GC_TRACE("TBOOT1::BackupCalData: support RID function not impliment yet, use com port as folder name!");
            //load do not support query RID, please use comport to backup //?????
		        //return MetaResult;
		        use_com_as_folder = true;
        }
        else if (MetaResult == META_SUCCESS)
        {
            //support rid query, then query
            MetaResult = META_MISC_GetRID_r(m_sDnParam.i_meta_handle, 1000, RID_HEX_value, 16);
            if (MetaResult == META_SUCCESS)
            {
                GC_TRACE("TBOOT1::BackupCalData: META_MISC_GetRID_r: %s ", RID_HEX_value);
                if(RID_HEX_value[0] == 0)
                {
                   check_meta_extra_result = CHECK_META_NOT_SUPPORT_GET_RID_ERROR;
                   GC_TRACE("TBOOT1::BackupCalData: The RID is Null,Please check this load or use comport as backup folder!");
                   return -1;
                }
            }
            else
            {
                GC_TRACE("TBOOT1::BackupCalData: Query RID failed,  the load do not support query, please use comport as backup folder or update load!");
                return MetaResult;
            }
        }
        else
        {
		         //unknown error
            GC_TRACE("TBOOT1::BackupCalData: unknown error occured when query RID, meta result:  %d", MetaResult);
            return MetaResult;
        }
    }

	  //if use com port as folder name
    if(use_com_as_folder)
    {
        m_CurrentbackupFolderRule = "COMPORT";
        GC_TRACE("TBOOT1::BackupCalData: use comport as folder name");
        bool b_new_load = Query_BackupCalData_Support();

        AnsiString as_iniFilePath = m_sDnParam.as_working_dir + "BACKUP.ini";
        MISC_BACKUP_REQ_T s_backup_req;
        s_backup_req.m_pIniFilePath = as_iniFilePath.c_str();
        AnsiString as_backup_dir = m_sDnParam.as_working_dir + "backup_and_restore_data\\" + IntToStr(m_sDnParam.i_meta_handle) + "\\";
        s_backup_req.m_pBackupFolderPath = as_backup_dir.c_str();
        s_backup_req.cb_progress = ::cb_backup_progress;
        s_backup_req.cb_progress_arg = this;

        m_CurrentbackupFolder=as_backup_dir;

		   // empty backup folder
		   MetaResult = META_DeleteAllFilesInBackupFolder_r(m_sDnParam.i_meta_handle, s_backup_req.m_pBackupFolderPath);
		   if (MetaResult != META_SUCCESS)
		   {
		       GC_TRACE("TBOOT1::BackupCalData: META_DeleteAllFilesInBackupFolder_r Fail! MetaResult(%d)",MetaResult);
			     return MetaResult;
		   }
       GC_TRACE("TBOOT1::BackupCalData: META_DeleteAllFilesInBackupFolder_r done!");
       // backup data
       if (b_new_load)
       {
           GC_TRACE("TBOOT1::BackupCalData: META_BackupCalibrationData_r");
           MetaResult = META_BackupCalibrationData_r(m_sDnParam.i_meta_handle, &s_backup_req, &g_iStopFlag[m_sDnParam.i_meta_handle]);
       }
       else
		   {
			    GC_TRACE("====== TBOOT1::BackupCalData: META_BasicBackupCalibrationData_r ========");
			    MetaResult = META_BasicBackupCalibrationData_r(m_sDnParam.i_meta_handle, &s_backup_req, &g_iStopFlag[m_sDnParam.i_meta_handle]);
		   }

		   if (MetaResult != META_SUCCESS)
		   {
			     return MetaResult;
		   }

       MainForm->m_stBkStatus[m_sDnParam.i_meta_handle]->Hint = as_backup_dir;

    }
    else
    {
        m_CurrentbackupFolderRule = "RID";
        GC_TRACE("==BackupCalData: use RID as folder name");
        bool b_new_load = Query_BackupCalData_Support();

        AnsiString as_iniFilePath = m_sDnParam.as_working_dir + "BACKUP.ini";
        MISC_BACKUP_REQ_T s_backup_req;
        s_backup_req.m_pIniFilePath = as_iniFilePath.c_str();
        AnsiString temp_rid_string ;
        temp_rid_string= (char   * )RID_HEX_value;
        AnsiString as_backup_dir = m_sDnParam.as_working_dir + "backup_and_restore_data\\" + temp_rid_string + "\\";

        s_backup_req.m_pBackupFolderPath = as_backup_dir.c_str();
        s_backup_req.cb_progress = ::cb_backup_progress;
        s_backup_req.cb_progress_arg = this;

        if  (DirectoryExists(as_backup_dir))
        {
            if(m_eWithoutBatteryKey == FLASHTOOL_WITHOUT_BATTERY_ON)
            {
               // empty backup folder
               GC_TRACE("====== TBOOT1::BackupCalData: META_DeleteAllFilesInBackupFolder_r ========");
		           MetaResult = META_DeleteAllFilesInBackupFolder_r(m_sDnParam.i_meta_handle, s_backup_req.m_pBackupFolderPath);
		           if (MetaResult != META_SUCCESS)
		           {
			             return MetaResult;
	             }

			         if(RemoveDirectory(s_backup_req.m_pBackupFolderPath) == FALSE)
			         {
			             return -1;
			         }
           }
           else
           {
              GC_TRACE("ERROR: BackupCalData:backup folder has existed, if you still want to do it,please remove it!backup folder name: %s", as_backup_dir);
		          check_meta_extra_result =  CHECK_META_FOLDER_ALREADY_EXIST;
              MainForm->m_stBkStatus[m_sDnParam.i_meta_handle]->Hint = as_backup_dir ;
              return META_FAILED;
           }
        }

        if(!CreateDir(as_backup_dir))
        {
            GC_TRACE("== ERROR: BackupCalData:  Create folder fail: %s ==", as_backup_dir);
            check_meta_extra_result = CHECK_META_CREATE_FOLDER_FAIL;
            return META_FAILED;
        }

        m_CurrentbackupFolder=as_backup_dir;
        // backup data
        if (b_new_load)
        {
            GC_TRACE("====== TBOOT1::BackupCalData: META_BackupCalibrationData_r ========");
            MetaResult = META_BackupCalibrationData_r(m_sDnParam.i_meta_handle, &s_backup_req, &g_iStopFlag[m_sDnParam.i_meta_handle]);
        }
        else
        {
            GC_TRACE("====== TBOOT1::BackupCalData: META_BasicBackupCalibrationData_r ========");
            MetaResult = META_BasicBackupCalibrationData_r(m_sDnParam.i_meta_handle, &s_backup_req, &g_iStopFlag[m_sDnParam.i_meta_handle]);
        }

        //if backup fail,the backup folder should be delete, then the operator can do backup again!
        if (MetaResult != META_SUCCESS)
        {
           // empty backup folder
            GC_TRACE("Error:backup fail,delete backup folder!begin to delete all file in backup folder!");
            META_RESULT MetaResultTmp;
            MetaResultTmp = META_DeleteAllFilesInBackupFolder_r(m_sDnParam.i_meta_handle, s_backup_req.m_pBackupFolderPath);
            if (MetaResultTmp != META_SUCCESS)
            {
                GC_TRACE("Error:META_DeleteAllFilesInBackupFolder_r fail when backup fail!");
            }

            if(RemoveDirectory(s_backup_req.m_pBackupFolderPath) == FALSE)
            {
                GC_TRACE("Error:remove backup folder fail!folder path:%s",s_backup_req.m_pBackupFolderPath);
            }
            return MetaResult;
        }

        MainForm->m_stBkStatus[m_sDnParam.i_meta_handle]->Hint = as_backup_dir ;
    }

    // Set RTC to download mode for next download
    // backup stage should always set download flag and watchdog to next donwload/format stage
    // Only for USB download to prevent the target cannot enter META when using UART
    if( USB_COM == m_sDnParam.e_com_type &&
        (boot_result.m_bbchip_type == MT6276M || boot_result.m_bbchip_type == MT6280 ))
    {
        SYSTEM_EX_CMD  meta_system_ex_command;
        meta_system_ex_command = SET_DL_FLAG;
        if( META_SUCCESS != ( ret = META_MISC_EX_SetCommandToSystem_r( m_sDnParam.i_meta_handle,5000, meta_system_ex_command) ) )
        {
            // disconnect
            GC_TRACE("Error:Set Brom download flag fail,META_MISC_EX_SetCommandToSystem_r return(%d)!", ret);
            Exit_META_Mode(TRUE);
            return ret;
        }
    }

	FtWatchDog watch_dog_req;
	memset(&watch_dog_req,    0, sizeof(watch_dog_req));

	watch_dog_req.ms_timeout_interval = (unsigned int)GetWatchDogTimeOutInterval();
	GC_TRACE("====== TBOOT1::BackupCalData: META_EnableWatchDogTimer_r Interval: %d ========",watch_dog_req.ms_timeout_interval);
	MetaResult = META_EnableWatchDogTimer_r(m_sDnParam.i_meta_handle, 2000, &watch_dog_req);
	if (MetaResult != META_SUCCESS)
	{
		return MetaResult;
	}

	GC_TRACE("====== TBOOT1::BackupCalData: Exit_META_Mode ========");
	MetaResult = Exit_META_Mode(false);
	if (MetaResult != META_SUCCESS)
	{
		return MetaResult;
	}

	GC_TRACE("====== TBOOT1::BackupCalData: is in meta mode:%d ========",m_bInMetaMode);
	m_bBackup = true;
	return META_SUCCESS;
}


//===========================================================================
META_RESULT _fastcall TBOOT1::RestoreCalData(void)
{
    BOOT_RESULT boot_result;
    META_RESULT MetaResult;
    m_eMetaappOp = METAAPP_OP_RESTORE_CAL_DATA;

    GC_TRACE("====== Tboot::RestoreCalData:: Begin RestoreCalData ========");
    if (RESET_TO_FACTORY == m_sDnParam.e_format_op)
    {
        StartRestoreCalDataProgress();
    }

    if (RESET_TO_FACTORY != m_sDnParam.e_format_op)
    {
        MetaResult = Enter_META_Mode(boot_result,m_sDnParam.e_bbchip_type, m_sDnParam.e_ext_clock);
        if (MetaResult != META_SUCCESS)
        {
            return MetaResult;
        }
    }

    if(m_CurrentbackupFolder=="")
    {
        bool use_com_as_folder=false;
    	  unsigned char RID_HEX_value[33];
	      //query use comport as folder name or use rid as folder name
    	  if(MainForm->m_CalibrationFolderNamingRule=="COMPORT"
	        || m_CurrentbackupFolderRule == "COMPORT")
        {
            use_com_as_folder = true;
	      }
	   else
	   {
	       use_com_as_folder = false;
         MetaResult = META_QueryIfFunctionSupportedByTarget_r(m_sDnParam.i_meta_handle, 1000, "META_MISC_GetRID");
         if (MetaResult == META_FUNC_NOT_IMPLEMENT_YET)
         {
		         GC_TRACE("====== RestoreCalData: support RID function not impliment yet, use com port as folder name ========");
             //load do not support query RID, please use comport to backup //?????
		         //return MetaResult;
		         use_com_as_folder = true;
         }
         else if (MetaResult == META_SUCCESS)
         {
		         //support rid query, then query
		         MetaResult = META_MISC_GetRID_r(m_sDnParam.i_meta_handle, 1000, RID_HEX_value, 16);
		         if (MetaResult == META_SUCCESS)
             {
	        	     GC_TRACE("==RestoreCalData: query RID: %s ", RID_HEX_value);
	        	     if(RID_HEX_value[0] == 0)
                 {
                   check_meta_extra_result = CHECK_META_NOT_SUPPORT_GET_RID_ERROR;
                   return -1;
                 }
             }
             else
             {
		             GC_TRACE("==RestoreCalData: Query RID failed,  the target do not support query");
			           return MetaResult;
             }
 	    }
	    else
	    {
		      //unknown error
		      GC_TRACE("==RestoreCalData: unknown error occured when query RID, meta result:  %d", MetaResult);
		      return MetaResult;
	    }
	}

        if(use_com_as_folder)
        {
            m_CurrentbackupFolder = m_sDnParam.as_working_dir + "backup_and_restore_data\\" +  IntToStr(m_sDnParam.i_meta_handle) + "\\";
            m_CurrentbackupFolderRule = "COMPORT";
        }
        else
        {
            AnsiString temp_rid_string ;       //
            temp_rid_string= (char   * )RID_HEX_value;
            m_CurrentbackupFolder = m_sDnParam.as_working_dir + "backup_and_restore_data\\" + temp_rid_string + "\\";
            m_CurrentbackupFolderRule = "RID";
        }
    }
    /////////////////////////////////////

    bool b_new_load = Query_BackupCalData_Support();
    AnsiString as_iniFilePath = m_sDnParam.as_working_dir + "BACKUP.ini";
    MISC_RESTORE_REQ_T s_restore_req;
    s_restore_req.m_pIniFilePath = as_iniFilePath.c_str();
    //AnsiString as_restore_dir = m_sDnParam.as_working_dir + "backup_and_restore_data\\" + IntToStr(m_sDnParam.i_meta_handle) + "\\";
    AnsiString as_restore_dir = m_CurrentbackupFolder;
    s_restore_req.m_pBackupFolderPath = as_restore_dir.c_str();
    s_restore_req.cb_progress = ::cb_restore_progress;
    s_restore_req.cb_progress_arg = this;

    MainForm->m_stBkStatus[m_sDnParam.i_meta_handle]->Hint = as_restore_dir ;
    if (b_new_load)
    {
        MetaResult = META_RestoreCalibrationData_r(m_sDnParam.i_meta_handle, &s_restore_req, &g_iStopFlag[m_sDnParam.i_meta_handle]);
    }
    else
    {
        MetaResult = META_BasicRestoreCalibrationData_r(m_sDnParam.i_meta_handle, &s_restore_req, &g_iStopFlag[m_sDnParam.i_meta_handle]);
    }

    if (MetaResult != META_SUCCESS)
    {
        return MetaResult;
    }


    if(m_CurrentbackupFolderRule == "RID")
    {
        bool isRemoveRIDFolder=true;
        isRemoveRIDFolder = MainForm->m_delete_CalibrationAfterRS;
        if(isRemoveRIDFolder)
        {
            MetaResult = META_DeleteAllFilesInBackupFolder_r(m_sDnParam.i_meta_handle, s_restore_req.m_pBackupFolderPath);
            if (MetaResult != META_SUCCESS)
            {
                return MetaResult;
            }
            //remove dir
            RemoveDirectory(s_restore_req.m_pBackupFolderPath);
	          MainForm->m_stBkStatus[m_sDnParam.i_meta_handle]->Hint = "Restore OK" ;
        }
    }
    else
    {
        MetaResult = META_DeleteAllFilesInBackupFolder_r(m_sDnParam.i_meta_handle, s_restore_req.m_pBackupFolderPath);
        if (MetaResult != META_SUCCESS)
        {
           return MetaResult;
        }
        MainForm->m_stBkStatus[m_sDnParam.i_meta_handle]->Hint = "Restore OK" ;
    }
/*
    bool use_com_as_folder=false;
    	unsigned char RID_HEX_value[33];
	//query use comport as folder name or use rid as folder name
	if(MainForm->m_CalibrationFolderNamingRule=="COMPORT"
	    || m_CurrentbackupFolderRule == "COMPORT")
       {
            use_com_as_folder = true;
	}
	else
	{
	    use_com_as_folder = false;

           MetaResult = META_QueryIfFunctionSupportedByTarget_r(m_sDnParam.i_meta_handle, 1000, "META_MISC_GetRID");
           if (MetaResult == META_FUNC_NOT_IMPLEMENT_YET)
           {
		    GC_TRACE("====== RestoreCalData: support RID function not impliment yet, use com port as folder name ========");
                  //load do not support query RID, please use comport to backup //?????
		    //return MetaResult;
		    use_com_as_folder = true;
           }
	    else if (MetaResult == META_SUCCESS)
	    {
		    //support rid query, then query
		    MetaResult = META_MISC_GetRID_r(m_sDnParam.i_meta_handle, 1000, RID_HEX_value, 16);
		    if (MetaResult == META_SUCCESS)
                 {
	        	    GC_TRACE("==RestoreCalData: query RID: %s ", RID_HEX_value);
                 }
		   else
		   {
		          GC_TRACE("==RestoreCalData: Query RID failed,  the target do not support query");
			   return MetaResult;
		   }
 	    }
	    else
	    {
		    //unknown error
		    GC_TRACE("==RestoreCalData: unknown error occured when query RID, meta result:  %d", MetaResult);
		    return MetaResult;
	    }
	}


    if(use_com_as_folder)
    {
    bool b_new_load = Query_BackupCalData_Support();
    AnsiString as_iniFilePath = m_sDnParam.as_working_dir + "BACKUP.ini";
    MISC_RESTORE_REQ_T s_restore_req;
    s_restore_req.m_pIniFilePath = as_iniFilePath.c_str();
    AnsiString as_restore_dir = m_sDnParam.as_working_dir + "backup_and_restore_data\\" + IntToStr(m_sDnParam.i_meta_handle) + "\\";
    s_restore_req.m_pBackupFolderPath = as_restore_dir.c_str();
    s_restore_req.cb_progress = ::cb_restore_progress;
    s_restore_req.cb_progress_arg = this;

    MainForm->m_stBkStatus[m_sDnParam.i_meta_handle]->Hint = as_restore_dir ;
    if (b_new_load)
    {
        MetaResult = META_RestoreCalibrationData_r(m_sDnParam.i_meta_handle, &s_restore_req, &g_iStopFlag[m_sDnParam.i_meta_handle]);
    }
    else
    {
        MetaResult = META_BasicRestoreCalibrationData_r(m_sDnParam.i_meta_handle, &s_restore_req, &g_iStopFlag[m_sDnParam.i_meta_handle]);
    }

    if (MetaResult != META_SUCCESS)
    {
        return MetaResult;
    }
           MetaResult = META_DeleteAllFilesInBackupFolder_r(m_sDnParam.i_meta_handle, s_restore_req.m_pBackupFolderPath);
    if (MetaResult != META_SUCCESS)
    {
        return MetaResult;
    }
           MainForm->m_stBkStatus[m_sDnParam.i_meta_handle]->Hint = "Restore OK" ;
    }
    else //use RID as folder name to restore
    {

    bool b_new_load = Query_BackupCalData_Support();
    AnsiString as_iniFilePath = m_sDnParam.as_working_dir + "BACKUP.ini";
    MISC_RESTORE_REQ_T s_restore_req;
    s_restore_req.m_pIniFilePath = as_iniFilePath.c_str();
    AnsiString temp_rid_string ;       //
    temp_rid_string= (char   * )RID_HEX_value;
    AnsiString as_restore_dir = m_sDnParam.as_working_dir + "backup_and_restore_data\\" + temp_rid_string + "\\";

    s_restore_req.m_pBackupFolderPath = as_restore_dir.c_str();
    s_restore_req.cb_progress = ::cb_restore_progress;
    s_restore_req.cb_progress_arg = this;


       if  (!DirectoryExists(as_restore_dir))
       {
                 GC_TRACE("== ERROR: RestoreCalData:  RID folder do not exist: %s ==", as_restore_dir);
		   check_meta_extra_result = CHECK_META_FOLDER_DO_NOT_EXIST;
		   return META_FAILED;
       }
       MainForm->m_stBkStatus[m_sDnParam.i_meta_handle]->Hint = temp_rid_string ;

    if (b_new_load)
    {
        MetaResult = META_RestoreCalibrationData_r(m_sDnParam.i_meta_handle, &s_restore_req, &g_iStopFlag[m_sDnParam.i_meta_handle]);
    }
    else
    {
        MetaResult = META_BasicRestoreCalibrationData_r(m_sDnParam.i_meta_handle, &s_restore_req, &g_iStopFlag[m_sDnParam.i_meta_handle]);
    }

    if (MetaResult != META_SUCCESS)
    {
        return MetaResult;
    }
        bool isRemoveRIDFolder=true;
        isRemoveRIDFolder = MainForm->m_delete_CalibrationAfterRS;
        if(isRemoveRIDFolder)
        {
          MetaResult = META_DeleteAllFilesInBackupFolder_r(m_sDnParam.i_meta_handle, s_restore_req.m_pBackupFolderPath);
          if (MetaResult != META_SUCCESS)
          {
            return MetaResult;
          }
          //remove dir
          RemoveDirectory(s_restore_req.m_pBackupFolderPath);
	    MainForm->m_stBkStatus[m_sDnParam.i_meta_handle]->Hint = "Restore OK" ;
        }

    }
             */
#if 0
	FtWatchDog watch_dog_req;
	memset(&watch_dog_req,    0, sizeof(watch_dog_req));
	watch_dog_req.ms_timeout_interval = (unsigned int)GetWatchDogTimeOutInterval();
	GC_TRACE("====== TBOOT1::BackupCalData: META_EnableWatchDogTimer_r Interval: %d ========",watch_dog_req.ms_timeout_interval);

	MetaResult = META_EnableWatchDogTimer_r(m_sDnParam.i_meta_handle, 2000, &watch_dog_req);
	if (MetaResult != META_SUCCESS)
	{
		return MetaResult;
	}
#endif

	//add for stress testing by mingxue 2013-4-12
		/*FtWatchDog watch_dog_req;
		memset(&watch_dog_req,	  0, sizeof(watch_dog_req));
	
		watch_dog_req.ms_timeout_interval = (unsigned int)GetWatchDogTimeOutInterval();
		GC_TRACE("====== TBOOT1::BackupCalData: META_EnableWatchDogTimer_r Interval: %d ========",watch_dog_req.ms_timeout_interval);
		MetaResult = META_EnableWatchDogTimer_r(m_sDnParam.i_meta_handle, 2000, &watch_dog_req);
		if (MetaResult != META_SUCCESS)
		{
			return MetaResult;
		}*/
		//end testing


    //Need modify ~~~~~
    
	int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
    //if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite()) 
	if(true == MainForm->cbAutoPollingArray[i]->Checked && IsUSBDownloadWithTwoSite())//change by mingxue
    {
        MetaResult = Exit_META_Mode(false);
    }
    else
    {
        MetaResult = Exit_META_Mode(true);
    }

    if (MetaResult != META_SUCCESS)
    {
        return MetaResult;
    }

    GC_TRACE("====== Tboot::RestoreCalData:: End RestoreCalData ========");

	

    return META_SUCCESS;
}

//===========================================================================
META_RESULT _fastcall TBOOT1::UploadUserData()
{
    BOOT_RESULT boot_result;
    META_RESULT metaResult;
	m_eMetaappOp = METAAPP_OP_UPLOAD_USER_DATA;
    metaResult = Enter_META_Mode(boot_result,m_sDnParam.e_bbchip_type, m_sDnParam.e_ext_clock);
    
    if (metaResult != META_SUCCESS)
    {
        return metaResult;
    }

    const AnsiString iniFilePath =m_sDnParam.as_working_dir + "BACKUP.ini";

  /*  MISC_UPLOAD_REQ_T uploadRequest;
    uploadRequest.m_pIniFilePath = iniFilePath.c_str();
    uploadRequest.cb_progress = &cb_upload_progress;
    uploadRequest.cb_progress_arg = this;

    metaResult = META_UploadFilesToTarget_r(
                        m_sDnParam.i_meta_handle,
                        &uploadRequest,
                        &g_iStopFlag[m_sDnParam.i_meta_handle]);

    if (metaResult != META_SUCCESS)
    {
        return metaResult;
    }
*/
    m_ucProgressPercentage      = 0;
    progress_finished_bytes  = 0;
    bUpdateFinishBytes       = true;
    //  SyncInitProgress();

    //-3. call META upload files api
    MISC_UPLOAD_REQ_EX2_T meta_upload_req;
    AnsiString imei_status;
    AnsiString macaddr_status;

    //ArgMETAUploadFilesToTarget(meta_upload_req, &imei_status, &macaddr_status);
    memset(&meta_upload_req,  0, sizeof(meta_upload_req));
    meta_upload_req.uploadRequest.m_pIniFilePath       = iniFilePath.c_str();
    meta_upload_req.cb_filetransfer_progress = cb_meta_upload_progress;
    meta_upload_req.filetransfer_arg = this;

    if( META_SUCCESS != ( ret = META_UploadFilesToTarget_Ex2_r(m_sDnParam.i_meta_handle,&meta_upload_req,  &g_iStopFlag[m_sDnParam.i_meta_handle] ) ) )
    {
        META_DisconnectWithTarget();
        return ret;
    }
    else
    {
        //META DLL doesn't call this function if there are no upload files
        //Call this call back function when the META function succeeded
        cb_meta_upload_progress(100,progress_finished_bytes, progress_total_bytes, 0, this );
    }

    return Exit_META_Mode();
}

//===========================================================================
/*typedef struct {
		unsigned short record_index; 
		unsigned int	 bufferLength;
		char*				 buffer;
	} META_GET_BARCODE_T; */

META_RESULT _fastcall TBOOT1::CheckSDS(int* ret)//add by mingxue
{
	*ret=0;
	BOOT_RESULT boot_result;
    META_RESULT metaResult;
	META_RESULT rsdsResult;
	unsigned int status_restore;
    metaResult = Enter_META_Mode(boot_result,m_sDnParam.e_bbchip_type, m_sDnParam.e_ext_clock);
	m_eMetaappOp = METAAPP_OP_CHECK_SDS;
	if (metaResult != META_SUCCESS)
    {
        *ret=5;    //Enter META Mode fail
        GC_TRACE("Failed to Enter META mode for CheckSDS\n");
        return metaResult;
    }

     /*********check cal flag**********/
	META_RESULT mr = META_QueryIfFunctionSupportedByTarget_r(m_sDnParam.i_meta_handle, 1000, "META_MISC_GetBarCodeValue_r");
	if(mr==META_SUCCESS)
		{
			META_GET_BARCODE_T barcode;
			barcode.record_index = 1;
			if(ReadBardcode(barcode))
			{
	    		char*bc=barcode.buffer;
				if((bc[60] != '1') || (bc[61] != '0')) 
				{
		    		//FAT cal not test
		    		*ret=1;
					GC_TRACE("FAT has no calibration flag\n");
					//return mr;
				}
			}
		}
	else if(mr==META_FUNC_NOT_IMPLEMENT_YET)
		{
			*ret=6;   //not support read barcode
			GC_TRACE("target not support ReadBarcode\n");
			return mr;
		}

	 /********************/

	/****restore sds data****/
	metaResult = META_QueryIfFunctionSupportedByTarget_r(m_sDnParam.i_meta_handle, 1000, "META_MISC_EX_BackupCalibrationToStorage_r");
	if(metaResult == META_SUCCESS)
	{
		rsdsResult = META_MISC_EX_BackupCalibrationToStorage_r(m_sDnParam.i_meta_handle, 5000, 1, &status_restore);
		
		if(rsdsResult==META_SUCCESS && status_restore==0)//restore sds ok
			{
				META_RESULT mr_sec = META_QueryIfFunctionSupportedByTarget_r(m_sDnParam.i_meta_handle, 1000, "META_MISC_GetBarCodeValue_r");
				if(mr_sec==META_SUCCESS)
				{
			    	//read bard code
			    	META_GET_BARCODE_T get_barcode;
					get_barcode.record_index = 1;
					if(ReadBardcode(get_barcode))
					{
						char*get_bc=get_barcode.buffer;
						if((get_bc[60] != '1') || (get_bc[61] != '0')) //sds cal fail
							{
							    //cal in SDS has some error
							    *ret=2;
								GC_TRACE("SDS has no calibration flag\n");
								return mr_sec;
							}
					}
				 }
				else if(mr_sec==META_FUNC_NOT_IMPLEMENT_YET)
					{
						*ret=6;   //not support read barcode
						GC_TRACE("target not support META_MISC_GetBarCodeValue_r\n");
			             return mr_sec;
					  
					}
				
			}
		else
			{
			    *ret=3;
				GC_TRACE("restore SDS failed\n");
				return rsdsResult;
				
			}
		return rsdsResult;
	}
	else if(metaResult == META_FUNC_NOT_IMPLEMENT_YET)
	{
	    *ret = 4;
		GC_TRACE("target not support SDS\n");
		return metaResult;
	}
	

}

bool _fastcall TBOOT1::ReadBardcode(META_GET_BARCODE_T get_barcode)
{
	
				//META_RESULT mr = META_QueryIfFunctionSupportedByTarget_r(0, 1000, "META_MISC_GetBarCodeValue_r");
    			//if(mr != META_SUCCESS)
    			//{
        		//	return false;
    			//}
    		       // META_GET_BARCODE_T get_barcode;
    			get_barcode.record_index = 1; // record index, it must be set.
    		   META_RESULT mr = META_MISC_GetBarCodeValue_r(m_sDnParam.i_meta_handle, 1000, &get_barcode);
				if(mr==META_SUCCESS)
					{
						
						return true;
						
					}
				
    			else if(mr != META_SUCCESS)
    			{
        			return false;
    			}
    			
}


//===========================================================================
static int __stdcall cb_meta_upload_progress( unsigned char   percent,
                     int    sent_bytes,
                     int    total_bytes,
                     const short token,
                     void *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;

    //t->progress_percentage		= percent;  m_ucProgressPercentage
    t->m_ucProgressPercentage		= percent;
    t->progress_finished_bytes	= sent_bytes;
    t->progress_total_bytes 	= total_bytes;

    t->bUpdateFinishBytes		= true;
    t->SyncUpdateProgress();

    return 0;
}
//===========================================================================
META_RESULT _fastcall TBOOT1::UploadUserData_ForOneStationDownloadViaUSB()
{
  m_eMetaappOp = METAAPP_OP_UPLOAD_USER_DATA;
  time_t start,finish;
  unsigned char com_port_number;
  		//Get start time
  int index = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;

  GC_TRACE_EX("==>");
  GC_TRACE_EX("critical_section_manager:0x%08X",&critical_section_manager);

  time(&start);
  do
  {
  	if(BOOT_STOP == g_iStopFlag[index])
  	{
  		if(critical_section_manager.is_in_critic_process(this))
  		{
  			critical_section_manager.leave_critic_usb_dl(this);
  		}
  		ret = S_STOP;
  		return false;
  	}

  	com_port_number = get_new_created_com_port();

  	if(com_port_number != 0)
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
  /*
  if(critical_section_manager.is_in_critic_process(this))
  {
    critical_section_manager.leave_critic_usb_dl(this);
  }
  */

  META_RESULT metaResult =
          Enter_META_Mode_ForOneStationUSBMeta(m_sDnParam.e_bbchip_type,
                                                m_sDnParam.e_ext_clock,
                                                com_port_number);
  GC_TRACE_EX("critical_section_manager:0x%08X",&critical_section_manager);

  if(critical_section_manager.is_in_critic_process(this))
  {
  	critical_section_manager.leave_critic_usb_dl(this);
  }

  if (metaResult != META_SUCCESS)
  {
      return metaResult;
  }

  const AnsiString iniFilePath =
          m_sDnParam.as_working_dir + "BACKUP.ini";

 /* MISC_UPLOAD_REQ_T uploadRequest;
  uploadRequest.m_pIniFilePath = iniFilePath.c_str();
  uploadRequest.cb_progress = &cb_upload_progress;
  uploadRequest.cb_progress_arg = this;

  metaResult = META_UploadFilesToTarget_r(
                                          m_sDnParam.i_meta_handle,
                                          &uploadRequest,
                                          &g_iStopFlag[m_sDnParam.i_meta_handle]);

  if (metaResult != META_SUCCESS)
  {
      return metaResult;
  }*/
   m_ucProgressPercentage      = 0;
 progress_finished_bytes  = 0;
 bUpdateFinishBytes       = true;
  //  SyncInitProgress();

	//-3. call META upload files api
MISC_UPLOAD_REQ_EX2_T meta_upload_req;
AnsiString imei_status;
AnsiString macaddr_status;

memset(&meta_upload_req,  0, sizeof(meta_upload_req));
meta_upload_req.uploadRequest.m_pIniFilePath       = iniFilePath.c_str();
meta_upload_req.cb_filetransfer_progress = cb_meta_upload_progress;
meta_upload_req.filetransfer_arg = this;

if( META_SUCCESS != ( ret = META_UploadFilesToTarget_Ex2_r(m_sDnParam.i_meta_handle,&meta_upload_req,  &g_iStopFlag[m_sDnParam.i_meta_handle] ) ) ) {
			META_DisconnectWithTarget();
			return ret;
}
else
{
	//META DLL doesn't call this function if there are no upload files
	//Call this call back function when the META function succeeded
	cb_meta_upload_progress(100,progress_finished_bytes, progress_total_bytes, 0, this );
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

      GC_TRACE_EX("Exit_META_Mode()");
      metaResult  = Exit_META_Mode();
      if(critical_section_manager.is_in_critic_process(this))
      {
          critical_section_manager.leave_critic_usb_dl(this);
      }
      return metaResult;
  }

}
