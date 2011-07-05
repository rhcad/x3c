/*! \file XModuleImpl.h
 *  \brief Implement plugin's export functions and x3CreateObject.
 *  \note Include this file in one and only one CPP file of your plugin project.\n
 *        If you don't want to use XModuleMacro.h and this file, then you can use XComCreator.h file.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_PLUGINIMPL_MODULEIMPL_H_
#define X3_PLUGINIMPL_MODULEIMPL_H_

#include "XClassItem.h"
#include "XModuleItem.h"
#include "Cx_Module.h"
#include "Ix_ObjectFactory.h"

#include "../Portability/portimpl.h"
#ifdef X3_LOG_DEBUGR_H_
#include "../Log/DebugR.cpp"
#endif

OUTAPI Ix_Module*   x3GetModuleInterface(Ix_ObjectFactory*, HMODULE);
OUTAPI DWORD    x3GetClassEntryTable(DWORD*, DWORD*, X3CLASSENTRY*, DWORD);
OUTAPI int      x3InternalCreateObject(const char*, X3IID, Ix_Object**, HMODULE);
OUTAPI bool     x3CanUnloadPlugin();

//! the only one module object in this project.
static Cx_Module    s_x3Module;

//! A export function used by the plugin manager.
/*! \ingroup _GROUP_PLUGIN_CORE2_
    \param pFactory the plugin manager object, skip if NULL.
    \param hModule DLL handle of this plugin, skip if NULL.
    \return the module object in this plugin.
    \see x3InternalCreateObject, x3GetClassEntryTable
    \see optional export function: OUTAPI bool x3InitializePlugin()
    \see optional export function: OUTAPI void x3UninitializePlugin()
*/
OUTAPI Ix_Module* x3GetModuleInterface(Ix_ObjectFactory* pFactory, HMODULE hModule)
{
    if (pFactory || hModule)
    {
        s_x3Module.Initialize(pFactory, hModule);
    }
    return &s_x3Module;
}

static long GetClassCount(BYTE minType)
{
    int nClassCount = 0;
    const X3CLASSENTRY* pCls = X3CLASSENTRY::s_classes;

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
    \param[in,out] pEntrySize Pass in sizeof X3CLASSENTRY and fill actual size, skip if NULL.
    \param[out] pTable Pass in array address and fill items. Return actual count if pTable is NULL.
    \param[in] nMaxCount max count of elements in pTable.
    \return element count of actual copied. Return actual count if pTable is NULL.
    \see x3GetModuleInterface
    \see optional export function: OUTAPI bool x3InitializePlugin()
    \see optional export function: OUTAPI void x3UninitializePlugin()
*/
OUTAPI DWORD x3GetClassEntryTable(DWORD* pBuildInfo, DWORD* pEntrySize,
                                  X3CLASSENTRY* pTable, DWORD nMaxCount)
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

    DWORD nEntrySize = sizeof(X3CLASSENTRY);

    if (pEntrySize)
    {
        nEntrySize = nEntrySize < *pEntrySize ? nEntrySize : *pEntrySize;
        nEntrySize = nEntrySize ? nEntrySize : sizeof(X3CLASSENTRY);
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
            X3CLASSENTRY::s_classes + i, nEntrySize);
    }

    return nClassCount;
}

//! A export function to create object whose class is implement in this project.
/*! \ingroup _GROUP_PLUGIN_CORE2_
    \param clsid class unique id, must be valid.
    \param iid interface id, see X3DEFINE_IID.
    \param ppv Pass in a valid address and return a new object.
    \param fromdll DLL handle of the caller's module.
    \return 0 or failed.
    \see x3GetModuleInterface, x3CreateObject, x3GetModuleInterface
*/
OUTAPI int x3InternalCreateObject(const char* clsid, X3IID iid, 
                                  Ix_Object** ppv, HMODULE fromdll)
{
    if (NULL == ppv)
        return 1;
    *ppv = NULL;

    X3CLSID clsid2(clsid);
    const X3CLASSENTRY* pCls = X3CLASSENTRY::s_classes;

    for (; pCls->pfnObjectCreator; ++pCls)
    {
        if (clsid2 == pCls->clsid)
        {
            *ppv = (*pCls->pfnObjectCreator)(iid, fromdll);
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
    \param iid interface id, see X3DEFINE_IID.
    \param ppv Pass in a valid address and return a new object.
    \return 0 or failed.
    \see x3InternalCreateObject, Ix_ObjectFactory, x3IsCreatorRegister
*/
int x3CreateObject(const X3CLSID& clsid, X3IID iid, Ix_Object** ppv)
{
    if (NULL == ppv)
        return 1;
    *ppv = NULL;

    int ret = x3InternalCreateObject(clsid.str(), iid, ppv, x3GetModuleHandle());

    if (ret != 0)
    {
        Ix_ObjectFactory* pFactory = s_x3Module.GetObjectFactory();
        if (pFactory)
        {
            ret = pFactory->CreateObject(clsid, iid, ppv, x3GetModuleHandle());
        }
    }

    return ret;
}

//! Return DLL handle of the current plugin module.
//! Using it can check how many objects are used by other modules.
HMODULE x3GetModuleHandle()
{
    return s_x3Module.GetModuleInstance();
}

Ix_Module* x3GetCurrentModule()
{
    return &s_x3Module;
}

Ix_ObjectFactory* x3GetObjectFactory()
{
    return s_x3Module.GetObjectFactory();
}

bool x3IsCreatorRegister(const X3CLSID& clsid)
{
    Ix_ObjectFactory* pFactory = s_x3Module.GetObjectFactory();
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
    Cx_ModuleItem::ClearModuleItems();
}

void Cx_Module::Initialize(Ix_ObjectFactory* pFactory, HMODULE hModule)
{
    bool changed = false;

    if (m_pFactory != pFactory)
    {
        m_pFactory = pFactory;
        changed = true;
    }
    if (hModule && !m_hModule)
    {
        m_hModule = hModule;
        m_hResource = m_hModule;
        changed = true;
    }

    if (changed)
    {
        Cx_ModuleItem::InitModuleItems(GetClassCount(MIN_SINGLETON_TYPE));
    }
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
    const X3CLASSENTRY* pCls = X3CLASSENTRY::s_classes;

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
OUTAPI bool x3CanUnloadPlugin()
{
    const X3CLASSENTRY* pCls = X3CLASSENTRY::s_classes;

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
