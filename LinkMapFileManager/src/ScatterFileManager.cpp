
#pragma hdrstop

#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

#include "form/mainform/MultiPortFlashDownloadTool.h"
#include "LinkMapFileManager/inc/ScatterFileManager.h"
#include "mdt_component/error_handler/inc/GCTrace.h"
#include "form/InputImageDlgForm/InputImageDlg.h"
#include "brom_dll/inc/flashtool_handle.h"

extern DL_HANDLE_T             *g_pDL_HANDLE[MAX_SUPPORT_LOAD_NUM+1];
extern DL_HANDLE_LIST_T        g_DL_HANDLE_LIST;
extern PACKAGE TMainForm       *MainForm;
extern TfrmInputImage *frmInputImage;
extern ROOTCERT_HANDLE_T  g_ROOTCERT_HANDLE_DL;
extern bool g_is_Root_Cert_File_In_Download_Handle;

struct push_back_file : public unary_function<string, void>
{
    push_back_file(vector<string> *p_v){m_p_v = p_v;};

    vector<string> *m_p_v;

    void operator()(string x) { m_p_v->push_back(x); };
};






//scatMT6235B_EVB.txt
bool ScatterFileSearcher::IsTargetFile(const string& file)
{
    //First condition -- scatter file's type is txt file
    //size_type pos = file.find_first_of(".txt");

	string FileName=file;

	//To Upper case
	transform(FileName.begin(), FileName.end(), FileName.begin(), toupper);

    if(FileName.size() < 8)
    {
        return false;
    }

    if(FileName.compare(FileName.size()-4, 4, ".TXT") != 0)
    {
        return false;
    }

    //Second condition -- begin with  scat
    if(FileName.compare(0, 4, "SCAT") != 0)
    {
        return false;
    }

    return true;

}




bool ScatterFileManager::gather_load_info(map<string, MAUI_LoadHandle> &LoadInfo)
{
#if 0
    unsigned short rom_count;
    ROM_INFO       rom_info[MAX_LOAD_SECTIONS];
    vector<unsigned short> need_manual_input;
    int mtk_status;
    string scatter;
    DL_HANDLE_T p_dl_handle;
    _BOOL is_nfb;
	int HandleCounter;

	mtk_status=DL_GetHandleNumber(*m_DownloadHandleList,&HandleCounter);
	if (S_DONE != mtk_status)
	{
		GC_TRACE("clear::DL_GetHandleNumber Error: %d",mtk_status);
		return false;
	}


	for(int index=HandleCounter-1;index>=0;index--)
	{
		mtk_status=DL_GetHandle(*m_DownloadHandleList,index,&p_dl_handle);
		if (S_DONE != mtk_status)
		{
			GC_TRACE("clear::DL_GetHandleNumber Error: %d",mtk_status);
			continue;
		}

        image_info  info;

        mtk_status = DL_IsNFB(p_dl_handle, &is_nfb);

        if(is_nfb)
        {
            BL_INFO   bl_info;

            mtk_status = DL_BL_GetInfo(p_dl_handle, &bl_info);

            if (S_DONE != mtk_status)
            {
                Destroy_DLHandle(&p_dl_handle);
                clear();
                GC_TRACE("SFM::gather_load_info get BL info fail , err code %d", mtk_status);
                return false;
            }

            {
                //Set BL info
                Image  image;

                image.name = "Bootloader";
                image.path = bl_info.m_filepath;
                image.is_checked =  bl_info.m_enable;

                info.push_back(image);
            }

            if(bl_info.m_ext_bootloader_exist)
            {
                Image  image;

                image.name = "Ext_bootloader";
                image.path = bl_info.m_ext_filepath;
                image.is_checked =  bl_info.m_enable;

                info.push_back(image);
            }

        }

        //Sec RO
        if(m_sec_ro.get_scatter() == scatter)
        {
            //if current scatter with Sec RO
            Image  image;

            image.name = "SEC_RO";
            image.path = m_sec_ro.get_path();
            image.is_checked =  m_sec_ro.is_enable();

            info.push_back(image);
        }

        //Load other files
        mtk_status = DL_GetCount(p_dl_handle, &rom_count);
        if(S_DONE != mtk_status)
        {
            set_last_error(MDT_GET_LOADED_ROM_COUNT_FAIL);
            GC_TRACE("gather_load_info::%s , err code %d", MDT_GET_LOADED_ROM_COUNT_FAIL, mtk_status);
            return false;
        }

        if(rom_count>MAX_LOAD_SECTIONS)
        {
            GC_TRACE("gather_load_info::MDT_GET_TOO_MANY_ROM");
            set_last_error(MDT_GET_TOO_MANY_ROM);
            return false;
        }

        mtk_status = DL_Rom_GetInfoAll(p_dl_handle, rom_info, MAX_LOAD_SECTIONS);
        if(S_DONE != mtk_status)
        {
            set_last_error(MDT_GET_ROM_INFO_ALL_FAIL);
            GC_TRACE("gather_load_info::%s , err code %d", MDT_GET_ROM_INFO_ALL_FAIL, mtk_status);
            return false;
        }

        for(unsigned short i=0; i<rom_count; i++)
        {
            Image  image;

            image.name       = rom_info[i].name;
            image.path       = rom_info[i].filepath;
            image.is_checked = rom_info[i].enable;

            info.push_back(image);
        }

        image_infos.insert(map<string, image_info>::value_type(scatter, info));
    }

    return true;
#else
	LoadInfo=m_TargetHandleMap;
	return true;
#endif
}


struct find_image_by_name
{
    find_image_by_name(string name) : _name(name){};

    bool operator()(Image img){
        return _name == img.name;
    }

    string _name;
};
bool ScatterFileManager::update_load(map<string, MAUI_LoadHandle> &LoadInfo)
{
#if 0
	unsigned short rom_count;
	ROM_INFO       rom_info[MAX_LOAD_SECTIONS];
	vector<unsigned short> need_manual_input;
	int mtk_status;
	string scatter;

	DL_HANDLE_T p_dl_handle;
	_BOOL is_nfb;
	int HandleCounter;

	mtk_status=DL_GetHandleNumber(*m_DownloadHandleList,&HandleCounter);
	if (S_DONE != mtk_status)
	{
		GC_TRACE("clear::DL_GetHandleNumber Error: %d",mtk_status);
		return false;
	}


	for(int index=HandleCounter-1;index>=0;index--)
	{
		mtk_status=DL_GetHandle(*m_DownloadHandleList,index,&p_dl_handle);
		if (S_DONE != mtk_status)
		{
			GC_TRACE("clear::DL_GetHandleNumber Error: %d",mtk_status);
			continue;
		}


	    image_info  info;
	    image_info::iterator it_info;
	    Image image;


	    //Find Scatter fail name
	    if(m_TargetHandleMap.end() != m_TargetHandleMap.find(&p_dl_handle))
	    {
	        scatter = (*m_TargetHandleMap.find(&p_dl_handle)).second;
	    }
	    else
	    {
	        GC_TRACE("Search scatter file name fail!");
	        continue;
	    }

	    //Find image info fail
	    if(image_infos.end() != image_infos.find(scatter))
	    {
	        info = (*image_infos.find(scatter)).second;
	    }
	    else
	    {
	        GC_TRACE("Image info fail.");
	        continue;
	    }

	    //Query flash type
	    mtk_status = DL_IsNFB(p_dl_handle, &is_nfb);
	    if (S_DONE != mtk_status)
	    {
	        Destroy_DLHandle(&p_dl_handle);
	        clear();
	        GC_TRACE("SFM::update_load query is NFB fail , err code %d", mtk_status);
	        return false;
	    }

	    //Load bootloade (For NAND(NFB) Flash)
	    if(is_nfb)
	    {
	        BL_INFO   bl_info;

	        mtk_status = DL_BL_GetInfo(p_dl_handle, &bl_info);

	        if (S_DONE != mtk_status)
	        {
	            Destroy_DLHandle(&p_dl_handle);
	            clear();
	            GC_TRACE("SFM::gather_load_info get BL info fail , err code %d", mtk_status);
	            return false;
	        }

	        {
	            //Set BL info
	            it_info = find_if(info.begin(), info.end(), find_image_by_name("Bootloader"));
	            if(it_info == info.end())
	            {
	                GC_TRACE("Find image fail.");
	                continue;
	            }

	            if((*it_info).path != bl_info.m_filepath)
	            {
	                DL_BL_Load(p_dl_handle, (*it_info).path.c_str());
	            }

	            if((*it_info).is_checked !=  bl_info.m_enable)
	            {
	                DL_BL_SetEnableAttr(p_dl_handle, (_BOOL)((*it_info).is_checked));
	            }

	        }

	        //Update Extension bootloader
	        if(bl_info.m_ext_bootloader_exist)
	        {
	            it_info = find_if(info.begin(), info.end(), find_image_by_name("Ext_bootloader"));
	            if(it_info == info.end())
	            {
	                GC_TRACE("Find image fail.");
	                continue;
	            }

	            if((*it_info).path != bl_info.m_ext_filepath)
	            {
	                DL_BL_EXT_Load(p_dl_handle, (*it_info).path.c_str());
	            }
	        }

	    }

	    //Sec RO
	    if(m_sec_ro.get_scatter() == scatter)
	    {
	        //if current scatter with Sec RO
	        it_info = find_if(info.begin(), info.end(), find_image_by_name("SEC_RO"));
	        if(it_info == info.end())
	        {
	            GC_TRACE("Find image fail.");
	            continue;
	        }

	        if((*it_info).path != m_sec_ro.get_path())
	        {
	            m_sec_ro.set_path((*it_info).path);
	        }

	        if((*it_info).is_checked != m_sec_ro.is_enable())
	        {
	            if((*it_info).is_checked)
	                m_sec_ro.load();
	            else
	                m_sec_ro.un_load();
	        }
	    }

	    //ROMs
	    mtk_status = DL_GetCount(p_dl_handle, &rom_count);
	    if(S_DONE != mtk_status)
	    {
	        set_last_error(MDT_GET_LOADED_ROM_COUNT_FAIL);
	        GC_TRACE("SFM::%s , err code %d", MDT_GET_LOADED_ROM_COUNT_FAIL, mtk_status);
	        return false;
	    }

	    if(rom_count>MAX_LOAD_SECTIONS)
	    {
	        set_last_error(MDT_GET_TOO_MANY_ROM);
	        return false;
	    }

	    mtk_status = DL_Rom_GetInfoAll(p_dl_handle, rom_info, MAX_LOAD_SECTIONS);
	    if(S_DONE != mtk_status)
	    {
	        set_last_error(MDT_GET_ROM_INFO_ALL_FAIL);
	        GC_TRACE("SFM::%s , err code %d", MDT_GET_ROM_INFO_ALL_FAIL, mtk_status);
	        return false;
	    }

	    for(unsigned short i=0; i<rom_count; i++)
	    {
	        //Search right Image
	        it_info = find_if(info.begin(), info.end(), find_image_by_name(rom_info[i].name));
	        if(it_info == info.end())
	        {
	            GC_TRACE("Find image fail.");
	            continue;
	        }

	        //Get right image
	        image = *it_info;

	        //check is checked mark
	        if(image.is_checked != rom_info[i].enable)
	        {
	            DL_Rom_SetEnableAttr(p_dl_handle, i, (_BOOL)(image.is_checked));
	        }

	        //check path
	        if(0 != strcmp(rom_info[i].filepath, image.path.c_str()))
	        {
	            DL_Rom_Unload(p_dl_handle, i);
	            DL_Rom_Load(p_dl_handle, i, image.path.c_str());
	        }
	    }
	}

	return true;
#else
	return true;
#endif
}

/*
bool ScatterFileManager::search_scatter_files(string folder)
{
	{
		WIN32_FIND_DATA find_data;
		HANDLE hFind;
		bool bIsDirectory;
		string file_name, file_path, search_path;
		search_path = folder + "\\*.*";
		bool isFindValidFile=false;


		if(INVALID_FILE_ATTRIBUTES==GetFileAttributes(folder.c_str()))
		{
			set_last_error(MDT_INVALID_FOLDER_PATH);
	        return false;
		}

		hFind = FindFirstFile(search_path.c_str(), &find_data);
		if (hFind == INVALID_HANDLE_VALUE)
		{
			FindClose(hFind);
			return false;
		}


		bIsDirectory = ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
		file_name = find_data.cFileName;

		if(!bIsDirectory)
		{
			m_AvailableFileFinder=&m_ConfigFileSearcher;
			if(true==m_AvailableFileFinder->search(folder))
			{
				isFindValidFile=true;
			}
			else
			{
				m_AvailableFileFinder=&m_ScatterFileSearcher;
				if(true==m_AvailableFileFinder->search(folder))
				{
					isFindValidFile=true;
				}
			}
		}
		else
		{
		   if((".." != file_name) && ("." != file_name))
		   {
			  file_path = folder + "\\";
			  file_path += find_data.cFileName;
			  search_scatter_files(file_path);
		   }
		}

		//For Find next file
		while(FindNextFile(hFind, &find_data))
		{
			bIsDirectory = ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
			file_name = find_data.cFileName;

			if(!bIsDirectory)
			{
				if(false==isFindValidFile)
				{
					m_AvailableFileFinder=&m_ConfigFileSearcher;
					if(true==m_AvailableFileFinder->search(folder))
					{
						isFindValidFile=true;
					}
					else
					{
						m_AvailableFileFinder=&m_ScatterFileSearcher;
						if(true==m_AvailableFileFinder->search(folder))
						{
							isFindValidFile=true;
						}
					}
				}
			}
			else
			{
				if((".." != file_name) && ("." != file_name))
				{
				  file_path = folder + "\\";
				  file_path += find_data.cFileName;
				  search_scatter_files(file_path);
				}
			}
		}

		FindClose(hFind);
		//do not find target file~
		return true;
	}

    if((m_scatter_files.empty())||(m_config_files.empty()))
    {
        set_last_error(MDT_NONE_SCATTER_IS_FOUND);
        return false;
    }

    if((m_scatter_files.size() > MAX_SUPPORT_LOAD_NUM)||(m_config_files.size() > MAX_SUPPORT_LOAD_NUM))
    {
        set_last_error(MDT_TOO_MANY_SCATTER_FILE);
        return false;
    }

    return true;
}

*/

/*
bool ScatterFileManager::load_scatter_files()
{
    vector<string>::iterator it;

    for(it = m_scatter_files.begin(); it != m_scatter_files.end(); it++)
    {
        if(!load_scatter_file(*it, distance(m_scatter_files.begin(), it)))
        {
            return false;
        }
    }

    return true;
}
*/

bool ScatterFileManager::loadTargetFile(string& ScatterFile)
{

	{
		int mtk_status;
		_BOOL is_nfb = _FALSE;

		map<string, MAUI_LoadHandle>::iterator iter;

		iter=m_TargetHandleMap.find(ScatterFile);
		if(iter==m_TargetHandleMap.end())
		{
			GC_TRACE("ScatterFileManager::loadTargetFile==>Can not find: %s", ScatterFile.c_str());
			throw MDT_SEARCH_SCATTER_ERROR;
		}

		string path=iter->first;

		GC_TRACE("ScatterFileManager::loadTargetFile==>loading scatter file %s", path.c_str());

		DL_HANDLE_T* p_dl_handle = new DL_HANDLE_T;
		BL_INFO BootloaderInfo;

		//Create Download handle
		mtk_status = DL_Create(p_dl_handle);
		if(S_DONE != mtk_status)
		{
			GC_TRACE("ScatterFileManager::loadTargetFile==>load_scatter_file Create DL handle fail, err code %d", mtk_status);
			throw string("Create DL handle fail");
		}

		//Load scatter file
		mtk_status = DL_LoadScatter(*p_dl_handle, path.c_str());
		if (S_DONE != mtk_status)
		{
		    GC_TRACE("ScatterFileManager::loadTargetFile==>load_scatter_file load scatter file fail , err code %d", mtk_status);
			throw string("load scatter file fail");
		}

		//Load ROMs
		mtk_status = DL_AutoLoadByScatRegionName(*p_dl_handle, path.c_str(), NORMAL_ROM|RESOURCE_BIN|JUMPTABLE_BIN, _TRUE);
		if (S_DONE != mtk_status)
		{
		    GC_TRACE("ScatterFileManager::loadTargetFile==>load_scatter_file Automatic load by scatter region name fail , err code %d", mtk_status);
			throw string("Automatic load by scatter region name fail");
		}

		if(!check_ROM(path, *p_dl_handle))
		{
		    GC_TRACE("Check Image fail!");
		    throw MDT_CAN_NOT_LOAD_ALL_IMAGES;
		}
		//Modified for secure usb download on 2011.01.06

		mtk_status=DL_BL_IsReady(*p_dl_handle,&BootloaderInfo,_FALSE);
		if(S_DONE==mtk_status)
		{
			mtk_status = DL_IsNFB(*p_dl_handle, &is_nfb);
			if(is_nfb)
		    {
		        if(!load_bootloader(path, *p_dl_handle))
		        {
		            GC_TRACE("ScatterFileManager::loadTargetFile==>load_scatter_file load bootloader fail , err code %d", mtk_status);
		            throw MDT_LOAD_EXTENSION_BOOTLOADER_FAIL;
		        }
		    }

		}
		else
		{

		}

		//Sec RO
		if(!load_SEC_RO(path))
		{
		    GC_TRACE_EX("load SEC RO fail");
		    throw string("More than one Secure_RO exist.");
		}

		//Record handle
		if(NULL == m_DownloadHandleList)
		{
		    GC_TRACE("MDT_SAME_FLASHID_AND_BBCHIP_SW_VER");
			throw string("m_DownloadHandleList is invalid pointer");
		}

		mtk_status = DL_AddHandleToList( *m_DownloadHandleList, *p_dl_handle );
		if(S_DONE != mtk_status)
		{
		    GC_TRACE("ScatterFileManager::loadTargetFile==>Add download handle to handle list fail , err code %d", mtk_status);
			throw string("Add dl handle to handle_list fail: May be a same load in list.");
		}
		iter->second.m_dl_handle=p_dl_handle;

		//Other setting
		//Default Value is 4K Bytes~~
		DL_SetPacketLength(*p_dl_handle, 4096);  //Set packet length
		DL_ResourceProjectIdComparisonSetting(*p_dl_handle, _TRUE);

		return true;
	}

}



bool ScatterFileManager::is_with_SEC_RO(string scatter_file, string &sec_ro/*path*/)
{
    HANDLE   test_handle = INVALID_HANDLE_VALUE;
    bool     ret;

    try
    {
        sec_ro = scatter_file.substr(0, scatter_file.rfind('\\')) + "\\SECURE_RO";

        test_handle = CreateFile(sec_ro.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        ret = (test_handle != INVALID_HANDLE_VALUE);

        GC_TRACE("%s find SEC_RO image.", (ret ? "" : "Not"));

        CloseHandle(test_handle);

        return ret;
    }
    catch(...)
    {
        if(INVALID_HANDLE_VALUE != test_handle )
        {
            CloseHandle(test_handle);
        }
        set_last_error(MDT_UNKNOW_ERROR);
        return false;
    }
}


//---------------------------------------------------------------------------
bool ScatterFileManager::load_SEC_RO(string scatter_file)
{
    string sec_ro;
    unsigned char ** pp_data;
    unsigned int	 len;

    if(!is_with_SEC_RO(scatter_file, sec_ro))
    {
        //without sec ro is normal
        GC_TRACE_EX("Load is not with Secure Ro");
        return true;
    }

    //Only accept one scatter file with SEC RO
    if(!m_sec_ro.empty())
    {
        //already load sec_ro
        GC_TRACE_EX("Already exist Secure RO,More than one.");
        set_last_error(MDT_MORE_THAN_ONE_SEC_RO);
        return false;
    }

    //Set path
    m_sec_ro.set_path(sec_ro);

    m_sec_ro.set_scatter(scatter_file);

    //Load SEC RO: Secure USB DL
    if(!m_sec_ro.load())
    {
        set_last_error(MDT_LOAD_SEC_RO_FILE_FAIL);
        return true;
    }

    //Record info
    GC_TRACE("Load SEC_RO image %s.", sec_ro);

    return true;
}

//---------------------------------------------------------------------------
bool ScatterFileManager::check_ROM(string scatter_file, DL_HANDLE_T  dl_handle)
{
    unsigned short rom_count;
    ROM_INFO       rom_info[MAX_LOAD_SECTIONS];
    vector<unsigned short> need_manual_input;
    int mtk_status;

    mtk_status = DL_GetCount(dl_handle, &rom_count);
    if(S_DONE != mtk_status)
    {
        set_last_error(MDT_GET_LOADED_ROM_COUNT_FAIL);
        GC_TRACE("SFM::%s , err code %d", MDT_GET_LOADED_ROM_COUNT_FAIL, mtk_status);
        return false;
    }

    if(rom_count>MAX_LOAD_SECTIONS)
    {
        set_last_error(MDT_GET_TOO_MANY_ROM);
        return false;
    }

    mtk_status = DL_Rom_GetInfoAll(dl_handle, rom_info, MAX_LOAD_SECTIONS);
    if(S_DONE != mtk_status)
    {
        set_last_error(MDT_GET_ROM_INFO_ALL_FAIL);
        GC_TRACE("SFM::%s , err code %d", MDT_GET_ROM_INFO_ALL_FAIL, mtk_status);
        return false;
    }

    for(unsigned short i=0; i<rom_count; i++)
    {
        //Check is this ROM loaded
        if(strlen(rom_info[i].filepath) == 0)
        {
            GC_TRACE("SFM::ROM %s not loaded, need user input manually.", rom_info[i].name);
            need_manual_input.push_back(i);
        }
    }

    //List Loaded ROM
    DL_Rom_GetInfoAll(dl_handle, rom_info, MAX_LOAD_SECTIONS);
    GC_TRACE("");
    GC_TRACE("=============== ROM LOAD REPORT =============");
    GC_TRACE("Scatter File: %s", scatter_file.c_str());
    for(int i=0; i<rom_count; i++)
    {
        GC_TRACE("[%s] [%s] [%s]",
            (rom_info[i].enable ? "Enable" : "Disable"),
            rom_info[i].name,
            rom_info[i].filepath);
    }

    return true;
}

//---------------------------------------------------------------------------
bool ScatterFileManager::check_image(string scatter_file, DL_HANDLE_T  dl_handle)
{
    if(!check_ROM(scatter_file, dl_handle))
    {
        return false;
    }

    return true;
}


//---------------------------------------------------------------------------
bool ScatterFileManager::check_Bootloader(string scatter_file,
                                          BL_INFO bl_info,
                                          DL_HANDLE_T  dl_handle)
{
    bool is_need_manual_input = false;
    BL_INFO *p_bl_info = &bl_info;

    if(0 == strlen(p_bl_info->m_filepath))
    {
        is_need_manual_input = true;
    }
    if((0 == strlen(p_bl_info->m_ext_filepath)) && (p_bl_info->m_ext_bootloader_exist))
    {
        is_need_manual_input = true;
    }

    if(false == is_need_manual_input)
    {
        // all needed bootloader is loaded
        return true;
    }

    //else manual input bootloader
    //return let_user_input_bootloader(scatter_file, &bl_info, dl_handle);
    return true;

}

void ScatterFileManager::loadExternalMemorySetting(struct ExternalMemorySetting *externalMemorySetting)
{
    GC_TRACE_EX("Unsupported operation.Do nothing...");
}

//---------------------------------------------------------------------------
bool ScatterFileManager::load_bootloader(string scatter, DL_HANDLE_T  dl_handle)
{
    BL_INFO bl_info;
    int mtk_status;
    bool is_need_manual_input = false;

    //Get bootloader info
    mtk_status = DL_BL_GetInfo(dl_handle, &bl_info);
    if(S_DONE != mtk_status)
    {
        //give user a oppotunity to input bootloader file manually
        strcpy(bl_info.m_filepath, "");
        strcpy(bl_info.m_ext_filepath, "");
        bl_info.m_ext_bootloader_exist = _FALSE;

        mtk_status = DL_BL_GetInfo(dl_handle, &bl_info);
        if(S_DONE != mtk_status)
        {
            set_last_error(MDT_GET_BOOTLOADER_INFO_FAIL);
            GC_TRACE("SFM::Get bootloader info fail , err code %d", mtk_status);
            return false;
        }
    }

    // Load basic bootloader
    mtk_status = DL_BL_Load(dl_handle, bl_info.m_filepath);
    if( S_DONE != mtk_status )
    {
        //set_last_error(SFM_LOAD_BOOTLOADER_FAIL);
        GC_TRACE("SFM::Load basic bootloader fail , err code %d", mtk_status);
        is_need_manual_input = true;
    }

    // Load extension bootloader
    if(bl_info.m_ext_bootloader_exist)
    {
        mtk_status = DL_BL_EXT_Load(dl_handle, bl_info.m_ext_filepath);
        if ( S_DONE != mtk_status)
        {
            set_last_error(MDT_LOAD_EXTENSION_BOOTLOADER_FAIL);
            GC_TRACE("SFM::Load extension bootloader fail , err code %d", mtk_status);
            is_need_manual_input = true;
        }
    }

    // Enable bootloader
    mtk_status = DL_BL_SetEnableAttr( dl_handle, _TRUE );
    if( S_DONE != mtk_status )
    {
        set_last_error(MDT_ENABLE_BOOTLOADER_FAIL);
        GC_TRACE("SFM::Enable bootloader fail , err code %d", mtk_status);
        return false;
    }

    DL_BL_GetInfo(dl_handle, &bl_info);
    GC_TRACE("========SFM::Query bootloader info success=======");
    GC_TRACE("[%s] [Bootloader] [%s]", (bl_info.m_enable ? "Enable" : "Disable"), bl_info.m_filepath);
    GC_TRACE("[%s] [Extension bootloader] [%s]", (bl_info.m_ext_bootloader_exist ? "With" : "Without"), bl_info.m_ext_filepath);

    (void)is_need_manual_input; //not used
    return true;
}

bool ScatterFileManager::clear()
{
	int HandleCounter;
	DL_HANDLE_T TempHandle;
	int mtk_status;
	GC_TRACE("Scatter File::clear");

	m_RootFolderPath="";

	if(0>=m_TargetHandleMap.size())
	{
		GC_TRACE("CLinkMapFile::clear==>m_TargetHandleMap.size()==0");
		return true;
	}
	m_TargetHandleMap.clear();


	mtk_status=DL_GetHandleNumber(*m_DownloadHandleList,&HandleCounter);
	if (S_DONE != mtk_status)
	{
		GC_TRACE("clear::DL_GetHandleNumber Error: %d",mtk_status);
	}


	for(int index=HandleCounter-1;index>=0;index--)
	{
		mtk_status=DL_GetHandle(*m_DownloadHandleList,index,&TempHandle);
		if (S_DONE != mtk_status)
		{
			GC_TRACE("clear::DL_GetHandleNumber Error: %d",mtk_status);
			continue;
		}
		mtk_status=DL_DeleteHandleFromList(*m_DownloadHandleList,TempHandle);
		if (S_DONE != mtk_status)
		{
			GC_TRACE("clear::DL_DeleteHandleFromList Error: %d",mtk_status);
			continue;
		}
		if (!Destroy_DLHandle(&TempHandle))
		{
			GC_TRACE("CLinkMapFile::clear==>Destroy_DLHandle Error");
			continue;
		}
		GC_TRACE("CLinkMapFile::clear==>Unload Dl Hanlde OK");
	}
    m_sec_ro.clear();

	return true;
}



bool SecRO::load()
{
    FILE *fp;
    struct _stat  file_stat={0};

    if(m_path.empty())
    {
        return false;
    }

    free_buf();

    fp = fopen(m_path.c_str(), "rb");

    if( NULL == fp )
    {
        clear();
        return false;
    }

    if( _fstat(fileno(fp), &file_stat) )
    {
        clear();
        return false;
    }

    if( 0 >= (m_len=filelength(fileno(fp))) )
    {
        clear();
        return false;
    }

    if( 0 != (m_len%2) )
    {
        m_len = m_len+1;
    }
    else
    {
        m_len = m_len;
    }

    if( NULL == (m_p_data=(unsigned char *)malloc(m_len)) )
    {
        clear();
        return false;
    }

    if( m_len > fread(m_p_data, 1, m_len, fp) )
    {
        clear();
        return false;
    }

    return true;
}

//$ is seperate
string Image::to_string()
{
    string  str;

    //Save checked info
    str = is_checked ? "true" : "false";
    str += "$";

    //Save name info
    str += name;
    str += "$";

    str += path;

    return str;
}

//config a image object from string
void Image::from_string(string str)
{
    string str_checked;

    //Get checked
    str_checked = str.substr(0, str.find("$"));
    str.erase(0, str.find("$")+1);
    this->is_checked = ("true" == str_checked) ? true : false;

    //get name
    this->name = str.substr(0, str.find("$"));
    str.erase(0, str.find("$")+1);

    //get path
    this->path = str;
}



//============================================================================================
bool CLinkMapFile::loadAllTargetFiles()
{
    map<string, MAUI_LoadHandle>::iterator it;
    bool ret_value;
    try
    {
        for(it = m_TargetHandleMap.begin(); it != m_TargetHandleMap.end(); it++)
        {
            ret_value = loadTargetFile(it->first);
        }
        return ret_value;
    }
    catch(...)
    {
        m_TargetHandleMap.erase(it);
        throw;
    }
}

void CLinkMapFile::read_info_from_ini()

{

#if 0
	int scat_load_num;
	vector<string> &scat_files;
	pair<string, MAUI_LoadHandle> TargetHaneleItem;

	if(NULL==m_IniFileHandler)
	{
		throw (int)MDT_INI_FILE_IS_INVALID;
	}

	//resize scatter file num
	int scat_file_num = atoi(m_IniFileHandler->read_sactter_file_num().c_str());
	if(0==scat_file_num)
	{
		return;
	}

	//gather scatter file names
	m_IniFileHandler->read_sactter_files_path(scat_file_num, scat_files);

	for(vector<string>::iterator it=scat_files.begin(); it != scat_files.end(); it++)
	{
		TargetHaneleItem.first=*it;
		TargetHaneleItem.second.m_dl_handle=NULL;
		//Some thing abnormal in this function
		vector<string> load_infos;

		//Get load number
		scat_load_num = atoi(m_IniFileHandler->read_sactter_loads_num(distance(scat_files.begin(), it)).c_str());

		//read loads info
		m_IniFileHandler->read_sactter_loads(distance(scat_files.begin(), it), scat_load_num, load_infos);

		//for(vector<string>::iterator it_inf = load_infos.begin(); it_inf = load_infos.end(); it_inf++)
		for(unsigned int i=0; i<load_infos.size(); i++)
		{
			TargetHaneleItem.second.ROMSetting

		}

		image_infos.insert(pair<string, image_info>(*it, imgs));
	}
#endif
}

void CLinkMapFile::loadAllTargetFilesFromIni()
{

}
bool CLinkMapFile::loadTargetFileFromIni(string& ScatterFile)
{
  return false;
}


/*
virtual bool CLinkMapFile::load(string folder)
{

}
*/

bool CLinkMapFile::Destroy_DLHandle(DL_HANDLE_T *p_dl_handle)
{
    if( NULL != p_dl_handle )
    {
        int mtk_status;
        mtk_status = DL_Rom_UnloadAll( *p_dl_handle );
        if( mtk_status != 0 )
        {
            GC_TRACE("SFM::load_scatter_file Unload all ROM fail , err code %d", mtk_status);
            return false;
        }

        mtk_status = DL_Destroy( p_dl_handle );
        if( mtk_status != 0 )
        {
            GC_TRACE("SFM::load_scatter_file Unload all ROM fail , err code %d", mtk_status);
            return false;
        }

        delete p_dl_handle;
    }

    return true;
}

bool CLinkMapFile::clear()
{
	int HandleCounter;
	DL_HANDLE_T TempHandle;
	int mtk_status;
	GC_TRACE("Scatter File::clear");

	m_RootFolderPath="";

	if(0>=m_TargetHandleMap.size())
	{
		GC_TRACE("CLinkMapFile::clear==>m_TargetHandleMap.size()==0");
		return true;
	}
	m_TargetHandleMap.clear();


	mtk_status=DL_GetHandleNumber(*m_DownloadHandleList,&HandleCounter);
	if (S_DONE != mtk_status)
	{
		GC_TRACE("clear::DL_GetHandleNumber Error: %d",mtk_status);
	}


	for(int index=HandleCounter-1;index>=0;index--)
	{
		mtk_status=DL_GetHandle(*m_DownloadHandleList,index,&TempHandle);
		if (S_DONE != mtk_status)
		{
			GC_TRACE("clear::DL_GetHandleNumber Error: %d",mtk_status);
			continue;
		}
		mtk_status=DL_DeleteHandleFromList(*m_DownloadHandleList,TempHandle);
		if (S_DONE != mtk_status)
		{
			GC_TRACE("clear::DL_DeleteHandleFromList Error: %d",mtk_status);
			continue;
		}
		if (!Destroy_DLHandle(&TempHandle))
		{
			GC_TRACE("CLinkMapFile::clear==>Destroy_DLHandle Error");
			continue;
		}
		GC_TRACE("CLinkMapFile::clear==>Unload Dl Hanlde OK");
	}

	return true;
}


void CLinkMapFile::getLoadedTargetFilePath(vector<string> &paths)
{
	paths.clear();
	map<string, MAUI_LoadHandle>::iterator Iter;

	Iter=m_TargetHandleMap.begin();
	paths.push_back(Iter->first);

    /*
	for(Iter=m_TargetHandleMap.begin();Iter!=m_TargetHandleMap.end();Iter++)
	{
		paths.push_back(Iter->first);
	}
	*/
}

void CLinkMapFile::save_to_ini()
{
#if 0
	map<string, image_info> image_infos;
	map<string, image_info>::iterator it;
	vector<string>	scat_paths;

	if(NULL==m_IniFileHandler)
	{
		set_last_error(MDT_INI_FILE_IS_INVALID);
	}

	gather_load_info(image_infos);

	if(image_infos.size() == 0)
	{
		return;
	}
	//save num
	m_IniFileHandler->write_sactter_file_num(image_infos.size());

	//Save sactter file path
	for(it = image_infos.begin(); it != image_infos.end(); it++)
	{
		scat_paths.push_back((*it).first);
	}

	m_IniFileHandler->write_sactter_files_path(scat_paths);

	//Save loads
	for(it = image_infos.begin(); it != image_infos.end(); it++)
	{
		m_IniFileHandler->write_sactter_loads_num(distance(image_infos.begin(), it),
			(*it).second.size());

		for(image_info::iterator it_info = (*it).second.begin();
		it_info != (*it).second.end(); it_info++)
		{
			m_IniFileHandler->write_sactter_loads(distance(image_infos.begin(), it),
				distance((*it).second.begin(), it_info),
				(*it_info).to_string());
		}
	}
#elif 0

	//Need to design ~  //Modified by dongguo
	map<string, MAUI_LoadHandle>::iterator iter;
	vector<string>	scat_paths;

	if(NULL==m_IniFileHandler)
	{
		throw (int)MDT_INI_FILE_IS_INVALID;
	}
	if(m_TargetHandleMap.size() == 0)
	{
		return;
	}

	//save num
	m_IniFileHandler->write_sactter_file_num(m_TargetHandleMap.size());



	//Save loads
	for(iter = m_TargetHandleMap.begin(); iter != m_TargetHandleMap.end(); iter++)
	{
		unsigned short ROMCounter;
		ROM_INFO_EX RomInfo[MAX_LOAD_SECTIONS];
		string LoadFilePath;

		if(NULL==iter->second.m_dl_handle)
		{
			throw (int)MDT_INVALID_DOWNLOAD_HANDLE;
		}
		DL_GetCount_Ex(*iter->second.m_dl_handle,&ROMCounter);
		DL_Rom_GetInfoAll_Ex(*iter->second.m_dl_handle,&RomInfo,ROMCounter);

		m_IniFileHandler->write_sactter_files_path(iter->first,distance(m_TargetHandleMap.begin(),iter));
		m_IniFileHandler->write_sactter_loads_num(
										distance(m_TargetHandleMap.begin(),iter),
										ROMCounter;
										);
		for(int index=0;index<ROMCounter;index++)
		{
			LoadFilePath=RomInfo[index].filepath;
			m_IniFileHandler->write_sactter_loads(
												index,
												distance(m_TargetHandleMap.begin(),iter),
												LoadFilePath
												);
		}

	}

#else

#endif
}

bool CLinkMapFile::config_from_ini()
{
#if 0
	vector<string>	scat_files;
	map<string, image_info> image_infos;

	read_info_from_ini(scat_files, image_infos);

	for(vector<string>::iterator it=m_TargetFiles.begin(); it != m_TargetFiles.end(); it++)
	{
		//Once find a scatter file not matched then
		if(scat_files.end() == find(scat_files.begin(), scat_files.end(), *it))
		{
			GC_TRACE("Scatter files not matched, exit config from ini file.");
			return false;
		}
	}

	update_load(image_infos);

	return true;
#elif 0

	m_TargetHandleMap.clear();


	vector<string>	scat_files;
	map<string, image_info> image_infos;

	read_info_from_ini();

	for(vector<string>::iterator it=m_TargetFiles.begin(); it != m_TargetFiles.end(); it++)
	{
		//Once find a scatter file not matched then
		if(scat_files.end() == find(scat_files.begin(), scat_files.end(), *it))
		{
			GC_TRACE("Scatter files not matched, exit config from ini file.");
			return false;
		}
	}

	update_load(image_infos);

	return true;
#else
       return true;
#endif
}



void CLinkMapFile::set_last_error(MDT_ERROR_STATUS err)
{
	SET_LAST_ERROR(err);
	GC_TRACE("Scatter File Manager Set last error: %s", GET_LAST_ERROR());
}


bool CLinkMapFile::searchTargetFile(const string& folder_path)
{
	string targetFilePath;
	pair<string, MAUI_LoadHandle> TargetHanleItem;
	if(m_AvailableFileFinder->search(folder_path,targetFilePath))
	{
		TargetHanleItem.first=targetFilePath;
		m_TargetHandleMap.insert(TargetHanleItem);
		return true;
	}
	else
	{
		return false;
	}

}


//==================================================================================
bool ConfigFileManager::loadTargetFile(string& ScatterFile)
{
  //load config file~
  int ret;
  DL_HANDLE_T* p_dl_handle = new DL_HANDLE_T;
  map<string, MAUI_LoadHandle>::iterator iter;

  //
  {
    iter=m_TargetHandleMap.find(ScatterFile);
    if(iter==m_TargetHandleMap.end())
    {
      GC_TRACE_EX("Can not find: %s",ScatterFile.c_str());
      throw string("Can not find config file");;
    }

    ROMSetting* p_romSetting=&(iter->second.m_romSetting);
    string path=iter->first;

    GC_TRACE_EX("p_romSetting:  0x%0X8",p_romSetting);
    GC_TRACE_EX("Config File:  %s",path.c_str());


    if(NULL==m_DownloadHandleList)
    {
      GC_TRACE("ConfigFileManager::loadTargetFile==>Invalid Download Handle List");
      throw (int)MDT_INVALID_DOWNLOAD_HANDLE;
    }

    ret = GetROMSetting(path.c_str(), p_romSetting);
    if (ret != S_DONE)
    {
      GC_TRACE("ConfigFileManager::loadTargetFile==>Invalid Config File: %s",path.c_str());
      throw string("Invalid Config File: "+path);
    }

    if (p_romSetting->version == 1)
    {
      GC_TRACE("ConfigFileManager::loadTargetFile==>Invalid Config File==>romSetting.version==%d",p_romSetting->version);
      throw string("Invalid Config File: "+path);
    }
    else if (p_romSetting->version >= 2)
    {
    /*  if(UNKNOWN_BBCHIP_TYPE == p_romSetting->u.v02.chipType)     //20120116 huifen for MT6255
      {
        GC_TRACE("ConfigFileManager::Unkown BB Chip Type.");
        throw string("Invalid Config File: "+path);
      }     */
      ret=DL_Create(p_dl_handle);
      if (ret != S_DONE)
      {
        GC_TRACE("ConfigFileManager::DL_Create==>Failed ");
        throw string("Invalid Config File: "+path);
      }

      ret = DL_CreateROMEntries(*p_dl_handle, p_romSetting);

      if (ret != S_DONE)
      {
        GC_TRACE("ConfigFileManager::loadTargetFile==>Failed to create ROM entries");
        throw string("Invalid Config File: "+path);
      }

      ret = DL_AutoLoadROMFiles(*p_dl_handle);

      if (ret != S_DONE)
      {
        GC_TRACE("ConfigFileManager::loadTargetFile==>Failed to Load ROM Files");
        throw string("Invalid Config File: "+path);
      }
    }

    //Record handle
    ret = DL_AddHandleToList(*m_DownloadHandleList, *p_dl_handle );
    if(S_DONE != ret)
    {
      GC_TRACE("ConfigFileManager::loadTargetFile==>MDT_SAME_FLASHID_AND_BBCHIP_SW_VER");
    	throw (int)MDT_SAME_FLASHID_AND_BBCHIP_SW_VER;
    }

    iter->second.m_dl_handle=p_dl_handle;

    //Other setting
    //Default Value is 4K Bytes~~
    DL_SetPacketLength(*p_dl_handle, 4096);  //Set packet length

    ret=DL_ResourceProjectIdComparisonSetting(*p_dl_handle, _TRUE);
    if(S_DONE!=ret)
    {
    	GC_TRACE("ConfigFileManager::loadTargetFile==>DL_ResourceProjectIdComparisonSetting Fail");
    	throw ret;
    }

    if( S_DONE == ( ret = ROOTCERT_SyncWithDLHandle(g_ROOTCERT_HANDLE_DL, *p_dl_handle)) )
    {
       g_is_Root_Cert_File_In_Download_Handle= true;
    }
    GC_TRACE("ConfigFileManager::loadTargetFile==>Load %s Ok",path.c_str());
    return  true;
  }

}

bool ConfigFileManager::gather_load_info(map<string, MAUI_LoadHandle> &LoadInfo)
{
	LoadInfo=m_TargetHandleMap;
	return true;
}

void ConfigFileManager::loadExternalMemorySetting(struct ExternalMemorySetting *externalMemorySetting)
{
    GC_TRACE_EX("Load Memory Setting==>");
   	map<string, MAUI_LoadHandle>::iterator iter;
    if(m_TargetHandleMap.size()<=0)
    {
        GC_TRACE_EX("m_TargetHandleMap.size()<=0");
        return;
    }
    iter = m_TargetHandleMap.begin();

    GetExternalMemorySetting(iter->first.c_str(),
                                externalMemorySetting);
}




