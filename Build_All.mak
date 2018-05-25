TOOL_VERSION = 5.1348.00.00

D_ROOT = .
SERVICE_CENTER_VERSION_OUTPUT_NAME = Multiport_download_exe_v$(TOOL_VERSION)(service_center).zip
NORMAL_VERSION_OUTPUT_NAME = Multiport_download_exe_v$(TOOL_VERSION).zip
SOURCECODE_OUTPUT_NAME = Multiport_download_src_v$(TOOL_VERSION).zip
Generate_Make_File:
  bpr2mak -o$(D_ROOT)/Temporary_Build.mak $(D_ROOT)/MultiPortFlashDownloadProject.bpr
Build_Service_Center_Version: 
  call delete_temp.bat
  make -DUSERDEFINES=SERVICE_CENTER -fTemporary_Build.mak  
  copy /Y MultiPortFlashDownloadProject.ini .\output\MultiPortFlashDownloadProject.ini
  copy /Y BACKUP.ini .\output\BACKUP.ini
  call delete_temp.bat
  .\tool\zip -r -9 ..\$(SERVICE_CENTER_VERSION_OUTPUT_NAME) .\output
  
Build_Normal_Version:
  call delete_temp.bat
  make -fTemporary_Build.mak  
  copy /Y MultiPortFlashDownloadProject.ini .\output\MultiPortFlashDownloadProject.ini
  copy /Y BACKUP.ini .\output\BACKUP.ini
  call delete_temp.bat
  .\tool\zip -r -9 ..\$(NORMAL_VERSION_OUTPUT_NAME) .\output

Package_All_SourceCode:
  call delete_temp.bat
  .\tool\zip -r -9 ..\$(SOURCECODE_OUTPUT_NAME) .
  
Delete_Make_File:
  del Temporary_Build.mak
 
#
  