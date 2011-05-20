// Included by X3Portability.h to declare functions for GCC compiler.

#ifndef X3GCC_PORTABILITY_H
#define X3GCC_PORTABILITY_H

#include <string.h>
#include <stdlib.h>
#include <wchar.h>

#ifndef interface
#define interface struct
#endif

#define EXTERN_C
#define STDCALL
#define DECLEXPORT
#define OUTAPI      EXTERN_C DECLEXPORT

#ifndef MAX_PATH
#define MAX_PATH 256
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
inline long InterlockedExchange(long* p, long v)
    { long old = *p; *p = v; return old; }
inline void* InterlockedCompareExchange(void** p, void* newv, void* cmp)
{
    void* old = *p;
    if (cmp == *p)
        *(long*)p = (long)newv;
    return old;
}


bool FreeLibrary(HMODULE hdll);
HMODULE LoadLibraryW(const wchar_t* filename);
HMODULE LoadLibraryExW(const wchar_t* filename);
HMODULE GetModuleHandleW(const wchar_t* filename);
void* GetProcAddress(HMODULE hdll, const char* name);
void GetModuleFileNameW(HMODULE hdll, wchar_t* filename, int size);
void GetModuleFileNameA(HMODULE hdll, char* filename, int size);

bool OpenFileForRead(HANDLE& hfile, const wchar_t* filename);
bool OpenFileForWrite(HANDLE& hfile, const wchar_t* filename);
bool CloseFile(HANDLE file);
bool ReadFile(HANDLE file, void* buf, DWORD size, DWORD* readed, void*);
bool WriteFile(HANDLE file, const void* buf, DWORD size, DWORD* written, void*);
bool PathFileExistsW(const wchar_t* path);
bool CreateDirectoryW(const wchar_t* path, void*);
bool DeleteFileW(const wchar_t* filename);
DWORD GetFileSize(HANDLE file, DWORD* high);

char* PathFindFileNameA(const char* path);
wchar_t* PathFindFileNameW(const wchar_t* path);
bool PathIsRelativeW(const wchar_t* path);
void PathStripPathW(wchar_t* path);
void PathRemoveFileSpecW(wchar_t* path);
void PathRemoveExtensionW(wchar_t* path);
void PathRemoveBackslashW(wchar_t* path);
void PathAppendW(wchar_t* path, const wchar_t* more);
wchar_t* PathAddBackslashW(wchar_t* path);
void PathRenameExtensionW(wchar_t* path, const wchar_t* more);

void GetTempPathW(DWORD len, wchar_t* buf);
bool CheckFileAttributes(const wchar_t* filename, bool* readonly, bool* folder);
bool SetFileAttributesNormal(const wchar_t* filename);
DWORD GetLastError();

int WideCharToMultiByte(int codepage, DWORD flags,
                        const wchar_t* wstr, int wchars,
                        char* astr, int achars,
                        const char* defaultChar, void*);
int MultiByteToWideChar(int codepage, DWORD flags,
                        const char* astr, int achars,
                        wchar_t* wstr, int wchars);

inline int _stricmp(const char* s1, const char* s2)
    { return strncasecmp(s1, s2, strlen(s1)); }
inline int _wcsicmp(const wchar_t* s1, const wchar_t* s2)
    { return wcsncasecmp(s1, s2, wcslen(s1)); }

#endif // X3GCC_PORTABILITY_H
