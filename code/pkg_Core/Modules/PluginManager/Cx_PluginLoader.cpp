// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// author: Zhang Yun Gui, Tao Jian Lin
// v1: 2010.12

#include "stdafx.h"
#include "Cx_PluginLoader.h"

Cx_PluginLoader::Cx_PluginLoader()
    : m_instance(NULL)
{
}

Cx_PluginLoader::~Cx_PluginLoader()
{
}

HMODULE Cx_PluginLoader::GetMainModuleHandle()
{
    return m_instance;
}

static void ReplaceSlashes(wchar_t* filename)
{
    for (; *filename; ++filename)
    {
        if ('/' == *filename)
        {
            *filename = '\\';
        }
    }
}

long Cx_PluginLoader::LoadPlugins(HMODULE instance, const wchar_t* path, 
                                  const wchar_t* ext, bool recursive)
{
    wchar_t fullpath[MAX_PATH];

    m_instance = instance;
    GetModuleFileNameW(instance, fullpath, MAX_PATH);
    PathRemoveFileSpecW(fullpath);
    PathAppendW(fullpath, path);

    return LoadPlugins(fullpath, ext, recursive);
}

long Cx_PluginLoader::LoadPlugins(const wchar_t* path, const wchar_t* ext, bool recursive)
{
    WIN32_FIND_DATAW fd;
    wchar_t rootpath[MAX_PATH];
    wchar_t filename[MAX_PATH];
    long count = 0;
    const int extlen = lstrlenW(ext);
    std::vector<std::wstring> subpaths;

    if (PathIsRelativeW(path) || 0 == path[0])
    {
        GetModuleFileNameW(NULL, rootpath, MAX_PATH);
        PathRemoveFileSpecW(rootpath);
        PathAppendW(rootpath, path);
    }
    else
    {
        lstrcpynW(rootpath, path, MAX_PATH);
    }

    ReplaceSlashes(rootpath);
    lstrcpynW(filename, rootpath, MAX_PATH);
    PathAppendW(filename, L"*.*");
    
    HANDLE hFind = ::FindFirstFileW(filename, &fd);
    BOOL bContinue = (hFind != INVALID_HANDLE_VALUE);

    while (bContinue)
    {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (fd.cFileName[0] != '.' && recursive)
            {
                lstrcpynW(filename, rootpath, MAX_PATH);
                PathAppendW(filename, fd.cFileName);
                subpaths.push_back(filename);
            }
        }
        else
        {
            int len = lstrlenW(fd.cFileName);

            if (StrCmpIW(&fd.cFileName[max(0, len - extlen)], ext) == 0)
            {
                lstrcpynW(filename, rootpath, MAX_PATH);
                PathAppendW(filename, fd.cFileName);
                if (LoadPlugin(filename))
                {
                    count++;
                }
            }
        }
        bContinue = ::FindNextFileW(hFind, &fd);
    }
    ::FindClose(hFind);
    
    std::vector<std::wstring>::const_iterator it = subpaths.begin();
    for (; it != subpaths.end(); ++it)
    {
        count += LoadPlugins(it->c_str(), ext, recursive);
    }
    
    return count;
}

long Cx_PluginLoader::LoadPluginFiles(const wchar_t* path, const wchar_t* files, HMODULE instance)
{
    wchar_t filename[MAX_PATH];
    wchar_t apppath[MAX_PATH];

    m_instance = instance;
    GetModuleFileNameW(instance, apppath, MAX_PATH);
    PathRemoveFileSpecW(apppath);

    lstrcpynW(filename, apppath, MAX_PATH);
    PathAppendW(filename, path);
    PathAddBackslashW(filename);
    
    const int len0 = lstrlenW(filename);
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
            lstrcpynW(nameend, files + i, min(MAX_PATH - len0, 1 + j - i));
            ReplaceSlashes(filename);
            filenames.push_back(filename);
        }
        i = j;
    }

    int count = 0;
    std::vector<std::wstring>::const_iterator it = filenames.begin();

    for (; it != filenames.end(); ++it)
    {
        if (LoadPlugin(it->c_str()))
        {
            count++;
        }
    }

    return count;
}

long Cx_PluginLoader::InitializePlugins()
{
    long nSuccessLoadNum = 0;

    for (unsigned int i = 0; i < m_vecModule.size(); i++)
    {
        if (m_vecModule[i].bInit)
        {
            continue;
        }

        typedef bool (*FUNC_PLUGINLOAD)();
        FUNC_PLUGINLOAD pfn = (FUNC_PLUGINLOAD)GetProcAddress(
            m_vecModule[i].hModule, "InitializePlugin");

        if (!pfn || (*pfn)())
        {
            nSuccessLoadNum++;
            m_vecModule[i].bInit = true;
        }
    }

    return nSuccessLoadNum;
}

bool Cx_PluginLoader::RegisterPlugin(HMODULE instance)
{
    if (FindModule(instance) >= 0)
    {
        return true;
    }

    Ix_Module* pModule = GetModule(instance);

    if (pModule != NULL)
    {
        MODULEINFO moduleInfo;

        moduleInfo.hModule = instance;
        moduleInfo.pModule = pModule;
        moduleInfo.bOwner = false;
        moduleInfo.bInit = false;
        m_vecModule.push_back(moduleInfo);

        RegisterClassEntryTable(instance);

        return true;
    }

    return false;
}

bool Cx_PluginLoader::LoadPlugin(const wchar_t* filename)
{
    bool bOwner = false;
    HMODULE hModule = GetModuleHandleW(filename);

    if (!hModule)
    {
        hModule = LoadLibraryExW(filename, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
        if (!hModule)
        {
            return false;
        }
        bOwner = true;
    }

    int moduleIndex = FindModule(hModule);
    if (moduleIndex < 0 && RegisterPlugin(hModule))
    {
        moduleIndex = FindModule(hModule);
        ASSERT(moduleIndex >= 0);
        m_vecModule[moduleIndex].bOwner = bOwner;
    }
    else if (bOwner)
    {
        FreeLibrary(hModule);
    }

    return moduleIndex >= 0;
}

bool Cx_PluginLoader::UnloadPlugin(const wchar_t* name)
{
    HMODULE hModule = GetModuleHandleW(name);

    if (!hModule || FindModule(hModule) < 0)
    {
        return false;
    }

    typedef bool (*FUNC_CANUNLOAD)();
    FUNC_CANUNLOAD pfnCan = (FUNC_CANUNLOAD)GetProcAddress(hModule, "xCanUnloadPlugin");

    if (pfnCan && !pfnCan())
    {
        return false;
    }

    typedef void (*FUNC_UNLOAD)();
    FUNC_UNLOAD pfnUnload = (FUNC_UNLOAD)GetProcAddress(hModule, "UninitializePlugin");
    if (pfnUnload)
    {
        pfnUnload();
    }

    VERIFY(ClearModuleItems(hModule));
    ReleaseModule(hModule);

    return true;
}

long Cx_PluginLoader::UnloadPlugins()
{
    int i = 0;
    int nUnLoadPluginNum = 0;

    for (i = m_vecModule.size() - 1; i >= 0; i--)
    {
        typedef void (*FUNC_UNLOAD)();
        FUNC_UNLOAD pfnUnload = (FUNC_UNLOAD)GetProcAddress(
            m_vecModule[i].hModule, "UninitializePlugin");
        if (pfnUnload)
        {
            pfnUnload();
        }
    }

    for (i = m_vecModule.size() - 1; i >= 0; i--)
    {
        if (ClearModuleItems(m_vecModule[i].hModule))
        {
            nUnLoadPluginNum++;
        }
    }

    for (i = m_vecModule.size() - 1; i >= 0; i--)
    {
        ReleaseModule(m_vecModule[i].hModule);
    }

    return nUnLoadPluginNum;
}

bool Cx_PluginLoader::issep(wchar_t c)
{
    return ',' == c || ';' == c || iswspace(c);
}

bool Cx_PluginLoader::ClearModuleItems(HMODULE hModule)
{
    ASSERT(hModule);

    Ix_Module* pModule = GetModule(hModule);

    if (pModule)
    {
        pModule->ClearModuleItems();
        return true;
    }

    return false;
}
