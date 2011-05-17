# Microsoft Developer Studio Project File - Name="SimpleUse" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=SimpleUse - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "SimpleUse.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "SimpleUse.mak" CFG="SimpleUse - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "SimpleUse - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SimpleUse - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SimpleUse - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\code\bin\gcc\Release\UnitTests"
# PROP Intermediate_Dir "..\..\obj\gcc\Release\SimpleUse"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GR /GX /O2 /I "..\..\code\pkg_Example\Modules\SimpleUse" /I "..\..\code\pkg_Example\Interface" /I "..\..\code\pkg_Core\Interface" /I "..\..\code\pkg_Core\Interface\PluginManager" /I "..\..\code\pkg_Core\Interface\UtilFunc" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 shlwapi.lib /nologo /subsystem:console /pdb:"..\..\obj\gcc\Release\Symbols/SimpleUse.pdb" /machine:I386
# SUBTRACT LINK32 /pdb:none /map

!ELSEIF  "$(CFG)" == "SimpleUse - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\code\bin\gcc\Debug\UnitTests"
# PROP Intermediate_Dir "..\..\obj\gcc\Debug\SimpleUse"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /ZI /Od /I "..\..\code\pkg_Example\Modules\SimpleUse" /I "..\..\code\pkg_Example\Interface" /I "..\..\code\pkg_Core\Interface" /I "..\..\code\pkg_Core\Interface\PluginManager" /I "..\..\code\pkg_Core\Interface\UtilFunc" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib /nologo /subsystem:console /pdb:"..\..\obj\gcc\Debug\Symbols/SimpleUse.pdb" /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /map

!ENDIF

# Begin Target

# Name "SimpleUse - Win32 Release"
# Name "SimpleUse - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\code\pkg_Example\Modules\SimpleUse\Main.cpp
# End Source File
# Begin Source File

SOURCE=..\..\code\pkg_Example\Modules\SimpleUse\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\code\pkg_Example\Modules\SimpleUse\StdAfx.h
# End Source File
# End Group
# End Target
# End Project
