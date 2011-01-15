// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include "stdafx.h"
#include "Cx_PluginLoader.h"

class Cx_PluginLoaderOut
    : public Cx_PluginLoader
    , public Ix_Object
{
public:
    Cx_PluginLoaderOut()
    {
    }

private:
    void AddRef(HMODULE) {}
    void Release(HMODULE) {}
    const char* GetClassName() const { return "Cx_PluginLoader"; }
};

static Cx_PluginLoaderOut s_loader;

extern "C" __declspec(dllexport) Ix_ObjectFactory* xGetRegisterBank()
{
    return &s_loader;
}

extern "C" __declspec(dllexport) HMODULE xGetMainModuleHandle()
{
    return s_loader.GetMainModuleHandle();
}

HMODULE xGetModuleHandle()
{
    return NULL;
}

HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
    return s_loader.CreateObject(clsid, ppv, xGetModuleHandle());
}

#ifdef _USRDLL
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
    hModule; dwReason; lpReserved;
    return TRUE;
}
#endif // _USRDLL
