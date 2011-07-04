// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// v1: 2011.2.7, ooyg: Add Ix_AppWorkPath.
// v2: 2011.2.8, ooyg: Add Ix_PluginDelayLoad.
// v3: 2011.7.4, ooyg: Add GetLocalAppDataPath using SHGetKnownFolderPath.

#include <UtilFunc/PluginInc.h>
#include "Cx_PluginLoader.h"
#include <UtilFunc/RelToAbs.h>
#include <Log/DebugR.cpp>
#include <Portability/portimpl.h>
#include <Module/Cx_Object.h>

class Cx_PluginLoaderOut : public Cx_Object<Cx_PluginLoader>
{
public:
    Cx_PluginLoaderOut() : m_hModule(NULL)
    {
    }

    HMODULE         m_hModule;
    std::wstring    m_path;

    int CreateObject(const X3CLSID& clsid, X3IID iid, Ix_Object** ppv, HMODULE fromdll)
    {
        if (x3::CLSID_AppWorkPath == clsid
            || x3::CLSID_PluginDelayLoad == clsid)
        {
            return QueryInterface(iid, ppv, fromdll) ? 0 : 1;
        }
        return Cx_PluginLoader::CreateObject(clsid, iid, ppv, fromdll);
    }

private:
    Cx_PluginLoaderOut(const Cx_PluginLoaderOut&);
    void operator=(const Cx_PluginLoaderOut&);

    std::wstring GetWorkPath()
    {
        if (m_path.empty())
        {
            m_path = GetLocalAppDataPath(L"x3c");
        }
        return m_path;
    }

    void SetWorkPath(const std::wstring& path)
    {
        m_path = path;
        x3::EnsurePathHasSlash(m_path);
    }

    std::wstring GetLocalAppDataPath(const wchar_t* company)
    {
        wchar_t path[MAX_PATH] = { 0 };

        if (GetLocalAppDataPath_(path))
        {
            wchar_t appname[MAX_PATH];
            GetModuleFileNameW(GetMainModuleHandle(), appname, MAX_PATH);

            if (company)
                PathAppendW(path, company);
            PathAppendW(path, PathFindFileNameW(appname));
            PathRenameExtensionW(path, L"");
            PathAddBackslashW(path);
        }
        else
        {
            GetModuleFileNameW(GetMainModuleHandle(), path, MAX_PATH);
            PathRemoveFileSpecW(path);
            PathAddBackslashW(path);
        }

        return path;
    }

    bool GetLocalAppDataPath_(wchar_t* path);
};

static Cx_PluginLoaderOut s_loader;

OUTAPI Ix_ObjectFactory* x3GetRegisterBank()
{
    return &s_loader;
}

Ix_ObjectFactory* x3GetObjectFactory()
{
    return &s_loader;
}

OUTAPI HMODULE x3GetMainModuleHandle()
{
    return s_loader.GetMainModuleHandle();
}

HMODULE x3GetModuleHandle()
{
    return s_loader.m_hModule;
}

int x3CreateObject(const X3CLSID& clsid, X3IID iid, Ix_Object** ppv)
{
    return s_loader.CreateObject(clsid, iid, ppv, x3GetModuleHandle());
}

#if defined(_USRDLL) && defined(APIENTRY)
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

bool Cx_PluginLoaderOut::GetLocalAppDataPath_(wchar_t* path)
{
    bool ret = false;
#ifdef WINOLEAPI_
    const GUID uuidLocalAppData = {0xF1B32785,0x6FBA,0x4FCF,{0x9D,0x55,
        0x7B,0x8E,0x7F,0x15,0x70,0x91}};

    typedef HRESULT (STDAPICALLTYPE *PFNGET)(REFGUID, DWORD, HANDLE, PWSTR*);
    HMODULE hdll = LoadLibraryW(L"SHELL32.DLL");

    if (hdll != NULL)
    {
        PWSTR shpath = NULL;
        PFNGET pfn = (PFNGET)GetProcAddress(hdll, "SHGetKnownFolderPath");

        if (pfn != NULL)
        {
            pfn(uuidLocalAppData, 0, NULL, &shpath);
        }
        if (shpath != NULL)
        {
            wcscpy_s(path, MAX_PATH, shpath);
            ret = (*path != 0);
            CoTaskMemFree(shpath);
        }
        FreeLibrary(hdll);
    }
#endif
    return ret;
}
