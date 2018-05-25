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
 *   form_MultiLoad.h
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  Multi-load form header file
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

#ifndef _FORM_MULTILOAD_H_
#define _FORM_MULTILOAD_H_

#if 0  //for this is no use now

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>

#ifndef _MULTIPORT_COMMON_H_
#include "multiport_common.h"
#endif

#ifndef _INIFILEHANDLE_H_
#include "INIFileHandle.h"
#endif

// parameter
#ifndef _PARAM_H_
#include "param.h"
#endif

//---------------------------------------------------------------------------
class TfrmMultiLoad : public TForm
{
__published:	// IDE-managed Components
        TStaticText *lblScatFileName1;
        TOpenDialog *dlgOpenScatter1;
        TOpenDialog *dlgOpenROM1;
        TOpenDialog *dlgOpenFAT1;
        TListView *lv1;
        TListView *lv2;
        TListView *lv3;
        TListView *lv4;
        TStatusBar *sbMultiLoad;
        TButton *btnScatFile1;
        TButton *btnScatFile2;
        TStaticText *lblScatFileName2;
        TButton *btnScatFile3;
        TStaticText *lblScatFileName3;
        TButton *btnScatFile4;
        TStaticText *lblScatFileName4;
        TButton *btnDelLoad4;
        TButton *btnDelLoad3;
        TButton *btnDelLoad2;
        TButton *btnDelLoad1;
        TOpenDialog *dlgOpenScatter2;
        TOpenDialog *dlgOpenScatter3;
        TOpenDialog *dlgOpenScatter4;
        TOpenDialog *dlgOpenROM3;
        TOpenDialog *dlgOpenROM4;
        TOpenDialog *dlgOpenROM2;
        TOpenDialog *dlgOpenFAT2;
        TOpenDialog *dlgOpenFAT3;
        TOpenDialog *dlgOpenFAT4;
        TListView *lvPar1;
        TListView *lvPar2;
        TListView *lvPar3;
        TListView *lvPar4;
        TOpenDialog *dlgOpenSecRo;
        TOpenDialog *m_dlgOpenGPS;

        void __fastcall Disable_BL();

        void __fastcall lvChange(TObject *Sender, TListItem *Item,
          TItemChange Change);
        void __fastcall lvChanging(TObject *Sender, TListItem *Item,
          TItemChange Change, bool &AllowChange);
        void __fastcall lvClick(TObject *Sender);
        void __fastcall btnScatFileClick(TObject *Sender);
        void __fastcall btnDelLoadClick(TObject *Sender);
        void __fastcall lvParamChange(TObject *Sender, TListItem *Item,
          TItemChange Change);
        void __fastcall lvParamChanging(TObject *Sender, TListItem *Item,
          TItemChange Change, bool &AllowChange);
        void __fastcall lvParamClick(TObject *Sender);

        void __fastcall DelLoad(int idx);
        
private:	// User declarations
        // file
        TStaticText* m_lblScatFileName[MAX_SUPPORT_LOAD_NUM];
        TOpenDialog* m_dlgOpenScatter[MAX_SUPPORT_LOAD_NUM];
        TOpenDialog* m_dlgOpenROM[MAX_SUPPORT_LOAD_NUM];
        TOpenDialog* m_dlgOpenFAT[MAX_SUPPORT_LOAD_NUM];
        //AnsiString m_asDAPath;
        //AnsiString m_asDAFileName;
        AnsiString m_asScatPath[MAX_SUPPORT_LOAD_NUM];
        AnsiString m_asScatFileName[MAX_SUPPORT_LOAD_NUM];
        AnsiString m_asROMPath[MAX_SUPPORT_LOAD_NUM];
        AnsiString m_asROMFileName[MAX_SUPPORT_LOAD_NUM];
        AnsiString m_asFATPath[MAX_SUPPORT_LOAD_NUM];
        AnsiString m_asFATFileName[MAX_SUPPORT_LOAD_NUM];
       // AnsiString m_asSecRoFileName[MAX_SUPPORT_LOAD_NUM];
       // AnsiString m_asSecRoPath[MAX_SUPPORT_LOAD_NUM];



        // ini file
         CINIFileHandle m_INIFileH;

        // form
        

        // List view
        TListView *m_lv[MAX_SUPPORT_LOAD_NUM];
        TListView *m_lvPar[MAX_SUPPORT_LOAD_NUM];
        int m_iLV_FAT_index[MAX_SUPPORT_LOAD_NUM];
        S_LV_CHANGED m_slvChanged[MAX_SUPPORT_LOAD_NUM];
        S_LV_CHANGED m_sLvParamChanged[MAX_SUPPORT_LOAD_NUM];

        // parameter
        S_PARAMETER_DOWNLOAD_CONFIG m_sParameter[MAX_SUPPORT_LOAD_NUM];
        // handle
        //DL_HANDLE_T m_TempDlHandle;

public:		// User declarations
        __fastcall TfrmMultiLoad(TComponent* Owner);
       // bool FileOpenDownloadAgentExecute( void );
       // bool OpenReadDAFile( AnsiString asFileName );
        bool FileOpenScatExecute( int idx );
        bool OpenReadScatFile(AnsiString asMapFileName, int idx, DL_HANDLE_T *p_dl_handle );
        void __fastcall RedrawLVList( int idx, DL_HANDLE_T *p_dl_handle );
        void __fastcall RedrawLVParamList( int idx, DL_HANDLE_T *p_dl_handle );
        void __fastcall RedrawLVCheckBox( int idx );
        void __fastcall lv_oldClick(TObject *Sender);
        // DL handle
        bool Destroy_DLHandle( DL_HANDLE_T *p_dl_handle );


//        void Display_LVSetting( void );
//        void Save_LVSetting( void );
        void LoadBootLoader( int idx, DL_HANDLE_T* p_dl_handle );

        // parameter
        bool __fastcall LoadFileInfo(const char *pathname, unsigned int *p_nFileLength, long *p_last_modify_time);
        bool __fastcall LoadFile(const char *pathname, unsigned char **pp_buf, unsigned int *p_nFileLength, long *p_last_modify_time);
        void __fastcall LoadSecRO(int idx);
        void __fastcall LoadGPS(int idx);

        // share information
        S_PARAMETER_DOWNLOAD_CONFIG Get_Parameter(void);

        void SetScatterFileCaption(int idx, AnsiString  text);

        bool __fastcall load_bootloader(DL_HANDLE_T  dl_handle, const char *bl_filepath);
        bool __fastcall load_basic_bootloader(DL_HANDLE_T  dl_handle, const char *bl_filepath);
        bool __fastcall load_ex_bootloader(DL_HANDLE_T  dl_handle, const char *bl_filepath);
        bool __fastcall is_need_to_load_ex_bootloader(DL_HANDLE_T  dl_handle);
        AnsiString __fastcall get_ex_bootloader_path(DL_HANDLE_T  dl_handle);
        bool __fastcall is_need_to_change_bl_enable_status(int index, DL_HANDLE_T dl_handle);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMultiLoad *frmMultiLoad;
//---------------------------------------------------------------------------
#endif //#if 0

#endif
