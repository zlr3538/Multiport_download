#ifndef MDT_EFUSEWRITER_CEFUSEREADERHANDLE_H____
#define MDT_EFUSEWRITER_CEFUSEREADERHANDLE_H____

#define MDT_EFUSE_READER_SPARE_BUFFER_LEN 12
#define MDT_EFUSE_READER_AC_KEY_BUFFER_LEN 16
#define MDT_EFUSE_READER_SBC_HASH_BUFFER_LEN 32

#include <map.h>
#include "brom_dll/inc/brom.h"
#include "mdt_component/error_handler/inc/MDT_ErrorTypes.h"
#include "efusewriter/inc/mdt_handle_rwlock.h"
#include "efusewriter/inc/cmdtefuseparameterhandle.h"
class CMDT_Efuse_Reader_Handle:public CMDT_Efuse_Parameter_Handle
{
public:
  CMDT_Efuse_Reader_Handle();
  explicit CMDT_Efuse_Reader_Handle(const CMDT_Efuse_Reader_Handle& handle);
  virtual ~CMDT_Efuse_Reader_Handle();
  virtual MDT_ERROR_STATUS reset();
  
  virtual void PrintSpareDataLog()const;
  virtual void PrintAcKeyLog()const;
  virtual void PrintPublicKeyDataLog()const;
private:
  //private: do not use = operator
  CMDT_Efuse_Reader_Handle& operator=(const CMDT_Efuse_Reader_Handle& handle)
  {
		//Do nothing...
    return *this;
  }
};


class CMDT_Efuse_Reader_Handle_List
{
public:
  CMDT_Efuse_Reader_Handle_List();
  virtual ~CMDT_Efuse_Reader_Handle_List();
  virtual MDT_ERROR_STATUS Update(const int ComPort,const CMDT_Efuse_Reader_Handle& efuse_reader_handle);

  map<int,CMDT_Efuse_Reader_Handle> m_efuse_reader_list;
  MDT_Handle_Rwlock m_mdt_handle_lock;
};


#endif
