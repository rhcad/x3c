# Microsoft Developer Studio Project File - Name="HookManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=HookManager - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HookManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HookManager.mak" CFG="HookManager - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HookManager - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HookManager - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HookManager - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\code\bin\vc60\Release\plugins"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Release\HookManager"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\code\pkg_Platform\Interface" /I "..\..\..\code\pkg_Core\Interface" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /FD /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 ole32.lib /nologo /dll /pdb:"..\..\..\obj\vc60\Release\Symbols/HookManager.pdb" /map:"..\..\..\obj\vc60\Release\Symbols/HookManager.map" /machine:I386 /out:"..\..\..\code\bin\vc60\Release\plugins/HookManager.plugin.dll" /implib:"..\..\..\obj\vc60\Release\Lib/HookManager.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "HookManager - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\code\bin\vc60\Debug\plugins"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Debug\HookManager"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\code\pkg_Platform\Interface" /I "..\..\..\code\pkg_Core\Interface" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /FD /GZ /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 ole32.lib /nologo /dll /pdb:"..\..\..\obj\vc60\Debug\Symbols/HookManager.pdb" /debug /machine:I386 /out:"..\..\..\code\bin\vc60\Debug\plugins/HookManager.plugin.dll" /implib:"..\..\..\obj\vc60\Debug\Lib/HookManager.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /map

!ENDIF 

# Begin Target

# Name "HookManager - Win32 Release"
# Name "HookManager - Win32 Debug"
# Begin Group "Interface"

# PROP Default_Filter ""
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\HookManager\Cx_HookManager.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\Public\ApiHook.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\HookManager\Cx_HookManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\HookManager\Module.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\HookManager\HookManager.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\HookManager\Version.rc2
# End Source File
# End Group
# End Target
# End Project
