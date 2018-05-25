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
 *   T_PCMCIA.cpp
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  Power on PCMCIA card thread source file
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
 * Dec 3 2007 mtk00490
 * [STP100001572] [Multiport download tool] Multiport download tool ver 3.0748.0
 * 
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#pragma hdrstop

#ifndef _T_PCMCIA_H_
#include "T_PCMCIA.h"
#endif

#ifndef _OX_DEVICE_QUERY
#include "oxdevicequery.h"
#endif

#define OXCF950_CHIP_ID 0x16C95008 
//==============================================================================
__fastcall TPCMCIA::TPCMCIA(bool CreateSuspended, HANDLE hCOM)
        : TThread(CreateSuspended)
{
    m_hCOM = hCOM;
}

//----------------------------------------------------------------------------
void __fastcall TPCMCIA::Execute(void)
{
    // oxford COM port detection
    OxQueryDeviceInfo deviceInfo;
    DWORD bytesReturned;
    deviceInfo.dwRequestedType = OX_FOR_SERIAL_DRIVER;

    BOOL ok = DeviceIoControl(
                 m_hCOM,
                 IOCTL_OXSER_QUERY_INFO,
                 &deviceInfo,
                 sizeof(deviceInfo),
                 &deviceInfo,
                 sizeof(deviceInfo),
                 &bytesReturned,
                 NULL);

    if (!ok)
    {
        return;
    }

    if (ok)
    {
        if ((bytesReturned < sizeof(deviceInfo))        ||
            (deviceInfo.dwMagicNumber != OXMAGICNUMBER) ||
            (deviceInfo.ChipId != OXCF950_CHIP_ID)
           )
        {
            return;
        }
    }

    //g_pcmcia_power_ptr = this;
    int (*mio_pull)(HANDLE handle, int which, int up);

    HINSTANCE hDLL = LoadLibrary("miodll.dll");
    if (NULL == hDLL)
    {
        return;
    }

    mio_pull = (int (*)(HANDLE,int,int))GetProcAddress(hDLL, "mio_pull");

    if (m_hCOM == (HANDLE)-1)
    {
        return;
    }

    // reset
    mio_pull(m_hCOM, 0, 1);
    Sleep(100);
    mio_pull(m_hCOM, 0, 0);
    Sleep(100);

    // power on
    mio_pull(m_hCOM, 1, 1);
    //Sleep(3000);
    //mio_pull(hCard, 1, 0);
    FreeLibrary(hDLL);
}

