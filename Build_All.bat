@color a 
@echo on
make -fBuild_All.mak Generate_Make_File
make -fBuild_All.mak Build_Service_Center_Version
make -fBuild_All.mak Build_Normal_Version
make -fBuild_All.mak Package_All_SourceCode
make -fBuild_All.mak Delete_Make_File






