// Included by X3Portability.h to declare functions on linux or macosx.

#ifndef X3UNIX_PORTABILITY_H
#define X3UNIX_PORTABILITY_H

#include <string.h>
#include <stdlib.h>
#include <wchar.h>

#define DECLEXPORT
#define OUTAPI      extern "C" DECLEXPORT

#if defined (MACOSX)
#define PLNEXT      L".dylib"
#else
#define PLNEXT      L".so"
#endif

#ifndef MAX_PATH
#define MAX_PATH    512
#endif

typedef void* HMODULE;
typedef void* HANDLE;
typedef void* HWND;
typedef void* PROC;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef DWORD ULONG;

long InterlockedIncrement(long* p);
long InterlockedDecrement(long* p);
long InterlockedExchange(long* p, long v);

bool FreeLibrary(HMODULE hdll);
HMODULE LoadLibraryW(const wchar_t* filename);
HMODULE LoadLibraryExW(const wchar_t* filename);
HMODULE GetModuleHandleW(const wchar_t* filename);
PROC GetProcAddress(HMODULE hdll, const char* name);
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

int _stricmp(const char* s1, const char* s2);
int _wcsncmp(const wchar_t* s1, const wchar_t* s2);
int _wcsncmp(const wchar_t* s1, const wchar_t* s2, int count);

#endif // X3UNIX_PORTABILITY_H
