#pragma once

#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
    virtual ~CMainFrame();

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
    DECLARE_MESSAGE_MAP()

private:
	CStatusBar  m_wndStatusBar;
	CChildView  m_wndView;
    class MyObserver;
    MyObserver*  m_observer;
};
