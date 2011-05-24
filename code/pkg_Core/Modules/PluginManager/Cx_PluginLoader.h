// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// author: Zhang Yun Gui, Tao Jian Lin
// v1: 2010.12
// v3: 2011.2.7, ooyg: Implement the delay-loaded feature.
// v4: 2011.2.8, ooyg: Implement Ix_PluginDelayLoad to support delay-load feature for observer plugins.

#ifndef _X3_CORE_PLUGINLOADER_H
#define _X3_CORE_PLUGINLOADER_H

#include "Cx_ObjectFactory.h"
#include "Ix_PluginLoader.h"
#include "Ix_PluginDelayLoad.h"

class Cx_PluginLoader
    : public Cx_ObjectFactory
    , public Ix_PluginLoader
    , public Ix_PluginDelayLoad
{
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

    // From Ix_PluginDelayLoad
    //
    virtual void AddObserverPlugin(HMODULE hdll, const char* obtype);
    virtual void FireFirstEvent(const char* obtype);

private:
    Cx_PluginLoader(const Cx_PluginLoader&);
    void operator=(const Cx_PluginLoader&);

    bool issep(wchar_t c);
    bool ClearModuleItems(HMODULE hModule);
    void ReplaceSlashes(wchar_t* filename);
    void MakeFullPath(wchar_t* fullpath, HMODULE instance, const wchar_t* path);
    void FindPlugins(std::vector<std::wstring>& filenames,
        const wchar_t* path, const wchar_t* ext, bool recursive);
    int GetPluginIndex(const wchar_t* filename);
    virtual bool LoadDelayPlugin(const wchar_t* filename);
    void VerifyLoadFileNames();
    void LoadFileNames(const wchar_t* sectionName, const wchar_t* iniFile);
    bool IsDelayPlugin(const wchar_t* filename);
    bool LoadPluginOrDelay(const wchar_t* filename);
    bool BuildPluginCache(const wchar_t* filename);
    bool LoadPluginCache(const wchar_t* filename);
    bool LoadClsids(CLSIDS& clsids, const wchar_t* filename);
    bool SaveClsids(const CLSIDS& clsids, const wchar_t* filename);
    bool SaveClsids();

private:
    HMODULE                     m_instance;
    wchar_t                     m_inifile[MAX_PATH];
    wchar_t                     m_clsfile[MAX_PATH];
    std::vector<std::wstring>   m_delayFiles;
    Cx_Ptr                      m_cache;
};

#endif // _X3_CORE_PLUGINLOADER_H
