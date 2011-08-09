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
!MESSAGE "x3core - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "x3core - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "x3core - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\code\bin\vc60\Debug\plugins"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Debug\x3core"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\code\pkg_Platform\Modules\Public" /I "..\..\..\code\pkg_Platform\Interface" /I "..\..\..\code\pkg_Core\Interface" /I "..\..\..\obj\vc60\Debug\x3core" /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /i "..\..\..\obj\vc60\Debug\x3core" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /pdb:"..\..\..\obj\vc60\Debug\Symbols/x3core.pdb" /debug /machine:I386 /out:"..\..\..\code\bin\vc60\Debug\plugins/x3core.com.dll" /implib:"..\..\..\obj\vc60\Debug\Lib/x3core.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "x3core - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\code\bin\vc60\Release\plugins"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Release\x3core"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O1 /I "..\..\..\code\pkg_Platform\Modules\Public" /I "..\..\..\code\pkg_Platform\Interface" /I "..\..\..\code\pkg_Core\Interface" /I "..\..\..\obj\vc60\Release\x3core" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /i "..\..\..\obj\vc60\Release\x3core" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /pdb:"..\..\..\obj\vc60\Release\Symbols/x3core.pdb" /map:"..\..\..\obj\vc60\Release\Symbols/x3core.map" /machine:I386 /out:"..\..\..\code\bin\vc60\Release\plugins/x3core.com.dll" /implib:"..\..\..\obj\vc60\Release\Lib/x3core.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "x3core - Win32 Debug"
# Name "x3core - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\dllmain.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\stdafx.cpp
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\x3core.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\x3core.def
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\x3core.idl

!IF  "$(CFG)" == "x3core - Win32 Debug"

# ADD MTL /tlb "..\..\..\obj\vc60\Debug\x3core/x3core.tlb" /h "..\..\..\obj\vc60\Debug\x3core/x3core_i.h" /iid "..\..\..\obj\vc60\Debug\x3core/x3core_i.c"

!ELSEIF  "$(CFG)" == "x3core - Win32 Release"

# ADD MTL /tlb "..\..\..\obj\vc60\Release\x3core/x3core.tlb" /h "..\..\..\obj\vc60\Release\x3core/x3core_i.h" /iid "..\..\..\obj\vc60\Release\x3core/x3core_i.c"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\x3core.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\dllmain.h
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\resource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav"
# Begin Source File

SOURCE=..\..\..\code\pkg_Platform\Modules\x3core\x3core.rgs
# End Source File
# End Group
# End Target
# End Project
