/*! \file complugin_inc.h
 *  \brief Include files for COM plugin project.
 *  \note Include this file in stdafx.h of COM plugin project.
 *  \see complugin_impl.h
 */
#ifndef X3_COMPLUGIN_INC_H_
#define X3_COMPLUGIN_INC_H_

#ifndef STRICT
#define STRICT
#endif

#include <UtilFunc/PluginInc.h>

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

#include <atlbase.h>

struct AtlPluginImpl
{
    static bool IsInitialized();
    static long Initialize(bool delay, LPCWSTR subdir, LPCWSTR plugins);
    static void Uninitialize();
};

#if _MSC_VER > 1200

#define ATLDLLMAIN(hInstance, dwReason, lpReserved) \
    (hInstance, _AtlModule.DllMain(dwReason, lpReserved))

#else

#define _Module (*_pModule)
#define _AtlBaseModule _AtlModule

#define ATLDLLMAIN(hInstance, dwReason, lpReserved) \
    _AtlModule.DllMain_vc6(ObjectMap, hInstance, dwReason, lpReserved)

#define DECLARE_LIBID(libid) \
    static void InitLibId() throw() \
    { \
        CComModule::m_libid = libid; \
    }

#define DECLARE_REGISTRY_APPID_RESOURCEID(resid, appid) \
    static LPCOLESTR GetAppId() throw() \
    { \
        return OLESTR(appid); \
    }

template <class T>
class ATL_NO_VTABLE CAtlDllModuleT : public CComModule
{
public:
    CAtlDllModuleT()
    {
    }
    
    BOOL DllMain_vc6(_ATL_OBJMAP_ENTRY* pObjMap, HINSTANCE hInstance, DWORD dwReason, LPVOID) throw()
    {
        if (dwReason == DLL_PROCESS_ATTACH)
        {
            T::InitLibId();
            CComModule::Init(pObjMap, hInstance, &CComModule::m_libid);
            DisableThreadLibraryCalls(hInstance);
        }
        else if (dwReason == DLL_PROCESS_DETACH)
        {
            AtlPluginImpl::Uninitialize();
            CComModule::Term();
        }
        return TRUE;
    }
    
    HRESULT DllCanUnloadNow() throw()
    {
        return (CComModule::GetLockCount()==0) ? S_OK : S_FALSE;
    }
    
    HRESULT DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) throw()
    {
        return CComModule::GetClassObject(rclsid, riid, ppv);
    }
    
    HRESULT DllRegisterServer(BOOL bRegTypeLib = TRUE) throw()
    {
        return CComModule::RegisterServer(bRegTypeLib);
    }
    
    HRESULT DllUnregisterServer(BOOL bUnRegTypeLib = TRUE) throw()
    {
        return CComModule::UnregisterServer(bUnRegTypeLib);
    }
};

#endif // _MSC_VER

#include <atlcom.h>

using namespace ATL;

//! Declare plugins to be used by this module.
/*!
    \param delay enable delay-loading feature or not.
    \param path plugin path relative to this module.
    \param plugins include filename of plugins, separated by spaces or comma
*/
#define DECLARE_PLUGINS(delay, path, plugins) \
    static LPCWSTR GetPluginPath() throw() { return path; } \
    static LPCWSTR GetPlugins() throw() { return plugins; } \
    static bool IsEnableDelayLoading() throw() { return delay; }

template <class T, class AtlBase = CAtlDllModuleT<T> >
class ATL_NO_VTABLE CAtlPluginT : public AtlBase
{
public :
    CAtlPluginT() throw()
    {
    }
    
    ~CAtlPluginT() throw()
    {
    }
    
    BOOL WINAPI DllMain(DWORD dwReason, LPVOID lpReserved) throw()
    {
        if (DLL_PROCESS_DETACH == dwReason)
        {
            AtlPluginImpl::Uninitialize();
        }
        
        return AtlBase::DllMain(dwReason, lpReserved);
    }
    
    HRESULT DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) throw()
    {
        if (!AtlPluginImpl::IsInitialized())
        {
            AtlPluginImpl::Initialize(T::IsEnableDelayLoading(), 
                T::GetPluginPath(), T::GetPlugins());
        }
        
        return AtlBase::DllGetClassObject(rclsid, riid, ppv);
    }
};

#endif // X3_COMPLUGIN_INC_H_
