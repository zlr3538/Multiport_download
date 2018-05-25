#include "LinkMapFileManager/inc/ConfigFileSearcher.h"

bool ConfigFileSearcher::IsTargetFile(const string& file)
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
    
    if(FileName.compare(FileName.size()-4, 4, ".CFG") != 0)
    {
        return false;
    }
    
    return true;
}



