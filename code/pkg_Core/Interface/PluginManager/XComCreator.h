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

/*! \file XComCreator.h
 *  \brief Implement xCreateObject() to use Cx_Interface. XModuleMacro.h and XModuleImpl.h are not needed.
 *
 *  \note 本文件用于那些不需要实现组件类，仅需要使用组件接口的工程，不需要包含
 *        XModuleMacro.h 和 XModuleImpl.h 等文件。\n
 *        这些工程一般是单元测试程序、非插件体系的程序、COM控件、简单EXE工程。\n
 *
 *    使用方法：一般将本文件包含到StdAfx.cpp中，只在工程的一个CPP中包含，这样通过实现其中的
 *        xCreateObject 函数来创建组件对象。\n
 *        (1) 如果需要使用多个插件，则不定义USE_ONE_PLUGIN，先使用 PluginManager.h 加载这些插件。\n
 *        (2) 如果仅加载一个插件，则可以不使用PluginManager.h，而是采用简化方法：
 *        先定义 USE_ONE_PLUGIN 后再包含本文件，在外部使用 LoadLibrary 为 g_hPluginDll 赋值。
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */

#ifndef USE_ONE_PLUGIN

#include "Ix_ObjectFactory.h"

HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
    if (NULL == ppv)
        return E_POINTER;
    *ppv = NULL;

    typedef Ix_ObjectFactory* (*FUNC_GET)();
    FUNC_GET pfn = (FUNC_GET)GetProcAddress(
        GetModuleHandleW(L"PluginManagerX3.dll"), "xGetRegisterBank");

    Ix_ObjectFactory* pFactory = pfn ? (*pfn)() : NULL;
    if (NULL == pFactory)
        return E_FAIL;  // plugins must are already loaded using PluginManager.h

    return pFactory->CreateObject(clsid, ppv, NULL);
}

#else // USE_ONE_PLUGIN

// Define USE_ONE_PLUGIN then include this file, and assign module handle (using LoadLibrary) to g_hPluginDll,
// thus xCreateObject() can work and Cx_Interface can be used.

HMODULE     g_hPluginDll = NULL;

HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
    if (NULL == ppv)
        return E_POINTER;
    *ppv = NULL;

    typedef HRESULT (*FUNC_CREATE)(const char*, Ix_Object**, HMODULE);
    FUNC_CREATE pfn = (FUNC_CREATE)GetProcAddress(
        g_hPluginDll, "_xInternalCreateObject");

    return pfn ? (*pfn)(clsid.str(), ppv, NULL) : E_FAIL;
}

#endif // USE_ONE_PLUGIN

HMODULE xGetModuleHandle()
{
    return NULL;
}
