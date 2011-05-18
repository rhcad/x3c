// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// v1: 2011.2.7, ooyg: Add Ix_AppWorkPath.
// v2: 2011.2.8, ooyg: Add Ix_PluginDelayLoad.

#include "stdafx.h"
#include "Cx_PluginLoader.h"
#include <Ix_AppWorkPath.h>
#include <RelToAbs.h>

#ifndef _MSC_VER
#include "../Portability/portimpl.h"
#endif

class Cx_PluginLoaderOut
    : public Cx_PluginLoader
    , public Ix_Object
    , public Ix_AppWorkPath
{
public:
    Cx_PluginLoaderOut() : m_hModule(NULL)
    {
    }

    HMODULE         m_hModule;
    std::wstring    m_path;

public:
    int CreateObject(const XCLSID& clsid, Ix_Object** ppv, HMODULE fromdll)
    {
        if (CLSID_AppWorkPath == clsid
            || CLSID_PluginDelayLoad == clsid)
        {
            *ppv = this;
            return 0;
        }
        return Cx_PluginLoader::CreateObject(clsid, ppv, fromdll);
    }

private:
    std::wstring GetWorkPath()
    {
        return m_path.empty() ? FileNameRelToAbs(L"", false) : m_path;
    }

    void SetWorkPath(const std::wstring& path)
    {
        m_path = path;
        EnsurePathHasSlash(m_path);
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
    return s_loader.m_hModule;
}

int xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
    return s_loader.CreateObject(clsid, ppv, xGetModuleHandle());
}

#if defined(_USRDLL) && defined(_MSC_VER)
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, void* lpReserved)
{
    lpReserved;
    if (DLL_PROCESS_ATTACH == dwReason)
    {
        s_loader.m_hModule = (HMODULE)hModule;
        DisableThreadLibraryCalls(s_loader.m_hModule);
    }

    return TRUE;
}
#endif // _USRDLL
