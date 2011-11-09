# Microsoft Developer Studio Project File - Name="x3core" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=x3core - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "x3core.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "x3core.mak" CFG="x3core - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "x3core - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "x3core - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "x3core - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\code\bin\vc60\Release\python"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Release\x3core"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\code\pkg_Core\Interface" /I "..\..\..\code\pkg_Platform\Interface" /I "$(IntDir)" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /FD /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 /nologo /dll /pdb:"..\..\..\obj\vc60\Release\Symbols/x3core.pdb" /map:"..\..\..\obj\vc60\Release\Symbols/x3core.map" /machine:I386 /out:"..\..\..\code\bin\vc60\Release\python/_x3core.pyd" /implib:"..\..\..\obj\vc60\Release\Lib/x3core.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "x3core - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\code\bin\vc60\Debug\python"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Debug\x3core"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\code\pkg_Core\Interface" /I "..\..\..\code\pkg_Platform\Interface" /I "$(IntDir)" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /FD /GZ /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 /nologo /dll /pdb:"..\..\..\obj\vc60\Debug\Symbols/x3core.pdb" /debug /machine:I386 /out:"..\..\..\code\bin\vc60\Debug\python/_x3core.pyd" /implib:"..\..\..\obj\vc60\Debug\Lib/x3core.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /map

!ENDIF 

# Begin Target

# Name "x3core - Win32 Release"
# Name "x3core - Win32 Debug"
# Begin Group "Interface"

# PROP Default_Filter ""
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\Module.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\x3core.rc
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\Version.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\testcore.py
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\x3core.i

!IF  "$(CFG)" == "x3core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\..\code\bin\vc60\Release\python
InputPath=..\..\..\code\pkg_Platform\Modules\x3core\x3core.i
InputName=x3core

"$(InputName)._swig" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	swig.exe -c++ -python -I$(ProjectDir)..\..\..\code\pkg_Core\Interface -outdir $(OutDir) $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "x3core - Win32 Debug"

# Begin Custom Build
OutDir=.\..\..\..\code\bin\vc60\Debug\python
InputPath=..\..\..\code\pkg_Platform\Modules\x3core\x3core.i
InputName=x3core

"$(InputName)._swig" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	swig.exe -c++ -python -I$(ProjectDir)..\..\..\code\pkg_Core\Interface -outdir $(OutDir) $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\x3core.py

!IF  "$(CFG)" == "x3core - Win32 Release"

# Begin Custom Build
IntDir=.\..\..\..\obj\vc60\Release\x3core
TargetDir=\x3c\code\bin\vc60\Release\python
InputPath=..\..\..\code\pkg_Platform\Modules\x3core\x3core.py
InputName=x3core

"$(IntDir)\$(InputName)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist $(InputPath) xcopy $(InputPath) "$(TargetDir)"  /S/Q/Y/D

# End Custom Build

!ELSEIF  "$(CFG)" == "x3core - Win32 Debug"

# Begin Custom Build
IntDir=.\..\..\..\obj\vc60\Debug\x3core
TargetDir=\x3c\code\bin\vc60\Debug\python
InputPath=..\..\..\code\pkg_Platform\Modules\x3core\x3core.py
InputName=x3core

"$(IntDir)\$(InputName)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist $(InputPath) xcopy $(InputPath) "$(TargetDir)"  /S/Q/Y/D

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
