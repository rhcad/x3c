#ifndef X3LINUX_PORTABILITY_IMPL_H
#define X3LINUX_PORTABILITY_IMPL_H
#ifdef __linux__

bool FreeLibrary(HMODULE hdll)
{
    return true;
}

HMODULE LoadLibraryW(const wchar_t* filename)
{
    return NULL;
}

HMODULE LoadLibraryExW(const wchar_t* filename, void*, DWORD)
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


HANDLE CreateFileW(const wchar_t* filename, DWORD access, 
                          DWORD shareMode, void*, DWORD disposition, 
                          DWORD attributes, void*)
{
    return NULL;
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


char* PathFindFileNameA(const char* path)
{
    return NULL;
}

wchar_t* PathFindFileNameW(const wchar_t* path)
{
    return NULL;
}

bool PathIsRelativeW(const wchar_t* path)
{
    return false;
}

void PathStripPathW(wchar_t* path)
{
}

void PathRemoveFileSpecW(wchar_t* path)
{
}

void PathRemoveExtensionW(wchar_t* path)
{
}

void PathRemoveBackslashW(wchar_t* path)
{
}

void PathAppendW(wchar_t* path, const wchar_t* more)
{
}

wchar_t* PathAddBackslashW(wchar_t* path)
{
    return NULL;
}

void PathRenameExtensionW(wchar_t* path, const wchar_t* more)
{
}

void GetTempPathW(DWORD len, wchar_t* buf)
{
}

DWORD GetFileAttributesW(const wchar_t* filename)
{
    return 0;
}

bool SetFileAttributesW(const wchar_t* filename, DWORD attr)
{
    return 0;
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
                        
#endif // __linux__
#endif // X3LINUX_PORTABILITY_IMPL_H
