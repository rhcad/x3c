#pragma once

#include "MoveObserver.h"

class CWndA : public CWnd, private MoveObserver
{
public:
	CWndA();
    virtual ~CWndA();

    BOOL CreateWnd(CWnd* pParentWnd, UINT nID);
    void Refresh();

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDemoInView();
	DECLARE_MESSAGE_MAP()

private:
     virtual void OnMove(long x, long y, MoveObserver* sender);

private:
    CPoint  m_point;
    bool    m_selfmove;
};
