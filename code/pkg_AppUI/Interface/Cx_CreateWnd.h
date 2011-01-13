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

/*! \file Cx_CreateWnd.h
 *  \brief Define template class (Cx_CreateWnd) to implement Ix_CreateWnd.
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_VIEW_CREATEWND_IMPL_H_
#define X3_VIEW_CREATEWND_IMPL_H_

#pragma warning(disable:4097)   // typedef-name used as synonym

#include "Ix_CreateWnd.h"

//! The macro to register window class in XBEGIN_DEFINE_MODULE() group.
/*!
    \ingroup _GROUP_APPUI_
    \param clsid window class unique id.
    \param cls window class deriving from CWnd or other window class.
    \see Cx_CreateWnd, XDEFINE_CLASSMAP_ENTRY
*/
#if defined(XDEFINE_CLASSMAP_ENTRY) && !defined(XDEFINE_CLASSMAP_ENTRY_Wnd)
#define XDEFINE_CLASSMAP_ENTRY_Wnd(clsid, cls) \
    _XCLASSMETA_ENTRY(1, "Cx_Object<Cx_CreateWnd<" #cls ">>", clsid, "",    \
        reinterpret_cast<PFNXObjectCreator>(&Cx_Object<Cx_CreateWnd<cls> >::CreateObject),  \
        reinterpret_cast<PFNXGetObjectCount>(&Cx_Object<Cx_CreateWnd<cls> >::GetObjectCount),   \
        reinterpret_cast<PFNXRefCountByOthers>(&Cx_Object<Cx_CreateWnd<cls> >::GetRefCountByOthers)), 
#endif

//! Template class to implement Ix_CreateWnd.
/*! BASEWND is a window class which need to implement the following functions: 
    \code
    BOOL CreateWnd(CWnd* pParentWnd, UINT nID);
    void Refresh();
    \endcode
    \ingroup _GROUP_APPUI_
    \see XDEFINE_CLASSMAP_ENTRY_Wnd
*/
template <class BASEWND>
class Cx_CreateWnd : public Ix_CreateWnd
{
public:
    typedef Cx_CreateWnd<BASEWND> Cx_BaseWnd;

    Cx_CreateWnd()
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
        m_pWnd = new BASEWND();
    }

    virtual ~Cx_CreateWnd()
    {
        ASSERT(NULL == m_pWnd);
    }
    
    virtual HWND GetWindow() const
    {
        return m_pWnd->GetSafeHwnd();
    }

    // BASEWND class must has function: BOOL CreateWnd(CWnd* pParentWnd, UINT nID)
    virtual bool CreateWnd(HWND hwndParent, UINT nID)
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
        return !!m_pWnd->CreateWnd(CWnd::FromHandle(hwndParent), nID);
    }
    
    virtual void DestroyWnd()
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
        if (m_pWnd != NULL)
        {
            m_pWnd->DestroyWindow();
            delete m_pWnd;
            m_pWnd = NULL;
        }
    }
    
    virtual BOOL DoCmdMsg(UINT nID, int nCode, void* pExtra, void* pInfo)
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
        AFX_CMDHANDLERINFO* pHandlerInfo = static_cast<AFX_CMDHANDLERINFO*>(pInfo);
        return m_pWnd->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
    }

    // BASEWND class may has function: void Refresh()
    virtual void Refresh()
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
#if _MSC_VER > 1300
        __if_exists(BASEWND::Refresh)
#endif
        {
            m_pWnd->Refresh();
        }
    }

protected:
    BASEWND*    m_pWnd;
};

#endif // X3_VIEW_CREATEWND_IMPL_H_
