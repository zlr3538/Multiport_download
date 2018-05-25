// GCTrace.h: interface for the NWVLTrace class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable: 4530)

#if !defined   _GC_GET_LAST_ERR_H_
#define        _GC_GET_LAST_ERR_H_

#include "MDT_ErrorTypes.h"
#include <string>
#include <map>

using namespace std;



typedef int GCErrCode;
typedef  std::pair<GCErrCode, string> MDTErrorType;


//------------------------------------
class  MDTErrorHandler
{
public:
	MDTErrorHandler()
	{
		m_err_table.clear();
		m_err = MDT_OK;
	}
	~MDTErrorHandler()
	{
		m_err_table.clear();
	};
	
	char* get_last_error();
	void reset(){m_err = MDT_OK;};
	void set_last_error(GCErrCode err){m_err = err;};
	void initial_err_table();
	void add_err_table(GCErrCode code, string info);
private:

     map<GCErrCode, std::string>  m_err_table;
     GCErrCode   m_err;
};
extern MDTErrorHandler G_ErrorHandler;

#define GET_LAST_ERROR() \
	G_ErrorHandler.get_last_error()

#define SET_LAST_ERROR(err) \
	G_ErrorHandler.set_last_error(err)

#define ADD_ERROR_TABLE_ITEM(code,info)\
	G_ErrorHandler.add_err_table(code,info)

#define INIT_ERROR_TABLE()\
	G_ErrorHandler.initial_err_table()


#endif // _GC_GET_LAST_ERR_H_
