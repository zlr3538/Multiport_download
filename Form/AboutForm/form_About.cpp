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
 *   form_About.cpp
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  About form source
 *
 * Author:
 * -------
 *  Andy Ueng (mtk00490)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision:   1.9  $
 * $Modtime:   Sep 25 2005 11:31:54  $
 * $Log:   //mtkvs01/vmdata/Multiport_Download/archives/Multiport_Download/Form/form_About.cpp-arc  $
 *
 * Nov 29 2006 mtk00490
 * [STP100001239] [Multiport download tool] Multiport download tool ver 3.1.02
 * 
 * 
 *    Rev 1.9   Sep 25 2005 12:02:46   mtk00490
 * Support NFB download and NAND flash format
 * 
 *    Rev 1.8   Sep 02 2005 10:22:38   mtk00490
 * Support MT6227, MT6228 baseband chip
 * 
 *    Rev 1.7   Jul 11 2005 14:45:22   mtk00490
 * Add set to factory default
 * 
 *    Rev 1.6   Jul 04 2005 20:56:00   mtk00490
 * Add download time, throughput and fail reason to Microsoft Access
 * 
 *    Rev 1.5   Jun 24 2005 15:24:56   mtk00490
 * Support maximum 16 port download, format only type, multi-bin option
 * 
 *    Rev 1.4   Apr 14 2005 16:08:30   mtk00490
 * add stop button to stop specific or all mobile downloading and formatting
 * 
 *    Rev 1.3   Feb 18 2005 11:18:10   mtk00490
 * Update brom.dll and download agent ver 2.4.1009 to resolve INTEL W18/W30 series flash doesn't support Buffered-Program
 * 
 *    Rev 1.2   Dec 01 2004 10:00:02   mtk00490
 * Multiport download tool ver 2.4.1007 (Add status indicator--download successful:green light, download fail:red light)
 * 
 *    Rev 1.1   Nov 05 2004 17:15:08   mtk00490
 * Multiport download tool ver 2.4.1007 (Support automatic baseband chip and external clock rate detection)
 * 
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
                 
#include "form_About.h"

#include "brom_dll/inc/brom.h"
#include "meta_dll/inc/meta.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_AboutMD *Form_AboutMD;

//---------------------------------------------------------------------------
__fastcall TForm_AboutMD::TForm_AboutMD(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_AboutMD::BitBtn1Click(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int TForm_AboutMD::GetVersion( unsigned int *major_ver, unsigned int *minor_ver, unsigned int *release_num, unsigned int *build_num )
{

	static unsigned int s_major_ver=0;
	static unsigned int s_minor_ver=0;
    static unsigned int s_release_num=0;
	static unsigned int s_build_num=0;

    if( NULL == major_ver || NULL == minor_ver || NULL== release_num || NULL == build_num ) {
    	return 1;
	}

    *major_ver = 0;
    *minor_ver = 0;
    *release_num = 0;
    *build_num = 0;

	if( 0==s_major_ver && 0==s_minor_ver && 0==s_release_num && 0==s_build_num ) {

		// get file version indo
		DWORD dwHnd;
	 	DWORD dwVerInfoSize;
	 	char *pBuffer;
		if( 0 >= (dwVerInfoSize=GetFileVersionInfoSize("MultiPortFlashDownloadProject.exe", &dwHnd)) ) {
			// get fileversion size error
			return 2;
		}
		if( NULL == (pBuffer=(char *)malloc(dwVerInfoSize)) ) {
			// not enough memory
			return 3;
		}

		// get file version info
		if(!GetFileVersionInfo("MultiPortFlashDownloadProject.exe", dwHnd, dwVerInfoSize, pBuffer)) {
			// get file version info fail
			return 4;
		}

		// get FileVersion string from resource
		VS_FIXEDFILEINFO *p_version;
		unsigned int version_len=0;
		if(!VerQueryValue(pBuffer, "\\", (void **)&p_version, &version_len)) {
			// get query value fail
			return 5;
		}

        /*                                            */
        /* Look at FILEVERSION in rc file.            */
        /*                                            */
        /* FILEVERSION    1,    2,    3,    4         */
        /*             0001  0002  0003  0004         */
        /*             -----+----  -----+----         */
        /*                  |         dwFileVersionLS */
        /*                  |                         */
        /*           dwFileVersionMS                  */
        /*                                            */
		s_major_ver = HIWORD(p_version->dwFileVersionMS);
		s_minor_ver = LOWORD(p_version->dwFileVersionMS);
        s_release_num = HIWORD(p_version->dwFileVersionLS);
		s_build_num = LOWORD(p_version->dwFileVersionLS);
	}

	// return version number
	*major_ver = s_major_ver;
	*minor_ver = s_minor_ver;
    *release_num = s_release_num;
	*build_num = s_build_num;

	return 0;
}

void __fastcall TForm_AboutMD::FormCreate(TObject *Sender)
{
   AnsiString as;
   lb_BuildDate->Caption = "Build date: " + AnsiString( __DATE__ );

   unsigned int major_ver;
   unsigned int minor_ver;
   unsigned int release_num;
   unsigned int build_num;

   // get flash tool (UI) verison
   GetVersion(&major_ver, &minor_ver, &release_num, &build_num);

//   VersionInfo->Caption = "FlashTool v" + IntToStr(major_ver) + "." + IntToStr(minor_ver) + "." + IntToStr(release_num) + "." + IntToStr(build_num);
    as.printf("Multiport Download Tool v%u.%04u.%02u.%02u", major_ver, minor_ver, release_num, build_num);
    VersionInfo->Caption = as;

#ifdef SERVICE_CENTER
     as = VersionInfo->Caption;
     as = as+" (Service Center Version) ";
     VersionInfo->Caption = as;
#endif /* #ifdef _DEBUG */

   const char *p_version, *p_release_type, *p_build_date;

   // get the brom dll information
   Brom_GetDLLInfo(&p_version, &p_release_type, &p_build_date, NULL);
   as.printf("%s", p_version);
   brom_dll_version->Caption = as;
   as.printf("%s", p_release_type);
   brom_dll_release_type->Caption = as;
   as.printf("(Build-Date: %s)", p_build_date);
   brom_dll_build_date->Caption = as;

   // get the meta dll information
   META_GetDLLInfo(&p_version, &p_release_type, &p_build_date, NULL);
   as.printf("%s", p_version);
   meta_dll_version->Caption = as;
   as.printf("%s", p_release_type);
   meta_dll_release_type->Caption = as;
   as.printf("(Build-Date: %s)", p_build_date);
   meta_dll_build_date->Caption = as;
}
//---------------------------------------------------------------------------

void __fastcall TForm_AboutMD::Button1Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

