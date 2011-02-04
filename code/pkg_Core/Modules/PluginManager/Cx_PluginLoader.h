// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// author: Zhang Yun Gui, Tao Jian Lin
// v1: 2010.12

#ifndef _X3_CORE_PLUGINLOADER_H
#define _X3_CORE_PLUGINLOADER_H

#include "Cx_ObjectFactory.h"
#include "Ix_PluginLoader.h"

class Cx_PluginLoader
    : public Cx_ObjectFactory
    , public Ix_PluginLoader
{
public:
    Cx_PluginLoader();
    virtual ~Cx_PluginLoader();

    HMODULE GetMainModuleHandle();

    virtual long LoadPlugins(HMODULE instance, const wchar_t* path, 
        const wchar_t* ext = L".plugin.dll", bool recursive = true);
    virtual long LoadPlugins(const wchar_t* path, 
        const wchar_t* ext = L".plugin.dll", bool recursive = true);
    virtual long LoadPluginFiles(const wchar_t* path, 
        const wchar_t* files, HMODULE instance = NULL);
    virtual long InitializePlugins();
    virtual bool RegisterPlugin(HMODULE instance);
    virtual bool LoadPlugin(const wchar_t* filename);
    virtual bool UnloadPlugin(const wchar_t* name);
    virtual long UnloadPlugins();

private:
    bool issep(wchar_t c);
    bool ClearModuleItems(HMODULE hModule);
    void ReplaceSlashes(wchar_t* filename);
    void MakeFullPath(wchar_t* fullpath, HMODULE instance, const wchar_t* path);

private:
    HMODULE m_instance;
};

#endif // _X3_CORE_PLUGINLOADER_H
