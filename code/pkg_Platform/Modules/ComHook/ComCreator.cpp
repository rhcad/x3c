#include <UtilFunc/PluginInc.h>
#include "ComCreator.h"
#include "ComFileMap.h"
#include "../Public/ApiHook.h"
#include <UtilFunc/RelToAbs.h>

static const PROC   s_oldfunc = (PROC)CoCreateInstance;
static CComFileMap  s_filemap;
static CComModules  s_modules;

void CComCreator::Free()
{
    s_modules.Free();
    s_filemap.Free();
}

bool CComCreator::Hook(HMODULE hmod)
{
    return HookModuleFunction("ole32.dll", s_oldfunc, (PROC)Hook_CoCreateInstance, hmod);
}

bool CComCreator::Unhook(HMODULE hmod)
{
    return HookModuleFunction("ole32.dll", (PROC)Hook_CoCreateInstance, s_oldfunc, hmod);
}

HRESULT WINAPI CComCreator::Hook_CoCreateInstance(
        REFCLSID rclsid, 
        LPUNKNOWN pUnkOuter, DWORD context, 
        REFIID riid, LPVOID* ppv)
{
    if (NULL == ppv)
        return E_POINTER;
    *ppv = NULL;

    HRESULT hr = LocalCreateInstance(rclsid, riid, ppv);

    if (FAILED(hr))
    {
        typedef HRESULT (WINAPI *FUNC_CREATE)(
            REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID*);
        HRESULT hr2 = ((FUNC_CREATE)s_oldfunc)(rclsid, pUnkOuter, context, riid, ppv);
        if (hr2 != REGDB_E_CLASSNOTREG)
            hr = hr2;
    }

    return hr;
}

static inline std::wstring tostr(REFCLSID rclsid)
{
    LPOLESTR olestr = NULL;
	VERIFY(SUCCEEDED(StringFromCLSID(rclsid, &olestr)));

    std::wstring clsid(olestr);
    CoTaskMemFree(olestr);

    if (L'{' == clsid[0])
    {
        clsid.erase(0, 1);
    }
    if (L'}' == *clsid.rbegin())
    {
        clsid.erase(clsid.find(L'}'));
    }

    return clsid;
}

HRESULT CComCreator::LocalCreateInstance(
        REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    std::wstring filename(s_filemap.GetComFile(tostr(rclsid)));
    if (PathIsRelativeW(filename.c_str()))
        filename = x3::FileNameRelToAbs(filename.c_str());

    HMODULE hmod = s_modules.GetModule(filename);
    HRESULT hr = hmod ? E_FAIL : REGDB_E_CLASSNOTREG;

    if (hmod != NULL)
    {
        IClassFactory* factory = NULL;

        typedef HRESULT (WINAPI *FUNC_GET)(REFCLSID, REFIID, void**);
        FUNC_GET pfnGet = (FUNC_GET)GetProcAddress(hmod, "DllGetClassObject");

        if (pfnGet != NULL)
        {
            const IID IID_IClassFactory = {1,0,0,{0xC0,0,0,0,0,0,0,0x46}};
            hr = (*pfnGet)(rclsid, IID_IClassFactory, (void**)&factory);
        }
        if (factory != NULL)
        {
            hr = factory->CreateInstance(NULL, riid, ppv);
            factory->Release();
        }
    }

    return hr;
}
