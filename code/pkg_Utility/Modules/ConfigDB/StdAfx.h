// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#if _MSC_VER >= 1600 // VC2010
#include <SDKDDKVer.h>		// Defines the highest available Windows platform.
#endif

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  // some CString constructors will be explicit
#define _AFX_ALL_WARNINGS	// turns off MFC's warning messages often safely ignored

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <shlwapi.h>		// Windows light-weight utility APIs

#include <vecfunc.h>		// STL master include file and functions
#include <SafeCall.h>		// SafeCall, InterfaceSafeCall...
#include <Log/DebugR.h>		// ASSERT, VERIFY and ASSERT_MESSAGE
#include <Log/LogHelper.h>	// LOG_WARNING ...
#define  LOGHEAD  L"@ConfigDB:"	// eg: LOG_WARNING(LOGHEAD L"IDS_XXX);

#include "msado15.tlh"

