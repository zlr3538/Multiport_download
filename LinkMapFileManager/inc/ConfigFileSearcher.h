#ifndef _CONFIG_FILE_MANAGER_
#define _CONFIG_FILE_MANAGER_

#include "GCFileFinder.h"

//------------------------------------
//ScatterFileSearcher
class  ConfigFileSearcher:public GCFileFinder
{

public:

     ConfigFileSearcher(){};
     ~ConfigFileSearcher(){};
private:
   bool IsTargetFile(const string& file);
};



#endif

