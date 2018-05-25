// NWVLTrace.cpp: implementation of the NWVLTrace class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop

#include "mdt_component/error_handler/inc/GCTrace.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GCTrace	Log;

GCTrace::~GCTrace()
{
    debug_off();
}

BOOL GCTrace::is_log_file_exist()
{ 
    HANDLE	test_handle;

    test_handle = CreateFile(DEFAULT_NWVT_LOG_PATH, GENERIC_WRITE,
                             FILE_SHARE_WRITE|FILE_SHARE_READ, NULL, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL, NULL);

    return (INVALID_HANDLE_VALUE != test_handle);
}

void GCTrace::debug_off()
{
    m_is_debug_on = FALSE;

    if (INVALID_HANDLE_VALUE != m_h_log)
    {
        CloseHandle(m_h_log);
    }
}

void GCTrace::debug_on()
{
    m_is_debug_on = TRUE;


    //Find if log file exist
    if (TRUE == is_log_file_exist())
    {
            m_h_log = CreateFile(DEFAULT_NWVT_LOG_PATH, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                                             OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);

            SetFilePointer(m_h_log, 0, 0, FILE_END);
    }
    else
    {
            m_h_log = CreateFile(DEFAULT_NWVT_LOG_PATH, GENERIC_WRITE, FILE_SHARE_WRITE|FILE_SHARE_WRITE, NULL,
                                                     CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
    }

    if (m_h_log == INVALID_HANDLE_VALUE) 
    { 
        m_is_debug_on = FALSE;
    } 

    base_tarce("\n=========================================================\n");
    base_tarce("| Multiport Flash Download Project Tarce On		 \n");
    base_tarce("|                                     			 \n");
    base_tarce("| Build Data:  %s \n", __DATE__);
    base_tarce("| Build Time:  %s \n", __TIME__);
    base_tarce("=========================================================\n\n");

}

void GCTrace::clear()
{
    debug_off();

    DeleteFile(DEFAULT_NWVT_LOG_PATH);

    m_h_log = CreateFile(DEFAULT_NWVT_LOG_PATH, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (INVALID_HANDLE_VALUE != m_h_log)
    {
        CloseHandle(m_h_log);
    }
    
    debug_on();
}

void GCTrace::base_tarce(const char *pText, ...)const
{
    va_list params;
    DWORD	wl;
    char msg[TRACE_BUFFER_SIZE];

    if (!m_is_debug_on)
    {
        return;
    }

    va_start( params, pText );
    _vsnprintf( msg, TRACE_BUFFER_SIZE, pText, params );
    va_end( params );

    WriteFile(m_h_log, msg, strlen(msg), &wl, NULL);

    return;
}

void GCTrace::tarce(const char *pText, ...)const
{
    va_list params;
    DWORD	wl;
    char trace_time[TRACE_HEADER_SIZE];
    char trace_process_info[TRACE_HEADER_SIZE];
    char msg[TRACE_BUFFER_SIZE];

    SYSTEMTIME  system_time;

    if (!m_is_debug_on)
    {
        return;
    }

    sprintf(trace_time, "\r\n[PID:%04d] [TID:%04d]",
            GetCurrentProcessId(),
            GetCurrentThreadId());

    string info = trace_time;


    GetLocalTime(&system_time);

    sprintf(trace_time, " [%02d-%02d-%02d %02d:%02d:%02d::%03d] ",
            system_time.wYear,
            system_time.wMonth,
            system_time.wDay,
            system_time.wHour,
            system_time.wMinute,
            system_time.wSecond,
            system_time.wMilliseconds);

    info += trace_time;

    va_start( params, pText );
    _vsnprintf( msg, TRACE_BUFFER_SIZE, pText, params );
    va_end( params );

    info += msg;

    WriteFile(m_h_log, info.c_str(), info.size(), &wl, NULL);

    return;
}

//tarcedump_binary_by_hex
// 0x56 0x96 0x36 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF  -> 16 for row
// 0x56 0x96 0x36
#define  DUMP_BINARY_BY_HEX_ROW_NUMBER	16

void GCTrace::dump_binary_by_hex(const unsigned char * byte,  unsigned long len)const
{
    for (unsigned long i=0; i< len; i++)
    {
        if ((i%DUMP_BINARY_BY_HEX_ROW_NUMBER) == 0)
        {
            tarce("\n ");
        }

        tarce("0X%02x ", *(byte+i));
    }
}


void GCTrace::SetLogFormat(const char* FileName,int LineNumber,const char* Functionname,const char* Prefix)
{
	const char* m_file;
	
	if (FileName != NULL)
    {
        // retrieve the filename only
        NULL==(m_file=_tcsrchr(FileName,'\\')) ? m_file = FileName : m_file = m_file + 1;
    	this->m_FileName=m_file;
	}
	else
	{
		this->m_FileName="";
	}
	this->m_LineNumber=LineNumber;
	this->m_FunctionName=Functionname;
	this->m_FunctionName+="() ";
	this->m_Prefix=Prefix;
}


void GCTrace::operator()(const char* pText, ... ) const
{
	va_list params;
	DWORD	wl;
	char trace_time[TRACE_HEADER_SIZE];
	char trace_process_info[TRACE_HEADER_SIZE];
	char msg[TRACE_BUFFER_SIZE];

	SYSTEMTIME	system_time;

	if (!m_is_debug_on)
	{
		return;
	}

	sprintf(trace_time, "\r\n[PID:%04d] [TID:%04d]",
			GetCurrentProcessId(),
			GetCurrentThreadId());

	string info = trace_time;


	GetLocalTime(&system_time);

	sprintf(trace_time, " [%02d-%02d-%02d %02d:%02d:%02d::%03d] ",
			system_time.wYear,
			system_time.wMonth,
			system_time.wDay,
			system_time.wHour,
			system_time.wMinute,
			system_time.wSecond,
			system_time.wMilliseconds);
	info += trace_time;
	info+=m_Prefix;
	info+=m_FunctionName;

	va_start( params, pText );
	_vsnprintf( msg, TRACE_BUFFER_SIZE, pText, params );
	va_end( params );
	info += msg;

	info+="  (";
	info+=m_FileName;
	info+=":";
	
	sprintf(trace_time, "%d",m_LineNumber);
	info+=trace_time;
	info+=")  ";
	


	WriteFile(m_h_log, info.c_str(), info.size(), &wl, NULL);

	return;
}


