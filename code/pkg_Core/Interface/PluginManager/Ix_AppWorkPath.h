/*! \file Ix_AppWorkPath.h
 *  \brief Define interface of getting applicaton's writtable path: Ix_AppWorkPath
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_MANAGER_IWORKPATH_H_
#define X3_MANAGER_IWORKPATH_H_

#include "XComPtr.h"

X3CLSID_DEFINE(CLSID_AppWorkPath, "b2615355-772d-4195-94eb-59c31250a537");

/*! \ingroup _GROUP_APPUI_
 *  \interface Ix_AppWorkPath
 *  \brief interface of getting applicaton's writtable path.
 *  \see   x3::CLSID_AppWorkPath, x3::GetAppWorkPath()
 */
class Ix_AppWorkPath : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_AppWorkPath)

    //! Get applicaton's writtable absolute path.
    virtual std::wstring GetWorkPath() = 0;

    //! Set applicaton's writtable absolute path. (call before loading plugins)
    virtual void SetWorkPath(const std::wstring& path) = 0;
};

namespace x3 {

//! Get applicaton's writtable absolute path.
/*!
    \ingroup _GROUP_APPUI_
    \see x3::RelToAbsWithPlugin(), x3::FileNameRelToAbs()
*/
inline std::wstring GetAppWorkPath()
{
    Cx_Interface<Ix_AppWorkPath> pIFPath(x3::CLSID_AppWorkPath);
#ifdef ASSERT
    ASSERT(pIFPath.IsNotNull());
#endif
    return pIFPath->GetWorkPath();
}

} // x3

#endif // X3_MANAGER_IWORKPATH_H_
