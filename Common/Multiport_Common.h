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
 *   multiport_common.h
 *
 * Project:
 * --------
 *   Multiport Download Tool
 *
 * Description:
 * ------------
 *  Multiport download tool common header
 *
 * Author:
 * -------
 *  Andy Ueng (mtk00490)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
* $Revision:   1.16  $
 * $Modtime:   Sep 25 2005 11:24:48  $
 * $Log:   //mtkvs01/vmdata/Multiport_Download/archives/Multiport_Download/Common/Multiport_Common.h-arc  $
 *
 * Sep 8 2008 MTK02172
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
 * Sep 9 2007 mtk00490
 * [STP100001508] [Multiport download tool] Multiport download tool ver 3.2.0
 *
 *
 * Nov 29 2006 mtk00490
 * [STP100001239] [Multiport download tool] Multiport download tool ver 3.1.02
 *
 *
 * Jun 21 2006 MTK00490
 * [STP100000939] Multiport download Tool_v2.9.1001
 *
 *
 * Apr 4 2006 mtk00490
 * [STP100000735] [Multiport_Download] Multiport download tool ver 2.7.1017
 *
 *
 *    Rev 1.16   Sep 25 2005 12:02:40   mtk00490
 * Support NFB download and NAND flash format
 *
 *    Rev 1.15   Sep 02 2005 10:22:30   mtk00490
 * Support MT6227, MT6228 baseband chip
 *
 *    Rev 1.14   Jul 11 2005 14:45:10   mtk00490
 * Add set to factory default
 *
 *    Rev 1.13   Jul 04 2005 20:55:50   mtk00490
 * Add download time, throughput and fail reason to Microsoft Access
 *
 *    Rev 1.12   Jun 24 2005 15:24:50   mtk00490
 * Support maximum 16 port download, format only type, multi-bin option
 *
 *    Rev 1.11   Apr 14 2005 16:08:28   mtk00490
 * add stop button to stop specific or all mobile downloading and formatting
 *
 *    Rev 1.10   Apr 14 2005 16:05:40   mtk00490
 * add stop button to stop specific or all mobile downloading and formatting
 *
 *    Rev 1.9   Feb 18 2005 11:18:02   mtk00490
 * Update brom.dll and download agent ver 2.4.1009 to resolve INTEL W18/W30 series flash doesn't support Buffered-Program
 *
 *    Rev 1.8   Dec 01 2004 09:59:54   mtk00490
 * Multiport download tool ver 2.4.1007 (Add status indicator--download successful:green light, download fail:red light)
 *
 *    Rev 1.7   Nov 05 2004 17:15:00   mtk00490
 * Multiport download tool ver 2.4.1007 (Support automatic baseband chip and external clock rate detection)
 *
 *    Rev 1.6   Sep 08 2004 19:48:44   mtk00490
 * Multiport download tool ver 2.4.1004
 *
 *    Rev 1.4   Aug 28 2004 21:10:24   mtk00490
 * Multiport download ver 2.4.1003
 *
 *    Rev 1.3   Aug 28 2004 20:47:46   mtk00490
 * Multiport download ver 2.4.1002
 *
 *    Rev 1.2   Jul 19 2004 17:27:46   mtk00490
 * Multiport download ver 2.4.0
 *
 *    Rev 1.1   Jun 02 2004 21:25:32   mtk00490
 * Multiport download ver 2.3.0
 * Resolution for 2: Multiport download ver 2.3.0
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifndef _MULTIPORT_COMMON_H_
#define _MULTIPORT_COMMON_H_

// META
#ifndef META_DLL_H
#include "meta_dll/inc/meta.h"
#endif

#ifndef	_FLASHTOOL_HANDLE_H_
#include "flashtool_handle.h"
#endif

#ifndef _FLASHTOOL_H_
#include "brom_dll/inc/flashtool.h"
#endif

#ifndef _PARAM_H_
#include "param.h"
#endif
//---------------------------------------------------------------------------
//Next Block is some MACRO for some feature of Multiport Download Tool.
//

//The Macro which defined next line is about the issue:
//#define WAIT_FOR_USB_COM_PORT_READY_AFTER_REGISTER_READY

//The Macro which defined next line is about service_center version of Multiport Download Tool
//#define SERVICE_CENTER
//---------------------------------------------------------------------------



#define MAX_SUPPORT_PORT_NUM 16

#define DEFAULT_MIN_WATCHDOG_TIMEOUT_SETTING 2000
#define DEFAULT_MAX_WATCHDOG_TIMEOUT_SETTING 10000
#define DEFAULT_WATCHDOG_TIMEOUT_SETTING_INTERVAL 2000


#define ROM_LOAD_INDEX 0
#define FAT_LOAD_INDEX 1


#define IN
#define OUT
#define INOUT

//add mainly for replace the bool, which is the return type of meta_action_before_download()
// and meta_action_after_download()
//use bool as the type of return value, is not enough for some situation
typedef enum
{
    STATUS_FAIL = 0,
    SUCCESS_AND_GOON,
    SUCCESS_BUT_NOT_GOON
}E_ResultAndAction;

typedef enum
{
    CHECKUSB_OK = 0,
    CHECKUSB_PRESENT_DEVICE_FAIL=1,
    CHECKUSB_OPEN_REGISTRY_FAIL=2,
    CHECKUSB_PORT_NOT_EXIST=3,
    CHECKUSB_PID_VID_NOT_MATCH=4,
    CHECKUSB_NO_COM_PORT=5,
    CHECKUSB_END
}E_CheckUSBResult;

//add for meta extra error
typedef enum
{
    CHECK_META_OK = 0,
    CHECK_META_FOLDER_ALREADY_EXIST=1, //when backup
    CHECK_META_CREATE_FOLDER_FAIL=2,
    CHECK_META_FOLDER_DO_NOT_EXIST=3, //when restore
    CHECK_META_NOT_SUPPORT_GET_RID_ERROR = 4,
    CHECK_META_END
}E_CheckMetaExtraError;


typedef enum
{

	USB_DOWNLOAD_SUPPORT_NONE=0,
	USB_DOWNLOAD_SUPPORT,
	BROM_USB_DOWNLOAD_SUPPORT,

	USB_DOWNLOAD_SUPPORT_END
}E_USB_Download_Support_Status;

// download status
#define DOWNLOAD_STATUS_NOTRUNNING  0
#define DOWNLOAD_STATUS_RUNNING     1
#define DOWNLOAD_STATUS_ERROR       2
#define DOWNLOAD_STATUS_FINISH      3

// META
#define INVALID_META_HANDLE        -1

// Multi load
#define MAX_SUPPORT_LOAD_NUM        10


// type index
#ifndef SERVICE_CENTER
#define DOWNLOAD_ROM_AND_FAT_INDEX     0
#define DOWNLOAD_ROM_INDEX             1
#define DOWNLOAD_ROM_AND_FORMAT_INDEX  2
#define FORMAT_INDEX                   3
#define ENABLE_BOOT_CERT               4
#else
#define DOWNLOAD_ROM_INDEX 0
#endif

//#define WATCH_DOG_TIMEOUT_INTERVAL  2000
#define WATCH_DOG_TIMEOUT_INTERVAL  5000


typedef enum
{
    BAUD_RATE_115200_INDEX = 0,
    BAUD_RATE_230400_INDEX,
    BAUD_RATE_460800_INDEX,
    BAUD_RATE_921600_INDEX
}E_BAUD_RATE_INDEX_T;

typedef enum
{
    OPERATION_NOR = 0,
    OPERATION_NAND,
    OPERATION_NFB
}E_OPERATION_T;

typedef enum
{
    UART_COM = 0,
    USB_COM
}E_COM_PORT_TYPE_T;


/*
	Next enum type is added for Multiport Download Tool detect usb_cable insert
*/
typedef enum
{
	S_USB_INSERT_READY=0,
	S_USER_STOP_PROGRESS,
	S_WAIT_EVENT_UNKNOWN_ERROR
}E_WAIT_FOR_USB_INSERT_STATUS;

typedef struct
{
    bool         b_bank0_auto;
    unsigned int ui_bank0_cfg;
    bool         b_bank1_auto;
    unsigned int ui_bank1_cfg;
}S_EMI_PARAM_T;


typedef struct
{
    unsigned int		ui_nand_fat_begin_addr;
    unsigned int		ui_nand_fat_length;
    _BOOL                       b_validation;
}S_NFB_PARAM;

typedef struct
{
    unsigned int		ui_fat_begin_addr;
    unsigned int		ui_fat_length;
    _BOOL                       b_validation;
}S_NOR_PARAM;

typedef enum
{
    FLASHTOOL_DOWNLOAD = 0,
    FLASHTOOL_READBACK,
    FLASHTOOL_FORMAT,
    FLASHTOOL_ENABLE_BOOT_CERT
}E_FLASHTOOL_FUNCTION;

typedef enum
{
    FLASHTOOL_PROGRESS_BACKUP = 0,
    FLASHTOOL_PROGRESS_DOWNLOAD,
    FLASHTOOL_PROGRESS_RESTORE,
}E_FLASHTOOL_PROGRESS;

typedef enum
{
    FLASHTOOL_WITHOUT_BATTERY_CLOSE = 0,
    FLASHTOOL_WITHOUT_BATTERY_ON,
}E_FLASHTOOL_WITHOUT_BATTERY;

typedef enum
{
    DISABLE_FORMAT = 0,
    RESET_TO_FACTORY,
    AUTO_FORMAT,
    MANUAL_FORMAT
} E_FORMAT_OPTION;

typedef struct
{
    //bool b_check_eco_ver; //this is duplicate with the third, so remove this
    bool b_enable_nfi_cs1;
    bool b_check_bbchip_version;
} S_BBCHIP_OPTION_T;

typedef struct
{
    bool b_check_target_resource_layout;
    bool b_auto_load_resource_file_by_scat;
    bool b_compare_resource_project_id;
} S_MULTIBIN_OPTION;

typedef struct
{
    unsigned int	ui_nand_acccon;
    bool		b_enable_dram_setting;
    unsigned int	ui_emi_gen_a;
    unsigned int	ui_emi_gen_b;
    unsigned int	ui_emi_gen_c;
    unsigned int	ui_emi_dram_con_i_mode;
    unsigned int	ui_emi_dram_con_i_ext_mode;
    unsigned int	ui_emi_dram_con_k;
    unsigned int	ui_emi_dram_con_l;
} S_DRAM_NFI_SETTTING;

// backup and restore calibration data
typedef enum
{
    DN_WITHOUT_BK_AND_RS_CAL_DATA = 0,
    DN_WITH_BK_AND_RS_CAL_DATA,
    DN_WITH_RS_CAL_DATA,
    DN_WITH_UL_USER_DATA,
    RS_CAL_DATA_ONLY,
    UPLOAD_USER_DATA_ONLY,
    CHECK_SDS_ONLY,             //mingxue 2012-1-21 checkSDS

	BACKUP_RESTORE_OPTOIN_END
}E_BACKUP_AND_RESTORE_CAL_DATA_OP_T;

typedef struct
{
    int                 i_FirstComNo;
//    bool                b_PullDownGPIO17;
    BBCHIP_TYPE		e_bbchip_type;
    EXT_CLOCK		e_ext_clock;
    UART_BAUDRATE       e_baud_rate;
    E_COM_PORT_TYPE_T   e_com_type;
    E_FLASHTOOL_FUNCTION e_Function;
    E_OPERATION_T e_Operation;
    E_FORMAT_OPTION e_format_op;
    S_MULTIBIN_OPTION s_multibin_op;
    S_BBCHIP_OPTION_T   s_bbchip_op;
    S_NFB_PARAM  s_nfb_param;
    S_NOR_PARAM  s_nor_param;
    S_EMI_PARAM_T  s_emi_param;
    int          i_meta_handle;
    S_PARAMETER_DOWNLOAD_CONFIG s_param;
    S_DRAM_NFI_SETTTING	        sEMI_NFI_Setting;
    // backup & restore calibration data
    E_BACKUP_AND_RESTORE_CAL_DATA_OP_T e_backup_cal_data_op;

    bool       b_disconnect_comport_option;

    AnsiString as_working_dir;
    //MISC_BACKUP_REQ_T s_backup_req;
    //MISC_RESTORE_REQ_T s_restore_req;
}S_DN_PARAM_T;

//add mtk71518 2013-07-23, for login identify
typedef enum
{
    LOGIN_OPERATOR = 0,
    LOGIN_ENGINEER,

    LOGIN_IDENTIFY_UNKNOWN  = 0xFFFF
}E_Login_Identify;

/*
#define NO_CHANGE -1
typedef struct
{
    bool bPreCheckBoxState;
    int iChangedIndex;
} S_LV_CHANGED;
*/
#endif
