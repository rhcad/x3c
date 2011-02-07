/*! \file Ix_AppWorkPath.h
 *  \brief Define interface of getting applicaton's writtable path: Ix_AppWorkPath
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.02.07
 */
#ifndef X3_MANAGER_IWORKPATH_H_
#define X3_MANAGER_IWORKPATH_H_

#include "XComPtr.h"

const XCLSID CLSID_AppWorkPath("b2615355-772d-4195-94eb-59c31250a537");

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_AppWorkPath
 *  \brief interface of getting applicaton's writtable path.
 *  \see   CLSID_AppWorkPath, GetAppWorkPath()
 */
interface Ix_AppWorkPath
{
    //! Get applicaton's writtable absolute path.
    virtual std::wstring GetWorkPath() = 0;

    //! Set applicaton's writtable absolute path. (call before loading plugins)
    virtual void SetWorkPath(const std::wstring& path) = 0;
};

//! Get applicaton's writtable absolute path.
//! \ingroup _GROUP_PLUGIN_CORE_
inline std::wstring GetAppWorkPath()
{
    Cx_Interface<Ix_AppWorkPath> pIFPath(CLSID_AppWorkPath);
#ifdef ASSERT
    ASSERT(pIFPath.IsNotNull());
#endif
    return pIFPath->GetWorkPath();
}

#endif // X3_MANAGER_IWORKPATH_H_
