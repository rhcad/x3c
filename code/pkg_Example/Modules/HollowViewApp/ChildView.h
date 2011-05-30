#pragma once

#include <mfc/EmbedWnd.h>

class CChildView : public CWnd
{
public:
	CChildView();
    virtual ~CChildView();

public:
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pInfo);
    virtual BOOL DestroyWindow();

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

private:
    CEmbedWnd   m_wndLeft;
    CEmbedWnd   m_wndRight;
    long        m_locker;
};
