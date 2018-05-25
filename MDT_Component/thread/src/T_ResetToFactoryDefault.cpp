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
 *   T_GPS.cpp
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  Backup and restore calibration data thread source file
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
 * Aug 13 2008 mtk00490
 * [STP100001788] [Multiport download tool] Multiport download tool ver 3.0832.0
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#pragma hdrstop

#ifndef META_DLL_H
#include "meta_dll/inc/meta.h"
#endif

#ifndef _FLASHDOWNLOAD_H_
#include "mdt_component/thread/inc/FlashDownload.h"
#endif


//----------------------------------------------------------------------------
META_RESULT _fastcall TBOOT1::Reset_To_Factory_Default_Procedure(const BBCHIP_TYPE bbchip, const EXT_CLOCK ext_clock)
{
    m_eMetaappOp = METAAPP_OP_RESET_TO_FACTORY_DEFAULT;
    META_RESULT MetaResult;
    BOOT_RESULT boot_result;
    MetaResult = Enter_META_Mode(boot_result,bbchip, ext_clock);
    if (MetaResult != META_SUCCESS)
    {
        return MetaResult;
    }

    MetaResult = Reset_To_Factory_Default();
    if (MetaResult != META_SUCCESS)
    {
        return MetaResult;
    }

    if (DN_WITHOUT_BK_AND_RS_CAL_DATA == m_sDnParam.e_backup_cal_data_op)
    {
        Exit_META_Mode();
    }
    return META_SUCCESS;
}

//----------------------------------------------------------------------------
META_RESULT _fastcall TBOOT1::Reset_To_Factory_Default(void)
{
    META_RESULT MetaResult;
    MetaResult = META_NVRAM_ResetToFactoryDefault_r(m_sDnParam.i_meta_handle, 40000);
    if (MetaResult != META_SUCCESS)
    {
        SyncStopFactoryDefaultProgress();
        //m_asMsg = "META_NVRAM_ResetToFactoryDefault(): ERROR: " + AnsiString(META_GetErrorString(meta_ret));
        //Synchronize(ShowMsg);
        return MetaResult;
    }

    m_asMsg = "Reset to factory default Succesfully ";
    Synchronize(ShowMsg);
    SyncFinishFactoryDefaultProgress();
    return META_SUCCESS;
}



