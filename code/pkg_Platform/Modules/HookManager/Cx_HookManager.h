// x3c - C++ PluginFramework
#ifndef _X3_HOOKMANAGER_IMPL_H
#define _X3_HOOKMANAGER_IMPL_H

#include <Ix_HookManager.h>

class Cx_HookManager : public Ix_HookManager
{
    X3BEGIN_CLASS_DECLARE(Cx_HookManager)
        X3DEFINE_INTERFACE_ENTRY(Ix_HookManager)
    X3END_CLASS_DECLARE()
protected:
    Cx_HookManager();
    ~Cx_HookManager();

private:
    virtual long HookPlugins(LPCWSTR dllname, LPCSTR func, PROC newproc);
    virtual long UnhookPlugins(PROC newproc);
    virtual bool HookProc(PROC oldproc, PROC newproc, HMODULE hmod = NULL);
    virtual bool UnhookProc(PROC newproc, HMODULE hmod = NULL);

private:
    typedef std::pair<PROC, HMODULE>    KEY;
    std::map<KEY, PROC>        m_new2old;
};

#endif // _X3_HOOKMANAGER_IMPL_H
