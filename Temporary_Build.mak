# ---------------------------------------------------------------------------
!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

# ---------------------------------------------------------------------------
# IDE SECTION
# ---------------------------------------------------------------------------
# The following section of the project makefile is managed by the BCB IDE.
# It is recommended to use the IDE to change any of the values in this
# section.
# ---------------------------------------------------------------------------

VERSION = BCB.06.00
# ---------------------------------------------------------------------------
PROJECT = output\MultiPortFlashDownloadProject.exe
OBJFILES = output\MultiPortFlashDownloadProject.obj \
    output\MultiPortFlashDownloadTool.obj output\time_utils.obj \
    output\form_About.obj output\file_utils.obj output\T_PCMCIA.obj \
    output\T_GPS.obj output\BromDLLProcAddr.obj output\BromDLLWrapper.obj \
    output\T_UsbCom.obj output\SetBeginComPort.obj output\InputImageDlg.obj \
    output\ToolSetting.obj output\com_util.obj \
    output\EFuseWriterViewerForm.obj output\ScatterFileManager.obj \
    output\ConfigFileSearcher.obj output\SV5_DownloadThread.obj \
    output\EFuseWriter.obj output\EFuseWriterParameter.obj \
    output\MultiPort_Utils.obj output\INIFileHandle.obj \
    output\FlashDownLoad.obj output\GCTrace.obj output\GCFileFinder.obj \
    output\GCGetLastErr.obj output\MDT_ErrorTypes.obj \
    output\T_UpdateParameter.obj output\T_META_Common.obj \
    output\T_ResetToFactoryDefault.obj \
    output\mdt_efusewriter_cefusewriterconfigfile.obj \
    output\mdt_efusewriter_cefusewriterfilereader.obj \
    output\mdt_efusewriter_cefusewriterlockfile.obj \
    output\mdt_handle_rwlock.obj output\EFuseReader.obj \
    output\cmdtefusereaderhandle.obj output\cmdtefuseparameterhandle.obj \
    output\cmdtefusewriterhandle.obj output\CriticalSectionManager.obj \
    output\Form_Changepw.obj output\Form_EngineerPasswd.obj
RESFILES = MultiPortFlashDownloadProject.res
MAINSOURCE = MultiPortFlashDownloadProject.cpp
RESDEPEN = $(RESFILES) Form\MainForm\MultiPortFlashDownloadTool.dfm \
    Form\AboutForm\form_About.dfm Form\SetBeginComPortForm\SetBeginComPort.dfm \
    Form\InputImageDlgForm\InputImageDlg.dfm \
    Form\ToolSettingForm\ToolSetting.dfm \
    Form\EFuseParameterViewerForm\EFuseWriterViewerForm.dfm \
    Form\ChgpasswdForm\Form_Changepw.dfm \
    Form\EngineerpwForm\Form_EngineerPasswd.dfm
LIBFILES = "C:\Program Files\Borland\CBuilder6\Lib\Psdk\setupapi.lib" \
    sla_challenge\lib\SLA_Challenge.lib META_dll\lib\META_DLL.lib \
    META_dll\lib\Controls.lib Brom_dll\lib\brom.lib \
    Brom_dll\lib\USBSwitchDLLibrary.lib Brom_dll\lib\FlashtoolLib.lib \
    Des\lib\des.lib
IDLFILES = 
IDLGENFILES = 
LIBRARIES = vcldb.lib vclx.lib bcbsmp.lib adortl.lib vcl.lib rtl.lib dbrtl.lib
PACKAGES = vcl.bpi rtl.bpi vclx.bpi bcbsmp.bpi dbrtl.bpi adortl.bpi vcldb.bpi \
    qrpt.bpi bdertl.bpi dsnap.bpi cds.bpi bdecds.bpi teeui.bpi teedb.bpi \
    tee.bpi vcldbx.bpi teeqr.bpi ibxpress.bpi visualclx.bpi visualdbclx.bpi \
    vclie.bpi xmlrtl.bpi inet.bpi inetdbbde.bpi inetdbxpress.bpi nmfast.bpi \
    bcbie.bpi soaprtl.bpi dclocx.bpi dbexpress.bpi dbxcds.bpi indy.bpi \
    bcb2kaxserver.bpi MMTools_c6.bpi dclusr.bpi
SPARELIBS = dbrtl.lib rtl.lib vcl.lib adortl.lib bcbsmp.lib vclx.lib vcldb.lib
DEFFILE = 
OTHERFILES = 
# ---------------------------------------------------------------------------
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
USERDEFINES = $(USERDEFINES);NO_WIN32_LEAN_AND_MEAN
SYSDEFINES = NO_STRICT;_NO_VCL
INCLUDEPATH = Form\EngineerpwForm;Form\ChgpasswdForm;MDT_Component\error_handler\src;MDT_Component\thread\src;INIFileHandle\src;Form\MainForm;efusewriter\src;SV5_DownloadThread\src;LinkMapFileManager\src;Form\ToolSettingForm;Form\AboutForm;Form\SetBeginComPortForm;Form\InputImageDlgForm;Form\EFuseParameterViewerForm;META_App\src;"C:\Documents and Settings\mtk70823";Comm;"Comm\USB COM";"META App";GPS;Comm\PCMCIA;FailReason;Form;$(BCB)\include;$(BCB)\include\vcl;Common;INIFileHandle;Parameter;Comm\PCMCIA\Inc;Brom_dll\inc;META_dll\inc;E:\MTK_Tool\MDT\W1332\Official\Multiport_download_src_v5.1332.00.00\Des\inc
LIBPATH = Form\EngineerpwForm;Form\ChgpasswdForm;MDT_Component\error_handler\src;MDT_Component\thread\src;INIFileHandle\src;Form\MainForm;efusewriter\src;SV5_DownloadThread\src;LinkMapFileManager\src;Form\ToolSettingForm;Form\AboutForm;Form\SetBeginComPortForm;Form\InputImageDlgForm;Form\EFuseParameterViewerForm;META_App\src;"C:\Documents and Settings\mtk70823";Comm;"Comm\USB COM";"META App";GPS;Comm\PCMCIA;FailReason;Form;Common;INIFileHandle;"C:\Program Files\Borland\CBuilder6\Projects";$(BCB)\Projects\Lib;$(BCB)\lib\obj;$(BCB)\lib;$(BCB)\Lib\Psdk;E:\MTK_Tool\MDT\W1332\Official\Multiport_download_src_v5.1332.00.00\Des\lib
WARNINGS= -w-par
PATHCPP = .;Form\MainForm;Common;Form\AboutForm;Common;Comm\PCMCIA;GPS;GPS;GPS;"Comm\USB COM";Form\SetBeginComPortForm;Form\InputImageDlgForm;Form\ToolSettingForm;Comm;Form\EFuseParameterViewerForm;LinkMapFileManager\src;LinkMapFileManager\src;SV5_DownloadThread\src;efusewriter\src;efusewriter\src;INIFileHandle\src;INIFileHandle\src;MDT_Component\thread\src;MDT_Component\error_handler\src;LinkMapFileManager\src;MDT_Component\error_handler\src;MDT_Component\error_handler\src;MDT_Component\thread\src;MDT_Component\thread\src;MDT_Component\thread\src;efusewriter\src;efusewriter\src;efusewriter\src;efusewriter\src;efusewriter\src;efusewriter\src;efusewriter\src;efusewriter\src;MDT_Component\thread\src;Form\ChgpasswdForm;Form\EngineerpwForm
PATHASM = .;
PATHPAS = .;
PATHRC = .;
PATHOBJ = .;$(LIBPATH)
# ---------------------------------------------------------------------------
CFLAG1 = -O2 -H=$(BCB)\lib\vcl60.csm -Vx -Ve -RT- -X- -a8 -b -k- -vi -tWD -tWM- -c
IDLCFLAGS = -IForm\EngineerpwForm -IForm\ChgpasswdForm \
    -IMDT_Component\error_handler\src -IMDT_Component\thread\src \
    -IINIFileHandle\src -IForm\MainForm -Iefusewriter\src \
    -ISV5_DownloadThread\src -ILinkMapFileManager\src -IForm\ToolSettingForm \
    -IForm\AboutForm -IForm\SetBeginComPortForm -IForm\InputImageDlgForm \
    -IForm\EFuseParameterViewerForm -IMETA_App\src \
    -I"C:\Documents and Settings\mtk70823" -IComm -I"Comm\USB COM" \
    -I"META App" -IGPS -IComm\PCMCIA -IFailReason -IForm -I$(BCB)\include \
    -I$(BCB)\include\vcl -ICommon -IINIFileHandle -IParameter \
    -IComm\PCMCIA\Inc -IBrom_dll\inc -IMETA_dll\inc \
    -IE:\MTK_Tool\MDT\W1332\Official\Multiport_download_src_v5.1332.00.00\Des\inc \
    -src_suffix cpp -D$(USERDEFINES) -DNO_WIN32_LEAN_AND_MEAN -boa
PFLAGS = -N2output -N0output -$Y- -$L- -$D- -$A8 -v -JPHNE -M
RFLAGS = 
AFLAGS = /mx /w2 /zn
LFLAGS = -loutput -Ioutput -D"" -aa -Tpe -GD -s -Gn -Gi -M
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib
# ---------------------------------------------------------------------------
!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0

[Version Info Keys]
CompanyName=
FileDescription=
FileVersion=1.0.0.0
InternalName=
LegalCopyright=
LegalTrademarks=
OriginalFilename=
ProductName=
ProductVersion=1.0.0.0
Comments=

[Debugging]
DebugSourceDirs=$(BCB)\source\vcl

!endif





# ---------------------------------------------------------------------------
# MAKE SECTION
# ---------------------------------------------------------------------------
# This section of the project file is not used by the BCB IDE.  It is for
# the benefit of building from the command-line using the MAKE utility.
# ---------------------------------------------------------------------------

.autodepend
# ---------------------------------------------------------------------------
!if "$(USERDEFINES)" != ""
AUSERDEFINES = -d$(USERDEFINES:;= -d)
!else
AUSERDEFINES =
!endif

!if !$d(BCC32)
BCC32 = bcc32
!endif

!if !$d(CPP32)
CPP32 = cpp32
!endif

!if !$d(DCC32)
DCC32 = dcc32
!endif

!if !$d(TASM32)
TASM32 = tasm32
!endif

!if !$d(LINKER)
LINKER = ilink32
!endif

!if !$d(BRCC32)
BRCC32 = brcc32
!endif


# ---------------------------------------------------------------------------
!if $d(PATHCPP)
.PATH.CPP = $(PATHCPP)
.PATH.C   = $(PATHCPP)
!endif

!if $d(PATHPAS)
.PATH.PAS = $(PATHPAS)
!endif

!if $d(PATHASM)
.PATH.ASM = $(PATHASM)
!endif

!if $d(PATHRC)
.PATH.RC  = $(PATHRC)
!endif

!if $d(PATHOBJ)
.PATH.OBJ  = $(PATHOBJ)
!endif
# ---------------------------------------------------------------------------
$(PROJECT): $(OTHERFILES) $(IDLGENFILES) $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) -L$(LIBPATH) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES)
!
# ---------------------------------------------------------------------------
.pas.hpp:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.pas.obj:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.cpp.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.cpp.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.asm.obj:
    $(BCB)\BIN\$(TASM32) $(AFLAGS) -i$(INCLUDEPATH:;= -i) $(AUSERDEFINES) -d$(SYSDEFINES:;= -d) $<, $@

.rc.res:
    $(BCB)\BIN\$(BRCC32) $(RFLAGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -fo$@ $<



# ---------------------------------------------------------------------------




