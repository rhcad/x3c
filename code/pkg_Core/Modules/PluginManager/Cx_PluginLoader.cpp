// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include "Cx_PluginLoader.h"
#include <PluginManager/Ix_AppWorkPath.h>
#include <UtilFunc/LockCount.h>
#include <UtilFunc/ScanFiles.h>

Cx_PluginLoader::Cx_PluginLoader()
    : m_instance(NULL)
{
    m_clsfile[0] = 0;
}

Cx_PluginLoader::~Cx_PluginLoader()
{
}

HMODULE Cx_PluginLoader::GetMainModuleHandle()
{
    return m_instance;
}

void Cx_PluginLoader::ReplaceSlashes(wchar_t* filename)
{
    for (; *filename; ++filename)
    {
#ifdef _WIN32
        if (L'/' == *filename)
        {
            *filename = L'\\';
        }
#else
        if (L'\\' == *filename)
        {
            *filename = L'/';
        }
#endif
    }
}

void Cx_PluginLoader::MakeFullPath(wchar_t* fullpath, HMODULE instance,
                                   const wchar_t* path)
{
    if (!path || 0 == path[0] || PathIsRelativeW(path))
    {
        GetModuleFileNameW(instance, fullpath, MAX_PATH);
        PathRemoveFileSpecW(fullpath);
        PathAppendW(fullpath, path);
    }
    else
    {
        wcscpy_s(fullpath, MAX_PATH, path);
    }
    ReplaceSlashes(fullpath);
    PathAddBackslashW(fullpath);
}

long Cx_PluginLoader::LoadPlugins(HMODULE instance, const wchar_t* path,
                                  const wchar_t* ext, bool recursive)
{
    wchar_t fullpath[MAX_PATH];

    m_instance = instance;
    MakeFullPath(fullpath, instance, path);

    return LoadPlugins(fullpath, ext, recursive);
}

long Cx_PluginLoader::LoadPlugins(const wchar_t* path, const wchar_t* ext,
                                  bool recursive)
{
    wchar_t fullpath[MAX_PATH];
    std::vector<std::wstring> filenames;

    MakeFullPath(fullpath, NULL, path);
    FindPlugins(filenames, fullpath, ext, recursive);

    return InLoadPlugins(filenames);
}

long Cx_PluginLoader::InLoadPlugins(const std::vector<std::wstring>& filenames)
{
    long count = 0;
    std::vector<std::wstring>::const_iterator it;

    if (!filenames.empty())
    {
        LoadCacheFile(filenames.front().c_str());

        for (it = filenames.begin(); it != filenames.end(); ++it)
        {
            if (LoadPluginOrDelay(it->c_str()))
            {
                count++;
            }
        }
    }

    return count;
}

class CScanPluginsByExt : public x3::CScanFilesCallback
{
public:
    CScanPluginsByExt(std::vector<std::wstring>* files, const wchar_t* ext)
        : m_files(files), m_ext(ext), m_extlen(wcslen(ext))
    {
    }

private:
    virtual void OnCheckFile(const wchar_t* filename, const wchar_t*, bool&)
    {
        int len = wcslen(filename);
        if (len >= m_extlen && _wcsicmp(&filename[len - m_extlen], m_ext) == 0)
        {
            m_files->push_back(filename);
        }
    }

private:
    CScanPluginsByExt();
    CScanPluginsByExt(const CScanPluginsByExt&);
    void operator=(const CScanPluginsByExt&);

    std::vector<std::wstring>*  m_files;
    const wchar_t*              m_ext;
    const int                   m_extlen;
};

void Cx_PluginLoader::FindPlugins(std::vector<std::wstring>& filenames,
                                  const wchar_t* path, const wchar_t* ext,
                                  bool recursive)
{
    CScanPluginsByExt scanner(&filenames, ext);
    x3::ScanFiles(&scanner, path, recursive);
}

bool Cx_PluginLoader::issep(wchar_t c)
{
    return L',' == c || L';' == c || iswspace(c);
}

long Cx_PluginLoader::LoadPluginFiles(const wchar_t* path,
                                      const wchar_t* files,
                                      HMODULE instance)
{
    wchar_t filename[MAX_PATH];

    m_instance = instance;
    MakeFullPath(filename, instance, path);

    const int len0 = wcslen(filename);
    wchar_t* nameend = filename + len0;

    std::vector<std::wstring> filenames;
    int i, j;

    for (i = 0; files[i] != 0; )
    {
        while (issep(files[i]))
        {
            i++;
        }
        for (j = i; files[j] != 0 && !issep(files[j]); j++)
        {
        }
        if (j > i)
        {
            wcsncpy_s(nameend, MAX_PATH - len0, files + i,
                MAX_PATH - len0 < j - i ? MAX_PATH - len0 : j - i);
            nameend[j - i] = 0;
            ReplaceSlashes(filename);
            filenames.push_back(filename);
        }
        i = j;
    }

    return InLoadPlugins(filenames);
}

long Cx_PluginLoader::InitializePlugins()
{
    CLockCount locker(&m_loading);
    long count = 0;

    for (long i = 0; i < x3::GetSize(m_modules); i++)
    {
        if (m_modules[i]->inited)
        {
            continue;
        }
        if (!m_modules[i]->hdll) // delay-load
        {
            count++;
            m_modules[i]->inited = true;
            continue;
        }

        typedef bool (*FUNC_INIT)();
        FUNC_INIT pfn = (FUNC_INIT)GetProcAddress(
            m_modules[i]->hdll, "x3InitializePlugin");

        if (pfn && !(*pfn)())
        {
            GetModuleFileNameW(m_modules[i]->hdll, m_modules[i]->filename, MAX_PATH);
            X3LOG_WARNING2(L"@PluginManager:IDS_INITPLUGIN_FAIL", m_modules[i]->filename);
            VERIFY(UnloadPlugin(m_modules[i]->filename));
            i--;
        }
        else
        {
            count++;
            m_modules[i]->inited = true;
        }
    }

    SaveClsids();

    return count;
}

int Cx_PluginLoader::GetPluginIndex(const wchar_t* filename)
{
    const wchar_t* title = PathFindFileNameW(filename);
    int i = x3::GetSize(m_modules);

    while (--i >= 0)
    {
        // ignore folders
        if (_wcsicmp(title, PathFindFileNameW(m_modules[i]->filename)) == 0)
        {
            break;
        }
    }

    return i;
}

bool Cx_PluginLoader::RegisterPlugin(HMODULE instance)
{
    if (FindModule(instance) >= 0)
    {
        return false;
    }

    Ix_Module* pModule = GetModule(instance);

    if (pModule != NULL)
    {
        MODULE moduleInfo;

        moduleInfo.hdll = instance;
        moduleInfo.module = pModule;
        moduleInfo.owned = false;
        moduleInfo.inited = false;
        GetModuleFileNameW(moduleInfo.hdll, moduleInfo.filename, MAX_PATH);

        int moduleIndex = GetPluginIndex(moduleInfo.filename);
        if (moduleIndex >= 0)
        {
            ASSERT(m_modules[moduleIndex] != NULL);
            *m_modules[moduleIndex] = moduleInfo;
        }
        else
        {
            moduleIndex = x3::GetSize(m_modules);
            MODULE* module = new MODULE;
            *module = moduleInfo;
            m_modules.push_back(module);
        }

        RegisterClassEntryTable(moduleIndex);

        return true;
    }

    return false;
}

bool Cx_PluginLoader::LoadPlugin(const wchar_t* filename)
{
    CLockCount locker(&m_loading);
    int existIndex = GetPluginIndex(filename);

    if (existIndex >= 0 && m_modules[existIndex]->hdll)
    {
        if (_wcsicmp(filename, m_modules[existIndex]->filename) != 0)
        {
            X3LOG_DEBUG2(L"The plugin is already loaded.",
                filename << L", " << (m_modules[existIndex]->filename));
        }
        return false;
    }

    HMODULE hdll = LoadLibraryExW(filename);
    DWORD errcode = GetLastError();

    if (hdll)
    {
        if (RegisterPlugin(hdll))
        {
            int moduleIndex = FindModule(hdll);

            ASSERT(moduleIndex >= 0);
            ASSERT(existIndex < 0 || existIndex == moduleIndex);

            m_modules[moduleIndex]->owned = true;
#ifdef _WIN32
            DisableThreadLibraryCalls(hdll);
#endif
        }
        else
        {
            FreeLibrary(hdll);
            hdll = NULL;
        }
    }
    else if (PathFileExistsW(filename))
    {
        X3LOG_WARNING2(L"Fail to load plugin.", errcode << L", " << filename);
    }

    return hdll != NULL;
}

bool Cx_PluginLoader::UnloadPlugin(const wchar_t* name)
{
    CLockCount locker(&m_unloading);
    int moduleIndex = GetPluginIndex(name);
    HMODULE hdll = moduleIndex < 0 ? NULL : m_modules[moduleIndex]->hdll;

    if (NULL == hdll)
    {
        return false;
    }

    typedef bool (*FUNC_CANUNLOAD)();
    FUNC_CANUNLOAD pfnCan = (FUNC_CANUNLOAD)GetProcAddress(
        hdll, "x3CanUnloadPlugin");

    if (pfnCan && !pfnCan())
    {
        return false;
    }

    typedef void (*FUNC_UNLOAD)();
    FUNC_UNLOAD pfnUnload = (FUNC_UNLOAD)GetProcAddress(
        hdll, "x3UninitializePlugin");

    if (pfnUnload)
    {
        pfnUnload();
    }

    VERIFY(ClearModuleItems(hdll));
    ReleaseModule(hdll);

    return true;
}

long Cx_PluginLoader::UnloadPlugins()
{
    CLockCount locker(&m_unloading);
    SaveClsids();
    m_cache.Release();

    long i = 0;
    long count = 0;

    for (i = x3::GetSize(m_modules) - 1; i >= 0; i--)
    {
        typedef void (*FUNC_UNLOAD)();
        FUNC_UNLOAD pfnUnload = (FUNC_UNLOAD)GetProcAddress(
            m_modules[i]->hdll, "x3UninitializePlugin");
        if (pfnUnload)
        {
            pfnUnload();
        }
    }

    for (i = x3::GetSize(m_modules) - 1; i >= 0; i--)
    {
        ClearModuleItems(m_modules[i]->hdll);
    }

    for (i = x3::GetSize(m_modules) - 1; i >= 0; i--)
    {
        if (m_modules[i]->hdll)
        {
            ReleaseModule(m_modules[i]->hdll);
            count++;
        }
    }

    return count;
}

bool Cx_PluginLoader::ClearModuleItems(HMODULE hModule)
{
    Ix_Module* pModule = GetModule(hModule);

    if (pModule)
    {
        pModule->ClearModuleItems();
        return true;
    }

    return false;
}

long Cx_PluginLoader::GetPluginCount()
{
    return x3::GetSize(m_modules);
}

bool Cx_PluginLoader::GetPluginFileName(long index, HMODULE& hdll, std::wstring& filename)
{
    bool valid = x3::IsValidIndexOf(m_modules, index);

    hdll = valid ? m_modules[index]->hdll : NULL;
    filename = valid ? m_modules[index]->filename : L"";

    return valid;
}
