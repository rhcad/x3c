#ifndef X3C_PORTABILITY_H
#define X3C_PORTABILITY_H

#if defined (_MSC_VER)      // VC++

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#ifdef _AFXDLL
#define VC_EXTRALEAN
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _AFX_ALL_WARNINGS
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#else
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>        // Windows master include file
#endif // _AFXDLL

#include <shlwapi.h>        // Windows light-weight utility APIs
#pragma comment(lib, "shlwapi.lib")

#if _MSC_VER <= 1200        // VC6
#ifndef interface
#include <objbase.h>
#endif
#endif // VC6

#elif defined (__GNUC__)    // GCC

#undef _WIN32
#include "../Portability/portgcc.h"

#endif // _MSC_VER

#ifdef _NEED_STDIO
#include <stdio.h>
#include <stdarg.h>
#ifndef _STDIO_DEFINED
#define _STDIO_DEFINED
#endif
#endif
#include "func_s.h"

#endif // X3C_PORTABILITY_H
