// GCTrace.h: interface for the NWVLTrace class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable: 4530)

#if !defined(_GC_TRACE_H_)
#define  _GC_TRACE_H_

#include <windows.h>
#include <string>
using namespace std;

#define	DEFAULT_NWVT_LOG_PATH	"C:\\FP_MDT.log"
#define	TRACE_BUFFER_SIZE	4096
#define	TRACE_HEADER_SIZE   128

#define	BOOL	bool

class GCTrace  
{
public:
	GCTrace()
	{
		m_h_log = INVALID_HANDLE_VALUE;
		m_is_debug_on = FALSE;
	}
	virtual ~GCTrace();
	void set_log_path(string  log_path)
	{
		m_log_path = log_path;
	}
	void dump_binary_by_hex(const unsigned char * byte,  unsigned long len)const;
	void tarce(const char *pText, ...)const;
	void base_tarce(const char *pText, ...)const;
	void debug_on();
	void debug_off();
	void clear();
	BOOL is_log_file_exist();
	void operator()(const char* Format, ... ) const;
	void SetLogFormat(const char* FileName,int LineNumber,const char* Functionname,const char* Prefix);
private:
	string m_log_path;
	HANDLE m_h_log;
	bool   m_is_debug_on;
	char trace_time[TRACE_HEADER_SIZE];
	char trace_process_info[TRACE_HEADER_SIZE];
	char msg[TRACE_BUFFER_SIZE];
	string m_FileName;
	int m_LineNumber;
	string m_FunctionName;
	string m_Prefix;
};

extern GCTrace	Log;

#define	GC_TRACE_CLEAR	        Log.clear
#define	GC_TRACE_ON	        Log.debug_on
#define	GC_TRACE_OFF	        Log.debug_off
#define	GC_TRACE	        Log.tarce
#define	GC_TRACE_DUMP(X, Y)	Log.dump_binary_by_hex(X, Y)

#define GC_TRACE_EX	Log.SetLogFormat( __FILE__, __LINE__, __FUNC__, ""); Log
#define GC_TRACE_WARN_EX	Log.SetLogForamt( __FILE__, __LINE__, __FUNC__, "WARNING");Log
#define GC_TRACE_ERR_EX Log Log.SetLogForamt( __FILE__, __LINE__, __FUNC__, "ERROR");Log



#endif // _GC_TRACE_H_
