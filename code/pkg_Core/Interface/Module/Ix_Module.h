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

/*! \file Ix_Module.h
 *  \brief 定义插件模块接口 Ix_Module
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_IMODULE_H_
#define X3_PLUGINIMPL_IMODULE_H_

#include "Ix_Object.h"

interface Ix_ObjectFactory;

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_Module
 *  \brief 插件模块接口
 *  \note  每个插件模块DLL中包含一个Ix_Module对象, 可用 xGetCurrentModule() 得到该对象
 *  \see xGetCurrentModule, xIsCreatorRegister, Ix_ObjectFactory
 */
interface Ix_Module
{
    //! 在卸载模块前释放所有单实例对象
    virtual void ClearModuleItems() = 0;

    //! 返回未释放的对象个数
    virtual long GetUnfreeObjectCount() = 0;

    //! 返回插件管理器对象
    virtual Ix_ObjectFactory* GetObjectFactory() const = 0;

    //! 返回本模块DLL句柄
    virtual HMODULE GetModuleInstance() const = 0;

    //! 返回本模块资源句柄
    virtual HMODULE GetModuleResourceHandle() const = 0;

    //! 设置本模块的资源句柄，当需要支持本地化资源时调用
    virtual HMODULE SetModuleResourceHandle(HMODULE hResource) = 0;
};

//! 返回当前工程内的模块对象
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \return 当前插件模块中唯一的模块对象
*/
Ix_Module* xGetCurrentModule();

//! 返回指定的组件类ID是否已经注册类工厂函数
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \param clsid 组件类ID
    \return 该组件类是否已经注册(即是否已加载其插件)
*/
bool xIsCreatorRegister(const XCLSID& clsid);

#endif // X3_PLUGINIMPL_IMODULE_H_
