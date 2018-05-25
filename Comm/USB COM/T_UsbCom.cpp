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
 *  USB COM port thread source file
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
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/


#pragma hdrstop

#ifndef _COM_ENUM_H_
#include "brom_dll/inc/com_enum.h"
#endif

#ifndef _FLASHDOWNLOAD_H_
#include "mdt_component/thread/inc/FlashDownload.h"
#endif


#include "mdt_component/error_handler/inc/GCTrace.h"
#include "comm/com_util.h"

extern int g_iStopFlag[MAX_SUPPORT_PORT_NUM];
extern HANDLE g_hUsbComMutex;
//---------------------------------------------------------------------------
bool __fastcall TBOOT1::EnumerateUsbCom(unsigned short us_target_com_num)
{
    bool b_match = false;
    while (!b_match)
    {
        int index = us_target_com_num - m_sDnParam.i_FirstComNo;
        m_asMsg = "Please press USB download button of mobile " + IntToStr(index);
        DWORD dwWaitResult;

        //GC_TRACE("====== Tboot::begin wait into usb com cirtical section ==%d======", index);
		
        dwWaitResult = WaitForSingleObject(g_hUsbComMutex, 3000L);
        if (BOOT_STOP == g_iStopFlag[index])
        {
            ReleaseMutex(g_hUsbComMutex);
            return false;
        }

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
            {
                unsigned short us_com_port_array[255];
                unsigned short us_com_port_count=255;
                int result = ComPortEnumerate(us_com_port_array, &us_com_port_count);
                //int result = ComPortEnumerateEx(COM_ENUM_BY_CREATEFILE, us_com_port_array, &us_com_port_count);
                ReleaseMutex(g_hUsbComMutex);

               //GC_TRACE("====== Tboot:: ==%d %d %d %d======", us_com_port_array[0], us_com_port_array[1], us_com_port_array[2], us_com_port_array[3] );

      		  if (0 == result) 
                {
                    for (unsigned short i=0; i<us_com_port_count; i++)
                    {
                        if (us_target_com_num == us_com_port_array[i])
                        {
                            b_match = true;
                            return true;
                        }
                    }
                }
                Sleep(20);
                if (BOOT_STOP == g_iStopFlag[index])
                {
                    return false;
                }
            }
            break;

            case WAIT_TIMEOUT:
            default:
                continue;

        } // switch()
    } // while()
    return false;
}

bool __fastcall TBOOT1::WaitForUSBCOMPortDisappear(unsigned short us_target_com_num)
{
//Check is USB_COM_Port disappear by check windows register,
//but sometimes USB_COM_Port do not disappear in windows register.
#if 1
	bool IsDisappear = false;

	GC_TRACE("====== Tboot::Wait For USB COM Port %d Disappear ", us_target_com_num);
			
	while (!IsDisappear)
	{
		int index = us_target_com_num - m_sDnParam.i_FirstComNo;
		m_asMsg = "Please press USB download button of mobile " + IntToStr(index);
		DWORD dwWaitResult;

		dwWaitResult = WaitForSingleObject(g_hUsbComMutex, 3000L);
		if (BOOT_STOP == g_iStopFlag[index])
		{
			ReleaseMutex(g_hUsbComMutex);
			return false;
		}

		switch (dwWaitResult)
		{
			case WAIT_OBJECT_0:
			{
				unsigned short us_com_port_array[255];
				unsigned short us_com_port_count=255;
				int result = ComPortEnumerate(us_com_port_array, &us_com_port_count);
				//int result = ComPortEnumerateEx(COM_ENUM_BY_CREATEFILE, us_com_port_array, &us_com_port_count);
				ReleaseMutex(g_hUsbComMutex);

			   //GC_TRACE("====== Tboot:: ==%d %d %d %d======", us_com_port_array[0], us_com_port_array[1], us_com_port_array[2], us_com_port_array[3] );

				if (0 == result) 
				{
					IsDisappear=true;
					for (unsigned short i=0; i<us_com_port_count; i++)
					{
						if (us_target_com_num == us_com_port_array[i])
						{
							IsDisappear = false;
							break;
						}
					}
				}
				//Sleep(20);
				//Sleep(120);
				if(IsDisappear)
				{
					GC_TRACE("====== Tboot::USB COM Port %d Disappear ", us_target_com_num);
					return true;
				}			
				if (BOOT_STOP == g_iStopFlag[index])
				{
					return false;
				}
			}
			break;

			case WAIT_TIMEOUT:
			default:
				continue;

		} // switch()
	} // while()
	return false;
#elif 0
	bool IsDisappear = false;

	GC_TRACE("====== Tboot::Wait For USB COM Port %d Disappear By Open Com Port %d",us_target_com_num, us_target_com_num);
			
	while (!IsDisappear)
	{
		int index = us_target_com_num - m_sDnParam.i_FirstComNo;
		m_asMsg = "Please press USB download button of mobile " + IntToStr(index);
		DWORD dwWaitResult;

		dwWaitResult = WaitForSingleObject(g_hUsbComMutex, 3000L);
		if (BOOT_STOP == g_iStopFlag[index])
		{
			ReleaseMutex(g_hUsbComMutex);
			return false;
		}

		switch (dwWaitResult)
		{
			case WAIT_OBJECT_0:
			{
				/*
				unsigned short us_com_port_array[255];
				unsigned short us_com_port_count=255;
				int result = ComPortEnumerate(us_com_port_array, &us_com_port_count);
				int result = ComPortEnumerateEx(COM_ENUM_BY_CREATEFILE, us_com_port_array, &us_com_port_count);
				*/
				if(IsUSBCOMPortCanBeOpen(us_target_com_num))
				{
					IsDisappear=false;
				}
				else
				{
					IsDisappear=true;
				}
				ReleaseMutex(g_hUsbComMutex);
			   //GC_TRACE("====== Tboot:: ==%d %d %d %d======", us_com_port_array[0], us_com_port_array[1], us_com_port_array[2], us_com_port_array[3] );
				if(IsDisappear)
				{
					GC_TRACE("====== Tboot::USB COM Port %d Disappear ", us_target_com_num);
					return true;
				}
				if (BOOT_STOP == g_iStopFlag[index])
				{
					return false;
				}
				Sleep(20);
				//Sleep(120);			
			}
			break;

			case WAIT_TIMEOUT:
			default:
				continue;

		} // switch()
	} // while()
	return false;
#else
	bool IsDisappear = false;

	GC_TRACE("====== Tboot::Wait For USB COM Port %d Disappear ", us_target_com_num);
			
	while (!IsDisappear)
	{
		int index = us_target_com_num - m_sDnParam.i_FirstComNo;
		m_asMsg = "Please press USB download button of mobile " + IntToStr(index);
		DWORD dwWaitResult;

		dwWaitResult = WaitForSingleObject(g_hUsbComMutex, 3000L);
		if (BOOT_STOP == g_iStopFlag[index])
		{
			ReleaseMutex(g_hUsbComMutex);
			return false;
		}

		switch (dwWaitResult)
		{
			case WAIT_OBJECT_0:
			{
				unsigned short us_com_port_array[255];
				unsigned short us_com_port_count=255;
				int result = ComPortEnumerate(us_com_port_array, &us_com_port_count);
				//int result = ComPortEnumerateEx(COM_ENUM_BY_CREATEFILE, us_com_port_array, &us_com_port_count);
				ReleaseMutex(g_hUsbComMutex);

			   //GC_TRACE("====== Tboot:: ==%d %d %d %d======", us_com_port_array[0], us_com_port_array[1], us_com_port_array[2], us_com_port_array[3] );

				if (0 == result) 
				{
					IsDisappear=true;
					for (unsigned short i=0; i<us_com_port_count; i++)
					{
						if (us_target_com_num == us_com_port_array[i])
						{
							IsDisappear = false;
							break;
						}
					}
				}
				if(IsDisappear)
				{
					GC_TRACE("====== Tboot::USB COM Port %d Disappear ", us_target_com_num);
					return true;
				}
				else
				{
					if(IsUSBCOMPortCanBeOpen(us_target_com_num))
					{
						IsDisappear=false;
					}
					else
					{
						IsDisappear=true;
						GC_TRACE("====== Tboot::USB COM Port %d Disappear ", us_target_com_num);
						return true;
					}
				}
				if (BOOT_STOP == g_iStopFlag[index])
				{
					return false;
				}
				Sleep(20);
				//Sleep(120);
			}
			break;

			case WAIT_TIMEOUT:
			default:
				continue;

		} // switch()
	} // while()
	return false;

		
#endif
}


bool __fastcall TBOOT1::waitforUsbComClear(unsigned short us_target_com_num)
{
    bool b_match = false;
    while (!b_match)
    {
        int index = us_target_com_num - m_sDnParam.i_FirstComNo;
        //m_asMsg = "Please press USB download button of mobile " + IntToStr(index);
        DWORD dwWaitResult;

        if (BOOT_STOP == g_iStopFlag[index])
        {
              return false;
        }
        //GC_TRACE("====== Tboot::begin wait into usb com cirtical section ==%d======", index);
		
        dwWaitResult = WaitForSingleObject(g_hUsbComMutex, 3000L);
        if (BOOT_STOP == g_iStopFlag[index])
        {
            ReleaseMutex(g_hUsbComMutex);
            return false;
        }

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
            {
                unsigned short us_com_port_array[255];
                unsigned short us_com_port_count=255;
                int result = ComPortEnumerate(us_com_port_array, &us_com_port_count);
                //int result = ComPortEnumerateEx(COM_ENUM_BY_CREATEFILE, us_com_port_array, &us_com_port_count);
                ReleaseMutex(g_hUsbComMutex);

               //GC_TRACE("====== Tboot:: ==%d %d %d %d======", us_com_port_array[0], us_com_port_array[1], us_com_port_array[2], us_com_port_array[3] );

      		if (0 == result) 
                {
                    for (unsigned short i=0; i<us_com_port_count; i++)
                    {
                        if (us_target_com_num == us_com_port_array[i])
                        {
                            b_match = true;
			    break;
                        }
                    }
		    if(b_match)
		    {
		       b_match = false;
		       continue;
		    }
		    else //no find
		    {
		       return true;
		    }
		     
              }
              Sleep(100);
              if (BOOT_STOP == g_iStopFlag[index])
              {
                   return false;
              }
            }
            break;

            case WAIT_TIMEOUT:
            default:
                continue;

        } // switch()
    } // while()
    return false;
}


