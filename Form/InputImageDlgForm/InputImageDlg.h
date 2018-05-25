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
 *   ThreadManager.h
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *
 *
 * Author:
 * -------
 *  Maobin Guo (mtk80061)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 *

 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

//---------------------------------------------------------------------------
#pragma warning(disable: 4530)

#ifndef InputImageDlgH
#define InputImageDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>

#include <windows.h>
//#include <Dialogs.hpp>
#include <CheckLst.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <string>
#include <vector>
#include <map>

#include "multiport_common.h"
#include "LinkMapFileManager/inc/ScatterFileManager.h"

using namespace std;

//---------------------------------------------------------------------------
class TfrmInputImage : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *dlg_input_open_bin;
	TCheckListBox *clbRomImageSelector;
	TComboBox *cbScatterFileList;
	TLabel *Label1;
        TImage *ImageBootloaderUSBDownloadSupport;
        TImage *ImageBootROMUSBDownload;
	void __fastcall mbOKClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall clbRomImageSelectorDblClick(TObject *Sender);
	void __fastcall cbScatterFileListChange(TObject *Sender);
	void __fastcall clbRomImageSelectorClickCheck(TObject *Sender);
	void __fastcall mbCancelClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
public:
	__fastcall TfrmInputImage(TComponent* Owner);
	void set_image_info(map<string, MAUI_LoadHandle> &image_infos);
private:
	int get_rom_index(string name);
	void add_a_item_check_list_box(Image &info);
	void update_image_path(int index, string new_path);
	string get_key_string(string key);
	string get_key(string text);
	void fill_rom_table(int index);

private:

	// User declarations
	ROM_INFO  *m_p_rom_info_array;
	BL_INFO   *m_p_bl_info;
	bool   m_is_load_success;
	DL_HANDLE_T* m_p_CurrentHandle;
	
	typedef enum
	{
		IT_ROM,
		IT_BOOTLOADER,
	}INPUT_TYPE;
	INPUT_TYPE m_input_type;
	map<string, MAUI_LoadHandle>* _p_image_infos;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInputImage *frmInputImage;
//---------------------------------------------------------------------------
#endif
