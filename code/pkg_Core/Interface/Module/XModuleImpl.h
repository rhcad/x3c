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

/*! \file XModuleImpl.h
 *  \brief 实现插件模块的导出函数和 xCreateObject 等全局函数
 *  \note 在工程中的一个CPP文件中包含本文件，且只能在一个CPP文件中包含本文件。\n
 *        如果不希望使用本文件和 XModuleMacro.h 等文件，可使用 XComCreator.h 文件。
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_MODULEIMPL_H_
#define X3_PLUGINIMPL_MODULEIMPL_H_

#include "XClassItem.h"
#include "XModuleItem.h"
#include "Cx_Module.h"
#include "Ix_ObjectFactory.h"

#define OUTAPI  extern "C" __declspec(dllexport)

OUTAPI Ix_Module*   _xGetModuleInterface(Ix_ObjectFactory*, HMODULE);
OUTAPI DWORD    _xGetClassEntryTable(DWORD*, DWORD*, _XCLASSMETA_ENTRY*, DWORD);
OUTAPI HRESULT  _xInternalCreateObject(const char*, Ix_Object**, HMODULE);
OUTAPI bool     xCanUnloadPlugin();

static Cx_Module    s_xModuleObject;    // 全局唯一的插件模块对象

//! 插件模块的导出函数，供插件管理器使用
/*! \ingroup _GROUP_PLUGIN_CORE2_
    \param pFactory 插件管理器对象，为NULL则忽略
    \param hModule 本插件模块的DLL句柄，为NULL则忽略
    \return 本插件模块的唯一模块对象
    \see _xInternalCreateObject, _xGetClassEntryTable, xPluginOnLoad, xPluginOnUnload
*/
OUTAPI Ix_Module* _xGetModuleInterface(Ix_ObjectFactory* pFactory, HMODULE hModule)
{
    if (pFactory || hModule)
    {
        s_xModuleObject.Initialize(pFactory, hModule);
    }
    return &s_xModuleObject;
}

static long GetClassCount(BYTE minType)
{
    int nClassCount = 0;
    const _XCLASSMETA_ENTRY* pCls = _XCLASSMETA_ENTRY::s_classes;

    for (; pCls->pfnObjectCreator; ++pCls)
    {
        if (pCls->type >= minType)
        {
            nClassCount++;
        }
    }

    return nClassCount;
}

//! 获得本插件模块的组件类信息表
/*! \ingroup _GROUP_PLUGIN_CORE2_
    \param[out] pBuildInfo 填充VC++构建信息，为NULL时忽略该参数
    \param[in,out] pEntrySize 输入和填充 _XCLASSMETA_ENTRY 的大小，为NULL时忽略该参数
    \param[out] pTable 输入数组地址，填充组件类信息项，为NULL时返回实际元素个数
    \param[in] nMaxCount 缓冲pTable的元素最多个数
    \return 实际复制的元素个数，pTable为NULL时为实际元素个数
    \see _xGetModuleInterface, xPluginOnLoad, xPluginOnUnload
*/
OUTAPI DWORD _xGetClassEntryTable(DWORD* pBuildInfo, DWORD* pEntrySize, 
                                  _XCLASSMETA_ENTRY* pTable, DWORD nMaxCount)
{
    if (pBuildInfo)
    {
        *pBuildInfo = _MSC_VER << 2;
#ifdef _DEBUG
        *pBuildInfo |= 1;
#endif
    }

    DWORD nEntrySize = sizeof(_XCLASSMETA_ENTRY);

    if (pEntrySize)
    {
        nEntrySize = min(nEntrySize, *pEntrySize);
        nEntrySize = nEntrySize ? nEntrySize : sizeof(_XCLASSMETA_ENTRY);
        *pEntrySize = nEntrySize;
    }

    DWORD nClassCount = GetClassCount(0);

    if (NULL == pTable)
    {
        return nClassCount;
    }

    nClassCount = min(nClassCount, nMaxCount);
    for (DWORD i = 0; i < nClassCount; i++)
    {
        memcpy((LPBYTE)pTable + i * nEntrySize, 
            _XCLASSMETA_ENTRY::s_classes + i, nEntrySize);
    }

    return nClassCount;
}

//! 仅在本工程内创建对象的导出函数
/*! \ingroup _GROUP_PLUGIN_CORE2_
    \param clsid 组件类UID，必须有效
    \param ppv 填充创建的对象，必须为有效地址
    \param fromdll 调用者所在模块的DLL句柄
    \return S_OK 表示成功，其余失败
    \see _xGetModuleInterface, xCreateObject, _xGetModuleInterface
*/
OUTAPI HRESULT _xInternalCreateObject(const char* clsid, Ix_Object** ppv, HMODULE fromdll)
{
    if (NULL == ppv)
        return E_POINTER;
    *ppv = NULL;

    XCLSID clsid2(clsid);
    const _XCLASSMETA_ENTRY* pCls = _XCLASSMETA_ENTRY::s_classes;

    for (; pCls->pfnObjectCreator; ++pCls)
    {
        if (clsid2 == pCls->clsid)
        {
            *ppv = (*pCls->pfnObjectCreator)(fromdll);
            return S_OK;
        }
    }

    return E_NOINTERFACE;
}

//! 供本工程使用的对象创建函数
/*! \ingroup _GROUP_PLUGIN_CORE2_
    智能指针类 Cx_Interface 和 Cx_Ptr 会调用本函数，
    如果不希望使用XModuleImpl.h等文件，可使用 XComCreator.h 文件。

    \param clsid 组件类UID，必须有效
    \param ppv 填充创建的对象，必须为有效地址
    \return S_OK 表示成功，其余失败
    \see _xInternalCreateObject, Ix_ObjectFactory, xIsCreatorRegister
*/
HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
    if (NULL == ppv)
        return E_POINTER;
    *ppv = NULL;

    HRESULT hr;
    bool bRetry = true;
    Ix_ObjectFactory* pFactory = s_xModuleObject.GetObjectFactory();

    if (pFactory && pFactory->HasCreatorReplaced(clsid))
    {
        hr = pFactory->CreateObject(clsid, ppv, xGetModuleHandle());
        if (S_OK == hr)
        {
            return hr;
        }
        bRetry = false;
    }

    hr = _xInternalCreateObject(clsid.str(), ppv, xGetModuleHandle());

    if (FAILED(hr) && pFactory && bRetry)
    {
        hr = pFactory->CreateObject(clsid, ppv, xGetModuleHandle());
    }

    return hr;
}

//! 返回当前插件模块的DLL句柄，用于记录其他模块是否使用其内部组件对象
HMODULE xGetModuleHandle()
{
    return s_xModuleObject.GetModuleInstance();
}

Ix_Module* xGetCurrentModule()
{
    return &s_xModuleObject;
}

bool xIsCreatorRegister(const XCLSID& clsid)
{
    Ix_ObjectFactory* pFactory = s_xModuleObject.GetObjectFactory();
    return pFactory && pFactory->IsCreatorRegister(clsid);
}

Cx_Module::Cx_Module() : m_pFactory(NULL), m_hModule(NULL), m_hResource(NULL)
{
}

Cx_Module::~Cx_Module()
{
}

void Cx_Module::ClearModuleItems()
{
    CModuleItem::ClearModuleItems();
}

void Cx_Module::Initialize(Ix_ObjectFactory* pFactory, HMODULE hModule)
{
    m_pFactory = pFactory;

    if (hModule && !m_hModule)
    {
        m_hModule = hModule;
        m_hResource = m_hModule;
    }

    CModuleItem::InitModuleItems(GetClassCount(MIN_SINGLETON_TYPE));
}

HMODULE Cx_Module::SetModuleResourceHandle(HMODULE hResource)
{
    HMODULE hOld = m_hResource;
    m_hResource = (NULL == hResource) ? m_hModule : hResource;
    return hOld;
}

long Cx_Module::GetUnfreeObjectCount()
{
    long n, nTotal = 0;
    const _XCLASSMETA_ENTRY* pCls = _XCLASSMETA_ENTRY::s_classes;

    for (; pCls->pfnObjectCreator; ++pCls)
    {
        PFNXGetObjectCount pfn = pCls->pfnGetObjectCount;
        if (pfn && (n = (*pfn)()) > 0)
        {
            nTotal += n;

            OutputDebugStringA("> Unfree: ");
            OutputDebugStringA(pCls->className);
#ifdef TRACE1
            TRACE1(", %d", n);
#endif
            OutputDebugStringA("!\n");
        }
    }

    return nTotal;
}

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief 返回本模块是否可以安全卸载，即没有其他模块正在使用其内部组件对象
 */
OUTAPI bool xCanUnloadPlugin()
{
    const _XCLASSMETA_ENTRY* pCls = _XCLASSMETA_ENTRY::s_classes;

    for (; pCls->pfnObjectCreator; ++pCls)
    {
        PFNXRefCountByOthers pfn = pCls->pfnRefCountByOthers;
        long n = 0;

        if (pfn && (n = (*pfn)()) > 0)
        {
            return false;
        }
    }

    return true;
}

#endif // X3_PLUGINIMPL_MODULEIMPL_H_
