// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*! \file Ix_CreateWnd.h
 *  \brief Define window creator interface: Ix_CreateWnd
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_VIEW_ICREATEWND_H_
#define X3_VIEW_ICREATEWND_H_

//! Window creator interface
/*! Use Cx_CreateWnd<YourWndClass> to implement this interface.
    Parent window class need not to known child window class and implement detail.
    \interface Ix_CreateWnd
    \ingroup _GROUP_APPUI_
    \see Cx_CreateWnd
*/
interface Ix_CreateWnd
{
    //! Return window handle.
    virtual HWND GetWindow() const = 0;
    
    //! Create window with a specified control id (eg: AFX_IDW_PANE_FIRST).
    virtual bool CreateWnd(HWND hwndParent, UINT nID) = 0;

    //! Destroy window and object.
    virtual void DestroyWnd() = 0;
    
    //! Dispatch OnCmdMsg notify. See CCmdTarget::OnCmdMsg() in MSDN.
    virtual BOOL DoCmdMsg(UINT nID, int nCode, void* pExtra, void* pInfo) = 0;

    //! Refresh display.
    virtual void Refresh() = 0;
};

#endif // X3_VIEW_ICREATEWND_H_
