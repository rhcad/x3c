/*! \file Ix_HookManager.h
 *  \brief Define Windows API hooking interface: Ix_HookManager
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.11.01
 */
#ifndef X3_UTIL_IHOOKMANAGER_H_
#define X3_UTIL_IHOOKMANAGER_H_

#include <Ix_Object.h>

X3CLSID_DEFINE(CLSID_HookManager, "a62aa05e-4027-4627-9e7c-00ec5963d06f");

//! Windows API hooking interface.
/*!
    \interface Ix_HookManager
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_HookManager
*/
class Ix_HookManager : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_HookManager)

    virtual bool HookProc(PROC oldproc, PROC newproc) = 0;
    virtual bool UnhookProc(PROC newproc) = 0;

    virtual bool HookProc(LPCWSTR dllname, LPCSTR func, PROC newproc) = 0;
    virtual bool UnhookProc(LPCWSTR dllname, LPCSTR funcname) = 0;
};

#endif // X3_UTIL_IHOOKMANAGER_H_
