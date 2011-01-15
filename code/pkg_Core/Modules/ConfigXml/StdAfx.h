// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#define  _WIN32_WINNT   0x0400
#if _MSC_VER >= 1600        // VC2010
#include <SDKDDKVer.h>      // Defines the highest available Windows platform.
#endif

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>        // Windows master include file
#include <shlwapi.h>        // Windows light-weight utility APIs

#include <vecfunc.h>        // STL master include file and functions
#include <Log/DebugR.h>     // ASSERT, VERIFY and ASSERT_MESSAGE
#include <Log/LogHelper.h>  // LOG_WARNING ...
#define  LOGHEAD  L"@ConfigXml:"    // eg: LOG_WARNING(LOGHEAD L"IDS_XXX);

