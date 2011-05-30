// Included by portimpl.h to implement functions on Linux.

#ifndef X3LINUX_PORTABILITY_IMPL_H
#define X3LINUX_PORTABILITY_IMPL_H

#include <../UtilFunc/ConvStr.h>
#include <dlfcn.h>
#include <stdio.h>

#define W2A(wstr)   x3::w2a(wstr).c_str()

static std::string  s_err;
static std::map<HMODULE, std::string>   s_plugins;

static inline void seterr(const char* err)
{
    s_err = err ? err : "";
}

bool FreeLibrary(HMODULE hdll)
{
    int ret = hdll ? dlclose(hdll) : 0;

    seterr(dlerror());
    s_plugins.erase(hdll);

    return 0 == ret;
}

HMODULE LoadLibraryW(const wchar_t* filename)
{
    wchar_t fullpath[MAX_PATH];

    if (PathIsRelativeW(filename))
    {
        GetModuleFileNameW(NULL, fullpath, MAX_PATH);
        PathRemoveFileSpecW(fullpath);
        PathAppendW(fullpath, filename);
        filename = fullpath;
    }

    std::string name(x3::w2a(filename));
    HMODULE hdll = dlopen(name.c_str(), RTLD_LAZY);

    seterr(dlerror());
    if (hdll)
    {
        s_plugins[hdll] = name;
    }

    return hdll;
}

HMODULE LoadLibraryExW(const wchar_t* filename)
{
    return LoadLibraryW(filename);
}

static inline bool cmpdl(const char* dpname, const char* match)
{
    int len = strlen(dpname);
    int len2 = strlen(match);

    if (0 == strncasecmp(match, dpname + std::max(0, len - len2), std::min(len, len2)))
    {
        return true;
    }

    return false;
}

#include <../PluginManager/Ix_PluginLoader2.h>
#include <../UtilFunc/LockCount.h>

Ix_ObjectFactory* xGetObjectFactory();
static long s_objFactoryLocker = 0;

HMODULE GetModuleHandleW(const wchar_t* filename)
{
    std::string match(x3::w2a(filename));
    std::map<HMODULE, std::string>::const_iterator it;

    for (it = s_plugins.begin(); it != s_plugins.end(); ++it)
    {
        if (cmpdl(it->second.c_str(), match.c_str()))
        {
            return it->first;
        }
    }

    CLockCount locker(&s_objFactoryLocker);
    Ix_PluginLoader2* factory = (s_objFactoryLocker > 1) ? NULL
        : dynamic_cast<Ix_PluginLoader2*>(xGetObjectFactory());

    if (factory)
    {
        HMODULE hdll = NULL;
        std::wstring file;

        for (int i = 0; factory->GetPluginFileName(i, hdll, file); i++)
        {
            if (cmpdl(W2A(file), match.c_str()))
            {
                return hdll;
            }
        }
    }

    return NULL;
}

void* GetProcAddress(HMODULE hdll, const char* name)
{
    void* sym = NULL;

    if (hdll)
    {
        sym = dlsym(hdll, name);
        seterr(dlerror());
    }

    return sym;
}

void GetModuleFileNameW(HMODULE hdll, wchar_t* filename, int size)
{
    *filename = 0;

    if (!hdll)
    {
        char tmp[32];
        char buf[MAX_PATH];

        sprintf(tmp, "/proc/%d/exe", getpid());
        int bytes = readlink(tmp, buf, MAX_PATH);
        if (bytes > 0)
        {
            buf[std::min(bytes, MAX_PATH - 1)] = '\0';
            wcscpy_s(filename, size, x3::a2w(buf).c_str());
        }
    }
    else
    {
        std::map<HMODULE, std::string>::const_iterator it = s_plugins.find(hdll);
        if (it != s_plugins.end())
        {
            wcscpy_s(filename, size, x3::a2w(it->second).c_str());
        }

        CLockCount locker(&s_objFactoryLocker);
        Ix_PluginLoader2* factory = (s_objFactoryLocker > 1) ? NULL
            : dynamic_cast<Ix_PluginLoader2*>(xGetObjectFactory());

        if (factory && 0 == filename[0])
        {
            HMODULE hdll2 = NULL;
            std::wstring file;

            for (int i = 0; factory->GetPluginFileName(i, hdll2, file); i++)
            {
                if (hdll2 == hdll)
                {
                    wcscpy_s(filename, size, file.c_str());
                }
            }
        }
    }
}

void GetModuleFileNameA(HMODULE hdll, char* filename, int size)
{
    wchar_t wfile[MAX_PATH] = { 0 };

    GetModuleFileNameW(hdll, wfile, MAX_PATH);
    strcpy_s(filename, size, x3::w2a(wfile).c_str());
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

int WideCharToMultiByte(int /*codepage*/, DWORD /*flags*/,
                        const wchar_t* wstr, int wchars,
                        char* astr, int achars,
                        const char*, void*)
{
    return astr ? wcstombs(astr, wstr, achars)
        : (wchars * sizeof(wchar_t));
}

int MultiByteToWideChar(int /*codepage*/, DWORD /*flags*/,
                        const char* astr, int achars,
                        wchar_t* wstr, int wchars)
{
    return wstr ? mbstowcs(wstr, astr, wchars) : achars;
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

#endif // X3LINUX_PORTABILITY_IMPL_H
