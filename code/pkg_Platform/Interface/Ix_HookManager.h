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

    //! Replace a API function in the import directory of all plugins.
    /*! The functions and module are all in the current process.
        \param dllname Valid name of the module imported by any plugin.
        \param func Function name of the module of 'dllname'.
        \param newproc A function to be used to replace.
        \return how many plugins are replaced.
    */
    virtual long HookPlugins(LPCWSTR dllname, LPCSTR func, PROC newproc) = 0;

    //! Restore a API function in the import directory of all plugins.
    /*!
        \param newproc A function which has been used to replace.
        \return how many plugins are replaced.
    */
    virtual long UnhookPlugins(PROC newproc) = 0;

    //! Replace a API function in the import directory of the specified module.
    /*! The functions and module are all in the current process.
        \param oldproc A function to be replaced.
        \param newproc A function to be used to replace.
        \param hmod The specified module whose import directory will be replaced.
            If hmod is null then use the main application module.
        \return true if replaced successful.
    */
    virtual bool HookProc(PROC oldproc, PROC newproc, HMODULE hmod = NULL) = 0;

    //! Restore a API function in the import directory of the specified module.
    /*!
        \param newproc A function which has been used to replace.
        \param hmod The specified module whose import directory will be replaced.
            If hmod is null then use the main application module.
        \return true if replaced successful.
    */
    virtual bool UnhookProc(PROC newproc, HMODULE hmod = NULL) = 0;
};

#endif // X3_UTIL_IHOOKMANAGER_H_
