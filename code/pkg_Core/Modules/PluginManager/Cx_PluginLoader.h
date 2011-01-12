// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

    virtual long LoadPlugins(HMODULE instance, LPCWSTR path, 
        LPCWSTR ext = L".plugin.dll", bool recursive = true);
    virtual long LoadPlugins(LPCWSTR path, 
        LPCWSTR ext = L".plugin.dll", bool recursive = true);
    virtual long LoadPluginFiles(LPCWSTR path, 
        LPCWSTR files, HMODULE instance = NULL);
    virtual long InitializePlugins();
    virtual bool RegisterPlugin(HMODULE instance);
    virtual bool LoadPlugin(LPCWSTR filename);
    virtual bool UnloadPlugin(LPCWSTR name);
    virtual long UnloadPlugins();

private:
    bool issep(WCHAR c);
    bool ClearModuleItems(HMODULE hModule);

private:
    HMODULE m_instance;
};

#endif // _X3_CORE_PLUGINLOADER_H
