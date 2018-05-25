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
*   MultiPortFlashDownloadTool.cpp
*
* Project:
* --------
*   Multiport download
*
* Description:
* ------------
*  Multiport download form source
*
* Author:
* -------
*  Andy Ueng (mtk00490)
*
*============================================================================
*             HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.12  $
* $Modtime:   Jun 24 2005 15:13:30  $
* $Log:   //mtkvs01/vmdata/Multiport_Download/archives/Multiport_Download/MultiPortFlashDownloadTool.cpp-arc  $
*
* Sep 10 2008 MTK02172
* [STP100001803] [Multiport download tool] Multiport download tool ver 3.0836.0
*
*
* Aug 12 2008 mtk00490
* [STP100001788] [Multiport download tool] Multiport download tool ver 3.0832.0
*
*
* May 21 2008 mtk00490
* [STP100001729] [Multiport download tool] Multiport download tool ver 3.0820.0
*
*
* Feb 26 2008 mtk00490
* [STP100001648] [Multiport download tool] Multiport download tool ver 3.0808.0
*
*
* Dec 3 2007 mtk00490
* [STP100001572] [Multiport download tool] Multiport download tool ver 3.0748.0
*
*
* Sep 9 2007 mtk00490
* [STP100001508] [Multiport download tool] Multiport download tool ver 3.2.0
*
*
* Mar 13 2007 mtk00490
* [STP100001333] [Multiport download tool] Multiport download tool ver 3.1.04
*
*
* Nov 29 2006 mtk00490
* [STP100001239] [Multiport download tool] Multiport download tool ver 3.1.02
*
*
* Nov 29 2006 mtk00490
* [STP100001237] [Multiport download tool] Multiport download tool ver 2.9.1006
*
*
* Jun 21 2006 MTK00490
* [STP100000939] Multiport download Tool_v2.9.1001
*
*
*    Rev 1.12   Jun 24 2005 15:25:08   mtk00490
* Support maximum 16 port download, format only type, multi-bin option
*
*    Rev 1.11   Apr 14 2005 16:08:36   mtk00490
* add stop button to stop specific or all mobile downloading and formatting
*
*    Rev 1.10   Apr 14 2005 16:05:48   mtk00490
* add stop button to stop specific or all mobile downloading and formatting
*
*    Rev 1.9   Feb 18 2005 11:18:38   mtk00490
* Update brom.dll and download agent ver 2.4.1009 to resolve INTEL W18/W30 series flash doesn't support Buffered-Program
*
*    Rev 1.8   Dec 01 2004 10:00:16   mtk00490
* Multiport download tool ver 2.4.1007 (Add status indicator--download successful:green light, download fail:red light)
*
*    Rev 1.7   Nov 05 2004 17:15:32   mtk00490
* Multiport download tool ver 2.4.1007 (Support automatic baseband chip and external clock rate detection)
*
*    Rev 1.6   Sep 08 2004 19:48:50   mtk00490
* Multiport download tool ver 2.4.1004
*
*    Rev 1.4   Aug 28 2004 21:10:28   mtk00490
* Multiport download ver 2.4.1003
*
*    Rev 1.3   Aug 28 2004 20:47:52   mtk00490
* Multiport download ver 2.4.1002
*
*    Rev 1.2   Jul 19 2004 17:27:52   mtk00490
* Multiport download ver 2.4.0
*
*    Rev 1.1   Jun 02 2004 21:15:52   mtk00490
* Multiport download ver 2.3.0
* Resolution for 2: Multiport download ver 2.3.0
*
*    Rev 1.0   Mar 22 2004 15:13:00   mtk00490
* Initial revision.
* Resolution for 1: Multiport download ver 2.1.0
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*============================================================================
****************************************************************************/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <inifiles.hpp>
#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <setupapi.h>
#include <Registry.hpp>

#include <list>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <string.h>



#include "Brom_dll/inc/com_enum.h"
#include "meta_dll/inc/meta.h"
#include "comm/com_util.h"

#include <Shlobj.h>
#include <FileCtrl.hpp>
#include <Dbt.h>

#include "Brom_dll/inc/USBSwitchDLLibrary.h"
#include "brom_dll/inc/sp_brom.h"


#include "Des/inc/des.h"



// form
#ifndef form_AboutH
#include "form_About.h"
#endif

#ifndef Form_ChangepwH
#include "Form_Changepw.h"
#endif

#ifndef Form_EngineerPasswdH
#include "Form_EngineerPasswd.h"
#endif


//#ifndef _FORM_MULTILOAD_H_
//#include "form_MultiLoad.h"  //no use now
//#endif

#include "Multiport_Common.h"

#ifndef _MD_MSG_
#include "MD_msg.h"
#endif

#ifndef _MUTLIPORTFLASHDOWNLOADTOOL_H_
#include "MultiPortFlashDownloadTool.h"
#endif

#ifndef _FLASHDOWNLOAD_H_
#include "FlashDownLoad.h"
#endif

// database
#ifndef _FACTORY_COMMON_H_
#include "factory_common.h"
#endif

// misc
#ifndef  _FILE_UTILS_H_
#include "file_utils.h"
#endif

#include "MDT_Component/error_handler/inc/GCTrace.h"
#include "com_util.h"

#include "InputImageDlg.h"
#include "EFuseWriterViewerForm.h"
#include "SV5_DownloadThread/inc/SV5_DownloadThread.h"
#include "efusewriter/inc/EFuseWriter.h"
#include "MDT_Component/error_handler/inc/MDT_ErrorTypes.h"
#include "efusewriter/inc/EFuseReader.h"
#include "mdt_component/thread/inc/OSD_com_port_manager.h"

using namespace std;

//---------------------------------------------------------------------------
/*
typedef enum
{
MPDT_SB_MSG_IDX = 0,
MPDT_SB_TOTAL_NUM_IDX,
MPDT_SB_CURRENT_NUM_IDX
}E_MPDT_SB_INDEX;
*/
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TMainForm *MainForm;
struct DL_HANDLE	*g_DL_HANDLE = NULL;
struct DA_HANDLE	*g_DA_HANDLE = NULL;
AUTH_HANDLE_T	        g_AUTH_HANDLE = NULL;
bool            g_AUTH_HANDLE_Loaded = false;//mingxue 2012-12-12
DL_HANDLE_T             *g_pDL_HANDLE[MAX_SUPPORT_LOAD_NUM+1];
DL_HANDLE_LIST_T        g_DL_HANDLE_LIST;

ROOTCERT_HANDLE_T  g_ROOTCERT_HANDLE = NULL;
bool g_is_Root_Cert_File_Loaded = false;
ROOTCERT_HANDLE_T  g_ROOTCERT_HANDLE_DL = NULL;
bool g_is_Root_Cert_File_In_Download_Handle = false;
SCERT_HANDLE_T  g_SCERT_HANDLE = NULL;
bool g_is_Certificate_File_Loaded = false;
bool g_is_Send_Root_Cert_Forcely = false;

HANDLE hPostMsgDestHandle;  ///handle point to this main frame
bool isStopTrigger[MAX_SUPPORT_PORT_NUM];

//for resolve two station usb download auto polling issue
//bool isFirstTwoStationUSBDownload[MAX_SUPPORT_PORT_NUM];
extern TEFuseWriterParameterReader* G_EFuseWriterReader;

// access
HANDLE hSemaphore;  ///use for factory database log

//extern  bool isShowNoFormatInfo;  ///no use
//extern  bool isShowFileNotLoaded; ///no use
//extern  int boot_stop;


// PCMCIA card
//TThread* g_p_PCMCIA[MAX_SUPPORT_PORT_NUM];

// USB COM
HANDLE g_hUsbComMutex;

//HANDLE g_hDisableBLMutex;
map<int, int> g_comport_status_map;

vector<int> G_All_USB_ComPort;

//OSD_USB_Com_Port_Number_Manager* g_p_osd_usb_com_port_number_manager;
//for stress test record total running times
//int AutoPullTimes=0;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
: TForm(Owner)
{
  //assign each checkbox to array, easy for use subscript to index
  cbCOMArray[0]  = cbCOM1;
  cbCOMArray[1]  = cbCOM2;
  cbCOMArray[2]  = cbCOM3;
  cbCOMArray[3]  = cbCOM4;
  cbCOMArray[4]  = cbCOM5;
  cbCOMArray[5]  = cbCOM6;
  cbCOMArray[6]  = cbCOM7;
  cbCOMArray[7]  = cbCOM8;
  cbCOMArray[8]  = cbCOM9;
  cbCOMArray[9]  = cbCOM10;
  cbCOMArray[10] = cbCOM11;
  cbCOMArray[11] = cbCOM12;
  cbCOMArray[12] = cbCOM13;
  cbCOMArray[13] = cbCOM14;
  cbCOMArray[14] = cbCOM15;
  cbCOMArray[15] = cbCOM16;

  lblTimeArray[0] = lblCOM1Time;
  lblTimeArray[1] = lblCOM2Time;
  lblTimeArray[2] = lblCOM3Time;
  lblTimeArray[3] = lblCOM4Time;
  lblTimeArray[4] = lblCOM5Time;
  lblTimeArray[5] = lblCOM6Time;
  lblTimeArray[6] = lblCOM7Time;
  lblTimeArray[7] = lblCOM8Time;
  lblTimeArray[8] = lblCOM9Time;
  lblTimeArray[9] = lblCOM10Time;
  lblTimeArray[10] = lblCOM11Time;
  lblTimeArray[11] = lblCOM12Time;
  lblTimeArray[12] = lblCOM13Time;
  lblTimeArray[13] = lblCOM14Time;
  lblTimeArray[14] = lblCOM15Time;
  lblTimeArray[15] = lblCOM16Time;

  COMPercentageArray[0]  = COM1Percentage;
  COMPercentageArray[1]  = COM2Percentage;
  COMPercentageArray[2]  = COM3Percentage;
  COMPercentageArray[3]  = COM4Percentage;
  COMPercentageArray[4]  = COM5Percentage;
  COMPercentageArray[5]  = COM6Percentage;
  COMPercentageArray[6]  = COM7Percentage;
  COMPercentageArray[7]  = COM8Percentage;
  COMPercentageArray[8]  = COM9Percentage;
  COMPercentageArray[9]  = COM10Percentage;
  COMPercentageArray[10] = COM11Percentage;
  COMPercentageArray[11] = COM12Percentage;
  COMPercentageArray[12] = COM13Percentage;
  COMPercentageArray[13] = COM14Percentage;
  COMPercentageArray[14] = COM15Percentage;
  COMPercentageArray[15] = COM16Percentage;

  cbAutoPollingArray[0]  = cbAutoPolling1;
  cbAutoPollingArray[1]  = cbAutoPolling2;
  cbAutoPollingArray[2]  = cbAutoPolling3;
  cbAutoPollingArray[3]  = cbAutoPolling4;
  cbAutoPollingArray[4]  = cbAutoPolling5;
  cbAutoPollingArray[5]  = cbAutoPolling6;
  cbAutoPollingArray[6]  = cbAutoPolling7;
  cbAutoPollingArray[7]  = cbAutoPolling8;
  cbAutoPollingArray[8]  = cbAutoPolling9;
  cbAutoPollingArray[9]  = cbAutoPolling10;
  cbAutoPollingArray[10] = cbAutoPolling11;
  cbAutoPollingArray[11] = cbAutoPolling12;
  cbAutoPollingArray[12] = cbAutoPolling13;
  cbAutoPollingArray[13] = cbAutoPolling14;
  cbAutoPollingArray[14] = cbAutoPolling15;
  cbAutoPollingArray[15] = cbAutoPolling16;

  shpCOMArray[0]  = shpCOM1;
  shpCOMArray[1]  = shpCOM2;
  shpCOMArray[2]  = shpCOM3;
  shpCOMArray[3]  = shpCOM4;
  shpCOMArray[4]  = shpCOM5;
  shpCOMArray[5]  = shpCOM6;
  shpCOMArray[6]  = shpCOM7;
  shpCOMArray[7]  = shpCOM8;
  shpCOMArray[8]  = shpCOM9;
  shpCOMArray[9]  = shpCOM10;
  shpCOMArray[10] = shpCOM11;
  shpCOMArray[11] = shpCOM12;
  shpCOMArray[12] = shpCOM13;
  shpCOMArray[13] = shpCOM14;
  shpCOMArray[14] = shpCOM15;
  shpCOMArray[15] = shpCOM16;

  pbCOMArray[0]  = pbCOM1;
  pbCOMArray[1]  = pbCOM2;
  pbCOMArray[2]  = pbCOM3;
  pbCOMArray[3]  = pbCOM4;
  pbCOMArray[4]  = pbCOM5;
  pbCOMArray[5]  = pbCOM6;
  pbCOMArray[6]  = pbCOM7;
  pbCOMArray[7]  = pbCOM8;
  pbCOMArray[8]  = pbCOM9;
  pbCOMArray[9]  = pbCOM10;
  pbCOMArray[10] = pbCOM11;
  pbCOMArray[11] = pbCOM12;
  pbCOMArray[12] = pbCOM13;
  pbCOMArray[13] = pbCOM14;
  pbCOMArray[14] = pbCOM15;
  pbCOMArray[15] = pbCOM16;


  btnCOMStartArray[0]  = btnCOM1Start;
  btnCOMStartArray[1]  = btnCOM2Start;
  btnCOMStartArray[2]  = btnCOM3Start;
  btnCOMStartArray[3]  = btnCOM4Start;
  btnCOMStartArray[4]  = btnCOM5Start;
  btnCOMStartArray[5]  = btnCOM6Start;
  btnCOMStartArray[6]  = btnCOM7Start;
  btnCOMStartArray[7]  = btnCOM8Start;
  btnCOMStartArray[8]  = btnCOM9Start;
  btnCOMStartArray[9]  = btnCOM10Start;
  btnCOMStartArray[10] = btnCOM11Start;
  btnCOMStartArray[11] = btnCOM12Start;
  btnCOMStartArray[12] = btnCOM13Start;
  btnCOMStartArray[13] = btnCOM14Start;
  btnCOMStartArray[14] = btnCOM15Start;
  btnCOMStartArray[15] = btnCOM16Start;

  btnCOMStopArray[0]  = btnCOM1Stop;
  btnCOMStopArray[1]  = btnCOM2Stop;
  btnCOMStopArray[2]  = btnCOM3Stop;
  btnCOMStopArray[3]  = btnCOM4Stop;
  btnCOMStopArray[4]  = btnCOM5Stop;
  btnCOMStopArray[5]  = btnCOM6Stop;
  btnCOMStopArray[6]  = btnCOM7Stop;
  btnCOMStopArray[7]  = btnCOM8Stop;
  btnCOMStopArray[8]  = btnCOM9Stop;
  btnCOMStopArray[9]  = btnCOM10Stop;
  btnCOMStopArray[10] = btnCOM11Stop;
  btnCOMStopArray[11] = btnCOM12Stop;
  btnCOMStopArray[12] = btnCOM13Stop;
  btnCOMStopArray[13] = btnCOM14Stop;
  btnCOMStopArray[14] = btnCOM15Stop;
  btnCOMStopArray[15] = btnCOM16Stop;

  m_stBkStatus[0]  = m_stBkStatus0;
  m_stBkStatus[1]  = m_stBkStatus1;
  m_stBkStatus[2]  = m_stBkStatus2;
  m_stBkStatus[3]  = m_stBkStatus3;
  m_stBkStatus[4]  = m_stBkStatus4;
  m_stBkStatus[5]  = m_stBkStatus5;
  m_stBkStatus[6]  = m_stBkStatus6;
  m_stBkStatus[7]  = m_stBkStatus7;
  m_stBkStatus[8]  = m_stBkStatus8;
  m_stBkStatus[9]  = m_stBkStatus9;
  m_stBkStatus[10] = m_stBkStatus10;
  m_stBkStatus[11] = m_stBkStatus11;
  m_stBkStatus[12] = m_stBkStatus12;
  m_stBkStatus[13] = m_stBkStatus13;
  m_stBkStatus[14] = m_stBkStatus14;
  m_stBkStatus[15] = m_stBkStatus15;

  m_p_scatter_manager=new ScatterFileManager(&g_DL_HANDLE_LIST,&INIFileH);
  m_p_Config_Manager=new ConfigFileManager(&g_DL_HANDLE_LIST,&INIFileH);
  m_p_LinkMapFileManager=NULL;

  memset(&m_boot_Cert,0x00,sizeof(m_boot_Cert));
  USBCardDownloadHandle = NULL;

  //initialize efuse parameter
  /*
  p_efuse_write_file_reader = NULL;
  p_efuse_lock_file_reader = NULL;
  p_efuse_write_lock_argument = NULL;
  */
  //m_m_mdt_efuse_parameter_reader.clear();
}


bool __fastcall TMainForm::response_usb_message(void)
{
    // when start, on. when stop, off
    // off, on
    return true;
}

int _strupr_s( char *str, int numberOfElements )
{
    if(NULL == str)
    {
        return EINVAL; //fail
    }
    if(numberOfElements <= strlen(str) )
    {
        return EINVAL; //fail
    }
   // if(NULL == _strupr(str))
    //{
      //  return EINVAL; //fail
   // }
    return 0; //success
}


E_CheckUSBResult __fastcall TMainForm::query_current_comport(IN int begin_comport,
                                                             INOUT int *current_comport)
{

//Original Detect method~~
#if 1
    //////////////

    DWORD i;
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA DeviceInfoData;
    AnsiString KeyPath;

    //	GUID_SERENUM_BUS_ENUMERATOR
    //	{4D36E978-E325-11CE-BFC1-08002BE10318};
    GUID guidPortClass =
    {
        0x4D36E978L, 0xE325, 0x11CE,
        { 0xBF, 0xC1,  0x08,  0x00,  0x2B,	0xE1,  0x03,  0x18 }
    };

    memset(current_comport, 0, sizeof(int)*MAX_SUPPORT_PORT_NUM);

    // Create a HDEVINFO with all present devices.
    hDevInfo = SetupDiGetClassDevs((GUID*)&guidPortClass, 0, 0,  DIGCF_PRESENT );

    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        return CHECKUSB_PRESENT_DEVICE_FAIL;
    }

    // Enumerate through all devices in Set.
    TCHAR rawbuf[256];
    AnsiString comport="";        //for example:   "COM3"   "LTP1"   ..
    AnsiString comport_type="";   //for example:   "COM"    "LTP"
    AnsiString comport_num="";    //for example:         "3"
    AnsiString DeviceInstanceId="";  //for example:  "USB\\Vid_0e8d&Pid_0003\\5&11339659&0&1"

    TRegistry *Registry = new TRegistry;
    int com_number=0;
    int comport_count=0;
	char usb_device_friendly_name[512];
	char* COM_Start=NULL;
	int idLen =512;

	AnsiString DeviceHardwareId = "";

    //add mtk71518 2013-07-17 for DualTalk
	AnsiString subDeviceHardwareId = "";
	int preLoaderidStrlen = m_preloaderdeviceid.Length();

    Registry->RootKey = HKEY_LOCAL_MACHINE;
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    for (i=0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
    {
#if 1
        SetupDiGetDeviceInstanceId(hDevInfo, &DeviceInfoData, rawbuf, sizeof(rawbuf), NULL);

        //  get hardware id  for USB 1.1 to 2.0
        char hardwareID[512];
        if(!SetupDiGetDeviceRegistryProperty(
            hDevInfo,
            &DeviceInfoData,
            SPDRP_HARDWAREID,
            NULL,
            (PBYTE)hardwareID,
            idLen-1,
            NULL))
        {
            GC_TRACE("Get Hardware ID failed");
        }
        // parse hardware ID
        _strupr_s(hardwareID,512);
        char *pch_id = strchr(hardwareID, '\\');
        if(!pch_id) continue;
        GC_TRACE( "Get Device info : HardwareID = %s", pch_id+1);

        pch_id = pch_id+1;
        DeviceHardwareId = AnsiString(pch_id);
        //  end get hardware id  for USB 1.1 to 2.0

        DeviceInstanceId = rawbuf;
        DeviceInstanceId.Trim();
        // find your specific device here
        KeyPath.sprintf("SYSTEM\\CurrentControlSet\\Enum\\%s\\Device Parameters", DeviceInstanceId);
	//	if(!Registry->OpenKey(KeyPath.c_str(),false))//huifen
        if(!Registry->OpenKeyReadOnly(KeyPath.c_str()))
        {   //open key fail
            delete Registry;
            return CHECKUSB_OPEN_REGISTRY_FAIL;
        }

        if( !Registry->ValueExists("PortName") )
        {   //PortName not exist
            Registry->CloseKey();
            delete Registry;
            return CHECKUSB_PORT_NOT_EXIST;
        }
        comport = Registry->ReadString("PortName");
        Registry->CloseKey();

        comport = comport.UpperCase();    //COM11
        comport_type = comport.SubString(1, 3);
        if(comport_type != "COM")
        {
            continue;
        }

        //get number
        comport_num = comport.SubString( 4, comport.Length()-3);    // 4 is the begin index
        com_number = comport_num.ToIntDef(0);
        
        //add mtk71518 for DualTalk,2013-0626
		if(mi_USBDownloadReadbackDualTalk->Checked == true)  
	    {
	        GC_TRACE( "query_current_comport: Enable External modem...");
	        GC_TRACE( "query_current_comport: comPort = %d", com_number);
			subDeviceHardwareId = DeviceHardwareId.SubString(1, preLoaderidStrlen);
			if( subDeviceHardwareId.AnsiCompareIC(m_preloaderdeviceid) == 0) 
            {  //if preloader usb then switch it to single port
                
				SP_BOOT_ARG_S stArg;
				int BootStop = SP_BOOT_INFINITE;
				int ret = S_DONE;
				
				//Parameter settings
				stArg.m_bbchip_type = SP_AUTO_DETECT_BBCHIP;
				stArg.m_ext_clock = SP_AUTO_DETECT_EXT_CLOCK;
				stArg.m_ms_boot_timeout = SP_BOOT_INFINITE;
				stArg.m_max_start_cmd_retry_count = SP_DEFAULT_BROM_START_CMD_RETRY_COUNT;
				
				stArg.m_uTimeout = 20000;
				stArg.m_uRetryTime = 2000;
				stArg.m_uInterval = 10;
				stArg.m_uBaudrate = CBR_115200;
				
				stArg.m_auth_handle = NULL;
				stArg.m_scert_handle = NULL;
				stArg.m_cb_sla_challenge = NULL;
				stArg.m_cb_sla_challenge_arg = NULL;
				stArg.m_cb_sla_challenge_end = NULL;
				stArg.m_cb_sla_challenge_end_arg = NULL;
				
				stArg.m_pStopFlag = &BootStop;
				stArg.m_bIsUSBEnable = true;
				stArg.m_bIsSymbolicEnable = false;
				stArg.m_bIsCompositeDeviceEnable = true;
				stArg.m_euBootMode = SP_DUALTALK_SWITCH;
				stArg.m_uPortNumber = com_number;
				memset(stArg.m_szPortSymbolic, 0, 256);
				GC_TRACE( "query_current_comport: after %d millisecond begin switch to Modem...", m_iDelayTimeSec);
				Sleep(m_iDelayTimeSec);
				ret = SP_Preloader_BootMode(&stArg);
				if(SP_S_DONE == ret) // change to flashtoollib api,2013-06-19,mtk71518
			    {     
			       GC_TRACE( "Switch to Modem OK...");	   
				   continue;
			    }
				else
				{
				   GC_TRACE( "Switch to Modem error, Error code = %d...", ret);
				   continue;
				}
            }
	  	}
        else
        {
           GC_TRACE( "query_current_comport: Disable External modem...");
           if(com_number < begin_comport || com_number > begin_comport + MAX_SUPPORT_PORT_NUM)
           {  //
              continue;
           }
		   
           if( DeviceHardwareId.Length())
           {
              if( DeviceHardwareId.AnsiCompareIC(m_usbdeviceid))
              {  //if device id error
                 continue;
              }
           }
        }
		
        current_comport[comport_count]= com_number;
        comport_count++;
#else
		if(!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_FRIENDLYNAME,
			NULL,
			(PBYTE)usb_device_friendly_name,
			511,
			NULL))
		{
			GC_TRACE("Get friendly name failed");
			//sprintf(usb_device_friendly_name, "Unknown");
			continue;
		}
		comport="";
		comport=usb_device_friendly_name;
		//MTK USB Port (COM36)
		comport_type = comport.SubString(15, 3);
        if(comport_type != "COM")
        {
             continue;
        }

        //get number
        comport_num = comport.SubString(18, comport.Length()-18);    // 4 is the begin index
        com_number = comport_num.ToIntDef(0);
        if(com_number < begin_comport || com_number > begin_comport + MAX_SUPPORT_PORT_NUM)
        {  //
            continue;
        }
        //
        current_comport[comport_count]= com_number;
        comport_count++;
#endif

    }//for

    //Cleanup
    delete Registry;
    SetupDiDestroyDeviceInfoList(hDevInfo);
    //GC_TRACE("query current comport: %d %d %d %d", current_comport[0], current_comport[1], current_comport[2], current_comport[3]);

    return CHECKUSB_OK;
#else
	//////////////

	int ComPortIndex=0;
	unsigned short com_number=0;
	int comport_count=0;

	memset(current_comport, 0, sizeof(int)*MAX_SUPPORT_PORT_NUM);
	unsigned short us_com_port_array[255];
	unsigned short us_com_port_count=255;
	int result = ComPortEnumerate(us_com_port_array, &us_com_port_count);

	for(ComPortIndex=0;ComPortIndex<255;ComPortIndex++)
	{
		if(0!=us_com_port_array[ComPortIndex])
		{
			com_number=us_com_port_array[ComPortIndex];
			if(com_number < begin_comport || com_number > begin_comport + MAX_SUPPORT_PORT_NUM)
			{
				continue;
			}
			else
			{
				current_comport[comport_count]= com_number;
        		comport_count++;
			}
		}
	}
    GC_TRACE("query current comport: %d %d %d %d", current_comport[0], current_comport[1], current_comport[2], current_comport[3]);

    return CHECKUSB_OK;

#endif
}

void __fastcall TMainForm::record_current_comport(IN int * current_comport)
{
    //save to global list
    //list<int> g_comport_status_list
    int i=0;

    g_comport_status_map.clear();
    for(i=0;i< MAX_SUPPORT_PORT_NUM; i++)
    {
        if(current_comport[i]!=0)
        {
            g_comport_status_map[current_comport[i]] = current_comport[i];
        }
        else
        {
            break;
        }
    }
}

int __fastcall TMainForm::get_current_comport_increase(IN int *current_comport,
                                                       INOUT int * current_increase_comport)
{
    int i=0;
    int index=0;

    memset(current_increase_comport, 0, sizeof(int)*MAX_SUPPORT_PORT_NUM);

    map<int,int>::iterator it;
    for(i=0;i< MAX_SUPPORT_PORT_NUM; i++)
    {
        if(current_comport[i] == 0)
        {
            break;
        }
        it = g_comport_status_map.find(current_comport[i]);
        if( it == g_comport_status_map.end() )
        {
            current_increase_comport[index] = current_comport[i];
            index++;
        }
    }

    //return the count of increased comport
    return index;
}

int  __fastcall TMainForm::get_current_comport_decrease(IN int *current_comport,
                                                        INOUT int * current_decrease_comport)
{
    int i=0;
    int index=0;
    int bfind=0;

    memset(current_decrease_comport, 0, sizeof(int)*MAX_SUPPORT_PORT_NUM);

    map<int,int>::iterator it;
    for(it=g_comport_status_map.begin(); it != g_comport_status_map.end() ; it++)
    {
        bfind=0;
        for(i=0;i< MAX_SUPPORT_PORT_NUM; i++)
        {
            if( (*it).first == current_comport[i])
            {
                bfind=1;
                break;
            }
        }
        if(bfind==0) //no find
        {
            current_decrease_comport[index] = current_comport[i];
            index++;
        }
    }

    //return the count of decreased comport
    return index;
}

void __fastcall TMainForm::OnDeviceChange(Messages::TMessage &Message)
{
    //#define DBT_DEVNODES_CHANGED            0x0007

	static SYSTEMTIME  Device_Change_Record_Time;
	static int ByPassDetectFlag;
	SYSTEMTIME  Current_Time;

	/*
    GetLocalTime(&Current_Time);
	if((Current_Time.wMinute==Device_Change_Record_Time.wMinute)&&
		(Current_Time.wSecond==Device_Change_Record_Time.wSecond)&&
		(Current_Time.wMilliseconds==Device_Change_Record_Time.wMilliseconds)&&
		(0==ByPassDetectFlag)
		)
	{
		ByPassDetectFlag=1;
        GC_TRACE("Timestamp is same,continue");
		return ;
	}
    */
	if(UART_COM==m_sDnParam.e_com_type)
	{
		GC_TRACE("TMainForm::OnDeviceChange==>Uart Download,Do Nothing ");
		return;
	}
	else if(USB_COM==m_sDnParam.e_com_type && !IsUSBDownloadWithTwoSite())//One Station Download
	{
	/*
	  if( g_p_osd_usb_com_port_number_manager->m_thread_waiting_for_usb_comport_number <= 0)
	  {
        GC_TRACE("TMainForm::OnDeviceChange==>No One Waiting... ");
        return ;
	  }
	  */
  	  GC_TRACE("TMainForm::OnDeviceChange==>One Station Download ");
	/*
	  if(Message.Msg== WM_DEVICECHANGE)
      {
      	ByPassDetectFlag=0;
          GC_TRACE("OnDeviceChange: Message.WParam ==%d ", Message.WParam);
          if(Message.WParam == DBT_DEVNODES_CHANGED)
          {
              vector<int> Current_USB_Com_Port;

  			query_current_comport_OneStation(Current_USB_Com_Port);
  			get_current_comport_increase_OneStation(Current_USB_Com_Port);
  			record_current_comport_OneStation(Current_USB_Com_Port);
          }

      }
      */

	}
	else if(USB_COM==m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite()) //two station download
	{
		GC_TRACE("TMainForm::OnDeviceChange==>Two Station Download ");
	    do{
	        if(!response_usb_message())
	        {
	            break;
	        }

	        //deal with windows message
	        if(Message.Msg== WM_DEVICECHANGE)
	        {
	        	  ByPassDetectFlag=0;
	            GC_TRACE("OnDeviceChange: Message.WParam ==%d ", Message.WParam);
	            if(Message.WParam == DBT_DEVNODES_CHANGED)
	            {
	                // 1 query the current com port set, from Registry
	                int current_comport[MAX_SUPPORT_PORT_NUM];
	                int current_increase_comport[MAX_SUPPORT_PORT_NUM];
	                int current_decrease_comport[MAX_SUPPORT_PORT_NUM];
	                int i=0, count=0;
	                query_current_comport(m_sDnParam.i_FirstComNo,current_comport);

	                // 2 compare with the older com port set,  get che change
	                count = get_current_comport_increase(current_comport, current_increase_comport);

                        GC_TRACE("Increase Com Port: %d %d %d %d", current_increase_comport[0], current_increase_comport[1], current_increase_comport[2], current_increase_comport[3]);
	                if(count)
	                {  // 3 if the change is usb insert, get the com port index
	                    for(i=0; i< count; i++)
	                    {
	                        int temp = current_increase_comport[i]-m_sDnParam.i_FirstComNo;
	                        SetEvent(Wait_USB_Insert_Event[temp]);
	                    }
	                }
	                {   //if the change is usb plug out, record it to global list
	                    record_current_comport(current_comport);
	                }
					//Record process time:
				    GetLocalTime(&Device_Change_Record_Time);
	            }

	        }
	    }while(0);
	}
	else
	{
		GC_TRACE("TMainForm::OnDeviceChange==>Error Option ");
	}
	TForm::Dispatch(&Message);

}


//---------------------------------------------------------------------------
void _fastcall TMainForm::SubClassWndProc(Messages::TMessage &Message)
{
    switch (Message.Msg)
    {
    case WM_MD_DOWNLOAD_SUCCESSFUL:
        {
            if (cbAutoPollingArray[Message.WParam]->Checked )
            {
                //isFirstTwoStationUSBDownload[(int)Message.WParam]=false;
                Set_DownloadParameter((unsigned char)Message.WParam);
                m_bStartMetaApp[(int)Message.WParam] = false;
                btnCOMDownloadClick((int)Message.WParam);
            }
        }
        break;

    case WM_MD_MISC_FOLDER_EMPTY_CHECKING_FAIL:
        {

        }
        break;

    case WM_MD_SELECT_DOWNLOAD_TYPE_FAIL:
        {
            Enable_UIComponent();
        }
        break;

    default:
        {

        }
        break;
    }

    this->WndProc(Message);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    //int i;
    //int j=0;

    TIniFile *ini;
    AnsiString as_ComportEnabled;

    hPostMsgDestHandle = this->Handle;
    WindowProc = SubClassWndProc;

    // ENABLE DEBUG
    DA_Create(&g_DA_HANDLE);
    AUTH_Create(&g_AUTH_HANDLE);

    SCERT_Create(&g_SCERT_HANDLE);
    ROOTCERT_Create(&g_ROOTCERT_HANDLE);
    ROOTCERT_Create(&g_ROOTCERT_HANDLE_DL);


    for (int i=0; i<MAX_SUPPORT_LOAD_NUM; i++)
    {
        g_pDL_HANDLE[i] = NULL;
    }

    DL_CreateList(&g_DL_HANDLE_LIST);

    //READ INI
#ifdef SERVICE_CENTER
    MainForm->Caption = (AnsiString) "Multi-port download tool (Service center)";
    rbAuto->Enabled = false;
    rbManual->Enabled = false;
    rbNOR->Enabled = false;
    rbNAND->Enabled = false;
#endif

#ifndef SERVICE_CENTER
    cbType->Items->Add("Download ROM and FAT" );
#endif

    cbType->Items->Add("Download ROM");
#ifndef SERVICE_CENTER
    cbType->Items->Add("Download ROM and Format");
    cbType->Items->Add("Format");
    //[Dongguo]this feature is not finished...disable it []
//    cbType->Items->Add("Enable Boot");
#endif

    for (int i=0; i<MAX_SUPPORT_PORT_NUM; i++)
    {
        DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;
        isStopTrigger[i] = false;
        m_bStartMetaApp[i] = false;
		    g_iStopFlag[i]=BOOT_STOP;
    }

    // initalization
    //    isFATFileLoaded = false;

    // multibin
    //    lvChanged.iChangedIndex = NO_CHANGE;
    m_sDnParam.s_multibin_op.b_check_target_resource_layout    = true;
    m_sDnParam.s_multibin_op.b_auto_load_resource_file_by_scat = true;
    m_sDnParam.s_multibin_op.b_compare_resource_project_id     = true;

    // EMI
    m_sDnParam.sEMI_NFI_Setting.ui_nand_acccon = 0;
    m_sDnParam.sEMI_NFI_Setting.b_enable_dram_setting = false;
    m_sDnParam.sEMI_NFI_Setting.ui_emi_gen_a = 0;
    m_sDnParam.sEMI_NFI_Setting.ui_emi_gen_b = 0;
    m_sDnParam.sEMI_NFI_Setting.ui_emi_gen_c = 0;
    m_sDnParam.sEMI_NFI_Setting.ui_emi_dram_con_i_mode = 0;
    m_sDnParam.sEMI_NFI_Setting.ui_emi_dram_con_i_ext_mode = 0;
    m_sDnParam.sEMI_NFI_Setting.ui_emi_dram_con_k = 0;
    m_sDnParam.sEMI_NFI_Setting.ui_emi_dram_con_l = 0;

    // event for all process finish check
    for (int i=0; i < MAX_SUPPORT_PORT_NUM; i++)
    {
        Flash_Download_Event[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    //add by changshun for wait usb insert
    for (int i=0; i < MAX_SUPPORT_PORT_NUM; i++)
    {
        Wait_USB_Insert_Event[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        User_Stop_Event[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
    }
//    One_Station_Download_USB_Insert_Event = CreateEvent(NULL, FALSE, FALSE, NULL);
//	g_p_osd_usb_com_port_number_manager =new OSD_USB_Com_Port_Number_Manager();
    // USB COM
    g_hUsbComMutex = CreateMutex(NULL, FALSE, "UsbComMutex");


    for(int i=0;i<MAX_SUPPORT_PORT_NUM;i++)
    {
        ThreadBootUpTimeTable[i]=GetTickCount();
    }
    ThreadBootUpTimeTableMutex=CreateMutex(NULL, FALSE, "ThreadBootUpTimeTableMutexName");

	/*
	if(NULL==G_EFuseWriterReader)
	{
		G_EFuseWriterReader=new TEFuseWriterParameterReader();
	}
	*/
  p_efuse_write_file_reader = NULL;
  p_efuse_lock_file_reader = NULL;

//for usbdownload_dualtalk
    memset(&dtStartupInfo, 0, sizeof(dtStartupInfo));
    memset(&dtProcessInfo, 0, sizeof(dtProcessInfo));
    dtStartupInfo.cb = sizeof(dtStartupInfo);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
  GC_TRACE("De Init Meta Dll====>");
  DeInitMETADll();
  GC_TRACE("<====De Init Meta Dll");

  GC_TRACE("Destroy DA Handle====>");
  // DESTROY HANDLE
  DA_Unload( g_DA_HANDLE );
  DA_Destroy( &g_DA_HANDLE );
  GC_TRACE("<====Destroy DA Handle");

  AUTH_Destroy(&g_AUTH_HANDLE);

  SCERT_Destroy(&g_SCERT_HANDLE);
  ROOTCERT_Destroy(&g_ROOTCERT_HANDLE);
  ROOTCERT_Destroy(&g_ROOTCERT_HANDLE_DL);

  GC_TRACE("Destroy Download Handle====>");
  //    DL_DestroyList(&g_DL_HANDLE_LIST);
  GC_TRACE("<====Destroy Download Handle");


  	GC_TRACE("Delete Download Process Mutex====>");
  // event for all process finish
  for (int i=0; i < MAX_SUPPORT_PORT_NUM; i++)
  {
      CloseHandle(Flash_Download_Event[i]);
  }

  //add by changshun for wait usb insert
  for (int i=0; i < MAX_SUPPORT_PORT_NUM; i++)
  {
      CloseHandle(Wait_USB_Insert_Event[i]);
      CloseHandle(User_Stop_Event[i]);
  }

  // USB COM
  CloseHandle(g_hUsbComMutex);
  CloseHandle(ThreadBootUpTimeTableMutex);
  GC_TRACE("<====Delete Download Process Mutex");

  if( NULL != USBCardDownloadHandle)
  {
    DisableUSBSwitch(USBCardDownloadHandle);
    USBCardDownloadHandle = NULL;
  }
  //for usbdownloaddualtalk

  //TerminateProcess(MainForm->dtProcessInfo.hProcess, 0)!=0

  if(MainForm->dtProcessInfo.hProcess != NULL)
  {
     if(TerminateProcess(MainForm->dtProcessInfo.hProcess, 0)!=0)
     {
         MainForm->sbMPDT->Panels->Items[0]->Text = "TerminateProcess OK!";
         CloseHandle(MainForm->dtProcessInfo.hThread);
         CloseHandle(MainForm->dtProcessInfo.hProcess);
     }
  }

  // Disable Debug
  Brom_DebugOff();
  SP_Brom_DebugOff();


  //clear
  /*
  if(NULL!=G_EFuseWriterReader)
  {
  	delete G_EFuseWriterReader;
  }
  */
  /*
  if ( NULL != p_efuse_write_file_reader)
  {
    delete p_efuse_write_file_reader;
  }
  if ( NULL != p_efuse_lock_file_reader)
  {
    delete p_efuse_lock_file_reader;
  }
  if ( NULL != p_efuse_common_arg)
  {
    delete p_efuse_common_arg;
  }
  if ( NULL != p_efuse_secure_arg)
  {
    delete p_efuse_secure_arg;
  }
  if ( NULL != p_efuse_lock_arg)
  {
    delete p_efuse_lock_arg;
  }

  m_m_mdt_efuse_parameter_reader.clear();
  */
  //Clear all dynamic created forms.~
  if(NULL!=Form_AboutMD)
  {
  	delete Form_AboutMD;
  }
  if(NULL!=dlgSetBeginComPort)
  {
  	delete dlgSetBeginComPort;
  }
  if(NULL!=frmInputImage)
  {
  	delete frmInputImage;
  }
  if(NULL!=tool_setting)
  {
  	delete tool_setting;
  }
  if(NULL!=EFuseWriterViewer)
  {
  	delete EFuseWriterViewer;
  }

   if(NULL!= Form_Chgpasswd)
  {
  	delete Form_Chgpasswd;
  }

   if(NULL!= Form_Engineerpw)
  {
  	delete Form_Engineerpw;
  }
  

  /*
  if(NULL !=g_p_osd_usb_com_port_number_manager)
  {
    delete g_p_osd_usb_com_port_number_manager;
  }
*/
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{

    //AnsiString as_AutoLoadResByScat;

    MainForm->Left = 13;
    MainForm->Top = 9;

    Display_MDTLog();
    Display_BROMDllLog();
    Display_METADllLog();
    Display_CheckEnableNFI();
    Display_BkAndRsOptional();
    Display_Operation();
    Display_Cable();
    Display_BasebandChip();
    Display_ExternalClock();
    Display_Baudrate();
    Display_Type();
    Display_DAFile();
    Display_AuthFile();
    Display_RootCertFile();
    Display_CertificateFile();

    Display_ComEnabled();
    Display_AutoPollingEnabled();
    Display_Read_USB_DL_WITH_TWO_SITE();
    Display_EnterMetaModeAfterDLFMT();

    Display_EnableMMAA();
    Display_Scatter();
    Display_BBChipVerChecked();
    Display_OptFlashType();

    Display_FormatFatRange();
    Display_BackupAndRestoreOption();
    Read_CalibrationFolder_option();

    // access
    Display_DataSource();
    Display_DBLogOption();

    Read_FormatFATBeginAddress();
    Read_FormatFATLength();
    Read_NANDFormatFATBeginAddress();
    Read_NANDFormatFATLength();
    Read_EraseValidation();
    Read_EMI_Setting();
    Read_usb_device_id();
	Read_SwitchToModem_DelayTime();
	Read_PasswordFilePath();

    Display_EnableUSB_2_0();
    Display_EnableBackupNvramPartion();//display backup nvram partion option
    Read_Disconnect_Comport_option(); //whether disconnect comport after USB download

    //   get_PullDownGPIO17(); //phase out now

    //init meta dll spend much time
    Get_LoginIdentify();
    if(m_LoginIdentify == LOGIN_OPERATOR)
    {
        Disable_UIComponent();
        SetWindowText(this->Handle, "Multiple Download Tool - Operator Mode");
    }
	else if(m_LoginIdentify  == LOGIN_ENGINEER)
	{
	    Engineer1->Enabled = true;
	    Engineer1->Checked = true;
	    Operator1->Enabled = false;
	    Operator1->Checked = false;
            SetWindowText(this->Handle, "Multiple Download Tool - Engineer Mode");
	}
    InitMETADll(); //

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{

    int temp_dn_status[MAX_SUPPORT_PORT_NUM];

    btnStopAllClick(this);

    TimerCOM1->Enabled=false;

    // save menu setting
    Save_BBChipVerChecked();
    Save_BkAndRsOptional();
    Save_CheckEnableNFI();
    Save_BasebandChip();
    Save_ExternalClock();
    //Save_CheckECOVersion();
    Save_EnableMMAA();
    Save_DataSource();   // access
    Save_DBLogOption(); // access
    //Save_Read_USB_DL_WITH_TWO_SITE();
    Save_EnterMetaModeAfterDLFMT();

    Save_BROMDllLog();
    Save_METADllLog();
    Save_MDTLog();

    //UI setting
    Save_OptFlashType();
    Save_Baudrate();
    Save_Operation();
    Save_Cable();
    Save_ComEnabled();
    Save_AutoPollingEnabled();
    Save_Type();
    Save_DAFile();
    Save_AuthFile();
    Save_RootCertFile();
    Save_CertificateFile();

    Save_FormatFatRange(); //format fat options
    //Save_BackupAndRestoreOption();
    Save_Scatter();

    Save_EnableUSB_2_0();
    Save_EnableBackupNvramPartion();
	Save_usb_device_id();
	Save_SwitchToModem_DelayTime();

    if(NULL!=m_p_LinkMapFileManager)
    {
        m_p_LinkMapFileManager->save_to_ini();
    }

    if( NULL != m_p_scatter_manager)
    {
        delete m_p_scatter_manager;
    }
    if( NULL != m_p_Config_Manager)
    {
        delete m_p_Config_Manager;
    }

    if(MainForm->dtProcessInfo.hProcess != NULL)
    {
       if(TerminateProcess(MainForm->dtProcessInfo.hProcess, 0)!=0)
       {
           MainForm->sbMPDT->Panels->Items[0]->Text = "TerminateProcess OK!";
           CloseHandle(MainForm->dtProcessInfo.hThread);
           CloseHandle(MainForm->dtProcessInfo.hProcess);
       }
    }
    //WaitForMultipleObjects(MAX_SUPPORT_LOAD_NUM,Flash_Download_Event,true,5000);

}


//---------------------------------------------------------------------------
//meta callback function for error handle
void __stdcall ErrorHandler(const META_CNF_ERR_CODE err)
{

}


//---------------------------------------------------------------------------
void TMainForm::InitMETADll( void )
{
    // initialize META
    META_RESULT meta_ret;
    for(int i=0; i<MAX_SUPPORT_PORT_NUM; i++ )
    {
        if( (meta_ret = META_GetAvailableHandle( &m_iMETA_handle_array[i] )) != META_SUCCESS )
        {
            AnsiString asMsg = "META_GetAvailableHandle(): ERROR: " + AnsiString(META_GetErrorString(meta_ret));
            Application->MessageBox( asMsg.c_str(), "Fail", MB_OK );
            return;
        }

        if( (meta_ret = META_Init_r( m_iMETA_handle_array[i], ErrorHandler )) != META_SUCCESS )
        {
            AnsiString asMsg = "META_Init_r(): ERROR: " + AnsiString(META_GetErrorString(meta_ret));
            Application->MessageBox( asMsg.c_str(), "Fail", MB_OK );
            return;
        }
    }
}

//---------------------------------------------------------------------------
void TMainForm::DeInitMETADll( void )
{
    META_RESULT meta_ret;
    for(int i=0; i<MAX_SUPPORT_PORT_NUM; i++ )
    {
        META_Deinit_r( &m_iMETA_handle_array[i] );
    }
}

//---------------------------------------------------------------------------
bool TMainForm::FileOpenDownloadAgentExecute()
{

    if(m_asDAPath.Length()>0)
    {   //point the dialog show path to current DA folder path
        dlgOpenDA->InitialDir = m_asDAPath;
    }

    if( dlgOpenDA->Execute() )    // *.bin file
    {
        if ( OpenReadDAFile( dlgOpenDA->FileName ))
        {
            m_asDAFileName = dlgOpenDA->FileName;
            int iLD = m_asDAFileName.LastDelimiter("\\:");

            if ( iLD > 0)
            {
                m_asDAPath = m_asDAFileName.SubString(1, iLD-1 );
            }

            return true;
        }
        else
        {
            stDAFileName->Text = "";
            return false;
        }
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------------------
int TMainForm::UpdateDAInfo( void )
{
    int ret;
    AnsiString as_msg;
    AnsiString as_dapath;
    DA_INFO	da_info;

    if(stDAFileName->Text.IsEmpty())
    {
        as_msg = "Please input DA file!";
        Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
        return 4;
    }

    // if( MT6208!=m_sDnParam.e_bbchip_type && FTHND_OK!=(ret=DA_IsReady(g_DA_HANDLE, &da_info, _TRUE)) )
    if( S_DONE!=(ret=DA_IsReady(g_DA_HANDLE, &da_info, _TRUE)) )
    {
        if( S_FTHND_FILE_IS_NOT_LOADED_YET == ret || S_FTHND_FILE_IS_UPDATED == ret )
        {
            if( S_DONE != (ret=DA_Load(g_DA_HANDLE, da_info.filepath, _TRUE)) )
            {
                if( S_FTHND_HANDLE_BUSY_NOW == ret )
                {
                    Application->MessageBox( "Program is busy! Can not reload DA right now.", "Fail", MB_OK );
                }
                else if( S_INVALID_DA_FILE == ret )
                {
                    as_dapath = da_info.filepath;
                    as_msg    = " \"" + as_dapath + "\" is not a valid DA format!";
                    Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
                    return 1;
                }
                else
                {
                    as_dapath = da_info.filepath;
                    as_msg    = " Load DA \"" + as_dapath + "\" failed!";
                    Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
                    return 2;
                }
            }
        }
        else
        {
            as_dapath = da_info.filepath;
            as_msg    = " Check DA \"" + as_dapath + "\" failed!";
            Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
            return 3;
        }
    }

    return 0;
}






//---------------------------------------------------------------------------
bool TMainForm::OpenReadDAFile( AnsiString asFileName)
{
    int ret = DA_Load(g_DA_HANDLE, asFileName.c_str(), _TRUE);

    if (ret)
    {
        if (S_FTHND_HANDLE_BUSY_NOW == ret)
        {
            Application->MessageBox("Program is busy! Can not reload DA right now.", "Fail", MB_OK);
            return false;
        }
        else if (S_INVALID_DA_FILE == ret)
        {
            AnsiString as_msg = " \"" + asFileName + "\" is not a valid DA format!";
            Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
            return false;
        }
        else
        {
            AnsiString as_msg = " Load DA file " + asFileName + " error ";
            Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
        }
        return false;
    }

    if(0 == ret)
    {
        stDAFileName->Text = asFileName;
        return true;
    }

    return false;
}


//------------------------------------------------------------------------------
E_FLASHTOOL_FUNCTION TMainForm::Get_Function( void )
{
    E_FLASHTOOL_FUNCTION func;

#ifndef SERVICE_CENTER
    if(ENABLE_BOOT_CERT == cbType->ItemIndex)
    {
      func = FLASHTOOL_ENABLE_BOOT_CERT;
    }
    else if( FORMAT_INDEX == cbType->ItemIndex )
    {
        func = FLASHTOOL_FORMAT;
    }
    else
#endif
    {
        func = FLASHTOOL_DOWNLOAD;
    }

    return func;
}

//------------------------------------------------------------------------------
void TMainForm::Set_DownloadParameter(unsigned char index)
{
    m_sComPortSetting.com.number       = index + m_sDnParam.i_FirstComNo;
    m_sComPortSetting.baudrate         = Get_Baudrate();
    m_sComPortSetting.ms_read_timeout  = COM_DEFAULT_TIMEOUT;
    m_sComPortSetting.ms_write_timeout = COM_DEFAULT_TIMEOUT;

    m_sDnParam.e_bbchip_type           = Get_BBChipType();
    m_sDnParam.e_ext_clock             = Get_ExternalClockType();

    if (m_rbUART->Checked)
    {
        m_sDnParam.e_com_type          = UART_COM;
    }
    else if(m_rbUSB->Checked)
    {
        m_sDnParam.e_com_type          = USB_COM;
    }
    else //uart + usb
    {
        m_sDnParam.e_com_type          = USB_COM;
    }

    m_sDnParam.e_Function             = Get_Function();
    m_sDnParam.e_Operation            = Get_Operation();
    m_sDnParam.e_format_op            = Get_FormatOption();
    m_sDnParam.s_multibin_op          = Get_MultiBinOption();
    Get_BBChipOption(m_sDnParam.s_bbchip_op);

    Read_FormatFATBeginAddress();//add these four here, to avoid restart tool, when modify the ini
    Read_FormatFATLength();
    Read_NANDFormatFATBeginAddress();
    Read_NANDFormatFATLength();

    m_sDnParam.i_meta_handle          = m_iMETA_handle_array[index];

    // backup and restore calibration data
    if (m_miDnWithoutBkAndRsCalData->Checked)
    {
        m_sDnParam.e_backup_cal_data_op = DN_WITHOUT_BK_AND_RS_CAL_DATA;
    }
    else if (m_miDnWithBkAndRsCalData->Checked)
    {
        m_sDnParam.e_backup_cal_data_op = DN_WITH_BK_AND_RS_CAL_DATA;
    }
    else if (m_miDnAndRsCalDataOnly->Checked)
    {
        m_sDnParam.e_backup_cal_data_op = DN_WITH_RS_CAL_DATA;
    }
    else if (m_miDnAndUlUserData->Checked)
    {
        m_sDnParam.e_backup_cal_data_op = DN_WITH_UL_USER_DATA;
    }
	else if (m_miCheckSDS->Checked)//mingxue 2013-1-21 checkSDS
	{
		m_sDnParam.e_backup_cal_data_op = CHECK_SDS_ONLY;
	}
    else if(m_miRsCalDataOnly->Checked)
    {
        m_sDnParam.e_backup_cal_data_op = RS_CAL_DATA_ONLY;
    }
    else if(m_miUploadUserDataOnly->Checked)
    {
        m_sDnParam.e_backup_cal_data_op = UPLOAD_USER_DATA_ONLY;
    }
    else
    {
        m_sDnParam.e_backup_cal_data_op = BACKUP_RESTORE_OPTOIN_END;
    }

    m_sDnParam.as_working_dir = GetWorkingDir();

    // enable  usb message, and enumerate current exist comport



    ResetEvent(Wait_USB_Insert_Event[index]);
    ResetEvent(User_Stop_Event[index]);

}


//------------------------------------------------------------------------------
void __fastcall TMainForm::btnCOMDownloadClick(int index)
{
	try
	{
		if(this->ActionPage->ActivePage==this->eFuse)
		{
			try
			{
		      CheckUIEFuseSetting();
			}
			catch(int e)
			{
				Application->MessageBox(MDT_ErrorStatusToString(e),"EFuse Write/Lock Setting Error",MB_ICONERROR);
				return;
			}
			catch(string e)
			{
				Application->MessageBox(e.c_str(),"EFuse Writer Error",MB_ICONERROR);
				return;
			}
			catch(...)
			{
				Application->MessageBox("EFuse Write/Lock Setting Error","Error",MB_ICONERROR);
				return;
			}

		}
		else
		{
		    if (!DownloadCommonFunction())
		    {
		        return;
		    }
		}
	    //  Get_Baudrate();

	    if( cbCOMArray[index]->Checked )
	    {
			if( miEnableFDLog->Checked )
			{
				// access
				TDateTime datetime;
				TDateTime date = datetime.CurrentDate();
				TDateTime time = datetime.CurrentTime();
				sTime     stime;
				time.DecodeTime( &stime.hour, &stime.min, &stime.sec, &stime.msec);
				MainForm->SetDnDate( index, date );
				MainForm->SetDnStartTime( index, time );
				MainForm->SetDnStartsTime( index, stime );
			}

			g_iStopFlag[index] = 0;
			Disable_UIComponent();
			Disable_SpecificMsUI(index);
			isStopTrigger[index] = false;
			DownloadStatus[index] = DOWNLOAD_STATUS_RUNNING;
			pbCOMArray[index]->Progress = 0;
			DownLoadTimeSec[index] = 0;

			//TimerCOMArray[index]->Enabled = true;
			UpdateDownloadProgress[index]=true;
			 m_stBkStatus[index]->Hint = "";


			/// 2
			int current_comport[MAX_SUPPORT_PORT_NUM];
			query_current_comport(m_sDnParam.i_FirstComNo,current_comport);
			record_current_comport(current_comport);
			///
			if(this->ActionPage->ActivePage==this->DownloadAction)
			{
				if(m_p_LinkMapFileManager==m_p_Config_Manager)
				{
					A_Thread[index] = new SV5_Thread(FALSE, hPostMsgDestHandle, m_sComPortSetting, m_sDnParam);
					A_Thread[index]->FreeOnTerminate = true;
				}
				else if(m_p_LinkMapFileManager==m_p_scatter_manager)
				{
					A_Thread[index] = new TBOOT1(FALSE, hPostMsgDestHandle, m_sComPortSetting, m_sDnParam);
					A_Thread[index]->FreeOnTerminate = true;
				}
				else
				{
					GC_TRACE("Download Action: m_p_LinkMapFileManager is Invalid");
					Application->MessageBox("m_p_LinkMapFileManager is Invalid","Error",MB_ICONERROR);
				}
			}
			else if(this->ActionPage->ActivePage==this->eFuse)
			{
				//EFuse Read parameter
				if( this->EFuseReadCheckBox->Checked == true)
				{
				  A_Thread[index] = new TEFuseReader(FALSE, hPostMsgDestHandle, m_sComPortSetting, m_sDnParam);
				  dynamic_cast<TEFuseReader*>(A_Thread[index])->setefusereadhandle(&m_efuse_read_handle_list);
				}
				else
				{
				  A_Thread[index] = new TEFuseWriter(FALSE, hPostMsgDestHandle, m_sComPortSetting, m_sDnParam);
				  dynamic_cast<TEFuseWriter*>(A_Thread[index])->SetEFuseWriteHandle(&efuse_writer_handle);

				  //Set Write
				  if(this->EFuseWriteCheckBox->Checked==true)
				  {
					dynamic_cast<TEFuseWriter*>(A_Thread[index])->SetEFuseWriteAction(true);
				  }
				  else
				  {
					dynamic_cast<TEFuseWriter*>(A_Thread[index])->SetEFuseWriteAction(false);
				  }

				  //Set Lock
				  if(this->EFuseLockCheckBox->Checked == true)
				  {
					dynamic_cast<TEFuseWriter*>(A_Thread[index])->SetEFuseLockAction(true);
				  }
				  else
				  {
					  dynamic_cast<TEFuseWriter*>(A_Thread[index])->SetEFuseLockAction(false);
				  }
				  A_Thread[index]->FreeOnTerminate = true;
				}
			}
			else
			{
				GC_TRACE("Invalid Operation");
				Application->MessageBox("m_p_LinkMapFileManager is Invalid","Error",MB_ICONERROR);
			}

	    }
	}
	catch(int excep)
	{
		Application->MessageBox(MDT_ErrorStatusToString(excep),"EFuse Write/Lock Setting Error",MB_ICONERROR);
		return;
	}
	catch(string e)
	{
		Application->MessageBox(e.c_str(),"EFuse Writer Error",MB_ICONERROR);
		return;
	}
	catch(...)
	{
		Application->MessageBox("EFuse Write/Lock Setting Error","Error",MB_ICONERROR);
		return;
	}

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::btnSeperateDownloadClick(TObject *Sender)
{
    TButton *bt = (TButton*)Sender;

    GC_TRACE("SeperateDownloadClick DL-ID:%d", bt->Tag);
    if(this->ActionPage->ActivePage!=this->eFuse)
	{
	    if(stScatterFile->Text.IsEmpty())
	    {
	        Application->MessageBox( "Please select scatter file!", "Fail", MB_OK );
	        return;
	    }
    }

    Set_DownloadParameter( bt->Tag );
    m_bStartMetaApp[bt->Tag] = false;

    //isFirstTwoStationUSBDownload[bt->Tag]=true;

    btnCOMDownloadClick( bt->Tag );
}

//==============================================================================
bool TMainForm::DownloadCommonFunction( void )
{
    int ret;

    // flag
    //   isShowNoFormatInfo = false;
    //    isShowFileNotLoaded = false;

    if(stScatterFile->Text.IsEmpty())
    {
        Application->MessageBox( "Please select scatter file!", "Fail", MB_OK );
        return false;
    }

    if(0 != UpdateDAInfo() )
    {
        stDAFileName->Text = "";
        return false;
    }

    // check multi load and ECO consistency
    int HandleNumber;
    if( 0 != DL_GetHandleNumber(g_DL_HANDLE_LIST, &HandleNumber) )
    {
        sbMPDT->Panels->Items[0]->Text = "  [DL_HANDLE] Get handle number failed";
        Application->MessageBox( "[DL_HANDLE] Get handle number failed", "Fail", MB_OK );
        return false;
    }

    if( (HandleNumber >= 2) && (! miCheckECOversion->Checked) )
    {
        sbMPDT->Panels->Items[0]->Text = "  Please enable BB chip version check for multiload download";
        Application->MessageBox( "Please enable BB chip version check for multiload download", "Fail", MB_OK );
        return false;
    }

    if(  Get_Function() == FLASHTOOL_ENABLE_BOOT_CERT )
    {
      if(NULL == m_boot_Cert.m_data ||
        0 == m_boot_Cert.m_len)
        {
          Application->MessageBox( "Please select Boot Cert File!", "Fail", MB_OK );
          return false;
        }
    }

    //if one station USB DL, or two station usb DL
    if(  Get_Function() == FLASHTOOL_DOWNLOAD
        && (m_rbUSB->Checked || m_rbUART_USB->Checked)
        )
    {
        //check whether at lease one rom is selected
        if(CheckRomNumber())
        {
            return false;
        }
    }


    return true;
}

//---------------------------------------------------------------------------
UART_BAUDRATE TMainForm::Get_Baudrate( AnsiString as_baudrate )
{
    UART_BAUDRATE baud_rate;

    if ( m_asBaudrate.AnsiCompareIC("115200") == 0 )
    {
        baud_rate =  UART_BAUD_115200;
    }
    else if ( m_asBaudrate.AnsiCompareIC("230400") == 0 )
    {
        baud_rate =  UART_BAUD_230400;
    }
    else if( m_asBaudrate.AnsiCompareIC("460800") == 0 )
    {
        baud_rate =  UART_BAUD_460800;
    }
    else if( m_asBaudrate.AnsiCompareIC("921600") == 0 )
    {
        baud_rate =  UART_BAUD_921600;
    }
    else // default set to 460800
    {
        Application->MessageBox( "Baud Rate setting is wrong. Set Default 460800", "Notice", MB_OK );
        baud_rate =  UART_BAUD_460800;
    }
    return baud_rate;
}

//----------------------------------------------------------------------------
UART_BAUDRATE TMainForm::Get_Baudrate(void)
{
    UART_BAUDRATE baud_rate;
    switch ((E_BAUD_RATE_INDEX_T) cbBaudrate->ItemIndex)
    {
    case BAUD_RATE_115200_INDEX:
        {
            baud_rate = UART_BAUD_115200;
        }
        break;

    case BAUD_RATE_230400_INDEX:
        {
            baud_rate = UART_BAUD_230400;
        }
        break;

    case BAUD_RATE_460800_INDEX:
        {
            baud_rate = UART_BAUD_460800;
        }
        break;

    case BAUD_RATE_921600_INDEX:
    default:
        {
            baud_rate =  UART_BAUD_921600;
        }
        break;
    }

    return baud_rate;

}

//============================================================================
void TMainForm::Disable_UIComponent( void )
{
    Disable_EngineerOption();
    Disable_FileMenu();
    Disable_FactoryDatabaseMenu();
    Disable_OptionMenu();
    Disable_DebugLoggingMenu();
    Disable_FormatFatRangeRadioButton();
    Disable_BaudrateComboBox();
    Disable_TypeComboBox();
    Disable_ComPortRadioButton();
    Disable_SetAndDelScatterFile();

	if(this->ActionPage->ActivePage==this->eFuse)
	{
		this->ActionPage->Enabled=false;
	}
}

//----------------------------------------------------------------------------
void TMainForm::Enable_UIComponent( void )
{
    Identify1->Enabled = true; 
    if(m_LoginIdentify == LOGIN_ENGINEER)
    {
       SetWindowText(this->Handle, "Multiple Download Tool - Engineer mode");
       Enable_EngineerOption();
       Enable_FileMenu();
       Enable_FactoryDatabaseMenu();
       Enable_OptionMenu();
       Enable_DebugLoggingMenu();
       Enable_FormatFatRangeRadioButton();
       Enable_BaudrateComboBox();
       Enable_TypeComboBox();
       Enable_ComPortRadioButton();
       Enable_SetAndDelScatterFile();

       if(true == m_rbUSB->Checked || true == m_rbUART_USB->Checked)
       {
           update_UI_components_for_USB_mode();
       }

	   if(this->ActionPage->ActivePage==this->eFuse)
	   {
		   this->ActionPage->Enabled=true;
	   }
    }
}

void TMainForm::Disable_SetAndDelScatterFile( void )
{
  ScatterFileButton1->Enabled = false;
  ScatterFileButton2->Enabled = false;
  ScatterFileButton3->Enabled = false;
  SctterFileButton4->Enabled = false;

  btnReloadScatterFile->Enabled = false;
  btDeleteScatterFile2->Enabled = false;
  btDeleteScatterFile3->Enabled = false;
  btDeleteScatterFile4->Enabled = false;
}


void TMainForm::Enable_SetAndDelScatterFile( void )
{
  ScatterFileButton1->Enabled = true;
  ScatterFileButton2->Enabled = true;
  ScatterFileButton3->Enabled = true;
  SctterFileButton4->Enabled = true;

  btnReloadScatterFile->Enabled = true;
  btDeleteScatterFile2->Enabled = true;
  btDeleteScatterFile3->Enabled = true;
  btDeleteScatterFile4->Enabled = true;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_FileMenu( void )
{
  miFile->Enabled = false;
  Help1->Enabled = false;
  this->EFuseReadCheckBox->Enabled = false;
  this->btnEFuseParameterView->Enabled = false;

#if 0
  this->EFuseWriteCheckBox->Enabled = false;
  if ( true == this->EFuseWriteCheckBox->Checked)
  {
  this->btnSelectEFuseSettingFile->Enabled = false;
  }
  this->EFuseLockCheckBox->Enabled = false;
  if ( true == this->EFuseLockCheckBox->Checked)
  {
  this->btnSelectEFuseLockFile->Enabled = false;
  }
#endif

}

void TMainForm::Disable_EngineerOption( void )
{
    if(m_LoginIdentify == LOGIN_ENGINEER)
	{
	   Engineer1->Enabled = true;
	   Engineer1->Checked = true;
	   Operator1->Enabled = false;
	   Operator1->Checked = false;
	}
	else if(m_LoginIdentify == LOGIN_OPERATOR)
	{
	   Engineer1->Enabled = false;
	   Engineer1->Checked = false;
	   Operator1->Enabled = true;
	   Operator1->Checked = true;
	}
}

void TMainForm::Enable_EngineerOption(void)
{
    if(m_LoginIdentify== LOGIN_ENGINEER)
	{
	   Engineer1->Enabled = true;
	   Engineer1->Checked = true;
	   Operator1->Enabled = false;
	   Operator1->Checked = false;
	}
}

//----------------------------------------------------------------------------
void TMainForm::Enable_FileMenu( void )
{
  miFile->Enabled = true;
  Help1->Enabled = true;

  this->EFuseReadCheckBox->Enabled = true;
  this->btnEFuseParameterView->Enabled = true;

#if 0
  this->EFuseWriteCheckBox->Enabled = true;
  if ( true == this->EFuseWriteCheckBox->Checked)
  {
    this->btnSelectEFuseSettingFile->Enabled = true;
  }
  this->EFuseLockCheckBox->Enabled = true;
  if ( true == this->EFuseLockCheckBox->Checked)
  {
    this->btnSelectEFuseLockFile->Enabled = true;
  }
#endif
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_FactoryDatabaseMenu( void )
{
    miFactoryDatabase->Enabled = false;
}

//----------------------------------------------------------------------------
void TMainForm::Enable_FactoryDatabaseMenu( void )
{
    miFactoryDatabase->Enabled = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_OptionMenu( void )
{
    miOption->Enabled = false;
}

//----------------------------------------------------------------------------
void TMainForm::Enable_OptionMenu( void )
{
    miOption->Enabled = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_DebugLoggingMenu( void )
{
    miDebuglog->Enabled = false;
}

//----------------------------------------------------------------------------
void TMainForm::Enable_DebugLoggingMenu( void )
{
    miDebuglog->Enabled = true;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_ComPortRadioButton(void)
{
    m_rbUART->Enabled = false;
    m_rbUSB->Enabled = false;
    m_rbUART_USB->Enabled = false;
}

//----------------------------------------------------------------------------
void TMainForm::Enable_ComPortRadioButton(void)
{
    if(mi_USBDownloadReadbackDualTalk->Checked == false)
    {
      m_rbUART->Enabled = true;
      m_rbUSB->Enabled = true;
      m_rbUART_USB->Enabled = true;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_FormatFatRangeRadioButton( void )
{
    rbAuto->Enabled = false;
    rbNOR->Enabled = false;
    rbNAND->Enabled = false;
    rbManual->Enabled = false;
    rbResetToFactory->Enabled = false;
}

//----------------------------------------------------------------------------
void TMainForm::Enable_FormatFatRangeRadioButton( void )
{
    rbAuto->Enabled = true;
    rbManual->Enabled = true;
    rbNOR->Enabled = true;
    rbNAND->Enabled = true;
    rbResetToFactory->Enabled = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_BaudrateComboBox( void )
{
    cbBaudrate->Enabled = false;
}

//----------------------------------------------------------------------------
void TMainForm::Enable_BaudrateComboBox( void )
{
    cbBaudrate->Enabled = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_TypeComboBox( void )
{
    cbType->Enabled = false;
}

//----------------------------------------------------------------------------
void TMainForm::Enable_TypeComboBox( void )
{
    cbType->Enabled = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_SeperateDownloadButton( void )
{
    for (int i=0; i<MAX_SUPPORT_PORT_NUM; i++)
    {
        btnCOMStartArray[i]->Enabled = false;
    }
}

//----------------------------------------------------------------------------
void TMainForm::Enable_SeperateDownloadButton( void )
{
    for (int i=0; i<MAX_SUPPORT_PORT_NUM; i++)
    {
        btnCOMStartArray[i]->Enabled = true;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_AllDownloadButton( void )
{
    Disable_SeperateDownloadButton();
}

//----------------------------------------------------------------------------
void TMainForm::Enable_AllDownloadButton( void )
{
    Enable_SeperateDownloadButton();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Disable_SpecificMsUI(int index)
{
    cbCOMArray[index]->Enabled = false;
    cbAutoPollingArray[index]->Enabled = false;
    btnCOMStartArray[index]->Enabled = false;
}

//----------------------------------------------------------------------------
void TMainForm::Enable_SpecificMsUI(int index)
{
    cbCOMArray[index]->Enabled = true;
    cbAutoPollingArray[index]->Enabled = true;
    btnCOMStartArray[index]->Enabled = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Start_Timer(int index)
{
//    TimerCOMArray[index]->Enabled = true;
	UpdateDownloadProgress[index]=false;
}

//----------------------------------------------------------------------------
void TMainForm::Stop_Timer(int index)
{
//    TimerCOMArray[index]->Enabled = false;
	UpdateDownloadProgress[index]=false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mOpenDAFileClick(TObject *Sender)
{
    FileOpenDownloadAgentExecute();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenDownloadAgentFile1Click(TObject *Sender)
{
    FileOpenDownloadAgentExecute();
}
//---------------------------------------------------------------------------
void TMainForm::Display_DAFile( void )
{
    m_asDAFileName =  INIFileH.read_DA_bin( "MultiPortFlashDownloadProject.ini", Application->ExeName );

    if(m_asDAFileName.IsEmpty())
    {
        int iLD = Application->ExeName.LastDelimiter("\\");
        if ( iLD > 0)
        {
            m_asDAFileName = Application->ExeName.SubString(1, iLD-1 );
            m_asDAFileName += "\\MTK_AllInOne_DA.bin";
        }
    }


    if( OpenReadDAFile(m_asDAFileName) )
    {
        int iLD = m_asDAFileName.LastDelimiter("\\:");
        if ( m_asDAFileName.LastDelimiter("\\:") > 0)
        {
            m_asDAPath = m_asDAFileName.SubString(1, iLD-1 );
        }
        stDAFileName->Text = m_asDAFileName;
    }
}

//----------------------------------------------------------------------------
void TMainForm::Save_DAFile( void )
{
    INIFileH.write_DA_bin( "MultiPortFlashDownloadProject.ini", Application->ExeName, m_asDAFileName);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Display_AuthFile( void )
{
    AnsiString as_auth_file;
    int ret;
    stAuthFile->Text = "";
    as_auth_file =  INIFileH.read_AuthFile( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_auth_file.AnsiCompareIC("") !=  0)
    {
        if( S_DONE != (ret=AUTH_Load(g_AUTH_HANDLE, as_auth_file.c_str())) )
        {
            g_AUTH_HANDLE_Loaded=false;//mingxue2012-12-12
            if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
                Application->MessageBox( "Program is busy! Can not update setting right now.", "Fail", MB_OK );
                return;
            }
            else
            {
                AnsiString as_msg = " Load authentication File \"" + stAuthFile->Text + "\" failed!";
                Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );
                return;
            }
        }
        stAuthFile->Text = as_auth_file;
        g_AUTH_HANDLE_Loaded=true;//mingxue 2012-12-12
        sbMPDT->Panels->Items[0]->Text = "  Load authentication file successfully";
    }
}
//-------------------------------------------------------------
void TMainForm::Save_AuthFile( void )
{
    INIFileH.write_AuthFile( "MultiPortFlashDownloadProject.ini", Application->ExeName, stAuthFile->Text);
}
//----------------------------------------------------------------------------
void TMainForm::Display_RootCertFile( void )
{
  AnsiString as_rootcert_file;
  int ret;
  as_rootcert_file = "";
  as_rootcert_file =  INIFileH.read_RootCertFile( "MultiPortFlashDownloadProject.ini", Application->ExeName );

  if( as_rootcert_file.AnsiCompareIC("") !=  0)
  {
    ret = ROOTCERT_Load(g_ROOTCERT_HANDLE, as_rootcert_file.c_str());

    if (ret != S_DONE)
    {
      g_is_Root_Cert_File_Loaded= false;
      as_rootcert_file = "";
    }
    else
    {
      g_is_Root_Cert_File_Loaded = true;
      //g_ROOTCERT_File = ed_ROOTCERT_File->Text;
    }
  }
    this->RootCert_File_DisplayEdit->Text = as_rootcert_file;
}
//-------------------------------------------------------------
void TMainForm::Save_RootCertFile( void )
{
    INIFileH.write_RootCertFile( "MultiPortFlashDownloadProject.ini",
                              Application->ExeName,
                              RootCert_File_DisplayEdit->Text);
}
//-------------------------------------------------------------
void TMainForm::Display_CertificateFile( void )
{
  AnsiString as_certificate_file;
  int ret;
  as_certificate_file = "";
  as_certificate_file =  INIFileH.read_CertificateFile( "MultiPortFlashDownloadProject.ini", Application->ExeName );

  if( as_certificate_file.AnsiCompareIC("") !=  0)
  {
    ret = SCERT_Load(g_SCERT_HANDLE, as_certificate_file.c_str());

    if (ret != S_DONE)
    {
        as_certificate_file = "";
        g_is_Certificate_File_Loaded = false;
    }
    else
    {
        g_is_Certificate_File_Loaded = true;
    }
  }
  this->Certificate_File_DisplayEdit->Text = as_certificate_file;
}
//-------------------------------------------------------------
void TMainForm::Save_CertificateFile( void )
{
    INIFileH.write_CertificateFile( "MultiPortFlashDownloadProject.ini",
                             Application->ExeName,
                             Certificate_File_DisplayEdit->Text);
}

//=============================================================================
void TMainForm::Display_Type(void)
{
    m_asType =  INIFileH.read_Type( "MultiPortFlashDownloadProject.ini", Application->ExeName );
#ifndef SERVICE_CENTER
    if (m_asType.AnsiCompareIC("Download ROM and FAT") == 0)
    {
        cbType->ItemIndex = DOWNLOAD_ROM_AND_FAT_INDEX;
    }
    else if (m_asType.AnsiCompareIC("Download ROM") == 0)
    {
        cbType->ItemIndex = DOWNLOAD_ROM_INDEX;
    }
    else if (m_asType.AnsiCompareIC("Download ROM and Format") == 0)
    {
        cbType->ItemIndex =  DOWNLOAD_ROM_AND_FORMAT_INDEX;
    }
    else if (m_asType.AnsiCompareIC("Enable Boot Cert") == 0)
    {
        cbType->ItemIndex = ENABLE_BOOT_CERT;
    }
    else
    {
        cbType->ItemIndex = FORMAT_INDEX;
    }
#else
    cbType->ItemIndex =  DOWNLOAD_ROM_INDEX;
#endif


}

//------------------------------------------------------------------------------
void TMainForm::Save_Type( void )
{
#ifndef SERVICE_CENTER
    switch ( cbType->ItemIndex )
    {
    case DOWNLOAD_ROM_AND_FAT_INDEX:
        INIFileH.write_Type( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "Download ROM and FAT");
        break;

    case DOWNLOAD_ROM_INDEX:
        INIFileH.write_Type( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "Download ROM");
        break;

    case DOWNLOAD_ROM_AND_FORMAT_INDEX:
        INIFileH.write_Type( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "Download ROM and Format");
        break;

    case FORMAT_INDEX:
        INIFileH.write_Type( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "Format");
        break;
    case ENABLE_BOOT_CERT:
        INIFileH.write_Type( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "Enable Boot Cert");
        break;
    default:  //Download ROM and FAT
        INIFileH.write_Type( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "Download ROM and FAT");
        break;
    }
#else
    INIFileH.write_Type( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "Download ROM");
#endif

}

//=============================================================================
E_FORMAT_OPTION TMainForm::Get_FormatOption( void )
{
    E_FORMAT_OPTION format_op;

#ifndef SERVICE_CENTER
    if( DOWNLOAD_ROM_AND_FAT_INDEX == cbType->ItemIndex )
    {
        format_op = DISABLE_FORMAT;
    }
    else if( (DOWNLOAD_ROM_AND_FORMAT_INDEX == cbType->ItemIndex) ||
        (FORMAT_INDEX                  == cbType->ItemIndex)
        )
    {
        if( rbAuto->Checked )
        {   format_op = AUTO_FORMAT;
        }
        else if( rbManual->Checked )
        {   format_op = MANUAL_FORMAT;
        }
        else // reset to factory default
        {   format_op = RESET_TO_FACTORY;
        }
    }
    else // DOWNLOAD_ROM_INDEX
#endif
    {
        format_op = DISABLE_FORMAT;
    }

    return format_op;
}


//----------------------------------------------------------------------------
void TMainForm::Display_FormatFatRangeVisible( void )
{
#ifndef SERVICE_CENTER
    if( DOWNLOAD_ROM_AND_FORMAT_INDEX == cbType->ItemIndex  )
    {
        gbFormatFATRange->Visible = true;
        rbAuto->Visible = true;
        rbManual->Visible = true;
        rbNOR->Visible = true;
        rbNAND->Visible = true;
        AnsiString as_RTFD_visible = INIFileH.read_Reset_to_factory_default_visible( "MultiPortFlashDownloadProject.ini", Application->ExeName );
        if( as_RTFD_visible.AnsiCompareIC("yes") == 0 )
        {
            rbResetToFactory->Visible = true;
            //lblResetToFactory->Visible = true;
        }
        else
        {   rbResetToFactory->Visible = false;
        //lblResetToFactory->Visible = false;
        }
    }
    else if( FORMAT_INDEX == cbType->ItemIndex  )
    {
        gbFormatFATRange->Visible = true;
        rbAuto->Visible = false;
        if( rbAuto->Checked )
        {
            rbManual->Checked = true;
        }
        rbManual->Visible = true;
        rbNOR->Visible = true;
        rbNAND->Visible = true;
        AnsiString as_RTFD_visible = INIFileH.read_Reset_to_factory_default_visible( "MultiPortFlashDownloadProject.ini", Application->ExeName );
        if( as_RTFD_visible.AnsiCompareIC("yes") == 0 )
        {
            rbResetToFactory->Visible = true;
            //lblResetToFactory->Visible = true;
        }
        else
        {
            rbResetToFactory->Visible = false;
            //lblResetToFactory->Visible = false;
        }
    }
    else if(ENABLE_BOOT_CERT == cbType->ItemIndex)
    {
      gbFormatFATRange->Visible = false;
      this->BootCertOptions->Visible = true;
      this->BootCert_File_OpenDialog->FileName = "";
    }
    else
#endif
    {
        gbFormatFATRange->Visible = false;
    }
}

//---------------------------------------------------------------------------
void TMainForm::Display_FormatFatRange( void )
{
    Display_FormatFatRangeVisible();
    AnsiString as_Format_FAT_range =  INIFileH.read_Format_FAT_range("MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_Format_FAT_range.AnsiCompareIC( "auto" ) == 0 )
    {
        rbAuto->Checked = true;
    }
    else if( as_Format_FAT_range.AnsiCompareIC( "manual" ) == 0 )
    {
        rbManual->Checked = true;
    }
    else
    {   rbResetToFactory->Checked = true;
    }
}

//------------------------------------------------------------------------------
void TMainForm::Save_FormatFatRange( void )
{
    if( rbAuto->Checked )
    {
        INIFileH.write_Format_FAT_range( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "auto");
    }
    else if( rbManual->Checked )
    {
        INIFileH.write_Format_FAT_range( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "manual");
    }
    else
    {   INIFileH.write_Format_FAT_range( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "reset factory default");
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Display_BackupAndRestoreOption(void)
{
#ifndef SERVICE_CENTER
    if (cbType->ItemIndex == FORMAT_INDEX)
    {
        m_miDnAndRsCalDataOnly->Enabled = false;
        m_miDnAndUlUserData->Enabled = false;
        m_miRsCalDataOnly->Enabled = false;
    }
#endif

}

//------------------------------------------------------------------------------
//void TMainForm::Save_BackupAndRestoreOption(void)
//{
//}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Read_EMI_Setting(void)
{
    AnsiString as;
    as = INIFileH.read_bank0_auto("MultiPortFlashDownloadProject.ini", Application->ExeName);
    if (as.AnsiCompareIC("no") == 0 )
    {
        m_sDnParam.s_emi_param.b_bank0_auto = false;
    }
    else
    {
        m_sDnParam.s_emi_param.b_bank0_auto = true;
    }

    as = INIFileH.read_bank0_cfg("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.s_emi_param.ui_bank0_cfg = as.ToInt();

    as = INIFileH.read_bank1_auto("MultiPortFlashDownloadProject.ini", Application->ExeName);
    if (as.AnsiCompareIC("no") == 0 )
    {
        m_sDnParam.s_emi_param.b_bank1_auto = false;
    }
    else
    {
        m_sDnParam.s_emi_param.b_bank1_auto = true;
    }

    as = INIFileH.read_bank1_cfg("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.s_emi_param.ui_bank1_cfg = as.ToInt();

    as = INIFileH.read_nand_acccon("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.sEMI_NFI_Setting.ui_nand_acccon = as.ToInt();

    as = INIFileH.read_emi_gen_a("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.sEMI_NFI_Setting.ui_emi_gen_a = as.ToInt();

    as = INIFileH.read_emi_gen_b("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.sEMI_NFI_Setting.ui_emi_gen_b = as.ToInt();

    as = INIFileH.read_emi_gen_c("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.sEMI_NFI_Setting.ui_emi_gen_c = as.ToInt();

    as = INIFileH.read_emi_dram_con_i_mode("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.sEMI_NFI_Setting.ui_emi_dram_con_i_mode = as.ToInt();

    as = INIFileH.read_emi_dram_con_i_ext_mode("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.sEMI_NFI_Setting.ui_emi_dram_con_i_ext_mode = as.ToInt();

    as = INIFileH.read_emi_dram_con_k("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.sEMI_NFI_Setting.ui_emi_dram_con_k = as.ToInt();

    as = INIFileH.read_emi_dram_con_l("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.sEMI_NFI_Setting.ui_emi_dram_con_l = as.ToInt();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Read_FormatFATBeginAddress( void )
{
    AnsiString as_addr = INIFileH.read_Format_FAT_Begin_Address( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    m_sDnParam.s_nor_param.ui_fat_begin_addr = as_addr.ToInt();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Read_FormatFATLength( void )
{
    AnsiString as_len = INIFileH.read_Format_FAT_length( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    m_sDnParam.s_nor_param.ui_fat_length = as_len.ToInt();
}

void TMainForm::Read_usb_device_id( void )
{
    AnsiString as_deviceid = INIFileH.read_device_id( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    m_usbdeviceid = as_deviceid;
	AnsiString as_preloaderid = INIFileH.read_preloader_id( "MultiPortFlashDownloadProject.ini", Application->ExeName );
	m_preloaderdeviceid = as_preloaderid;
}

void TMainForm::Save_usb_device_id( void )
{
   INIFileH.write_device_id("MultiPortFlashDownloadProject.ini", Application->ExeName, m_usbdeviceid);
   INIFileH.write_preloader_id("MultiPortFlashDownloadProject.ini", Application->ExeName, m_preloaderdeviceid);
}


void TMainForm::Read_SwitchToModem_DelayTime( void )
{
    m_iDelayTimeSec = INIFileH.read_SwitchToMode_DelayTime("MultiPortFlashDownloadProject.ini", Application->ExeName);
}

void TMainForm::Save_SwitchToModem_DelayTime(void)
{
    AnsiString str;
    str = str.sprintf("%d", m_iDelayTimeSec);
	INIFileH.write_SwitchToMode_DelayTime("MultiPortFlashDownloadProject.ini", Application->ExeName, str);
}

void TMainForm::Read_PasswordFilePath(void)
{
   AnsiString asSetupPath = "";
   if (getPathFromStr(Application->ExeName, asSetupPath) && withPath( asSetupPath))
   {
       m_asPasswdFilePath = asSetupPath+"\\"+"MDTDATA";
   }
}

void TMainForm::Get_LoginIdentify(void)
{
    BYTE key[10]="03055030";    
    BYTE password[LOGIN_PASSWORD_MAX];	
	
	if(ReadDataFromFile(password,LOGIN_PASSWORD_MAX, key, m_asPasswdFilePath.c_str()) == S_DES_SUCCESS)
    {
        if(password[0] == '0' && password[1] == '0')
        {
           m_LoginIdentify = LOGIN_OPERATOR;
        }
		else if(password[0] == '0' && password[1] == '1')
		{
		   m_LoginIdentify = LOGIN_ENGINEER;
		}
		else
		{
		   m_LoginIdentify = LOGIN_IDENTIFY_UNKNOWN;
		}		
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Read_NANDFormatFATBeginAddress( void )
{
    AnsiString as_NAND_Format_FAT_begin_address = INIFileH.read_NAND_Format_FAT_Begin_Address( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    m_sDnParam.s_nfb_param.ui_nand_fat_begin_addr = as_NAND_Format_FAT_begin_address.ToInt();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Read_NANDFormatFATLength( void )
{
    AnsiString as_NAND_Format_FAT_length = INIFileH.read_NAND_Format_FAT_length( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    m_sDnParam.s_nfb_param.ui_nand_fat_length = as_NAND_Format_FAT_length.ToInt();
}

void TMainForm::Read_Disconnect_Comport_option( void )
{
    bool flag = INIFileH.read_Disconnect_Comport_After_DL( "MultiPortFlashDownloadProject.ini", Application->ExeName );

    if(flag)
    {
       m_sDnParam.b_disconnect_comport_option=true;
    }
    else
    {
        m_sDnParam.b_disconnect_comport_option=false;
    }

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Read_EraseValidation( void )
{
    AnsiString as_EraseValidation = INIFileH.read_Erase_Validation( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_EraseValidation.AnsiCompareIC("yes") == 0 )
    {   m_sDnParam.s_nfb_param.b_validation = _TRUE;
    m_sDnParam.s_nor_param.b_validation = _TRUE;
    }
    else
    {   m_sDnParam.s_nfb_param.b_validation = _FALSE;
    m_sDnParam.s_nor_param.b_validation = _FALSE;
    }
}


//=============================================================================
void TMainForm::Display_ComEnabled( void )
{
    int i, j;

    AnsiString as_TheFirstComNo = INIFileH.read_TheFirstComPortNo( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    m_sDnParam.i_FirstComNo = as_TheFirstComNo.ToInt();
    AnsiString as_ComportChecked = INIFileH.read_ComEnabled( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    iCOMChecked = as_ComportChecked.ToInt();


    //if(  miComManual->Checked )
    {
        for (i=0; i<MAX_SUPPORT_PORT_NUM; i++)
        {
            cbCOMArray[i]->Caption = "COM" + IntToStr( m_sDnParam.i_FirstComNo + i);
        }

        for(i=0;i<MAX_SUPPORT_PORT_NUM;i++)
        {
            j= (iCOMChecked & (1<<i));
            if(j==0)
            {
                cbCOMArray[i]->Checked = false;
            }
            else
            {
                cbCOMArray[i]->Checked = true;
            }
        }
    }

}

void __fastcall  TMainForm::Update_ComPortNumber(void)
{
    int i=0;
	bool IsComportAutoPollingSelectAll=false;

    AnsiString as_TheFirstComNo = INIFileH.read_TheFirstComPortNo( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    int new_value = as_TheFirstComNo.ToInt();
    //AnsiString as_ComportChecked = INIFileH.read_ComEnabled( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    //iCOMChecked = as_ComportChecked.ToInt();

    if( m_sDnParam.i_FirstComNo == new_value)
    {
        return;
    }

    m_sDnParam.i_FirstComNo = new_value;
    for (i=0; i<MAX_SUPPORT_PORT_NUM; i++)
    {
        cbCOMArray[i]->Caption = "COM" + IntToStr( new_value + i);
        cbAutoPollingArray[i]->Caption = "Auto polling " + IntToStr( new_value + i);
    }

	#if 0
	for(i=0;i<MAX_SUPPORT_PORT_NUM;i++)
	{
        if( (true != cbAutoPollingArray[i]->Enabled)||(true != cbCOMArray[i]->Enabled))
        {
            break;
        }
		else
		{
			if( (true != cbAutoPollingArray[i]->Checked)||(true != cbCOMArray[i]->Checked))
	        {
	            break;
	        }
			else
			{
				continue;
			}
		}
    }
	if(MAX_SUPPORT_PORT_NUM==i)
	{
		IsComportAutoPollingSelectAll=true;
	}

	if(true==IsComportAutoPollingSelectAll)
	{
		for(i=0;i<MAX_SUPPORT_PORT_NUM;i++)
		{
			cbAutoPollingArray[i]->Checked=true;
			cbCOMArray[i]->Checked=true;
			iAutoPolling |= (1<<i);
			iCOMChecked |= (1<<i);
		}
		cbSelAllAutoPolling->Checked=true;
		cbSelAllCOM->Checked=true;
	}
	else
	{
		for(i=0;i<MAX_SUPPORT_PORT_NUM;i++)
		{
			iAutoPolling &= ~(1<<i);
			cbAutoPollingArray[i]->Checked=false;

			iCOMChecked &= ~(1<<i);
			cbCOMArray[i]->Checked=false;
		}
		cbSelAllAutoPolling->Checked=false;
		cbSelAllCOM->Checked=false;
	}

	#else
//Clear all selection~
	for(i=0;i<MAX_SUPPORT_PORT_NUM;i++)
	{
		iAutoPolling &= ~(1<<i);
		cbAutoPollingArray[i]->Checked=false;

		iCOMChecked &= ~(1<<i);
		cbCOMArray[i]->Checked=false;
	}
	cbSelAllAutoPolling->Checked=false;
	cbSelAllCOM->Checked=false;

	#endif

}

void __fastcall TMainForm::Read_CalibrationFolder_option(void)
{
    m_CalibrationFolderNamingRule = INIFileH.read_CalibrationFolderNamingRule("MultiPortFlashDownloadProject.ini", Application->ExeName);

    m_delete_CalibrationAfterRS = INIFileH.read_Delete_Calibration_After_RS( "MultiPortFlashDownloadProject.ini", Application->ExeName);
}

void __fastcall TMainForm::Update_FormatFatAddressLength(void)
{
    Read_FormatFATBeginAddress();
    Read_FormatFATLength();

    Read_NANDFormatFATBeginAddress();
    Read_NANDFormatFATLength();

}

//----------------------------------------------------------------------------
void TMainForm::Save_ComEnabled( void )
{
    INIFileH.write_ComEnabled( "MultiPortFlashDownloadProject.ini", Application->ExeName, "0x"+IntToHex(iCOMChecked,2));
}

//============================================================================
void TMainForm::Get_BBChipOption(S_BBCHIP_OPTION_T& bbchip_op)
{
    //bbchip_op.b_check_eco_ver  = miCheckECOversion->Checked;
    bbchip_op.b_enable_nfi_cs1 = miEnableNFICS1->Checked;
    bbchip_op.b_check_bbchip_version = miBBChipVersionCheck->Checked;
}

//----------------------------------------------------------------------------
BBCHIP_TYPE TMainForm::Get_BBChipType(AnsiString as_BBChip)
{
    if (as_BBChip.AnsiCompareIC("auto detect") == 0)
    {
        return AUTO_DETECT_BBCHIP;
    }
    else if (as_BBChip.AnsiCompareIC("6205") == 0)
    {
        return MT6205;
    }
    else if (as_BBChip.AnsiCompareIC("6205B") == 0)
    {
        return MT6205B;
    }
    else if (as_BBChip.AnsiCompareIC("6217") == 0)
    {
        return MT6217;
    }
    else if (as_BBChip.AnsiCompareIC("6218") == 0)
    {
        return MT6218;
    }
    else if (as_BBChip.AnsiCompareIC("6218B") == 0)
    {
        return MT6218B;
    }
    else if (as_BBChip.AnsiCompareIC("6219") == 0)
    {
        return MT6219;
    }
    else if (as_BBChip.AnsiCompareIC("6223") == 0)
    {
        return MT6223;
    }
    else if (as_BBChip.AnsiCompareIC("6223P") == 0)
    {
        return MT6223P;
    }
    else if (as_BBChip.AnsiCompareIC("6225") == 0)
    {
        return MT6225;
    }
    else if (as_BBChip.AnsiCompareIC("6226") == 0)
    {
        return MT6226;
    }
    else if (as_BBChip.AnsiCompareIC("6226D") == 0)
    {
        return MT6226D;
    }
    else if (as_BBChip.AnsiCompareIC("6226M") == 0)
    {
        return MT6226M;
    }
    else if (as_BBChip.AnsiCompareIC("6227") == 0)
    {
        return MT6227;
    }
    else if (as_BBChip.AnsiCompareIC("6228") == 0)
    {
        return MT6228;
    }
    else if (as_BBChip.AnsiCompareIC("6229") == 0)
    {
        return MT6229;
    }
    else return UNKNOWN_BBCHIP_TYPE;
}

//---------------------------------------------------------------------------
BBCHIP_TYPE TMainForm::Get_BBChipType(void)
{
    return AUTO_DETECT_BBCHIP;
}

//---------------------------------------------------------------------------
EXT_CLOCK TMainForm::Get_ExternalClockType( AnsiString as_ExtClock )
{
    if( as_ExtClock.AnsiCompareIC("auto detect") == 0 )  return AUTO_DETECT_EXT_CLOCK;
    else if( as_ExtClock.AnsiCompareIC("13MHz") == 0 )   return EXT_13M;
    else if( as_ExtClock.AnsiCompareIC("39MHz") == 0 )   return EXT_39M;
    else if( as_ExtClock.AnsiCompareIC("52MHz") == 0 )   return EXT_52M;
    else if( as_ExtClock.AnsiCompareIC("26MHz") == 0 )   return EXT_26M;
    else return EXT_26M;
}

//---------------------------------------------------------------------------
EXT_CLOCK TMainForm::Get_ExternalClockType( void )
{
    EXT_CLOCK ext_clock;

    if( miAutodetectExtClock->Checked ) ext_clock = AUTO_DETECT_EXT_CLOCK;
    else if( mi13MHz->Checked )         ext_clock = EXT_13M;
    else if( mi26MHz->Checked )         ext_clock = EXT_26M;
    else if( mi39MHz->Checked )         ext_clock = EXT_39M;
    else if( mi52MHz->Checked )         ext_clock = EXT_52M;

    return ext_clock;
}



//----------------------------------------------------------------------------
void TMainForm::Display_Operation(void)
{

}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void TMainForm::Display_Cable(void)
{
    AnsiString as_Operation = INIFileH.read_download_cable("MultiPortFlashDownloadProject.ini", Application->ExeName);

    if(as_Operation == "USB")
    {
        m_rbUSB->Checked = true;
        m_rbUART->Checked = false;
        m_rbUART_USB->Checked = false;
    }
    else if(as_Operation == "UART")
    {
        m_rbUSB->Checked =  false;
        m_rbUART->Checked = true;
        m_rbUART_USB->Checked = false;
    }
    else // usb + uart
    {
        m_rbUSB->Checked = false;
        m_rbUART->Checked = false;
        m_rbUART_USB->Checked = true;
    }
}

void TMainForm::Save_Cable(void)
{
    if (m_rbUSB->Checked)
    {
        INIFileH.write_download_cable("MultiPortFlashDownloadProject.ini", Application->ExeName, "USB");
    }
    else if(m_rbUART->Checked )
    {
        INIFileH.write_download_cable("MultiPortFlashDownloadProject.ini", Application->ExeName, "UART");
    }
    else
    {
        INIFileH.write_download_cable("MultiPortFlashDownloadProject.ini", Application->ExeName, "UART+USB");
    }

}


//------------------------------------------------------------------------------
void TMainForm::Save_BkAndRsOptional(void)
{
    // backup and restore calibration data
    int optional;

    if (m_miDnWithoutBkAndRsCalData->Checked)
    {
        optional = DN_WITHOUT_BK_AND_RS_CAL_DATA;
    }
    else if (m_miDnWithBkAndRsCalData->Checked)
    {
        optional = DN_WITH_BK_AND_RS_CAL_DATA;
    }
    else if (m_miDnAndRsCalDataOnly->Checked)
    {
        optional = DN_WITH_RS_CAL_DATA;
    }
    else if (m_miDnAndUlUserData->Checked)
    {
        optional = DN_WITH_UL_USER_DATA;
    }
    else if(m_miRsCalDataOnly->Checked)
    {
        optional = RS_CAL_DATA_ONLY;
    }
    else if(m_miUploadUserDataOnly->Checked)
    {
        optional = UPLOAD_USER_DATA_ONLY;
    }
    else if(m_miCheckSDS->Checked)
    {
        optional = CHECK_SDS_ONLY;
    }
    else
    {
        GC_TRACE_EX("Error Backup Restore Option");
        return;
    }

    //don't save checkSDS
    if(optional==CHECK_SDS_ONLY)
    	{
    	  	INIFileH.write_bk_and_rs_cfg("MultiPortFlashDownloadProject.ini", Application->ExeName, 0);
    	}
	else
		{
    		INIFileH.write_bk_and_rs_cfg("MultiPortFlashDownloadProject.ini", Application->ExeName, optional);
		}

}

//=============================================================================
void TMainForm::Display_BkAndRsOptional( void )
{
    int optional =  INIFileH.read_bk_and_rs_cfg( "MultiPortFlashDownloadProject.ini", Application->ExeName );

    switch(optional)
    {
    case DN_WITHOUT_BK_AND_RS_CAL_DATA:
        m_miDnWithoutBkAndRsCalData->Checked = true;
        break;
    case DN_WITH_BK_AND_RS_CAL_DATA:
        m_miDnWithBkAndRsCalData->Checked = true;
        break;
    case DN_WITH_RS_CAL_DATA:
        m_miDnAndRsCalDataOnly->Checked = true;
        break;
    case DN_WITH_UL_USER_DATA:
        m_miDnAndUlUserData->Checked = true;
        break;
    case RS_CAL_DATA_ONLY:
        m_miRsCalDataOnly->Checked = true;
        break;
    case UPLOAD_USER_DATA_ONLY:
        m_miUploadUserDataOnly->Checked = true;
        break;
	case CHECK_SDS_ONLY:
		m_miCheckSDS->Checked = true;
		break;
    default:
        m_miDnWithoutBkAndRsCalData->Checked = true;
        break;
    }
}

//------------------------------------------------------------------------------
void TMainForm::Save_Operation(void)
{
}

//=============================================================================
void TMainForm::Display_BasebandChip( void )
{
    m_asBBChip = "auto detect";
}


//------------------------------------------------------------------------------
void TMainForm::Save_BasebandChip( void )
{
    INIFileH.write_Baseband_chip( "MultiPortFlashDownloadProject.ini", Application->ExeName, m_asBBChip);

}

//=============================================================================
void TMainForm::Display_ExternalClock( void )
{

    m_asExtClock =  INIFileH.read_External_clock( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    m_sDnParam.e_ext_clock = Get_ExternalClockType(m_asExtClock);
    switch( m_sDnParam.e_ext_clock )
    {
    case AUTO_DETECT_EXT_CLOCK:
        {
            miAutodetectExtClock->Checked = true;
            mi13MHz->Checked = false;
            mi26MHz->Checked = false;
            mi39MHz->Checked = false;
            mi52MHz->Checked = false;
        }
        break;


    case EXT_13M:
        {
            miAutodetectExtClock->Checked = false;
            mi13MHz->Checked = true;
            mi26MHz->Checked = false;
            mi39MHz->Checked = false;
            mi52MHz->Checked = false;
        }
        break;

    case EXT_39M:
        {
            miAutodetectExtClock->Checked = false;
            mi39MHz->Checked = true;
            mi13MHz->Checked = false;
            mi26MHz->Checked = false;
            mi52MHz->Checked = false;
        }
        break;

    case EXT_52M:
        {
            miAutodetectExtClock->Checked = false;
            mi52MHz->Checked = true;
            mi13MHz->Checked = false;
            mi26MHz->Checked = false;
            mi39MHz->Checked = false;
        }
        break;

    case EXT_26M:
    default:
        {
            // set to 26mhz
            miAutodetectExtClock->Checked = false;
            mi26MHz->Checked = true;
            mi13MHz->Checked = false;
            mi39MHz->Checked = false;
            mi52MHz->Checked = false;
            m_asExtClock = (AnsiString) "26mhz";
        }
        break;
    }
}

//------------------------------------------------------------------------------
void TMainForm::Save_ExternalClock( void )
{
    INIFileH.write_External_clock( "MultiPortFlashDownloadProject.ini", Application->ExeName, m_asExtClock);
}
/*
//=============================================================================
void TMainForm::Display_CheckECOVersion( void )
{
    AnsiString as_Operation = INIFileH.read_CheckECOVersion("MultiPortFlashDownloadProject.ini", Application->ExeName);

    if(0 == strcmp(as_Operation.c_str(), "yes"))
    {
        miCheckECOversion->Checked = true;
        m_sDnParam.s_bbchip_op.b_check_eco_ver = true;
    }
    else
    {
        miCheckECOversion->Checked = false;
        m_sDnParam.s_bbchip_op.b_check_eco_ver = false;
    }
}

//-----------------------------------------------------------------------------
void TMainForm::Save_CheckECOVersion( void )
{
    if(true == miCheckECOversion->Checked)
    {
        INIFileH.write_CheckECOVersion("MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_CheckECOVersion("MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}
*/
//=============================================================================
void TMainForm::Display_CheckEnableNFI( void )
{
    AnsiString as_Operation = INIFileH.read_CheckEnableNFI("MultiPortFlashDownloadProject.ini", Application->ExeName);

    if(0 == strcmp(as_Operation.c_str(), "yes"))
    {
        miEnableNFICS1->Checked = true;
    }
    else
    {
        miEnableNFICS1->Checked = false;
    }
}

//-----------------------------------------------------------------------------
void TMainForm::Save_CheckEnableNFI( void )
{
    if(true == miEnableNFICS1->Checked)
    {
        INIFileH.write_CheckEnableNFI("MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_CheckEnableNFI("MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}

//=============================================================================
S_MULTIBIN_OPTION TMainForm::Get_MultiBinOption( void )
{
    S_MULTIBIN_OPTION multibin_op;

    multibin_op.b_check_target_resource_layout    = _TRUE;
    multibin_op.b_auto_load_resource_file_by_scat = _TRUE;
    multibin_op.b_compare_resource_project_id     = _TRUE;

    return multibin_op;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Display_BROMDllLog( void )
{
    AnsiString as_BROMDllLog =  INIFileH.read_BROMDllLog( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_BROMDllLog.AnsiCompareIC("no") == 0 )
    {
        miBromDllLog->Checked = false;
    }
    else
    {
        miBromDllLog->Checked = true;
        Brom_DebugOn();
		SP_Brom_DebugOn();
    }

}

//----------------------------------------------------------------------------
void TMainForm::Save_BROMDllLog( void )
{
    if( miBromDllLog->Checked )
    {
        INIFileH.write_BROMDllLog( "MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_BROMDllLog( "MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Display_METADllLog( void )
{
    AnsiString as_METADllLog =  INIFileH.read_BROMDllLog( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_METADllLog.AnsiCompareIC("no") == 0 )
    {
        miMETADllLog->Checked = false;
    }
    else
    {
        miMETADllLog->Checked = true;
        META_DebugOn();
    }

}

//----------------------------------------------------------------------------
void TMainForm::Save_METADllLog( void )
{
    if( miMETADllLog->Checked )
    {
        INIFileH.write_METADllLog( "MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_METADllLog( "MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}

//=============================================================================
void TMainForm::Display_Baudrate( void )
{
    m_asBaudrate = INIFileH.read_Baudrate("MultiPortFlashDownloadProject.ini", Application->ExeName);
    m_sDnParam.e_baud_rate = Get_Baudrate(m_asBaudrate);

    switch (m_sDnParam.e_baud_rate)
    {
    case UART_BAUD_115200:
        {
            cbBaudrate->ItemIndex = BAUD_RATE_115200_INDEX;
        }
        break;

    case UART_BAUD_230400:
        {
            cbBaudrate->ItemIndex = BAUD_RATE_230400_INDEX;
        }
        break;

    case UART_BAUD_460800:
        {
            cbBaudrate->ItemIndex = BAUD_RATE_460800_INDEX;
        }
        break;

    case UART_BAUD_921600:
        {
            cbBaudrate->ItemIndex = BAUD_RATE_921600_INDEX;
        }
        break;

    default: // default set to 460800
        {
            m_sDnParam.e_baud_rate = UART_BAUD_460800;
            cbBaudrate->ItemIndex =  BAUD_RATE_460800_INDEX;
            m_asBaudrate = (AnsiString) "460800";
        }
        break;
    }
}

//------------------------------------------------------------------------------
void TMainForm::Save_Baudrate(void)
{
    switch ( cbBaudrate->ItemIndex )
    {
    case BAUD_RATE_115200_INDEX:
        INIFileH.write_Baudrate( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "115200");
        break;

    case BAUD_RATE_230400_INDEX:
        INIFileH.write_Baudrate( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "230400");
        break;

    case BAUD_RATE_460800_INDEX:
        INIFileH.write_Baudrate( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "460800");
        break;

    case BAUD_RATE_921600_INDEX:
        INIFileH.write_Baudrate( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "921600");
        break;

    default:  // default set to 460800
        INIFileH.write_Baudrate( "MultiPortFlashDownloadProject.ini", Application->ExeName, (AnsiString) "460800");
        break;
    }
}

//=============================================================================
void TMainForm::Display_AutoPollingEnabled( void )
{
    int i, j;
    m_asAutoPollEn = INIFileH.read_AutoPollingEnabled( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    iAutoPolling = m_asAutoPollEn.ToInt();

    for (i=0; i<MAX_SUPPORT_PORT_NUM; i++)
    {
        cbAutoPollingArray[i]->Caption = "Auto polling " + IntToStr( m_sDnParam.i_FirstComNo + i);
    }

    for(i=0; i<MAX_SUPPORT_PORT_NUM; i++)
    {
        j= (iAutoPolling & (1<<i));
        if(j==0)
        {
            cbAutoPollingArray[i]->Checked = false;
        }
        else
        {
            cbAutoPollingArray[i]->Checked = true;
        }
    }
}

//----------------------------------------------------------------------------
void  TMainForm::Save_AutoPollingEnabled( void )
{
    INIFileH.write_AutoPollingEnabled( "MultiPortFlashDownloadProject.ini", Application->ExeName, "0x"+IntToHex(iAutoPolling,2));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Display_EnableUSB_2_0( void )
{
    AnsiString as_EnableUSB_2_0 =  INIFileH.read_EnableUSB_2_0( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_EnableUSB_2_0.AnsiCompareIC("no") == 0 )
    {
        EnableUSB11to20->Checked = false;
		    m_bEnableUSB1_1To2_0=false;
    }
    else
    {
        EnableUSB11to20->Checked = true;
        m_bEnableUSB1_1To2_0=true;
    }
}

//----------------------------------------------------------------------------
void TMainForm::Save_EnableUSB_2_0( void )
{
    if( EnableUSB11to20->Checked )
    {
        INIFileH.write_EnableUSB_2_0( "MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_EnableUSB_2_0( "MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
Function: get "backup nvram partition" from ini,then init the "backup nvram partition" in the UI Form
History:
  1. 2012/12/03: added by wuxiong
*/
void TMainForm::Display_EnableBackupNvramPartion( void )
{
    AnsiString as_Enable_BackupNvramPartion =  INIFileH.read_Enable_BackupNvramPartion( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_Enable_BackupNvramPartion.AnsiCompareIC("no") == 0 )
    {
        EnableBackupNvramPartion->Checked = false;
		    //m_bEnableBackupNvramPartition=false;
		    m_bEnableBackupNvramPartition = LNP_NONE;//0;mingxue
    }
    else
    {
        EnableBackupNvramPartion->Checked = true;
       // m_bEnableBackupNvramPartition=true;
       m_bEnableBackupNvramPartition=LNP_BACKUP_RESTORE; //1;mingxue
    }
}

/*
Function: Save "backup nvram partition" from UI options to ini
History:
  1. 2012/12/03: added by wuxiong
*/
void TMainForm::Save_EnableBackupNvramPartion( void )
{
    if( EnableUSB11to20->Checked )
    {
        INIFileH.write_Enable_BackupNvramPartion( "MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_Enable_BackupNvramPartion( "MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}


//==============================================================================
/*
void  TMainForm::get_PullDownGPIO17( void )
{
m_asPullDownGPIO17 =  INIFileH.read_Pull_down_GPIO17( "MultiPortFlashDownloadProject.ini", Application->ExeName );
if( m_asPullDownGPIO17.AnsiCompareIC( "yes" ) == 0 )
{
m_sDnParam.b_PullDownGPIO17 = true;
}
else
{
m_sDnParam.b_PullDownGPIO17 = false;
}
}*/

//------------------------------------------------------------------------------
void __fastcall TMainForm::btnStartAllClick(TObject *Sender)
{
    int m_DownLoadStatusResult;
    try
    {
        GC_TRACE("StartAllClick");
        if(this->ActionPage->ActivePage == this->eFuse)
        {
            CheckUIEFuseSetting();
        }
        else
        {
            if (!DownloadCommonFunction())
            {
                return;
            }
        }

        Identify1->Enabled = false; 
        Disable_UIComponent();
    /// 2
        /*
           if(mi_USBDownloadReadbackDualTalk->Checked == true)
           {
              //  if(MainForm->dtProcessInfo.hProcess==NULL)
             if(MainForm->dtProcessInfo.hProcess != NULL)
             {
                if(TerminateProcess(MainForm->dtProcessInfo.hProcess, 0)!=0)
                {
                    MainForm->sbMPDT->Panels->Items[0]->Text = "TerminateProcess OK!";
                    CloseHandle(MainForm->dtProcessInfo.hThread);
                    CloseHandle(MainForm->dtProcessInfo.hProcess);
                }
            }

            {
                if (false == ::CreateProcess("DualTalkSwitchTool.exe",
                       "",
                       0,
                       0,
                       false,
                       CREATE_NO_WINDOW, //CREATE_DEFAULT_ERROR_MODE CREATE_NO_WINDOW
                       0,
                       0,
                       &MainForm->dtStartupInfo,
                       &MainForm->dtProcessInfo))
                {
                    ShowMessage("Cannot create DualTalkSwitchTool process to switch com port!!");
                }
             }
          }
        */

        int current_comport[MAX_SUPPORT_PORT_NUM];
        query_current_comport(m_sDnParam.i_FirstComNo,current_comport);
        record_current_comport(current_comport);
        ///

    for (int i=0;i<MAX_SUPPORT_PORT_NUM;i++)
    {
        if (   cbCOMArray[i]->Checked
            && DownloadStatus[i] == DOWNLOAD_STATUS_NOTRUNNING)
        {
            Set_DownloadParameter(i);

            if( miEnableFDLog->Checked )
            {
                // access
                TDateTime datetime;
                TDateTime date = datetime.CurrentDate();
                TDateTime time = datetime.CurrentTime();
                sTime     stime;
                time.DecodeTime( &stime.hour, &stime.min, &stime.sec, &stime.msec);
                MainForm->SetDnDate( i, date );
                MainForm->SetDnStartTime( i, time );
                MainForm->SetDnStartsTime( i, stime );
            }

            m_bStartMetaApp[i] = false;
            g_iStopFlag[i] = 0;
            DownLoadTimeSec[i] = 0;
            COMPercentageArray[i]->Caption = "";
    //            TimerCOMArray[i]->Enabled = true;
    	    	UpdateDownloadProgress[i]=true;

            DownloadStatus[i] = DOWNLOAD_STATUS_RUNNING;
            btnCOMStartArray[i]->Enabled = false;
            cbCOMArray[i]->Enabled = false;
            cbAutoPollingArray[i]->Enabled = false;
            isStopTrigger[i] = false;
           
    		if(this->ActionPage->ActivePage==this->DownloadAction)
    		{
    			if(m_p_LinkMapFileManager==m_p_Config_Manager)
                {
    				A_Thread[i] = new SV5_Thread(FALSE, hPostMsgDestHandle, m_sComPortSetting, m_sDnParam);
    				A_Thread[i]->FreeOnTerminate = true;
                }
    			else if(m_p_LinkMapFileManager==m_p_scatter_manager)
    			{
    				A_Thread[i] = new TBOOT1(FALSE, hPostMsgDestHandle, m_sComPortSetting, m_sDnParam);
    				A_Thread[i]->FreeOnTerminate = true;
    			}
    			else
    			{
    				GC_TRACE("Download Action: m_p_LinkMapFileManager is Invalid");
    				Application->MessageBox("m_p_LinkMapFileManager is Invalid","Error",MB_ICONERROR);
    			}
    		}
    		else if(this->ActionPage->ActivePage == this->eFuse)
    		{
    		  //EFuse Read parameter
    		  if( this->EFuseReadCheckBox->Checked == true)
    		  {
                A_Thread[i] = new TEFuseReader(FALSE, hPostMsgDestHandle, m_sComPortSetting, m_sDnParam);
                dynamic_cast<TEFuseReader*>(A_Thread[i])->setefusereadhandle(&m_efuse_read_handle_list);
    	      }
        	  else
        	  {
                A_Thread[i] = new TEFuseWriter(FALSE, hPostMsgDestHandle, m_sComPortSetting, m_sDnParam);
        		dynamic_cast<TEFuseWriter*>(A_Thread[i])->SetEFuseWriteHandle(&efuse_writer_handle);

                //Set Write
                if(this->EFuseWriteCheckBox->Checked==true)
                {
                  dynamic_cast<TEFuseWriter*>(A_Thread[i])->SetEFuseWriteAction(true);
                }
                else
                {
                  dynamic_cast<TEFuseWriter*>(A_Thread[i])->SetEFuseWriteAction(false);
                }

                //Set Lock
                if(this->EFuseLockCheckBox->Checked == true)
                {
                  dynamic_cast<TEFuseWriter*>(A_Thread[i])->SetEFuseLockAction(true);
                }
                else
                {
                	dynamic_cast<TEFuseWriter*>(A_Thread[i])->SetEFuseLockAction(false);
                }
                A_Thread[i]->FreeOnTerminate = true;
        	  }
    	}
		else
		{
			GC_TRACE("Invalid Operation");
			Application->MessageBox("m_p_LinkMapFileManager is Invalid","Error",MB_ICONERROR);
		}
        }
    }//for

  }
  catch(int e)
  {
  	Application->MessageBox(MDT_ErrorStatusToString(e),"EFuse Write/Lock Setting Error",MB_ICONERROR);
  	return;
  }
  catch(string e)
  {
  	Application->MessageBox(e.c_str(),"EFuse Writer Error",MB_ICONERROR);
  	return;
  }
  catch(...)
  {
  	Application->MessageBox("EFuse Write/Lock Setting Error","Error",MB_ICONERROR);
  	return;
  }
}





//==============================================================================
/////////////////////////////    Timer     /////////////////////////////////////
//==============================================================================
void __fastcall TMainForm::TimerCOMTimer(TObject *Sender)
{
	/*
    TTimer * timer = (TTimer *)Sender;

    int tag = timer->Tag;

    if (m_bStartMetaApp[tag])
    {
        if (pbCOMArray[tag]->Progress < 100)
        {
            pbCOMArray[tag]->Progress++;
        }
    }
    */
	for(int index=0;index<MAX_SUPPORT_PORT_NUM;index++)
	{
		if(UpdateDownloadProgress[index]==true)
		{
			DownLoadTimeSec[index]++;
			lblTimeArray[index]-> Caption = (AnsiString) DownLoadTimeSec[index] + " sec";
		}
	}
}


//--------------------------------------------------------------------------
void __fastcall TMainForm::miAutodetectBBClick(TObject *Sender)
{
    m_asBBChip = (AnsiString) "auto detect";
    m_sDnParam.e_bbchip_type = Get_BBChipType( m_asBBChip );
}

//---------------------------------------------------------------------------
bool TMainForm::Set_COMPercentageCaption( int index, AnsiString as_str )
{
    COMPercentageArray[index]->Caption = as_str;
    return true;
}

//---------------------------------------------------------------------------
bool TMainForm::Set_shpCOMColor(int index, TColor color)
{
    shpCOMArray[index]->Brush->Color = color;
    return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::SetPbComProgress( int index, unsigned char progress_percentage )
{   pbCOMArray[index]->Progress = progress_percentage;
}

//----------------------------------------------------------------------------
void TMainForm::SetPbComForeColor(int index, TColor color)
{   pbCOMArray[index]->ForeColor = color;
}

//----------------------------------------------------------------------------
void TMainForm::SetPbComBackColor(int index, TColor color)
{   pbCOMArray[index]->BackColor = color;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Set_StartMetaAppFlag(unsigned char index, bool flag)
{
    m_bStartMetaApp[index] = flag;
}

//==============================================================================

void __fastcall TMainForm::miAutodetectExtClockClick(TObject *Sender)
{
    miAutodetectExtClock->Checked = true;
    mi13MHz->Checked = false;
    mi26MHz->Checked = false;
    mi39MHz->Checked = false;
    mi52MHz->Checked = false;
    m_asExtClock = (AnsiString) "auto detect";
    m_sDnParam.e_ext_clock = Get_ExternalClockType( m_asExtClock );
}

void __fastcall TMainForm::mi13MHzClick(TObject *Sender)
{
    miAutodetectExtClock->Checked = false;
    mi13MHz->Checked = true;
    mi26MHz->Checked = false;
    mi39MHz->Checked = false;
    mi52MHz->Checked = false;
    m_asExtClock = (AnsiString) "13mhz";
    m_sDnParam.e_ext_clock = Get_ExternalClockType( m_asExtClock );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mi26MHzClick(TObject *Sender)
{
    miAutodetectExtClock->Checked = false;
    mi26MHz->Checked = true;
    mi13MHz->Checked = false;
    mi39MHz->Checked = false;
    mi52MHz->Checked = false;
    m_asExtClock = (AnsiString) "26mhz";
    m_sDnParam.e_ext_clock = Get_ExternalClockType( m_asExtClock );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mi39MHzClick(TObject *Sender)
{
    miAutodetectExtClock->Checked = false;
    mi39MHz->Checked = true;
    mi26MHz->Checked = false;
    mi13MHz->Checked = false;
    mi52MHz->Checked = false;
    m_asExtClock = (AnsiString) "39mhz";
    m_sDnParam.e_ext_clock = Get_ExternalClockType( m_asExtClock );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mi52MHzClick(TObject *Sender)
{
    miAutodetectExtClock->Checked = false;
    mi52MHz->Checked = true;
    mi13MHz->Checked = false;
    mi26MHz->Checked = false;
    mi39MHz->Checked = false;
    m_asExtClock = (AnsiString) "52mhz";
    m_sDnParam.e_ext_clock = Get_ExternalClockType( m_asExtClock );

}

void __fastcall TMainForm::cbSelAllAutoPollingClick(TObject *Sender)
{
    TCheckBox *cb = (TCheckBox*)Sender;

    for(int i=0; i<MAX_SUPPORT_PORT_NUM; i++)
    {

        if(true == cbAutoPollingArray[i]->Enabled)
        {
            if (cb->Checked)
            {
                iAutoPolling |= (1<<i);
                cbAutoPollingArray[i]->Checked = 1;
            }
            else
            {
                iAutoPolling &= ~(1<<i);
                cbAutoPollingArray[i]->Checked = 0;
            }
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::cbAutoPollingClick(TObject *Sender)
{
    TCheckBox *cb = (TCheckBox*)Sender;

    GC_TRACE("AutoPollingClick DL-ID%d", cb->Tag);

    if (cb->Checked)
    {
        iAutoPolling |= (1<<cb->Tag);
    }
    else
    {
        iAutoPolling &= ~(1<<cb->Tag);
    }
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::miCheckECOversionClick(TObject *Sender)
{/*
    //this member function is no use now. because this is duplicated with BBChip Check

    if(miCheckECOversion->Checked)
    {
        miCheckECOversion->Checked = false;
        m_sDnParam.s_bbchip_op.b_check_eco_ver = false;
        m_asCheckECOVer = "no";
    }
    else
    {
        miCheckECOversion->Checked = true;
        m_sDnParam.s_bbchip_op.b_check_eco_ver = true;
        m_asCheckECOVer = "yes";
    }*/
}

void __fastcall TMainForm::cbSelAllCOMClick(TObject *Sender)
{
    TCheckBox *cb = (TCheckBox*)Sender;

    for(int i=0; i<MAX_SUPPORT_PORT_NUM; i++)
    {
        if(true == cbCOMArray[i]->Enabled)
        {
            if (cb->Checked)
            {
                iCOMChecked |= (1<<i);
                cbCOMArray[i]->Checked = 1;
            }
            else
            {
                iCOMChecked &= ~(1<<i);
                cbCOMArray[i]->Checked = 0;
            }
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::cbCOMClick(TObject *Sender)
{
    TCheckBox *cb = (TCheckBox*)Sender;

    GC_TRACE("COMClick DL-ID%d", cb->Tag);

    if (cbCOMArray[cb->Tag]->Checked)
    {
        iCOMChecked |= (1<<cb->Tag);
    }
    else
    {
        iCOMChecked &= ~(1<<cb->Tag);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::miAboutClick(TObject *Sender)
{
	AnsiString as;
	DA_INFO da_info;
	unsigned int ret;
	if(NULL==Form_AboutMD)
	{
		Form_AboutMD=new TForm_AboutMD(MainForm);
	}
	// retrieval the DA information
	if( !DA_GetInfo( g_DA_HANDLE, &da_info) )
	{
	 if( strlen(da_info.version) != 0 )
	 {
		 as.printf("DA_v%s",da_info.version);
		 Form_AboutMD->da_version->Caption = as;

		 if( strlen( da_info.last_modified_date ) != 0 )
		 {
			 as.printf( "(Build-Date: %s)", da_info.last_modified_date );
			 Form_AboutMD->da_build_date->Caption = as;
		 }
		 else{
			 Form_AboutMD->da_build_date->Caption = "";
		 }
	 }
	 else{
		 Form_AboutMD->da_version->Caption	= "";
		 Form_AboutMD->da_build_date->Caption = "";
	 }
	}
	else{
	 Form_AboutMD->da_version->Caption	= "";
	 Form_AboutMD->da_build_date->Caption = "";
	}

	Form_AboutMD->Left = MainForm->Left+100;
	Form_AboutMD->Top	= MainForm->Top+60;

	 // show FlashTool about Form
	 Form_AboutMD->ShowModal();

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::cbTypeChange(TObject *Sender)
{
    m_miDnWithoutBkAndRsCalData->Enabled = true;
    m_miDnWithBkAndRsCalData->Enabled = true;
    m_miDnAndRsCalDataOnly->Enabled = true;
    m_miDnAndUlUserData->Enabled = true;
    m_miRsCalDataOnly->Enabled = true;
	m_miCheckSDS->Enabled = true;

    this->BootCertOptions->Visible = false;


#ifndef SERVICE_CENTER
    switch (cbType->ItemIndex)
    {
    case DOWNLOAD_ROM_AND_FAT_INDEX:
        m_asType ="Download ROM and FAT";
        break;

    case DOWNLOAD_ROM_INDEX:
        m_asType = "Download ROM";
        break;

    case DOWNLOAD_ROM_AND_FORMAT_INDEX:
        m_asType = "Download ROM and Format";
        break;

    case FORMAT_INDEX:
        m_asType = "Format";

        m_miDnAndRsCalDataOnly->Enabled = false;
        m_miDnAndUlUserData->Enabled = false;
        m_miRsCalDataOnly->Enabled = false;

        if (m_miDnAndRsCalDataOnly->Checked ||
            m_miDnAndUlUserData->Checked ||
            m_miRsCalDataOnly->Checked)
        {
            m_miDnWithoutBkAndRsCalData->Checked = true;
            m_miDnAndRsCalDataOnly->Checked = false;
            m_miDnAndUlUserData->Checked = false;
            m_miRsCalDataOnly->Checked = false;
			m_miCheckSDS->Checked = false;
        }

        break;
     case ENABLE_BOOT_CERT:
        m_asType = "Enable Boot Cert";
        break;
    }

    Display_FormatFatRangeVisible();
#else
    m_asType = "Download ROM";
#endif

    GC_TRACE("TypeChange To %s", m_asType);
}

//---------------------------------------------------------------------------
void TMainForm::btnCOMStopClick(int i)
{

	bool IsAllStop=false;;
	if (DownloadStatus[i] == DOWNLOAD_STATUS_RUNNING)
	{
	    g_iStopFlag[i] = BOOT_STOP;
	    isStopTrigger[i] = true;

	    SetEvent(User_Stop_Event[i]);

	    if (A_Thread[i] != NULL)
	    {
	        A_Thread[i]->Terminate();
	        A_Thread[i] = NULL;
	    }
	}
	DownLoadTimeSec[i]=0;

	//   TimerCOMArray[i]->Enabled = false;
	UpdateDownloadProgress[i]=false;


	for(int j=0; j<MAX_SUPPORT_PORT_NUM; j++)
	{
	    if( DownloadStatus[j] == DOWNLOAD_STATUS_RUNNING ) return;
	}
	Enable_UIComponent();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::btnStopAllClick(TObject *Sender)
{
    GC_TRACE("StopAllClick");

    for(int i=0; i<MAX_SUPPORT_PORT_NUM; i++)
    {
		g_iStopFlag[i] = BOOT_STOP;
        if( DownloadStatus[i] == DOWNLOAD_STATUS_RUNNING )
        {
            SetEvent(User_Stop_Event[i]);
            DownLoadTimeSec[i]=0;

            isStopTrigger[i] = true;
            if (A_Thread[i] != NULL)
            {
                A_Thread[i]->Terminate();
                A_Thread[i] = NULL;
            }
        }
    }

    // stop all timer
     
    Enable_UIComponent();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::btnSeperateStopClick(TObject *Sender)
{
    TButton *bt = (TButton*)Sender;

    GC_TRACE("SeperateStopClick DL-ID:%d", bt->Tag);

    btnCOMStopClick( bt->Tag );
}

//---------------------------------------------------------------------------
//void TMainForm::UpdateMenuItem( void )
//{
//}

//---------------------------------------------------------------------------
//==============================================================================
////////////////////////////    Global information    //////////////////////////
//==============================================================================
bool TMainForm::Get_CheckTgtResLayout( void )
{
    return m_sDnParam.s_multibin_op.b_check_target_resource_layout;
}

//-----------------------------------------------------------------------------
bool TMainForm::Get_AutoLoadResByScat( void )
{
    return m_sDnParam.s_multibin_op.b_auto_load_resource_file_by_scat;
}

//-----------------------------------------------------------------------------
bool TMainForm::Get_CompareResProjectId( void )
{
    return m_sDnParam.s_multibin_op.b_compare_resource_project_id;
}


//==============================================================================
void __fastcall TMainForm::cbBaudrateChange(TObject *Sender)
{
    switch (cbBaudrate->ItemIndex)
    {
    case BAUD_RATE_115200_INDEX:
        {
            m_sDnParam.e_baud_rate = UART_BAUD_115200;
        }
        break;

    case BAUD_RATE_230400_INDEX:
        {
            m_sDnParam.e_baud_rate = UART_BAUD_230400;
        }
        break;

    case BAUD_RATE_460800_INDEX:
        {
            m_sDnParam.e_baud_rate = UART_BAUD_460800;
        }
        break;

    case BAUD_RATE_921600_INDEX:
        {
            m_sDnParam.e_baud_rate = UART_BAUD_921600;
        }
        break;
    }
}

//==============================================================================
//----------------         Access related function       -----------------------
//==============================================================================
//==============================================================================
///////////////////////////    ADO connection    ///////////////////////////////
//==============================================================================
void TMainForm::Set_ADOConnLoginPromptOff(void)
{
    ADOConn->LoginPrompt = false;
}

//------------------------------------------------------------------------------
bool TMainForm::Set_ADOConnString( AnsiString as_Data_Src )
{
    ADOConn->Close();
    AnsiString as_Provider = "Provider=Microsoft.Jet.OLEDB.4.0";
    AnsiString as_Security = "Persist Security Info=False";
    AnsiString as_DataSrc_str = "Data Source="+as_Data_Src;
    AnsiString as_ConnStr = as_Provider + ";" + as_DataSrc_str + ";" + as_Security;
    ADOConn->ConnectionString = as_ConnStr;
    ADOConn->Open();

    return  ADOConn->LoginPrompt;
}

//------------------------------------------------------------------------------
bool TMainForm::Check_ADOConnConnected( void )
{
    if( ADOConn->Connected )
    {
        return true;
    }
    return false;

}

//------------------------------------------------------------------------------
void TMainForm::InsertNewRecordToAccess( void )
{
    ADOTab->Insert();
}

//------------------------------------------------------------------------------
void TMainForm::ActivateADOTab( void )
{
    ADOTab->Active = true;
}

//------------------------------------------------------------------------------
void TMainForm::DeActivateADOTab( void )
{
    ADOTab->Active = false;
}

//------------------------------------------------------------------------------
void TMainForm::PostRecordToAccess( void )
{
    ADOTab->Post();
}


//------------------------------------------------------------------------------
void TMainForm::SetTabNameToMultiport_download( void )
{
    ADOTab->Active = false;
    ADOTab->TableName = "Multiport_download";
    ADOTab->Active = true;
}

//------------------------------------------------------------------------------
void TMainForm::AddStationToAccess( void )
{
    ADOTab->FieldByName("STATION")->AsString = "Multiport download";

}

//------------------------------------------------------------------------------
void TMainForm::AddPcToAccess( void )
{
    char hostname[256];
    unsigned long len=256;
    GetComputerName( hostname, &len );
    ADOTab->FieldByName("PC")->AsString = hostname;

}
//------------------------------------------------------------------------------
void TMainForm::AddToolTypeToAccess( void )
{
    ADOTab->FieldByName("TOOL_TYPE")->AsInteger = TOOL_TYPE_MULTIPORT_DN;
}

//------------------------------------------------------------------------------
void TMainForm::AddDateToAccess( int index )
{
    ADOTab->FieldByName("DATE")->AsString = DateToStr(dn_time[index].dn_date);
}

//------------------------------------------------------------------------------
void TMainForm::AddTimeToAccess( int index )
{
    ADOTab->FieldByName("TIME")->AsString = TimeToStr(dn_time[index].dn_start_time);

}

//------------------------------------------------------------------------------
void TMainForm::AddPassFailToAccess( int index )
{
    ADOTab->FieldByName("PASS_FAIL")->AsString = IntToStr(PassFail[index]);
}

//------------------------------------------------------------------------------
void TMainForm::AddFileSizeToAccess( void )
{
    ADOTab->FieldByName("FILE_SIZE")->AsString = IntToStr(m_uiTotalFileSize);
}

//------------------------------------------------------------------------------
void TMainForm::AddDownloadTimeToAccess( int index )
{
    float f_dn_time = dn_time[index].dn_time_ms / 1000.0;
    ADOTab->FieldByName("DOWNLOAD_TIME")->AsString = FloatToStr(f_dn_time);

}

//------------------------------------------------------------------------------
void TMainForm::AddThrougphputToAccess( int index )
{
    ADOTab->FieldByName("THROGHPUT")->AsString = FloatToStr(throughput[index]);
}


//------------------------------------------------------------------------------
void TMainForm::AddFailStepToAccess( int fail_step )
{
    ADOTab->FieldByName("FAIL_STEP")->AsString = IntToStr(fail_step);
}

//------------------------------------------------------------------------------
void TMainForm::AddFailReasonToAccess( int index )
{
    ADOTab->FieldByName("FAIL_REASON")->AsString = FailReason[index];
}

//------------------------------------------------------------------------------
bool TMainForm::AddDnResultToAccess( int index )
{
    hSemaphore = CreateSemaphore( NULL, 1, 1, NULL);

    if( ! Check_ADOConnConnected() )
    {
        Application->MessageBox( "Execution Failure : Connect to data source failed!", "FAILURE", MB_OK );
        return false;
    }

    SetTabNameToMultiport_download();
    InsertNewRecordToAccess();

    AddStationToAccess();
    AddPcToAccess();
    AddDateToAccess(index);
    AddTimeToAccess(index);
    AddPassFailToAccess(index);
    AddFailReasonToAccess(index);
    if(  TEST_RESULT_PASS == PassFail[index] )
    {
        AddFileSizeToAccess();
        AddDownloadTimeToAccess(index);
        AddThrougphputToAccess(index);
    }

    PostRecordToAccess();

    ReleaseSemaphore( hSemaphore,  1, NULL );

    return true;
}

//==============================================================================
/////////////////////       test result         ////////////////////////////////
//==============================================================================
bool TMainForm::SetPassFail( int index, int pass_fail)
{
    PassFail[index] = pass_fail;
    return true;
}

//------------------------------------------------------------------------------
int TMainForm::GetPassFail( int index )
{
    return PassFail[index];
}

//------------------------------------------------------------------------------
bool TMainForm::SetFailReason( int index, int fail_reason)
{
    AnsiString asFlrs;


	#if 0
    asFlrs = Get_FlrsString(fail_reason);
	#endif

	FailReason[index] = asFlrs;

    return true;
}

//------------------------------------------------------------------------------
AnsiString  TMainForm::GetFailReason( int index )
{
    return FailReason[index];
}

//------------------------------------------------------------------------------
#if 0
AnsiString  TMainForm::Get_FlrsString( int fail_reason )
{
    int i;
    int ret;
    sDnFlrs  fr;
    AnsiString asFlrs = "NONE";
    vector<sDnFlrs>:: iterator iter;

    // if( ret = BROM_RET(fail_reason) )
    if( (fail_reason >= S_BROM_ERROR_BEGIN) && (fail_reason <= S_BROM_ERROR_END) )
    {
        for( iter =  DnFlrs_Obj.vBromFlrs.begin();  iter != DnFlrs_Obj.vBromFlrs.end(); iter++)
        {
            fr.FlrsCode = iter->FlrsCode;
            if( fail_reason == fr.FlrsCode )
            {
                asFlrs = iter->asFlrs;
                return asFlrs;
            }
        }
    }

    // if( ret = FTHND_RET(fail_reason) )
    if( (fail_reason >= S_FTHND_ERROR_BEGIN) && (fail_reason <= S_FTHND_ERROR_END) )
    {
        for( iter =  DnFlrs_Obj.vFthndFlrs.begin();  iter != DnFlrs_Obj.vFthndFlrs.end(); iter++)
        {
            fr.FlrsCode = iter->FlrsCode;
            if( fail_reason == fr.FlrsCode )
            {
                asFlrs = iter->asFlrs;
                return asFlrs;
            }
        }
    }

    // if( ret = FT_RET(fail_reason) )
    if( (fail_reason >= S_FT_ERROR_BEGIN) && (fail_reason <=S_FT_ERROR_END) )
    {
        for( iter =  DnFlrs_Obj.vFtFlrs.begin();  iter != DnFlrs_Obj.vFtFlrs.end(); iter++)
        {
            fr.FlrsCode = iter->FlrsCode;
            if( fail_reason == fr.FlrsCode )
            {
                asFlrs = iter->asFlrs;
                return asFlrs;
            }
        }
    }

    return asFlrs;
}
#endif
//==============================================================================
/////////////////////       time handling       ////////////////////////////////
//==============================================================================
bool TMainForm::SetDnDate( int index, TDateTime date )
{
    dn_time[index].dn_date = date;
    return true;
}

//------------------------------------------------------------------------------
TDateTime TMainForm::GetDnDate( int index )
{
    return dn_time[index].dn_date;
}
//------------------------------------------------------------------------------
bool TMainForm::SetDnStartTime( int index, TDateTime time )
{
    dn_time[index].dn_start_time = time;
    return true;
}

//------------------------------------------------------------------------------
TDateTime TMainForm::GetDnStartTime( int index )
{
    return  dn_time[index].dn_start_time;
}

//------------------------------------------------------------------------------
bool TMainForm::SetDnStartsTime( int index, sTime time )
{
    dn_time[index].dn_start_stime = time;
    return true;
}

//------------------------------------------------------------------------------
sTime TMainForm::GetDnStartsTime( int index )
{
    return  dn_time[index].dn_start_stime;
}

//------------------------------------------------------------------------------
bool TMainForm::SetDnEndTime( int index, TDateTime time )
{
    dn_time[index].dn_end_time = time;
    return true;
}

//------------------------------------------------------------------------------
TDateTime TMainForm::GetDnEndTime( int index )
{
    return dn_time[index].dn_end_time;
}

//------------------------------------------------------------------------------
bool TMainForm::SetDnEndsTime( int index, sTime time )
{
    dn_time[index].dn_end_stime = time;
    return true;
}

//------------------------------------------------------------------------------
sTime TMainForm::GetDnEndsTime( int index )
{
    return dn_time[index].dn_end_stime;
}

//------------------------------------------------------------------------------
bool TMainForm::SetDnTime( int index )
{
    dn_time[index].dn_time_ms = DifferenceMiniSec( &dn_time[index].dn_start_stime, &dn_time[index].dn_end_stime );
    return true;
}

//------------------------------------------------------------------------------
unsigned TMainForm::GetDnTime( int index )
{
    return dn_time[index].dn_time_ms;
}

//------------------------------------------------------------------------------
bool TMainForm::SetThroughput( int index )
{
    if( m_uiTotalFileSize <= 0 )
    {
        return false;
    }
    throughput[index] = 1.0 * m_uiTotalFileSize / (dn_time[index].dn_time_ms / 1000.0);
    return true;
}

//------------------------------------------------------------------------------
float TMainForm::GetThroughput( int index )
{
    return  throughput[index];
}



//===========================================================================
void TMainForm::Display_DataSource( void )
{
    // set ADO connection
    as_DataSource = INIFileH.read_DataSource("MultiPortFlashDownloadProject.ini", Application->ExeName);
    if( Check_FileExist( as_DataSource ) )
    {
        Set_ADOConnString( as_DataSource );
        as_DataSource = as_DataSource;
    }
}

//---------------------------------------------------------------------------
void TMainForm::Save_DataSource( void )
{
    INIFileH.write_DataSource("MultiPortFlashDownloadProject.ini", Application->ExeName, as_DataSource);
}

//==============================================================================
void TMainForm::Display_DBLogOption( void )
{
    AnsiString DbLogEnable = INIFileH.read_DbLogEnable("MultiPortFlashDownloadProject.ini", Application->ExeName);
    if( DbLogEnable.AnsiCompareIC("yes") == 0 )
    {
        miEnableFDLog->Checked = true;
    }
    else
    {
        miEnableFDLog->Checked = false;
    }

}

//---------------------------------------------------------------------------
void TMainForm::Save_DBLogOption( void )
{
    if( miEnableFDLog->Checked )
    {
        INIFileH.write_DbLogEnable("MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_DbLogEnable("MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}

//---------------------------------------------------------------------------
bool TMainForm::Get_EnableFactoryDatabaseLog( void )
{
    if( ! miEnableFDLog->Checked )
    {
        return false;
    }
    return true;
}

//===========================================================================

void __fastcall TMainForm::miSetupDataSrcClick(TObject *Sender)
{
    bool ok = dlgOpenDataSrc->Execute();
    if( !ok )
    {
        return;
    }
    if( ! Check_FileExist( dlgOpenDataSrc->FileName ) )
    {
        AnsiString error_str = "Can not find file \'" + dlgOpenDataSrc->FileName + "' ";
        Application->MessageBox( error_str.c_str(), "Fail", MB_OK );
        return;
    }

    if(Set_ADOConnString( dlgOpenDataSrc->FileName ))
    {
        as_DataSource =dlgOpenDataSrc->FileName;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miEnableFDLogClick(TObject *Sender)
{
    if(  miEnableFDLog->Checked )
    {
        miEnableFDLog->Checked = false;
    }
    else
    {
        miEnableFDLog->Checked = true;
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::miBromDllLogClick(TObject *Sender)
{
    if( miBromDllLog->Checked )
    {
        miBromDllLog->Checked = false;
        Brom_DebugOff();
		SP_Brom_DebugOff();
    }
    else
    {
        miBromDllLog->Checked = true;
        Brom_DebugOn();
		SP_Brom_DebugOn();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miMETADllLogClick(TObject *Sender)
{
    if( miMETADllLog->Checked )
    {
        miMETADllLog->Checked = false;
        META_DebugOff();
    }
    else
    {
        miMETADllLog->Checked = true;
        META_DebugOn();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::miClearBromDllLogClick(TObject *Sender)
{
    Brom_DebugClear();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::miClearMETADllLogClick(TObject *Sender)
{
    META_DebugClear();
}


//============================================================================
void __fastcall TMainForm::rbNFBClick(TObject *Sender)
{
    GC_TRACE("NFBClick");
    m_sDnParam.e_Operation = OPERATION_NFB;
    //RedrawLVList();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
//===========================================================================
/////////////////////////// Export information  /////////////////////////////
//===========================================================================
S_DN_PARAM_T* TMainForm::Get_DNParameter(void)
{
    return &m_sDnParam;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned int TMainForm::Get_TotalFileSize(void)
{
    return m_uiTotalFileSize;
}

//---------------------------------------------------------------------------
void TMainForm::Set_TotalFileSize(unsigned int total_file_size)
{
    m_uiTotalFileSize = total_file_size;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DL_HANDLE_T* TMainForm::Get_DlHandle( int idx )
{
	return g_pDL_HANDLE[idx];
}

//---------------------------------------------------------------------------
void TMainForm::Set_DlHandle(int idx, DL_HANDLE_T* p_dl_handle)
{   g_pDL_HANDLE[idx] = p_dl_handle;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DL_HANDLE_LIST_T* TMainForm::Get_DlHandleList(void)
{   return &g_DL_HANDLE_LIST;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//BL_HANDLE_T* TMainForm::Get_BlHandle( void )
//{   return &m_sDnParam.bl_handle;
//}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//bool TMainForm::Get_CheckTgtResLayoutFlag( void )
//{   return m_sDnParam.s_multibin_op.b_check_target_resource_layout;
//}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//bool TMainForm::Get_AutoLoadResByScatFlag( void )
//{   return m_sDnParam.s_multibin_op.b_auto_load_resource_file_by_scat;
//}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//bool TMainForm::Get_CompareResProjectIdFlag( void )
//{   return m_sDnParam.s_multibin_op.b_compare_resource_project_id;
//}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int TMainForm::Get_Type( void )
{   return cbType->ItemIndex;
}

void __fastcall TMainForm::miOpenAuthFileClick(TObject *Sender)
{
    static AnsiString asAUTH_Path;
    int ret;

    if( stAuthFile->Text.AnsiCompareIC("") != 0 )
    {
        int iLD = stAuthFile->Text.LastDelimiter("\\:");
        if( 0 < iLD )
        {
            dlgOpenAuthFile->InitialDir = stAuthFile->Text.SubString(1, iLD-1 );
        }
    }

    if( dlgOpenAuthFile->Execute() )
    {
        if( S_DONE != (ret=AUTH_Load(g_AUTH_HANDLE, dlgOpenAuthFile->FileName.c_str())) )
        {
            g_AUTH_HANDLE_Loaded=false;//mingxue2012-12-12
            if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
                Application->MessageBox( "Program is busy! Can not load Authentication file now.", "Fail", MB_OK );
            }
            else
            {
                AnsiString as_msg = " Load authentication file \"" + dlgOpenAuthFile->FileName + "\" failed!";
                Application->MessageBox( as_msg.c_str(), "Fail", MB_OK );

            }
            return;
        }

        stAuthFile->Text = dlgOpenAuthFile->FileName;
        g_AUTH_HANDLE_Loaded = true;  //mingxue2012-12-12
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::miEnableNFICS1Click(TObject *Sender)
{
    miEnableNFICS1->Checked = !miEnableNFICS1->Checked;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_rbUARTClick(TObject *Sender)
{

    GC_TRACE("UARTClick");


    m_lblBaudRate->Visible = true;
    cbBaudrate->Visible = true;
       /*
    m_miDnWithoutBkAndRsCalData->Enabled = true;
    m_miDnWithBkAndRsCalData->Enabled = true;
    m_miDnAndRsCalDataOnly->Enabled = true;
    m_miDnAndUlUserData->Enabled = true;
    m_miRsCalDataOnly->Enabled = true;
    cbType->Enabled = true;
    */
}

void __fastcall TMainForm::update_UI_components_for_USB_mode()
{
/*   m_lblBaudRate->Visible = false;
cbBaudrate->Visible = false;

  //Check DL Without BK And RS Cal Data
  m_miDnWithoutBkAndRsCalData->Checked = true;
  m_miDnWithBkAndRsCalData->Checked = false;
  m_miDnAndRsCalDataOnly->Checked = false;
  m_miDnAndUlUserData->Checked = false;
  m_miRsCalDataOnly->Checked = false;

    m_miDnWithoutBkAndRsCalData->Enabled = false;
    m_miDnWithBkAndRsCalData->Enabled = false;
    m_miDnAndRsCalDataOnly->Enabled = false;
    m_miDnAndUlUserData->Enabled = false;
    m_miRsCalDataOnly->Enabled = false;

      //Forbiden Other Operation Type
      cbType->ItemIndex = DOWNLOAD_ROM_AND_FAT_INDEX;
      cbType->Enabled = false;

    Display_FormatFatRangeVisible();    */
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_rbUSBClick(TObject *Sender)
{
    GC_TRACE("USBClick");
    update_UI_components_for_USB_mode();
}

void __fastcall TMainForm::m_rbUART_USB_Click(TObject *Sender)
{
    GC_TRACE("UART+USB Click");
    //update_UI_components_for_USB_mode();
}



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenMemoryVerificationListFile1Click(
                                                                TObject *Sender)
{
    AnsiString asPath;
    AnsiString as_par;
    getPathFromStr(Application->ExeName, asPath);
    as_par = "\"" + asPath + "Memory_Validation_List_External.xlsx\"";
    HINSTANCE hinstance = ShellExecute(this->Handle, NULL, "excel.exe", as_par.c_str(), NULL, SW_SHOWNORMAL);
    if (ERROR_FILE_NOT_FOUND == (int)hinstance)
    {
        Application->MessageBox("If you want to open Memory_Validation_List_External.xlsx, please install Microsoft EXCEL.", "Fail", MB_OK);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::UnCheckBackupAndRestoreMenuItem(void)
{
    m_miDnWithoutBkAndRsCalData->Checked = false;
    m_miDnWithBkAndRsCalData->Checked = false;
    m_miDnAndRsCalDataOnly->Checked = false;
    m_miDnAndUlUserData->Checked = false;
    m_miRsCalDataOnly->Checked = false;
    m_miUploadUserDataOnly->Checked = false;
	m_miCheckSDS->Checked = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_miDnWithoutBkAndRsCalDataClick(TObject *Sender)
{
    UnCheckBackupAndRestoreMenuItem();
    m_miDnWithoutBkAndRsCalData->Checked = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_miDnWithBkAndRsCalDataClick(
                                                         TObject *Sender)
{
    UnCheckBackupAndRestoreMenuItem();
    m_miDnWithBkAndRsCalData->Checked = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_miDnAndRsCalDataOnlyClick(TObject *Sender)
{
    UnCheckBackupAndRestoreMenuItem();
    m_miDnAndRsCalDataOnly->Checked = true;
}

void __fastcall TMainForm::m_miDnAndUlUserDataClick(TObject *Sender)
{
    UnCheckBackupAndRestoreMenuItem();
    m_miDnAndUlUserData->Checked = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_miRsCalDataOnlyClick(TObject *Sender)
{
    UnCheckBackupAndRestoreMenuItem();
    m_miRsCalDataOnly->Checked = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Clear_BackupRestoreStatus(unsigned char idx)
{
    m_stBkStatus[idx]->Caption = "";
}

//---------------------------------------------------------------------------
void TMainForm::Display_BackupRestoreStatus(unsigned char idx, unsigned char total_num, unsigned char current_num)
{
    AnsiString as = IntToStr(current_num) + "/" + IntToStr(total_num);
    m_stBkStatus[idx]->Caption = as;
}

void __fastcall TMainForm::ScatterFileButtonClick(TObject *Sender)
{
    TCHAR bug_Msg[256];
    string folder_path;
    vector<string> scatter_files;
    int index = 1;
    string load_msg;
  try
  {
    //Frist:  display select folder
    if(!user_select_image_folder(folder_path))
	{
        return;
    }
    //Second : clear all download handle;
    m_p_Config_Manager->clear();
    m_p_scatter_manager->clear();

    //Search and Load
    SearchAllLinkMapFile(folder_path);
    LoadAllLinkMapFile(folder_path);

    //Display Load Result;
    vector<string>::iterator it_file;

    string StringFolderPath=folder_path;
    m_p_LinkMapFileManager->SetRootFolderPath(StringFolderPath);

    m_p_LinkMapFileManager->getLoadedTargetFilePath(scatter_files);

    for(it_file = scatter_files.begin();it_file != scatter_files.end(); it_file++)
    {
        load_msg+=*it_file;
        load_msg+='\n';
    }

    if(m_p_LinkMapFileManager->IsWithSecureRO() && miEnableMMAA1->Checked)
    {
        load_msg+="Notice: Two loads share a SecureRO!";
        load_msg+='\n';
    }
    Application->MessageBox(load_msg.c_str(), "Load Files Success", MB_OK );
    stScatterFile->Text = folder_path.c_str();
  }
  catch(string e)
  {
    Application->MessageBox(e.c_str(),"Exception",MB_ICONWARNING);
  }
  catch(int e)
  {
    const char* Return_Message = StatusToString(e);
    Application->MessageBox(Return_Message,"Exception",MB_ICONWARNING);
  }
  catch(...)
  {
    Application->MessageBox("MDT Unknown Error","Exception",MB_ICONWARNING);
  }//end of try

}


void TMainForm::LoadAllLinkMapFile(string& folder_path)
{
	vector<string> scatter_files;
	int index = 1;

	try
	{
		if((m_p_Config_Manager->getTargetFileNumber())>0)
		{
			m_p_LinkMapFileManager=m_p_Config_Manager;
		}
		else if((m_p_scatter_manager->getTargetFileNumber())>0)
		{
			m_p_LinkMapFileManager=m_p_scatter_manager;
		}
		else
		{
			throw string("Can not file any config/scatter files!");
		}

		if(!m_p_LinkMapFileManager->loadAllTargetFiles())
		{
			throw string("Load Target Files Error");
		}
	}
	catch(...)
	{
		throw;
	}

}


int CALLBACK BrowseCallbackProc(HWND hwnd,
                                UINT uMsg,
                                LPARAM lParam,
                                LPARAM lpData
                                )
{
    wchar_t szPath[MAX_PATH];

    switch(uMsg)
    {
    case BFFM_INITIALIZED:
        //SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
        int scrWidth,scrHeight;
        RECT rect, rect1;

        //get screen size
        scrWidth=GetSystemMetrics(SM_CXSCREEN);
        scrHeight=GetSystemMetrics(SM_CYSCREEN);
        //get window size
        GetWindowRect(hwnd,&rect);
        rect1.left = (scrWidth-rect.right+rect.left)/2;
        rect1.top =(scrHeight-rect.bottom+rect.top)/2;
        rect1.right=rect1.left + (rect.right-rect.left);
        rect1.bottom = rect1.top +  rect.bottom-rect.top;

        //set window position
        SetWindowPos(hwnd,HWND_TOP,rect1.left,rect1.top,rect1.right-rect1.left,rect1.bottom-rect1.top,SWP_SHOWWINDOW);

        break;

    case BFFM_SELCHANGED:
        break;
    }
    return   0;
}


bool TMainForm::user_select_image_folder(/*out*/string &folder_path)
{
    BROWSEINFO bInfo;
    TCHAR  path[MAX_PATH];
    LPMALLOC pMalloc;
    ZeroMemory(&bInfo, sizeof(bInfo));

    //bInfo.hwndOwner = NULL;
    bInfo.hwndOwner = Application->Handle;
    bInfo.lpszTitle = _T("Select Image Folder: ");
    bInfo.ulFlags   = BIF_RETURNONLYFSDIRS|BIF_EDITBOX;
    bInfo.lpfn      = BrowseCallbackProc;
    bInfo.lParam    = 0;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bInfo);

    if(pidl != NULL)
    {
        SHGetPathFromIDList(pidl, (char *)&path);

        folder_path = path;

        if(SUCCEEDED(SHGetMalloc(&pMalloc)))
        {
            pMalloc->Free(pidl);
            pMalloc->Release();
        }

        return true;

    }
    else
    {
        return false;
    }


    //
    //think about SelectDirectory is another ider for show dialog to choose path.
    //this is easy to control the initial path of dialog
    /*const   SELDIRHELP   =   1000;
    AnsiString   Dir   =   "C:\\";
    if(SelectDirectory(Dir, TSelectDirOpts() << sdAllowCreate  <<  sdPerformCreate   <<   sdPrompt, SELDIRHELP)
    )
    {
    //Application->MessageBox(Dir.c_str(), "dir");
    folder_path = Dir.c_str();
    }
    return false;
    */
}
//---------------------------------------------------------------------------

bool TMainForm::SearchAllLinkMapFile(string &folder)
{
	try
	{
		WIN32_FIND_DATA find_data;
		HANDLE hFind;
		bool bIsDirectory;
		string file_name, file_path, search_path;
		search_path = folder + "\\*.*";
		bool isFindValidFile=false;


		if(INVALID_FILE_ATTRIBUTES==GetFileAttributes(folder.c_str()))
		{
			   throw string("Invalid File Path");
		}

		hFind = FindFirstFile(search_path.c_str(), &find_data);
		if (hFind == INVALID_HANDLE_VALUE)
		{
			throw string("Invalid File Handle");
		}

		bIsDirectory = ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
		file_name = find_data.cFileName;

		if(!bIsDirectory)
		{
			if(true==m_p_Config_Manager->searchTargetFile(folder))
			{
				isFindValidFile=true;
			}
			else
			{
				if(true==m_p_scatter_manager->searchTargetFile(folder))
				{
					isFindValidFile=true;
				}
			}
		}
		else
		{
		   if((".." != file_name) && ("." != file_name))
		   {
			  file_path = folder + "\\";
			  file_path += find_data.cFileName;
			  SearchAllLinkMapFile(file_path);
		   }
		}

		//For Find next file
		while(FindNextFile(hFind, &find_data))
		{
			bIsDirectory = ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
			file_name = find_data.cFileName;

			if(!bIsDirectory)
			{
				if(false==isFindValidFile)
				{
					if(true==m_p_Config_Manager->searchTargetFile(folder))
					{
						isFindValidFile=true;
					}
					else
					{
						if(true==m_p_scatter_manager->searchTargetFile(folder))
						{
							isFindValidFile=true;
						}
					}
				}
			}
			else
			{
				if((".." != file_name) && ("." != file_name))
				{
				  file_path = folder + "\\";
				  file_path += find_data.cFileName;
				  SearchAllLinkMapFile(file_path);
				}
			}
		}

		FindClose(hFind);
		//do not find target file~
		return true;
	}
	catch(...)
	{
		throw;
	}
}


//====================================================================
void __fastcall TMainForm::btnReloadScatterFileClick(TObject *Sender)
{
    //  TButton *btn = (TButton*)Sender;
    TCHAR bug_Msg[256];
    int index = 1;
    vector<string> scatter_files;
    string folder_path=stScatterFile->Text.c_str();

    if(stScatterFile->Text.IsEmpty())
    {
        return;
    }

    m_p_LinkMapFileManager->clear();

    if(!SearchAllLinkMapFile(folder_path))
    {
		    return;
    }

    LoadAllLinkMapFile(folder_path);

    btnReloadScatterFile->Enabled = true;
    ScatterFileButton1->Enabled = true;

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(IDYES == Application->MessageBox("Do you want to exit?", "Multiport Download Tool", MB_YESNOCANCEL))
    {
        CanClose = true;
    }
    else
    {
        // IDNO IDCANCLE
        CanClose = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetbeginCOMport1Click(TObject *Sender)
{
	//dlgSetBeginComPort->Show();
	if(NULL==dlgSetBeginComPort)
	{
		dlgSetBeginComPort=new TdlgSetBeginComPort(MainForm);
	}
	dlgSetBeginComPort->ShowModal();

	//judege if the begin com port changed,
	//change the UI and ds
	Update_ComPortNumber();

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::miMDTLogClick(TObject *Sender)
{
    if( miMDTLog->Checked )
    {
        miMDTLog->Checked = false;
        GC_TRACE_OFF();
    }
    else
    {
        miMDTLog->Checked = true;
        GC_TRACE_ON();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miClearMDTLogClick(TObject *Sender)
{
    GC_TRACE_CLEAR();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Display_OptFlashType( void )
{
    AnsiString as_MDTLog =  INIFileH.read_OperateFlashType( "MultiPortFlashDownloadProject.ini", Application->ExeName );

    if( as_MDTLog.AnsiCompareIC("NAND") == 0 )
    {
        m_sDnParam.e_Operation = OPERATION_NFB;
        rbNAND->Checked = TRUE;
        rbNOR->Checked = FALSE;
    }
    else
    {
        m_sDnParam.e_Operation = OPERATION_NOR;
        rbNAND->Checked = FALSE;
        rbNOR->Checked = TRUE;
    }

}

//----------------------------------------------------------------------------
void TMainForm::Save_OptFlashType( void )
{
    if( rbNAND->Checked )
    {
        INIFileH.write_OperateFlashType( "MultiPortFlashDownloadProject.ini", Application->ExeName, "NAND");
    }
    else
    {
        INIFileH.write_OperateFlashType( "MultiPortFlashDownloadProject.ini", Application->ExeName, "NOR");
    }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Display_BBChipVerChecked( void )
{
    AnsiString as_ini =  INIFileH.read_BBChip_version_Checked( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_ini.AnsiCompareIC("no") == 0 )
    {
        miBBChipVersionCheck->Checked = FALSE;
    }
    else
    {
        miBBChipVersionCheck->Checked = TRUE;
    }

}


//----------------------------------------------------------------------------
void TMainForm::Save_BBChipVerChecked( void )
{
    if( miBBChipVersionCheck->Checked )
    {
        INIFileH.write_BBChip_version_Checke( "MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_BBChip_version_Checke( "MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}


//----------------------------------------------------------------------------
void TMainForm::Save_MDTLog( void )
{
    if( miMDTLog->Checked )
    {
        INIFileH.write_MDTLog( "MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_MDTLog( "MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}

//==============================================================================
void TMainForm::Display_MDTLog( void )
{
    AnsiString as_MDTLog =  INIFileH.read_MDTLog( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_MDTLog.AnsiCompareIC("no") == 0 )
    {
        miMDTLog->Checked = false;
        GC_TRACE_OFF();
    }
    else
    {
        miMDTLog->Checked = true;
        GC_TRACE_ON();
    }

}

//==============================================================================
void TMainForm::Display_Scatter(void)
{
	AnsiString LinkMapFileFolderPath;
	try
	{
		m_p_Config_Manager->clear();
		m_p_scatter_manager->clear();
		LinkMapFileFolderPath=  INIFileH.read_Scatter("MultiPortFlashDownloadProject.ini", Application->ExeName);

		if(LinkMapFileFolderPath=="")
		{
			return;
		}
		//Search and Load
		SearchAllLinkMapFile(LinkMapFileFolderPath.c_str());
		LoadAllLinkMapFile(LinkMapFileFolderPath.c_str());

		m_p_LinkMapFileManager->SetRootFolderPath(LinkMapFileFolderPath.c_str());
		stScatterFile->Text =LinkMapFileFolderPath;
	}
	catch(...)
	{
		GC_TRACE("TMainForm::Display_Scatter==>Catch Exception: Load Link MapFile Error!");
		m_p_Config_Manager->clear();
		m_p_scatter_manager->clear();
		stScatterFile->Text ="";
		INIFileH.write_Scatter("MultiPortFlashDownloadProject.ini",Application->ExeName,stScatterFile->Text);
	}

/*
	stScatterFile->Text =  INIFileH.read_Scatter("MultiPortFlashDownloadProject.ini", Application->ExeName);

	if(!stScatterFile->Text.IsEmpty())
	{
	    if(!m_scatter_manager.load(stScatterFile->Text.c_str()))
	    {
	        TCHAR bug_Msg[256];

	        sprintf(bug_Msg, "Load scatter file error! %s", m_scatter_manager.get_last_error().second.c_str());
	        Application->MessageBox(bug_Msg, "Fail", MB_OK );
	        stScatterFile->Text = "";
	    }
	    m_scatter_manager.config_from_ini();
	}
*/
}

//-----------------------------------------------------------------------------
void TMainForm::Save_Scatter(void)
{
    INIFileH.write_Scatter("MultiPortFlashDownloadProject.ini", Application->ExeName, stScatterFile->Text);
}

void __fastcall TMainForm::miEnableMMAA1Click(TObject *Sender)
{
    if( miEnableMMAA1->Checked )
    {
        miEnableMMAA1->Checked = false;
        UpdateMMAAEnable(false);
    }
    else
    {
        miEnableMMAA1->Checked = true;
        UpdateMMAAEnable(true);
    }
}
//---------------------------------------------------------------------------

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMainForm::Display_EnableMMAA( void )
{
    AnsiString as_EnableMMAA =  INIFileH.read_EnableMMAA( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_EnableMMAA.AnsiCompareIC("no") == 0 )
    {
        miEnableMMAA1->Checked = false;
        UpdateMMAAEnable(false);
    }
    else
    {
        miEnableMMAA1->Checked = true;
        UpdateMMAAEnable(true);
    }
}


//---------------------------------------------------------------------------
void TMainForm::Save_EnableMMAA( void )
{
    if( miEnableMMAA1->Checked )
    {
        INIFileH.write_EnableMMAA( "MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_EnableMMAA( "MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}

void TMainForm::Display_Read_USB_DL_WITH_TWO_SITE( void )
{
    AnsiString as_USB_Dl_Mode =  INIFileH.read_USB_DL_With_Two_Side( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_USB_Dl_Mode.AnsiCompareIC("no") == 0 )
    {
        miUSBDLWithTwoSteps->Checked = false;
    }
    else
    {
        miUSBDLWithTwoSteps->Checked = true;
    }
}


//---------------------------------------------------------------------------
void TMainForm::Save_Read_USB_DL_WITH_TWO_SITE( void )
{
    if( miUSBDLWithTwoSteps->Checked )
    {
        INIFileH.write_USB_DL_With_Two_Side( "MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_USB_DL_With_Two_Side( "MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}


void TMainForm::Display_EnterMetaModeAfterDLFMT( void )
{
    AnsiString as_Enter_Meta_Mode =  INIFileH.read_EnterMetaModeAfterDLFMT( "MultiPortFlashDownloadProject.ini", Application->ExeName );
    if( as_Enter_Meta_Mode.AnsiCompareIC("no") == 0 )
    {
        miEnterMetaModeafterDLFMT1->Checked = false;
    }
    else
    {
        miEnterMetaModeafterDLFMT1->Checked = true;
    }
}
//---------------------------------------------------------------------------
void TMainForm::Save_EnterMetaModeAfterDLFMT( void )
{
    if( miEnterMetaModeafterDLFMT1->Checked )
    {
        INIFileH.write_EnterMetaModeAfterDLFMT( "MultiPortFlashDownloadProject.ini", Application->ExeName, "yes");
    }
    else
    {
        INIFileH.write_EnterMetaModeAfterDLFMT( "MultiPortFlashDownloadProject.ini", Application->ExeName, "no");
    }
}


void TMainForm::Enable_NOR_NAND_slelect_rb()
{
    rbNOR->Enabled = true;
    rbNAND->Enabled = true;
}

void TMainForm::Disable_NOR_NAND_slelect_rb()
{
    rbNOR->Enabled = false;
    rbNAND->Enabled = false;
}


void __fastcall TMainForm::rbManualClick(TObject *Sender)
{
    Enable_NOR_NAND_slelect_rb();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::rbNANDClick(TObject *Sender)
{
    GC_TRACE("NFBClick");
    m_sDnParam.e_Operation = OPERATION_NFB;

    //rbManual->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::rbNORClick(TObject *Sender)
{
    GC_TRACE("NORClick");
    m_sDnParam.e_Operation = OPERATION_NOR;
    //RedrawLVList();
}

//----------------------------------------------------------------------------
E_OPERATION_T TMainForm::Get_Operation(void)
{
    if(rbNAND->Checked)
        return  OPERATION_NFB;
    else
        return  OPERATION_NOR;
}

//menu: scatter and load
void __fastcall TMainForm::Show_scatter_and_loadClick(TObject *Sender)
{
  try
  {
    map<string, MAUI_LoadHandle> image_infos;

    bool isNeedUpdate;
    GC_TRACE("Show sactter files and loads");

    if(NULL==m_p_LinkMapFileManager)
    {
        image_infos.clear();
    }
    else
    {
        if(!m_p_LinkMapFileManager->gather_load_info(image_infos))
        {
            GC_TRACE("ScatterFileManager::ggather_load_info fail");
        }
    }

    if(NULL==frmInputImage)
    {
        frmInputImage=new TfrmInputImage(MainForm);
    }
    frmInputImage->set_image_info(image_infos);

    isNeedUpdate=frmInputImage->ShowModal();

		/*
		if(isNeedUpdate&&(NULL!=m_p_LinkMapFileManager))
		{
			m_p_LinkMapFileManager->update_load(image_infos);
		}
		*/
	}
	catch(...)
	{
		Application->MessageBox("Error","MDT Exception",MB_ICONERROR);

	}
	//    m_scatter_manager.show_and_update_load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miBBChipVersionCheckClick(TObject *Sender)
{
    miBBChipVersionCheck->Checked = !miBBChipVersionCheck->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miUSBDLWithTwoStepsClick(TObject *Sender)
{
    miUSBDLWithTwoSteps->Checked = !miUSBDLWithTwoSteps->Checked;
}
//------------ ---------------------------------------------------------------

void __fastcall TMainForm::ClearAllLogsClick(TObject *Sender)
{
    Brom_DebugClear();
    META_DebugClear();
    GC_TRACE_CLEAR();
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::rbNANDMouseUp(TObject *Sender,
                                         TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //rbManual->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::rbNORMouseUp(TObject *Sender,
                                        TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //rbManual->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::miEnterMetaModeafterDLFMT1Click(TObject *Sender)
{
    //enter meta mode after DL/MFT
    if( miEnterMetaModeafterDLFMT1->Checked )
    {
        miEnterMetaModeafterDLFMT1->Checked = false;
    }
    else
    {
        miEnterMetaModeafterDLFMT1->Checked = true;
    }
}
//---------------------------------------------------------------------------


// check rom number in one station download
bool __fastcall TMainForm::CheckRomNumber(void)
{
#if 0
    //
    int handle_count = 0;
    int enabled_rom_num=0;
    int enabled_bl_num=0;

    DL_GetHandleNumber(g_DL_HANDLE_LIST, &handle_count);

    for (int handle_index=0; handle_index<handle_count; handle_index++)
    {
        DL_HANDLE_T p_dl_handle = NULL;

        DL_GetHandle(g_DL_HANDLE_LIST, handle_index, &p_dl_handle);

        if(NULL == p_dl_handle)
        {
            continue;
        }

        unsigned short rom_count = 0;
        ROM_INFO rom_info[MAX_LOAD_SECTIONS];

        DL_GetCount(p_dl_handle, &rom_count);

        if(S_DONE != DL_Rom_GetInfoAll(p_dl_handle, rom_info, MAX_LOAD_SECTIONS))
        {  //error
            return 1;
        }

        enabled_rom_num=0;
        enabled_bl_num=0;
        for (int rom_index=0; rom_index<rom_count; rom_index++)
        {
            if (   strcmpi(rom_info[rom_index].name, "BOOTLOADER") == 0
                || strcmpi(rom_info[rom_index].name, "ExtBootLoader") == 0)
            {
                enabled_bl_num++;
            }
            else
            {
                //if enable, count
                if(rom_info[rom_index].enable == _TRUE)
                {
                    enabled_rom_num++;
                }
            }
        }

        if(  enabled_rom_num<=0         //for check rom
            // || enabled_bl_num<=0    //for check bootloader
            )
        {
            //warning
            AnsiString str = "Please select at least one ROM for download";
            Application->MessageBox(str.c_str(), "Error", MB_OK);

            return 1 ; //stop

        }

    }

    return 0;
 #else
	return 0;
 #endif
}






void __fastcall TMainForm::miToolSettingClick(TObject *Sender)
{
    if(NULL==tool_setting)
    {
        tool_setting=new Ttool_setting(MainForm);
    }
    tool_setting->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenDeviceManager1Click(TObject *Sender)
{
    //open device manager, for user could check com port
    //command:     devmgmt.msc

    //HINSTANCE ShellExecute( HWND hwnd, LPCTSTR lpOperation, LPCTSTR lpFile,
    //   LPCTSTR lpParameters, LPCTSTR lpDirectory, INT nShowCmd );

    ShellExecute(NULL,"","devmgmt.msc","","",SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::m_stBkStatusDbClick(TObject *Sender)
{
      TStaticText *stext = (TStaticText*)Sender;

      GC_TRACE("DoubleClick backup status lable: ID: %d", stext->Tag);

      AnsiString folderpath;
    AnsiString currentfolder = stext->Hint;
    if(currentfolder=="")
    {
        return;
    }

    //folderpath = GetWorkingDir();
    //folderpath += "backup_and_restore_data\\";
    folderpath = currentfolder;
    //folderpath += "\\";

    //judge folder exist, if not, do nothing, return
     if  (!DirectoryExists(folderpath))
     {
         return;
     }
//HINSTANCE   ShellExecute( HWND hwnd, LPCTSTR lpOperation,  LPCTSTR lpFile, LPCTSTR lpParameters,
//  LPCTSTR   lpDirectory,   INT   nShowCmd   );
    AnsiString parameter = "/e," + folderpath;
    ShellExecute(NULL,"", "explorer.exe", parameter.c_str(), "", SW_SHOWNORMAL);

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------




void __fastcall TMainForm::EnableDisableeFuseWriter(TObject *Sender)
{
#if 1
  for(int i=0;i<MAX_SUPPORT_PORT_NUM;i++)
  {
    if( DownloadStatus[i] == DOWNLOAD_STATUS_RUNNING)
    {
      GC_TRACE("Thread %d is Running...",i);
      return ;
    }
  }
  if(this->ActionPage->ActivePage == this->eFuse)
  {
    this->ActionPage->ActivePage=this->DownloadAction;
    this->DownloadAction->TabVisible=true;
    this->eFuse->TabVisible=false;
    GC_TRACE("TMainForm::Disable eFuseWriter: ActionPage->ActivePageIndex : %d ",this->ActionPage->ActivePageIndex);
  }
  else if(this->ActionPage->ActivePage == this->DownloadAction)
  {
    Application->MessageBox("Do not use this option unless you really know what you are doing!","MDT Notice",MB_ICONWARNING);
    //
    if( NULL == p_efuse_write_file_reader )
    {
      p_efuse_write_file_reader = new CEFuseWriterConfigFile();
    }
    if( NULL == p_efuse_lock_file_reader )
    {
      p_efuse_lock_file_reader = new CEFuseWriterLockFile();
	}
        /*
	if( NULL == p_efuse_write_lock_argument)
	{
      p_efuse_write_lock_argument = new MDT_Efuse_Arg_All;
	}
      */
   // m_m_mdt_efuse_parameter_reader.clear();

    this->ActionPage->ActivePage=this->eFuse;
    this->DownloadAction->TabVisible=false;
    this->eFuse->TabVisible=true;
    GC_TRACE("TMainForm::Enable eFuseWriter: ActionPage->ActivePageIndex : %d ",this->ActionPage->ActivePageIndex);
  }
  else
  {
      //...
  }
#else
  GC_TRACE_EX("This action is not support");
#endif
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
  MDT_ERROR_STATUS mdt_status;
  AnsiString setting_file;

  try
  {
    if(eFuseSettingDialog->Execute())
    {
      setting_file = eFuseSettingDialog->FileName;
      mdt_status = p_efuse_write_file_reader->setfile(setting_file);
      if( MDT_OK != mdt_status)
      {
        throw (int)mdt_status;
      }
      mdt_status = p_efuse_write_file_reader->parsefile();
      if(MDT_OK != mdt_status)
      {
        throw (int)mdt_status;
      }
      const rwlock_writer_sentry Efuse_Setting_Parameter_Sentry(efuse_writer_handle.m_mdt_handle_lock,
	  	                                                        "EFuse Setting Parameter");
	  efuse_writer_handle.clearconfigfilesetting();
      mdt_status = p_efuse_write_file_reader->get_write_parameter(&efuse_writer_handle.m_common_arg,
       	                                                           &efuse_writer_handle.m_secure_arg
	  	                                                   );
	  efuse_writer_handle.PrintWriteParameterLog();

      if(MDT_OK != mdt_status)
      {
        throw (int)mdt_status;
      }
    }
    else
    {
      return ;
    }
    //G_EFuseWriterReader->ParseEFuseWriteParameter();
  }
  catch(int exp)
  {
  	Application->MessageBox(MDT_ErrorStatusToString(exp),"Error",MB_ICONWARNING);
  	this->eFuseSettingDialog->FileName="";
  }
  catch(...)
  {
  	Application->MessageBox("EFuseSetting Error","Error",MB_ICONERROR);
  	this->eFuseSettingDialog->FileName="";
  }
}
void __fastcall TMainForm::btnSelectEFuseSettingFileClick(TObject *Sender)
{
  MDT_ERROR_STATUS mdt_status;
  AnsiString setting_file;

  try
  {
    if(eFuseSettingDialog->Execute())
    {
      setting_file = eFuseSettingDialog->FileName;
      mdt_status = p_efuse_write_file_reader->setfile(setting_file);
      if( MDT_OK != mdt_status)
      {
        throw (int)mdt_status;
      }
      mdt_status = p_efuse_write_file_reader->parsefile();
      if(MDT_OK != mdt_status)
      {
        throw (int)mdt_status;
      }
      const rwlock_writer_sentry Efuse_Setting_Parameter_Sentry(efuse_writer_handle.m_mdt_handle_lock,
	  	                                                        "EFuse Setting Parameter");
	  efuse_writer_handle.clearconfigfilesetting();
      mdt_status = p_efuse_write_file_reader->get_write_parameter(&efuse_writer_handle.m_common_arg,
       	                                                           &efuse_writer_handle.m_secure_arg
	  	                                                   );
      if(MDT_OK != mdt_status)
      {
        throw (int)mdt_status;
      }
	  efuse_writer_handle.PrintWriteParameterLog();
    }
    else
    {
      return ;
    }
    //G_EFuseWriterReader->ParseEFuseWriteParameter();
  }
  catch(int exp)
  {
  	Application->MessageBox(MDT_ErrorStatusToString(exp),"Error",MB_ICONWARNING);
  	this->eFuseSettingDialog->FileName="";
  }
  catch(...)
  {
  	Application->MessageBox("EFuseSetting Error","Error",MB_ICONERROR);
  	this->eFuseSettingDialog->FileName="";
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnSelectEFuseLockFileClick(TObject *Sender)
{
  MDT_ERROR_STATUS mdt_status;

  try
  {
    if ( eFuseLockDialog->Execute() )
    {
      mdt_status=p_efuse_lock_file_reader->setfile(eFuseLockDialog->FileName);
      if( MDT_OK != mdt_status)
      {
        throw (int)mdt_status;
	  }

	  mdt_status=p_efuse_lock_file_reader->parsefile();
      if( MDT_OK != mdt_status)
      {
        throw (int)mdt_status;
	  }

	  const rwlock_writer_sentry Efuse_Lock_Parameter_Sentry(efuse_writer_handle.m_mdt_handle_lock,
															  "EFuse Setting Parameter");

	  efuse_writer_handle.clearlockfilesetting();
	  mdt_status = p_efuse_lock_file_reader->get_lock_parameter(&efuse_writer_handle.m_lock_arg);

	  if( MDT_OK != mdt_status)
	  {
	    throw (int)mdt_status;
	  }
	}
    else
    {
      return ;
    }

  }
  catch(int e)
  {
  	Application->MessageBox(MDT_ErrorStatusToString(e),"Error",MB_ICONWARNING);
  	this->eFuseLockDialog->FileName="";
  }
  catch(...)
  {
  	Application->MessageBox("EFuseSetting Error","Error",MB_ICONERROR);
  	this->eFuseLockDialog->FileName="";
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnEFuseSettingClearClick(TObject *Sender)
{
	//G_EFuseWriterReader->Clear();
	this->eFuseSettingDialog->FileName="";
	this->eFuseLockDialog->FileName="";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnEFuseParameterViewClick(TObject *Sender)
{
  AnsiString SettingFile,LockFile;

  rwlock_reader_sentry* p_efuse_reader_handle_sentry = NULL;
  rwlock_reader_sentry* p_efuse_write_handler_sentry = NULL;
  try
  {
    CheckUIEFuseSetting();
    EFuseWriterViewer=new TEFuseWriterViewer(this);

    if( EFuseReadCheckBox->Checked == true)
    {
      p_efuse_reader_handle_sentry= new rwlock_reader_sentry(m_efuse_read_handle_list.m_mdt_handle_lock);
      EFuseWriterViewer->set_efuse_reader_parameter(&m_efuse_read_handle_list);
    }
    else
    {
      p_efuse_write_handler_sentry = new rwlock_reader_sentry(efuse_writer_handle.m_mdt_handle_lock);
      if(EFuseWriteCheckBox->Checked == true)
      {
        SettingFile = eFuseSettingDialog->FileName;
      }

	  if(EFuseLockCheckBox->Checked == true)
	  {
	    LockFile = eFuseLockDialog->FileName;
      }
	  EFuseWriterViewer->SetEfuseSettingLockFile(SettingFile,LockFile);
      EFuseWriterViewer->set_efuse_writer_parameter(&efuse_writer_handle);
    }
    EFuseWriterViewer->ShowModal();
	delete p_efuse_reader_handle_sentry;
	delete p_efuse_write_handler_sentry;
    delete EFuseWriterViewer;
    EFuseWriterViewer=NULL;
  }
  catch(int exp)
  {
  	Application->MessageBox(MDT_ErrorStatusToString(exp),"EFuseParameterError",MB_ICONWARNING);
  }
  catch(string exp)
  {
  	Application->MessageBox(exp.c_str(),"EFuseParameterError",MB_ICONWARNING);
  }
  catch(...)
  {
  	Application->MessageBox("Unknown Error","EFuseParameterError",MB_ICONWARNING);
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EFuseWriteCheckBoxClick(TObject *Sender)
{
	if(this->EFuseWriteCheckBox->Checked==true)
	{
		this->btnSelectEFuseSettingFile->Enabled=true;

	}
	else
	{
		this->btnSelectEFuseSettingFile->Enabled=false;
		this->eFuseSettingDialog->FileName="";
		efuse_writer_handle.clearconfigfilesetting();

		//G_EFuseWriterReader->ClearSettingParameter();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EFuseLockCheckBoxClick(TObject *Sender)
{
	if(this->EFuseLockCheckBox->Checked==true)
	{
		this->btnSelectEFuseLockFile->Enabled=true;
	}
	else
	{
		this->btnSelectEFuseLockFile->Enabled=false;
		this->eFuseLockDialog->FileName="";
		efuse_writer_handle.clearlockfilesetting();
		/*
		if(NULL==G_EFuseWriterReader)
		{
			G_EFuseWriterReader=new TEFuseWriterParameterReader();
		}
		G_EFuseWriterReader->ClearLockParameter();
		*/
	}

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckUIEFuseSetting()
{
  if( EFuseReadCheckBox->Checked == true)
  {
    return;
  }
  else
  {
    if(EFuseWriteCheckBox->Checked==false && EFuseLockCheckBox->Checked==false)
    {
    throw string("Please Select At Least One: Read/Write/Lock");
    }
    if(EFuseWriteCheckBox->Checked==true && eFuseSettingDialog->FileName=="")
    {
    throw string("Please Select Setting.ini File");
    }
    if(EFuseLockCheckBox->Checked==true && eFuseLockDialog->FileName=="")
    {
    throw string("Please Select Lock.ini File");
    }
  }
}
//---------------------------------------------------------------------------
bool _fastcall TMainForm::IsUSBDownloadWithTwoSite()
{
    if (m_rbUSB->Checked)
    {
        return true;
    }
    return false;
}


void __fastcall TMainForm::ShowFactoryDatabaseFileClick(TObject *Sender)
{
	Application->MessageBox(as_DataSource.c_str(),"Factory File",MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EFuseReadCheckBoxClick(TObject *Sender)
{
  if( true == this->EFuseReadCheckBox->Checked)
  {
	this->EFuseWriteCheckBox->Enabled = false;
	if ( true == this->EFuseWriteCheckBox->Checked)
	{
      this->btnSelectEFuseSettingFile->Enabled = false;
	}
	this->EFuseLockCheckBox->Enabled = false;
    if ( true == this->EFuseLockCheckBox->Checked)
	{
      this->btnSelectEFuseLockFile->Enabled = false;
	}
  }
  else
  {
	this->EFuseWriteCheckBox->Enabled = true;
	if ( true == this->EFuseWriteCheckBox->Checked)
	{
      this->btnSelectEFuseSettingFile->Enabled = true;
	}
	this->EFuseLockCheckBox->Enabled = true;
    if ( true == this->EFuseLockCheckBox->Checked)
	{
      this->btnSelectEFuseLockFile->Enabled = true;
	}

  }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::USBDownloadWOBatteryClick(TObject *Sender)
{
    if( USBDownloadWOBattery->Checked )
    {
        USBDownloadWOBattery->Checked = false;
    }
    else
    {
        USBDownloadWOBattery->Checked = true;
	AnsiString as_DownloadRetry =  INIFileH.read_DownloadRetryCount( "MultiPortFlashDownloadProject.ini", Application->ExeName );
        g_DownloadRetry= StrToInt(as_DownloadRetry);
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_miUploadUserDataOnlyClick(TObject *Sender)
{
    UnCheckBackupAndRestoreMenuItem();
    m_miUploadUserDataOnly->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Btn_Select_RootCert_FileClick(TObject *Sender)
{
  this->BootCert_File_OpenDialog->FileName = "";
  if(BootCert_File_OpenDialog->Execute())
  {
    if( LoadFile(BootCert_File_OpenDialog->FileName.c_str(),
                  &m_boot_Cert.m_data,&m_boot_Cert.m_len,NULL))
    {
      AnsiString msg;

      msg.printf("Failed to load Boot Cert file \"%s\"",
                 BootCert_File_OpenDialog->FileName.c_str());
      ShowMessage(msg);
      return;
    }
    else
    {
      AnsiString msg;

      msg.printf("Load %s Success",BootCert_File_OpenDialog->FileName.c_str() );
      ShowMessage(msg);
        return;
    }
  }
  else
  {
    return;
  }
}
//---------------------------------------------------------------------------
int TMainForm::LoadFile(const char *pathname, unsigned char **pp_buf, unsigned int *p_nFileLength, long *p_last_modify_time)
{

	FILE *fp;
    unsigned int    ret;

	if( NULL == pp_buf ) {
		return 1;
	}

    ret = LoadFileInfo(pathname, p_nFileLength, p_last_modify_time);
    if( ret ){
        return ret;
    }

	file_open_sentry	file_sentry(pathname, "rb", fp);

    unsigned int buf_len = *p_nFileLength;
	unsigned char *buf;

	if( NULL == (buf=(unsigned char *)malloc(buf_len)) ) {
		return 5;
	}

	if( buf_len > fread(buf, 1, buf_len, fp) ) {
		free(buf);
		return 6;
	}

	if( NULL != *pp_buf ) {
		free(*pp_buf);
	}

	*pp_buf = buf;

	return 0;
}
//---------------------------------------------------------------------------
int TMainForm::LoadFileInfo(const char *pathname, unsigned int *p_nFileLength, long *p_last_modify_time)
{
	FILE *fp;
	struct _stat  file_stat={0};

	if( NULL == pathname || '\0' == pathname[0] || NULL == p_nFileLength ) return 1;


	file_open_sentry	file_sentry(pathname, "rb", fp);

    if( NULL == fp ) {
        return 2;
    }

	if( _fstat(fileno(fp), &file_stat) ) {
		return 3;
	}

	unsigned int file_len;
	unsigned int buf_len;

	if( 0 >= (file_len=filelength(fileno(fp))) ) {
		return 4;
	}

	if( 0 != (file_len%2) ) {
		buf_len = file_len+1;
	}
	else {
		buf_len = file_len;
	}

	*p_nFileLength = buf_len;
	if( NULL != p_last_modify_time ) {
		*p_last_modify_time = file_stat.st_mtime;
	}

    return 0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mi_USBDownloadReadbackDataCardClick(
      TObject *Sender)
{
//
  if(mi_USBDownloadReadbackDataCard->Checked == false)
  {
    mi_USBDownloadReadbackDataCard->Checked = true;
    MainForm->sbMPDT->Panels->Items[0]->Text = "Your COM Port Group Box is disabled!!!";

    m_rbUSB->Checked = true;
    m_Gb_ComPortType->Enabled = false;
    m_rbUART->Enabled = false;
    m_rbUSB->Enabled = false;
    m_rbUART_USB->Enabled = false;

    mi_USBDownloadReadbackDualTalk->Enabled = false;
    mi_USBDownloadReadbackDualTalk->Checked = false;
    if( NULL != USBCardDownloadHandle)
    {
      DisableUSBSwitch(USBCardDownloadHandle);
      USBCardDownloadHandle = NULL;
    }
    if(USBCardDownloadHandle == NULL)
    {
      USBCardDownloadHandle = EnableUSBSwitch("-b");
    }
  }
  else
  {
    mi_USBDownloadReadbackDataCard->Checked = false;

    m_Gb_ComPortType->Enabled = true;
    m_rbUART->Enabled = true;
    m_rbUSB->Enabled = true;
    m_rbUART_USB->Enabled = true;

    m_Gb_ComPortType->Hint = "";
    MainForm->sbMPDT->Panels->Items[0]->Text = "";
    mi_USBDownloadReadbackDualTalk->Enabled = true;
   // mi_USBDownloadReadbackDualTalk->Checked = true;
    if( NULL != USBCardDownloadHandle)
    {
      DisableUSBSwitch(USBCardDownloadHandle);
      USBCardDownloadHandle = NULL;
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::USBMetaModeAfterOneStationDownload1Click(
      TObject *Sender)
{
  if(USBMetaModeAfterOneStationDownload1->Checked)
  {
    USBMetaModeAfterOneStationDownload1->Checked = false;
  }
  else
  {
    USBMetaModeAfterOneStationDownload1->Checked = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenRootCertFileClick(TObject *Sender)
{
//Open and load root cert file
  AnsiString root_cert_file;

  if (!RootCertFileOpenDialog->Execute())
  {
    return ;
  }
  root_cert_file = RootCertFileOpenDialog->FileName;

  if (root_cert_file.Length() == 0)
  {
    return ;
  }
  ROOTCERT_Unload(g_ROOTCERT_HANDLE);
  g_is_Root_Cert_File_Loaded= false;

  const int ret = ROOTCERT_Load(g_ROOTCERT_HANDLE, root_cert_file.c_str());

  if (ret != S_DONE)
  {
    g_is_Root_Cert_File_Loaded = false;
    root_cert_file = "";
    if (ret == S_FTHND_HANDLE_BUSY_NOW)
    {
      Application->MessageBox("Program is busy! Can not reload Root CERT file right now.","Error",MB_ICONWARNING);
    }
    else
    {
      Application->MessageBox("Load ROOTCERT file fail!","Error",MB_ICONWARNING);
    }
    GC_TRACE_EX("Load Root Cert File Error");
  }
  else
  {
    g_is_Root_Cert_File_Loaded= true;
    //g_ROOTCERT_File = ed_ROOTCERT_File->Text;
    GC_TRACE_EX("Load Root Cert File Success");
  }
  this->RootCert_File_DisplayEdit->Text = root_cert_file;

  return ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenCertificateFileClick(TObject *Sender)
{
//open and load certificate file...
  AnsiString certificate_file;

  if (!CertificateFileOpenDialog->Execute())
  {
    return;
  }
  certificate_file = CertificateFileOpenDialog->FileName;
  if (certificate_file.Length() == 0)
  {
    return ;
  }
  SCERT_Unload(g_SCERT_HANDLE);
  g_is_Certificate_File_Loaded= false;

  const int ret = SCERT_Load(g_SCERT_HANDLE, certificate_file.c_str());

  if (ret != S_DONE)
  {
    certificate_file = "";
    g_is_Certificate_File_Loaded = false;

    if (ret == S_FTHND_HANDLE_BUSY_NOW)
    {
      Application->MessageBox("Program is busy! Can not reload CERT file right now.","Error",MB_ICONWARNING);
    }
    else
    {
      Application->MessageBox("Load Certificate file fail!","Error",MB_ICONWARNING);
    }
    GC_TRACE_EX("Load Certificate File Fail");
  }
  else
  {
    g_is_Certificate_File_Loaded = true;
    GC_TRACE_EX("Load Certificate File Success");
  }
  this->Certificate_File_DisplayEdit->Text = certificate_file;
  return ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SendRootCertForcelyClick(TObject *Sender)
{
  if(false == this->SendRootCertForcely->Checked)
  {
    this->SendRootCertForcely->Checked = true;
    g_is_Send_Root_Cert_Forcely = true;
  }
  else
  {
    this->SendRootCertForcely->Checked = false;
    g_is_Send_Root_Cert_Forcely = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EnableUSB11to20Click(TObject *Sender)
{
    if(EnableUSB11to20->Checked)
    {
        EnableUSB11to20->Checked = false;
		    m_bEnableUSB1_1To2_0=_FALSE;
      //  UpdateMMAAEnable(false);
    }
    else
    {
        EnableUSB11to20->Checked = true;
       // UpdateMMAAEnable(true);
       m_bEnableUSB1_1To2_0=_TRUE;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mi_USBDownloadReadbackDualTalkClick(
      TObject *Sender)
{
	   char tmpBuf[512];
	   if(mi_USBDownloadReadbackDualTalk->Checked == false)
	   {
		   mi_USBDownloadReadbackDualTalk->Checked = true;
		   m_Gb_ComPortType->Enabled = false;
		   mi_USBDownloadReadbackDataCard->Enabled = false;
		   mi_USBDownloadReadbackDataCard->Checked = false;
		   MainForm->sbMPDT->Panels->Items[0]->Text = "USBDownloadReadbackDualTalk is checked;Your COM Port Group Box is disabled!!!";
		   m_rbUSB->Checked = true;
		   m_rbUART->Enabled = false;
		   m_rbUSB->Enabled = false;
		   m_rbUART_USB->Enabled = false;
		   
		//remove by mtk71518,2013-0717
		/* 
		   if(MainForm->dtProcessInfo.hProcess != NULL)
		   {
			   if(TerminateProcess(MainForm->dtProcessInfo.hProcess, 0)!=0)
			   {
				  MainForm->sbMPDT->Panels->Items[0]->Text = "TerminateProcess OK!";
				  CloseHandle(MainForm->dtProcessInfo.hThread);
				  CloseHandle(MainForm->dtProcessInfo.hProcess);
			   }
		   }
	
		  if (false == ::CreateProcess("DualTalkSwitchTool.exe",
						   "",
						   0,
						   0,
						   false,
						   CREATE_NO_WINDOW, //CREATE_DEFAULT_ERROR_MODE
						   0,
						   0,
						   &MainForm->dtStartupInfo,
						   &MainForm->dtProcessInfo))
		   {
			   ShowMessage("Cannot create DualTalkSwitchTool process to switch com port!!");
		   }	
		   */
	
	
		  }
		  else
		  {
			  m_Gb_ComPortType->Enabled = true;
			  m_rbUART->Enabled = true;
			  m_rbUSB->Enabled = true;
			  m_rbUART_USB->Enabled = true;
	
			  mi_USBDownloadReadbackDualTalk->Checked = false;
			  mi_USBDownloadReadbackDataCard->Enabled = true;
			  m_Gb_ComPortType->Hint = "";
	
			  MainForm->sbMPDT->Panels->Items[0]->Text = "";
		  }
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::EnableBackupNvramPartionClick(TObject *Sender)
{
   if(EnableBackupNvramPartion->Checked)
   {
      EnableBackupNvramPartion->Checked = false;
      //m_bEnableBackupNvramPartition = false;
      m_bEnableBackupNvramPartition =LNP_NONE;//0;mingxue
   }
   else
   {
      EnableBackupNvramPartion->Checked = true;
      //m_bEnableBackupNvramPartition = true;
      m_bEnableBackupNvramPartition =LNP_BACKUP_RESTORE;//1;mingxue
   }
}
//---------------------------------------------------------------------------




void __fastcall TMainForm::m_miCheckSDSClick(TObject *Sender)
{
    UnCheckBackupAndRestoreMenuItem();
    m_miCheckSDS->Checked = true;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::FlashSafeModeClick(TObject *Sender)
{
   if(FlashSafeMode->Checked)
   {
      FlashSafeMode->Checked = false;
      m_bEnableFlashSafeMode = false;
   }
   else
   {
      FlashSafeMode->Checked = true;
      m_bEnableFlashSafeMode = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SwitchToOperator1Click(TObject *Sender)
{
	BYTE key[10]="03055030";    
    BYTE password[LOGIN_PASSWORD_MAX];	
	AnsiString asSetupPath = "";
	
    if(ReadDataFromFile(password,LOGIN_PASSWORD_MAX, key, m_asPasswdFilePath.c_str()) == S_DES_SUCCESS)
    {      
	    password[0] = '0';
		password[1] = '0';
		if(WriteDataToFile(password, LOGIN_PASSWORD_MAX, key, m_asPasswdFilePath.c_str())  == S_DES_SUCCESS)
		{
		   m_LoginIdentify = LOGIN_OPERATOR;
		   Disable_UIComponent();
		}
    }
    SetWindowText(this->Handle, "Multiple Download Tool - Operator Mode");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ChangePassword1Click(TObject *Sender)
{
     AnsiString as;
     unsigned int ret;
     if(NULL == Form_Chgpasswd)
     {
	    Form_Chgpasswd = new TForm_Chgpasswd(MainForm);
     }



	Form_Chgpasswd->Left = MainForm->Left+100;
	Form_Chgpasswd->Top  = MainForm->Top+60;

	 // show Change Engineer password Form
	 Form_Chgpasswd->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SwitchToEngineer1Click(TObject *Sender)
{
     AnsiString as;
     unsigned int ret;
     if(NULL == Form_Engineerpw)
     {
         Form_Engineerpw = new TForm_Engineerpw(MainForm);
     }

     Form_Engineerpw->Left = MainForm->Left+100;
     Form_Engineerpw->Top  = MainForm->Top+60;

     // show Input Engineer password Form
     Form_Engineerpw->ShowModal();
}
//---------------------------------------------------------------------------

