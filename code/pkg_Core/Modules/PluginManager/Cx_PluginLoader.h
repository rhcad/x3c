// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef _X3_CORE_PLUGINLOADER_H
#define _X3_CORE_PLUGINLOADER_H

#include "Cx_ObjectFactory.h"
#include <PluginManager/Ix_PluginLoader.h>
#include <PluginManager/Ix_PluginLoader2.h>
#include <PluginManager/Ix_AppWorkPath.h>
#include <PluginManager/Ix_PluginDelayLoad.h>

class Cx_PluginLoader
    : public Cx_ObjectFactory
    , public Ix_PluginLoader
    , public Ix_PluginLoader2
    , public Ix_PluginDelayLoad
    , public Ix_AppWorkPath
{
    X3BEGIN_CLASS_DECLARE(Cx_PluginLoader)
        X3DEFINE_INTERFACE_ENTRY(Ix_PluginLoader)
        X3DEFINE_INTERFACE_ENTRY(Ix_PluginLoader2)
        X3DEFINE_INTERFACE_ENTRY(Ix_PluginDelayLoad)
        X3DEFINE_INTERFACE_ENTRY(Ix_AppWorkPath)
        X3USE_INTERFACE_ENTRY(Cx_ObjectFactory)
    X3END_CLASS_DECLARE()
public:
    Cx_PluginLoader();
    virtual ~Cx_PluginLoader();

    HMODULE GetMainModuleHandle();

    // From Ix_PluginLoader
    //
    virtual long LoadPlugins(HMODULE instance, const wchar_t* path,
        const wchar_t* ext = L".plugin" PLNEXT, bool recursive = true);
    virtual long LoadPlugins(const wchar_t* path,
        const wchar_t* ext = L".plugin" PLNEXT, bool recursive = true);
    virtual long LoadPluginFiles(const wchar_t* path,
        const wchar_t* files, HMODULE instance = NULL);
    virtual long InitializePlugins();
    virtual bool RegisterPlugin(HMODULE instance);
    virtual bool LoadPlugin(const wchar_t* filename);
    virtual bool UnloadPlugin(const wchar_t* name);
    virtual long UnloadPlugins();

    // From Ix_PluginLoader2
    //
    virtual long GetPluginCount();
    virtual bool GetPluginFileName(long index, HMODULE& hdll, std::wstring& filename);

    // From Ix_PluginDelayLoad
    //
    virtual void AddObserverPlugin(HMODULE hdll, const char* obtype, const wchar_t* subtype = L"");
    virtual void FireFirstEvent(const char* obtype, const wchar_t* subtype = L"");
    virtual bool LoadDelayedPlugin(const std::wstring& filename);

    // Ix_AppWorkPath, implemented in Cx_PluginLoaderOut.
    virtual std::wstring GetWorkPath() { ASSERT(0); return L""; }
    virtual void SetWorkPath(const std::wstring&) { ASSERT(0); }
    virtual std::wstring GetLocalAppDataPath(const wchar_t*) { ASSERT(0); return L""; }

private:
    Cx_PluginLoader(const Cx_PluginLoader&);
    void operator=(const Cx_PluginLoader&);

    bool issep(wchar_t c);
    bool ClearModuleItems(HMODULE hModule);
    void ReplaceSlashes(wchar_t* filename);
    void MakeFullPath(wchar_t* fullpath, HMODULE instance, const wchar_t* path);
    void FindPlugins(std::vector<std::wstring>& filenames,
        const wchar_t* path, const wchar_t* ext, bool recursive);
    long InLoadPlugins(const std::vector<std::wstring>& filenames);
    int GetPluginIndex(const wchar_t* filename);
    virtual bool LoadDelayedPlugin_(const wchar_t* filename);
    bool LoadPluginOrDelay(const wchar_t* pluginFile);
    bool BuildPluginCache(int moduleIndex);
    bool LoadClsidsFromCache(const wchar_t* pluginFile);
    bool LoadCacheFile(const wchar_t* pluginFile);
    bool LoadClsids(CLSIDS& clsids, const wchar_t* pluginFile);
    bool SaveClsids(const CLSIDS& clsids, const wchar_t* pluginFile);
    bool SaveClsids();

private:
    HMODULE                     m_instance;
    wchar_t                     m_clsfile[MAX_PATH];
    Cx_Ptr                      m_cache;
};

#endif // _X3_CORE_PLUGINLOADER_H
