#include <vcl.h>
#include "efusewriter/inc/cmdtefusereaderhandle.h"
#include "stdio.h"

//---------------------------------------------------------------------------
CMDT_Efuse_Reader_Handle::CMDT_Efuse_Reader_Handle()
{
  m_common_arg.spare.buf = new char[MDT_EFUSE_READER_SPARE_BUFFER_LEN];
  m_common_arg.spare.buf_len = MDT_EFUSE_READER_SPARE_BUFFER_LEN;

  m_secure_arg.ac_key.buf = new char[MDT_EFUSE_READER_AC_KEY_BUFFER_LEN];
  m_secure_arg.ac_key.buf_len = MDT_EFUSE_READER_AC_KEY_BUFFER_LEN;
  
  m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf = new char[MDT_EFUSE_READER_SBC_HASH_BUFFER_LEN];
  m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf_len = MDT_EFUSE_READER_SBC_HASH_BUFFER_LEN;

  reset();
}
//---------------------------------------------------------------------------
CMDT_Efuse_Reader_Handle::CMDT_Efuse_Reader_Handle(const CMDT_Efuse_Reader_Handle& handle)
{
  m_common_arg.spare.buf = new char[MDT_EFUSE_READER_SPARE_BUFFER_LEN];
  m_common_arg.spare.buf_len = MDT_EFUSE_READER_SPARE_BUFFER_LEN;
  
  m_secure_arg.ac_key.buf = new char[MDT_EFUSE_READER_AC_KEY_BUFFER_LEN];
  m_secure_arg.ac_key.buf_len = MDT_EFUSE_READER_AC_KEY_BUFFER_LEN;
  
  m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf = new char[MDT_EFUSE_READER_SBC_HASH_BUFFER_LEN];
  m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf_len = MDT_EFUSE_READER_SBC_HASH_BUFFER_LEN;

  reset();
//backup buf pointer

  char* backup_common_arg_spare_buf = m_common_arg.spare.buf;
  unsigned int backup_common_arg_spare_buf_len = m_common_arg.spare.buf_len;

  char* backup_secure_arg_ackey_buf = m_secure_arg.ac_key.buf ;
  unsigned int backup_secure_arg_ackey_buf_len = m_secure_arg.ac_key.buf_len;
  
  char* backup_secure_arg_sbc_hash_buf = m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf;
  unsigned int backup_secure_arg_sbc_hash_buf_len = m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf_len;
  
  this->m_common_arg = handle.m_common_arg;
  this->m_secure_arg = handle.m_secure_arg;
  this->m_lock_arg = handle.m_lock_arg;

//Restore buf pointer;
  m_common_arg.spare.buf = backup_common_arg_spare_buf;
  m_common_arg.spare.buf_len = backup_common_arg_spare_buf_len;

  m_secure_arg.ac_key.buf = backup_secure_arg_ackey_buf;
  m_secure_arg.ac_key.buf_len = backup_secure_arg_ackey_buf_len;
  
  m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf = backup_secure_arg_sbc_hash_buf;
  m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf_len = backup_secure_arg_sbc_hash_buf_len;
//  memcpy(this,&handle,sizeof(handle));
  if( NULL != m_common_arg.spare.buf)
  {
    memcpy(m_common_arg.spare.buf,
           handle.m_common_arg.spare.buf,
           handle.m_common_arg.spare.buf_len);
  }
  if( NULL != m_secure_arg.ac_key.buf)
  {
    memcpy(m_secure_arg.ac_key.buf,
           handle.m_secure_arg.ac_key.buf,
           handle.m_secure_arg.ac_key.buf_len);
  }
  if( NULL != m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf)
  {
    memcpy(m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf,
  	       handle.m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf,
  	       handle.m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf_len);
  }
}

//---------------------------------------------------------------------------
CMDT_Efuse_Reader_Handle::~CMDT_Efuse_Reader_Handle()
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
  if ( NULL != m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf)
  {
	delete m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf;
	m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf = NULL;
  }
}
//---------------------------------------------------------------------------
MDT_ERROR_STATUS CMDT_Efuse_Reader_Handle::reset()
{
  //reset buffer...
  if(NULL != m_common_arg.spare.buf)
  {
    memset(m_common_arg.spare.buf,0x00,MDT_EFUSE_READER_SPARE_BUFFER_LEN);
  }
  if(NULL != m_secure_arg.ac_key.buf)
  {
    memset(m_secure_arg.ac_key.buf,0x00,MDT_EFUSE_READER_AC_KEY_BUFFER_LEN);
  }
  if(NULL != m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf)
  {
    memset(m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf
  	      ,0x00
  	      ,MDT_EFUSE_READER_SBC_HASH_BUFFER_LEN);
  }
  reset_setting();

  return MDT_OK;
}
//---------------------------------------------------------------------------
void CMDT_Efuse_Reader_Handle::PrintSpareDataLog()const
{
  AnsiString Buffer = "";
  int index;

  if( NULL != m_common_arg.spare.buf
      && m_common_arg.spare.buf_len>0)
  {
    Buffer = "";
    for(index = 0; index < (int)m_common_arg.spare.buf_len ;index++)
    {
      int Temp_Integer = m_common_arg.spare.buf[index]&0xFF;
      Buffer = Buffer +IntToHex(Temp_Integer,2)+" ";
    }
    GC_TRACE_EX("SpareData: %s",Buffer.c_str());
  }
}

//---------------------------------------------------------------------------
void CMDT_Efuse_Reader_Handle::PrintAcKeyLog()const
{
  AnsiString Buffer = "";
  int index;
  
  if( NULL != m_secure_arg.ac_key.buf
    && m_secure_arg.ac_key.buf_len>0)
  {
    Buffer = "";
    for(index = 0; index < (int)m_secure_arg.ac_key.buf_len ;index++)
    {
      int Temp_Integer = m_secure_arg.ac_key.buf[index]&0xFF;
  	  Buffer = Buffer +IntToHex(Temp_Integer,2)+" ";
    }    
    GC_TRACE_EX("AC Key: %s",Buffer.c_str());
  }
}
//---------------------------------------------------------------------------

void CMDT_Efuse_Reader_Handle::PrintPublicKeyDataLog()const
{
  AnsiString Buffer = "";
  int index;
  
  if( NULL != m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf
    && m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf_len>0)
  {

    Buffer = "";
    for(index = 0; index < (int)m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf_len ;index++)
    {
      int Temp_Integer = m_secure_arg.sbc_pub_key_u.r_sbc_pub_key_hash.buf[index]&0xFF;
      Buffer = Buffer + IntToHex(Temp_Integer,2)+" ";
    }
    
    GC_TRACE_EX("Public Key Hash: %s",Buffer.c_str());
  }
}
//---------------------------------------------------------------------------


//========================================================================================
CMDT_Efuse_Reader_Handle_List::CMDT_Efuse_Reader_Handle_List()
{
  m_efuse_reader_list.clear();
}

//---------------------------------------------------------------------------
CMDT_Efuse_Reader_Handle_List:: ~CMDT_Efuse_Reader_Handle_List()
{
  m_efuse_reader_list.clear();
}
//---------------------------------------------------------------------------
MDT_ERROR_STATUS CMDT_Efuse_Reader_Handle_List::Update(int comport,const CMDT_Efuse_Reader_Handle& efuse_reader_handle)
{
  map<int,CMDT_Efuse_Reader_Handle>::iterator Iter;
  Iter = this->m_efuse_reader_list.find(comport);
  pair<int, CMDT_Efuse_Reader_Handle> Item(comport,efuse_reader_handle);
  
  if ( Iter != m_efuse_reader_list.end())
  {
    m_efuse_reader_list.erase(Iter);
  }
  m_efuse_reader_list.insert(Item);  
  
  return MDT_OK;
}

