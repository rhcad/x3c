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
    virtual bool HookProc(PROC oldproc, PROC newproc);
    virtual bool UnhookProc(PROC newproc);
    virtual bool HookProc(LPCWSTR dllname, LPCSTR func, PROC newproc);
    virtual bool UnhookProc(LPCWSTR dllname, LPCSTR funcname);

private:
    std::map<PROC, HMODULE>     m_dlls;
    std::map<PROC, PROC>        m_new2old;
};

#endif // _X3_HOOKMANAGER_IMPL_H
