/*****************************************************************************
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of MediaTek Inc. (C) 2011
 *
 ****************************************************************************/

/*****************************************************************************
 * Filename:
 * ---------
 *  mdt_efusewriter_cefusewriterfilereader.cpp
 *
 * Project:
 * --------
 *  MDT EFuseWriter
 *
 * Description:
 * ------------
 *  MDT EFuseWriter Config/Lock file base class member function implementation
 *
 * Author:
 * -------
 *  Dongguo Jiang (mtk70823)
 *
 ****************************************************************************/
#include <vcl.h>
#include <windows.h>
#include "efusewriter/inc/mdt_efusewriter_cefusewriterfilereader.h"
#include "mdt_component/error_handler/inc/gctrace.h"

CEFuseWriterFileReader::CEFuseWriterFileReader() {
  this->m_file_name = "";
  this->m_is_parameter_ready = false;
  this->m_p_read_string_buffer= new char[EFUSE_READ_BUFFERSIZE];
}

CEFuseWriterFileReader::~CEFuseWriterFileReader() {
  if (NULL != m_p_read_string_buffer)
  {
    delete m_p_read_string_buffer;
  }
}
/**
 * Set filename which will be parsed.
 *
 * @param SettingFile is the filename which Reader will parse/
 *
 * @return zero for success or non-zero for failure
 */
MDT_ERROR_STATUS CEFuseWriterFileReader::setfile(const AnsiString& SettingFile) {

  HANDLE test_handle;
  WIN32_FIND_DATA   FindFileData;
  test_handle = FindFirstFile(SettingFile.c_str(), &FindFileData);  
  if (INVALID_HANDLE_VALUE == test_handle)
  {
    return MDT_SV5_EFUSE_WRITER_INVALID_FILE;
  }
  else
  {    
	reset();
    FindClose(test_handle);
    this->m_file_name=SettingFile;
  }
  
  if (false == is_valid_file())
  {
    return MDT_SV5_EFUSE_WRITER_INVALID_FILE;
  }
  m_is_parameter_ready = false;
  return MDT_OK;
}

MDT_ERROR_STATUS CEFuseWriterFileReader::getfile(AnsiString* SettingFile)const {

  if(NULL==SettingFile)
  {
    GC_TRACE_EX("Parameter is Invalid");
    return MDT_SV5_EFUSE_WRITER_INVALID_POINTER;
  }  
  *SettingFile=this->m_file_name;
  return MDT_OK;
}

MDT_ERROR_STATUS CEFuseWriterFileReader::reset() {

  this->m_is_parameter_ready=false;
  memset(m_p_read_string_buffer,0x00,EFUSE_READ_BUFFERSIZE);
  return MDT_OK;
}
/**
 * Read integer from file
 *
 * @param Section is the section in file;
 *
 * @param Ident is the identity in file;
 *
 * @param Default is default value;
 *
 * @return integer read from file
 */
int CEFuseWriterFileReader::read_integer(const AnsiString& Section,
                                            const AnsiString& Ident,
                                            const int Default)const {

  int attribute_value;
  attribute_value = GetPrivateProfileInt(Section.c_str(), Ident.c_str(),Default,m_file_name.c_str());
  return attribute_value;
}
int CEFuseWriterFileReader::read_attribute(const AnsiString& section,
							 const AnsiString& ident,
							 const int default_value)const
{
  int attribute_value;
  attribute_value = GetPrivateProfileInt(section.c_str(), ident.c_str(),default_value,m_file_name.c_str());
  if ( 1 == attribute_value )
  {
    return EFUSE_ACTIVE;
  }
  else if ( 0 == attribute_value )
  {
    return EFUSE_NONE;
  }
  else if ( default_value == attribute_value )
  {
    return EFUSE_NONE;
  }
  else
  {
    return EFUSE_NONE;
  }
}
/**
 * Read string from file
 *
 * @param Section is the section in file;
 *
 * @param Ident is the identity in file;
 *
 * @param p_ReadLength will pass length of string
 *
 * @return pointer which point to memory storing string,[NULL means fail]
 */
unsigned char* CEFuseWriterFileReader::read_string(const AnsiString& Section, 
                                                     const AnsiString& Ident,
                                                     const AnsiString& Default,
                                                     unsigned int* p_ReadLength
                                                    )const {
  unsigned int ReadStringLenth;
  unsigned char* pReadString=NULL;
  AnsiString TempString;  
  memset(m_p_read_string_buffer,0x00,EFUSE_READ_BUFFERSIZE);
  
  ReadStringLenth=GetPrivateProfileString(Section.c_str(),
                                          Ident.c_str(),
                                          Default.c_str(),
                                          m_p_read_string_buffer,
                                          EFUSE_READ_BUFFERSIZE,
                                          m_file_name.c_str());
  if((0>=ReadStringLenth)||(EFUSE_READ_BUFFERSIZE<=ReadStringLenth))
  {
  	//this section may be commented Or use select a invalid config file.
  	*p_ReadLength=0;
  	return NULL;
  }
  TempString = (char*)m_p_read_string_buffer;
  if(TempString == Default)
  {
    //this section may be commented Or use select a invalid config file.
    *p_ReadLength = 0;
    return NULL;
  }
  *p_ReadLength = ReadStringLenth;
  pReadString = new char[ReadStringLenth+1];
  memset(pReadString,0x00,ReadStringLenth+1);
  memcpy(pReadString,m_p_read_string_buffer,ReadStringLenth);
  
  return pReadString;
  
}
bool CEFuseWriterFileReader::is_valid_file() {

  return true;
}
//-----------------------------------------------------------------------------


