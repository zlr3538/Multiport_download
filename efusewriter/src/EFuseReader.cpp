#include "efusewriter/inc/EFuseReader.h"
//==============*********Next Block is for class TEFuseWriter***********======================
__fastcall TEFuseReader::TEFuseReader(
	bool CreateSuspended,
	HANDLE hMsgHandle,
	COM_PORT_SETTING com_port_setting,
	S_DN_PARAM_T dn_param
):TBOOT1(CreateSuspended,hMsgHandle,com_port_setting,dn_param)
{
  m_p_handle_list = NULL;
}
//---------------------------------------------------------------------------
MDT_ERROR_STATUS __fastcall TEFuseReader::setefusereadhandle(CMDT_Efuse_Reader_Handle_List* p_handle)
{
  if ( NULL ==  p_handle)
  {
    return MDT_SV5_EFUSE_WRITER_INVALID_POINTER;
  }

  m_p_handle_list = p_handle;

  return MDT_OK;
}
//---------------------------------------------------------------------------
void __fastcall TEFuseReader::printProcessInfo()
{
    GC_TRACE_EX("==================== Begin EFuse Reader====================");
    GC_TRACE_EX("COM Port: %d", m_sComPortSetting.com.number);
    GC_TRACE_EX("Cable Type: %s", (USB_COM == m_sDnParam.e_com_type ? "USB": "UART"));
    GC_TRACE_EX("UART Baud Rate Class: %d [1-921600][2-460800][3-230400][4-115200]", m_sDnParam.e_baud_rate);
    GC_TRACE_EX("Extern Clock: %d [1-13M][2-26M][3-39M][4-52M][254-AUTO][255-Unkonw]", m_sDnParam.e_ext_clock);
}
//---------------------------------------------------------------------------
MDT_ERROR_STATUS __fastcall TEFuseReader::checkparameter()
{
  if ( NULL == m_p_handle_list)
  {
	  GC_TRACE_EX("m_p_handle_list is NULL");
	  return MDT_SV5_EFUSE_WRITER_INVALID_PARAMETER;
  }

  return MDT_OK;
}

//---------------------------------------------------------------------------
void __fastcall TEFuseReader::Execute()
{
  E_WAIT_FOR_USB_INSERT_STATUS E_Wait_USB_Insert_Status;
  int i = m_sComPortSetting.com.number - m_sDnParam.i_FirstComNo;
  int efuse_status;
  unsigned int WriterHandle=0;

  FLASHTOOL_API_HANDLE_T flash_tool_handle = NULL;

  MDT_Handle_Rwlock& rwlock_handle = (MDT_Handle_Rwlock&)m_p_handle_list->m_mdt_handle_lock;
  rwlock_writer_sentry* p_efuse_reader_sentry = NULL;


  Initial_download_arg_memory();
  Set_FlashTool_arg();

  Synchronize(UpdateEfuseOperationProgressBarSetting);

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
	UpdateProgressStatus(i,"Searching...",0);
    if(USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
    { 
      E_Wait_USB_Insert_Status=WaitForUSBInsert(i);
      if(S_USB_INSERT_READY!=E_Wait_USB_Insert_Status)
      {
        SyncUpdateResultError();
        return ;
      }
      WaitForComPortReadyAfterRegisterReady(m_sComPortSetting.com.number);
    }		 
    
    if( ( UART_COM == m_sDnParam.e_com_type)
    || (USB_COM == m_sDnParam.e_com_type && IsUSBDownloadWithTwoSite())
    )
    { 
      UpdateProgressStatus(i,"Connecting...",10);
      GC_TRACE("====== TEFuseWriter::Execute Begin EFuse Reader==="); 			   
#if 1
      efuse_status= Brom_Connect(
                                &WriterHandle,
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

        int temp_status = Brom_DisConnect(&WriterHandle, &flash_tool_handle);
        if( S_DONE != temp_status)
        {
          GC_TRACE("TEFuseWriter::Disconnect Fail: %s",StatusToString(temp_status)); 
        }
        return ;
      }
      Sleep(1000);
      UpdateProgressStatus(i,"Reading...",50);
      efuse_status = Brom_ReadEfuseAll(WriterHandle,
                                       flash_tool_handle,
                                       &m_EFuseReaderItem.m_common_arg,
                                       &m_EFuseReaderItem.m_secure_arg,
                                       &m_EFuseReaderItem.m_lock_arg
                                       );
      if(S_DONE!=efuse_status)
      {
        GC_TRACE_EX("TEFuseWriter::Read Fail: %s",StatusToString(efuse_status)); 
        SyncUpdateResultError();

        int temp_status = Brom_DisConnect(&WriterHandle, &flash_tool_handle);
        if( S_DONE != temp_status)
        {
          GC_TRACE("TEFuseWriter::Disconnect Fail: %s",StatusToString(temp_status)); 
        }
        return ;
      }

      UpdateProgressStatus(i,"Reading...",90);
      Sleep(2000);
      UpdateProgressStatus(i,"Disconnecting...",95);
      Sleep(1000);
      efuse_status = Brom_DisConnect(&WriterHandle, &flash_tool_handle);
      if( S_DONE != efuse_status)
      {
        GC_TRACE("TEFuseWriter::Disconnect Fail: %s",StatusToString(efuse_status)); 
        SyncUpdateResultError();
        return;
      }
#endif
    }
    else
    {  
      GC_TRACE("====== TEFuseWriter::Execute:  Error: No Support Writer Mode ===");
      SyncUpdateResultError();
      return;
    }
    
    p_efuse_reader_sentry = new rwlock_writer_sentry(rwlock_handle);
    try
    {
      m_p_handle_list->Update(m_sComPortSetting.com.number,m_EFuseReaderItem);
    }
    catch(...)
    {
      GC_TRACE_EX("m_p_handle_list->Update() Throw An Exception!");
      delete p_efuse_reader_sentry;
      p_efuse_reader_sentry = NULL;
      throw;
    }
    delete p_efuse_reader_sentry;
    p_efuse_reader_sentry = NULL;
    
    GC_TRACE_EX("Update EFuse Reader Result: %d",m_sComPortSetting.com.number);
    m_EFuseReaderItem.PrintWriteParameterLog();
    m_EFuseReaderItem.PrintLockParameterLog();
    
    SetEvent(Flash_Download_Event[i]);
    
    GC_TRACE("Tboot::Execute eFuseWrite Success");
	UpdateProgressStatus(i,"",100);
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

