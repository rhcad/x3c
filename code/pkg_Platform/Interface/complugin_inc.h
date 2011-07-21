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
    static HINSTANCE hInstance;
    static bool IsPluginLoaded();
    static long LoadPlugins(bool delay, LPCWSTR subdir, LPCWSTR plugins);
    static void UnloadPlugins();
};

#if _MSC_VER <= 1200

#define _Module (*_pModule)
#define _AtlBaseModule _AtlModule

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

ATL::_ATL_OBJMAP_ENTRY* GetObjectMap();

template <class T>
class ATL_NO_VTABLE CAtlDllModuleT : public CComModule
{
public:
    CAtlDllModuleT()
    {
    }

    BOOL WINAPI DllMain(DWORD dwReason, LPVOID lpReserved) throw()
    {
        if (dwReason == DLL_PROCESS_ATTACH)
        {
            T::InitLibId();
            CComModule::Init(GetObjectMap(), AtlPluginImpl::hInstance, &CComModule::m_libid);
            DisableThreadLibraryCalls(AtlPluginImpl::hInstance);
        }
        else if (dwReason == DLL_PROCESS_DETACH)
        {
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

#include <atlcom.h>
using namespace ATL;

template <class T>
class ATL_NO_VTABLE CAtlPluginT : public CAtlDllModuleT<T>
{
public :
    CAtlPluginT() throw()
    {
    }
    
    BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) throw()
    {
        if (dwReason == DLL_PROCESS_ATTACH)
        {
            AtlPluginImpl::hInstance = hInstance;
        }
        else if (dwReason == DLL_PROCESS_DETACH)
        {
            AtlPluginImpl::UnloadPlugins();
        }
        
        return CAtlDllModuleT<T>::DllMain(dwReason, lpReserved);
    }
    
    HRESULT DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) throw()
    {
        if (!AtlPluginImpl::IsPluginLoaded())
        {
            AtlPluginImpl::LoadPlugins(T::IsEnableDelayLoading(), 
                T::GetPluginPath(), T::GetPlugins());
        }
        
        return CAtlDllModuleT<T>::DllGetClassObject(rclsid, riid, ppv);
    }

private:
    BOOL DllMain(DWORD,LPVOID); // Use DllMain(HINSTANCE, DWORD, LPVOID)
};

#endif // X3_COMPLUGIN_INC_H_
