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
    return E_FAIL;
}
