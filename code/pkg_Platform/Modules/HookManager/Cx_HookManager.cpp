// x3c - C++ PluginFramework
#include <UtilFunc/PluginInc.h>
#include "Cx_HookManager.h"
#include "../Public/ApiHook.h"
#include <UtilFunc/LoadDllHelper.h>
#include <PluginManager/Ix_PluginLoader2.h>
#include <Module/Ix_Module.h>

Ix_ObjectFactory* x3GetObjectFactory();

Cx_HookManager::Cx_HookManager()
{
}

Cx_HookManager::~Cx_HookManager()
{
    while (!m_new2old.empty())
    {
        KEY k = m_new2old.begin()->first;
        VERIFY(UnhookProc(k.first, k.second));
    }
}

bool Cx_HookManager::HookProc(PROC oldproc, PROC newproc, HMODULE hmod)
{
    ASSERT(oldproc && newproc && oldproc != newproc);

    if (HookModuleFunction(NULL, oldproc, newproc, hmod))
    {
        m_new2old[KEY(newproc, hmod)] = oldproc;
        return true;
    }

    return false;
}

bool Cx_HookManager::UnhookProc(PROC newproc, HMODULE hmod)
{
    std::map<KEY, PROC>::iterator it = m_new2old.find(KEY(newproc, hmod));
    bool ret = false;

    if (it != m_new2old.end())
    {
        ret = HookModuleFunction(NULL, newproc, it->second, hmod);
        m_new2old.erase(it);
    }

    return ret;
}

long Cx_HookManager::HookPlugins(LPCWSTR dllname, LPCSTR func, PROC newproc)
{
    ASSERT(dllname && *dllname && newproc);
    long count = 0;
    LoadDllHelper dll(dllname);
    PROC oldproc = dll.GetFunc(func);

    if (oldproc)
    {
        Cx_Interface<Ix_PluginLoader2> loader(x3GetObjectFactory());
        HMODULE hmod;
        std::wstring file;

        for (int i = 0; loader->GetPluginFileName(i, hmod, file); i++)
        {
            if (HookProc(oldproc, newproc, hmod))
            {
                count++;
            }
        }
        if (HookProc(oldproc, newproc, NULL))
        {
            count++;
        }
    }

    return count;
}

long Cx_HookManager::UnhookPlugins(PROC newproc)
{
    long count = 0;
    Cx_Interface<Ix_PluginLoader2> loader(x3GetObjectFactory());
    HMODULE hmod;
    std::wstring file;

    for (int i = 0; loader->GetPluginFileName(i, hmod, file); i++)
    {
        if (UnhookProc(newproc, hmod))
        {
            count++;
        }
    }
    if (UnhookProc(newproc, NULL))
    {
        count++;
    }

    return count;
}
