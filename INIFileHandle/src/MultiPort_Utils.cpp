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
 *   MultiPort_Utils.cpp
 *
 * Project:
 * --------
 *   Maui META APP
 *
 * Description:
 * ------------
 *  Multiport download utility source
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
 * $Modtime:   Sep 25 2005 11:47:08  $
 * $Log:   //mtkvs01/vmdata/Multiport_Download/archives/Multiport_Download/INIFileHandle/MultiPort_Utils.cpp-arc  $
 *
 * Aug 12 2008 mtk00490
 * [STP100001788] [Multiport download tool] Multiport download tool ver 3.0832.0
 * 
 * 
 *    Rev 1.16   Sep 25 2005 12:02:48   mtk00490
 * Support NFB download and NAND flash format
 * 
 *    Rev 1.15   Sep 02 2005 10:22:44   mtk00490
 * Support MT6227, MT6228 baseband chip
 * 
 *    Rev 1.14   Jul 11 2005 14:45:32   mtk00490
 * Add set to factory default
 * 
 *    Rev 1.13   Jul 04 2005 21:01:28   mtk00490
 * Add download time, throughput and fail reason to Microsoft Access
 * 
 *    Rev 1.12   Jun 24 2005 15:25:02   mtk00490
 * Support maximum 16 port download, format only type, multi-bin option
 * 
 *    Rev 1.11   Apr 14 2005 16:08:34   mtk00490
 * add stop button to stop specific or all mobile downloading and formatting
 * 
 *    Rev 1.10   Apr 14 2005 16:05:46   mtk00490
 * add stop button to stop specific or all mobile downloading and formatting
 * 
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#pragma hdrstop
#include "INIFileHandle/inc/MultiPort_Utils.h"
//------------------------------------------------------------------------------
bool getPathFromStr(AnsiString asStr, AnsiString &asPath)
{
    int iLD = asStr.LastDelimiter(":\\");
    if (iLD <= 0)
    {
        return false;
    }

    asPath = asStr.SubString(1, iLD);
    return true;
}

//-----------------------------------------------------------------------------
bool withPath(AnsiString asPath)
{
    if (asPath.LastDelimiter(":\\") <= 0)
    {
        return false;
    }
    return true;
}


