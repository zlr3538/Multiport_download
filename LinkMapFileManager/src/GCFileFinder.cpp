#pragma hdrstop

#include "LinkMapFileManager/inc/GCFileFinder.h"



bool GCFileFinder::search(const string& folder_path,string& targetFilePath)
{
    WIN32_FIND_DATA find_data;
    HANDLE hFind;
    bool bIsDirectory;
    string file_name, file_path, search_path;

    search_path = folder_path + "\\*.*";

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
		//on_find(folder_path, file_name);
		if(IsTargetFile(file_name))
		{
			targetFilePath=folder_path+"\\"+file_name;
			
			return true;
		}
    }
    else
    {
    	/*
       if((".." != file_name) && ("." != file_name))
       {
          file_path = folder_path + "\\";
          file_path += find_data.cFileName;
          search(file_path);
       }
       	*/
    }

    //For Find next file
    while(FindNextFile(hFind, &find_data))
    {     
        bIsDirectory = ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
        file_name = find_data.cFileName;

        if(!bIsDirectory)
        {
			//on_find(folder_path, file_name);
			if(IsTargetFile(file_name))
			{
				targetFilePath=folder_path+"\\"+file_name;
				return true;
			}
        }
        else
        {
           //...
        }
    }

    FindClose(hFind);
	//do not find target file~
    return false;
}

