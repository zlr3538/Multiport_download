/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   ThreadManager.h
 *
 * Project:
 * --------
 *   Multiport download
 *
 * Description:
 * ------------
 *
 *
 * Author:
 * -------
 *  Maobin Guo (mtk80061)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 *

 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

//---------------------------------------------------------------------------
#pragma warning(disable: 4530)

#ifndef _SCATTER_FILE_MANAGER_
#define _SCATTER_FILE_MANAGER_

#include <windows.h>

#include "LinkMapFileManager/inc/GCFileFinder.h"
#include "MDT_Component/error_handler/inc/GCGetLastErr.h"
#include "brom_dll/inc/flashtool_handle.h"
#include "multiport_common.h"
#include "ConfigFileSearcher.h"

#include "brom_dll/inc/rom_setting.h"

using namespace std;


typedef unsigned long size_type;


//--------------
class MDT_slight_exception
{
public:

	MDT_slight_exception(const string & wath)
		{ _what = wath;};

	MDT_slight_exception(){};

	virtual ~MDT_slight_exception(){};

	virtual string what() const
		{return _what;}

protected:

	string  _what;
};

//------------------------------------
//ScatterFileSearcher
class  ScatterFileSearcher:public GCFileFinder
{
public:

	ScatterFileSearcher(){};
	~ScatterFileSearcher(){};

private:
   bool IsTargetFile(const string& file);
};


class SecRO
{
public:

    SecRO():m_path(""),m_scatter(""),m_len(0),m_p_data(NULL)
    {};

    ~SecRO()
    {
      free_buf();
    }

    void clear()
    {
       m_path = "";
       m_len = 0;
       free_buf();
    }

    bool load();

    void un_load(){free_buf();};

    bool is_enable(){return m_p_data != NULL;};

    bool empty(){return (m_p_data == NULL);};

    string get_path(){return m_path;};
    void set_path(string sec_ro){m_path = sec_ro;}

    void set_scatter(string scatter){m_scatter = scatter;};
    string get_scatter(void){return m_scatter;};

    unsigned int get_len(){return m_len;};

    unsigned char * get_buf(){return m_p_data;};

private:

    void free_buf()
    {
       if(m_p_data != NULL)
       {
          free(m_p_data);
          m_p_data = NULL;
       }
    };

	string	m_path;
	unsigned int	m_len;
	unsigned char*	m_p_data;
	string	m_scatter;
};


//------------------------------------
//ScatterFileManager  definition
//------------------------------------



class Image
{
public:
   bool is_checked;
   string name;
   string path;

   string to_string();

   void from_string(string str);
};

typedef vector<Image>  image_info;

//=============================================================================================
typedef struct S_MAUI_LoadHandle
{
public:
	S_MAUI_LoadHandle()
	{
		memset(&m_romSetting,0x00,sizeof(ROMSetting));
		m_dl_handle=NULL;
	}

	ROMSetting m_romSetting;
	DL_HANDLE_T* m_dl_handle;
}MAUI_LoadHandle;

class CLinkMapFile
{
public:
	CLinkMapFile(GCFileFinder* FileFinder=NULL,DL_HANDLE_LIST_T* downloadHandleList=NULL,CINIFileHandle* IniFileHandler=NULL)
	{
		m_AvailableFileFinder=FileFinder;
		m_DownloadHandleList=downloadHandleList;
		m_IniFileHandler=IniFileHandler;
		m_RootFolderPath="";
		m_TargetHandleMap.clear();
	}


	~CLinkMapFile(){}

protected:
	string m_RootFolderPath;
	map<string, MAUI_LoadHandle> m_TargetHandleMap;

	//Take Care: Next three pointers is very dangerous
	GCFileFinder *m_AvailableFileFinder;
	DL_HANDLE_LIST_T* m_DownloadHandleList;
	CINIFileHandle* m_IniFileHandler;

public:
	virtual bool clear();
	virtual int getTargetFileNumber(){return m_TargetHandleMap.size();};
	virtual void getLoadedTargetFilePath(vector<string> &paths);

	virtual void save_to_ini();
	virtual bool config_from_ini();
	virtual void set_last_error(MDT_ERROR_STATUS err);
	virtual bool searchTargetFile(const string& folder_path);
	virtual	bool loadAllTargetFiles();

	virtual void read_info_from_ini();
	virtual void loadAllTargetFilesFromIni();
	virtual	bool loadTargetFileFromIni(string& ScatterFile);

	virtual void loadExternalMemorySetting(struct ExternalMemorySetting *externalMemorySetting)
	{

	}

	virtual void SetRootFolderPath(string& RootFolderPath)
	{
		m_RootFolderPath=RootFolderPath;
	}


	virtual	bool loadTargetFile(string& ScatterFile)
	{
		return true;
	}
	virtual bool gather_load_info(map<string, MAUI_LoadHandle> &LoadInfo)
	{
		return true;
	}
	virtual	bool update_load(map<string, MAUI_LoadHandle> &LoadInfo)
	{
		return true;
	}

	virtual const SecRO* get_sec_ro()
	{
	  return NULL;
	}
	virtual bool IsWithSecureRO()
	{
	  return false;
	}
	virtual bool Destroy_DLHandle(DL_HANDLE_T *p_dl_handle);
};

//------------------------------------
//ScatterFileManager
class  ScatterFileManager:public CLinkMapFile
{
public:

	ScatterFileManager(DL_HANDLE_LIST_T* p_DownloadHandleList=NULL,CINIFileHandle* IniFileHandle=NULL)
		:CLinkMapFile(&m_ScatterFileSearcher,p_DownloadHandleList,IniFileHandle)
	{
		m_sec_ro.clear();
	};

	~ScatterFileManager(){};
	virtual bool clear();

	bool gather_load_info(map<string, MAUI_LoadHandle> &LoadInfo);
	bool update_load(map<string, MAUI_LoadHandle> &LoadInfo);
protected:
	//SV5 load do not include Secure RO.
	//All download handle share one secure_ro!
	SecRO           m_sec_ro;

private:
//	bool search_scatter_files(string folder);
	bool loadTargetFile(string& ScatterFile);

	virtual const SecRO* get_sec_ro()
	{
	  return &m_sec_ro;
	}
	virtual bool IsWithSecureRO()
	{
	  if(m_sec_ro.empty())
	  {
	    return false;
	  }
	  else
	  {
        return true;
	  }
	}

	bool load_bootloader(string scatter, DL_HANDLE_T  dl_handle);
	bool load_SEC_RO(string scatter_file);
	bool is_with_SEC_RO(string scatter_file, string &sec_ro);
	bool check_image(string scatter_file, DL_HANDLE_T  dl_handle);
	bool check_ROM(string scatter_file, DL_HANDLE_T  dl_handle);
	bool check_Bootloader(string scatter_file, BL_INFO bl_info, DL_HANDLE_T  dl_handle);
	void loadExternalMemorySetting(struct ExternalMemorySetting *externalMemorySetting);
	ScatterFileSearcher m_ScatterFileSearcher;

};

class ConfigFileManager:public CLinkMapFile
{
public:
	ConfigFileManager(DL_HANDLE_LIST_T* p_DownloadHandleList=NULL,CINIFileHandle* IniFileHandle=NULL)
		:CLinkMapFile(&m_ConfigFileSearcher,p_DownloadHandleList,IniFileHandle)
	{

	}
	~ConfigFileManager()
	{

	}


protected:
	ConfigFileSearcher m_ConfigFileSearcher;
	void loadExternalMemorySetting(struct ExternalMemorySetting *externalMemorySetting);

	virtual bool gather_load_info(map<string, MAUI_LoadHandle> &LoadInfo);
	virtual bool loadTargetFile(string& ScatterFile);
};

//---------------------------------------------------------------------------
#endif    //_THREAD_MANAGER_H_
