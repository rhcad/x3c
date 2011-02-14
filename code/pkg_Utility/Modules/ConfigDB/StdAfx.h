// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  // some CString constructors will be explicit
#define _AFX_ALL_WARNINGS   // turns off MFC's warning messages often safely ignored

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <shlwapi.h>        // Windows light-weight utility APIs

#include <vecfunc.h>        // STL master include file and functions
#include <SafeCall.h>       // SafeCall, InterfaceSafeCall...
#include <Log/DebugR.h>     // ASSERT, VERIFY and ASSERT_MESSAGE
#include <Log/LogHelper.h>  // LOG_WARNING ...
#define  LOGHEAD  L"@ConfigDB:" // eg: LOG_WARNING(LOGHEAD L"IDS_XXX);

#include "msado15.tlh"

