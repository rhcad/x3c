/*! \file Ix_AppWorkPath.h
 *  \brief Define interface of getting applicaton's writtable path: Ix_AppWorkPath
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.07.04
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
    /*! The default path is same as GetLocalAppDataPath(L"x3c") if SetWorkPath() is not called.
        \see GetLocalAppDataPath, SetWorkPath
    */
    virtual std::wstring GetWorkPath() = 0;

    //! Set applicaton's writtable absolute path. (call before loading plugins)
    /*! \see GetLocalAppDataPath, GetWorkPath
    */
    virtual void SetWorkPath(const std::wstring& path) = 0;

    //! Return path as calling SHGetKnownFolderPath(FOLDERID_LocalAppData, ...)
    /*! The path form is "X:\Users\auser\AppData\Local\company\"
        or the executable file's folder if failed to call SHGetKnownFolderPath().
        \param company append company name to path if not empty.
        \return the absolute path.
    */
    virtual std::wstring GetLocalAppDataPath(const wchar_t* company) = 0;

    //! Return the language translation path of the current user.
    /*! eg: <exepath>\translations\chs\subfolder (not end with slash char).
        \param subfolder sub folder name in the translation path.
        \return the language translation path which not end with slash char.
    */
    virtual std::wstring GetTranslationsPath(const wchar_t* subfolder) = 0;
};

namespace x3 {

//! \copydoc Ix_AppWorkPath::GetWorkPath()
//! \ingroup _GROUP_APPUI_
inline std::wstring GetAppWorkPath()
{
    Cx_Interface<Ix_AppWorkPath> pIFPath(x3::CLSID_AppWorkPath);
#ifdef ASSERT
    ASSERT(pIFPath.IsNotNull());
#endif
    return pIFPath->GetWorkPath();
}

//! Return the language translation path of the current user.
/*! eg: <exepath>\translations\chs\subfolder
    \param subfolder sub folder name in the translation path.
    \return the language translation path which may not end with slash char.
*/
inline std::wstring GetTranslationsPath(const wchar_t* subfolder = L"")
{
    Cx_Interface<Ix_AppWorkPath> pIFPath(x3::CLSID_AppWorkPath);
#ifdef ASSERT
    ASSERT(pIFPath.IsNotNull());
#endif
    return pIFPath->GetTranslationsPath(subfolder);
}

} // x3

#endif // X3_MANAGER_IWORKPATH_H_
