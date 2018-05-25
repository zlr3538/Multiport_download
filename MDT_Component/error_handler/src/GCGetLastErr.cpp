// GCGetLastErr.cpp:
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "mdt_component/error_handler/inc/GCGetLastErr.h"
MDTErrorHandler G_ErrorHandler;

char* MDTErrorHandler::get_last_error()
{
   map<GCErrCode, std::string>::iterator it = m_err_table.find(m_err);

   if(m_err_table.end() != it)
   {
      it->second.c_str();
      return "Unknown";
   }
   else
   {
      return "Unknown MDT Error!";
   }
}

void MDTErrorHandler::initial_err_table()
{
	add_err_table(MDT_OK,"Multiport Download Tool OK");


	//Link Map File Error==>Search file error
	add_err_table(MDT_SEARCH_SCATTER_ERROR,  "Search scatter file error!");
	add_err_table(MDT_NONE_SCATTER_IS_FOUND, "Can not find a scatter file in specified folder!");
	add_err_table(MDT_TOO_MANY_SCATTER_FILE, "Too many scatter files!");
	add_err_table(MDT_SAME_FLASHID_AND_BBCHIP_SW_VER, "Find same flash ID and bbchip version!");
	add_err_table(MDT_CREATE_DL_HANDLE_FAIL, "Create DL handle failed!");
	add_err_table(MDT_GET_LOADED_ROM_COUNT_FAIL, "Get ROM count failed!");
	add_err_table(MDT_GET_ROM_INFO_ALL_FAIL, "Get ROM info all failed!");
	add_err_table(MDT_GET_TOO_MANY_ROM, "Too many ROM!");
	add_err_table(MDT_CAN_NOT_LOAD_ALL_IMAGES, "Can't load all images!");
	add_err_table(MDT_QUERY_FLAHS_TYPE_ERROR, "Query flash type error!");
	add_err_table(MDT_LOAD_EXTENSION_BOOTLOADER_FAIL, "Load extension bootloader failed!");
	add_err_table(MDT_LOAD_BOOTLOADER_FAIL, "Load bootloader failed!");
	add_err_table(MDT_GET_BOOTLOADER_INFO_FAIL, "Query bootloader info failed!");
	add_err_table(MDT_ENABLE_BOOTLOADER_FAIL, "Enable bootloader failed!");
	add_err_table(MDT_MORE_THAN_ONE_SEC_RO, "Find more than 1 SEC RO File!");
	add_err_table(MDT_LOAD_SEC_RO_FILE_FAIL, "Load SEC RO failed.");

	add_err_table(MDT_INI_FILE_IS_INVALID,"Ini handle is invalid");
	add_err_table(MDT_INVALID_DOWNLOAD_HANDLE,"Download Handle Is Invalid");

	


}

void MDTErrorHandler::add_err_table(GCErrCode code, string info)
{
	m_err_table[code]=info;	
}


