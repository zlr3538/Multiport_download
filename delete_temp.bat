
@REM delete all temp file, for release source code and check-in to code database

@echo off

echo delete all temp file...

del /f /s /q *.~*
del /f /s /q *.ddp
del /f /s /q *.bak
   

del /f /s /q output\*.obj
del /f /s /q output\*.tds
del /f /s /q output\backup_and_restore_data\*.*

 