# Microsoft Developer Studio Project File - Name="TestPlatform" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TestPlatform - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "TestPlatform.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "TestPlatform.mak" CFG="TestPlatform - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "TestPlatform - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TestPlatform - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestPlatform - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\code\bin\vc60\Release\tests"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Release\TestPlatform"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FD /c
# ADD CPP /nologo /MD /W4 /GR- /GX /O2 /I "..\..\..\code\pkg_UnitTest\Modules\Public" /I "..\..\..\code\pkg_UnitTest\Interface" /I "..\..\..\code\pkg_Core\Interface" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 cppunit_dll.lib TestRunneru.lib ole32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:console /pdb:"..\..\..\obj\vc60\Release\Symbols/TestPlatform.pdb" /machine:I386 /libpath:"..\..\..\code\bin\vc60\Release\tests"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "TestPlatform - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\code\bin\vc60\Debug\tests"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Debug\TestPlatform"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GR- /GX /ZI /Od /I "..\..\..\code\pkg_UnitTest\Modules\Public" /I "..\..\..\code\pkg_UnitTest\Interface" /I "..\..\..\code\pkg_Core\Interface" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cppunitd_dll.lib TestRunnerud.lib ole32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:console /pdb:"..\..\..\obj\vc60\Debug\Symbols/TestPlatform.pdb" /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\code\bin\vc60\Debug\tests"
# SUBTRACT LINK32 /pdb:none

!ENDIF

# Begin Target

# Name "TestPlatform - Win32 Release"
# Name "TestPlatform - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\code\pkg_UnitTest\Modules\TestPlatform\TestComHook.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\code\pkg_UnitTest\Modules\TestPlatform\TestComHook.h
# End Source File
# End Group
# Begin Group "Public"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\code\pkg_UnitTest\Modules\Public\BaseTest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_UnitTest\Modules\Public\BaseTest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_UnitTest\Modules\Public\tests.cpp
# End Source File
# End Group
# End Target
# End Project
