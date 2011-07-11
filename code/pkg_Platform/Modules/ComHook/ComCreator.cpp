#include <UtilFunc/PluginInc.h>
#include "ComCreator.h"

const PROC CComCreator::c_oldfunc = (PROC)CoCreateInstance;

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
        hr = ((FUNC_CREATE)c_oldfunc)(rclsid, pUnkOuter, context, riid, ppv);
    }

    return hr;
}

HRESULT CComCreator::CreateInstance(
        REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv)
{
    LPOLESTR clsid = NULL;
	VERIFY(SUCCEEDED(StringFromCLSID(rclsid, &clsid)));

    HMODULE hmod = FindModule(clsid);
    HRESULT hr = hmod ? E_FAIL : REGDB_E_CLASSNOTREG;

    CoTaskMemFree(clsid);

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

HMODULE CComCreator::FindModule(const std::wstring& clsid)
{
    return NULL;
}
