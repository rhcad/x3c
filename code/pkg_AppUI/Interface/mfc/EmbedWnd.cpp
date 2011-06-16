/*! \file EmbedWnd.cpp
 *  \brief Implement the proxy window class of CEmbedWnd.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.5.26
 */
#include <UtilFunc/PluginInc.h>
#include "EmbedWnd.h"
#include <UtilFunc/LockCount.h>
#include <afxpriv.h>

static UINT	s_nViewRefreshID = 0;

IMPLEMENT_DYNCREATE(CEmbedWnd, CWnd)

BEGIN_MESSAGE_MAP(CEmbedWnd, CWnd)
	//{{AFX_MSG_MAP(CEmbedWnd)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CEmbedWnd::CEmbedWnd(const X3CLSID& clsidWnd)
	: m_clsid(clsidWnd), m_menuIndex(-1), m_locker(0)
{
}

CEmbedWnd::~CEmbedWnd()
{
}

void CEmbedWnd::SetViewRefreshID(UINT nID)
{
	s_nViewRefreshID = nID;
}

void CEmbedWnd::SetContextMenu(int menuIndex)
{
	m_menuIndex = menuIndex;
}

HWND CEmbedWnd::GetChildWnd() const
{
	return InterfaceSafeCallIf(m_pIFWnd, GetWindow(), NULL);
}

Cx_Ptr CEmbedWnd::GetWndObj() const
{
	return Cx_Ptr(m_pIFWnd);
}

CString CEmbedWnd::GetCaption() const
{
	return m_caption;
}

void CEmbedWnd::SetCaption(LPCTSTR text)
{
	m_caption = text;
}

X3CLSID CEmbedWnd::GetClsid() const
{
	return m_clsid;
}

BOOL CEmbedWnd::DestroyWindow()
{
	InterfaceSafeCall(m_pIFWnd, DestroyWnd());
	return CWnd::DestroyWindow();
}

BOOL CEmbedWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

bool CEmbedWnd::Create(CWnd* pParentWnd, UINT nID, DWORD dwStyle, DWORD dwExStyle)
{
	return !!CWnd::CreateEx(dwExStyle, NULL,
		m_caption.IsEmpty() ? _T("EmbedWnd") : m_caption,
		dwStyle, CRect(0, 0, 0, 0), pParentWnd, nID);
}

bool CEmbedWnd::CreateSubWnd(const X3CLSID& clsidWnd)
{
	ASSERT(m_pIFWnd.IsNull() && GetSafeHwnd());

	m_clsid = clsidWnd;
	if (clsidWnd.valid() && m_pIFWnd.Create(clsidWnd))
	{
		if (m_pIFWnd->CreateWnd(GetSafeHwnd(), AFX_IDW_PANE_FIRST))
		{
			// for embed dialog
			if (::GetDlgCtrlID(m_pIFWnd->GetWindow()) != AFX_IDW_PANE_FIRST)
			{
				ModifyStyleEx(WS_EX_STATICEDGE | WS_EX_CLIENTEDGE, 0);
			}

			return true;
		}
	}

	return false;
}

void CEmbedWnd::OnPaint()
{
	CPaintDC dc(this);

	if (GetChildWnd() == NULL)
	{
		CRect rect;
		GetClientRect(&rect);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 0, 0));

		if (!m_caption.IsEmpty())
		{
			dc.DrawText(m_caption, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else
		{
			::DrawTextA(dc.GetSafeHdc(),
				m_clsid.valid() ? m_clsid.str() : "?",
				-1, &rect,
                DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

void CEmbedWnd::Refresh()
{
	InterfaceSafeCall(m_pIFWnd, Refresh());
}

BOOL CEmbedWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	CLockCount locker (&m_locker);
	if (m_locker > 1)
    {
        return FALSE;
    }

 	if (m_pIFWnd && ::IsWindowVisible(m_pIFWnd->GetWindow()))
 	{
 		if (m_pIFWnd->DoCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		{
			return TRUE;
		}

		if (nID == s_nViewRefreshID && CN_COMMAND == nCode)
		{
			if (NULL == pHandlerInfo)
			{
				m_pIFWnd->Refresh();
			}

			return TRUE;
		}
 	}

	return CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CEmbedWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	if (m_pIFWnd)
	{
		::SetFocus(m_pIFWnd->GetWindow());
	}
}

void CEmbedWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (m_pIFWnd && cx > 0 && cy > 0)
	{
		::MoveWindow(m_pIFWnd->GetWindow(), 0, 0, cx, cy, TRUE);
	}
}

BOOL CEmbedWnd::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	AFX_NOTIFY notify;
	notify.pResult = pResult;
	notify.pNMHDR = (NMHDR*)lParam;

	int nCode = MAKELONG(notify.pNMHDR->code, WM_REFLECT_BASE+WM_NOTIFY);

	if (m_pIFWnd && m_pIFWnd->DoCmdMsg(0, nCode, &notify, NULL))
    {
        return TRUE;
    }

	return CWnd::OnNotify(wParam, lParam, pResult);
}

BOOL CEmbedWnd::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if (message == WM_CONTEXTMENU && m_menuIndex >= 0)
	{
        if (TrackPopupMenu(m_menuIndex, CPoint(lParam)))
		{
			return TRUE;
		}
	}

	return CWnd::OnWndMsg(message, wParam, lParam, pResult);
}
