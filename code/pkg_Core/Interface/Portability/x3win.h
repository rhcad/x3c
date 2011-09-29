// Included by X3Portability.h to declare functions on Windows.

#ifndef X3WIN_PORTABILITY_H
#define X3WIN_PORTABILITY_H

#if defined(_WIN64) && !defined(_WIN32)
#define _WIN32
#endif

#if !defined(_MSC_VER) || _MSC_VER > 1200 // not VC6

#ifndef WINVER
#define WINVER 0x0501           // WinXP or later.
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT    WINVER
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS  WINVER
#endif
#ifndef _WIN32_IE
#define _WIN32_IE 0x0600        // IE6 or later.
#endif

#endif // _MSC_VER

#ifdef _AFXDLL
#define VC_EXTRALEAN
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _AFX_ALL_WARNINGS
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdisp.h>        // MFC Automation classes
#endif
#else
#define _WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>        // Windows master include file
#endif // _AFXDLL

#include <shlwapi.h>        // Windows light-weight utility APIs
#ifdef _MSC_VER
#pragma comment(lib, "shlwapi.lib")
#endif

#define DECLEXPORT  __declspec(dllexport)
#define OUTAPI      extern "C" DECLEXPORT
#define PLNEXT      L".dll"

bool x3OpenFileForRead(HANDLE& hfile, const wchar_t* filename);
bool x3OpenFileForWrite(HANDLE& hfile, const wchar_t* filename);
bool x3CloseFile(HANDLE file);
HMODULE x3LoadLibrary(const wchar_t* filename);
bool x3CheckFileAttributes(const wchar_t* filename, bool* readonly, bool* folder);
bool x3SetFileAttributesNormal(const wchar_t* filename);

bool x3InMainThread();

#endif // X3WIN_PORTABILITY_H
