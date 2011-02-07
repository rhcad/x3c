// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// author: Zhang Yun Gui, Tao Jian Lin
// v1: 2010.12
// v2: 2011.2.4, ooyg: Support absolute path in LoadPlugins(). 
//          Unload plugin if fail to call InitializePlugins().
//          Reuse element position in RegisterPlugin().
// v3: 2011.2.7, ooyg: Implement the delay-loaded feature.
// v4: 2011.2.8, ooyg: Call SaveClsids() only if clsids have changed.

#include "stdafx.h"
#include "Cx_PluginLoader.h"
#include <Ix_AppWorkPath.h>

Cx_PluginLoader::Cx_PluginLoader()
    : m_instance(NULL)
{
    m_inifile[0] = 0;
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
        if ('/' == *filename)
        {
            *filename = '\\';
        }
    }
}

void Cx_PluginLoader::MakeFullPath(wchar_t* fullpath, HMODULE instance, 
                                   const wchar_t* path)
{
    if (PathIsRelativeW(path) || 0 == path[0])
    {
        GetModuleFileNameW(instance, fullpath, MAX_PATH);
        PathRemoveFileSpecW(fullpath);
        PathAppendW(fullpath, path);
    }
    else
    {
        lstrcpynW(fullpath, path, MAX_PATH);
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
    VerifyLoadFileNames();
    FindPlugins(filenames, fullpath, ext, recursive);

    long count = 0;
    std::vector<std::wstring>::iterator it;

    for (it = filenames.begin(); it != filenames.end(); ++it)
    {
        if (LoadPluginOrDelay(it->c_str()))
        {
            count++;
        }
    }

    return count;
}

void Cx_PluginLoader::FindPlugins(std::vector<std::wstring>& filenames, 
                                  const wchar_t* path, const wchar_t* ext, 
                                  bool recursive)
{
    WIN32_FIND_DATAW fd;
    wchar_t filename[MAX_PATH];
    const int extlen = lstrlenW(ext);
    std::vector<std::wstring> subpaths;

    lstrcpynW(filename, path, MAX_PATH);
    PathAppendW(filename, L"*.*");
    
    HANDLE hFind = ::FindFirstFileW(filename, &fd);
    BOOL bContinue = (hFind != INVALID_HANDLE_VALUE);

    while (bContinue)
    {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (fd.cFileName[0] != '.' && recursive)
            {
                lstrcpynW(filename, path, MAX_PATH);
                PathAppendW(filename, fd.cFileName);
                subpaths.push_back(filename);
            }
        }
        else
        {
            int len = lstrlenW(fd.cFileName);

            if (StrCmpIW(&fd.cFileName[max(0, len - extlen)], ext) == 0)
            {
                lstrcpynW(filename, path, MAX_PATH);
                PathAppendW(filename, fd.cFileName);
                filenames.push_back(filename);
            }
        }
        bContinue = ::FindNextFileW(hFind, &fd);
    }
    ::FindClose(hFind);
    
    std::vector<std::wstring>::const_iterator it = subpaths.begin();
    for (; it != subpaths.end(); ++it)
    {
        FindPlugins(filenames, it->c_str(), ext, recursive);
    }
}

bool Cx_PluginLoader::issep(wchar_t c)
{
    return ',' == c || ';' == c || iswspace(c);
}

long Cx_PluginLoader::LoadPluginFiles(const wchar_t* path, 
                                      const wchar_t* files, 
                                      HMODULE instance)
{
    wchar_t filename[MAX_PATH];

    m_instance = instance;
    MakeFullPath(filename, instance, path);
    VerifyLoadFileNames();
    
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
        if (LoadPluginOrDelay(it->c_str()))
        {
            count++;
        }
    }

    return count;
}

long Cx_PluginLoader::InitializePlugins()
{
    long nSuccessLoadNum = 0;

    for (long i = 0; i < GetSize(m_modules); i++)
    {
        if (m_modules[i].inited || !m_modules[i].hdll)
        {
            continue;
        }

        typedef bool (*FUNC_PLUGINLOAD)();
        FUNC_PLUGINLOAD pfn = (FUNC_PLUGINLOAD)GetProcAddress(
            m_modules[i].hdll, "InitializePlugin");

        if (pfn && !(*pfn)())
        {
            GetModuleFileNameW(m_modules[i].hdll, m_modules[i].filename, MAX_PATH);
            LOG_WARNING2(LOGHEAD L"IDS_INITPLUGIN_FAIL", m_modules[i].filename);
            VERIFY(UnloadPlugin(m_modules[i].filename));
            i--;
        }
        else
        {
            nSuccessLoadNum++;
            m_modules[i].inited = true;
        }
    }

    return nSuccessLoadNum;
}

int Cx_PluginLoader::GetPluginIndex(const wchar_t* filename)
{
    int i = GetSize(m_modules);
    while (--i >= 0 && StrCmpIW(filename, m_modules[i].filename) != 0) ;
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
        MODULEINFO moduleInfo;

        moduleInfo.hdll = instance;
        moduleInfo.module = pModule;
        moduleInfo.owned = false;
        moduleInfo.inited = false;
        GetModuleFileNameW(moduleInfo.hdll, moduleInfo.filename, MAX_PATH);

        int moduleIndex = GetPluginIndex(moduleInfo.filename);
        if (moduleIndex >= 0)
        {
            m_modules[moduleIndex] = moduleInfo;
        }
        else
        {
            m_modules.push_back(moduleInfo);
        }

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
        DisableThreadLibraryCalls(hModule);
    }

    int moduleIndex = FindModule(hModule);
    if (moduleIndex < 0 && RegisterPlugin(hModule))
    {
        moduleIndex = FindModule(hModule);
        ASSERT(moduleIndex >= 0);
        m_modules[moduleIndex].owned = bOwner;
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
    FUNC_CANUNLOAD pfnCan = (FUNC_CANUNLOAD)GetProcAddress(
        hModule, "xCanUnloadPlugin");

    if (pfnCan && !pfnCan())
    {
        return false;
    }

    typedef void (*FUNC_UNLOAD)();
    FUNC_UNLOAD pfnUnload = (FUNC_UNLOAD)GetProcAddress(
        hModule, "UninitializePlugin");

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
    SaveClsids();
    m_cache.Release();

    long i = 0;
    long nUnLoadPluginNum = 0;

    for (i = GetSize(m_modules) - 1; i >= 0; i--)
    {
        typedef void (*FUNC_UNLOAD)();
        FUNC_UNLOAD pfnUnload = (FUNC_UNLOAD)GetProcAddress(
            m_modules[i].hdll, "UninitializePlugin");
        if (pfnUnload)
        {
            pfnUnload();
        }
    }

    for (i = GetSize(m_modules) - 1; i >= 0; i--)
    {
        if (ClearModuleItems(m_modules[i].hdll))
        {
            nUnLoadPluginNum++;
        }
    }

    for (i = GetSize(m_modules) - 1; i >= 0; i--)
    {
        ReleaseModule(m_modules[i].hdll);
    }

    return nUnLoadPluginNum;
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

// The configure file of the delay-loaded feature:
//     <ExePath>\Config\<ExeName>.ini
// Example content:
//     [Plugins]
//     MyPlugin.plugin.dll==
//     Plugin2.plugin.dll==

void Cx_PluginLoader::VerifyLoadFileNames()
{
    if (0 == m_inifile[0])
    {
        GetModuleFileNameW(m_instance, m_inifile, MAX_PATH);
        PathRenameExtensionW(m_inifile, L".ini");
        std::wstring name(PathFindFileNameW(m_inifile));

        lstrcpynW(m_inifile, GetAppWorkPath().c_str(), MAX_PATH);
        PathAppendW(m_inifile, L"Config");
        PathAppendW(m_inifile, name.c_str());

        LoadFileNames(L"Plugins", m_inifile);
    }
}

void Cx_PluginLoader::LoadFileNames(const wchar_t* sectionName, 
                                    const wchar_t* iniFile)
{
    DWORD size = 1024;
	DWORD retsize = size;
	wchar_t* buf = NULL;

    m_delayFiles.clear();

	while (true)
	{
		buf = new wchar_t[size];
		wmemset(buf, 0, size);

		retsize = GetPrivateProfileSectionW(sectionName, buf, size, iniFile);
		if (retsize <= size - sizeof(wchar_t))
        {
            break;
        }
		else
		{
			delete[] buf;
            buf = NULL;
			size += 512;
		}
	}

    for (wchar_t* pw = buf;  *pw != 0;  pw += wcslen(pw) + 1)
    {
        ReplaceSlashes(pw);

        std::wstring filename(pw);
        unsigned pos = filename.find(L'=');

		if (pos != std::wstring::npos)
		{
			filename = filename.substr(0, pos);
            m_delayFiles.push_back(filename);
        }
    }

    delete[] buf;
    buf = NULL;
}

bool Cx_PluginLoader::LoadPluginOrDelay(const wchar_t* filename)
{
    if (FindModule(GetModuleHandleW(filename)) >= 0)
    {
        return false;
    }

    int len = lstrlenW(filename);
    std::vector<std::wstring>::iterator it = m_delayFiles.begin();

    for (; it != m_delayFiles.end(); ++it)
    {
        const wchar_t* fnend = &filename[max(0, len - GetSize(*it))];
        if (StrCmpIW(fnend, it->c_str()) == 0)
        {
            return LoadPluginCache(filename)
                || LoadPlugin(filename) && (BuildPluginCache(filename) || 1);
        }
    }

    return LoadPlugin(filename);
}

bool Cx_PluginLoader::LoadDelayPlugin(const wchar_t* filename)
{
    bool ret = false;

    if (LoadPlugin(filename))
    {
        int moduleIndex = GetPluginIndex(filename);

        typedef bool (*FUNC_PLUGINLOAD)();
        FUNC_PLUGINLOAD pfn = (FUNC_PLUGINLOAD)GetProcAddress(
            m_modules[moduleIndex].hdll, "InitializePlugin");

        if (pfn && !(*pfn)())
        {
            LOG_WARNING2(LOGHEAD L"IDS_INITPLUGIN_FAIL", filename);
            VERIFY(UnloadPlugin(filename));
        }
        else
        {
            m_modules[moduleIndex].inited = true;
            BuildPluginCache(filename);
            ret = true;
        }
    }

    return ret;
}

bool Cx_PluginLoader::BuildPluginCache(const wchar_t* filename)
{
    int moduleIndex = GetPluginIndex(filename);
    ASSERT(moduleIndex >= 0);

    CLSIDS oldids;
    LoadClsids(oldids, filename);

    return oldids != m_modules[moduleIndex].clsids
        && SaveClsids(m_modules[moduleIndex].clsids, filename);
}

bool Cx_PluginLoader::LoadPluginCache(const wchar_t* filename)
{
    int moduleIndex = GetPluginIndex(filename);

    if (moduleIndex < 0)
    {
        MODULEINFO moduleInfo;

        moduleInfo.hdll = NULL;
        moduleInfo.module = NULL;
        moduleInfo.owned = false;
        moduleInfo.inited = false;
        lstrcpynW(moduleInfo.filename, filename, MAX_PATH);

        moduleIndex = GetSize(m_modules);
        m_modules.push_back(moduleInfo);
    }

    if (!m_modules[moduleIndex].clsids.empty())
    {
        return true;
    }

    _XCLASSMETA_ENTRY cls;
    CLSIDS clsids;

    if (!LoadClsids(clsids, filename))
    {
        return false;
    }

    ZeroMemory(&cls, sizeof(cls));
    for (CLSIDS::const_iterator it = clsids.begin(); it != clsids.end(); ++it)
    {
        cls.clsid = *it;
        if (m_clsmap.find(cls.clsid.str()) == m_clsmap.end())
        {
            m_clsmap[cls.clsid.str()] = MAPITEM(cls, moduleIndex);
            m_modules[moduleIndex].clsids.push_back(cls.clsid);
        }
    }

    return true;
}

#include <Xml/Ix_ConfigXml.h>
#include <Xml/ConfigIOSection.h>
#include <ConvStr.h>

bool Cx_PluginLoader::LoadClsids(CLSIDS& clsids, const wchar_t* filename)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile.IsNull())
    {
        wchar_t xmlfile[MAX_PATH];

        lstrcpyW(xmlfile, m_inifile);
        PathRenameExtensionW(xmlfile, L".clsbuf");

        if (pIFFile.Create(CLSID_ConfigXmlFile))
        {
            m_cache = pIFFile;
            pIFFile->SetFileName(xmlfile);
        }
    }

    clsids.clear();

    if (pIFFile)
    {
        CConfigIOSection seclist(pIFFile->GetData()->GetSection(NULL, 
            L"plugin", L"filename", filename, false));
        seclist = seclist.GetSection(L"clsids", false);

        for (int i = 0; i < 999; i++)
        {
            CConfigIOSection sec(seclist.GetSectionByIndex(L"clsid", i));
            if (!sec->IsValid())
            {
                break;
            }
            XCLSID clsid(std::w2a(sec->GetString(L"id")).c_str());
            if (clsid.valid() && find_value(clsids, clsid) < 0)
            {
                clsids.push_back(clsid);
            }
        }
    }

    return !clsids.empty();
}

bool Cx_PluginLoader::SaveClsids(const CLSIDS& clsids, const wchar_t* filename)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile)
    {
        CConfigIOSection seclist(pIFFile->GetData()->GetSection(NULL, 
            L"plugin", L"filename", filename));

        seclist = seclist.GetSection(L"clsids");
        seclist.RemoveChildren(L"clsid");

        for (CLSIDS::const_iterator it = clsids.begin(); 
            it != clsids.end(); ++it)
        {
            CConfigIOSection sec(seclist.GetSection(
                L"clsid", L"id", std::a2w(it->str()).c_str()));

            _XCLASSMETA_ENTRY* pEntry = FindEntry(*it);
            if (pEntry && pEntry->pfnObjectCreator)
            {
                sec->SetString(L"class", std::a2w(pEntry->className).c_str());
            }
        }
    }

    return true;
}

bool Cx_PluginLoader::SaveClsids()
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);
    return pIFFile && pIFFile->Save();
}
