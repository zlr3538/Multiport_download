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
 *   MultiPort_Utils.h
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  Multiport download utility header
 *
 * Author:
 * -------
 *  Andy Ueng (mtk00490)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision:   1.15  $
 * $Modtime:   Sep 25 2005 11:47:46  $
 * $Log:   //mtkvs01/vmdata/Multiport_Download/archives/Multiport_Download/INIFileHandle/MultiPort_Utils.h-arc  $
 *
 * Aug 12 2008 mtk00490
 * [STP100001788] [Multiport download tool] Multiport download tool ver 3.0832.0
 * 
 * 
 *    Rev 1.15   Sep 25 2005 12:02:50   mtk00490
 * Support NFB download and NAND flash format
 * 
 *    Rev 1.14   Sep 02 2005 10:22:46   mtk00490
 * Support MT6227, MT6228 baseband chip
 * 
 *    Rev 1.13   Jul 11 2005 14:45:34   mtk00490
 * Add set to factory default
 * 
 *    Rev 1.12   Jul 04 2005 21:01:30   mtk00490
 * Add download time, throughput and fail reason to Microsoft Access
 * 
 *    Rev 1.11   Jun 24 2005 15:25:04   mtk00490
 * Support maximum 16 port download, format only type, multi-bin option
 * 
 *    Rev 1.10   Apr 14 2005 16:08:34   mtk00490
 * add stop button to stop specific or all mobile downloading and formatting
 * 
 *    Rev 1.9   Feb 18 2005 11:18:28   mtk00490
 * Update brom.dll and download agent ver 2.4.1009 to resolve INTEL W18/W30 series flash doesn't support Buffered-Program
 * 
 *    Rev 1.8   Dec 01 2004 10:00:10   mtk00490
 * Multiport download tool ver 2.4.1007 (Add status indicator--download successful:green light, download fail:red light)
 * 
 *    Rev 1.7   Nov 05 2004 17:15:24   mtk00490
 * Multiport download tool ver 2.4.1007 (Support automatic baseband chip and external clock rate detection)
 * 
 *    Rev 1.6   Sep 08 2004 19:48:48   mtk00490
 * Multiport download tool ver 2.4.1004
 * 
 *    Rev 1.4   Aug 28 2004 21:10:28   mtk00490
 * Multiport download ver 2.4.1003
 * 
 *    Rev 1.3   Aug 28 2004 20:47:50   mtk00490
 * Multiport download ver 2.4.1002
 * 
 *    Rev 1.2   Jul 19 2004 17:27:52   mtk00490
 * Multiport download ver 2.4.0
 * 
 *    Rev 1.1   Jun 02 2004 21:15:50   mtk00490
 * Multiport download ver 2.3.0
 * Resolution for 2: Multiport download ver 2.3.0
 * 
 *    Rev 1.0   Mar 22 2004 15:13:24   mtk00490
 * Initial revision.
 * Resolution for 1: Multiport download ver 2.1.0
 * 
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef _MULTIPORT_UTILS_H_
#define _MULTIPORT_UTILS_H_

#include <vcl.h>
//-----------------------------------------------------------------------------
extern bool getPathFromStr(AnsiString asStr, AnsiString &asPath);
extern bool withPath(AnsiString asPath);

#endif
