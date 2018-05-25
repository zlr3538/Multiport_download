#ifndef _EFuseWriterParameter_H__
#define _EFuseWriterParameter_H__

#include "EFuseWriter.h"
#include "brom_dll/inc/brom.h"
//Next code is for fool-proof design
#define EFUSE_WEIRD_CODE 0x5AA5
#define EFUSE_READ_BUFFERSIZE 1024*4

//============================================================================


class TEFuseWriterParameterReader
{

private:
	Efuse_Common_Arg m_common_arg;	  // Global argument for Brom_WriteEfuseCommon		  
	Efuse_Secure_Arg m_secure_arg;	  // Global argument for Brom_WriteEfuseSecure
	Efuse_Lock_Arg m_lock_arg; 	  // Global argument for Brom_WriteEfuseSecure

	AnsiString m_SettingFile;
	AnsiString m_LockFile;
	
	bool m_IsSettingParameterReady;
	bool m_IsLockParameterReady;
	bool m_IsAllParameterReady;

	unsigned char ReadStringBuffer[EFUSE_READ_BUFFERSIZE];

	virtual int ReadIntegerFromSettingFile(const AnsiString Section, const AnsiString Ident, int Default=0);
	virtual int ReadIntegerFromLockFile(const AnsiString Section, const AnsiString Ident, int Default=0);
	
	virtual unsigned char* ReadStringFromSettingFile(
		const AnsiString Section, 
		const AnsiString Ident, 
		AnsiString Default,
		unsigned int* p_ReadLength
	);
	virtual unsigned char* ReadStringFromLockFile(
		const AnsiString Section, 
		const AnsiString Ident, 
		AnsiString Default,
		unsigned int* p_ReadLength
	);

	virtual unsigned short ReadUSBPID();
	virtual unsigned short ReadUSBVID();
	virtual MDT_ERROR_STATUS GetEfuseCommonArg();
	virtual MDT_ERROR_STATUS GetEfuseSecureArg();
	virtual MDT_ERROR_STATUS GetEfuseLockArg();


	
public:
	TEFuseWriterParameterReader();
	~TEFuseWriterParameterReader();
	virtual MDT_ERROR_STATUS SetEFuseWriterSettingFile(const AnsiString& SettingFile);
	virtual MDT_ERROR_STATUS SetEFuseWriterLockFile(const AnsiString& LockFile);

	virtual MDT_ERROR_STATUS CheckSettingLockFile();

	virtual MDT_ERROR_STATUS ParseEFuseWriteParameter();
	virtual MDT_ERROR_STATUS ParseEFuseLockParameter();
	virtual MDT_ERROR_STATUS ParseEFuseWriteLockParameter();

	virtual MDT_ERROR_STATUS GetEFuseWriteLockParameter(
						Efuse_Common_Arg* p_common_arg,		  
						Efuse_Secure_Arg* p_secure_arg,
						Efuse_Lock_Arg* p_lock_arg
	);

	virtual MDT_ERROR_STATUS GetEFuseWriteParameter(
						Efuse_Common_Arg* p_common_arg,
						Efuse_Secure_Arg* p_secure_arg
	);
	virtual MDT_ERROR_STATUS GetEFuseLockParameter( Efuse_Lock_Arg* p_lock_arg);

	#if 0
	//========Caution: Do not use those function unless you know what you are doing=================
	virtual MDT_ERROR_STATUS GetEFuseSettingLockParameter(
						Efuse_Common_Arg** p_p_common_arg,		  
						Efuse_Secure_Arg** p_p_secure_arg,
						Efuse_Lock_Arg** p_p_lock_arg
	);

	virtual MDT_ERROR_STATUS GetEFuseSettingParameter(
						Efuse_Common_Arg** p_p_common_arg,		  
						Efuse_Secure_Arg** p_p_secure_arg
	);
	virtual MDT_ERROR_STATUS GetEFuseLockParameter(	Efuse_Lock_Arg** p_p_lock_arg);
	//======================================================================================
	#endif
	
	virtual MDT_ERROR_STATUS GetSettingLockFilePath(
						AnsiString& SettingFile,
						AnsiString& LockFile
	);

	
	virtual MDT_ERROR_STATUS Clear();
	virtual MDT_ERROR_STATUS ClearSettingParameter();
	virtual MDT_ERROR_STATUS ClearLockParameter();
	
};
extern TEFuseWriterParameterReader* G_EFuseWriterReader;



#endif
