// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// author: Zhang Yun Gui, Tao Jian Lin
// v1: 2010.12
// v2: 2011.2.4, ooyg: Support absolute path in LoadPlugins().
//          Unload plugin if fail to call InitializePlugins().
//          Reuse element position in RegisterPlugin().
// v3: 2011.02.07, ooyg: Implement the delay-loaded feature.
// v4: 2011.02.08, ooyg: Call SaveClsids() only if clsids have changed.
//          Implement Ix_PluginDelayLoad to support delay-load feature for observer plugins.
// v5: 2011.02.14, ooyg: Ignore folders in GetPluginIndex. Rewrite LoadPlugin().
// v6: 2011.02.16, ooyg: Avoid plugin loading when a plugin is unloading.
//          Counting even a plugin is not loaded in InitializePlugins.
//          Not call ReleaseModule if a plugin is not loaded in UnloadPlugins.
//          Force load ConfigXml plugin if the class file is about to loaded.

#include <PluginInc.h>
#include "Cx_PluginLoader.h"
#include <Ix_AppWorkPath.h>
#include <LockCount.h>
#include <ScanFiles.h>

Cx_PluginLoader::Cx_PluginLoader()
    : m_instance(NULL)
{
    m_inifile[0] = 0;
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
        if (L'/' == *filename)
        {
            *filename = L'\\';
        }
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
        wcsncpy_s(fullpath, MAX_PATH, path, MAX_PATH);
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

class CScanPluginsByExt : public CScanFilesCallback
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

protected:
    std::vector<std::wstring>*  m_files;
    const wchar_t*              m_ext;
    const int                   m_extlen;
};

void Cx_PluginLoader::FindPlugins(std::vector<std::wstring>& filenames,
                                  const wchar_t* path, const wchar_t* ext,
                                  bool recursive)
{
    CScanPluginsByExt scanner(&filenames, ext);
    ScanFiles(&scanner, path, recursive);
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
    VerifyLoadFileNames();

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
                MAX_PATH - len0 < 1 + j - i ? MAX_PATH - len0 : 1 + j - i);
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
    long count = 0;

    for (long i = 0; i < GetSize(m_modules); i++)
    {
        if (m_modules[i].inited)
        {
            continue;
        }
        if (!m_modules[i].hdll) // delay-load
        {
            count++;
            m_modules[i].inited = true;
            continue;
        }

        typedef bool (*FUNC_INIT)();
        FUNC_INIT pfn = (FUNC_INIT)GetProcAddress(
            m_modules[i].hdll, "InitializePlugin");

        if (pfn && !(*pfn)())
        {
            GetModuleFileNameW(m_modules[i].hdll, m_modules[i].filename, MAX_PATH);
            LOG_WARNING2(L"@PluginManager:IDS_INITPLUGIN_FAIL", m_modules[i].filename);
            VERIFY(UnloadPlugin(m_modules[i].filename));
            i--;
        }
        else
        {
            count++;
            m_modules[i].inited = true;
        }
    }

    SaveClsids();

    return count;
}

int Cx_PluginLoader::GetPluginIndex(const wchar_t* filename)
{
    const wchar_t* title = PathFindFileNameW(filename);
    int i = GetSize(m_modules);

    while (--i >= 0)
    {
        // ignore folders
        if (_wcsicmp(title, PathFindFileNameW(m_modules[i].filename)) == 0)
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
    int existIndex = GetPluginIndex(filename);

    if (existIndex >= 0 && m_modules[existIndex].hdll)
    {
        if (_wcsicmp(filename, m_modules[existIndex].filename) != 0)
        {
            LOG_DEBUG2(L"The plugin is already loaded.",
                filename << L", " << (m_modules[existIndex].filename));
        }
        return false;
    }

    HMODULE hdll = LoadLibraryExW(filename);

    if (hdll)
    {
        if (RegisterPlugin(hdll))
        {
            int moduleIndex = FindModule(hdll);

            ASSERT(moduleIndex >= 0);
            ASSERT(existIndex < 0 || existIndex == moduleIndex);

            m_modules[moduleIndex].owned = true;
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
        LOG_WARNING2(L"Fail to load plugin.", filename);
    }

    return hdll != NULL;
}

bool Cx_PluginLoader::UnloadPlugin(const wchar_t* name)
{
    CLockCount locker(&m_unloading);
    int moduleIndex = GetPluginIndex(name);
    HMODULE hdll = moduleIndex < 0 ? NULL : m_modules[moduleIndex].hdll;

    if (NULL == hdll)
    {
        return false;
    }

    typedef bool (*FUNC_CANUNLOAD)();
    FUNC_CANUNLOAD pfnCan = (FUNC_CANUNLOAD)GetProcAddress(
        hdll, "xCanUnloadPlugin");

    if (pfnCan && !pfnCan())
    {
        return false;
    }

    typedef void (*FUNC_UNLOAD)();
    FUNC_UNLOAD pfnUnload = (FUNC_UNLOAD)GetProcAddress(
        hdll, "UninitializePlugin");

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
        ClearModuleItems(m_modules[i].hdll);
    }

    for (i = GetSize(m_modules) - 1; i >= 0; i--)
    {
        if (m_modules[i].hdll)
        {
            ReleaseModule(m_modules[i].hdll);
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

// The configure file of the delay-load feature:
//     <ExePath>\Config\<ExeName>.ini
// The encode of ini file is recommend Unicode.
//
// The class cache file will be saved as <ExePath>\Config\<ExeName>.clsbuf
// You can change the configure path using Ix_AppWorkPath.
//
// Example content of the configure file:
//     [Plugins]
//     Plugin2.plugin.dll==
//     MyExample.plugin.dll==
//     \Example.plugin.dll==
//     /HasSlashCanExactCompare.plugin.dll==
//
// If you want delay-load all plugins, you can add '.plugin.dll' or '.dll' as following:
//     [Plugins]
//     .plugin.dll==
//

void Cx_PluginLoader::VerifyLoadFileNames()
{
    if (0 == m_inifile[0])
    {
        GetModuleFileNameW(m_instance, m_inifile, MAX_PATH);
        PathRenameExtensionW(m_inifile, L".ini");
        std::wstring name(PathFindFileNameW(m_inifile));

        wcsncpy_s(m_inifile, MAX_PATH, GetAppWorkPath().c_str(), MAX_PATH);
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
#ifdef _WIN32
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
#endif
}

bool Cx_PluginLoader::IsDelayPlugin(const wchar_t* filename)
{
    int len = wcslen(filename);
    std::vector<std::wstring>::const_iterator it = m_delayFiles.begin();

    for (; it != m_delayFiles.end(); ++it)
    {
        int len2 = len - GetSize(*it);
        const wchar_t* fnend = &filename[0 > len2 ? 0 : len2];
        if (_wcsicmp(fnend, it->c_str()) == 0)
        {
            break;
        }
    }

    return it != m_delayFiles.end();
}

bool Cx_PluginLoader::LoadPluginOrDelay(const wchar_t* filename)
{
    if (m_unloading != 0 || GetPluginIndex(filename) >= 0)
    {
        return false;
    }

    if (IsDelayPlugin(filename))
    {
        return LoadPluginCache(filename)
            || LoadPlugin(filename) && (BuildPluginCache(filename) || 1);
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
            LOG_WARNING2(L"@PluginManager:IDS_INITPLUGIN_FAIL", filename);
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
        wcsncpy_s(moduleInfo.filename, MAX_PATH, filename, MAX_PATH);

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

    memset(&cls, 0, sizeof(cls));
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
#include <Xml/Ix_ConfigTransaction.h>
#include <ConvStr.h>

bool Cx_PluginLoader::LoadClsids(CLSIDS& clsids, const wchar_t* filename)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile.IsNull() && 0 == m_clsfile[0])
    {
        wcscpy_s(m_clsfile, MAX_PATH, filename);
        PathRemoveFileSpecW(m_clsfile);
        PathAppendW(m_clsfile, L"ConfigXml.plugin" PLNEXT);
        LoadPlugin(m_clsfile);

        wcscpy_s(m_clsfile, MAX_PATH, m_inifile);
        PathRenameExtensionW(m_clsfile, L".clsbuf");

        if (pIFFile.Create(CLSID_ConfigXmlFile))
        {
            m_cache = pIFFile;
            pIFFile->SetFileName(m_clsfile);
        }
    }

    clsids.clear();

    if (pIFFile)
    {
        CConfigIOSection seclist(pIFFile->GetData()->GetSection(NULL,
            L"plugins/plugin", L"filename", PathFindFileNameW(filename), false));
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

    bool has = !clsids.empty();
    if (!has)
    {
        CConfigIOSection seclist(pIFFile->GetData()->GetSection(NULL,
            L"plugins/plugin", L"filename", PathFindFileNameW(filename), false));
        seclist = seclist.GetSection(L"observers", false);
        has = (seclist.GetSectionCount(L"observer") > 0);
    }

    return has;
}

bool Cx_PluginLoader::SaveClsids(const CLSIDS& clsids, const wchar_t* filename)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile)
    {
        CConfigIOSection seclist(pIFFile->GetData()->GetSection(NULL,
            L"plugins/plugin", L"filename", PathFindFileNameW(filename)));

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
    CConfigTransaction autosave(m_cache);
    return autosave.Submit();
}

void Cx_PluginLoader::AddObserverPlugin(HMODULE hdll, const char* obtype)
{
    wchar_t filename[MAX_PATH] = { 0 };

    GetModuleFileNameW(hdll, filename, MAX_PATH);
    if (IsDelayPlugin(filename))
    {
        Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);
        if (pIFFile)
        {
            CConfigIOSection seclist(pIFFile->GetData()->GetSection(NULL,
                L"observers/observer", L"type", std::a2w(obtype).c_str()));
            seclist.GetSection(L"plugin", L"filename", PathFindFileNameW(filename));

            seclist = pIFFile->GetData()->GetSection(NULL,
                L"plugins/plugin", L"filename", PathFindFileNameW(filename));
            seclist.GetSection(L"observers/observer", L"type", std::a2w(obtype).c_str());
        }
    }
}

void Cx_PluginLoader::FireFirstEvent(const char* obtype)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile)
    {
        CConfigIOSection seclist(pIFFile->GetData()->GetSection(NULL,
            L"observers/observer", L"type", std::a2w(obtype).c_str(), false));

        for (int i = 0; i < 999; i++)
        {
            CConfigIOSection sec(seclist.GetSectionByIndex(L"plugin", i));
            std::wstring shortflname(sec->GetString(L"filename"));

            if (shortflname.empty())
            {
                break;
            }

            int moduleIndex = GetPluginIndex(shortflname.c_str());

            if (moduleIndex >= 0 && !m_modules[moduleIndex].hdll)
            {
                LoadDelayPlugin(m_modules[moduleIndex].filename);
            }
        }
    }
}
