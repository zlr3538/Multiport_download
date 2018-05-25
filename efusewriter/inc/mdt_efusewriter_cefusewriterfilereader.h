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
 *  mdt_efusewriter_cefusewriterfilereader.h
 *
 * Project:
 * --------
 *  MDT EFuseWriter
 *
 * Description:
 * ------------
 *  MDT EFuseWriter Config/Lock file base class
 *
 * Author:
 * -------
 *  Dongguo Jiang (mtk70823)
 *
 ****************************************************************************/
#ifndef MDT_EFUSEWRITER_CEFUSEWRITERFILEREADER_H_
#define MDT_EFUSEWRITER_CEFUSEWRITERFILEREADER_H_

#include <vcl.h>
#include "mdt_component/error_handler/inc/MDT_ErrorTypes.h"


typedef unsigned short uint16;

#define EFUSE_WEIRD_CODE 0x5AA5
#define EFUSE_READ_BUFFERSIZE 1024*4
// define Efuse Arg magic number
#define EFUSE_ACTIVE    0xA59914B3
#define EFUSE_NONE      0x241C8F6D



/*****************************************************************************
 *MDT EFuseWriter Config/Lock file reader base class
 *
 *
 ****************************************************************************/
class CEFuseWriterFileReader {
 public:
  CEFuseWriterFileReader();
  virtual ~CEFuseWriterFileReader();
  virtual MDT_ERROR_STATUS setfile(const AnsiString& SettingFile);
  virtual MDT_ERROR_STATUS getfile(AnsiString* SettingFile)const;
  virtual MDT_ERROR_STATUS reset();
 protected:
  virtual int read_integer(const AnsiString& section,
                             const AnsiString& ident,
                             const int default_value = 0)const;
  virtual int read_attribute(const AnsiString& section,
                               const AnsiString& ident,
                               const int default_value = 0)const;
  virtual unsigned char* read_string(const AnsiString& Section,
                                       const AnsiString& Ident,
                                       const AnsiString& Default,
                                       unsigned int* p_ReadLength)const;

  virtual MDT_ERROR_STATUS parsefile()=0;
  virtual bool is_valid_file();
  AnsiString m_file_name;
  bool m_is_parameter_ready;
  unsigned char *m_p_read_string_buffer;
};

#endif  // MDT_EFUSEWRITER_CEFUSEWRITERFILEREADER_H_ [build/header guard]
