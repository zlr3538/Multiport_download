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
 *   form_MultiLoad.cpp
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  Multi-load form source file
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
 * Jun 21 2006 MTK00490
 * [STP100000939] Multiport download Tool_v2.9.1001
 * 
 * 
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

//---------------------------------------------------------------------------

#if 0 //for this is no use now

#include <vcl.h>
#pragma hdrstop

#include <inifiles.hpp>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>


// common
#ifndef _MULTIPORT_COMMON_H_
#include "multiport_common.h"
#endif

// form
#ifndef _MUTLIPORTFLASHDOWNLOADTOOL_H_
#include "MultiPortFlashDownloadTool.h"
#endif

#include "form_MultiLoad.h"

#ifndef	_FLASHTOOL_HANDLE_H_
#include "flashtool_handle.h"
#endif

typedef enum {
	 LV_BOOTLOADER = 0
        ,LV_EXBOOTLOADER
	,LV_NFB_DL_ROM
	,LV_DL_ROM
	,LV_OTP
	,LV_FTCFG
	,LV_SEC_RO
	,LV_CUST_PARA
        ,LV_GPS_ROM
} E_LISTVIEW_ITEM_TYPE;

E_LISTVIEW_ITEM_TYPE g_LV_ItemType[] =
{
    LV_BOOTLOADER
    ,LV_EXBOOTLOADER
    ,LV_NFB_DL_ROM
    ,LV_DL_ROM
    ,LV_OTP
    ,LV_FTCFG
    ,LV_SEC_RO
    ,LV_CUST_PARA
    ,LV_GPS_ROM
};
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMultiLoad *frmMultiLoad;
//extern struct DL_HANDLE	*g_DL_HANDLE;
extern struct DA_HANDLE	*g_DA_HANDLE;

//---------------------------------------------------------------------------
__fastcall TfrmMultiLoad::TfrmMultiLoad(TComponent* Owner)
        : TForm(Owner)
{
    m_lv[0] = lv1;
    m_lv[1] = lv2;
    m_lv[2] = lv3;
    m_lv[3] = lv4;

    m_lvPar[0] = lvPar1;
    m_lvPar[1] = lvPar2;
    m_lvPar[2] = lvPar3;
    m_lvPar[3] = lvPar4;

    m_lblScatFileName[0] = lblScatFileName1;
    m_lblScatFileName[1] = lblScatFileName2;
    m_lblScatFileName[2] = lblScatFileName3;
    m_lblScatFileName[3] = lblScatFileName4;

    m_dlgOpenScatter[0] = dlgOpenScatter1;
    m_dlgOpenScatter[1] = dlgOpenScatter2;
    m_dlgOpenScatter[2] = dlgOpenScatter3;
    m_dlgOpenScatter[3] = dlgOpenScatter4;

    m_dlgOpenROM[0] = dlgOpenROM1;
    m_dlgOpenROM[1] = dlgOpenROM2;
    m_dlgOpenROM[2] = dlgOpenROM3;
    m_dlgOpenROM[3] = dlgOpenROM4;
}

//--------------------------------------------------------------------------
void TfrmMultiLoad::LoadBootLoader( int idx, DL_HANDLE_T* p_dl_handle )
{
    int ret;
    AnsiString	as_bloader_file;
    as_bloader_file = m_INIFileH.read_BootLoader( "MultiPortFlashDownloadProject.ini", Application->ExeName, idx+1 );

    if( 0 < as_bloader_file.Length() )
    {
        load_bootloader(*p_dl_handle, as_bloader_file.c_str());
    }

    AnsiString as_BootLoaderEnable = m_INIFileH.read_BootLoaderEnable( "MultiPortFlashDownloadProject.ini", Application->ExeName, idx+1 );
    if( as_BootLoaderEnable.AnsiCompareIC("no") == 0 )
    {
        DL_BL_SetEnableAttr( *p_dl_handle, _FALSE );
    }
    else
    {
        DL_BL_SetEnableAttr( *p_dl_handle, _TRUE );
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::btnScatFileClick(TObject *Sender)
{
    TButton *btn = (TButton*)Sender;

    FileOpenScatExecute( (int) btn->Tag );
}

//--------------------------------------------------------------------------
bool TfrmMultiLoad::FileOpenScatExecute(int idx)
{

    int ret;
    DL_HANDLE_T *p_temp_dl_handle = new DL_HANDLE_T;
    DL_Create(p_temp_dl_handle);
    DL_HANDLE_T *p_dl_handle = MainForm->Get_DlHandle(idx);
    DL_HANDLE_LIST_T *p_dl_handle_list = MainForm->Get_DlHandleList();

    if (m_asScatPath[idx].Length() > 0)
    {
        m_dlgOpenScatter[idx]->InitialDir = m_asScatPath[idx];
    }

    if (m_dlgOpenScatter[idx]->Execute())    // *.bin file
    {
        if (OpenReadScatFile(m_dlgOpenScatter[idx]->FileName, idx, p_temp_dl_handle))
        {
            m_asScatFileName[idx] = m_dlgOpenScatter[idx]->FileName;
            int iLD = m_asScatFileName[idx].LastDelimiter("\\:");

            if (iLD > 0)
            {
                m_asScatPath[idx] = m_asScatFileName[idx].SubString(1, iLD-1 );
            }

            if (MainForm->Get_AutoLoadResByScatFlag())
            {
                ret = DL_AutoLoadByScatRegionName(*p_temp_dl_handle, m_dlgOpenScatter[idx]->FileName.c_str(), NORMAL_ROM|RESOURCE_BIN|JUMPTABLE_BIN, _TRUE);
                if (ret != 0)
                {
                    Application->MessageBox("Automatic load by scatter region name fail", "Fail", MB_OK);
                    Destroy_DLHandle(p_temp_dl_handle);
                    return false;
                }
            }

            // update handle list
            if (NULL != p_dl_handle) // not new handle
            {
                ret = DL_CheckHandleSameSWVersionInList(*p_dl_handle_list, *p_temp_dl_handle);
                if (0 == ret) // no same S/W version in list
                {
                    if (0 != DL_CheckHandleInList(*p_dl_handle_list, *p_dl_handle)) // handle in list
                    {
                        ret = DL_DeleteHandleFromList(*p_dl_handle_list, *p_dl_handle);
                        if (ret != 0)
                        {
                            Application->MessageBox("Delete handle from list fail", "Fail", MB_OK);
                            return false;
                        }
                    }
                    Destroy_DLHandle(p_dl_handle);
                    p_dl_handle = p_temp_dl_handle;

                    MainForm->Set_DlHandle(idx, p_dl_handle);
                    ret = DL_AddHandleToList(*p_dl_handle_list, *p_dl_handle);
                    {
                        if (ret != 0)
                        {
                            Application->MessageBox("Add handle to list fail", "Fail", MB_OK);
                            return false;
                        }
                    }
                    //m_lblScatFileName[idx]->Caption = m_dlgOpenScatter[idx]->FileName;
                    SetScatterFileCaption(idx, m_dlgOpenScatter[idx]->FileName);
                }
                else // same S/W in handle list
                {
                    Destroy_DLHandle( p_temp_dl_handle  );
                    Application->MessageBox( "Has same S/W in handle list", "NOTICE", MB_OK );
                    return false;
                }

            }
            else // new handle
            {
                p_dl_handle = p_temp_dl_handle;
                ret = DL_AddHandleToList(*p_dl_handle_list, *p_dl_handle);
                {
                    if (ret != 0)
                    {
                        Application->MessageBox("Add handle to list fail", "Fail", MB_OK);
                        return false;
                    }
                }
                //m_lblScatFileName[idx]->Caption = m_dlgOpenScatter[idx]->FileName;
                SetScatterFileCaption(idx, m_dlgOpenScatter[idx]->FileName);
                Destroy_DLHandle(p_temp_dl_handle);
            }

            // secure RO
            AnsiString as_sec_ro = m_asScatPath[idx] + "\\SECURE_RO";
            m_sParameter[idx].m_sec_ro_enable = _FALSE;
            m_sParameter[idx].m_sec_ro_filepath = "";
            if (as_sec_ro.AnsiCompareIC("") != 0)
            {
                if( ! LoadFile(as_sec_ro.c_str(), &m_sParameter[idx].m_sec_ro.m_data, &m_sParameter[idx].m_sec_ro.m_len, NULL))
                {
                   // AnsiString as;
                   // as.printf("Fail to load SEC_RO file \"%s\" !", dlgOpenSecRo->FileName.c_str());
                   // ShowMessage(as);
                   //return false;
                }
                else
                {
                    m_sParameter[idx].m_sec_ro_filepath = as_sec_ro;
                    m_sParameter[idx].m_sec_ro_enable = _TRUE;
                }
            }

            // GPS, get GPS ROM path and gps.ini path
            AnsiString as_scatter_dir = ExtractFileDir(m_dlgOpenScatter[idx]->FileName);
            AnsiString as_gps_dir = as_scatter_dir + "\\GPS";
            if (DirectoryExists(as_gps_dir))
            {
                unsigned int bFindGpsRom = 0;
                m_sParameter[idx].m_gps_download = _TRUE;
                AnsiString as_gps_rom = as_gps_dir + "\\M-core";
                AnsiString as_gps_ini = as_gps_dir + "\\gps.ini";
                if (FileExists(as_gps_rom))
                {
                    bFindGpsRom = 1;
                }
                else
                {
                    TSearchRec sr;
                    if (FindFirst(as_gps_dir+"\\*.bin", 0, sr) == 0)
                    {
                        do
                        {
                            as_gps_rom = as_gps_dir + "\\" + sr.Name;
                            bFindGpsRom = 1;
                            break;
                        }
                        while (FindNext(sr) == 0);
                        FindClose(sr);
                    }
                }

                // Get the GPS GPIO information from gps.ini
                if (bFindGpsRom && FileExists(as_gps_ini))
                {
                    m_sParameter[idx].m_gps_enable        = _TRUE;
                    m_sParameter[idx].m_gps_rom_dirpath   = as_gps_dir;
                    m_sParameter[idx].m_gps_rom_filepath  = as_gps_rom;
                    m_sParameter[idx].m_gps_ini_filepath  = as_gps_ini;
                    if (!LoadFileInfo(as_gps_rom.c_str(), &m_sParameter[idx].m_gps_rom_filesize, NULL))
                    {
                        Application->MessageBox("Load file information fail", "Fail", MB_OK);
                        return false;
                    }
                    TIniFile *ini = new TIniFile(as_gps_ini);
            	    m_sParameter[idx].m_gps_power_pin     = ini->ReadInteger("GPIO", "gpio_gps_power_pin",   0xFFFF);
                    m_sParameter[idx].m_gps_reset_pin     = ini->ReadInteger("GPIO", "gpio_gps_reset_pin",   0xFFFF);
                    m_sParameter[idx].m_gps_standby_pin   = ini->ReadInteger("GPIO", "gpio_gps_standby_pin", 0xFFFF);
                    m_sParameter[idx].m_gps_32k_pin       = ini->ReadInteger("GPIO", "gpio_gps_32k_pin",     0xFFFF);
                }
                else
                {
                    m_sParameter[idx].m_gps_enable        = _FALSE;
                }
            }
            else
            {
                m_sParameter[idx].m_gps_download  = (_BOOL) false;
            }

            RedrawLVList(idx, p_dl_handle);
            RedrawLVParamList(idx, p_dl_handle);
            return true;
         }
         else
         {
             return false;
         }
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------------------
bool TfrmMultiLoad::OpenReadScatFile(AnsiString asMapFileName, int idx, DL_HANDLE_T *p_dl_handle )
{
    int ret;
    unsigned short rom_count;
    ret=DL_LoadScatter(*p_dl_handle, asMapFileName.c_str());
    if (ret)
    {
        if( S_FTHND_HANDLE_BUSY_NOW == ret )
        {
            Application->MessageBox( "Program is busy! Can not reload scat file right now.", "Fail", MB_OK );
        }
        else
        {
            Application->MessageBox( "Incorrect scatter file format!", "Fail", MB_OK );
        }
        return false;
    }

#if 0
    SetScatterFileCaption(idx, asMapFileName);
    if(!DL_GetCount(*p_dl_handle, &rom_count))
    {
        ROM_INFO   rom_info[MAX_LOAD_SECTIONS];
        if( !DL_Rom_GetInfoAll(*p_dl_handle, rom_info, MAX_LOAD_SECTIONS) )
        {
            TListItem	*p_list_item;
            AnsiString   as_reg_prefix;

            m_lv[idx]->Items->Clear();

            for( int i=0; i<rom_count; i++ )
            {
                p_list_item = m_lv[idx]->Items->Add();
                p_list_item->Caption = rom_info[i].name;
                p_list_item->Checked = true;
    	        DL_Rom_SetEnableAttr(*p_dl_handle, i, p_list_item->Checked);
                if( rom_info[i].addr_type == ABSOLUTE_ADDR )
                {
                    as_reg_prefix = "";

                }
                else
                {
                    as_reg_prefix = "+";
            	}

                p_list_item->SubItems->Add( as_reg_prefix + "0x" + IntToHex((int)rom_info[i].region_addr, 8) );
                p_list_item->SubItems->Add( "0x" + IntToHex((int)rom_info[i].begin_addr, 8) );
                p_list_item->SubItems->Add( "0x" + IntToHex((int)rom_info[i].end_addr, 8) );
            }
	}
    }
#endif
    return true;
}



//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::RedrawLVList( int idx, DL_HANDLE_T *p_dl_handle )
{
    unsigned short rom_count;
   // DL_HANDLE_T *p_dl_handle = MainForm->Get_DlHandle(idx);

    TListItem	*pLI;
    m_lv[idx]->Items->Clear();
    for( int i=0; i<MAX_SUPPORT_LOAD_NUM; i++ )
    {
        m_asROMFileName[i] = "";
        m_asFATFileName[i] = "";
    }

    S_DN_PARAM_T* p_dn_param = MainForm->Get_DNParameter();

    if( OPERATION_NFB == p_dn_param->e_Operation )
    {
        BL_INFO	bl_info;

        pLI = m_lv[idx]->Items->Add();
        pLI->Caption = "BootLoader";

        if( ! DL_BL_GetInfo( *p_dl_handle, &bl_info ) )
        {
            AnsiString  region_prefix;

            pLI->Checked = (_TRUE==bl_info.m_enable)?true:false;
            if(strlen(bl_info.m_filepath) == 0)
            {
                pLI->Checked = false;
            }

            pLI->SubItems->Add("");
            pLI->SubItems->Add( "0x" + IntToHex((int)bl_info.m_start_addr, 8) );
            pLI->SubItems->Add("");
            pLI->SubItems->Add(bl_info.m_filepath);




            if(bl_info.m_ext_bootloader_exist)
            {
                int ext_bl_addr = (int)bl_info.m_start_addr+(int)bl_info.m_filesize;
                int ext_bl_size = (int)bl_info.m_ext_filesize;

                pLI = m_lv[idx]->Items->Add();
                pLI->Caption = "ExtBootLoader";

                pLI->Checked = (_TRUE==bl_info.m_enable)?true:false;
                if(strlen(bl_info.m_ext_filepath) == 0)
                {
                    pLI->Checked = false;
                }
                
                pLI->SubItems->Add("");
                pLI->SubItems->Add( "0x" + IntToHex(ext_bl_addr, 8) );
                pLI->SubItems->Add( "0x" + IntToHex(ext_bl_addr + ext_bl_size - 1, 8) );
                pLI->SubItems->Add(bl_info.m_ext_filepath);


            }
        }
    }

    if(!DL_GetCount(*p_dl_handle, &rom_count))
    {
        ROM_INFO	 rom_info[MAX_LOAD_SECTIONS];
        if(!DL_Rom_GetInfoAll(*p_dl_handle, rom_info, MAX_LOAD_SECTIONS))
        {
            // access
            unsigned int total_file_size = 0;
            for (int i=0; i<rom_count; i++)
            {
                AnsiString  as_reg_prefix;
                TListItem	*p_list_item;

                // access
                total_file_size += rom_info[i].filesize;
              //  if( ! DL_Rom_GetInfo(g_DL_HANDLE, i, &(rom_info[i])) )
                {
                    p_list_item = m_lv[idx]->Items->Add();
                    p_list_item->Caption = rom_info[i].name;
                    if (strcmpi(rom_info[i].name, "BOOTLOADER") == 0)
                    {
                        m_asROMFileName[idx] = rom_info[i].filepath;
                    }
                    else if (strcmpi(rom_info[i].name, "ROM") == 0)
                    {
                        m_asROMFileName[idx] = rom_info[i].filepath;
                    }
                    else if (strcmpi(rom_info[i].name, "FAT") == 0)
                    {
                        m_iLV_FAT_index[idx] = i;
                        m_asFATFileName[idx] = rom_info[i].filepath;
                    }

                    /*if (   strcmpi(rom_info[i].name, "BOOTLOADER") != 0
                        && strcmpi(rom_info[i].name, "ExtBootLoader") != 0)
                    { */
                        p_list_item->Checked = rom_info[i].enable;
                    /*}*/


            	    if (ABSOLUTE_ADDR == rom_info[i].addr_type)
                    {
                        as_reg_prefix = "";
                    }
                    else
                    {
                        as_reg_prefix = "+";
                    }
                    p_list_item->SubItems->Add(as_reg_prefix + "0x" + IntToHex((int)rom_info[i].region_addr, 8));
                    p_list_item->SubItems->Add("0x" + IntToHex((int)rom_info[i].begin_addr, 8));
                    p_list_item->SubItems->Add("0x" + IntToHex((int)rom_info[i].end_addr, 8));
                    p_list_item->SubItems->Add(rom_info[i].filepath);
                }
            } // for
            MainForm->Set_TotalFileSize(total_file_size);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::RedrawLVParamList(int idx, DL_HANDLE_T *p_dl_handle)
{
    // update parameter list view
    TListItem	*pLI;
    DL_INFO	 dl_info;

    m_lvPar[idx]->Items->Clear();
    DL_GetInfo(*p_dl_handle, &dl_info);


    // add SEC_RO m_parameters
    if(dl_info.m_config.m_security_supported)
    {
        AnsiString as;
        pLI = m_lvPar[idx]->Items->Add();
        pLI->Caption = "Secure RO Data";
        pLI->Checked = m_sParameter[idx].m_sec_ro_enable?true:false;
        as.printf("len(%lu): %s", m_sParameter[idx].m_sec_ro.m_len, m_sParameter[idx].m_sec_ro_filepath.c_str());
        pLI->SubItems->Add(as);
        pLI->Data = &g_LV_ItemType[LV_SEC_RO];
    }


    // add GPS ROM
    if (m_sParameter[idx].m_gps_download)
    {
        pLI = m_lvPar[idx]->Items->Add();
        pLI->Caption = "GPS ROM";
        pLI->Checked = m_sParameter[idx].m_gps_enable ? _TRUE : _FALSE;
        AnsiString as;
        as.printf("len(%lu): %s", m_sParameter[idx].m_gps_rom_filesize, m_sParameter[idx].m_gps_rom_filepath.c_str());
        pLI->SubItems->Add(as);
        pLI->Data = &g_LV_ItemType[LV_GPS_ROM];
    }
    else
    {
    	m_sParameter[idx].m_gps_enable = _FALSE;
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::RedrawLVCheckBox( int idx )
{
    unsigned short rom_count;
    int	rom_begin_index;
    S_DN_PARAM_T* p_dn_param = MainForm->Get_DNParameter();
    DL_HANDLE_T *p_dl_handle = MainForm->Get_DlHandle(idx);

    rom_begin_index = 0;

    if( OPERATION_NFB == p_dn_param->e_Operation )
    {
       BL_INFO	bl_info;

       if(!DL_BL_GetInfo(*p_dl_handle, &bl_info))
       {
           m_lv[idx]->Items->Item[0]->Checked = (_TRUE==bl_info.m_enable)?true:false;

           if(strlen(bl_info.m_filepath) == 0)
           {
                m_lv[idx]->Items->Item[0]->Checked = false;
           }

           rom_begin_index++;

           // is load ex bootloader
           if(is_need_to_load_ex_bootloader(*p_dl_handle))
           {
              m_lv[idx]->Items->Item[1]->Checked = (_TRUE==bl_info.m_enable)?true:false;
              rom_begin_index++;

              if(strlen(bl_info.m_ext_filepath) == 0)
              {
                m_lv[idx]->Items->Item[1]->Checked = false;
              }
           }
       }
    }

    if(!DL_GetCount(*p_dl_handle, &rom_count))
    {
        ROM_INFO	rom[MAX_LOAD_SECTIONS];
        int		checked_count=0;
        if(!DL_Rom_GetInfoAll(*p_dl_handle, rom, MAX_LOAD_SECTIONS))
        {
            for(int i=0; i<rom_count; i++)
            {
                if(rom[i].enable)
                {
                    checked_count++;
                }

                if(NULL != m_lv[idx]->Items->Item[rom_begin_index+i])
                {
                   m_lv[idx]->Items->Item[rom_begin_index+i]->Checked = (_TRUE==rom[i].enable)?true:false;
                }
            }
        }
    }

    
}

//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::lvChange(TObject *Sender, TListItem *Item,
      TItemChange Change)
{
    TListView *plv = dynamic_cast<TListView *>(Sender);
    if( (Change == ctState) && (Item->Checked != m_slvChanged[plv->Tag].bPreCheckBoxState) )
    {
        m_slvChanged[plv->Tag].iChangedIndex = Item->Index;
        return;
    }

    m_slvChanged[plv->Tag].iChangedIndex = NO_CHANGE;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::lvChanging(TObject *Sender, TListItem *Item,
      TItemChange Change, bool &AllowChange)
{
    TListView *plv = dynamic_cast<TListView *>(Sender);
    m_slvChanged[plv->Tag].bPreCheckBoxState = Item->Checked;
    m_slvChanged[plv->Tag].iChangedIndex = NO_CHANGE;
}


//--------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::Disable_BL()
{
     DL_HANDLE_T *p_dl_handle;
     S_DN_PARAM_T* p_dn_param = MainForm->Get_DNParameter();

     if(OPERATION_NFB == p_dn_param->e_Operation)
     {
       for(int i=0; i<=3; i++)
       {
           if(m_lv[i]->Items->Count != 0)
           {
              // Disable Bootloader
              m_lv[i]->Items->Item[0]->Checked = _FALSE;

              // get handle
              p_dl_handle = MainForm->Get_DlHandle((int)i);

              // Disable Extension Bootloader
              if(is_need_to_load_ex_bootloader(*p_dl_handle))
              {
                 m_lv[i]->Items->Item[1]->Checked = _FALSE;
              }

              //
              DL_BL_SetEnableAttr( *p_dl_handle, _FALSE);
           }
       }
     }
     else  if(OPERATION_NOR == p_dn_param->e_Operation)
     {
       for(int i=0; i<=3; i++)
       {
           if(m_lv[i]->Items->Count != 0)
           {
              // Disable Bootloader
              m_lv[i]->Items->Item[0]->Checked = _FALSE;

              // get handle
              p_dl_handle = MainForm->Get_DlHandle((int)i);

              DL_Rom_SetEnableAttr(*p_dl_handle, 0, _FALSE);
           }
       }
     }
}


//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::lvClick(TObject *Sender)
{
    TListView *plv = dynamic_cast<TListView *>(Sender);

    S_DN_PARAM_T* p_dn_param = MainForm->Get_DNParameter();
    DL_HANDLE_T *p_dl_handle = MainForm->Get_DlHandle((int) plv->Tag);

    if( 0<=m_slvChanged[plv->Tag].iChangedIndex && m_slvChanged[plv->Tag].iChangedIndex < plv->Items->Count )
    {
        if( OPERATION_NOR == p_dn_param->e_Operation )
        {
            DL_Rom_SetEnableAttr( *p_dl_handle, m_slvChanged[plv->Tag].iChangedIndex, plv->Items->Item[m_slvChanged[plv->Tag].iChangedIndex]->Checked?_TRUE:_FALSE );
        }
        else
        {
            if(is_need_to_change_bl_enable_status(m_slvChanged[plv->Tag].iChangedIndex, *p_dl_handle))
            {
               DL_BL_SetEnableAttr( *p_dl_handle, plv->Items->Item[m_slvChanged[plv->Tag].iChangedIndex]->Checked?_TRUE:_FALSE);
            }
            else
            {
                DL_Rom_SetEnableAttr(*p_dl_handle, m_slvChanged[plv->Tag].iChangedIndex-1, plv->Items->Item[m_slvChanged[plv->Tag].iChangedIndex]->Checked?_TRUE:_FALSE);
            }
        }
        RedrawLVCheckBox( (int) plv->Tag );
    }
    else
    {
        //RedrawLVCheckBox( (int) plv->Tag );
        lv_oldClick(Sender);
    }

    

    /*plv->Update();
    plv->Repaint();*/


    RedrawLVCheckBox( (int) plv->Tag );

    /*plv->Update();
    plv->Repaint(); */

    m_slvChanged[plv->Tag].iChangedIndex = NO_CHANGE;



}


bool __fastcall TfrmMultiLoad::is_need_to_change_bl_enable_status(int index, DL_HANDLE_T dl_handle)
{
    S_DN_PARAM_T* p_dn_param = MainForm->Get_DNParameter();
    bool ret;

    if(OPERATION_NOR == p_dn_param->e_Operation)
    {
        ret = false;
    }
    else
    {
        if( 0 == index )
        {
            ret = true;
        }
        else if ( 1 == index )
        {
            if(is_need_to_load_ex_bootloader(dl_handle))
            {
                ret = true;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}


//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::lv_oldClick(TObject *Sender)
{
    TListView *p_lv = dynamic_cast<TListView *>(Sender);
    int ret;
    int idx=p_lv->Tag;
    DL_HANDLE_T *p_dl_handle = MainForm->Get_DlHandle(idx);

    if( NULL == p_lv->Selected )
       return;

    if( m_asROMPath[idx].Length()>0 )
    {
        m_dlgOpenROM[idx]->InitialDir = m_asROMPath[idx];
        m_dlgOpenROM[idx]->FileName = "";
    }
    else if( 4 <= p_lv->Selected->SubItems->Count )
    {
        int iLD = p_lv->Selected->SubItems->Strings[3].LastDelimiter("\\:");
        if ( iLD > 0)
        {
	    m_dlgOpenROM[idx]->InitialDir = p_lv->Selected->SubItems->Strings[3].SubString(1, iLD-1 );
            m_dlgOpenROM[idx]->FileName = "";
        }
    }

    if( m_dlgOpenROM[idx]->Execute( ))
    {
        DL_HANDLE_T *p_dl_handle = MainForm->Get_DlHandle(idx);
        unsigned short index;
        S_DN_PARAM_T* p_dn_param = MainForm->Get_DNParameter();

        if( OPERATION_NFB == p_dn_param->e_Operation )
        {
            if( 0 == p_lv->ItemIndex ) // boot loader
            {
                if(!load_bootloader(*p_dl_handle, m_dlgOpenROM[idx]->FileName.c_str()))
                {
                    return;
                }
            }
            else
            {
                index = p_lv->ItemIndex-1;
            }
        }
        else // NOR
        {
            index = p_lv->ItemIndex;
        }

        if( !  ( OPERATION_NFB == p_dn_param->e_Operation && 0 == p_lv->ItemIndex )  )
        {
            ret=DL_Rom_Load(*p_dl_handle, index, m_dlgOpenROM[idx]->FileName.c_str());
            if (ret)
            {
                if( S_FTHND_HANDLE_BUSY_NOW == ret )
                {
                    Application->MessageBox( "Program is busy! Can not update setting right now.", "Fail", MB_OK );
                    return;
                }
                else if( S_DL_LOAD_REGION_IS_OVERLAP == ret )
                {
                    AnsiString as_msg = "\"" + m_dlgOpenROM[idx]->FileName + "\" is too large and causes region overlap!";
                    Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
                    return;
                }
                else
                {
                    AnsiString as_msg = " Load file \"" + m_dlgOpenROM[idx]->FileName + "\" fail!";
                    Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
                    return;
                }
            }

            int iLD = m_dlgOpenROM[idx]->FileName.LastDelimiter("\\:");
            if ( iLD > 0)
            {
                m_asROMPath[idx] = m_dlgOpenROM[idx]->FileName.SubString(1, iLD-1 );
            }

            // check if NFB enabled
	    _BOOL    bNFBEnabled=_FALSE;
	    if( S_DONE == DL_IsNFB( *p_dl_handle, &bNFBEnabled) )
            {
	    	// update operation method
	        if( bNFBEnabled && (OPERATION_NFB!=p_dn_param->e_Operation) ) {
	            MainForm->rbNANDClick(Sender);
	        }
	        else if( !bNFBEnabled && (OPERATION_NFB==p_dn_param->e_Operation) ) {
	            MainForm->rbNORClick(Sender);
	        }
	    }

            // auto load download bin files
            if(MainForm->Get_AutoLoadResByScatFlag())
            {
                if(bNFBEnabled)
                {
                    ret = DL_AutoLoadByScatRegionName(*p_dl_handle, m_dlgOpenROM[idx]->FileName.c_str(), NORMAL_ROM|RESOURCE_BIN|JUMPTABLE_BIN, _FALSE);
                }
                else
                {
                    ret = DL_AutoLoadByScatRegionName(*p_dl_handle, m_dlgOpenROM[idx]->FileName.c_str(), RESOURCE_BIN|JUMPTABLE_BIN, _FALSE);
                }
                if( ret != 0 )
                {
                    Application->MessageBox( "Automatic load by scatter region name fail", "Fail", MB_OK );
                    return;
                }
            }
        }
    }

    RedrawLVList( (int) p_lv->Tag, p_dl_handle );
}



//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::btnDelLoadClick(TObject *Sender)
{
    TButton *btn = (TButton*)Sender;
    DelLoad(btn->Tag);
}

void __fastcall TfrmMultiLoad::DelLoad(int idx)
{
    int ret;

    DL_HANDLE_LIST_T *p_dl_handle_list = MainForm->Get_DlHandleList();
    DL_HANDLE_T *p_dl_handle = MainForm->Get_DlHandle(idx);

    SetScatterFileCaption(idx, "");
    
    m_lv[idx]->Clear();
    m_lvPar[idx]->Clear();

    ret = DL_CheckHandleInList( *p_dl_handle_list, *p_dl_handle );

    if( ret != 0 )
    {
        DL_DeleteHandleFromList( *p_dl_handle_list, *p_dl_handle );
    }
}

//---------------------------------------------------------------------------
bool TfrmMultiLoad::Destroy_DLHandle(DL_HANDLE_T *p_dl_handle)
{
    if( NULL != p_dl_handle )
    {
        int ret;
        ret = DL_Rom_UnloadAll( *p_dl_handle );
        if( ret != 0 )
        {
            Application->MessageBox( "Unload all ROM fail", "Fail", MB_OK );
            return false;
        }

        ret = DL_Destroy( p_dl_handle );
        if( ret != 0 )
        {
            Application->MessageBox( "Unload all ROM fail", "Fail", MB_OK );
            return false;
        }

        delete p_dl_handle;
    }
    
    return true;
}


void __fastcall TfrmMultiLoad::lvParamChange(TObject *Sender,
      TListItem *Item, TItemChange Change)
{
    TListView *plv = dynamic_cast<TListView *>(Sender);

    if( (Change == ctState) && (Item->Checked != m_sLvParamChanged[plv->Tag].bPreCheckBoxState) )
    {
        m_sLvParamChanged[plv->Tag].iChangedIndex = Item->Index;
        return;
    }

    m_sLvParamChanged[plv->Tag].iChangedIndex = NO_CHANGE;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMultiLoad::lvParamChanging(TObject *Sender,
      TListItem *Item, TItemChange Change, bool &AllowChange)
{
    TListView *plv = dynamic_cast<TListView *>(Sender);

    m_sLvParamChanged[plv->Tag].bPreCheckBoxState = Item->Checked;
    m_sLvParamChanged[plv->Tag].iChangedIndex = NO_CHANGE;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMultiLoad::lvParamClick(TObject *Sender)
{
    TListView *plv = dynamic_cast<TListView *>(Sender);

    if( 0<=m_sLvParamChanged[plv->Tag].iChangedIndex && m_sLvParamChanged[plv->Tag].iChangedIndex < plv->Items->Count )
    {
        TListItem *pItem = plv->Items->Item[m_sLvParamChanged[plv->Tag].iChangedIndex];
	E_LISTVIEW_ITEM_TYPE	type=*((E_LISTVIEW_ITEM_TYPE *)pItem->Data);

        switch(type)
        {
            case LV_OTP:
            {
                m_sParameter[plv->Tag].m_otp_enable = pItem->Checked ?_TRUE : _FALSE;
            }
            break;

            case LV_FTCFG:
            {
                m_sParameter[plv->Tag].m_ft_cfg_enable = pItem->Checked ? _TRUE : _FALSE;
            }
            break;

            case LV_SEC_RO:
            {
		m_sParameter[plv->Tag].m_sec_ro_enable = pItem->Checked ? _TRUE : _FALSE;
            }
            break;

            case LV_CUST_PARA:
            {
                m_sParameter[plv->Tag].m_cust_para_enable = pItem->Checked ? _TRUE : _FALSE;
            }
            break;

            case LV_GPS_ROM:
            {
                m_sParameter[plv->Tag].m_gps_enable = pItem->Checked ? _TRUE : _FALSE;
            }
            break;

            default:
            {
            }
            break;
        }
    }
    else if( NULL != plv->Selected )
    {
        TListItem *pItem=plv->Selected;
        E_LISTVIEW_ITEM_TYPE	type=*((E_LISTVIEW_ITEM_TYPE *)pItem->Data);

        switch(type)
        {
         #if 0
            case LV_OTP:
            {

                m_OTPSetting->Visible = true;

                if( m_sParameter.m_otp_op == OTP_WRITE )
                {
                    m_OTPSetting->m_Write->Checked     = true;
                    m_OTPSetting->m_WriteLock->Checked = false;
                    m_OTPSetting->m_Lock->Checked      = false;
                }
                else if( param.m_otp_op == OTP_WRITE_AND_LOCK )
                {
                    m_OTPSetting->m_Write->Checked     = false;
                    m_OTPSetting->m_WriteLock->Checked = true;
                    m_OTPSetting->m_Lock->Checked      = false;
                }
                else if( param.m_otp_op == OTP_LOCK )
                {
                    m_OTPSetting->m_Write->Checked     = false;
                    m_OTPSetting->m_WriteLock->Checked = false;
                    m_OTPSetting->m_Lock->Checked      = true;
                }
       		m_OTPSetting->m_otp_addr->Text = param.m_otp.m_addr;
   	    	m_OTPSetting->m_otp_len->Text = param.m_otp.m_len;
                m_OTPSetting->m_otp_file->Text = param.m_otp_filepath;
            }
            break;

            case LV_FTCFG:
            {
                g_bParameterPage = false;
                m_SecuritySetting->Visible = true;
            }
            break;
      #endif
            case LV_SEC_RO:
            {
                LoadSecRO(plv->Tag);
            }
            break;
      #if 0
            case LV_CUST_PARA:
            {
                LoadCustPara();
            }
            break;
      #endif

            case LV_GPS_ROM:
            {
                LoadGPS(plv->Tag);
            }
            break;

            default:
            break;
        }
    }

    m_sLvParamChanged[plv->Tag].iChangedIndex = NO_CHANGE;
}

//---------------------------------------------------------------------------
bool __fastcall TfrmMultiLoad::LoadFileInfo(const char *pathname, unsigned int *p_nFileLength, long *p_last_modify_time)
{
    FILE *fp;
    unsigned char *buf;
    unsigned int buf_len;
    unsigned int file_len;
    struct _stat  file_stat={0};

    if ((NULL == pathname)    ||
        ('\0' == pathname[0]) ||
        (NULL == p_nFileLength)
       )
    {
        return false;
    }

    fp = fopen(pathname, "rb");
    if (NULL == fp)
    {
        return false;
    }

    if (_fstat(fileno(fp), &file_stat))
    {
        return false;
    }

    if (0 >= (file_len=filelength(fileno(fp))))
    {
        return false;
    }

    if (0 != (file_len%2))
    {
        buf_len = file_len+1;
    }
    else
    {
        buf_len = file_len;
    }

    *p_nFileLength = buf_len;
    if (NULL != p_last_modify_time)
    {
        *p_last_modify_time = file_stat.st_mtime;
    }

    return true;
}

//-------------------------------------------------------------------------
bool __fastcall TfrmMultiLoad::LoadFile(const char *filename, unsigned char **pp_buf, unsigned int *p_nFileLength, long *p_last_modify_time)
{
    FILE *fp;
    unsigned char *buf;
    unsigned int buf_len;
    unsigned int file_len ;
    struct _stat  file_stat={0};

    if( NULL == filename || '\0' == filename[0] || NULL == pp_buf || NULL == p_nFileLength )
    {
        return false;
    }

    fp = fopen(filename, "rb");

    if( NULL == fp )
    {
        return false;
    }

    if( _fstat(fileno(fp), &file_stat) )
    {
        return false;
    }

    if( 0 >= (file_len=filelength(fileno(fp))) )
    {
        return false;
    }

    if( 0 != (file_len%2) )
    {
        buf_len = file_len+1;
    }
    else
    {
        buf_len = file_len;
    }

    if( NULL == (buf=(unsigned char *)malloc(buf_len)) )
    {
        return false;
    }

    if( file_len > fread(buf, 1, file_len, fp) )
    {
        free(buf);
        return false;
    }

    if( NULL != *pp_buf )
    {
        free(*pp_buf);
    }

    *pp_buf = buf;
    *p_nFileLength = buf_len;
    if( NULL != p_last_modify_time )
    {
        *p_last_modify_time = file_stat.st_mtime;
    }

    return true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::LoadSecRO(int idx)
{
    AnsiString	as;
    if (dlgOpenSecRo->Execute())
    {
        if (!LoadFile(dlgOpenSecRo->FileName.c_str(), &m_sParameter[idx].m_sec_ro.m_data, &m_sParameter[idx].m_sec_ro.m_len, NULL))
        {
            as.printf("Fail to load SEC_RO file \"%s\" !", dlgOpenSecRo->FileName.c_str());
            ShowMessage(as);
            return;
        }
    }

    m_sParameter[idx].m_sec_ro_filepath = dlgOpenSecRo->FileName;
    DL_HANDLE_T *p_dl_handle = MainForm->Get_DlHandle(idx);
    RedrawLVParamList(idx, p_dl_handle);

}

//---------------------------------------------------------------------------
void __fastcall TfrmMultiLoad::LoadGPS(int idx)
{
    if (m_dlgOpenGPS->Execute())
    {
        AnsiString selectDir;
        AnsiString selectIni;

        // load GPS firmware
        if (!LoadFileInfo(m_dlgOpenGPS->FileName.c_str(), &m_sParameter[idx].m_gps_rom_filesize, NULL))
        {
            AnsiString as;
            as.printf("Fail to load GPS ROM \"%s\" !", m_dlgOpenGPS->FileName.c_str());
            ShowMessage(as);
            return;
        }

        // parse the gps.ini GPIO setting
        selectDir = ::ExtractFilePath(m_dlgOpenGPS->FileName);
        selectIni = selectDir + "gps.ini";

        if (!::FileExists(selectIni))
        {
            AnsiString as;
            as.printf("Fail to load GPS FW's INI File \"%s\" !", selectIni.c_str());
            ShowMessage(as);
            return;
        }
    }
    else
    {
        return;
    }

    // Get the GPS GPIO information from gps.ini
    m_sParameter[idx].m_gps_rom_filepath   = m_dlgOpenGPS->FileName;
    m_sParameter[idx].m_gps_rom_dirpath    = ::ExtractFilePath(m_sParameter[idx].m_gps_rom_filepath);
    m_sParameter[idx].m_gps_ini_filepath   = m_sParameter[idx].m_gps_rom_dirpath + "gps.ini";

    TIniFile *ini = new TIniFile(m_sParameter[idx].m_gps_ini_filepath);
    m_sParameter[idx].m_gps_power_pin   = ini->ReadInteger("GPIO", "gpio_gps_power_pin",   0xFFFF);
    m_sParameter[idx].m_gps_reset_pin   = ini->ReadInteger("GPIO", "gpio_gps_reset_pin",   0xFFFF);
    m_sParameter[idx].m_gps_standby_pin = ini->ReadInteger("GPIO", "gpio_gps_standby_pin", 0xFFFF);
    m_sParameter[idx].m_gps_32k_pin     = ini->ReadInteger("GPIO", "gpio_gps_32k_pin",     0xFFFF);
    delete ini;

    DL_HANDLE_T *p_dl_handle = MainForm->Get_DlHandle(idx);
    RedrawLVParamList(idx, p_dl_handle);
}

//===========================================================================
////////////////////////        share information     ///////////////////////
//===========================================================================
S_PARAMETER_DOWNLOAD_CONFIG TfrmMultiLoad::Get_Parameter(void)
{
    return m_sParameter[0];
}

void TfrmMultiLoad::SetScatterFileCaption(int idx, AnsiString  text)
{
    //TODO: Add your source code here
    m_lblScatFileName[idx]->Caption = text;
}


//---------------------------------------------------------------------------
bool __fastcall TfrmMultiLoad::load_bootloader(DL_HANDLE_T  dl_handle,
                                               const char *bl_filepath)
{
    if(!load_basic_bootloader(dl_handle, bl_filepath))
    {
        return false;
    }

    if(is_need_to_load_ex_bootloader(dl_handle))
    {
        AnsiString ex_filepath = get_ex_bootloader_path(dl_handle);

        if(!load_ex_bootloader(dl_handle, ex_filepath.c_str()))
        {
            return false;
        }
    }

    return true;
}

bool __fastcall TfrmMultiLoad::load_basic_bootloader(DL_HANDLE_T  dl_handle, const char *bl_filepath)
{
    bool ret;

    // Load basic bootloader
    if( S_DONE != (ret=DL_BL_Load(dl_handle, bl_filepath)) )
    {
        if( S_FTHND_HANDLE_BUSY_NOW == ret )
        {
            Application->MessageBox( "Program is busy! Can not update setting right now.", "Fail", MB_OK );
        }
        else
        {
            //AnsiString as_bloader_file(bl_filepath);
            //AnsiString as_msg = " Load boot-loader \"" + as_bloader_file + "\" fail!";
            //Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
        }

        ret = false;
   }
   else
   {
        ret = true;
   }

   return ret;
}

bool __fastcall TfrmMultiLoad::is_need_to_load_ex_bootloader(DL_HANDLE_T  dl_handle)
{
     BL_INFO bl_info;

     if(S_DONE != DL_BL_GetInfo(dl_handle, &bl_info))
     {
        return false;
     }

     return  bl_info.m_ext_bootloader_exist;
}

AnsiString __fastcall TfrmMultiLoad::get_ex_bootloader_path(DL_HANDLE_T  dl_handle)
{
     BL_INFO bl_info;

     if(S_DONE != DL_BL_GetInfo(dl_handle, &bl_info))
     {
        return "";
     }

     return  bl_info.m_ext_filepath;
}

bool __fastcall TfrmMultiLoad::load_ex_bootloader(DL_HANDLE_T  dl_handle, const char *ex_bl_filepath)
{
   // Load extension bootloader
   if ( S_DONE != DL_BL_EXT_Load(dl_handle, ex_bl_filepath))
   {
      // pop error message
      //AnsiString as_msg;
      //as_msg.printf("Fail to load Extended BootLoader!\n\n%s", ex_bl_filepath);
      //Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
      return false;
   }
   else
   {
      return true;
   }
}

#endif  //#if 0  

