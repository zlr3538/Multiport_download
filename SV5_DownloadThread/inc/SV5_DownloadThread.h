#ifndef _SV5_DOWNLOADTHREAD_H___
#define _SV5_DOWNLOADTHREAD_H___

#include "MDT_Component/thread/inc/FlashDownLoad.h"
#include "MDT_Component/error_handler/inc/GCTrace.h"

class SV5_Thread:public TBOOT1
{
public:
	__fastcall SV5_Thread(bool CreateSuspended, HANDLE hMsgHandle, COM_PORT_SETTING com_port_setting, S_DN_PARAM_T dn_param);

protected:
	virtual void __fastcall printProcessInfo();
	//virtual int __fastcall uart_download_bootloader();
	
	virtual void __fastcall DisableROM(DL_HANDLE_LIST_T &dl_handle_list);
	virtual void __fastcall DisableROM(DL_HANDLE_T &dl_handle);

	virtual int __fastcall DisableBootloader(DL_HANDLE_T &dl_handle);

	virtual E_ResultAndAction _fastcall Format();
		

};
extern int __stdcall cb_format_report(unsigned char percent, void *usr_arg);
extern int __stdcall cb_format_report(unsigned char percent, void *usr_arg);
extern int __stdcall cb_format_statistics(const FormatStatisticsReport_T  *p_report, void *usr_arg);
extern int __stdcall cb_format_report_init(HW_StorageType_E storage_type, unsigned int begin_addr, unsigned int length, void *usr_arg);
#endif
