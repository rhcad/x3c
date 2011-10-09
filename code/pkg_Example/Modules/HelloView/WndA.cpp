#include <UtilFunc/PluginInc.h>
#include <HelloViewRes.h>
#include "WndA.h"

CWndA::CWndA() : m_point(0, 0), m_selfmove(false)
{
}

CWndA::~CWndA()
{
}

BEGIN_MESSAGE_MAP(CWndA, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_DEMO_INVIEW, OnDemoInView)
END_MESSAGE_MAP()

BOOL CWndA::CreateWnd(CWnd* pParentWnd, UINT nID)
{
    return Create(NULL, L"WndA", WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 0, 0), pParentWnd, nID, NULL);
}

void CWndA::Refresh()
{
    AfxMessageBox(L"CWndA::Refresh()");
}

BOOL CWndA::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CWndA::OnPaint()
{
	CPaintDC dc(this);
    CString str;
    CRect rect;

    GetClientRect(&rect);
    str.Format(L"(%ld, %ld) %s", 
        m_point.x, m_point.y, 
        m_selfmove ? L" me" : L"from other view");
    dc.DrawText(str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void CWndA::OnMouseMove(UINT nFlags, CPoint point)
{
    MoveObserver::Data(point.x, point.y, this).Notify();

	CWnd::OnMouseMove(nFlags, point);
}

void CWndA::OnDemoInView()
{
    AfxMessageBox(L"CWndA::OnDemoInView()");
}

void CWndA::OnMove(long x, long y, MoveObserver* sender)
{
    m_selfmove = (sender == this);
    m_point = CPoint(x, y);

    Invalidate();
}
