/*! \file Ix_CreateWnd.h
 *  \brief Define window creator interface: Ix_CreateWnd
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.10.11
 */
#ifndef X3_VIEW_ICREATEWND_H_
#define X3_VIEW_ICREATEWND_H_

#include <Ix_Object.h>

//! Window creator interface
/*! Use Cx_CreateWnd<YourWndClass> to implement this interface.
    Parent window class need not to known child window class or implement detail.
    \interface Ix_CreateWnd
    \ingroup _GROUP_APPUI_
    \see Cx_CreateWnd
*/
class Ix_CreateWnd : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_CreateWnd)

    //! Return the window handle.
    virtual HWND GetWindow() const = 0;

    //! Create window with a specified control id (eg: AFX_IDW_PANE_FIRST).
    virtual bool CreateWnd(HWND hwndParent, int id) = 0;

    //! Destroy window and object.
    virtual void DestroyWnd() = 0;

    //! Dispatch a command message.
    virtual bool OnCommand(int id, bool test = false) = 0;

    //! Dispatch the update notify of a command UI object.
    virtual bool OnUpdateUI(int id, bool& enabled, bool& checked, std::wstring& text) = 0;

    //! Refresh display.
    virtual void Refresh() = 0;
};

#endif // X3_VIEW_ICREATEWND_H_
