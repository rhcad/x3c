//! \file func_s.h
//! \brief Realize functions compatible with VC++ 6.0 and below

#ifndef FUNCTIONS_COMPATIBLE_VC60_H
#define FUNCTIONS_COMPATIBLE_VC60_H

#if _MSC_VER < 1400 // not VC8

#include <time.h>   // for localtime

#ifdef _INC_STDIO

inline int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...)
{
    sizeOfBuffer;
    va_list arglist;
    va_start(arglist, format);
    return vsprintf(buffer, format, arglist);
}

inline int swprintf_s(wchar_t *buffer, size_t sizeOfBuffer, const wchar_t *format, ...)
{
    sizeOfBuffer;
    va_list arglist;
    va_start(arglist, format);
    return vswprintf(buffer, format, arglist);
}

inline int vsprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, va_list arglist)
    { sizeOfBuffer; return vsprintf(buffer, format, arglist); }
inline int vswprintf_s(wchar_t *buffer, size_t sizeOfBuffer, const wchar_t *format, va_list arglist)
    { sizeOfBuffer; return vswprintf(buffer, format, arglist); }

#endif // _INC_STDIO

inline int strcpy_s(char *str, size_t size, const char *src)
    { return lstrcpynA(str, src, size) != NULL; }
inline int wcscpy_s(wchar_t *str, size_t size, const wchar_t *src)
    { return lstrcpynW(str, src, size) != NULL; }

inline int strncpy_s(char *str, size_t size, const char *src, size_t len)
    { return lstrcpynA(str, src, min(size, len)) != NULL; }
inline int wcsncpy_s(wchar_t *str, size_t size, const wchar_t *src, size_t len)
    { return lstrcpynW(str, src, min(size, len)) != NULL; }

inline int strcat_s(char *str, size_t size, const char *src)
    { size; return strcat(str, src) != NULL; }
inline int wcscat_s(wchar_t *str, size_t size, const wchar_t *src)
    { size; return wcscat(str, src) != NULL; }

inline wchar_t * _wcslwr_s(wchar_t *str)
    { return _wcslwr(str); }
inline wchar_t * _wcsupr_s(wchar_t *str)
    { return _wcsupr(str); }

inline int _splitpath_s(
    const char * path, char * drive, size_t driveSize,
    char * dir, size_t dirSize,
    char * fname, size_t nameSize,
    char * ext,  size_t extSize)
{
    driveSize; dirSize; nameSize; extSize;
    _splitpath(path, drive, dir, fname, ext);
    return errno;
}

inline int _wsplitpath_s(
    const wchar_t * path, wchar_t * drive, size_t driveSize,
    wchar_t * dir, size_t dirSize,
    wchar_t * fname, size_t nameSize,
    wchar_t * ext,  size_t extSize)
{
    driveSize; dirSize; nameSize; extSize;
    _wsplitpath(path, drive, dir, fname, ext);
    return errno;
}

inline int _makepath_s(char *path, size_t size,
    const char *drive, const char *dir, const char *fname, const char *ext)
    { size; _makepath(path, drive, dir, fname, ext); return errno; }

inline int _wmakepath_s(wchar_t *path, size_t size,
    const wchar_t *drive, const wchar_t *dir, const wchar_t *fname, const wchar_t *ext)
    { size; _wmakepath(path, drive, dir, fname, ext); return errno; }

inline int _ltoa_s(long value, char *str, size_t size, int radix)
    { size; _ltoa(value, str, radix); return errno; }
inline int _ltow_s(long value, wchar_t *str, size_t size, int radix)
    { size; _ltow(value, str, radix); return errno; }
inline int _itoa_s(int value, char *str, size_t size, int radix)
    { size; _itoa(value, str, radix); return errno; }
inline int _itow_s(int value, wchar_t *str, size_t size, int radix)
    { size; _itow(value, str, radix); return errno; }
inline int _ultow_s(unsigned long value, wchar_t *str, size_t size, int radix)
    { size; _ultow(value, str, radix); return errno; }

inline void localtime_s(struct tm *tmOut, const time_t *timer)
{
    struct tm * p = localtime(timer);
    if (tmOut != NULL && p != NULL)
        *tmOut = *p;
}

#define _sopen_s(fileHandler, filename, oflag, pmode, rw)   \
    (*fileHandler = _open(filename, oflag, pmode), errno)

#ifdef _UNICODE
#define _stprintf_s     swprintf_s
#define _vstprintf_s    vswprintf_s
#define _tcscpy_s       wcscpy_s
#define _tcsncpy_s      wcsncpy_s
#define _tcscat_s       wcscat_s
#define _tsplitpath_s   _wsplitpath_s
#define _tmakepath_s    _wmakepath_s
#define _ltot_s         _ltow_s
#define _itot_s         _itow_s
#else
#define _stprintf_s     sprintf_s
#define _vstprintf_s    vsprintf_s
#define _tcscpy_s       strcpy_s
#define _tcsncpy_s      strncpy_s
#define _tcscat_s       strcat_s
#define _tsplitpath_s   _splitpath_s
#define _tmakepath_s    _makepath_s
#define _ltot_s         _ltoa_s
#define _itot_s         _itoa_s
#endif // _UNICODE

#endif // _MSC_VER

#ifndef GET_WHEEL_DELTA_WPARAM
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))
#endif

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

#endif // FUNCTIONS_COMPATIBLE_VC60_H
