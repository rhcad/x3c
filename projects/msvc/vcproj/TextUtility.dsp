# Microsoft Developer Studio Project File - Name="TextUtility" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TextUtility - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "TextUtility.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "TextUtility.mak" CFG="TextUtility - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "TextUtility - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TextUtility - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TextUtility - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\code\bin\vc60\Release\Plugins"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Release\TextUtility"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W4 /GR /GX /O2 /I "..\..\..\code\pkg_Core\Interface" /I "..\..\..\code\pkg_Core\Interface" /I "..\..\..\code\pkg_Core\Interface\Module" /I "..\..\..\code\pkg_Core\Interface\UtilFunc" /I "..\..\..\code\pkg_Core\Interface\Utility" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /FD /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 user32.lib ole32.lib /nologo /dll /pdb:"..\..\..\obj\vc60\Release\Symbols/TextUtility.pdb" /map:"..\..\..\obj\vc60\Release\Symbols/TextUtility.map" /machine:I386 /out:"..\..\..\code\bin\vc60\Release\Plugins/TextUtility.plugin.dll" /implib:"..\..\..\obj\vc60\Release\Lib/TextUtility.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "TextUtility - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\code\bin\vc60\Debug\Plugins"
# PROP Intermediate_Dir "..\..\..\obj\vc60\Debug\TextUtility"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /ZI /Od /I "..\..\..\code\pkg_Core\Interface" /I "..\..\..\code\pkg_Core\Interface" /I "..\..\..\code\pkg_Core\Interface\Module" /I "..\..\..\code\pkg_Core\Interface\UtilFunc" /I "..\..\..\code\pkg_Core\Interface\Utility" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /FD /GZ /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 user32.lib ole32.lib /nologo /dll /pdb:"..\..\..\obj\vc60\Debug\Symbols/TextUtility.pdb" /debug /machine:I386 /out:"..\..\..\code\bin\vc60\Debug\Plugins/TextUtility.plugin.dll" /implib:"..\..\..\obj\vc60\Debug\Lib/TextUtility.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /map

!ENDIF

# Begin Target

# Name "TextUtility - Win32 Release"
# Name "TextUtility - Win32 Debug"
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Interface\Utility\ClsID_TextUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Interface\Utility\Ix_ClipboardUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Interface\Utility\Ix_GuidGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Interface\Utility\Ix_StringConvert.h
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Interface\Utility\Ix_TextFileUtil.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Modules\TextUtility\Cx_ClipboardUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Modules\TextUtility\Cx_GuidGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Modules\TextUtility\Cx_TextUtil.h
# End Source File

# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Modules\TextUtility\Cx_ClipboardUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Modules\TextUtility\Cx_GuidGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Modules\TextUtility\Cx_TextUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Modules\TextUtility\Module.cpp
# End Source File

# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Modules\TextUtility\TextUtility.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\code\pkg_Core\Modules\TextUtility\Version.rc2
# End Source File
# End Group
# End Target
# End Project
