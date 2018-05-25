BROM_DLL_VERSION = 5.1348.00
META_DLL_VERSION = 6.1336.02

BROM_DLL_FOLDER_NAME = BROM_DLL_exe_v$(BROM_DLL_VERSION)
META_DLL_FOLDER_NAME = META_DLL_exe_v$(META_DLL_VERSION)
D_ROOT = .
Parent_ROOT = ..
BROM_DLL_SOURCE_NAME = $(Parent_ROOT)\$(BROM_DLL_FOLDER_NAME)
META_DLL_SOURCE_NAME = $(Parent_ROOT)\$(META_DLL_FOLDER_NAME)

Update_Brom_Library_and_Header_File:
  copy /Y $(BROM_DLL_SOURCE_NAME)\brom.h .\brom_dll\inc\brom.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\com_enum.h .\brom_dll\inc\com_enum.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\DOWNLOAD.h .\brom_dll\inc\DOWNLOAD.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\external_memory_setting.h .\brom_dll\inc\external_memory_setting.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\flashtool.h .\brom_dll\inc\flashtool.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\flashtool_api.h .\brom_dll\inc\flashtool_api.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\flashtool_handle.h .\brom_dll\inc\flashtool_handle.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\mtk_mcu.h .\brom_dll\inc\mtk_mcu.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\mtk_resource.h .\brom_dll\inc\mtk_resource.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\mtk_status.h .\brom_dll\inc\mtk_status.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\rom_setting.h .\brom_dll\inc\rom_setting.h
  
  copy /Y $(BROM_DLL_SOURCE_NAME)\gps_DA.bin .\output\gps_DA.bin
  copy /Y $(BROM_DLL_SOURCE_NAME)\MTK_AllInOne_DA.bin .\output\MTK_AllInOne_DA.bin
  
  copy /Y $(BROM_DLL_SOURCE_NAME)\bcb\Release\brom.lib .\brom_dll\lib\brom.lib

  copy /Y $(BROM_DLL_SOURCE_NAME)\bcb\Release\brom.dll .\output\brom.dll
  copy /Y $(D_ROOT)\SLA_Challenge.dll .\output\SLA_Challenge.dll
  
Update_Meta_Library_and_Header_File:
  copy /Y $(META_DLL_SOURCE_NAME)\meta.h .\meta_dll\inc\meta.h
  
  copy /Y $(META_DLL_SOURCE_NAME)\bcb\Release\META_DLL.lib .\meta_dll\lib\META_DLL.lib
  copy /Y $(META_DLL_SOURCE_NAME)\bcb\Release\META_DLL.dll .\meta_dll\lib\META_DLL.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bcb\Release\Controls.lib .\meta_dll\lib\Controls.lib
  copy /Y $(META_DLL_SOURCE_NAME)\bcb\Release\Controls.dll .\meta_dll\lib\Controls.dll
  
  
  copy /Y $(META_DLL_SOURCE_NAME)\bcb\Release\META_DLL.dll .\output\META_DLL.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bcb\Release\Controls.dll .\output\Controls.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bcb\Release\Microsoft.VC90.CRT.manifest .\output\Microsoft.VC90.CRT.manifest
  copy /Y $(META_DLL_SOURCE_NAME)\bcb\Release\msvcm90.dll .\output\msvcm90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bcb\Release\msvcp90.dll .\output\msvcp90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bcb\Release\msvcr90.dll .\output\msvcr90.dll
  
  

Update_Brom_And_Meta_Library_and_Header_File: Update_Brom_Library_and_Header_File Update_Meta_Library_and_Header_File
  
  
#





















