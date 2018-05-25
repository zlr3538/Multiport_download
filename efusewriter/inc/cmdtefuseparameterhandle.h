#ifndef MDT_EFUSEWRITER_PARAMETER_HANDLE_H__
#define MDT_EFUSEWRITER_PARAMETER_HANDLE_H__
#include "brom_dll/inc/brom.h"
#include "mdt_component/error_handler/inc/GCTrace.h"
class CMDT_Efuse_Parameter_Handle
{
public:
  CMDT_Efuse_Parameter_Handle();
  virtual ~CMDT_Efuse_Parameter_Handle();
  void reset_setting();
  void reset_write_setting();
  void reset_lock_setting();
  virtual void PrintSpareDataLog()const;
  virtual void PrintAcKeyLog()const;
  virtual void PrintPublicKeyDataLog()const;
  
  virtual void PrintWriteParameterLog()const;
  virtual void PrintLockParameterLog()const;
  virtual bool is_non_secure_user_setting()const;

  Efuse_Common_Arg m_common_arg;
  Efuse_Secure_Arg m_secure_arg;
  Efuse_Lock_Arg m_lock_arg;

};


#endif
