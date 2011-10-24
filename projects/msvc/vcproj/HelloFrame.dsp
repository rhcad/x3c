# Microsoft Developer Studio Project File - Name="HelloFrame" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HelloFrame - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HelloFrame.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HelloFrame.mak" CFG="HelloFrame - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HelloFrame - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HelloFrame - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HelloFrame - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\code\bin\vc60\Release"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Release\HelloFrame"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\code\pkg_Core\Interface" /I "..\..\..\code\pkg_AppUI\Interface" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /i "..\..\..\code\pkg_Example\Interface" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:"..\..\..\obj\vc60\Release\Symbols/HelloFrame.pdb" /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copy test files
PostBuild_Cmds=@xcopy ..\..\..\code\bin\config ..\..\..\code\bin\vc60\release\config\  /S/Q/Y/D
# End Special Build Tool

!ELSEIF  "$(CFG)" == "HelloFrame - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\code\bin\vc60\Debug"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Debug\HelloFrame"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\code\pkg_Core\Interface" /I "..\..\..\code\pkg_AppUI\Interface" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /i "..\..\..\code\pkg_Example\Interface" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:"..\..\..\obj\vc60\Debug\Symbols/HelloFrame.pdb" /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copy test files
PostBuild_Cmds=@xcopy ..\..\..\code\bin\config ..\..\..\code\bin\vc60\debug\config\  /S/Q/Y/D
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "HelloFrame - Win32 Release"
# Name "HelloFrame - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\code\pkg_Example\Modules\HelloFrame\HelloApp.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\code\pkg_Example\Modules\HelloFrame\Resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\..\code\pkg_Example\Modules\HelloFrame\res\HelloFrame.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Example\Modules\HelloFrame\HelloFrame.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Example\Modules\HelloFrame\res\LargeIcons.png
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Example\Modules\HelloFrame\res\SmallIcons.png
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\code\pkg_Example\Modules\HelloFrame\uifactory.xml

!IF  "$(CFG)" == "HelloFrame - Win32 Release"

# Begin Custom Build
IntDir=.\..\..\..\obj\vc60\Release\HelloFrame
TargetDir=\x3c\code\bin\vc60\Release
InputPath=..\..\..\code\pkg_Example\Modules\HelloFrame\uifactory.xml
InputName=uifactory

"$(IntDir)\$(InputName)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	@xcopy $(InputPath) "$(TargetDir)\config\"  /S/Q/Y/D

# End Custom Build

!ELSEIF  "$(CFG)" == "HelloFrame - Win32 Debug"

# Begin Custom Build
IntDir=.\..\..\..\obj\vc60\Debug\HelloFrame
TargetDir=\x3c\code\bin\vc60\Debug
InputPath=..\..\..\code\pkg_Example\Modules\HelloFrame\uifactory.xml
InputName=uifactory

"$(IntDir)\$(InputName)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	@xcopy $(InputPath) "$(TargetDir)\config\"  /S/Q/Y/D

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
