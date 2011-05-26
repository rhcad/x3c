#include <PluginInc.h>
#include "ChildView.h"
#include <ClsID_ViewExample.h>
#include <EmbedWnd.cpp>
#include <LockCount.h>
#include <RawCmdMsgObserver.h>

CChildView::CChildView() : m_locker(0)
{
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

    cs.style &= ~WS_BORDER;
	cs.dwExStyle &= WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_BTNFACE+1), NULL);

	return TRUE;
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    if (!m_wndLeft.Create(this, AFX_IDW_PANE_FIRST)
        || !m_wndRight.Create(this, AFX_IDW_PANE_FIRST + 1))
    {
        return -1;
    }

    m_wndLeft.CreateSubWnd(CLSID_ExampleWndA);
    m_wndRight.CreateSubWnd(CLSID_ExampleWndB);
	
	return 0;
}

BOOL CChildView::DestroyWindow()
{
    m_wndLeft.DestroyWindow();
    m_wndRight.DestroyWindow();

	return CWnd::DestroyWindow();
}

BOOL CChildView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pInfo)
{
    if (m_wndLeft.OnCmdMsg(nID, nCode, pExtra, pInfo)
        || m_wndRight.OnCmdMsg(nID, nCode, pExtra, pInfo))
    {
        return TRUE;
    }

    CLockCount locker (&m_locker);
    if (1 == m_locker)
    {
        if (CN_COMMAND == nCode)
        {
            RawCmdMsgEventData data(nID);
            data.Notify();
            if (data.ret)
            {
                return TRUE;
            }
        }
        else if (CN_UPDATE_COMMAND_UI == nCode)
        {
            bool enabled = true;
            bool checked = false;
            std::wstring text;

            RawCmdMsgEventData data(nID, enabled, checked, text);
            CCmdUI* pCmdUI = (CCmdUI*)pExtra;

            data.Notify();
            if (data.ret)
            {
                pCmdUI->Enable(enabled);
                pCmdUI->SetCheck(checked ? 1 : 0);
                if (!text.empty())
                {
                    pCmdUI->SetText(text.c_str());
                }

                return TRUE;
            }
        }
    }
    
    return CWnd::OnCmdMsg(nID, nCode, pExtra, pInfo);
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

    if (cx > 0 && cy > 0)
	{
        int x = cx / 2;
        m_wndLeft.MoveWindow(0, 0, x - 2, cy);
        m_wndRight.MoveWindow(x, 0, cx - x, cy);
	}
}
