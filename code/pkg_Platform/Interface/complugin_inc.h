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
#include <atlcom.h>

using namespace ATL;

struct AtlPluginImpl
{
    static bool IsInitialized();
    static long Initialize(bool delay, LPCWSTR subdir, LPCWSTR plugins);
    static void Uninitialize();
};

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
