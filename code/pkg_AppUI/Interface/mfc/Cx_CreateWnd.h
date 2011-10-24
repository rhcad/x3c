/*! \file Cx_CreateWnd.h
 *  \brief Define template class (Cx_CreateWnd) to implement Ix_CreateWnd.
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.10.11
 */
#ifndef X3_VIEW_CREATEWND_MFCIMPL_H_
#define X3_VIEW_CREATEWND_MFCIMPL_H_

#ifdef _MSC_VER
#pragma warning(disable:4097)   // typedef-name used as synonym
#endif

#include "Ix_CreateWnd.h"
#include <XComPtr.h>
#include <afxpriv.h>

//! The macro to register window class in XBEGIN_DEFINE_MODULE() group.
/*!
    \ingroup _GROUP_APPUI_
    \param clsid window class unique id.
    \param cls window class deriving from CWnd or other window class.
    \see Cx_CreateWnd, XDEFINE_CLASSMAP_ENTRY
*/
#if defined(XDEFINE_CLASSMAP_ENTRY) && !defined(XDEFINE_CLASSMAP_ENTRY_Wnd)
#define XDEFINE_CLASSMAP_ENTRY_Wnd(clsid, cls) \
    X3CLASSENTRY(1, "Cx_Object<Cx_CreateWnd<" #cls ">>", clsid,    \
        reinterpret_cast<PFNXObjectCreator>(&Cx_Object<Cx_CreateWnd<cls> >::CreateObject),  \
        reinterpret_cast<PFNXGetObjectCount>(&Cx_Object<Cx_CreateWnd<cls> >::GetObjectCount),   \
        reinterpret_cast<PFNXRefCountByOthers>(&Cx_Object<Cx_CreateWnd<cls> >::GetRefCountByOthers)),
#endif

#ifdef __AFXWIN_H__
class Ix_CreateWndMfc : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_CreateWndMfc)
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, void* pHandlerInfo) = 0;
};
#endif

//! Template class to implement Ix_CreateWnd.
/*! BASEWND is a window class which need to implement the following functions:
    \code
    BOOL CreateWnd(CWnd* pParentWnd, UINT id);
    void Refresh();
    \endcode
    \ingroup _GROUP_APPUI_
    \see XDEFINE_CLASSMAP_ENTRY_Wnd
*/
template <class BASEWND>
class Cx_CreateWnd : public Ix_CreateWnd
#ifdef __AFXWIN_H__
    , public Ix_CreateWndMfc
#endif
{
    X3BEGIN_CLASS_DECLARE(Cx_CreateWnd)
        X3DEFINE_INTERFACE_ENTRY(Ix_CreateWnd)
    X3END_CLASS_DECLARE()
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

    // BASEWND class must has function: BOOL CreateWnd(CWnd* pParentWnd, UINT id)
    virtual bool CreateWnd(HWND hwndParent, int id)
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
        return m_pWnd && m_pWnd->CreateWnd(CWnd::FromHandle(hwndParent), id);
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

    virtual bool OnCommand(int id, bool test = false)
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
#ifdef __AFXWIN_H__
        AFX_CMDHANDLERINFO info = { NULL };
        return !!m_pWnd->OnCmdMsg(id, CN_COMMAND, NULL, test ? &info: NULL);
#else
        return false;
#endif
    }

    virtual bool OnUpdateUI(int id, bool& enabled, bool& checked, std::wstring& text)
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
#ifdef __AFXWIN_H__
        class CTempCmdUI : public CCmdUI
        {
        public:
            CTempCmdUI(bool& enabled, bool& checked, std::wstring& text)
                : m_enabled(enabled), m_checked(checked), m_text(text)
            {
            }

            virtual void Enable(BOOL on) { m_enabled = !!on; }
            virtual void SetCheck(int checked) { m_checked = (1 == checked); }
            virtual void SetRadio(BOOL on) { on; }
            virtual void SetText(LPCTSTR text) { m_text = text ? text : L""; }

            bool& m_enabled;
            bool& m_checked;
            std::wstring& m_text;
        };

        CTempCmdUI cmdui(enabled, checked, text);
        return !!m_pWnd->OnCmdMsg(id, CN_UPDATE_COMMAND_UI, &cmdui, NULL);
#else
        return false;
#endif
    }

#ifdef __AFXWIN_H__
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, void* pHandlerInfo)
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
        return m_pWnd->OnCmdMsg(nID, nCode, pExtra, 
            static_cast<AFX_CMDHANDLERINFO*>(pHandlerInfo));
    }
#endif

    // BASEWND class may has function: void Refresh()
    virtual void Refresh()
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
#if defined(_MSC_VER) && _MSC_VER > 1300
        __if_exists(BASEWND::Refresh)
#endif
        {
            m_pWnd->Refresh();
        }
    }

protected:
    BASEWND*    m_pWnd;
};

#ifdef __AFXWIN_H__
static inline BOOL DoCmdMsgHelper(Ix_CreateWnd* pWnd, UINT nID, int nCode, 
                                  void* pExtra, void* pHandlerInfo)
{
    Cx_Interface<Ix_CreateWndMfc> pIFMfc(pWnd);
    if (pIFMfc)
    {
        return pIFMfc->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
    }

    if (CN_UPDATE_COMMAND_UI == nCode)
    {
        CCmdUI *pUI = static_cast<CCmdUI*>(pExtra);
        bool enabled = true;
        bool checked = false;
        std::wstring text(L"@#@$");

        bool ret = pWnd->OnUpdateUI(nID, enabled, checked, text);

        if (ret)
        {
            pUI->Enable(ret && enabled);
            pUI->SetCheck(checked ? 1 : 0);
            if (text != L"@#@$")
                pUI->SetText(text.c_str());
        }
    }

    if (CN_COMMAND == nCode)
    {
        return pWnd->OnCommand(nID, pHandlerInfo != NULL);
    }

    return FALSE;
}
#endif

#endif // X3_VIEW_CREATEWND_MFCIMPL_H_
