#include "SV5_DownloadThread/inc/SV5_DownloadThread.h"
#include "MultiPortFlashDownloadTool.h"

__fastcall SV5_Thread::SV5_Thread(bool CreateSuspended, HANDLE hMsgHandle, COM_PORT_SETTING com_port_setting, S_DN_PARAM_T dn_param)
:TBOOT1(CreateSuspended,hMsgHandle,com_port_setting,dn_param)
{
	
}
//---------------------------------------------------------------------------
int __fastcall SV5_Thread::DisableBootloader(DL_HANDLE_T &dl_handle)
{
  unsigned short romNum=0;
  int ret;
  DL_INFO_EX dl_info = {};
  DL_GetInfo_Ex(dl_handle, &dl_info);

  if( (S_DONE ==(ret= DL_GetCount_Ex(dl_handle, &romNum)) ) && (0 < romNum) )
  {
    for(int i = 0; i < romNum; i++)                
    {
      ROM_INFO_EX romInfo = {};     
      if(S_DONE ==(ret= DL_Rom_GetInfo_Ex(dl_handle, i, &romInfo) ))
      {
  //      if((ARM_BL_ROM == romInfo.rom_type) || (DSP_BL_ROM == romInfo.rom_type)||(EXT_BL_ROM == romInfo.rom_type))
        if(ARM_BL_ROM == romInfo.rom_type)
    	{
    	  if(S_DONE !=(ret=DL_Rom_SetEnableAttr_Ex(dl_handle, i, _FALSE)))
          {
    	    GC_TRACE(" DL_Rom_SetEnableAttr_Ex() failed! ");
    	    throw ret;
          }
          else
          {
            GC_TRACE("SV5_Thread::DisableBootloader: %s",romInfo.name);
          }
        }
		else if(EXT_BL_ROM == romInfo.rom_type &&
                                !dl_info.bootloader_self_update_supported)
        {
          if(S_DONE !=(ret=DL_Rom_SetEnableAttr_Ex(dl_handle, i, _FALSE)))
          {
    	    GC_TRACE(" DL_Rom_SetEnableAttr_Ex() failed! ");
    	    throw ret;
          }
          else
          {
            GC_TRACE("SV5_Thread::DisableBootloader: %s",romInfo.name);
          }
        }
      }      
      else
      {
        GC_TRACE(" DL_Rom_GetInfo_Ex() failed! ");
        throw ret;
      }
    }
  }
  else
  {
    GC_TRACE(" DL_GetCount_Ex() failed! ");
    throw ret;
  }
  return MDT_OK;
}
//---------------------------------------------------------------------------

void __fastcall SV5_Thread::printProcessInfo()
{
	GC_TRACE_EX("==Begin SV5 Download==");
    GC_TRACE("COM Port: %d", m_sComPortSetting.com.number);
    GC_TRACE("Cable Type: %s", (USB_COM == m_sDnParam.e_com_type ? "USB": "UART"));
    GC_TRACE("UART Baud Rate Class: %d [1-921600][2-460800][3-230400][4-115200]", m_sDnParam.e_baud_rate);
    GC_TRACE("Function: %d [0-DL][1-RB][2-FR]", m_sDnParam.e_Function);
    GC_TRACE("Extern Clock: %d [1-13M][2-26M][3-39M][4-52M][254-AUTO][255-Unkonw]", m_sDnParam.e_ext_clock);
    GC_TRACE("BBChip Version Check [%s]", (m_sDnParam.s_bbchip_op.b_check_bbchip_version? "Enable":"Disable"));
    GC_TRACE("BK CAL DATA OP %d [0-DO NOT BK AND RS][1-BK AND RS][2-RS][3-DL USER DATA][4 RS CAL NOLY]", m_sDnParam.e_backup_cal_data_op);
    GC_TRACE("Is USB Two Site USB DL %s", IsUSBDownloadWithTwoSite() ? "yes" : "no");	
}
//---------------------------------------------------------------------------
/*
int __fastcall SV5_Thread::uart_download_bootloader()
{
	int mtk_status;
    int index = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
	FLASHTOOL_DOWNLOAD_ARG	Temp_sFtDlArg;
	
	//backup download parameter
	memcpy(&Temp_sFtDlArg,&m_sFtDlArg,sizeof(FLASHTOOL_DOWNLOAD_ARG));
	
	GC_TRACE("SV5_Thread::uart_download_bootloader==>Start"); 
		
	Temp_sFtDlArg.m_enable_wdt_timeout=_TRUE;
	Temp_sFtDlArg.m_ms_wdt_timeout_interval=WATCH_DOG_TIMEOUT_INTERVAL;
	Temp_sFtDlArg.m_format_enable=_FALSE;
	
	
    if (Temp_sFtDlArg.m_dl_handle != NULL)
    {
        DL_HANDLE_T dl_handle = NULL;
        
        if(S_DONE!=(mtk_status=DL_Clone(&dl_handle, Temp_sFtDlArg.m_dl_handle)))
        {
			GC_TRACE("SV5_Thread::uart_download_bootloader==>DL_Clone Fail,Error ID: 0x%08X",mtk_status); 
			return mtk_status;
		}
        DisableROM(dl_handle);
       
        Temp_sFtDlArg.m_dl_handle = dl_handle;
    }
    else if (Temp_sFtDlArg.m_dl_handle_list != NULL)
    {
        DL_HANDLE_LIST_T dl_handle_list = NULL;
        
        if(S_DONE!=(mtk_status=DL_CloneList(&dl_handle_list, Temp_sFtDlArg.m_dl_handle_list)))
        {
			GC_TRACE("SV5_Thread::uart_download_bootloader==>DL_CloneList Fail,Error ID: 0x%08X",mtk_status); 
			return mtk_status;			
		}
        DisableROM(dl_handle_list);
        
        Temp_sFtDlArg.m_dl_handle_list = dl_handle_list;
    }
    else
    {
        //assert(0);
        return 1;
    }

	
	mtk_status = FlashDownload(&m_sComPortSetting, &m_sFtArg, &m_sFtResult,
		&Temp_sFtDlArg, &m_sFtDnResult, &g_iStopFlag[index]);
	scan_exist_com_port(m_exist_com_port);

	if( S_DONE != mtk_status )
	{
      return mtk_status;
	}

	//Avoid Memory Leak
    if (Temp_sFtDlArg.m_dl_handle != NULL)
    {
        if(S_DONE!=(mtk_status=DL_Destroy(&Temp_sFtDlArg.m_dl_handle)))
        {
			return mtk_status;
		}
    }
    else if (Temp_sFtDlArg.m_dl_handle_list != NULL)
    {
        if(S_DONE!=(mtk_status=DL_DestroyList(&Temp_sFtDlArg.m_dl_handle_list)))
        {
			return mtk_status;
		}
    }


	return S_DONE;
}
*/
//---------------------------------------------------------------------------
void __fastcall SV5_Thread::DisableROM(DL_HANDLE_T &dl_handle)
{
	unsigned short romNum=0;
	int ret;
	
	if( (S_DONE ==(ret= DL_GetCount_Ex(dl_handle, &romNum)) ) && (0 < romNum) )
	{

		for(int i = 0; i < romNum; i++) 			   
		{
			ROM_INFO_EX romInfo = {};	  
			if(S_DONE ==(ret= DL_Rom_GetInfo_Ex(dl_handle, i, &romInfo) ))
			{
				if((ARM_BL_ROM != romInfo.rom_type)&&(DSP_BL_ROM!= romInfo.rom_type)&&(EXT_BL_ROM !=romInfo.rom_type))
				{
					if(S_DONE !=(ret=DL_Rom_SetEnableAttr_Ex(dl_handle, i, _FALSE)))
					{
						GC_TRACE(" SV5_Thread::DisableROM==>DL_Rom_SetEnableAttr_Ex() failed! ");
						throw ret;
					}
					else
					{
						GC_TRACE("SV5_Thread::DisableROM:FileName: %s",romInfo.name); 
					}
					
				}
			}
			else
			{
				GC_TRACE(" DL_Rom_GetInfo_Ex() failed! ");
				throw ret;			
			}
		}
	}
	else
	{
		GC_TRACE(" DL_GetCount_Ex() failed! ");
		throw ret;
	}
    

}
//---------------------------------------------------------------------------

void __fastcall SV5_Thread::DisableROM(DL_HANDLE_LIST_T &dl_handle_list)
{
	int handle_count = 0;
	DL_GetHandleNumber(dl_handle_list, &handle_count);
	
	for (int handle_index=0; handle_index<handle_count; ++handle_index)
	{
		DL_HANDLE_T dl_handle = NULL;
		
		DL_GetHandle(dl_handle_list, handle_index, &dl_handle);
		DisableROM(dl_handle);
	} 
}  


//---------------------------------------------------------------------------

E_ResultAndAction _fastcall SV5_Thread::Format()
{
	int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
	E_WAIT_FOR_USB_INSERT_STATUS E_Wait_USB_Insert_Status;	
	FLASHTOOL_FORMAT_ARG_EX m_sFmtArg_ex;

	//add by Changshun
	if(USB_COM == m_sDnParam.e_com_type  && IsUSBDownloadWithTwoSite())
	{  
		if(is_have_meta_action_before_download())
		{
			E_Wait_USB_Insert_Status=WaitForUSBInsert(i);
			if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
			{
				return STATUS_FAIL;
			}
			WaitForComPortReadyAfterRegisterReady(m_sComPortSetting.com.number);			
	  }
	}
	
	if (RESET_TO_FACTORY == m_sDnParam.e_format_op)
	{
		g_iStopFlag[i] = 0;
		
		m_eMetaResult = Reset_To_Factory_Default_Procedure(m_sDnParam.e_bbchip_type, m_sDnParam.e_ext_clock);
		if (m_eMetaResult != META_SUCCESS)
		{
			SyncUpdateMetaResultError();
			SetEvent(Flash_Download_Event[i]);
			return STATUS_FAIL;
		}
		
		if (m_sDnParam.e_backup_cal_data_op == DN_WITH_BK_AND_RS_CAL_DATA)
		{
			m_eMetaResult = RestoreCalData();
			if (m_eMetaResult == META_SUCCESS)
			{
				//SyncUpdateMetaResultOk();
			}
			else
			{
				SyncUpdateMetaResultError();
				SetEvent(Flash_Download_Event[i]);
		  return STATUS_FAIL;
			}
		}
		else
		{
			//SyncUpdateMetaResultOk();
		}
		
		//SetEvent(Flash_Download_Event[i]);
		return SUCCESS_AND_GOON;
	}
	else // manual format
	{
		//SyncStartFormat();
		// storage type
		switch(/*m_sDnParam.e_Operation*/ MainForm->Get_Operation())
		{
		case OPERATION_NFB:
		{
			m_sFmtArg_ex.m_format_cfg.storageType=HW_STORAGE_NAND;
			m_sFmtArg_ex.m_format_cfg.validation=m_sDnParam.s_nfb_param.b_validation;;
			m_sFmtArg_ex.m_format_cfg.formatAction.uArg.NAND_manual.formatFlag=NUTL_ERASE;
			m_sFmtArg_ex.m_format_cfg.formatAction.uArg.NAND_manual.formatRange.startAddr=m_sDnParam.s_nfb_param.ui_nand_fat_begin_addr;
			m_sFmtArg_ex.m_format_cfg.formatAction.uArg.NAND_manual.formatRange.length=m_sDnParam.s_nfb_param.ui_nand_fat_length;
		}
		break;
			
		case OPERATION_NOR:
		default:
		{
			m_sFmtArg_ex.m_format_cfg.storageType=HW_STORAGE_NOR;
			m_sFmtArg_ex.m_format_cfg.validation=m_sDnParam.s_nor_param.b_validation;
			m_sFmtArg_ex.m_format_cfg.formatAction.uArg.manual.startAddr=m_sDnParam.s_nor_param.ui_fat_begin_addr;
			m_sFmtArg_ex.m_format_cfg.formatAction.uArg.manual.length=m_sDnParam.s_nor_param.ui_fat_length;
		}
		} // switch()
		m_sFmtArg_ex.m_format_cfg.formatAction.type=NORMAL_MANUAL_FORMAT;
		
		m_sFmtArg_ex.m_cb_format_report_init=::cb_format_report_init;
		m_sFmtArg_ex.m_cb_format_report_init_arg=this;
		m_sFmtArg_ex.m_cb_format_report=::cb_format_report;
		m_sFmtArg_ex.m_cb_format_report_arg= this;
		m_sFmtArg_ex.m_cb_format_statistics= ::cb_format_statistics;
		m_sFmtArg_ex.m_cb_format_statistics_arg = this;
		
		if (m_sDnParam.e_backup_cal_data_op == DN_WITH_BK_AND_RS_CAL_DATA)
		{
			m_sFmtArg_ex.m_enable_wdt_timeout		= _TRUE;
			m_sFmtArg_ex.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
		}
	 	else if (IsEnterMetaModeAfterDLMFT())
		{
			m_sFmtArg_ex.m_enable_wdt_timeout		= _TRUE;
			m_sFmtArg_ex.m_ms_wdt_timeout_interval = WATCH_DOG_TIMEOUT_INTERVAL;
		}
		else
		{
			m_sFmtArg_ex.m_enable_wdt_timeout		= _FALSE;
			m_sFmtArg_ex.m_ms_wdt_timeout_interval = 0;
		}

		//mingxue flash safe mode
		if(MainForm->FlashSafeMode->Checked==TRUE)
		{
			m_sFmtArg_ex.m_nor_flash_erase_mode 			= NOR_FLASH_ERASE_SAFE_MODE;
		}
		else
		{
			m_sFmtArg_ex.m_nor_flash_erase_mode				=NOR_FLASH_ERASE_FAST_MODE;
		}
		//end
		
		ret = FlashFormat_Ex(&m_sComPortSetting,&m_sFtArg,&m_sFtResult,&m_sFmtArg_ex,&m_sFmtResult,&g_iStopFlag[i]);
		if (S_DONE != ret)
		{
			GC_TRACE("Tboot::Execute Format fail");
			SyncUpdateResultError();
			return STATUS_FAIL;
		}


	if(is_have_action_after_download())
	{
		if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
		{  //two station usb download
			
			E_Wait_USB_Insert_Status=WaitForUSBInsert(i);
			if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
			{
				return STATUS_FAIL;
			}
		}
		else if(USB_COM == m_sDnParam.e_com_type && !IsUSBDownloadWithTwoSite())
		{  //one station usb download
			m_sFtArg.m_boot_arg.m_usb_enable = _FALSE;
		}
	}
		
		
		/////meta action after format
		if(m_sDnParam.e_backup_cal_data_op == DN_WITHOUT_BK_AND_RS_CAL_DATA)
		{
			if(IsEnterMetaModeAfterDLMFT()) 
			{
				m_eMetaResult = EnterMetaModeOnly();
				if (m_eMetaResult != META_SUCCESS)
				{
					SyncUpdateMetaResultError();
					SetEvent(Flash_Download_Event[i]);
					return STATUS_FAIL;
				}				 
			}
		}
		else if (m_sDnParam.e_backup_cal_data_op == DN_WITH_BK_AND_RS_CAL_DATA)
		{
			m_eMetaResult = RestoreCalData();
			if (m_eMetaResult == META_SUCCESS)
			{
				 //SyncUpdateMetaResultOk();	 
				 return SUCCESS_AND_GOON;
			}
			else
			{
				  SyncUpdateMetaResultError();
				  SetEvent(Flash_Download_Event[i]);
				  return STATUS_FAIL;
			}
			
			//SetEvent(Flash_Download_Event[i]);

		}
		
		
	} // manual or auto format()
	
	return SUCCESS_AND_GOON;
}


