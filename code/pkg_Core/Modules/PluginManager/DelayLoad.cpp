// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include "Cx_PluginLoader.h"
#include <UtilFunc/LockCount.h>

bool Cx_PluginLoader::LoadPluginOrDelay(const wchar_t* pluginFile,
                                        bool enableDelayLoading)
{
    if (GetPluginIndex(pluginFile) >= 0)    // Already loaded.
    {
        return true;
    }
    if (m_unloading != 0)                   // Don't load when quiting.
    {
        return false;
    }

    bool ret = false;

    if (enableDelayLoading && m_cache.IsNotNull())
    {
        ret = LoadClsidsFromCache(pluginFile);
        if (!ret && LoadPlugin(pluginFile))
        {
            ret = true;
            BuildPluginCache(GetPluginIndex(pluginFile));
        }
    }
    else
    {
        ret = LoadPlugin(pluginFile);
    }

    return ret;
}

bool Cx_PluginLoader::LoadDelayedPlugin_(const wchar_t* filename)
{
    CLockCount locker(&m_loading);
    bool ret = false;

    if (LoadPlugin(filename))
    {
        int moduleIndex = GetPluginIndex(filename);

        typedef bool (*FUNC_PLUGINLOAD)();
        FUNC_PLUGINLOAD pfn = (FUNC_PLUGINLOAD)GetProcAddress(
            m_modules[moduleIndex]->hdll, "x3InitializePlugin");

        if (pfn && !(*pfn)())
        {
            X3LOG_WARNING2(L"@PluginManager:IDS_INITPLUGIN_FAIL", filename);
            VERIFY(UnloadPlugin(filename));
        }
        else
        {
            m_modules[moduleIndex]->inited = true;
            BuildPluginCache(moduleIndex);
            ret = true;
        }
    }

    return ret;
}

bool Cx_PluginLoader::BuildPluginCache(int moduleIndex)
{
    ASSERT(moduleIndex >= 0);
    const MODULE* module = m_modules[moduleIndex];

    if (GetProcAddress(module->hdll, "DllGetClassObject") != NULL)
    {
        CLockCount locker(&m_loading);
        AddObserverPlugin(module->hdll, "x3::complugin");
    }

    CLSIDS oldids;
    LoadClsids(oldids, module->filename);

    return oldids != module->clsids
        && SaveClsids(module->clsids, module->filename);
}

bool Cx_PluginLoader::LoadClsidsFromCache(const wchar_t* filename)
{
    int moduleIndex = GetPluginIndex(filename);

    if (moduleIndex >= 0 && !m_modules[moduleIndex]->clsids.empty())
    {
        return true;    // this function is already called.
    }

    X3CLASSENTRY cls;
    CLSIDS clsids;

    if (!LoadClsids(clsids, filename))  // No clsid and no observer.
    {
        return false;
    }

    if (moduleIndex < 0)
    {
        MODULE* module = new MODULE;

        module->hdll = NULL;
        module->module = NULL;
        module->owned = false;
        module->inited = false;
        wcscpy_s(module->filename, MAX_PATH, filename);

        moduleIndex = x3::GetSize(m_modules);
        m_modules.push_back(module);
    }

    memset(&cls, 0, sizeof(cls));
    for (CLSIDS::const_iterator it = clsids.begin(); it != clsids.end(); ++it)
    {
        cls.clsid = *it;
        if (m_clsmap.find(cls.clsid.str()) == m_clsmap.end())
        {
            m_clsmap[cls.clsid.str()] = MAPITEM(cls, moduleIndex);
            m_modules[moduleIndex]->clsids.push_back(cls.clsid);
        }
    }

    return true;
}

#include <Xml/Ix_ConfigXml.h>
#include <Xml/Cx_ConfigSection.h>
#include <Xml/Ix_ConfigTransaction.h>
#include <UtilFunc/ConvStr.h>

bool Cx_PluginLoader::LoadCacheFile(const wchar_t* pluginFile)
{
    bool loaded = false;

    if (m_cache.IsNull() && 0 == m_clsfile[0])
    {
        // Ensure ConfigXml.plugin is loaded.
        wcscpy_s(m_clsfile, MAX_PATH, pluginFile);
        PathRemoveFileSpecW(m_clsfile);
        PathAppendW(m_clsfile, L"ConfigXml.plugin" PLNEXT);
        loaded = LoadPlugin(m_clsfile);

        Cx_Interface<Ix_ConfigXml> pIFFile(x3::CLSID_ConfigXmlFile);
        if (pIFFile)
        {
            // Get application name.
            GetModuleFileNameW(m_instance, m_clsfile, MAX_PATH);
            std::wstring appname(PathFindFileNameW(m_clsfile));

            // Make cache file name.
            wcscpy_s(m_clsfile, MAX_PATH, GetWorkPath().c_str());
            PathAppendW(m_clsfile, appname.c_str());
            PathRenameExtensionW(m_clsfile, L".clsbuf");

            pIFFile->SetFileName(m_clsfile);
            pIFFile->SetRootName(L"cache");
            m_cache = pIFFile;

            Cx_ConfigSection root(pIFFile->GetData()->GetSection(L""));
            root->SetString(L"appname", appname.c_str());
        }
    }

    return loaded;
}

bool Cx_PluginLoader::LoadClsids(CLSIDS& clsids, const wchar_t* pluginFile)
{
    const wchar_t* name = PathFindFileNameW(pluginFile);
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);
    Cx_ConfigSection secPlugin;

    clsids.clear();

    if (pIFFile)
    {
        secPlugin = pIFFile->GetData()->GetSection(NULL,
            L"plugins/plugin", L"name", name, false);
        Cx_ConfigSection seclist(secPlugin.GetSection(L"clsids", false));

        for (int i = 0; i < 999; i++)
        {
            Cx_ConfigSection sec(seclist.GetSectionByIndex(L"clsid", i));
            if (!sec->IsValid())
            {
                break;
            }
            X3CLSID clsid(x3::w2a(sec->GetString(L"id")).c_str());
            if (clsid.valid() && x3::find_value(clsids, clsid) < 0)
            {
                clsids.push_back(clsid);
            }
        }
    }

    bool has = !clsids.empty();
    if (!has && secPlugin)
    {
        Cx_ConfigSection seclist(secPlugin.GetSection(L"observers", false));
        has = (seclist.GetSectionCount(L"observer") > 0);
    }

    return has; // Has clsid or observer.
}

bool Cx_PluginLoader::SaveClsids(const CLSIDS& clsids, const wchar_t* pluginFile)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile)
    {
        Cx_ConfigSection secPlugin(pIFFile->GetData()->GetSection(NULL,
            L"plugins/plugin", L"name", PathFindFileNameW(pluginFile)));
        Cx_ConfigSection seclist(secPlugin.GetSection(L"clsids"));

        secPlugin->SetString(L"filename", pluginFile);
        seclist.RemoveChildren(L"clsid");

        for (CLSIDS::const_iterator it = clsids.begin();
            it != clsids.end(); ++it)
        {
            Cx_ConfigSection sec(seclist.GetSection(
                L"clsid", L"id", x3::a2w(it->str()).c_str()));

            X3CLASSENTRY* pEntry = FindEntry(*it);
            if (pEntry && pEntry->pfnObjectCreator)
            {
                sec->SetString(L"class", x3::a2w(pEntry->className).c_str());
            }
        }
    }

    return true;
}

bool Cx_PluginLoader::SaveClsids()
{
    Cx_ConfigTransaction autosave(m_cache);
    return autosave.Submit();
}

void Cx_PluginLoader::AddObserverPlugin(HMODULE hdll, const char* obtype, 
                                        const wchar_t* subtype)
{
    wchar_t filename[MAX_PATH] = { 0 };
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile && m_loading > 0)
    {
        GetModuleFileNameW(hdll, filename, MAX_PATH);
        const wchar_t* name = PathFindFileNameW(filename);

        Cx_ConfigSection secObserver(pIFFile->GetData()->GetSection(NULL,
            L"observers/observer", 
            L"type", x3::a2w(obtype).c_str(), 
            L"subtype", subtype));
        secObserver.GetSection(L"plugin", L"name", name);

        Cx_ConfigSection secPlugin(pIFFile->GetData()->GetSection(NULL,
            L"plugins/plugin", L"name", name));
        secPlugin->SetString(L"filename", filename);
        secPlugin.GetSection(L"observers/observer", L"type", x3::a2w(obtype).c_str());
    }
}

void Cx_PluginLoader::FireFirstEvent(const char* obtype, const wchar_t* subtype)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile)
    {
        Cx_ConfigSection secObserver(pIFFile->GetData()->GetSection(NULL,
            L"observers/observer", 
            L"type", x3::a2w(obtype).c_str(), 
            L"subtype", subtype, false));

        for (int i = 0; i < 999; i++)
        {
            Cx_ConfigSection sec(secObserver.GetSectionByIndex(L"plugin", i));
            std::wstring shortflname(sec->GetString(L"name"));

            if (shortflname.empty())
            {
                break;
            }

            LoadDelayedPlugin(shortflname);
        }
    }
}

bool Cx_PluginLoader::LoadDelayedPlugin(const std::wstring& filename)
{
    int moduleIndex = GetPluginIndex(filename.c_str());

    return moduleIndex >= 0 && (m_modules[moduleIndex]->hdll
        || LoadDelayedPlugin_(m_modules[moduleIndex]->filename));
}
