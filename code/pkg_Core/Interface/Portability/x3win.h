// Included by X3Portability.h to declare functions on Windows.

#ifndef X3WIN_PORTABILITY_H
#define X3WIN_PORTABILITY_H

#ifndef WINVER
#if defined(_MSC_VER) && _MSC_VER <= 1200 // VC6
#define WINVER 0x0400
#else
#define WINVER 0x0501           // WinXP or later.
#endif
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

bool OpenFileForRead(HANDLE& hfile, const wchar_t* filename);
bool OpenFileForWrite(HANDLE& hfile, const wchar_t* filename);
bool CloseFile(HANDLE file);
HMODULE LoadLibraryExW(const wchar_t* filename);
bool CheckFileAttributes(const wchar_t* filename, bool* readonly, bool* folder);
bool SetFileAttributesNormal(const wchar_t* filename);

#endif // X3WIN_PORTABILITY_H
