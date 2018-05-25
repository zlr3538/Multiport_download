#include "efusewriter/inc/EFuseWriter.h"

//==============*********Next Block is for class TEFuseWriter***********======================
__fastcall TEFuseWriter::TEFuseWriter(
	bool CreateSuspended, 
	HANDLE hMsgHandle, 
	COM_PORT_SETTING com_port_setting, 
	S_DN_PARAM_T dn_param
)
:TBOOT1(CreateSuspended,hMsgHandle,com_port_setting,dn_param)
{
  m_EFuseLockAction = false;
  m_EFuseWriteAction = false;
  p_writer_handle = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriter::SetEFuseWriteAction(bool EFuseWriteAction)
{
  this->m_EFuseWriteAction = EFuseWriteAction;
}

void __fastcall TEFuseWriter::SetEFuseLockAction(bool EFuseLockAction)
{
  this->m_EFuseLockAction = EFuseLockAction;
}

//---------------------------------------------------------------------------
MDT_ERROR_STATUS __fastcall TEFuseWriter::SetEFuseWriteHandle(const CMDT_Efuse_Writer_Handle* p_handle)
{
  if ( NULL == p_handle )
  {
    return MDT_SV5_EFUSE_WRITER_INVALID_POINTER;
  }

  p_writer_handle = p_handle;

  return MDT_OK;
}
//---------------------------------------------------------------------------
void __fastcall TEFuseWriter::printProcessInfo()
{
    GC_TRACE("==================== Begin EFuse Writer====================");
    GC_TRACE("COM Port: %d", m_sComPortSetting.com.number);
    GC_TRACE("Cable Type: %s", (USB_COM == m_sDnParam.e_com_type ? "USB": "UART"));
    GC_TRACE("UART Baud Rate Class: %d [1-921600][2-460800][3-230400][4-115200]", m_sDnParam.e_baud_rate);
    GC_TRACE("Extern Clock: %d [1-13M][2-26M][3-39M][4-52M][254-AUTO][255-Unkonw]", m_sDnParam.e_ext_clock);
	if( true == m_EFuseWriteAction)
	{
		GC_TRACE_EX("Efuse Write Action is On!");
	}
	else
	{
		GC_TRACE_EX("Efuse Write Action is Off!");
	}
	if( true == m_EFuseLockAction)
	{
		GC_TRACE_EX("Efuse Lock Action is On!");
	}
	else
	{
		GC_TRACE_EX("Efuse Lock Action is Off!");
	}

	p_writer_handle->PrintWriteParameterLog();
	p_writer_handle->PrintLockParameterLog();	
}
//---------------------------------------------------------------------------
MDT_ERROR_STATUS __fastcall TEFuseWriter::checkparameter()
{
  if ( NULL == p_writer_handle)
  {
	  GC_TRACE_EX("p_writer_handle is NULL"); 
	  return MDT_SV5_EFUSE_WRITER_INVALID_PARAMETER;
  }
  if( false == m_EFuseWriteAction 
  	&& false == m_EFuseLockAction )
  {
    GC_TRACE("TEFuseWriter::Execute Error: m_EFuseWriteAction==false && m_EFuseLockAction==false"); 
    return MDT_SV5_EFUSE_WRITER_INVALID_PARAMETER;
  }
  
  return MDT_OK;
}

//---------------------------------------------------------------------------
void __fastcall TEFuseWriter::Execute()
{
  E_WAIT_FOR_USB_INSERT_STATUS E_Wait_USB_Insert_Status;
  int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
  int efuse_status;
  unsigned int WriterHandle;
  FLASHTOOL_API_HANDLE_T flash_tool_handle = NULL;
  
  HANDLE com_handle=INVALID_HANDLE_VALUE;
  MDT_Handle_Rwlock& rwlock_handle = (MDT_Handle_Rwlock&)p_writer_handle->m_mdt_handle_lock;
  rwlock_reader_sentry efuse_writer_sentry(rwlock_handle);

  Synchronize(UpdateEfuseOperationProgressBarSetting);

  Initial_download_arg_memory();
  Set_FlashTool_arg();
	
  printProcessInfo();
  if( MDT_OK != checkparameter())
  {
    SyncUpdateResultError();
    return ;
  }
  SyncStart();

  try
  {
    	// comport setting
    m_iComPortIdx = i;
	UpdateProgressStatus(i,"Searching",0);
    if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
    { 
      E_Wait_USB_Insert_Status=WaitForUSBInsert(i);
      if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
      {
        return ;
      }	  
      WaitForComPortReadyAfterRegisterReady(m_sComPortSetting.com.number);
    }		 
    UpdateProgressStatus(i,"Connecting",10);
	
    if( ( UART_COM == m_sDnParam.e_com_type)
    	|| (USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
    	   )
    { 
      GC_TRACE("====== TEFuseWriter::Execute Begin EFuse Writer===");
#if 1
      efuse_status = Brom_Connect(&WriterHandle,
                                  &flash_tool_handle,
                                  m_sComPortSetting.com.number,
                                  m_sFtArg.m_boot_arg.m_bbchip_type,
                                  m_sFtArg.m_boot_arg.m_ext_clock,
                                  &g_iStopFlag[i],
                                  m_sFtArg.m_boot_arg.m_ms_boot_timeout,
                                  m_sFtArg.m_boot_arg.m_max_start_cmd_retry_count);
      
      if(S_DONE!=efuse_status)
      {
        GC_TRACE("TEFuseWriter::Brom_Connect Fail: %s",StatusToString(efuse_status)); 
        SyncUpdateResultError();      
        return;
      }

      if(this->m_EFuseWriteAction)
      {
    	  UpdateProgressStatus(i,"Writing",30);
    	  Sleep(1000);
          //Write
        efuse_status= Brom_WriteEfuseCommon(
                                            WriterHandle,
                                            flash_tool_handle,
                                            &p_writer_handle->m_common_arg);
        if( S_DONE != efuse_status )
        {
          GC_TRACE("TEFuseWriter::Brom_Connect Fail: %s",StatusToString(efuse_status)); 
          SyncUpdateResultError();

		  int temp_status = Brom_DisConnect(&WriterHandle, &flash_tool_handle);
		  if( S_DONE != temp_status)
		  {
			GC_TRACE("TEFuseWriter::Disconnect Fail: %s",StatusToString(temp_status)); 
		  }
		  return ;
        }
		UpdateProgressStatus(i,"Writing",50);
		Sleep(1000);
        
        efuse_status= Brom_WriteEfuseSecure(
                                     WriterHandle,
                                     flash_tool_handle,
                                     &p_writer_handle->m_secure_arg);
        if(S_DONE!=efuse_status)
        {
          GC_TRACE("TEFuseWriter::Brom_Connect Fail: %s",StatusToString(efuse_status)); 
          SyncUpdateResultError();

		  int temp_status = Brom_DisConnect(&WriterHandle, &flash_tool_handle);
		  if( S_DONE != temp_status)
		  {
			GC_TRACE("TEFuseWriter::Disconnect Fail: %s",StatusToString(temp_status)); 
		  }
		  return ;
        }
      }
      
	  UpdateProgressStatus(i,"Writing",70);
	  Sleep(1000);
      //Lock
      if(this->m_EFuseLockAction)
      {
		UpdateProgressStatus(i,"Locking...",80);
		Sleep(500);
        efuse_status= Brom_WriteEfuseLock(
                                  WriterHandle,
                                  flash_tool_handle,
                                  &p_writer_handle->m_lock_arg);
        if(S_DONE!=efuse_status)
        {
          GC_TRACE("TEFuseWriter::Brom_Connect Fail: %s",StatusToString(efuse_status)); 
          SyncUpdateResultError();

		  int temp_status = Brom_DisConnect(&WriterHandle, &flash_tool_handle);
		  if( S_DONE != temp_status)
		  {
			GC_TRACE("TEFuseWriter::Disconnect Fail: %s",StatusToString(temp_status)); 
		  }
		  return ;
        }
      }
	  UpdateProgressStatus(i,"Disconnecting",100);
	  Sleep(1000);

      efuse_status = Brom_DisConnect(&WriterHandle, &flash_tool_handle);
      if( S_DONE != efuse_status)
      {
        GC_TRACE("TEFuseWriter::Disconnect Fail: %s",StatusToString(efuse_status)); 
        SyncUpdateResultError();
        return;
      }
	  UpdateProgressStatus(i,"",100);
	  Sleep(1000);
      
#endif
    }
    else
    {  
      GC_TRACE("====== TEFuseWriter::Execute:  Error: No Support Writer Mode ===");
      SyncUpdateResultError();
      return;
    }
    
    SetEvent(Flash_Download_Event[i]);
    GC_TRACE("Tboot::Execute eFuseWrite Success");
    SyncUpdateResultOk();
    MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;  	
  }
  catch(...)
  {
    GC_TRACE("DL work thread %d unexception arise", i);
    MainForm->DownloadStatus[i] = DOWNLOAD_STATUS_NOTRUNNING;
    return;
  }
	
}
//---------------------------------------------------------------------------


