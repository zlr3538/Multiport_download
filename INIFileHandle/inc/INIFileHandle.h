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
 *   INIFileHandle.h
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  INI file handling header file
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
#ifndef _INIFILEHANDLE_H_
#define _INIFILEHANDLE_H_
#include <vector.h>

#ifndef _CONTAINER_COMMON_H_
#include "container_common.h"
#endif

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define COM_PORT_UART_STR "UART COM"
#define COM_PORT_USB_STR "USB COM"

class CINIFileHandle
{
public:
    /*---------------------------------------------------------------------------*/
    int read_bk_and_rs_cfg(AnsiString asSetupFile,AnsiString asExeName);
    void write_bk_and_rs_cfg(AnsiString asSetupFile, AnsiString asExeName, int iCheck);

    /*---------------------------------------------------------------------------*/
    AnsiString read_field(AnsiString asSetupFile,AnsiString asExeName, AnsiString asSecName, AnsiString asFieldName, AnsiString asDefStr);
    void write_field(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString asFieldName, AnsiString asStr);
    //-----------------------------------------------------------------------------------
    AnsiString read_Operation(AnsiString asSetupFile,AnsiString asExeName);
    void write_Operation(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Operation);
    //-----------------------------------------------------------------------------------
    AnsiString read_ComPortType(AnsiString asSetupFile,AnsiString asExeName);
    void write_ComPortType(AnsiString asSetupFile,AnsiString asExeName, AnsiString as_com_type);
    //-----------------------------------------------------------------------------------
    AnsiString read_DA_bin(AnsiString asSetupFile,AnsiString asExeName);
    void write_DA_bin(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_DA_bin);
    //-----------------------------------------------------------------------------------
    AnsiString read_AuthFile(AnsiString asSetupFile,AnsiString asExeName);
    void write_AuthFile(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_AuthFile);
    //-----------------------------------------------------------------------------------
    AnsiString read_RootCertFile(AnsiString asSetupFile,AnsiString asExeName);
    void write_RootCertFile(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_RootCertFile);
    //-----------------------------------------------------------------------------------
    AnsiString read_CertificateFile(AnsiString asSetupFile,AnsiString asExeName);
    void write_CertificateFile(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_CertificateFile);
    //-----------------------------------------------------------------------------------
    AnsiString read_Scatter( AnsiString asSetupFile,AnsiString asExeName);
    void write_Scatter( AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Scatter);
    //-----------------------------------------------------------------------------------
    AnsiString read_ROM(AnsiString asSetupFile,AnsiString asExeName, int idx);
    void write_ROM(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_ROM);
    //-----------------------------------------------------------------------------------
    AnsiString read_FAT(AnsiString asSetupFile,AnsiString asExeName, int idx);
    void write_FAT(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_FAT);
    //-----------------------------------------------------------------------------------
    AnsiString read_SEC_RO(AnsiString asSetupFile,AnsiString asExeName, int idx);
    void write_SEC_RO(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_SEC_RO);
    //-----------------------------------------------------------------------------------
    AnsiString read_SEC_RO_Checked(AnsiString asSetupFile,AnsiString asExeName, int idx);
    void write_SEC_RO_Checked(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_SEC_RO_Checked);
    //-----------------------------------------------------------------------------------
    // backup and restore calibration data
    AnsiString read_BackupAndRestoreOp(AnsiString asSetupFile,AnsiString asExeName);
    void write_BackupAndRestoreOp(AnsiString asSetupFile, AnsiString asExeName, AnsiString as);
    //-----------------------------------------------------------------------------------
    // GPS
 //   AnsiString read_GPS_ROM_Path(AnsiString asSetupFile,AnsiString asExeName, int idx);
 //   void write_GPS_ROM_Path(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as);
    //-----------------------------------------------------------------------------------
//    AnsiString read_GPS_ROM_Checked(AnsiString asSetupFile,AnsiString asExeName, int idx);
//    void write_GPS_ROM_Checked(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as);
    //-----------------------------------------------------------------------------------
    AnsiString read_TheFirstComPortNo(AnsiString asSetupFile,AnsiString asExeName);
    void write_TheFirstComPortNo(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_TheFirstComPortNo);
    //-----------------------------------------------------------------------------------
    AnsiString read_ComEnabled(AnsiString asSetupFile,AnsiString asExeName);
    void write_ComEnabled(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_ComEnabled);
    //-----------------------------------------------------------------------------------
    AnsiString read_AutoPollingEnabled(AnsiString asSetupFile,AnsiString asExeName);
    void write_AutoPollingEnabled(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_AutoPollingEnabled);
    //-----------------------------------------------------------------------------------
    bool read_ComPortSetting(AnsiString asSetupFile,AnsiString asExeName, vAsniString &vAs);
    void write_ComPortSetting(AnsiString asSetupFile, AnsiString asExeName, vAsniString &vAs);
    //-----------------------------------------------------------------------------------
    bool read_Disconnect_Comport_After_DL(AnsiString asSetupFile, AnsiString asExeName);
    void write_Disconnect_Comport_After_DL(AnsiString asSetupFile, AnsiString asExeName, bool flag);


/*
    AnsiString read_LV_FAT_index(AnsiString asSetupFile, AnsiString asExeName, int idx);
    void write_LV_FAT_index(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_LV_FAT_index);
    //------------------------------------------------------------------------------
    AnsiString read_LV_count(AnsiString asSetupFile,AnsiString asExeName);
    void write_LV_count(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_count);
    //------------------------------------------------------------------------------
    AnsiString read_LV_name(AnsiString asSetupFile,AnsiString asExeName, int index);
    void write_LV_name(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_name);
    //-----------------------------------------------------------------------------------
    void write_LV_region_addr(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_region_addr);
    void write_LV_begin_addr(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_begin_addr);
    //-----------------------------------------------------------------------------------
    void write_LV_end_addr(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_end_addr);
    //-----------------------------------------------------------------------------------
    void write_LV_location(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_location);
    //-----------------------------------------------------------------------------------
*/
    AnsiString read_Baseband_chip(AnsiString asSetupFile,AnsiString asExeName);
    void write_Baseband_chip(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Baseband_chip);
    //------------------------------------------------------------------------------
    AnsiString read_External_clock(AnsiString asSetupFile,AnsiString asExeName);
    void write_External_clock(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_External_clock);
    //------------------------------------------------------------------------------
    AnsiString read_CheckECOVersion(AnsiString asSetupFile,AnsiString asExeName);
    void write_CheckECOVersion(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_CheckECOVersion);

    //------------------------------------------------------------------------------
    AnsiString read_OperateFlashType(AnsiString asSetupFile,AnsiString asExeName);
    void write_OperateFlashType(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_OperateFlashType);

    //------------------------------------------------------------------------------
    AnsiString read_CheckEnableNFI(AnsiString asSetupFile,AnsiString asExeName);
    void write_CheckEnableNFI(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_CheckEnableNFI);

    //------------------------------------------------------------------------------
    AnsiString read_CheckTgtResLayout(AnsiString asSetupFile,AnsiString asExeName);
    void write_CheckTgtResLayout(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_CheckTgtResLayout);
    //------------------------------------------------------------------------------
    AnsiString read_AutoLoadResByScat(AnsiString asSetupFile,AnsiString asExeName);
    void write_AutoLoadResByScat(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_AutoLoadResByScat);
    //------------------------------------------------------------------------------
    AnsiString read_CompareResProjectId(AnsiString asSetupFile,AnsiString asExeName);
    void write_CompareResProjectId(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_CompareResProjectId);
    //------------------------------------------------------------------------------
    AnsiString read_BROMDllLog(AnsiString asSetupFile,AnsiString asExeName);
    void write_BROMDllLog(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_BROMDllLog);
    //------------------------------------------------------------------------------
    AnsiString read_METADllLog(AnsiString asSetupFile,AnsiString asExeName);
    void write_METADllLog(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_METADllLog);
    //------------------------------------------------------------------------------
    AnsiString read_Baudrate(AnsiString asSetupFile,AnsiString asExeName);
    void write_Baudrate(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Baudrate);
    //------------------------------------------------------------------------------
    AnsiString read_Type(AnsiString asSetupFile,AnsiString asExeName);
    void write_Type(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Type);
    //------------------------------------------------------------------------------
    AnsiString read_Format_FAT_range(AnsiString asSetupFile,AnsiString asExeName);
    void write_Format_FAT_range(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Format_FAT_range);
    //------------------------------------------------------------------------------
    AnsiString read_Format_FAT_Begin_Address(AnsiString asSetupFile,AnsiString asExeName);
    void write_Format_FAT_Begin_Address(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Format_FAT_Begin_Address);
    //------------------------------------------------------------------------------
    AnsiString read_Format_FAT_length(AnsiString asSetupFile,AnsiString asExeName);
    void write_Format_FAT_length(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Format_FAT_length);
    //------------------------------------------------------------------------------
    AnsiString read_NAND_Format_FAT_Begin_Address(AnsiString asSetupFile,AnsiString asExeName);
    void write_NAND_Format_FAT_Begin_Address(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_NAND_Format_FAT_Begin_Address);
    //------------------------------------------------------------------------------
    AnsiString read_NAND_Format_FAT_length(AnsiString asSetupFile,AnsiString asExeName);
    void write_NAND_Format_FAT_length(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Format_FAT_length);
    //------------------------------------------------------------------------------
    AnsiString read_Reset_to_factory_default_visible(AnsiString asSetupFile,AnsiString asExeName);
    void write_Reset_to_factory_default_visible(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Reset_to_factory_default_visible);
    //------------------------------------------------------------------------------
    AnsiString read_Erase_Validation(AnsiString asSetupFile,AnsiString asExeName);
    //------------------------------------------------------------------------------
//    AnsiString read_Pull_down_GPIO17(AnsiString asSetupFile,AnsiString asExeName);

    //------------------------------------------------------------------------------
    AnsiString read_BBChip_version_Checked(AnsiString asSetupFile,AnsiString asExeName);
    void write_BBChip_version_Checke(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_BBChip_version_Checked);

    //==============================================================================
    // NFB
    AnsiString read_BootLoader(AnsiString asSetupFile,AnsiString asExeName, int idx);
    void write_BootLoader(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_BootLoader);
    //------------------------------------------------------------------------------
    AnsiString read_BootLoaderEnable(AnsiString asSetupFile,AnsiString asExeName, int idx);
    void write_BootLoaderEnable(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_BootLoader);

    //==============================================================================
    // access
    AnsiString read_DataSource(AnsiString asSetupFile,AnsiString asExeName);
    void write_DataSource(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_DataSource);
    //------------------------------------------------------------------------------
    AnsiString read_DbLogEnable(AnsiString asSetupFile,AnsiString asExeName);
    void write_DbLogEnable(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_DbLogEnable);

    AnsiString read_USB_DL_With_Two_Side(AnsiString asSetupFile,AnsiString asExeName);
    void write_USB_DL_With_Two_Side(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_is_with);

    AnsiString read_EnterMetaModeAfterDLFMT(AnsiString asSetupFile,AnsiString asExeName);
    void write_EnterMetaModeAfterDLFMT(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_is_with);

    //==============================================================================
    // USB & UART
    /*---------------------------------------------------------------------------*/
    AnsiString  read_download_cable(AnsiString asSetupFile,AnsiString asExeName);
    void write_download_cable(AnsiString asSetupFile, AnsiString asExeName, AnsiString oper_method);

    AnsiString read_MDTLog(AnsiString asSetupFile,AnsiString asExeName);
    void write_MDTLog(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_MDTLog);
	AnsiString read_EnableUSB_2_0(AnsiString asSetupFile,AnsiString asExeName);
	void write_EnableUSB_2_0(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_EnableUSB_2_0);

    AnsiString read_EnableMMAA(AnsiString asSetupFile,AnsiString asExeName);
    void write_EnableMMAA(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_EnableMMAA);

    //=============================================================================
    //nvram backup partion
    AnsiString read_Enable_BackupNvramPartion(AnsiString asSetupFile,AnsiString asExeName);
	void write_Enable_BackupNvramPartion(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Enable_BackupNvramPartion);

    //Scatter file and load
    string read_sactter_file_num();
    void write_sactter_file_num(int num);

    void read_sactter_files_path(int size, vector<string> &paths);
    void write_sactter_files_path(string &path,int index);

    string read_sactter_loads_num(int idx);
    void write_sactter_loads_num(int idx, int num);

    void read_sactter_loads(int sact_idx, int size, vector<string> &info);
    void write_sactter_loads(int sact_idx, int load_idx,  string info);


    // EMI
    AnsiString read_bank0_auto(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_bank0_cfg(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_bank1_auto(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_bank1_cfg(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_nand_acccon(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_emi_gen_a(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_emi_gen_b(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_emi_gen_c(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_emi_dram_con_i_mode(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_emi_dram_con_i_ext_mode(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_emi_dram_con_k(AnsiString asSetupFile,AnsiString asExeName);
    AnsiString read_emi_dram_con_l(AnsiString asSetupFile,AnsiString asExeName);


    AnsiString read_device_id(AnsiString asSetupFile, AnsiString asExeName);
	void write_device_id(AnsiString asSetupFile, AnsiString asExeName, AnsiString asComportID);
	//add mtk71518 2013-07-17 for DualTalk
	AnsiString read_preloader_id(AnsiString asSetupFile, AnsiString asExeName);
	void write_preloader_id(AnsiString asSetupFile, AnsiString asExeName, AnsiString asPreloaderID);
	int read_SwitchToMode_DelayTime(AnsiString asSetupFile, AnsiString asExeName);
	void write_SwitchToMode_DelayTime(AnsiString asSetupFile, AnsiString asExeName, AnsiString asDelayTime);

    bool read_Delete_Calibration_After_RS(AnsiString asSetupFile, AnsiString asExeName);
    void write_Delete_Calibration_After_RS(AnsiString asSetupFile, AnsiString asExeName, bool flag);

    AnsiString read_CalibrationFolderNamingRule(AnsiString asSetupFile,AnsiString asExeName);
    void write_CalibrationFolderNamingRule(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_rule);

	AnsiString read_DownloadRetryCount(AnsiString asSetupFile,AnsiString asExeName);

};

#endif

