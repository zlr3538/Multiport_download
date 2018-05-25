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
 *   FlashDownload.h
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  Flash download/format thread header file
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
 * Sep 8 2008 MTK02172
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
 * Dec 3 2007 mtk00490
 * [STP100001572] [Multiport download tool] Multiport download tool ver 3.0748.0
 *
 *
 * Nov 29 2006 mtk00490
 * [STP100001239] [Multiport download tool] Multiport download tool ver 3.1.02
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

//---------------------------------------------------------------------------
#ifndef _FLASHDOWNLOAD_H_
#define _FLASHDOWNLOAD_H_
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <set>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdio.h>
//---------------------------------------------------------------------------
#include "brom_dll/inc/flashtool.h"
#include "brom_dll/inc/brom.h"
#include "brom_dll/inc/sp_brom.h"
#include "brom_dll/inc/flashtool_handle.h"
#include "brom_dll/inc/mtk_mcu.h"
#include "brom_dll/inc/DOWNLOAD.h"
#include "common/multiport_common.h"
#include "mdt_component/thread/inc/metaapp_common.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
extern struct DA_HANDLE	*g_DA_HANDLE;
extern DWORD ThreadBootUpTimeTable[MAX_SUPPORT_PORT_NUM];
extern HANDLE ThreadBootUpTimeTableMutex;
extern  HANDLE Flash_Download_Event[MAX_SUPPORT_PORT_NUM];
extern  HANDLE Wait_USB_Insert_Event[MAX_SUPPORT_PORT_NUM];
extern  HANDLE User_Stop_Event[MAX_SUPPORT_PORT_NUM];
extern  int    g_iStopFlag[MAX_SUPPORT_PORT_NUM];
//---------------------------------------------------------------------------
class TBOOT1 : public TThread
{
private:
		// message handle
		HANDLE hPostMsgDestHandle;


		E_CheckUSBResult checkusbresult; //for check usb cable pid vid. In two station usb download
		E_CheckMetaExtraError check_meta_extra_result; // for extra meta error
		AnsiString  m_CurrentbackupFolder;
		AnsiString  m_CurrentbackupFolderRule;
public:
		int ret;
		int m_iComPortIdx;
		FLASHTOOL_ARG	m_sFtArg;
		FLASHTOOL_DOWNLOAD_ARG	m_sFtDlArg;
		FLASHTOOL_RESULT  m_sFtResult;
		FLASHTOOL_DOWNLOAD_RESULT   m_sFtDnResult;
		FLASHTOOL_FORMAT_ARG	m_sFmtArg;
		FLASHTOOL_FORMAT_RESULT m_sFmtResult;

		FLASHTOOL_ENABLE_BOOT_ARG m_sEnableBoot_Arg;

        // META common
        bool m_bBackup;
        bool m_bInMetaMode;
        META_RESULT m_eMetaResult;
        METAAPP_OP_T m_eMetaappOp;
        //W/O Retry
        unsigned int m_RetryTimes;
		unsigned int m_RetryFlag;
		// for upload file
    	bool	 		bUpdateFinishBytes;
		unsigned char	progress_percentage;
		unsigned long	progress_finished_bytes;
		unsigned long	progress_total_bytes;

protected:
        virtual void __fastcall Execute();
        int __fastcall ExecuteInternal();
		int __fastcall Init_FlashTool_arg();//mingxue 2013-3-16
		int __fastcall Flash_Execute();//mingxue 2013-3-16
		E_WAIT_FOR_USB_INSERT_STATUS __fastcall WaitForUSBInsert(unsigned short EventIndex);
		E_WAIT_FOR_USB_INSERT_STATUS __fastcall WaitForUSBInsertByOpenComport(unsigned short EventIndex);
		E_WAIT_FOR_USB_INSERT_STATUS __fastcall TBOOT1::WaitForUSBDraw(unsigned short EventIndex);

		void __fastcall WaitForComPortReadyAfterRegisterReady(unsigned short ComPortIndex);


public:
		//COM_PORT_HANDLE     m_com_port;
		S_DN_PARAM_T       m_sDnParam;
		COM_PORT_SETTING m_sComPortSetting;
		E_FLASHTOOL_FUNCTION m_eFunctionProgress;
		E_FLASHTOOL_WITHOUT_BATTERY m_eWithoutBatteryKey;

		// message
		AnsiString m_asMsg;

		AnsiString prefix;
		//TColor m_ePbForeColer;
		unsigned char m_ucProgressPercentage;

		unsigned int WatchDogTimeOutInterval;

		E_USB_Download_Support_Status USB_DL_Support_Status;
		int __fastcall GetWatchDogTimeOutInterval();

		// PCMCIA card
		TThread *m_ptPCMCIA;

		__fastcall TBOOT1(bool CreateSuspended, HANDLE hMsgHandle, COM_PORT_SETTING com_port_setting, S_DN_PARAM_T dn_param);

		// synchronize function;
		void _fastcall Start();
		void _fastcall SyncStart();
		void _fastcall StopTimer();
		void _fastcall SyncStopTimer();
		void _fastcall ShowMsg();
		void _fastcall SyncShowMsg();
		void _fastcall InitProgress();
		void _fastcall SyncInitProgress();
		void _fastcall UpdateProgress();
		void _fastcall SyncUpdateProgress();
		void _fastcall UpdateResultOk();
		void _fastcall SyncUpdateResultOk();
		void _fastcall UpdateMETAHandle();
        AnsiString _fastcall RetStatusToString(int iRet);
		//void _fastcall SyncUpdateMETAHandle();
		void _fastcall UpdateResultError();
		void _fastcall SyncUpdateResultError();
		void _fastcall UpdateMetaResultOk();
		void _fastcall SyncUpdateMetaResultOk();
		void _fastcall UpdateMetaResultError();
		void _fastcall SyncUpdateMetaResultError();
		//-----------------check SDS
		void _fastcall UpdateCheckSDSResultOk();
		void _fastcall SyncCheckSDSResultOk();
		void _fastcall UpdateCheckSDSResultError(int ret);
		void _fastcall SyncCheckSDSResultError(int ret);
		//void _fastcall UpdateMainFormAfterFinishErr(void);
		//void _fastcall SyncUpdateMainFormAfterFinishErr(void);
		//void _fastcall UpdateMainFormAfterFinishOk(void);
		//void _fastcall SyncUpdateMainFormAfterFinishOk(void);
		void _fastcall SyncEnableUI();
		void _fastcall EnableUI();

        // META common
        META_RESULT _fastcall Enter_META_Mode(BOOT_RESULT& boot_result,const BBCHIP_TYPE bbchip, const EXT_CLOCK  ext_clock);
		META_RESULT _fastcall Enter_META_Mode_ForOneStationUSBMeta(const BBCHIP_TYPE bbchip,
																	const EXT_CLOCK  ext_clock,
																	unsigned char com_port);

        META_RESULT _fastcall Exit_META_Mode(bool IsShutdownTarget=false);
        META_RESULT  _fastcall ArgMETAConnectWithTarget( META_Connect_Req &meta_con_req, META_Connect_Report   &meta_con_report);
        META_RESULT  _fastcall ArgMETAConnectWithTargetViaUSB( META_ConnectByUSB_Req &meta_con_req, META_ConnectByUSB_Report &meta_con_report);
        bool _fastcall is_have_meta_action_before_download();
        bool _fastcall is_have_action_after_download();

        // Reset to factory default
        bool _fastcall Query_BackupCalData_Support(void);
        META_RESULT _fastcall CheckBackupResultInfo(void);
        META_RESULT _fastcall Reset_To_Factory_Default_Procedure(const BBCHIP_TYPE  bbchip, const EXT_CLOCK  ext_clock);
        META_RESULT _fastcall Reset_To_Factory_Default(void);
        void _fastcall ResetFactoryDefaultProgress();
        void _fastcall SyncResetFactoryDefaultProgress();
        void _fastcall StartFactoryDefaultProgress();
        void _fastcall SyncStartFactoryDefaultProgress();
        void _fastcall StopFactoryDefaultProgress();
        void _fastcall SyncStopFactoryDefaultProgress();
        void _fastcall FinishFactoryDefaultProgress();
        void _fastcall SyncFinishFactoryDefaultProgress();


        // error message
        void __fastcall GetErrorMessag(STATUS_E id, unsigned int m_msp_error_code);

        // GPS
        //WRAPPER_RETURN _fastcall GPSDownload(void);
        //void __fastcall GetGPSErrorMessag(WRAPPER_RETURN id);

        // backup & restore calibration data
        META_RESULT _fastcall BackupCalData(void);
        META_RESULT _fastcall RestoreCalData(void);
        //void _fastcall StartBackupCalData();
        //void _fastcall SyncStartBackupCalData();
        void _fastcall StartBackupCalDataProgress();
        void _fastcall SyncStartBackupCalDataProgress();
        //void _fastcall StopBackupCalDataProgress();
        //void _fastcall SyncStopBackupCalDataProgress();
        void _fastcall StartRestoreCalDataProgress();
        void _fastcall SyncStartRestoreCalDataProgress();

		void _fastcall StartCheckDataProgress();
		void _fastcall SyncStartCheckDataProgress();

		// Upload user data
		META_RESULT _fastcall UploadUserData();
		META_RESULT _fastcall UploadUserData_ForOneStationDownloadViaUSB();

		//check SDS
		META_RESULT _fastcall CheckSDS(int* ret);
		bool _fastcall ReadBardcode(META_GET_BARCODE_T get_barcode);

		void _fastcall StartUploadUserDataProgress();
		void _fastcall SyncStartUploadUserDataProgress();

		//enter meta mode only
		META_RESULT _fastcall EnterMetaModeOnly(void);
		//
		bool __fastcall IsEnterMetaModeAfterDLMFT(void );

		// export information
		METAAPP_OP_T _fastcall Get_MetaAppOp(void);


        //Sync backup & restore
        unsigned char _ucBackUpTotalNum;
        unsigned char _ucBackupNum;
        unsigned char _ucRestoreTotalNum;
        unsigned char _ucRestoreNum;
        unsigned char _ucUploadTotalNum;
        unsigned char _ucUploadNum;

		virtual void __fastcall DisableROM(DL_HANDLE_LIST_T &dl_handle_list);
		virtual void __fastcall DisableROM(DL_HANDLE_T &dl_handle);

		virtual int __fastcall DisableBootloader(DL_HANDLE_LIST_T &dl_handle_list);
		virtual int __fastcall DisableBootloader(DL_HANDLE_T &dl_handle);


		virtual int __fastcall FlashDownload_OnlyROM(COM_PORT_SETTING *p_com_setting,
		                  const FLASHTOOL_ARG *p_arg,
		                  FLASHTOOL_RESULT *p_result,
		                  FLASHTOOL_DOWNLOAD_ARG *p_dl_arg,
		                  FLASHTOOL_DOWNLOAD_RESULT *p_dl_result,
		                  int *p_stopflag);
		virtual int __fastcall FlashDownload_OnlyROM_ForUploadUserDataViaUSB(
			      COM_PORT_SETTING *p_com_setting,
	              const FLASHTOOL_ARG *p_arg,
	              FLASHTOOL_RESULT *p_result,
	              FLASHTOOL_DOWNLOAD_ARG *p_dl_arg,
	              FLASHTOOL_DOWNLOAD_RESULT *p_dl_result,
	              int *p_stopflag);


    virtual int __fastcall uart_download_bootloader();
    virtual int __fastcall DL_Connect(FLASHTOOL_API_HANDLE_T &ft_api_handle,_BOOL isUSBMode,unsigned char com_port);
    virtual int __fastcall DL_Change_Baudrate(FLASHTOOL_API_HANDLE_T &ft_api_handle);
    virtual int __fastcall DL_BootLoader(FLASHTOOL_API_HANDLE_T &ft_api_handle);
    virtual int __fastcall DL_Enable_WatchDogTimeout(FLASHTOOL_API_HANDLE_T &ft_api_handle);
    virtual void _fastcall Boot_Arg_Setting(BOOT_FLASHTOOL_ARG	&boot_arg,_BOOL isUSBMode);

    void _fastcall Sync_refresh_backup_progress( void );
    void _fastcall Refresh_backup_progress( void );
    void _fastcall Sync_refresh_restore_progress( void );
    void _fastcall Refresh_restore_progress( void );
    void _fastcall Sync_refresh_upload_progress( void );
    void _fastcall Refresh_upload_progress( void );

    //init download arg
    void _fastcall Set_FlashTool_arg(void);
    void _fastcall Set_FlashTool_download_arg(void);
    bool _fastcall Get_BMTPoolAddress(unsigned int * iBmt_Pool_Address);

    E_ResultAndAction _fastcall Meta_action_before_download();
    virtual void _fastcall Initial_download_arg_memory();
    E_ResultAndAction _fastcall Action_after_download();
    virtual E_ResultAndAction _fastcall Format();
    bool _fastcall Download_bootloader_for_usb_download();
    bool _fastcall Download_rom_for_usb_download();

    bool _fastcall Unload_all_bootloader();
    bool _fastcall Load_all_bootloader();

    //bool _fastcall Load_all_rom_except_bootloader();
    //void  _fastcall Disable_all_bootloader_in_two_station_usb_dl();

    std::set<int>   m_exist_com_port;
    void            scan_exist_com_port( std::set<int>  &exist_com_ports /*out*/ );
    int             get_new_created_com_port();

    bool __fastcall is_roms_include_bootloader(ROM_INFO *p_rom_info, int rom_count);

    E_USB_Download_Support_Status __fastcall Is_Support_BROM_USB_DL();

    virtual void __fastcall printProcessInfo();
    int _fastcall boot_meta_in_brom_stage();

    // USB COM
    bool __fastcall EnumerateUsbCom(unsigned short us_target_com_num);
    bool __fastcall waitforUsbComClear(unsigned short us_target_com_num);
    bool _fastcall IsUSBDownloadWithTwoSite();
    E_CheckUSBResult __fastcall check_is_usb_cable(void);
    bool __fastcall WaitForUSBCOMPortReady(unsigned short comPortNum);
    bool __fastcall WaitForUSBCOMPortDisappear(unsigned short comPortNum);
    void _fastcall UpdateProgressStatus(const int index,const AnsiString& Contect,const unsigned char per);
    void _fastcall UpdateEfuseOperationProgressBarSetting();
	bool __fastcall IsUSBModeUploadUserDataAfterOneStationDownload();
    void _fastcall Set_FlashTool_EnableBootCert_arg(void);
};
//---------------------------------------------------------------------------


extern vector<int> G_Available_USB_ComPort;;


#endif
