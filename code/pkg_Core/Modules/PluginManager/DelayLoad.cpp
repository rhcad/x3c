// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include "Cx_PluginLoader.h"

bool Cx_PluginLoader::LoadPluginOrDelay(const wchar_t* pluginFile)
{
    if (GetPluginIndex(pluginFile) >= 0)
    {
        return true;
    }
    if (m_unloading != 0)
    {
        return false;
    }

    bool ret = false;

    if (m_cache)
    {
        ret = LoadPluginCache(pluginFile)
            || (LoadPlugin(pluginFile) && (BuildPluginCache(pluginFile) || 1));
    }
    else
    {
        ret = LoadPlugin(pluginFile);
    }

    return ret;
}

bool Cx_PluginLoader::LoadDelayPlugin(const wchar_t* filename)
{
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
            BuildPluginCache(filename);
            ret = true;
        }
    }

    return ret;
}

bool Cx_PluginLoader::BuildPluginCache(const wchar_t* pluginFile)
{
    int moduleIndex = GetPluginIndex(pluginFile);
    ASSERT(moduleIndex >= 0);

    CLSIDS oldids;
    LoadClsids(oldids, pluginFile);

    return oldids != m_modules[moduleIndex]->clsids
        && SaveClsids(m_modules[moduleIndex]->clsids, pluginFile);
}

bool Cx_PluginLoader::LoadPluginCache(const wchar_t* filename)
{
    int moduleIndex = GetPluginIndex(filename);

    if (moduleIndex >= 0 && !m_modules[moduleIndex]->clsids.empty())
    {
        return true;
    }

    X3CLASSENTRY cls;
    CLSIDS clsids;

    if (!LoadClsids(clsids, filename))
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
        wcsncpy_s(module->filename, MAX_PATH, filename, MAX_PATH);

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
            wcsncpy_s(m_clsfile, MAX_PATH, GetWorkPath().c_str(), MAX_PATH);
            PathAppendW(m_clsfile, appname.c_str());
            PathRenameExtensionW(m_clsfile, L".clsbuf");

            pIFFile->SetFileName(m_clsfile);
            m_cache = pIFFile;
        }
    }

    return loaded;
}

bool Cx_PluginLoader::LoadClsids(CLSIDS& clsids, const wchar_t* pluginFile)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    clsids.clear();

    if (pIFFile)
    {
        Cx_ConfigSection seclist(pIFFile->GetData()->GetSection(NULL,
            L"plugins/plugin", L"filename", PathFindFileNameW(pluginFile), false));
        seclist = seclist.GetSection(L"clsids", false);

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
    if (!has)
    {
        Cx_ConfigSection seclist(pIFFile->GetData()->GetSection(NULL,
            L"plugins/plugin", L"filename", PathFindFileNameW(pluginFile), false));
        seclist = seclist.GetSection(L"observers", false);
        has = (seclist.GetSectionCount(L"observer") > 0);
    }

    return has;
}

bool Cx_PluginLoader::SaveClsids(const CLSIDS& clsids, const wchar_t* pluginFile)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile)
    {
        Cx_ConfigSection seclist(pIFFile->GetData()->GetSection(NULL,
            L"plugins/plugin", L"filename", PathFindFileNameW(pluginFile)));

        seclist = seclist.GetSection(L"clsids");
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

void Cx_PluginLoader::AddObserverPlugin(HMODULE hdll, const char* obtype)
{
    wchar_t filename[MAX_PATH] = { 0 };
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile)
    {
        GetModuleFileNameW(hdll, filename, MAX_PATH);

        Cx_ConfigSection seclist(pIFFile->GetData()->GetSection(NULL,
            L"observers/observer", L"type", x3::a2w(obtype).c_str()));
        seclist.GetSection(L"plugin", L"filename", PathFindFileNameW(filename));

        seclist = pIFFile->GetData()->GetSection(NULL,
            L"plugins/plugin", L"filename", PathFindFileNameW(filename));
        seclist.GetSection(L"observers/observer", L"type", x3::a2w(obtype).c_str());
    }
}

void Cx_PluginLoader::FireFirstEvent(const char* obtype)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(m_cache);

    if (pIFFile)
    {
        Cx_ConfigSection seclist(pIFFile->GetData()->GetSection(NULL,
            L"observers/observer", L"type", x3::a2w(obtype).c_str(), false));

        for (int i = 0; i < 999; i++)
        {
            Cx_ConfigSection sec(seclist.GetSectionByIndex(L"plugin", i));
            std::wstring shortflname(sec->GetString(L"filename"));

            if (shortflname.empty())
            {
                break;
            }

            int moduleIndex = GetPluginIndex(shortflname.c_str());

            if (moduleIndex >= 0 && !m_modules[moduleIndex]->hdll)
            {
                LoadDelayPlugin(m_modules[moduleIndex]->filename);
            }
        }
    }
}
