// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
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

/*! \file PluginManager.h
 *  \brief 定义插件管理器DLL的封装类
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_MANAGER_PLUGINMANAGER_H_
#define X3_MANAGER_PLUGINMANAGER_H_

#include "Ix_ObjectFactory.h"
#include "Ix_PluginLoader.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \brief 插件管理器DLL的封装类
 *  \see   Ix_ObjectFactory, Ix_PluginLoader
 */
class CPluginManager
{
public:
	CPluginManager() : m_dll(NULL)
	{
		lstrcpyW(m_filename, L"PluginManagerX3.dll");
	}

	~CPluginManager()
	{
		Unload();
	}

	//! 卸载插件管理器DLL
	void Unload(bool all = false)
	{
		if (all || m_dll)
		{
			Ix_PluginLoader* pLoader = GetPluginLoader();
			if (pLoader != NULL)
			{
				pLoader->UnloadPlugins();
			}
		}
		if (m_dll != NULL)
		{
			FreeLibrary(m_dll);
			m_dll = NULL;
		}
	}

	//! 加载插件管理器
	bool LoadPluginManager(LPCWSTR subdir, HMODULE instance = NULL)
	{
		GetModuleFileNameW(instance, m_filename, MAX_PATH);
		PathRemoveFileSpecW(m_filename);
		PathAppendW(m_filename, subdir);
		PathAppendW(m_filename, L"PluginManagerX3.dll");

		if (GetModuleHandleW(m_filename) || m_dll)
		{
			return true;
		}

		m_dll = LoadLibraryW(m_filename);
		return m_dll != NULL;
	}

	//! 加载核心插件和插件管理器
	bool LoadCorePlugins(LPCWSTR subdir, HMODULE instance = NULL)
	{
		if (!LoadPluginManager(subdir, instance))
		{
			return false;
		}

		Ix_PluginLoader* pLoader = GetPluginLoader();
		if (pLoader)
		{
			long n = pLoader->LoadPluginFiles(subdir, 
				L"LogManager.plugin.dll, "
				L"LogWriter.plugin.dll, "
				L"ConfigXml.plugin.dll, "
				L"StringTable.plugin.dll, "
				L"ChangeManager.plugin.dll, "
				L"FileUtility.plugin.dll, "
				L"PluginManagerEx.plugin.dll", instance);

			if (pLoader->InitializePlugins() > 0 && n > 0)
			{
				return true;
			}
		}

		return false;
	}

	//! 返回对象创建工厂接口对象
	Ix_ObjectFactory* GetObjectFactory()
	{
		typedef Ix_ObjectFactory* (*FUNC_GETREGISTERBANK)();
		FUNC_GETREGISTERBANK pfn = (FUNC_GETREGISTERBANK)GetProcAddress(
			GetModuleHandleW(m_filename), "xGetRegisterBank");

		return pfn ? (*pfn)() : NULL;
	}

	//! 返回插件加载的接口对象
	Ix_PluginLoader* GetPluginLoader()
	{
		return dynamic_cast<Ix_PluginLoader*>(GetObjectFactory());
	}

private:
	HMODULE		m_dll;
	WCHAR		m_filename[MAX_PATH];
};

#endif // X3_MANAGER_PLUGINMANAGER_H_
