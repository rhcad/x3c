// Included by X3Portability.h to declare functions for VC++ compiler.

#ifndef X3VC_PORTABILITY_H
#define X3VC_PORTABILITY_H

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
#ifdef _MSC_VER
#pragma comment(lib, "shlwapi.lib")
#endif

#define STDCALL     __stdcall
#define DECLEXPORT  __declspec(dllexport)
#define OUTAPI      extern "C" DECLEXPORT

#if _MSC_VER <= 1200        // VC6
#ifndef interface
#include <objbase.h>
#endif
#endif // VC6

inline bool OpenFileForRead(HANDLE& hfile, const wchar_t* filename)
{
    hfile = ::CreateFileW(filename,
        GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    return hfile != INVALID_HANDLE_VALUE;
}

inline bool OpenFileForWrite(HANDLE& hfile, const wchar_t* filename)
{
    hfile = ::CreateFileW(filename,
        GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    return hfile != INVALID_HANDLE_VALUE;
}

inline bool CloseFile(HANDLE file)
{
    return !!CloseHandle(file);
}

inline HMODULE LoadLibraryExW(const wchar_t* filename)
{
    return ::LoadLibraryExW(filename, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
}

inline bool CheckFileAttributes(const wchar_t* filename, bool* readonly, bool* folder)
{
    DWORD attr = GetFileAttributesW(filename);

    if (readonly)
        *readonly = !!(attr & FILE_ATTRIBUTE_READONLY);
    if (folder)
        *folder = !!(attr & FILE_ATTRIBUTE_DIRECTORY);

    return attr != (DWORD)-1;
}

inline bool SetFileAttributesNormal(const wchar_t* filename)
{
    return !!SetFileAttributesW(filename, FILE_ATTRIBUTE_NORMAL);
}

#endif // X3VC_PORTABILITY_H
