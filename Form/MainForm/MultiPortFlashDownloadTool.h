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
 *   MultiPortFlashDownloadTool.h
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *  Multiport download form header
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
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifndef _MUTLIPORTFLASHDOWNLOADTOOL_H_
#define _MUTLIPORTFLASHDOWNLOADTOOL_H_
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>

//#pragma warning(disable: 8058)
//#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
//#include <Menus.hpp>
#include <CGAUGES.h>

#include <ADODB.hpp>
#include <DB.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>

#include "SetBeginComPort.h"
#include "ToolSetting.h"
#include "brom_dll/inc/flashtool_handle.h"
#include "brom_dll/inc/mtk_mcu.h"
#include "brom_dll/inc/download.h"
#include "Multiport_Common.h"
#include "INIFileHandle/inc/INIFileHandle.h"

#include "LinkMapFileManager/inc/ScatterFileManager.h"
#include "brom_dll/inc/brom.h"
#include "efusewriter/inc/EFuseWriter.h"
#include "efusewriter/inc/EFuseWriterParameter.h"
#include "efusewriter/inc/mdt_efusewriter_cefusewriterconfigfile.h"
#include "efusewriter/inc/mdt_efusewriter_cefusewriterlockfile.h"
#include "efusewriter/inc/cmdtefusewriterhandle.h"
#include "efusewriter/inc/cmdtefusereaderhandle.h"


#ifndef _TIME_UTILS_H_
#include "time_utils.h"
#endif

#define LOGIN_PASSWORD_MAX 64

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	 //
        TLabel *COM1Percentage;
        TLabel *COM2Percentage;
        TLabel *COM3Percentage;
        TLabel *COM4Percentage;
        TLabel *COM5Percentage;
        TLabel *COM6Percentage;
        TLabel *COM7Percentage;
        TLabel *COM8Percentage;
        TLabel *COM9Percentage;
        TLabel *COM10Percentage;
        TLabel *COM11Percentage;
        TLabel *COM12Percentage;
        TLabel *COM13Percentage;
        TLabel *COM14Percentage;
        TLabel *COM15Percentage;
        TLabel *COM16Percentage;

        TLabel *lblCOM1Time;
        TLabel *lblCOM2Time;
        TLabel *lblCOM3Time;
        TLabel *lblCOM4Time;
        TLabel *lblCOM5Time;
        TLabel *lblCOM6Time;
        TLabel *lblCOM7Time;
        TLabel *lblCOM8Time;
        TLabel *lblCOM9Time;
        TLabel *lblCOM10Time;
        TLabel *lblCOM11Time;
        TLabel *lblCOM12Time;
        TLabel *lblCOM13Time;
        TLabel *lblCOM14Time;
        TLabel *lblCOM15Time;
        TLabel *lblCOM16Time;

        TCheckBox *cbAutoPolling1;
        TCheckBox *cbAutoPolling2;
        TCheckBox *cbAutoPolling3;
        TCheckBox *cbAutoPolling4;
        TCheckBox *cbAutoPolling5;
        TCheckBox *cbAutoPolling6;
        TCheckBox *cbAutoPolling7;
        TCheckBox *cbAutoPolling8;
        TCheckBox *cbAutoPolling9;
        TCheckBox *cbAutoPolling10;
        TCheckBox *cbAutoPolling11;
        TCheckBox *cbAutoPolling12;
        TCheckBox *cbAutoPolling13;
        TCheckBox *cbAutoPolling14;
        TCheckBox *cbAutoPolling15;
        TCheckBox *cbAutoPolling16;
        TCheckBox *cbSelAllAutoPolling;
	 //
        TCheckBox *cbCOM1;
        TCheckBox *cbCOM2;
        TCheckBox *cbCOM3;
        TCheckBox *cbCOM4;
        TCheckBox *cbCOM5;
        TCheckBox *cbCOM6;
        TCheckBox *cbCOM7;
        TCheckBox *cbCOM8;
	 	TCheckBox *cbCOM9;
        TCheckBox *cbCOM10;
        TCheckBox *cbCOM11;
        TCheckBox *cbCOM12;
        TCheckBox *cbCOM13;
        TCheckBox *cbCOM14;
        TCheckBox *cbCOM15;
        TCheckBox *cbCOM16;
        TCheckBox *cbSelAllCOM;

	 //progress bar
        TCGauge *pbCOM1;
        TCGauge *pbCOM2;
        TCGauge *pbCOM3;
        TCGauge *pbCOM4;
        TCGauge *pbCOM5;
        TCGauge *pbCOM6;
        TCGauge *pbCOM7;
        TCGauge *pbCOM8;
        TCGauge *pbCOM9;
        TCGauge *pbCOM10;
        TCGauge *pbCOM11;
        TCGauge *pbCOM12;
        TCGauge *pbCOM13;
        TCGauge *pbCOM14;
        TCGauge *pbCOM15;
        TCGauge *pbCOM16;

        TShape *shpCOM1;
        TShape *shpCOM2;
        TShape *shpCOM3;
	 	TShape *shpCOM4;
        TShape *shpCOM5;
        TShape *shpCOM6;
        TShape *shpCOM7;
        TShape *shpCOM8;
        TShape *shpCOM9;
        TShape *shpCOM10;
        TShape *shpCOM11;
        TShape *shpCOM12;
        TShape *shpCOM13;
        TShape *shpCOM14;
        TShape *shpCOM15;
        TShape *shpCOM16;

        TButton *btnCOM1Start;
        TButton *btnCOM2Start;
        TButton *btnCOM3Start;
        TButton *btnCOM4Start;
        TButton *btnCOM5Start;
        TButton *btnCOM6Start;
        TButton *btnCOM7Start;
        TButton *btnCOM8Start;
        TButton *btnCOM9Start;
        TButton *btnCOM10Start;
        TButton *btnCOM11Start;
        TButton *btnCOM12Start;
        TButton *btnCOM13Start;
        TButton *btnCOM14Start;
        TButton *btnCOM15Start;
        TButton *btnCOM16Start;
        TButton *btnStartAll;

        TButton *btnCOM1Stop;
        TButton *btnCOM2Stop;
        TButton *btnCOM3Stop;
        TButton *btnCOM4Stop;
        TButton *btnCOM5Stop;
        TButton *btnCOM6Stop;
        TButton *btnCOM7Stop;
        TButton *btnCOM8Stop;
        TButton *btnCOM9Stop;
        TButton *btnCOM10Stop;
        TButton *btnCOM11Stop;
        TButton *btnCOM12Stop;
        TButton *btnCOM13Stop;
        TButton *btnCOM14Stop;
        TButton *btnCOM15Stop;
        TButton *btnCOM16Stop;
        TButton *btnStopAll;

        TTimer *TimerCOM1;


        TMainMenu *MainMenu1;
        TMenuItem *miFile; //file menu
        TMenuItem *miOpenAuthFile;
	 	TMenuItem *OpenDownloadAgentFile1;
        TMenuItem *OpenMemoryVerificationListFile1;
        TMenuItem *Show_scatter_and_load; //Show sactter files and loads

        TMenuItem *miFactoryDatabase;
        TMenuItem *miSetupDataSrc;
        TMenuItem *miEnableFDLog;

        TMenuItem *miOption;
        TMenuItem *miExternalclock;
        TMenuItem *miAutodetectExtClock;
        TMenuItem *mi13MHz;
        TMenuItem *mi26MHz;
        TMenuItem *mi39MHz;
        TMenuItem *mi52MHz;

        TMenuItem *miBasebandchipoption;
        TMenuItem *miCheckECOversion;
        TMenuItem *miEnableNFICS1;
        TMenuItem *miBBChipVersionCheck;

        TMenuItem *m_miBackupCalDataOption;
        TMenuItem *m_miDnWithBkAndRsCalData;
        TMenuItem *m_miDnAndRsCalDataOnly;
        TMenuItem *m_miDnWithoutBkAndRsCalData;
        TMenuItem *m_miRsCalDataOnly;
        TMenuItem *m_miDnAndUlUserData;

        TMenuItem *miEnableMMAA1;
        TMenuItem *miUSBDLWithTwoSteps;

        TMenuItem *miDebuglog;
        TMenuItem *miBromDllLog;
        TMenuItem *miMETADllLog;
        TMenuItem *miMDTLog;
        TMenuItem *miClearMDTLog;
        TMenuItem *miClearBromDllLog;
        TMenuItem *miClearMETADllLog;

        TMenuItem *Help1;
        TMenuItem *miAbout;


        TLabel *Label1; //DA file name
        TLabel *Label2;

        TOpenDialog *dlgOpenDA;
        TDataSource *DataSrc;
        TADOTable *ADOTab;
        TADOConnection *ADOConn;
        TOpenDialog *dlgOpenDataSrc;

        TStaticText *m_stBkStatus0;
        TStaticText *m_stBkStatus1;
        TStaticText *m_stBkStatus2;
        TStaticText *m_stBkStatus3;
        TStaticText *m_stBkStatus4;
        TStaticText *m_stBkStatus5;
        TStaticText *m_stBkStatus6;
        TStaticText *m_stBkStatus7;
        TStaticText *m_stBkStatus8;
        TStaticText *m_stBkStatus9;
        TStaticText *m_stBkStatus10;
        TStaticText *m_stBkStatus11;
        TStaticText *m_stBkStatus12;
        TStaticText *m_stBkStatus13;
        TStaticText *m_stBkStatus14;
        TStaticText *m_stBkStatus15;

        TOpenDialog *dlgOpenAuthFile;
        TEdit *stDAFileName;
        TEdit *stAuthFile;
        TMenuItem *SetbeginCOMport1;
        TGroupBox *GroupBox3;
        TButton *ScatterFileButton1;
        TButton *btnReloadScatterFile;
        TEdit *stScatterFile;
        TButton *ScatterFileButton2;
        TButton *ScatterFileButton3;
        TButton *SctterFileButton4;
        TButton *btDeleteScatterFile2;
        TButton *btDeleteScatterFile3;
        TButton *btDeleteScatterFile4;
        TMenuItem *ClearAllLogs;
        TMenuItem *debug_logging_separater;
        TMenuItem *N1;
        TMenuItem *miEnterMetaModeafterDLFMT1;
        TMenuItem *miToolSetting;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *OpenDeviceManager1;
        TPageControl *ActionPage;
        TTabSheet *DownloadAction;
        TLabel *Label4;
        TComboBox *cbType;
        TGroupBox *gbFormatFATRange;
        TRadioButton *rbAuto;
        TRadioButton *rbManual;
        TRadioButton *rbResetToFactory;
        TGroupBox *GroupBox1;
        TRadioButton *rbNAND;
        TRadioButton *rbNOR;
        TTabSheet *eFuse;
        TGroupBox *eFuseOperation;
        TOpenDialog *eFuseSettingFile;
        TOpenDialog *eFuseLockFile;
        TActionList *ActionList1;
        TAction *EnableDisableeFuseWtitter;
        TStatusBar *sbMPDT;
        TGroupBox *m_Gb_ComPortType;
        TRadioButton *m_rbUART;
        TRadioButton *m_rbUSB;
        TRadioButton *m_rbUART_USB;
        TLabel *m_lblBaudRate;
        TComboBox *cbBaudrate;
        TButton *btnSelectEFuseSettingFile;
        TButton *btnSelectEFuseLockFile;
        TButton *btnEFuseParameterView;
        TOpenDialog *eFuseSettingDialog;
        TOpenDialog *eFuseLockDialog;
        TCheckBox *EFuseWriteCheckBox;
        TCheckBox *EFuseLockCheckBox;
        TMenuItem *ShowFactoryDatabaseFile;
        TCheckBox *EFuseReadCheckBox;
        TMenuItem *USBDownloadWOBattery;
        TMenuItem *m_miUploadUserDataOnly;
        TOpenDialog *BootCert_File_OpenDialog;
        TGroupBox *BootCertOptions;
        TButton *Btn_Select_RootCert_File;
        TMenuItem *USBMetaModeAfterOneStationDownload1;
        TLabel *Label3;
        TLabel *Label5;
        TEdit *RootCert_File_DisplayEdit;
        TEdit *Certificate_File_DisplayEdit;
        TMenuItem *OpenRootCertFile;
        TMenuItem *OpenCertificateFile;
        TSaveDialog *SaveDialog1;
        TOpenDialog *RootCertFileOpenDialog;
        TOpenDialog *CertificateFileOpenDialog;
        TMenuItem *SendRootCertForcely;
        TMenuItem *EnableUSB11to20;
        TMenuItem *mi_USBDownloadReadbackDualTalk;
        TMenuItem *mi_USBDownloadReadbackDataCard;
        TMenuItem *EnableBackupNvramPartion;
        TMenuItem *m_miCheckSDS;
        TMenuItem *FlashSafeMode;
        TMenuItem *Identify1;
        TMenuItem *Engineer1;
        TMenuItem *Operator1;
        TMenuItem *SwitchToOperator1;
        TMenuItem *ChangePassword1;
        TMenuItem *SwitchToEngineer1;

       // void __fastcall lvClick(TObject *Sender);
       // void __fastcall lvChanging(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange);
       // void __fastcall lvChange(TObject *Sender, TListItem *Item, TItemChange Change);
      //  void __fastcall lv_oldClick(TObject *Sender);

        void __fastcall mOpenDAFileClick(TObject *Sender);

        void __fastcall OpenDownloadAgentFile1Click(TObject *Sender);
        void __fastcall btnStartAllClick(TObject *Sender);
        void __fastcall btnStopAllClick(TObject *Sender);
        void __fastcall btnSeperateDownloadClick(TObject *Sender);
        void __fastcall btnSeperateStopClick(TObject *Sender);
        bool __fastcall CheckRomNumber(void);
		void __fastcall TimerCOMTimer(TObject *Sender);

        void __fastcall miAutodetectBBClick(TObject *Sender);
        void __fastcall mi13MHzClick(TObject *Sender);
        void __fastcall mi26MHzClick(TObject *Sender);
        void __fastcall mi39MHzClick(TObject *Sender);
        void __fastcall mi52MHzClick(TObject *Sender);
        void __fastcall cbAutoPollingClick(TObject *Sender);
        void __fastcall miCheckECOversionClick(TObject *Sender);
        void __fastcall cbCOMClick(TObject *Sender);
        void __fastcall miAboutClick(TObject *Sender);
        void __fastcall cbTypeChange(TObject *Sender);
        void __fastcall cbBaudrateChange(TObject *Sender);
        void __fastcall miSetupDataSrcClick(TObject *Sender);
        void __fastcall miEnableFDLogClick(TObject *Sender);
        void __fastcall miBromDllLogClick(TObject *Sender);
        void __fastcall miMETADllLogClick(TObject *Sender);
        void __fastcall rbNFBClick(TObject *Sender);
        void __fastcall rbNORClick(TObject *Sender);
        void __fastcall miClearBromDllLogClick(TObject *Sender);
        void __fastcall miClearMETADllLogClick(TObject *Sender);
        void __fastcall miOpenAuthFileClick(TObject *Sender);
        void __fastcall miEnableNFICS1Click(TObject *Sender);
        void __fastcall OpenMemoryVerificationListFile1Click( TObject *Sender);
        void __fastcall m_miDnWithBkAndRsCalDataClick(TObject *Sender);
        void __fastcall m_miDnAndRsCalDataOnlyClick(TObject *Sender);
        void __fastcall m_miDnWithoutBkAndRsCalDataClick(TObject *Sender);
        void __fastcall m_miRsCalDataOnlyClick(TObject *Sender);
        void __fastcall m_miDnAndUlUserDataClick(TObject *Sender);
        void __fastcall cbSelAllCOMClick(TObject *Sender);
        void __fastcall cbSelAllAutoPollingClick(TObject *Sender);
        void __fastcall m_rbUARTClick(TObject *Sender);
        void __fastcall m_rbUSBClick(TObject *Sender);
        void __fastcall m_rbUART_USB_Click(TObject *Sender);

        void __fastcall ScatterFileButtonClick(TObject *Sender);
        void __fastcall btnReloadScatterFileClick(TObject *Sender);
        void __fastcall miAutodetectExtClockClick(TObject *Sender);
        void __fastcall SetbeginCOMport1Click(TObject *Sender);
        void __fastcall miMDTLogClick(TObject *Sender);
        void __fastcall miClearMDTLogClick(TObject *Sender);
        void __fastcall miEnableMMAA1Click(TObject *Sender);
        void __fastcall rbManualClick(TObject *Sender);
        void __fastcall rbNANDClick(TObject *Sender);
        void __fastcall Show_scatter_and_loadClick(TObject *Sender);
        void __fastcall miBBChipVersionCheckClick(TObject *Sender);
        void __fastcall miUSBDLWithTwoStepsClick(TObject *Sender);


        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall rbNANDMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall rbNORMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall ClearAllLogsClick(TObject *Sender);
        void __fastcall miEnterMetaModeafterDLFMT1Click(TObject *Sender);
        void __fastcall miToolSettingClick(TObject *Sender);
        void __fastcall OpenDeviceManager1Click(TObject *Sender);
        void __fastcall m_stBkStatusDbClick(TObject *Sender);
        void __fastcall EnableDisableeFuseWriter(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall btnSelectEFuseSettingFileClick(TObject *Sender);
        void __fastcall btnSelectEFuseLockFileClick(TObject *Sender);
        void __fastcall btnEFuseSettingClearClick(TObject *Sender);
        void __fastcall btnEFuseParameterViewClick(TObject *Sender);
        void __fastcall EFuseWriteCheckBoxClick(TObject *Sender);
        void __fastcall EFuseLockCheckBoxClick(TObject *Sender);
        void __fastcall ShowFactoryDatabaseFileClick(TObject *Sender);
        void __fastcall EFuseReadCheckBoxClick(TObject *Sender);
        void __fastcall USBDownloadWOBatteryClick(TObject *Sender);
        void __fastcall m_miUploadUserDataOnlyClick(TObject *Sender);
        void __fastcall Btn_Select_RootCert_FileClick(TObject *Sender);
        void __fastcall mi_USBDownloadReadbackDataCardClick(
          TObject *Sender);
        void __fastcall USBMetaModeAfterOneStationDownload1Click(
          TObject *Sender);
        void __fastcall OpenRootCertFileClick(TObject *Sender);
        void __fastcall OpenCertificateFileClick(TObject *Sender);
        void __fastcall SendRootCertForcelyClick(TObject *Sender);
        void __fastcall EnableUSB11to20Click(TObject *Sender);
        void __fastcall mi_USBDownloadReadbackDualTalkClick(
          TObject *Sender);
        void __fastcall EnableBackupNvramPartionClick(TObject *Sender);
        void __fastcall m_miCheckSDSClick(TObject *Sender);
        void __fastcall FlashSafeModeClick(TObject *Sender);
        void __fastcall SwitchToOperator1Click(TObject *Sender);
        void __fastcall ChangePassword1Click(TObject *Sender);
        void __fastcall SwitchToEngineer1Click(TObject *Sender);


private:	// User declarations
	// common
	// int i_FlashToolFunction;

	// AnsiString m_asROM_Path;
	AnsiString m_asDAPath;
	// AnsiString m_asScat_Path;
	// AnsiString m_asFAT_Path;
	AnsiString m_asAutoPollEn;
	AnsiString m_asBBChip;
	AnsiString m_asExtClock;
	AnsiString m_asCheckECOVer;
	AnsiString m_asBaudrate;
	AnsiString m_asType;
	AnsiString m_asFormat_FAT_range;
	//        AnsiString m_asPullDownGPIO17;
	//        bool  isFATFileLoaded;
	bool bCheckECOVersion;
	AnsiString m_asDAFileName;
	//        AnsiString asScatFileName;
	//        AnsiString m_asBLFileName;
	//        AnsiString m_asROMFileName;
	//        AnsiString m_asFATFileName;
	int iCOMChecked;
	int iAutoPolling;


	TShape *shpCOMArray[MAX_SUPPORT_PORT_NUM];

	// multibin
	// bool m_bCheckTgtResLayout;
	// bool m_bAutoLoadResByScat;
	// bool m_bCompareResProjectId;

	//    ROM_INFO   rom_info[MAX_LOAD_SECTIONS];
	//    S_LV_CHANGED lvChanged;
	//   AnsiString as_LVItem[MAX_LOAD_SECTIONS];
	//    int i_LV_FAT_index;


	// parameter to TBOOT1


	// factory default
	bool m_bStartMetaApp[MAX_SUPPORT_PORT_NUM];
	int  m_iMETA_handle_array[MAX_SUPPORT_PORT_NUM];


	// NFB
	//NFB_PARAM_S  m_sNfbParam;

	// access
	int PassFail[MAX_SUPPORT_PORT_NUM];
	AnsiString  FailReason[MAX_SUPPORT_PORT_NUM];
	unsigned int m_uiTotalFileSize;
	sDownloadTime  dn_time[MAX_SUPPORT_PORT_NUM];
	float throughput[MAX_SUPPORT_PORT_NUM];
	AnsiString as_DataSource;
	#if 0
	CDNFLRS  DnFlrs_Obj;
	#endif

	// timer
	TTimer * TimerCOMArray[MAX_SUPPORT_PORT_NUM];
	TLabel *lblTimeArray[MAX_SUPPORT_PORT_NUM];

	// UI

	void Display_Cable(void);


public:		// User declarations
    COM_PORT_SETTING m_sComPortSetting;
	S_DN_PARAM_T  m_sDnParam;

	CINIFileHandle INIFileH;
	AnsiString   m_usbdeviceid;
	//add mtk71518 2013-07-17  for DualTalk
	AnsiString   m_preloaderdeviceid;
	int          m_iDelayTimeSec;
	E_Login_Identify m_LoginIdentify;
	AnsiString   m_asPasswdFilePath;

	AnsiString   m_CalibrationFolderNamingRule;
	bool           m_delete_CalibrationAfterRS;
	bool m_bEnableUSB1_1To2_0 ;//huifen;
	//bool m_bEnableBackupNvramPartition ;//wuxiong
	int m_bEnableBackupNvramPartition;//mingxue 0/1/2
	bool m_bEnableFlashSafeMode;//mingxue

	TCheckBox *cbCOMArray[MAX_SUPPORT_PORT_NUM];
	TCheckBox *cbAutoPollingArray[MAX_SUPPORT_PORT_NUM];
	TLabel    *COMPercentageArray[MAX_SUPPORT_PORT_NUM];
	TCGauge* pbCOMArray[MAX_SUPPORT_PORT_NUM];
	TThread *A_Thread[MAX_SUPPORT_PORT_NUM];
	int DownLoadTimeSec[MAX_SUPPORT_PORT_NUM];
	TButton *btnCOMStartArray[MAX_SUPPORT_PORT_NUM];
	TButton *btnCOMStopArray[MAX_SUPPORT_PORT_NUM];
	TStaticText *m_stBkStatus[MAX_SUPPORT_PORT_NUM];

	int DownloadStatus[MAX_SUPPORT_PORT_NUM];
	unsigned int g_DownloadRetry;


	ScatterFileManager* m_p_scatter_manager;
	ConfigFileManager* m_p_Config_Manager;
	CLinkMapFile* m_p_LinkMapFileManager;


	void Enable_NOR_NAND_slelect_rb();
	void Disable_NOR_NAND_slelect_rb();

	void Display_OptFlashType( void );
	void Save_OptFlashType( void );

	// menu
	void __fastcall UpdateNandEraseOptionUi(TObject *Sender);

	__fastcall TMainForm(TComponent* Owner);

	bool FileOpenDownloadAgentExecute();
	bool OpenReadDAFile(AnsiString asFileName);
	void Read_FormatFATBeginAddress( void );
	void Read_FormatFATLength(void);
	void Display_Scatter( void );
	void Save_Scatter( void );
	//------------------------------------------------------------
	void Read_NANDFormatFATBeginAddress( void );
	void Read_NANDFormatFATLength( void );
	void Read_EraseValidation( void );
	int  UpdateDAInfo( void );
	void __fastcall btnCOMDownloadClick( int index );

	void Display_BBChipVerChecked( void );
	void Save_BBChipVerChecked( void );

	//------------------------------------------------------------
	E_OPERATION_T Get_Operation(void);
	void Display_Operation( void );
	void Save_Operation( void );
	//------------------------------------------------------------

	BBCHIP_TYPE Get_BBChipType( AnsiString as_BBChip );
	BBCHIP_TYPE Get_BBChipType( void );
	void Display_BasebandChip( void );
	void Save_BasebandChip( void );
	//-------------------------------------------------------------
	EXT_CLOCK Get_ExternalClockType( AnsiString as_ExtClock );
	EXT_CLOCK Get_ExternalClockType( void );
	void Display_ExternalClock( void );
	void Save_ExternalClock( void );
	//-------------------------------------------------------------
	void Get_BBChipOption(S_BBCHIP_OPTION_T& bbchip_op);
	//void Display_CheckECOVersion( void );
	//void Save_CheckECOVersion( void );
	void Display_CheckEnableNFI( void );
	void Save_CheckEnableNFI( void );
	//-------------------------------------------------------------
	S_MULTIBIN_OPTION Get_MultiBinOption( void );
	//-------------------------------------------------------------
	void Display_BROMDllLog( void );
	void Save_BROMDllLog( void );
	//-------------------------------------------------------------
	void Display_METADllLog( void );
	void Save_METADllLog( void );
	//-------------------------------------------------------------
	UART_BAUDRATE Get_Baudrate( AnsiString as_baudrate );
	UART_BAUDRATE Get_Baudrate( void );
	void Display_Baudrate( void );
	void Save_Baudrate( void );
	//-------------------------------------------------------------
	void Display_ComEnabled( void );
	void Save_ComEnabled( void );
	//-------------------------------------------------------------
	void Display_AutoPollingEnabled( void );
	void Save_AutoPollingEnabled( void );

	void Display_Read_USB_DL_WITH_TWO_SITE( void );
	void Save_Read_USB_DL_WITH_TWO_SITE( void );

	void Display_EnterMetaModeAfterDLFMT( void );
	void Save_EnterMetaModeAfterDLFMT( void );

	void Read_Disconnect_Comport_option( void );

	//-------------------------------------------------------------
	//        void ReadFileSetting( void );
	//        void WriteFileSetting( void );
	//-------------------------------------------------------------
	void Display_DAFile( void );
	void Save_DAFile( void );
	//-------------------------------------------------------------
	void Display_AuthFile( void );
	void Save_AuthFile( void );
	//-------------------------------------------------------------
	void Display_RootCertFile( void );
	void Save_RootCertFile( void );
	//-------------------------------------------------------------
	void Display_CertificateFile( void );
	void Save_CertificateFile( void );
	//-------------------------------------------------------------

	void Display_Type( void );
	void Save_Type(void);
	//-------------------------------------------------------------
	E_FORMAT_OPTION Get_FormatOption(void);
	void Display_FormatFatRangeVisible(void);
	void Display_FormatFatRange(void);
	void Save_FormatFatRange(void);
	//-------------------------------------------------------------
	void Display_BackupAndRestoreOption(void);
	void Display_EnableUSB_2_0( void );
	void Save_EnableUSB_2_0( void );

    void Display_EnableBackupNvramPartion( void );
    void Save_EnableBackupNvramPartion( void );
	//void Save_BackupAndRestoreOption(void);
	//-------------------------------------------------------------
	// EMI
	void Read_EMI_Setting(void);

	void Read_usb_device_id( void );
	void Save_usb_device_id( void );
	void Read_SwitchToModem_DelayTime(void);
	void Save_SwitchToModem_DelayTime(void);
	void Read_PasswordFilePath(void);
	void Get_LoginIdentify(void);

	// void Display_LVSetting( void );
	// void Save_LVSetting( void );
	// void Enable_lvListView( void );
	// void Disable_lvListView( void );
	//-------------------------------------------------------------

	//void get_PullDownGPIO17( void );
	//-------------------------------------------------------------
    void Disable_EngineerOption( void );
	void Enable_EngineerOption(void);
	void Disable_UIComponent( void );
	void Enable_UIComponent( void );
	void Disable_FileMenu( void );
	void Enable_FileMenu( void );
	void Disable_FactoryDatabaseMenu( void );
	void Enable_FactoryDatabaseMenu( void );
	void Disable_OptionMenu( void );
	void Enable_OptionMenu( void );
	void Disable_DebugLoggingMenu( void );
	void Enable_DebugLoggingMenu( void );

	void Disable_SetAndDelScatterFile( void );
	void Enable_SetAndDelScatterFile( void );
	void Disable_BasebandChipRadioButton( void );
	void Enable_BasebandChipRadioButton( void );
	void Disable_FormatFatRangeRadioButton( void );
	void Enable_FormatFatRangeRadioButton( void );
	void Disable_TypeComboBox( void );
	void Enable_TypeComboBox( void );
	void Disable_BaudrateComboBox( void );
	void Enable_BaudrateComboBox( void );
	void Disable_AllDownloadButton( void );
	void Enable_AllDownloadButton( void );
	void Disable_ExternalClockRadioButton( void );
	void Enable_ExternalClockRadioButton( void );
	void Disable_SeperateDownloadButton( void );
	void Enable_SeperateDownloadButton( void );
	void Disable_SpecificMsUI(int index);
	void Enable_SpecificMsUI(int index);
	void Start_Timer(int index);
	void Stop_Timer(int index);
	//-------------------------------------------------------------
	//void UpdateMenuItem( void );
	// data format transform


	// get, set MainForm member
	//bool Get_miMT6218BChecked( void );
	bool Set_COMPercentageCaption( int index, AnsiString as_str );
	bool Set_shpCOMColor( int index, TColor color );
	void SetPbComProgress( int index, unsigned char progress_percentage );
	void SetPbComForeColor(int index, TColor color);
	void SetPbComBackColor(int index, TColor color);
	//------------------------------------------------------------
	void Set_StartMetaAppFlag(unsigned char index, bool flag);
	//------------------------------------------------------------
	// download, format
	E_FLASHTOOL_FUNCTION Get_Function( void );
	void Set_DownloadParameter( unsigned char	index );
	bool DownloadCommonFunction( void );

	// multi-bin

	//void __fastcall RedrawLVCheckBox( void );
	//void __fastcall RedrawLVList( void );
	//int  getIndexFromListView( TListView *p_lv);

	// stop
	void btnCOMStopClick( int i );

	// Global information
	bool Get_CheckTgtResLayout( void );
	bool Get_AutoLoadResByScat( void );
	bool Get_CompareResProjectId( void );
	int  Get_FlashToolFunction( void );
	int  Get_Format_FAT_begin_address( void );
	int  Get_Format_FAT_length( void );
	bool user_select_image_folder(/*out*/string &folder_path);
	bool SearchAllLinkMapFile(/*out*/string &folder_path);

	void LoadAllLinkMapFile(string &folder_path);

	// database
	// access
	//---------------------------------------------------------------
	// UI
	void Display_DataSource(void);
	void Save_DataSource(void);

	void Display_DBLogOption(void);
	void Save_DBLogOption(void);

	void Save_EnableMMAA( void );
	void Display_EnableMMAA( void );

	//void miAllBBChipUnChecked(void);

	// ADO connection
	void Set_ADOConnLoginPromptOff( void );
	bool Set_ADOConnString( AnsiString as_Data_Src );
	bool Check_ADOConnConnected( void );

	void InsertNewRecordToAccess( void );
	void ActivateADOTab( void );
	void DeActivateADOTab( void );
	void PostRecordToAccess( void );
	void SetTabNameToMultiport_download( void );
	void AddStationToAccess( void );
	void AddPcToAccess( void );
	void AddToolTypeToAccess( void );
	void AddDateToAccess( int index );
	void AddTimeToAccess( int index );
	void AddPassFailToAccess(int pass_fail );
	void AddFileSizeToAccess( void );
	void AddDownloadTimeToAccess( int index );
	void AddThrougphputToAccess( int index );
	void AddFailStepToAccess( int fail_step );
	void AddFailReasonToAccess( int fail_reason_code );
	bool AddDnResultToAccess( int index );
	//----------------------------------------------------------------
	// test result
	bool SetPassFail( int index, int pass_fail);
	int GetPassFail( int index );
	bool SetFailReason( int index, int fail_reason);
	AnsiString  GetFailReason( int index );
	AnsiString  Get_FlrsString( int fail_reason );
	// time handling
	bool SetDnDate( int index, TDateTime date );
	TDateTime GetDnDate( int index );
	bool SetDnStartTime( int index, TDateTime time );
	TDateTime GetDnStartTime( int index );
	bool SetDnStartsTime( int index, sTime time );
	sTime GetDnStartsTime( int index );
	bool SetDnEndTime( int index, TDateTime time );
	TDateTime GetDnEndTime( int index );
	bool SetDnEndsTime( int index, sTime time );
	sTime GetDnEndsTime( int index );
	bool SetDnTime( int index );
	unsigned GetDnTime( int index );
	// throughput
	bool SetThroughput( int index );
	float GetThroughput( int index );
	bool Get_EnableFactoryDatabaseLog( void );

	// META_DLL
	void InitMETADll(void);
	void DeInitMETADll(void);

	//-------------------------------------------------------------
	/////////////// backup and restore calibration data ///////////
	//-------------------------------------------------------------
	// UI
	void UnCheckBackupAndRestoreMenuItem(void);

	// export information
	S_DN_PARAM_T* Get_DNParameter(void);
	unsigned int Get_TotalFileSize(void);
	void Set_TotalFileSize(unsigned int total_file_size);
	DL_HANDLE_T* Get_DlHandle(int idx);
	void Set_DlHandle(int idx, DL_HANDLE_T* p_dl_handle);
	DL_HANDLE_LIST_T* Get_DlHandleList(void);
	//bool Get_CheckTgtResLayoutFlag(void);
	//bool Get_AutoLoadResByScatFlag(void);
	//bool Get_CompareResProjectIdFlag(void);
	int  Get_Type(void);
	void Clear_BackupRestoreStatus(unsigned char idx);
	void Display_BackupRestoreStatus(unsigned char idx, unsigned char total_num, unsigned char current_num);

	void Disable_ComPortRadioButton(void);
	void Enable_ComPortRadioButton(void);

	void Save_BkAndRsOptional(void);
	void Display_BkAndRsOptional( void );

	void __fastcall update_UI_components_for_USB_mode();
	void Save_Cable(void);
	void Display_MDTLog( void );
	void Save_MDTLog( void );
	void  __fastcall Update_ComPortNumber(void);
	void __fastcall  Update_FormatFatAddressLength(void);
	void __fastcall Read_CalibrationFolder_option(void);
	void _fastcall SubClassWndProc(Messages::TMessage &Message);

public:
  bool __fastcall response_usb_message(void);
  E_CheckUSBResult __fastcall query_current_comport(IN int begin_comport,
                                                                    INOUT int *current_comport);
  void __fastcall record_current_comport(IN int * current_comport);
  int __fastcall get_current_comport_increase(IN int *current_comport,
                                                           INOUT int * current_increase_comport);
  int __fastcall get_current_comport_decrease(IN int *current_comport,
                                                                       INOUT int * current_decrease_comport);

  //For one station usb download
  bool _fastcall IsUSBDownloadWithTwoSite();

  int LoadFile(const char *pathname, unsigned char **pp_buf, unsigned int *p_nFileLength, long *p_last_modify_time);
  int LoadFileInfo(const char *pathname, unsigned int *p_nFileLength, long *p_last_modify_time);


protected:
  //Write and Lock
  CEFuseWriterConfigFile* p_efuse_write_file_reader;
  CEFuseWriterLockFile* p_efuse_lock_file_reader;
  CMDT_Efuse_Writer_Handle efuse_writer_handle;
  //Read efuse setting
  //map<int ,MDT_Efuse_Arg_All> m_m_mdt_efuse_parameter_reader;
  CMDT_Efuse_Reader_Handle_List m_efuse_read_handle_list;

public:
  BootCert_T m_boot_Cert;

private:
  void *USBCardDownloadHandle;
   STARTUPINFOA dtStartupInfo; //for dual talk download
   PROCESS_INFORMATION dtProcessInfo; //for dual talk download  //huifen

private: // User declarations
  void __fastcall OnDeviceChange(Messages::TMessage &Message);
  void __fastcall CheckUIEFuseSetting();

  //


  BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(WM_DEVICECHANGE, TMessage, OnDeviceChange) ;
  END_MESSAGE_MAP(TForm)

};

typedef enum {
    DISABLE_DL_WO_BATT = 0,
    ENABLE_AUTO_RETRY,
    ENABLE_NO_RETRY
} DL_WO_BATT_OPTION_E;

class file_open_sentry
{

    public:
	    file_open_sentry ( const char *filepath, const char *mode, FILE *&fp, bool bIsDebugOn=false)
        :m_fp(fp),
         m_bIsDebugOn(bIsDebugOn)
        {
            m_fp = NULL;

		    if ( NULL==filepath || '\0'==filepath[0] || NULL==mode || '\0'==mode[0] ) return;

		    if ( NULL == ( m_fp = fopen(filepath, mode) ) ) {}
		    else {
			    if(m_bIsDebugOn) {}
		    }
    	}

    	~file_open_sentry()
        {
		    if( NULL != m_fp )
            {
			    fclose( m_fp );
			    if( m_bIsDebugOn ) { }
			    m_fp = NULL;
		    }
	    }

    private:
	    FILE	*&m_fp;
	    bool	m_bIsDebugOn;
};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
extern bool UpdateDownloadProgress[MAX_SUPPORT_PORT_NUM];
//extern HANDLE One_Station_Download_USB_Insert_Event;
//---------------------------------------------------------------------------
#endif
