#ifndef MDT_EFUSEWRITER_CEFUSEWRITERHANDLE_H__
#define MDT_EFUSEWRITER_CEFUSEWRITERHANDLE_H__

#include "brom_dll/inc/brom.h"
#include "efusewriter/inc/mdt_handle_rwlock.h"
#include "efusewriter/inc/cmdtefuseparameterhandle.h"
#include "mdt_component/error_handler/inc/MDT_ErrorTypes.h"
class CMDT_Efuse_Writer_Handle:public CMDT_Efuse_Parameter_Handle
{
public:
  CMDT_Efuse_Writer_Handle();
  virtual void PrintSpareDataLog()const;
  virtual void PrintAcKeyLog()const;
  virtual void PrintPublicKeyDataLog()const;
  
  virtual ~CMDT_Efuse_Writer_Handle();
  virtual void clearconfigfilesetting();
  virtual void clearlockfilesetting();  
  virtual MDT_ERROR_STATUS reset();

  MDT_Handle_Rwlock m_mdt_handle_lock;

private:
  //private: do not use = operator
  CMDT_Efuse_Writer_Handle& operator=(const CMDT_Efuse_Writer_Handle& handle)
  {
    //Do nothing...
    return *this;
  }
  //do not use copy constructor
  CMDT_Efuse_Writer_Handle(const CMDT_Efuse_Writer_Handle& handle)
  {
    //Do nothing...
  }
};

#endif
