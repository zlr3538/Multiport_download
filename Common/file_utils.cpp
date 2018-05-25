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
 *   file_utils.cpp
 *
 * Project:
 * --------
 *   Multiport Download Tool
 *
 * Description:
 * ------------
 *  File untility source
 *
 * Author:
 * -------
 *  Andy Ueng (mtk00490)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision:   1.3  $
 * $Modtime:   Sep 25 2005 11:23:04  $
 * $Log:   //mtkvs01/vmdata/Multiport_Download/archives/Multiport_Download/Common/file_utils.cpp-arc  $
 *
 * Aug 12 2008 mtk00490
 * [STP100001788] [Multiport download tool] Multiport download tool ver 3.0832.0
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
 *    Rev 1.3   Sep 25 2005 12:02:38   mtk00490
 * Support NFB download and NAND flash format
 * 
 *    Rev 1.2   Sep 02 2005 10:22:28   mtk00490
 * Support MT6227, MT6228 baseband chip
 * 
 *    Rev 1.1   Jul 11 2005 14:45:06   mtk00490
 * Add set to factory default
 * 
 *    Rev 1.0   Jul 04 2005 21:06:12   mtk00490
 * Initial revision.
 * 
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#include <vcl.h>

#pragma hdrstop

#include <stdio.h>

#ifndef  _FILE_UTILS_H_
#include "file_utils.h"
#endif

//-----------------------------------------------------------------------------
bool Check_FileExist(AnsiString asFileName)
{
    FILE *fp;

    if( (fp = fopen(asFileName.c_str(), "r")) == NULL )
    {
        return false;
    }
    
    fclose( fp );
    return true;
}

//-----------------------------------------------------------------------------
bool withPath( AnsiString asPath )
{
    if ( asPath.LastDelimiter(":\\") > 0 )
        return true;
    else
        return false;
}

//---------------------------------------------------------------------------
bool getPathFromStr( AnsiString asStr, AnsiString &asPath )
{
    int iLD = asStr.LastDelimiter(":\\");
    if (iLD <= 0)
      return false;

    asPath = asStr.SubString( 1, iLD );
    return true;
}

//-----------------------------------------------------------------------------
AnsiString getFullPathFileName( AnsiString as_filename )
{
    AnsiString as_path, as_full_filename;

    getPathFromStr( Application->ExeName, as_path);
    as_full_filename = as_path + as_filename;

    return  as_full_filename;
}

//-----------------------------------------------------------------------------
AnsiString GetWorkingDir(void)
{
    AnsiString asPath;
    getPathFromStr(Application->ExeName, asPath);
    return asPath;
}     
