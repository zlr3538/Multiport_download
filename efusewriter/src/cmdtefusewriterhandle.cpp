#include "efusewriter/inc/cmdtefusewriterhandle.h"

CMDT_Efuse_Writer_Handle::CMDT_Efuse_Writer_Handle()
{

}

CMDT_Efuse_Writer_Handle::~CMDT_Efuse_Writer_Handle()
{
  if ( NULL != m_common_arg.spare.buf)
  {
	delete m_common_arg.spare.buf;
	m_common_arg.spare.buf = NULL;
  }
  if ( NULL != m_secure_arg.ac_key.buf)
  {
	delete m_secure_arg.ac_key.buf;
	m_secure_arg.ac_key.buf = NULL;
  }
  if( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf )
  {
	delete m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf;
	m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf = NULL;
  }
  if( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf)
  {
	delete m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf;
	m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf = NULL;
  }
}
void CMDT_Efuse_Writer_Handle::clearconfigfilesetting()
{
  if ( NULL != m_common_arg.spare.buf )
  {
    delete m_common_arg.spare.buf;
    m_common_arg.spare.buf = NULL;
  }
  if ( NULL != m_secure_arg.ac_key.buf)
  {
    delete m_secure_arg.ac_key.buf;
    m_secure_arg.ac_key.buf = NULL;
  }
  if( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf )
  {
    delete m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf;
    m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf = NULL;
  }
  if( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf)
  {
    delete m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf;
    m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf = NULL;
  }
  
  reset_write_setting();
}
void CMDT_Efuse_Writer_Handle::clearlockfilesetting()
{
  reset_lock_setting();
}

MDT_ERROR_STATUS CMDT_Efuse_Writer_Handle::reset()
{
  clearconfigfilesetting();
  clearlockfilesetting();

  return MDT_OK;
}
void CMDT_Efuse_Writer_Handle::PrintSpareDataLog()const
{
	if( NULL != m_common_arg.spare.buf
	  && m_common_arg.spare.buf_len>0)
	{
	  GC_TRACE_EX("SpareData: %s",m_common_arg.spare.buf);
	}
	else
	{
		GC_TRACE_EX("SpareData is null");
	}
}

void CMDT_Efuse_Writer_Handle::PrintAcKeyLog()const
{
	if( NULL != m_secure_arg.ac_key.buf
	  && m_secure_arg.ac_key.buf_len>0)
	{
	  GC_TRACE_EX("AC Key: %s",m_secure_arg.ac_key.buf);
	}
	else
	{
		GC_TRACE_EX("AC Key is null");
	}
}

void CMDT_Efuse_Writer_Handle::PrintPublicKeyDataLog()const
{

	if( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf
	  && m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf_len>0)
	{
	  GC_TRACE_EX("Public Key E: %s",m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_e.buf);
	}
	else
	{
		GC_TRACE_EX("Public Key E is null");
	}
	
	if( NULL != m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf
	  && m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf_len>0)
	{
	  GC_TRACE_EX("Public Key N: %s",m_secure_arg.sbc_pub_key_u.w_sbc_pub_key.key_n.buf);
	}
	else
	{
		GC_TRACE_EX("Public Key N is null");
	}
}

