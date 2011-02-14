#pragma once

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>        // Windows master include file
#include <shlwapi.h>        // Windows light-weight utility APIs

#include <vecfunc.h>        // STL master include file and functions
#include <Log/DebugR.h>     // ASSERT, VERIFY and ASSERT_MESSAGE
#include <Log/LogHelper.h>  // LOG_WARNING ...
#define  LOGHEAD  L"@Win32DllTempl:"    // eg: LOG_WARNING(LOGHEAD L"IDS_XXX);

