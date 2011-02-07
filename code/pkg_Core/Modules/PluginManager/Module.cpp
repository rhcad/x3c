// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// v1: 2011.2.7, ooyg: Add Ix_AppWorkPath.

#include "stdafx.h"
#include "Cx_PluginLoader.h"
#include <Ix_AppWorkPath.h>
#include <RelToAbs.h>

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
    HRESULT CreateObject(const XCLSID& clsid, Ix_Object** ppv, HMODULE fromdll)
    {
        if (CLSID_AppWorkPath == clsid)
        {
            *ppv = this;
            return S_OK;
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

HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
    return s_loader.CreateObject(clsid, ppv, xGetModuleHandle());
}

#ifdef _USRDLL
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
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
