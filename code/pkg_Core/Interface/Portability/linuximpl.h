// Included by portimpl.h to implement functions on Linux.

#ifndef X3LINUX_PORTABILITY_IMPL_H
#define X3LINUX_PORTABILITY_IMPL_H
#ifdef __linux__

#include <ConvStr.h>

#define W2A(wstr)   x3::w2a(wstr).c_str()

bool FreeLibrary(HMODULE hdll)
{
    return true;
}

HMODULE LoadLibraryW(const wchar_t* filename)
{
    return NULL;
}

HMODULE LoadLibraryExW(const wchar_t* filename)
{
    return LoadLibraryW(filename);
}

HMODULE GetModuleHandleW(const wchar_t* filename)
{
    return NULL;
}

void* GetProcAddress(HMODULE hdll, const char* name)
{
    return NULL;
}

void GetModuleFileNameW(HMODULE hdll, wchar_t* filename, int size)
{
}

void GetModuleFileNameA(HMODULE hdll, char* filename, int size)
{
}


bool OpenFileForRead(HANDLE& hfile, const wchar_t* filename)
{
    return false;
}

bool OpenFileForWrite(HANDLE& hfile, const wchar_t* filename)
{
    return false;
}

bool CloseFile(HANDLE file)
{
    return false;
}

bool ReadFile(HANDLE file, void* buf, DWORD size, DWORD* readed, void*)
{
    return false;
}

bool WriteFile(HANDLE file, const void* buf, DWORD size, DWORD* written, void*)
{
    return false;
}

bool PathFileExistsW(const wchar_t* path)
{
    return false;
}

bool CreateDirectoryW(const wchar_t* path, void*)
{
    return false;
}

bool DeleteFileW(const wchar_t* filename)
{
    return false;
}

DWORD GetFileSize(HANDLE file, DWORD* high)
{
    return 0;
}

void GetTempPathW(DWORD len, wchar_t* buf)
{
}

bool CheckFileAttributes(const wchar_t* filename, bool* readonly, bool* folder)
{
    return false;
}

bool SetFileAttributesNormal(const wchar_t* filename)
{
    return false;
}

DWORD GetLastError()
{
    return 0;
}


int WideCharToMultiByte(int codepage, DWORD flags,
                        const wchar_t* wstr, int wchars,
                        char* astr, int achars,
                        const char* defaultChar, void*)
{
    return 0;
}

int MultiByteToWideChar(int codepage, DWORD flags,
                        const char* astr, int achars,
                        wchar_t* wstr, int wchars)
{
    return 0;
}

long InterlockedIncrement(long* p)
{
    return ++(*p);
}

long InterlockedDecrement(long* p)
{
    return --(*p);
}

long InterlockedExchange(long* p, long v)
{
    long old = *p;
    *p = v;
    return old;
}

void* InterlockedCompareExchange(void** p, void* newv, void* cmp)
{
    void* old = *p;
    if (cmp == *p)
    {
        *(long*)p = (long)newv;
    }
    return old;
}

#endif // __linux__
#endif // X3LINUX_PORTABILITY_IMPL_H
