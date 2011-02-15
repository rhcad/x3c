# Microsoft Developer Studio Project File - Name="ConfigDB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ConfigDB - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ConfigDB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ConfigDB.mak" CFG="ConfigDB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ConfigDB - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ConfigDB - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ConfigDB - Win32 Release"

# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\code\bin\gcc\Release\Plugins"
# PROP Intermediate_Dir "..\..\obj\gcc\Release\ConfigDB"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W4 /GR /GX /O2 /I "..\..\code\pkg_Utility\Modules\ConfigDB" /I "..\..\code\pkg_Utility\Interface\Database" /I "..\..\code\pkg_Core\Interface" /I "..\..\code\pkg_Core\Interface\Module" /I "..\..\code\pkg_Core\Interface\UtilFunc" /I "..\..\code\pkg_Core\Interface\Utility" /I "..\..\code\pkg_Core\Interface\Xml" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "UNICODE" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 shlwapi.lib /nologo /dll /pdb:"..\..\obj\gcc\Release\Symbols/ConfigDB.pdb" /machine:I386 /out:"..\..\code\bin\gcc\Release\Plugins/ConfigDB.plugin.dll"
# SUBTRACT LINK32 /pdb:none /map

!ELSEIF  "$(CFG)" == "ConfigDB - Win32 Debug"

# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\code\bin\gcc\Debug\Plugins"
# PROP Intermediate_Dir "..\..\obj\gcc\Debug\ConfigDB"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /ZI /Od /I "..\..\code\pkg_Utility\Modules\ConfigDB" /I "..\..\code\pkg_Utility\Interface\Database" /I "..\..\code\pkg_Core\Interface" /I "..\..\code\pkg_Core\Interface\Module" /I "..\..\code\pkg_Core\Interface\UtilFunc" /I "..\..\code\pkg_Core\Interface\Utility" /I "..\..\code\pkg_Core\Interface\Xml" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "UNICODE" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 shlwapi.lib /nologo /dll /pdb:"..\..\obj\gcc\Debug\Symbols/ConfigDB.pdb" /debug /machine:I386 /out:"..\..\code\bin\gcc\Debug\Plugins/ConfigDB.plugin.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /map

!ENDIF 

# Begin Target

# Name "ConfigDB - Win32 Release"
# Name "ConfigDB - Win32 Debug"
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\ClsID_Internal.h
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Interface\Database\Ix_ConfigDBFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Ix_InitDatabase.h
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Ix_SQLParser.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_CfgDatabase.h
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_CfgDbSection.h
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_CfgRecord.h
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_CfgRecordset.h
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_ConfigFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_SQLParser.h
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\DbFunc.h
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\StdAfx.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_CfgDatabase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_CfgDbSection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_CfgRecord.cpp
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_CfgRecordset.cpp
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Cx_ConfigFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\DbFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Module.cpp
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\ConfigDB.rc
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Utility\Modules\ConfigDB\Version.rc2
# End Source File
# End Group
# End Target
# End Project
