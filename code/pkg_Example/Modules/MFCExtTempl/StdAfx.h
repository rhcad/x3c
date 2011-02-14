#pragma once

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <shlwapi.h>        // Windows light-weight utility APIs

#include <afxole.h>         // MFC OLE classes
#include <afxdisp.h>        // MFC Automation classes
#include <afxcmn.h>         // MFC support for Windows Common Controls
#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls

#include <Log/DebugR.h>     // ASSERT, VERIFY and ASSERT_MESSAGE
#include <Log/LogHelper.h>  // LOG_WARNING ...
#define  LOGHEAD  L"@Win32DllTempl:"    // eg: LOG_WARNING(LOGHEAD L"IDS_XXX);

