/*! \file EmbedWnd.h
 *  \brief Define the proxy window class for Ix_CreateWnd.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.5.26
 */
#ifndef X3_VIEW_MFC_EMBEDWND_H_
#define X3_VIEW_MFC_EMBEDWND_H_

#include "Ix_CreateWnd.h"

//! The proxy window class for Ix_CreateWnd.
/*! This window has a child window which Ix_CreateWnd is implemented.
    Use this to enable child window class to be implemented in
    another module and avoid problem in frame window.
    \ingroup _GROUP_VIEW_
*/
class CEmbedWnd : public CWnd
{
    DECLARE_DYNCREATE(CEmbedWnd)
public:
    CEmbedWnd(const X3CLSID& clsidWnd = X3CLSID());
    virtual ~CEmbedWnd();

// Attributes
public:
    //! Returns the child window's handle.
    HWND GetChildWnd() const;

    //! Returns the child window which Ix_CreateWnd is implemented.
    Cx_Ptr GetWndObj() const;

    //! Returns this window caption.
    CString GetCaption() const;

    //! Set window caption when embed in tab control.
    void SetCaption(LPCTSTR text);

    //! Returns the child window's class id.
    X3CLSID GetClsid() const;

// Operations
public:
    //! Create this embed window before call CreateSubWnd.
    bool Create(CWnd* pParentWnd, 
        UINT nID = AFX_IDW_PANE_FIRST, 
        DWORD dwStyle = WS_CHILD | WS_VISIBLE, 
        DWORD dwExStyle = WS_EX_STATICEDGE);

    //! Create the child window which Ix_CreateWnd is implemented.
    bool CreateSubWnd(const X3CLSID& clsidWnd);

    //! Call Ix_CreateWnd::Refresh.
    void Refresh();

    //! Set sub menu index (see TrackPopupMenu).
    void SetContextMenu(int menuIndex);

    //! Set menu id to refresh (see Ix_CreateWnd::Refresh).
    static void SetViewRefreshID(UINT nID);

// ClassWizard generated virtual function overrides
public:
    //{{AFX_VIRTUAL(CEmbedWnd)
    public:
    virtual BOOL DestroyWindow();
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
    protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    //}}AFX_VIRTUAL

    virtual bool TrackPopupMenu(int menuIndex, const CPoint& point)
    {
        menuIndex; point; return false;
    }

// Generated message map functions
protected:
    //{{AFX_MSG(CEmbedWnd)
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    Cx_Interface<Ix_CreateWnd>  m_pIFWnd;
    CString         m_caption;
    X3CLSID         m_clsid;
    int             m_menuIndex;
    long            m_locker;
};

#endif // X3_VIEW_MFC_EMBEDWND_H_
