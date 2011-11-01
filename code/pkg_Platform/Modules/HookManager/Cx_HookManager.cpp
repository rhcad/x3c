// x3c - C++ PluginFramework
#include <UtilFunc/PluginInc.h>
#include "Cx_HookManager.h"
#include "../ComHook/ApiHook.cpp"

Cx_HookManager::Cx_HookManager()
{
}

Cx_HookManager::~Cx_HookManager()
{
    while (!m_new2old.empty())
    {
        VERIFY(UnhookProc(m_new2old.begin()->first));
    }
    ASSERT(m_dlls.empty());
}

bool Cx_HookManager::HookProc(PROC oldproc, PROC newproc)
{
    ASSERT(oldproc && newproc && oldproc != newproc);

    if (HookModuleFunction(NULL, oldproc, newproc))
    {
        m_new2old[newproc] = oldproc;
        return true;
    }

    return false;
}

bool Cx_HookManager::UnhookProc(PROC newproc)
{
    std::map<PROC, PROC>::iterator it = m_new2old.find(newproc);

    if (it != m_new2old.end())
    {
        VERIFY(HookModuleFunction(NULL, it->second, newproc));
        m_new2old.erase(it);

        std::map<PROC, HMODULE>::iterator it2 = m_dlls.find(newproc);
        if (it2 != m_dlls.end())
        {
            FreeLibrary(it2->second);
            m_dlls.erase(it2);
        }

        return true;
    }

    return false;
}

bool Cx_HookManager::HookProc(LPCWSTR dllname, LPCSTR func, PROC newproc)
{
    HMODULE hdll = GetModuleHandleW(dllname);
    bool add = false;

    if (NULL == hdll)
    {
        hdll = x3LoadLibrary(dllname);
        add = !!hdll;
    }

    bool ret = HookProc(GetProcAddress(hdll, func), newproc);

    if (add)
    {
        if (ret)
            m_dlls[newproc] = hdll;
        else
            FreeLibrary(hdll);
    }

    return ret;
}

bool Cx_HookManager::UnhookProc(LPCWSTR dllname, LPCSTR funcname)
{
    HMODULE hdll = GetModuleHandleW(dllname);
    return UnhookProc(GetProcAddress(hdll, funcname));
}
