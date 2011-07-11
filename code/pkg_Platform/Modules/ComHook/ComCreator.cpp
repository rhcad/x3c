#include <UtilFunc/PluginInc.h>
#include "ComCreator.h"
#include "ApiHook.h"
#include "ComFileMap.h"

static const PROC   s_oldfunc = (PROC)CoCreateInstance;
static CComFileMap  s_filemap;
static CComModules  s_modules;

bool CComCreator::Init()
{
    return HookModuleFunction("ole32.dll", s_oldfunc, (PROC)Hook_CoCreateInstance);
}

void CComCreator::Free()
{
    s_modules.Free();
    s_filemap.Free();
    HookModuleFunction("ole32.dll", (PROC)Hook_CoCreateInstance, s_oldfunc);
}

HRESULT WINAPI CComCreator::Hook_CoCreateInstance(
        REFCLSID rclsid, 
        LPUNKNOWN pUnkOuter, DWORD context, 
        REFIID riid, LPVOID FAR* ppv)
{
    if (NULL == ppv)
        return E_POINTER;
    *ppv = NULL;

    HRESULT hr = CreateInstance(rclsid, riid, ppv);

    if (FAILED(hr))
    {
        typedef HRESULT (WINAPI *FUNC_CREATE)(
            REFCLSID, LPUNKNOWN, DWORD, REFIID, OUT LPVOID FAR*);
        hr = ((FUNC_CREATE)s_oldfunc)(rclsid, pUnkOuter, context, riid, ppv);
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

HRESULT CComCreator::CreateInstance(
        REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv)
{
    HMODULE hmod = s_modules.GetModule(s_filemap.GetComFile(tostr(rclsid)));
    HRESULT hr = hmod ? E_FAIL : REGDB_E_CLASSNOTREG;

    if (hmod != NULL)
    {
        IClassFactory* factory = NULL;

        typedef HRESULT (WINAPI *FUNC_GET)(REFCLSID, REFIID, void**);
        FUNC_GET pfnGet = (FUNC_GET)GetProcAddress(hmod, "DllGetClassObject");

        if (pfnGet != NULL)
        {
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
