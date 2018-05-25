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
 *  GPS download thread source file
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
 * Aug 12 2008 mtk00490
 * [STP100001788] [Multiport download tool] Multiport download tool ver 3.0832.0
 * 
 *
 * May 21 2008 mtk00490
 * [STP100001729] [Multiport download tool] Multiport download tool ver 3.0820.0
 * 
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#if 0  //for gps download is no use now

#ifndef _FLASHDOWNLOAD_H_
#include "FlashDownload.h"
#endif

#ifndef	_BROM_DLL_WRAPPER_H_
#include "BromDllWrapper.h"
#endif

#ifndef _MUTLIPORTFLASHDOWNLOADTOOL_H_
#include "MultiPortFlashDownloadTool.h"
#endif

extern int g_iStopFlag[MAX_SUPPORT_PORT_NUM];
//---------------------------------------------------------------------------
static int __stdcall cb_gps_download_da_init(void *usr_arg);
static int __stdcall cb_gps_download_da(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg);
static int __stdcall cb_gps_download_flash_init(void *usr_arg);
static int __stdcall cb_gps_download_flash(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg);

//---------------------------------------------------------------------------
static int __stdcall cb_gps_download_da_init(void *usr_arg)
{
    TBOOT1 *t = (TBOOT1 *)usr_arg;
    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;

    t->prefix = "GPS DA ";
    MainForm->SetPbComBackColor(i, clWhite);
    MainForm->SetPbComProgress(i, 0);
    MainForm->SetPbComForeColor(i, clSkyBlue);
    t->SyncInitProgress();
    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_gps_download_da(
        unsigned char           percent,
        unsigned int            sent_bytes,
        unsigned int            total_bytes,
        void                    *usr_arg)
{

	TBOOT1 *t = (TBOOT1 *)usr_arg;

	t->m_ucProgressPercentage = percent;
       //	t->progress_finished_bytes  = sent_bytes;
       //	t->progress_total_bytes     = total_bytes;

       //	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}

//---------------------------------------------------------------------------
static int __stdcall cb_gps_download_flash_init(void *usr_arg)
{
    TBOOT1 *t = (TBOOT1 *)usr_arg;
    int i = t->m_sComPortSetting.com.number - t->m_sDnParam.i_FirstComNo;
    MainForm->SetPbComBackColor(i, clWhite);
    t->m_ucProgressPercentage = 0;
    MainForm->SetPbComForeColor(i, clSkyBlue);
    t->SyncInitProgress();

    return 0;
}

//---------------------------------------------------------------------------
static int __stdcall cb_gps_download_flash(
        unsigned char           percent,
        unsigned int            sent_bytes,
        unsigned int            total_bytes,
        void                    *usr_arg)
{
    TBOOT1 *t=(TBOOT1 *)usr_arg;
    t->prefix = "GPS DL ";
    t->m_ucProgressPercentage = percent;
    t->SyncUpdateProgress();

    return 0;
}

//---------------------------------------------------------------------------
WRAPPER_RETURN _fastcall TBOOT1::GPSDownload(void)
{

    CBromDllWrapper	    m_wrapper;
    WRAPPER_RETURN      ret;
    AnsiString          strAppDir;
    AnsiString          strLog	= "C:\\BROM_DLL_gps.log";	// default value.
    AnsiString          strDLL;
    AnsiString          strDA;
    AnsiString          strScat;
    AnsiString          strImg;
    CallBackFlashtool   cbFlashtool;
    CallBackDownload    cbDownload;

    // Init path    
    strAppDir   = ExtractFilePath(Application->ExeName);
    strDLL      = strAppDir + "gps_brom.dll";
    strDA       = strAppDir + "gps_DA.bin";
    strScat     = strAppDir + "scat.txt";


    strImg   = m_sDnParam.s_param.m_gps_rom_filepath;


    memset( &cbFlashtool, 0, sizeof(cbFlashtool));
    memset( &cbDownload,  0, sizeof(cbDownload));

    cbFlashtool.cb_download_da_init         = cb_gps_download_da_init;
    cbFlashtool.cb_download_da_init_arg     = this;
    cbFlashtool.cb_download_da              = cb_gps_download_da;
    cbFlashtool.cb_download_da_arg          = this;

    cbDownload.cb_download_flash_init       = cb_gps_download_flash_init;
    cbDownload.cb_download_flash_init_arg   = this;
    cbDownload.cb_download_flash            = cb_gps_download_flash;
    cbDownload.cb_download_flash_arg        = this;

    //- 1. Load BromDLL library
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnLoadBromDLL(strDLL.c_str())) ) {
        if( ERROR_DLL_NOT_LOAD == ret ){
            ShowMessage("[Error] Loaded GPS BROM DLL but failed");
	    	return ERROR_DLL_NOT_LOAD;
        }
        else{
            return ret;
        }
    }

    m_wrapper.fnDebugOn(strLog.c_str());  //-- Debug On

    //- 2. Load DA
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnLoadDA(strDA.c_str())) ){
        return ret;
    }

    //- 3. Load Scatter file and Firmware
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnLoadImageByScatter(strScat.c_str(),strImg.c_str())) ){
        return ret;
    }

   //- 4. Download Firmware
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnDownloadFirmware(m_sComPortSetting.com.number, &cbFlashtool, &cbDownload, &g_iStopFlag[m_iComPortIdx])) ){
        return ret;
    }

    m_wrapper.fnDebugOff(); //-- Debug Off

    return COMPLETE_SUCCESS;
}


//===========================================================================
void __fastcall TBOOT1::GetGPSErrorMessag(WRAPPER_RETURN id)
{
    AnsiString prefix;
    prefix.printf("GPS Error Code(%d) ", id);

    m_asMsg = "";




    switch(id){
	//ERROR_GENERAL,
//	case ERROR_WRONG_PARAM:
//	case ERROR_DLL_NOT_LOAD:
//	case ERROR_FUNC_INTERNAL_LOGIC:
//	case ERROR_SOMEWHERE_COMPLICATE_LOGIC:
//	case ERROR_SOMEWHERE_NONEXPECTED:
	//
	case ERROR_FAIL_TO_LOAD_DLL:
		m_asMsg = "[GPS FW] Dynamic-Load GPS DLL fails!";
		break;
	case ERROR_FAIL_TO_GETPROCADDRESS:
		m_asMsg = "[GPS FW] Dynamic-Link GPS DLL fails!";
		break;
	case ERROR_FAIL_TO_CREATE_IMAGEOBJ:
		m_asMsg = "[GPS FW] Create DL Handle fails!";
		break;
	case ERROR_FAIL_TO_CREATE_DAOBJ:
		m_asMsg = "[GPS FW] Create DA Handle fails!";
		break;
	case ERROR_FAIL_TO_CREATE_RBOBJ:
		m_asMsg = "[GPS FW] Create RB Handle fails!";
		break;
	case ERROR_FAIL_TO_DESTROY_IMAGEOBJ:
		m_asMsg = "[GPS FW] Destroy DL Object fails!";
		break;
	case ERROR_FAIL_TO_DESTROY_DAOBJ:
		m_asMsg = "[GPS FW] Destroy DA Object fails!";
		break;
	case ERROR_FAIL_TO_DESTROY_RBOBJ:
		m_asMsg = "[GPS FW] Destroy RB Object fails!";
		break;
//	case ERROR_FAIL_TO_SET_DA_STARTADDR:
	//
//	case ERROR_SCAT_INCORRECT_FORMAT:
//	case ERROR_SCAT_OFFSET_IS_NOT_WORD_ALIG:
//	case ERROR_SCAT_ADDR_IS_NOT_WORD_ALIGN:
//	case ERROR_SCAT_ADDR_IS_NOT_ASCENDING_ORDER:
//	case ERROR_SCAT_FAIL_GET_COUNT:
//	case ERROR_SCAT_FAIL_GET_INFO:
//	case ERROR_SCAT_FAIL_SETATTR:
	//
	case ERROR_DL_FW_INVALID_FORMAT:
		m_asMsg = "[GPS FW] You select an invalid format GPS FW!\r\nPlease select a correct GPS FW!";
		break;
	//
//	case ERROR_FAIL_TO_SET_RB:
//	case ERROR_RB_GET_COUNT:
//	case ERROR_RB_FAIL_SETATTR:
	//
//	case ERROR_FAIL_TO_SETPACKETLENGTH:
//	case ERROR_BOOT_STOP:
//	case ERROR_CALLBACK:
	case ERROR_FAIL_TO_OPEN_COMPORT:
		m_asMsg = "[GPS FW] Cannot open COM PORT!";
		break;
//	case ERROR_FAIL_TO_SET_DLBLOCK:
	case ERROR_FAIL_TO_DOWNLOAD_DA:
		m_asMsg = "[GPS FW] Download GPS Loader fails!\n\nPossible reasons:\n1. There doesn't exit GPS Module.\n2. GPIO_GPS_POWER_ON_PIN may be incorrectly defined!\n3. DL Cable is unstable, please try again.";
		break;
	case ERROR_FAIL_TO_FLASHDOWNLOAD:
		m_asMsg = "[GPS FW] Download GPS FW fails!\n\nPossible reasons:\n1. There doesn't exit GPS Module.\n2. GPIO_GPS_POWER_ON_PIN may be incorrectly defined!\n3. DL Cable is unstable, please try again.";
		break;
	case ERROR_FAIL_TO_FLASHREADBACK:
		m_asMsg = "[GPS FW] Readback GPS FW fails!\n\nPossible reasons:\n1. There doesn't exit GPS Module.\n2. GPIO_GPS_POWER_ON_PIN may be incorrectly defined!\n3. DL Cable is unstable, please try again.";
		break;
	//
	case ERROR_FAIL_TO_OPEN_DEBUG_LOG:
		m_asMsg = "[GPS FW] Open Debug Log fails!";
		break;
	case ERROR_FAIL_TO_CLOSE_DEBUG_LOG:
		m_asMsg = "[GPS FW] Close Debug Log fails!";
		break;
	default:
		break;
    }

    m_asMsg = prefix + "\n\n" + m_asMsg;
}
#endif //#if 0

/////////////////////////////////////////////////////////////////////////






