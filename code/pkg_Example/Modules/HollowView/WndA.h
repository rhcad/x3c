#pragma once

class CWndA : public CWnd
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
    CPoint  m_point;
};
