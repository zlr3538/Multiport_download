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
 *   INIFileHandle.cpp
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  INI file handling source file
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
 * Feb 4 2008 mtk00490
 * [STP100001633] [Multiport download tool] Multiport download tool ver 3.0804.0
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
#pragma hdrstop

#include <inifiles.hpp>



#ifndef _MULTIPORT_COMMON_H_
#include "multiport_common.h"
#endif



#include "INIFileHandle/inc/MultiPort_Utils.h"

#include "INIFileHandle/inc/INIFileHandle.h"

#define COM_PORT_TYPE_STR "COM port type"



//==============================================================================
AnsiString CINIFileHandle::read_field(AnsiString asSetupFile,AnsiString asExeName, AnsiString asSecName, AnsiString asFieldName, AnsiString asDefStr)
{
    AnsiString asPath;
    AnsiString as_str;
    if ( getPathFromStr(asExeName, asPath) &&
         withPath( asPath) &&
         !withPath( asSetupFile)
       )
    {
       asSetupFile = asPath + asSetupFile;
    }

    TIniFile *ini;

    try
    {
       ini = new TIniFile(asSetupFile);
       if(ini != NULL)
       {
           as_str  = ini->ReadString(asSecName, asFieldName, asDefStr);
           delete ini;
       }
    }
    catch (...)
    {
        ShowMessage( " read setup file " + asSetupFile + " error: " + asFieldName);
    }
    return as_str;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_field(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString asFieldName, AnsiString asStr)
{
    AnsiString asPath;
    if ( getPathFromStr(asExeName, asPath) && withPath( asPath) && !withPath( asSetupFile))
    {
       asSetupFile = asPath + asSetupFile;
    }

    TIniFile *ini;

    try
    {
        ini = new TIniFile( asSetupFile );

        if(ini != NULL)
        {
            ini->WriteString(asSecName, asFieldName, asStr );
            delete ini;
        }

    }
    catch (...)
    {
        ShowMessage( " write setup file : " + asSetupFile + " error" + asStr);
    }
}

//==============================================================================
int CINIFileHandle::read_bk_and_rs_cfg(AnsiString asSetupFile,AnsiString asExeName)
{
    int check;
    AnsiString as_check = read_field(asSetupFile, asExeName, "form", "Bk_And_Rs_Cgf", "0");

    try
    {
       check = as_check.ToInt();
    }
    catch(EConvertError &e)
    {
       check = 0;
    }
    catch(...)
    {
       check = 0;
    }
    return  check;
}

//----------------------------------------------------------------------------
void CINIFileHandle::write_bk_and_rs_cfg(AnsiString asSetupFile, AnsiString asExeName, int iCheck)
{
    AnsiString as_check;
    as_check =  IntToStr(iCheck);
    write_field(asSetupFile, asExeName, "form", "Bk_And_Rs_Cgf", as_check);
}

//----------------------------------------------------------------------------
AnsiString CINIFileHandle::read_Operation(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_Operation = read_field(asSetupFile, asExeName, "form", "Operation", "NOR");
    return  as_Operation;
}

//----------------------------------------------------------------------------
void CINIFileHandle::write_Operation(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Operation)
{
    write_field(asSetupFile, asExeName, "form", "Operation", as_Operation);
}

AnsiString  CINIFileHandle::read_download_cable(AnsiString asSetupFile,AnsiString asExeName)
{
   AnsiString as_Operation = read_field(asSetupFile, asExeName, "form", "Cable", "UART");
   return  as_Operation;
}

void CINIFileHandle::write_download_cable(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_cable)
{
   write_field(asSetupFile, asExeName, "form", "Cable", as_cable);
}

//==============================================================================
AnsiString CINIFileHandle::read_ComPortType(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_Operation = read_field(asSetupFile, asExeName, "form", COM_PORT_TYPE_STR, COM_PORT_UART_STR);
    return  as_Operation;
}

//----------------------------------------------------------------------------
void CINIFileHandle::write_ComPortType(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_com_type)
{
    write_field(asSetupFile, asExeName, "form", COM_PORT_TYPE_STR, as_com_type);
}

//==============================================================================
AnsiString CINIFileHandle::read_DA_bin(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_DA_bin = read_field(asSetupFile, asExeName, "form","DA_bin", "MTK_AllInOne_DA.bin");
    return  as_DA_bin;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_DA_bin(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_DA_bin)
{
    write_field(asSetupFile, asExeName, "form", "DA_bin", as_DA_bin);
}

//==============================================================================
AnsiString CINIFileHandle::read_AuthFile(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_AuthFile = read_field(asSetupFile, asExeName, "form", "Auth file", "");
    return  as_AuthFile;
}
//-----------------------------------------------------------------------------------
AnsiString CINIFileHandle::read_RootCertFile(AnsiString asSetupFile,AnsiString asExeName)
{
  AnsiString as_AuthFile = read_field(asSetupFile, asExeName, "form", "RootCert File", "");
  return  as_AuthFile;
}
//-----------------------------------------------------------------------------------
void CINIFileHandle::write_RootCertFile(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_RootCertFile)
{
    write_field(asSetupFile, asExeName, "form", "RootCert File", as_RootCertFile);
}
//-----------------------------------------------------------------------------------
AnsiString CINIFileHandle::read_CertificateFile(AnsiString asSetupFile,AnsiString asExeName)
{
  AnsiString as_AuthFile = read_field(asSetupFile, asExeName, "form", "Certificate File ", "");
  return  as_AuthFile;
}
//-----------------------------------------------------------------------------------
void CINIFileHandle::write_CertificateFile(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_CertificateFile)
{
    write_field(asSetupFile, asExeName, "form", "Certificate File ", as_CertificateFile);
}
//-----------------------------------------------------------------------------------

void CINIFileHandle::write_AuthFile(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_AuthFile)
{
    write_field(asSetupFile, asExeName, "form", "Auth file", as_AuthFile);
}

//==============================================================================
AnsiString CINIFileHandle::read_Scatter( AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_Scatter = read_field(asSetupFile, asExeName, "form", "Scatter_Folder", "");
    return  as_Scatter;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_Scatter(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Scatter)
{
    write_field(asSetupFile, asExeName, "form", "Scatter_Folder", as_Scatter);
}

//==============================================================================
AnsiString CINIFileHandle::read_ROM(AnsiString asSetupFile,AnsiString asExeName, int idx)
{
    AnsiString as_KEY_NAME = "ROM" + IntToStr(idx);
    AnsiString as_ROM = read_field(asSetupFile, asExeName, "form", as_KEY_NAME, "MT6205B.bin");
    return  as_ROM;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_ROM(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_ROM)
{
    AnsiString as_KEY_NAME = "ROM" + IntToStr(idx);
    write_field(asSetupFile, asExeName, "form", as_KEY_NAME, as_ROM);
}

//==============================================================================
AnsiString CINIFileHandle::read_FAT(AnsiString asSetupFile,AnsiString asExeName, int idx)
{
    AnsiString as_KEY_NAME = "FAT" + IntToStr(idx);
    AnsiString as_FAT = read_field(asSetupFile, asExeName, "form", as_KEY_NAME, "MT6205B_FAT.bin");
    return  as_FAT;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_FAT(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_FAT)
{
    AnsiString as_KEY_NAME = "FAT" + IntToStr(idx);
    write_field(asSetupFile, asExeName, "form", as_KEY_NAME, as_FAT);
}

//==============================================================================
AnsiString CINIFileHandle::read_SEC_RO(AnsiString asSetupFile,AnsiString asExeName, int idx)
{
    AnsiString as_KEY_NAME = "SEC_RO" + IntToStr(idx);
    AnsiString as_SEC_RO = read_field(asSetupFile, asExeName, "form", as_KEY_NAME, "SECURE_RO");
    return  as_SEC_RO;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_SEC_RO(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_SEC_RO)
{
    AnsiString as_KEY_NAME = "SEC_RO" + IntToStr(idx) ;
    write_field(asSetupFile, asExeName, "form", as_KEY_NAME, as_SEC_RO);
}

//==============================================================================
AnsiString CINIFileHandle::read_BBChip_version_Checked(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_KEY_NAME = "BBChip_Ver_Checked";
    AnsiString as_BBChip_version_Checked = read_field(asSetupFile, asExeName, "form", as_KEY_NAME, "yes");
    return  as_BBChip_version_Checked;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_BBChip_version_Checke(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_BBChip_version_Checked)
{
    AnsiString as_KEY_NAME = "BBChip_Ver_Checked";
    write_field(asSetupFile, asExeName, "form", as_KEY_NAME, as_BBChip_version_Checked);
}

//==============================================================================
AnsiString CINIFileHandle::read_SEC_RO_Checked(AnsiString asSetupFile,AnsiString asExeName, int idx)
{
    AnsiString as_KEY_NAME = "SEC_RO" + IntToStr(idx) + " chekced";
    AnsiString as_SEC_RO_Checked = read_field(asSetupFile, asExeName, "form", as_KEY_NAME, "yes");
    return  as_SEC_RO_Checked;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_SEC_RO_Checked(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_SEC_RO_Checked)
{
    AnsiString as_KEY_NAME = "SEC_RO" + IntToStr(idx) + " chekced";
    write_field(asSetupFile, asExeName, "form", as_KEY_NAME, as_SEC_RO_Checked);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
AnsiString CINIFileHandle::read_GPS_ROM_Path(AnsiString asSetupFile,AnsiString asExeName, int idx)
{
    AnsiString as_KEY_NAME = "GPS ROM Path" + IntToStr(idx);
    AnsiString as = read_field(asSetupFile, asExeName, "form", as_KEY_NAME, "GPS_ROM");
    return  as;
}
*/
//===========================================================================
//////////////////////////// backup and restore /////////////////////////////
//===========================================================================
AnsiString CINIFileHandle::read_BackupAndRestoreOp(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as = read_field(asSetupFile, asExeName, "form", "Backup and restore option", "download without backup and restore calibration data");
    return  as;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_BackupAndRestoreOp(AnsiString asSetupFile, AnsiString asExeName, AnsiString as)
{
    write_field(asSetupFile, asExeName, "form", "Backup and restore option", as);
}

/*
//---------------------------------------------------------------------------
void CINIFileHandle::write_GPS_ROM_Path(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as)
{
    AnsiString as_KEY_NAME = "GPS ROM Path" + IntToStr(idx) ;
    write_field(asSetupFile, asExeName, "form", as_KEY_NAME, as);
}


//==============================================================================
AnsiString CINIFileHandle::read_GPS_ROM_Checked(AnsiString asSetupFile,AnsiString asExeName, int idx)
{
    AnsiString as_KEY_NAME = "GPS_ROM" + IntToStr(idx) + " chekced";
    AnsiString as = read_field(asSetupFile, asExeName, "form", as_KEY_NAME, "yes");
    return  as;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_GPS_ROM_Checked(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as)
{
    AnsiString as_KEY_NAME = "GPS_ROM" + IntToStr(idx) + " chekced";
    write_field(asSetupFile, asExeName, "form", as_KEY_NAME, as);
}
*/

//==============================================================================
AnsiString CINIFileHandle::read_TheFirstComPortNo(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_FirstComPortNo = read_field(asSetupFile, asExeName, "form","TheFirstComPortNo", "3");
    return  as_FirstComPortNo;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_TheFirstComPortNo(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_TheFirstComPortNo)
{
    write_field(asSetupFile, asExeName, "form", "TheFirstComPortNo", as_TheFirstComPortNo);
}

//==============================================================================
AnsiString CINIFileHandle::read_ComEnabled(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_ComEnabled = read_field(asSetupFile, asExeName, "form","ComportEnabled", "1");
    return  as_ComEnabled;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_ComEnabled(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_ComportEnabled)
{
    write_field(asSetupFile, asExeName, "form", "ComportEnabled", as_ComportEnabled);
}

//==============================================================================
AnsiString CINIFileHandle::read_USB_DL_With_Two_Side(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_SEC_RO_Checked = read_field(asSetupFile, asExeName, "form", "USB DL With Two Site", "no");
    return  as_SEC_RO_Checked;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_USB_DL_With_Two_Side(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_is_with)
{
    write_field(asSetupFile, asExeName, "form", "USB DL With Two Site", as_is_with);
}


//==============================================================================
AnsiString CINIFileHandle::read_EnterMetaModeAfterDLFMT(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_enter = read_field(asSetupFile, asExeName, "form", "Enter Meta Mode After DL/FMT", "no");
    return  as_enter;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_EnterMetaModeAfterDLFMT(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_is_with)
{
    write_field(asSetupFile, asExeName, "form", "Enter Meta Mode After DL/FMT", as_is_with);
}

//==============================================================================
AnsiString CINIFileHandle::read_CalibrationFolderNamingRule(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_rule = read_field(asSetupFile, asExeName, "form", "CalibrationFolderNaming", "RID");
    return  as_rule;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_CalibrationFolderNamingRule(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_rule)
{
    write_field(asSetupFile, asExeName, "form", "CalibrationFolderNaming", as_rule);
}



bool CINIFileHandle::read_Delete_Calibration_After_RS(AnsiString asSetupFile, AnsiString asExeName)
{
    AnsiString as_flag = read_field(asSetupFile, asExeName, "form", "DeleteCalibrationFolderAfterRS", "0");

    if(as_flag.AnsiCompare("0") == 0)
    {
        return false;
    }
    else
    {
        return true;
    }

}

void CINIFileHandle::write_Delete_Calibration_After_RS(AnsiString asSetupFile, AnsiString asExeName, bool flag)
{
    if(flag)
    {
        write_field(asSetupFile, asExeName, "form", "DeleteCalibrationFolderAfterRS", "1");
    }
    else
    {
        write_field(asSetupFile, asExeName, "form", "DeleteCalibrationFolderAfterRS", "0");
    }

}


AnsiString CINIFileHandle::read_DownloadRetryCount(AnsiString asSetupFile, AnsiString asExeName) //usb wo battery
{
	AnsiString as_downloadretrycount = read_field(asSetupFile, asExeName, "DOWNLOAD", "download_retry_times", "2");
	   return  as_downloadretrycount;

}


bool CINIFileHandle::read_Disconnect_Comport_After_DL(AnsiString asSetupFile, AnsiString asExeName)
{
    AnsiString as_flag = read_field(asSetupFile, asExeName, "form", "DisconnectUSBComportAfterDownload", "0");

    if(as_flag.AnsiCompare("0") == 0)
    {
        return false;
    }
    else
    {
        return true;
    }

}

void CINIFileHandle::write_Disconnect_Comport_After_DL(AnsiString asSetupFile, AnsiString asExeName, bool flag)
{
    if(flag)
    {
        write_field(asSetupFile, asExeName, "form", "DisconnectUSBComportAfterDownload", "1");
    }
    else
    {
        write_field(asSetupFile, asExeName, "form", "DisconnectUSBComportAfterDownload", "0");
    }

}


//==============================================================================
bool CINIFileHandle::read_ComPortSetting(AnsiString asSetupFile,AnsiString asExeName, vector<AnsiString> &vAs)
{

    for(int i=0; i<MAX_SUPPORT_PORT_NUM; i++)
    {
         AnsiString as_COM = read_field(asSetupFile, asExeName, "COM port setting", "COM_ENUM"+IntToStr(i+1), "0xFF");
         if( as_COM.AnsiCompareIC("0xFF") != 0 )
         {
             vAs.push_back(as_COM);
         }
    }

    return true;
}

//--------------------------------------------------------------------------
void CINIFileHandle::write_ComPortSetting(AnsiString asSetupFile, AnsiString asExeName, vAsniString &vAs)
{
    int i;
    vector<AnsiString>:: iterator iter;
    AnsiString  as;

    for( i=0, iter = vAs.begin(); i<MAX_SUPPORT_PORT_NUM, iter != vAs.end(); i++, iter++)
    {
        as=*iter;
        write_field(asSetupFile, asExeName, "COM port setting", "COM_ENUM"+IntToStr(i+1), as);
    }
}

//==============================================================================
AnsiString CINIFileHandle::read_AutoPollingEnabled(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_AutoPollingEnabled = read_field(asSetupFile, asExeName, "form", "Auto polling enabled", "0xFF");
    return  as_AutoPollingEnabled;
}

//--------------------------------------------------------------------------
void CINIFileHandle::write_AutoPollingEnabled(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_AutoPollingEnabled)
{
    write_field(asSetupFile, asExeName, "form", "Auto polling enabled", as_AutoPollingEnabled);
}

/*
//==============================================================================
AnsiString CINIFileHandle::read_LV_FAT_index( AnsiString asSetupFile, AnsiString asExeName, int idx )
{
    AnsiString as_KEY_NAME = "rom_info_FAT_index" + IntToStr( idx );
    AnsiString as_LV_FAT_index = read_field(asSetupFile, asExeName, "Download", as_KEY_NAME, "0");
    return  as_LV_FAT_index;
}

//-----------------------------------------------------------------------------
void CINIFileHandle::write_LV_FAT_index(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_LV_FAT_index)
{
    AnsiString as_KEY_NAME = "rom_info_FAT_index" + IntToStr( idx );
    write_field(asSetupFile, asExeName, "Download", as_KEY_NAME, as_LV_FAT_index);
}

//==============================================================================
AnsiString CINIFileHandle::read_LV_count(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_LV_count = read_field(asSetupFile, asExeName, "Download", "rom_info_count", "0");
    return  as_LV_count;
}

//--------------------------------------------------------------------------
void CINIFileHandle::write_LV_count(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_count)
{
    write_field(asSetupFile, asExeName, "Download", asSecName, as_LV_count);
}

//==============================================================================
AnsiString CINIFileHandle::read_LV_name(AnsiString asSetupFile,AnsiString asExeName, int index)
{
    AnsiString as_LV_name = read_field(asSetupFile, asExeName, "Download", "rom_info_name"+IntToStr(index), "");
    return  as_LV_name;
}

//--------------------------------------------------------------------------
void CINIFileHandle::write_LV_name(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_name)
{
    write_field(asSetupFile, asExeName, "Download", asSecName, as_LV_name);
}

//==============================================================================
void CINIFileHandle::write_LV_region_addr(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_region_addr)
{
    write_field(asSetupFile, asExeName, "Download", asSecName, as_LV_region_addr);
}

//==============================================================================
void CINIFileHandle::write_LV_begin_addr(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_begin_addr)
{
    write_field(asSetupFile, asExeName, "Download", asSecName, as_LV_begin_addr);
}

//==============================================================================
void CINIFileHandle::write_LV_end_addr(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_end_addr)
{
    write_field(asSetupFile, asExeName, "Download", asSecName, as_LV_end_addr);
}

//==============================================================================
void CINIFileHandle::write_LV_location(AnsiString asSetupFile, AnsiString asExeName, AnsiString asSecName, AnsiString as_LV_location)
{
    write_field(asSetupFile, asExeName, "Download", asSecName, as_LV_location);
}
*/
//==============================================================================
AnsiString CINIFileHandle::read_Baseband_chip(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_Baseband_chip = read_field(asSetupFile, asExeName, "form","Baseband chip", "6205B");
    return  as_Baseband_chip;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_Baseband_chip(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Baseband_chip)
{
    write_field(asSetupFile, asExeName, "form", "Baseband chip", as_Baseband_chip);
}

//==========================================================================================
AnsiString CINIFileHandle::read_External_clock(AnsiString asSetupFile,AnsiString asExeName)
{
//Only support External Clock 26 M //On 11-4-19
/*
    AnsiString as_External_clock = read_field(asSetupFile, asExeName, "form","External clock", "26 mhz");
    return  as_External_clock;
*/
    return "26mhz";
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_External_clock(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_External_clock)
{
//Only support External Clock 26 M //On 11-4-19
/*
    write_field(asSetupFile, asExeName, "form", "External clock", as_External_clock);
*/
    //do nothing..
}

//==============================================================================
AnsiString CINIFileHandle::read_CheckECOVersion(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_CheckECOVersion = read_field(asSetupFile, asExeName, "form", "Check ECO version", "yes");
    return  as_CheckECOVersion;
}

//--------------------------------------------------------------------------
void CINIFileHandle::write_CheckECOVersion(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_CheckECOVersion)
{
    write_field(asSetupFile, asExeName, "form", "Check ECO version", as_CheckECOVersion);
}

//==============================================================================
AnsiString CINIFileHandle::read_OperateFlashType(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_CheckECOVersion = read_field(asSetupFile, asExeName, "form", "OperateFlashType", "NAND");
    return  as_CheckECOVersion;
}

//--------------------------------------------------------------------------
void CINIFileHandle::write_OperateFlashType(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_OperateFlashType)
{
    write_field(asSetupFile, asExeName, "form", "OperateFlashType", as_OperateFlashType);
}

AnsiString CINIFileHandle::read_CheckEnableNFI(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_CheckEnableNFI = read_field(asSetupFile, asExeName, "form", "Check Enable NFI", "no");
    return  as_CheckEnableNFI;
}

void CINIFileHandle::write_CheckEnableNFI(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_CheckEnableNFI)
{
    write_field(asSetupFile, asExeName, "form", "Check Enable NFI", as_CheckEnableNFI);
}



//==============================================================================
//////////////////////////     Multi-bin option     ////////////////////////////
//==============================================================================
AnsiString CINIFileHandle::read_CheckTgtResLayout(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_CheckTgtResLayout = read_field(asSetupFile, asExeName, "form", "Check target resource layout", "yes");
    return  as_CheckTgtResLayout;
}

//----------------------------------------------------------------------------
void CINIFileHandle::write_CheckTgtResLayout(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_CheckTgtResLayout)
{
    write_field(asSetupFile, asExeName, "form", "Check target resource layout", as_CheckTgtResLayout);
}

//==============================================================================
AnsiString CINIFileHandle::read_AutoLoadResByScat(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_AutoLoadResByScat = read_field(asSetupFile, asExeName, "form", "Auto load resource by scat", "yes");
    return  as_AutoLoadResByScat;
}

//----------------------------------------------------------------------------
void CINIFileHandle::write_AutoLoadResByScat(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_AutoLoadResByScat)
{
    write_field(asSetupFile, asExeName, "form", "Auto load resource by scat", as_AutoLoadResByScat);
}

//==============================================================================
AnsiString CINIFileHandle::read_CompareResProjectId(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_CompareResProjectId = read_field(asSetupFile, asExeName, "form", "Compare resoure project ID", "yes");
    return  as_CompareResProjectId;
}

//----------------------------------------------------------------------------
void CINIFileHandle::write_CompareResProjectId(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_CompareResProjectId)
{
    write_field(asSetupFile, asExeName, "form", "Compare resoure project ID", as_CompareResProjectId);
}

//==============================================================================
AnsiString CINIFileHandle::read_BROMDllLog(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_BROMDllLog = read_field(asSetupFile, asExeName, "form", "BROM_DLL logging", "yes");
    return  as_BROMDllLog;
}

//----------------------------------------------------------------------------
void CINIFileHandle::write_BROMDllLog(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_BROMDllLog)
{
    write_field(asSetupFile, asExeName, "form", "BROM_DLL logging", as_BROMDllLog);
}

//==============================================================================
AnsiString CINIFileHandle::read_MDTLog(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_MDTLog = read_field(asSetupFile, asExeName, "form", "MDT_DLL logging", "yes");
    return  as_MDTLog;
}

//----------------------------------------------------------------------------
void CINIFileHandle::write_MDTLog(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_MDTLog)
{
    write_field(asSetupFile, asExeName, "form", "MDT_DLL logging", as_MDTLog);
}

AnsiString CINIFileHandle::read_EnableMMAA(AnsiString asSetupFile,AnsiString asExeName)
{
    return read_field(asSetupFile, asExeName, "form", "EnableMMAA", "no");
}

void CINIFileHandle::write_EnableMMAA(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_EnableMMAA)
{
    write_field(asSetupFile, asExeName, "form", "EnableMMAA", as_EnableMMAA);
}


//==============================================================================
AnsiString CINIFileHandle::read_METADllLog(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_METADllLog = read_field(asSetupFile, asExeName, "form", "META_DLL logging", "yes");
    return  as_METADllLog;
}

//----------------------------------------------------------------------------
void CINIFileHandle::write_METADllLog(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_METADllLog)
{
    write_field(asSetupFile, asExeName, "form", "META_DLL logging", as_METADllLog);
}

//==============================================================================
AnsiString CINIFileHandle::read_EnableUSB_2_0(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_EnableUSB_2_0 = read_field(asSetupFile, asExeName, "form", "Enable USB 11_to_20", "yes");
    return  as_EnableUSB_2_0;
}

//----------------------------------------------------------------------------
void CINIFileHandle::write_EnableUSB_2_0(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_EnableUSB_2_0)
{
    write_field(asSetupFile, asExeName, "form", "Enable USB 11_to_20", as_EnableUSB_2_0);
}

/*
Function: Read "Backup Nvram partition" initial UI form option from ini file
*/
AnsiString CINIFileHandle::read_Enable_BackupNvramPartion(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_Enable_BackupNvramPartion = read_field(asSetupFile, asExeName, "form", "backup_nvram_partition", "no");
    return  as_Enable_BackupNvramPartion;
}

void CINIFileHandle::write_Enable_BackupNvramPartion(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Enable_BackupNvramPartion)
{
    write_field(asSetupFile, asExeName, "form", "backup_nvram_partition", as_Enable_BackupNvramPartion);
}

//==============================================================================
AnsiString CINIFileHandle::read_Baudrate(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_baudrate = read_field(asSetupFile, asExeName, "form", "Baudrate", "921600");
    return  as_baudrate;

}

//---------------------------------------------------------------------------
void CINIFileHandle::write_Baudrate(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Baudrate)
{
    write_field(asSetupFile, asExeName, "form", "Baudrate", as_Baudrate );
}

//==========================================================================================
AnsiString CINIFileHandle::read_Type(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_Type = read_field(asSetupFile, asExeName, "form", "Type", "Download ROM and FAT");
    return  as_Type;


}

//---------------------------------------------------------------------------
void CINIFileHandle::write_Type(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Type)
{
    write_field(asSetupFile, asExeName, "form", "Type", as_Type );
}

//==========================================================================================
AnsiString CINIFileHandle::read_Format_FAT_range(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_FormatFat = read_field(asSetupFile, asExeName, "form", "Format FAT range", "auto");
    return  as_FormatFat;

}

//---------------------------------------------------------------------------
void CINIFileHandle::write_Format_FAT_range(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Format_FAT_range)
{
    write_field(asSetupFile, asExeName, "form", "Format FAT range", as_Format_FAT_range );
}

//==========================================================================================
AnsiString CINIFileHandle::read_Format_FAT_Begin_Address(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString Format_FAT_Begin_Address = read_field(asSetupFile, asExeName, "form", "Format FAT begin address", "0x00700000");
    return  Format_FAT_Begin_Address;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_Format_FAT_Begin_Address(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Format_FAT_Begin_Address)
{
    write_field(asSetupFile, asExeName, "form", "Format FAT begin address", as_Format_FAT_Begin_Address );
}

//==========================================================================================
AnsiString CINIFileHandle::read_Format_FAT_length(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString Format_FAT_length = read_field(asSetupFile, asExeName, "form", "Format FAT length", "0x00100000");
    return  Format_FAT_length;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_Format_FAT_length(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Format_FAT_length)
{
    write_field(asSetupFile, asExeName, "form", "Format FAT length", as_Format_FAT_length );
}


//---------------------------------------------------------------------------
AnsiString CINIFileHandle::read_device_id(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString deviceid = read_field(asSetupFile, asExeName, "form", "Com port filter", "VID_0E8D&PID_0003");
    return  deviceid;
}

void CINIFileHandle::write_device_id(AnsiString asSetupFile, AnsiString asExeName, AnsiString asComportID)
{
    write_field(asSetupFile, asExeName, "form", "Com port filter", asComportID );
}

//---------------------------------------------------------------------------
//add mtk71518 2013-07-17 for DualTalk 
AnsiString CINIFileHandle::read_preloader_id(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString deviceid = read_field(asSetupFile, asExeName, "form", "Preloader USB filter", "VID_0E8D&PID_2000");
    return  deviceid;
}

void CINIFileHandle::write_preloader_id(AnsiString asSetupFile, AnsiString asExeName, AnsiString asPreloaderID)
{
    write_field(asSetupFile, asExeName, "form", "Preloader USB filter", asPreloaderID );
}


//---------------------------------------------------------------------------
//add mtk71518 2013-07-17 for DualTalk 
int CINIFileHandle::read_SwitchToMode_DelayTime(AnsiString asSetupFile, AnsiString asExeName)
{
    int iDelayTime; 

    AnsiString as_DelayTime = read_field(asSetupFile, asExeName, "form", "Switch to modem delay time", "500");
    try
    {
       iDelayTime = as_DelayTime.ToInt();
    }
    catch(EConvertError &e)
    {
       iDelayTime = 500;
    }
    catch(...)
    {
       iDelayTime = 500;
    }
    return iDelayTime;
}

void CINIFileHandle::write_SwitchToMode_DelayTime(AnsiString asSetupFile, AnsiString asExeName, AnsiString asDelayTime)
{
    write_field(asSetupFile, asExeName, "form", "Switch to modem delay time", asDelayTime );
}


//==========================================================================================
AnsiString CINIFileHandle::read_NAND_Format_FAT_Begin_Address(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString NAND_Format_FAT_Begin_Address = read_field(asSetupFile, asExeName, "form", "NAND format FAT begin address", "0x00000000");
    return  NAND_Format_FAT_Begin_Address;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_NAND_Format_FAT_Begin_Address(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_NAND_Format_FAT_Begin_Address)
{
    write_field(asSetupFile, asExeName, "form", "NAND format FAT begin address", as_NAND_Format_FAT_Begin_Address );
}

//==========================================================================================
AnsiString CINIFileHandle::read_NAND_Format_FAT_length(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString NAND_Format_FAT_length = read_field(asSetupFile, asExeName, "form", "NAND format FAT length", "0x08000000");
    return  NAND_Format_FAT_length;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_NAND_Format_FAT_length(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_NAND_Format_FAT_length)
{
    write_field(asSetupFile, asExeName, "form", "NAND format FAT length", as_NAND_Format_FAT_length );
}

//==========================================================================================
AnsiString CINIFileHandle::read_Reset_to_factory_default_visible(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_Reset_to_factory_default_visible = read_field(asSetupFile, asExeName, "form", "Reset to factory default visible", "yes");
    return  as_Reset_to_factory_default_visible;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_Reset_to_factory_default_visible(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_Reset_to_factory_default_visible)
{
    write_field(asSetupFile, asExeName, "form", "Reset to factory default visible", as_Reset_to_factory_default_visible );
}

//=============================================================================
AnsiString CINIFileHandle::read_Erase_Validation(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_Erase_Validation = read_field(asSetupFile, asExeName, "FORM", "erase_validation", "no");
    return  as_Erase_Validation;
}


//==========================================================================================
/*
AnsiString CINIFileHandle::read_Pull_down_GPIO17(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString Format_FAT_length = read_field(asSetupFile, asExeName, "form", "Pull down GPIO17", "yes");
    return  Format_FAT_length;
}
*/
//=============================================================================
///////////////////////////          NFB           ////////////////////////////
//=============================================================================
AnsiString CINIFileHandle::read_BootLoader(AnsiString asSetupFile,AnsiString asExeName, int idx )
{
    AnsiString as_KEY_NAME = "bloader" + IntToStr(idx);
    AnsiString as_BootLoader = read_field(asSetupFile, asExeName, "NFB", as_KEY_NAME, "");
    return  as_BootLoader;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_BootLoader(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_BootLoader)
{
    AnsiString as_KEY_NAME = "bloader" + IntToStr(idx);
    write_field(asSetupFile, asExeName, "NFB", as_KEY_NAME, as_BootLoader );
}

//=============================================================================
AnsiString CINIFileHandle::read_BootLoaderEnable(AnsiString asSetupFile,AnsiString asExeName, int idx)
{
    AnsiString as_KEY_NAME = "bloader_enable" + IntToStr(idx);
    AnsiString as_BootLoaderEnable = read_field(asSetupFile, asExeName, "NFB", as_KEY_NAME, "yes");
    return  as_BootLoaderEnable;
}

//---------------------------------------------------------------------------
void CINIFileHandle::write_BootLoaderEnable(AnsiString asSetupFile, AnsiString asExeName, int idx, AnsiString as_BootLoader_Enable)
{
    AnsiString as_KEY_NAME = "bloader_enable" + IntToStr(idx);
    write_field(asSetupFile, asExeName, "NFB", as_KEY_NAME, as_BootLoader_Enable );
}

//=============================================================================
///////////////////////////        Access          ////////////////////////////
//=============================================================================
AnsiString CINIFileHandle::read_DataSource(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_DataSource = read_field(asSetupFile, asExeName, "Access", "data source", "MTK_DATABASE.mdb");
    return  as_DataSource;
}

//------------------------------------------------------------------------------
void CINIFileHandle::write_DataSource(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_DataSource)
{
    write_field(asSetupFile, asExeName, "Access", "data source", as_DataSource);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_DbLogEnable(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_DataSource = read_field(asSetupFile, asExeName, "Access", "Database logging enable", "no");
    return  as_DataSource;
}

//------------------------------------------------------------------------------
void CINIFileHandle::write_DbLogEnable(AnsiString asSetupFile, AnsiString asExeName, AnsiString as_DbLogEnable)
{
    write_field(asSetupFile, asExeName, "Access", "Database logging enable", as_DbLogEnable);
}

//=============================================================================
/////////////////////////////        EMI     //////////////////////////////////
//=============================================================================
AnsiString CINIFileHandle::read_bank0_auto(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_bank0_auto = read_field(asSetupFile, asExeName, "EMI", "bank0_auto", "yes");
    return  as_bank0_auto;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_bank0_cfg(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_bank0_cfg = read_field(asSetupFile, asExeName, "EMI", "bank0_cfg", "0x00004102");
    return  as_bank0_cfg;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_bank1_auto(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_bank1_auto = read_field(asSetupFile, asExeName, "EMI", "bank1_auto", "yes");
    return  as_bank1_auto;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_bank1_cfg(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_bank1_cfg = read_field(asSetupFile, asExeName, "EMI", "bank1_cfg", "0x00004102");
    return  as_bank1_cfg;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_nand_acccon(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_nand_acccon = read_field(asSetupFile, asExeName, "EMI", "nand_acccon", "0x000007FF");
    return  as_nand_acccon;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_emi_gen_a(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_emi_gen_a = read_field(asSetupFile, asExeName, "EMI", "emi_gen_a", "0x568996A2");
    return  as_emi_gen_a;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_emi_gen_b(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_emi_gen_b = read_field(asSetupFile, asExeName, "EMI", "emi_gen_b", "0x5B8A69DA");
    return  as_emi_gen_b;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_emi_gen_c(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_emi_gen_c = read_field(asSetupFile, asExeName, "EMI", "emi_gen_c", "0x00000000");
    return  as_emi_gen_c;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_emi_dram_con_i_mode(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_emi_dram_con_i_mode = read_field(asSetupFile, asExeName, "EMI", "emi_dram_con_i_mode", "0x03A90223");
    return  as_emi_dram_con_i_mode;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_emi_dram_con_i_ext_mode(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_emi_dram_con_i_ext_mode = read_field(asSetupFile, asExeName, "EMI", "emi_dram_con_i_ext_mode", "0x03A94000");
    return  as_emi_dram_con_i_ext_mode;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_emi_dram_con_k(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_emi_dram_con_k = read_field(asSetupFile, asExeName, "EMI", "emi_dram_con_k", "0x50004564");
    return  as_emi_dram_con_k;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString CINIFileHandle::read_emi_dram_con_l(AnsiString asSetupFile,AnsiString asExeName)
{
    AnsiString as_emi_dram_con_l = read_field(asSetupFile, asExeName, "EMI", "emi_dram_con_l", "0x04107777");
    return  as_emi_dram_con_l;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string CINIFileHandle::read_sactter_file_num()
{
   return read_field("MultiPortFlashDownloadProject.ini", Application->ExeName,
                     "SCATTER AND LOADS", "SCATTER_NUM", "0").c_str();
}

void CINIFileHandle::write_sactter_file_num(int num)
{
    write_field("MultiPortFlashDownloadProject.ini", Application->ExeName,
                "SCATTER AND LOADS", "SCATTER_NUM",  IntToStr(num));
}

string CINIFileHandle::read_sactter_loads_num(int idx)
{
   string key_name;

   key_name = "SCATTER_LODS_NUM";
   key_name += IntToStr(idx).c_str();

  return read_field("MultiPortFlashDownloadProject.ini", Application->ExeName,
                    "SCATTER AND LOADS", key_name.c_str(), "0").c_str();
}

void CINIFileHandle::write_sactter_loads_num(int idx, int num)
{
   string key_name;

   key_name = "SCATTER_LODS_NUM";
   key_name += IntToStr(idx).c_str();

   write_field("MultiPortFlashDownloadProject.ini", Application->ExeName,
                "SCATTER AND LOADS", key_name.c_str(),  IntToStr(num));
}


void CINIFileHandle::read_sactter_files_path(int size, vector<string> &paths)
{
    string key_name, path;

    for(int i=0; i<size; i++)
    {
       key_name = "sactter_file_";
       key_name += IntToStr(i).c_str();

       path =  read_field("MultiPortFlashDownloadProject.ini", Application->ExeName,
                          "SCATTER AND LOADS", key_name.c_str(), "").c_str();

       paths.push_back(path);
    }
}

void CINIFileHandle::write_sactter_files_path(string &path,int index)
{
#if 0
    string key_name;

   key_name = "sactter_file_";
   key_name += IntToStr(index, it)).c_str();

   write_field("MultiPortFlashDownloadProject.ini", Application->ExeName,
               "SCATTER AND LOADS", key_name.c_str(),  (*it).c_str());
#endif
}

void CINIFileHandle::write_sactter_loads(int sact_idx, int load_idx,  string info)
{
   string key_name;

   key_name = "sactter_load_";
   key_name += IntToStr(sact_idx).c_str();
   key_name += "_";
   key_name += IntToStr(load_idx).c_str();

   write_field("MultiPortFlashDownloadProject.ini", Application->ExeName,
                "SCATTER AND LOADS", key_name.c_str(),  info.c_str());
}

void CINIFileHandle::read_sactter_loads(int sact_idx, int size, vector<string> &infos)
{
    string key_name, info;

    for(int i=0; i<size; i++)
    {
       key_name = "sactter_load_";
       key_name += IntToStr(sact_idx).c_str();
       key_name += "_";
       key_name += IntToStr(i).c_str();

       info = read_field("MultiPortFlashDownloadProject.ini", Application->ExeName,
                  "SCATTER AND LOADS", key_name.c_str(),  "").c_str();

       infos.push_back(info);
    }
}
