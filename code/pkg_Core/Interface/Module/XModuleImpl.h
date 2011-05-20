/*! \file XModuleImpl.h
 *  \brief Implement plugin's export functions and xCreateObject.
 *  \note Include this file in one and only one CPP file of your plugin project.\n
 *        If you don't want to use XModuleMacro.h and this file, then you can use XComCreator.h file.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.05.18
 */
#ifndef X3_PLUGINIMPL_MODULEIMPL_H_
#define X3_PLUGINIMPL_MODULEIMPL_H_

#include "XClassItem.h"
#include "XModuleItem.h"
#include "Cx_Module.h"
#include "Ix_ObjectFactory.h"

#ifndef _MSC_VER
#include "../Portability/portimpl.h"
#endif
#ifdef X3_LOG_DEBUGR_H_
#include "../Log/DebugR.cpp"
#endif

OUTAPI Ix_Module*   _xGetModuleInterface(Ix_ObjectFactory*, HMODULE);
OUTAPI DWORD    _xGetClassEntryTable(DWORD*, DWORD*, _XCLASSMETA_ENTRY*, DWORD);
OUTAPI int      _xInternalCreateObject(const char*, Ix_Object**, HMODULE);
OUTAPI bool     xCanUnloadPlugin();

//! the only one module object in this project.
static Cx_Module    s_xModuleObject;

//! A export function used by the plugin manager.
/*! \ingroup _GROUP_PLUGIN_CORE2_
    \param pFactory the plugin manager object, skip if NULL.
    \param hModule DLL handle of this plugin, skip if NULL.
    \return the module object in this plugin.
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

//! Get class factory registries of the plugin module.
/*! \ingroup _GROUP_PLUGIN_CORE2_
    \param[out] pBuildInfo Fill C++ building info, skip if NULL.
    \param[in,out] pEntrySize Pass in sizeof _XCLASSMETA_ENTRY and fill actual size, skip if NULL.
    \param[out] pTable Pass in array address and fill items. Return actual count if pTable is NULL.
    \param[in] nMaxCount max count of elements in pTable.
    \return element count of actual copied. Return actual count if pTable is NULL.
    \see _xGetModuleInterface, xPluginOnLoad, xPluginOnUnload
*/
OUTAPI DWORD _xGetClassEntryTable(DWORD* pBuildInfo, DWORD* pEntrySize,
                                  _XCLASSMETA_ENTRY* pTable, DWORD nMaxCount)
{
    if (pBuildInfo)
    {
        *pBuildInfo = 0;
#ifdef _MSC_VER
        *pBuildInfo |= (4 | (_MSC_VER << 8));
#endif
#ifdef __GNUC__
        *pBuildInfo |= (8 | (__GNUC__ << 8));
#endif
#ifdef _DEBUG
        *pBuildInfo |= 1;
#endif
    }

    DWORD nEntrySize = sizeof(_XCLASSMETA_ENTRY);

    if (pEntrySize)
    {
        nEntrySize = nEntrySize < *pEntrySize ? nEntrySize : *pEntrySize;
        nEntrySize = nEntrySize ? nEntrySize : sizeof(_XCLASSMETA_ENTRY);
        *pEntrySize = nEntrySize;
    }

    DWORD nClassCount = GetClassCount(0);

    if (NULL == pTable)
    {
        return nClassCount;
    }

    nClassCount = nClassCount < nMaxCount ? nClassCount : nMaxCount;
    for (DWORD i = 0; i < nClassCount; i++)
    {
        memcpy((BYTE*)pTable + i * nEntrySize,
            _XCLASSMETA_ENTRY::s_classes + i, nEntrySize);
    }

    return nClassCount;
}

//! A export function to create object whose class is implement in this project.
/*! \ingroup _GROUP_PLUGIN_CORE2_
    \param clsid class unique id, must be valid.
    \param ppv Pass in a valid address and return a new object.
    \param fromdll DLL handle of the caller's module.
    \return 0 or failed.
    \see _xGetModuleInterface, xCreateObject, _xGetModuleInterface
*/
OUTAPI int _xInternalCreateObject(const char* clsid, Ix_Object** ppv, HMODULE fromdll)
{
    if (NULL == ppv)
        return 1;
    *ppv = NULL;

    XCLSID clsid2(clsid);
    const _XCLASSMETA_ENTRY* pCls = _XCLASSMETA_ENTRY::s_classes;

    for (; pCls->pfnObjectCreator; ++pCls)
    {
        if (clsid2 == pCls->clsid)
        {
            *ppv = (*pCls->pfnObjectCreator)(fromdll);
            return 0;
        }
    }

    return 2;
}

//! Object factory function used by Cx_Interface or Cx_Ptr.
/*! \ingroup _GROUP_PLUGIN_CORE2_
    Autoptr classes (Cx_Interface and Cx_Ptr) will call it. \n
    If you don't want to use this file, then you can use XComCreator.h file.
    \param clsid class unique id, must be valid.
    \param ppv Pass in a valid address and return a new object.
    \return 0 or failed.
    \see _xInternalCreateObject, Ix_ObjectFactory, xIsCreatorRegister
*/
int xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
    if (NULL == ppv)
        return 1;
    *ppv = NULL;

    int hr = 0;
    bool bRetry = true;
    Ix_ObjectFactory* pFactory = s_xModuleObject.GetObjectFactory();

    if (pFactory && pFactory->HasCreatorReplaced(clsid))
    {
        hr = pFactory->CreateObject(clsid, ppv, xGetModuleHandle());
        if (0 == hr)
        {
            return hr;
        }
        bRetry = false;
    }

    hr = _xInternalCreateObject(clsid.str(), ppv, xGetModuleHandle());

    if (hr != 0 && pFactory && bRetry)
    {
        hr = pFactory->CreateObject(clsid, ppv, xGetModuleHandle());
    }

    return hr;
}

//! Return DLL handle of the current plugin module.
//! Using it can check how many objects are used by other modules)
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

#ifdef OutputDebugString
            OutputDebugStringA("> Unfree: ");
            OutputDebugStringA(pCls->className);
#ifdef TRACE1
            TRACE1(", %d", n);
#endif
            OutputDebugStringA("!\n");
#endif // OutputDebugString
        }
    }

    return nTotal;
}

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief Return true if this module can be safe unloaded (there is no object using by other modules).
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
