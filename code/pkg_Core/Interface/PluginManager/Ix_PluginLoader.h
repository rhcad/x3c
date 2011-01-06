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

/*! \file Ix_PluginLoader.h
 *  \brief 定义插件加载的接口 Ix_PluginLoader
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_MANAGER_IPLUGINLOADER_H_
#define X3_MANAGER_IPLUGINLOADER_H_

#include "Ix_Object.h"

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_PluginLoader
 *  \brief 插件加载的接口
 *  \see   Ix_ObjectFactory
 */
interface Ix_PluginLoader
{
	//! 加载指定DLL的某个子目录下的所有插件
	/*!
		\param instance 用于指定目录的模块句柄，为NULL则取EXE路径
		\param path 相对目录名，末尾可以不带斜号，例如“Plugins”
		\param ext 插件的后缀名，用于匹配搜索，不区分大小写，
			点号前可以有其他字符，不带问号和星号，例如“.plugin”、“.plugin.dll”、“_core.dll”
		\param recursive 为true时同时加载所有子目录的插件
		\return 加载成功的插件个数
		\note 后续还需要调用 InitializePlugins() 以便执行新加载插件的初始化函数
		\see InitializePlugins, LoadPlugins, LoadPluginFiles
	*/
	virtual long LoadPlugins(HMODULE instance, LPCWSTR path, 
		LPCWSTR ext = L".plugin.dll", bool recursive = true) = 0;

	//! 加载当前EXE的指定目录下的所有插件
	/*!
		\param path 目录名，相对目录或绝对路径，末尾可以不带斜号，例如“Plugins”
		\param ext 插件的后缀名，用于匹配搜索，不区分大小写，
			点号前可以有其他字符，不带问号和星号，例如“.plugin”、“.plugin.dll”、“_core.dll”
		\param recursive 为true时同时加载所有子目录的插件
		\return 加载成功的插件个数
		\note 后续还需要调用 InitializePlugins() 以便执行新加载插件的初始化函数
		\see InitializePlugins, LoadPlugins, LoadPluginFiles
	*/
	virtual long LoadPlugins(LPCWSTR path, 
		LPCWSTR ext = L".plugin.dll", bool recursive = true) = 0;

	//! 加载指定模块的同目录下的多个插件
	/*!
		\param path 相对目录名或空串，例如“Plugins”，空串表示同目录
		\param files 由插件的相对文件名组成，用逗号或空白字符分隔，例如“1.dll, 2.dll”
		\param instance 用于指定目录的模块句柄，一般是主模块，为NULL则取EXE路径
		\return 加载成功的插件个数
		\note 后续还需要调用 InitializePlugins() 以便执行新加载插件的初始化函数
		\see InitializePlugins, LoadPlugins
	*/
	virtual long LoadPluginFiles(LPCWSTR path, LPCWSTR files, HMODULE instance = NULL) = 0;

	//! 初始化所有新加载的插件
	/*! 调用插件的 InitializePlugin 函数，不会重复初始化已有插件
		\return 新初始化的插件的个数(成功调用 InitializePlugin 或其插件未实现该函数的)
	*/
	virtual long InitializePlugins() = 0;

	//! 注册一个插件
	/*! 仅注册插件的类工厂函数，可用于静态链接的动态库插件或调用插件管理器的主模块
		\param instance 要注册的插件的模块句柄
		\return 是否注册成功
		\note 后续还需要调用 InitializePlugins() 以便执行新加载插件的初始化函数
		\see InitializePlugins
	*/
	virtual bool RegisterPlugin(HMODULE instance) = 0;

	//! 加载一个插件
	/*! 使用LoadLibraryEx进行加载，同时注册插件(RegisterPlugin)
		\param filename 插件的文件全名，或相对于EXE的相对文件名
		\return 是否加载成功
		\note 后续还需要调用 InitializePlugins() 以便执行新加载插件的初始化函数
		\see InitializePlugins
	*/
	virtual bool LoadPlugin(LPCWSTR filename) = 0;

	//! 卸载指定名称的插件
	/*!
		\param name 插件文件名，没有路径，例如“MyData.plugin.dll”
		\return 是否卸载成功
	*/
	virtual bool UnloadPlugin(LPCWSTR name) = 0;

	//! 卸载所有插件
	/*! 不再需要插件时调用，一般在程序退出时调用
		\return 本次已卸载的插件个数
	*/
	virtual long UnloadPlugins() = 0;
};

#endif // X3_MANAGER_IPLUGINLOADER_H_
