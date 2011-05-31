#include <UtilFunc/PluginInc.h>
#include "Resource.h"
#include "MainFrm.h"
#include "../HollowView/MoveObserver.h"

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_NUM,
	ID_INDICATOR_XY,
};

class CMainFrame::MyObserver : private MoveObserver
{
public:
    MyObserver(CStatusBar* bar) : m_bar(bar) {}

private:
    virtual void OnMove(long x, long y, MoveObserver* sender);

private:
    CStatusBar* m_bar;
};

CMainFrame::CMainFrame()
{
    m_observer = new MyObserver(&m_wndStatusBar);
}

CMainFrame::~CMainFrame()
{
    delete m_observer;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		return -1;
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators, _countof(indicators)))
	{
		return -1;
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	m_wndView.SetFocus();

    CFrameWnd::OnSetFocus(pOldWnd);
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::MyObserver::OnMove(long x, long y, MoveObserver*)
{
    CString str;
    str.Format(L"%ld, %ld", x, y);
    m_bar->SetPaneText(m_bar->CommandToIndex(ID_INDICATOR_XY), str);
}
