#ifndef _DES_H
#define _DES_H

#include <windows.h>

#define DES_KEY_LEN 8
#define DES_DATA_LEN 64

typedef enum {
  S_DES_SUCCESS,
  S_DES_FAIL,
  S_DDES_FAIL,
  S_DES_DATALEN_TOO_BIG,
  S_DES_KEYLEN_TOO_BIG,
  S_DES_OPEN_FILE_ERROR
}STATUS_DES;

#ifdef __cplusplus
extern "C"
{
#endif

/*
Function Name: WriteDataToFile
Function Description: use DES to encrypt the data then write to file.
intput: 
   data: the data need to be encrypted, data length must be smaller than 64 byte
   datelen: datalen, must smaller than 64 byte
   key: must be 8 byte(64 bit key)
return: 
   S_DES_SUCCESS: indicates success;
   other value: indicates fail, please print the return value when fail
*/
__declspec(dllexport) INT32 __stdcall WriteDataToFile(BYTE *data,INT32 datelen, BYTE *key, char* pcPathBuf);

/*
Function Name: ReadDataFromFile
Function Description: read data from file then decrypt it
intput: 
   data: after calling ReadDataFromFile, then decrypt is saved it to the pointer of data
   datelen: datalen, must smaller than 64 byte
   key: must be 8 byte(64 bit key)
return: 
   S_DES_SUCCESS: indicates success;
   other value: indicates fail, please print the return value when fail
*/
 __declspec(dllexport) INT32 __stdcall ReadDataFromFile(BYTE *data,INT32 datelen, BYTE *key, char* pcPathBuf);

#ifdef __cplusplus
};
#endif

#endif