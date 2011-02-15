# Microsoft Developer Studio Project File - Name="LogWriter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LogWriter - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LogWriter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LogWriter.mak" CFG="LogWriter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LogWriter - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LogWriter - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LogWriter - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\bin\vc60\Release\Plugins"
# PROP Intermediate_Dir "..\..\..\..\obj\vc60\Release\LogWriter"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W4 /GR /GX /O2 /I "..\..\Interface" /I "..\..\..\pkg_Core\Interface" /I "..\..\..\pkg_Core\Interface\Module" /I "..\..\..\pkg_Core\Interface\UtilFunc" /I "..\..\..\pkg_Core\Interface\Utility" /I "..\..\..\pkg_Core\Interface\Log" /I ".\log4cplus\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /D "LOG4CPLUS_STATIC" /D "INSIDE_LOG4CPLUS" /D LONG_PTR=long /Yu"stdafx.h" /FD /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 advapi32.lib wsock32.lib /nologo /dll /pdb:"..\..\..\..\obj\vc60\Release\Symbols/LogWriter.pdb" /map:"..\..\..\..\obj\vc60\Release\Symbols/LogWriter.map" /machine:I386 /out:"..\..\..\bin\vc60\Release\Plugins/LogWriter.plugin.dll" /implib:"..\..\..\..\obj\vc60\Release\Lib/LogWriter.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "LogWriter - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\bin\vc60\Debug\Plugins"
# PROP Intermediate_Dir "..\..\..\..\obj\vc60\Debug\LogWriter"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /ZI /Od /I "..\..\Interface" /I "..\..\..\pkg_Core\Interface" /I "..\..\..\pkg_Core\Interface\Module" /I "..\..\..\pkg_Core\Interface\UtilFunc" /I "..\..\..\pkg_Core\Interface\Utility" /I "..\..\..\pkg_Core\Interface\Log" /I ".\log4cplus\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /D "LOG4CPLUS_STATIC" /D "INSIDE_LOG4CPLUS" /D LONG_PTR=long /Yu"stdafx.h" /FD /GZ /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 advapi32.lib wsock32.lib /nologo /dll /pdb:"..\..\..\..\obj\vc60\Debug\Symbols/LogWriter.pdb" /debug /machine:I386 /out:"..\..\..\bin\vc60\Debug\Plugins/LogWriter.plugin.dll" /implib:"..\..\..\..\obj\vc60\Debug\Lib/LogWriter.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /map

!ENDIF 

# Begin Target

# Name "LogWriter - Win32 Release"
# Name "LogWriter - Win32 Debug"
# Begin Group "Interface"

# PROP Default_Filter ""
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\LogObserver.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "log4cplus"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\log4cplus\src\appender.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\appenderattachableimpl.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\configurator.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\consoleappender.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\factory.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\fileappender.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\filter.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=".\log4cplus\src\global-init.cxx"
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\hierarchy.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\hierarchylocker.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\layout.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\logger.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\loggerimpl.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\loggingevent.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\loglevel.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\loglog.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\logloguser.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\ndc.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\nteventlogappender.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\nullappender.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\objectregistry.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\patternlayout.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\pointer.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\property.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\rootlogger.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\sleep.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=".\log4cplus\src\socket-win32.cxx"
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\socket.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\socketappender.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\socketbuffer.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\stringhelper.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\syncprims.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\syslogappender.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\threads.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\timehelper.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\win32consoleappender.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\log4cplus\src\win32debugappender.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\LogObserver.cpp
# End Source File
# Begin Source File

SOURCE=.\Module.cpp
# End Source File
# Begin Source File

SOURCE=.\Plugin.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\LogWriter.rc
# End Source File
# Begin Source File

SOURCE=.\Version.rc2
# End Source File
# End Group
# End Target
# End Project
