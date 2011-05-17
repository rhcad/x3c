#ifndef X3GCC_PORTABILITY_H
#define X3GCC_PORTABILITY_H

#include <string.h>
#include <stdlib.h>

#ifndef interface
#define interface struct
#endif

typedef void* HMODULE;
typedef void* HANDLE;
typedef void* HWND;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef DWORD ULONG;

inline void DebugBreak() {}
inline long InterlockedIncrement(long* p) { return ++(*p); }
inline long InterlockedDecrement(long* p) { return --(*p); }
inline long InterlockedExchange(long* p, long v) { return *p = v; }
inline void* InterlockedCompareExchange(void** p, void* newv, void* oldv) { *(long*)p = (long)newv; return oldv; }

inline bool FreeLibrary(HMODULE hdll)
{
    return true;
}

inline HMODULE LoadLibraryW(const wchar_t* filename)
{
    return NULL;
}

inline HMODULE LoadLibraryExW(const wchar_t* filename, void*, DWORD)
{
    return LoadLibraryW(filename);
}

inline void* GetProcAddress(HMODULE hdll, const char* name)
{
    return NULL;
}

inline HMODULE GetModuleHandleW(const wchar_t* filename)
{
    return NULL;
}

inline HANDLE CreateFileW(const wchar_t* filename, DWORD access, 
                          DWORD shareMode, void*, DWORD disposition, 
                          DWORD attributes, void*)
{
    return NULL;
}

inline char* PathFindFileNameA(const char* path)
{
    return NULL;
}

inline bool PathFileExistsW(const wchar_t* path)
{
    return false;
}

inline bool PathIsRelativeW(const wchar_t* path)
{
    return false;
}

inline wchar_t* PathFindFileNameW(const wchar_t* path)
{
    return NULL;
}

inline void GetModuleFileNameW(HMODULE hdll, wchar_t* filename, int size)
{
}

inline void PathStripPathW(wchar_t* path)
{
}

inline void PathRemoveFileSpecW(wchar_t* path)
{
}

inline void PathRemoveExtensionW(wchar_t* path)
{
}

inline void PathRemoveBackslashW(wchar_t* path)
{
}

inline void PathAppendW(wchar_t* path, const wchar_t* more)
{
}

inline wchar_t* PathAddBackslashW(wchar_t* path)
{
    return NULL;
}

inline void PathRenameExtensionW(wchar_t* path, const wchar_t* more)
{
}

inline void GetTempPathW(DWORD len, wchar_t* buf)
{
}

inline DWORD GetFileAttributesW(const wchar_t* filename)
{
    return 0;
}

inline bool SetFileAttributesW(const wchar_t* filename, DWORD attr)
{
    return 0;
}

inline bool CreateDirectoryW(const wchar_t* path, void*)
{
    return false;
}

inline DWORD GetLastError()
{
    return 0;
}

#endif // X3GCC_PORTABILITY_H
