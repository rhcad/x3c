// x3c - C++ PluginFramework
#include "stdafx.h"
#include "SDIFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainSDIFrame, CXTPFrameWnd)

BEGIN_MESSAGE_MAP(CMainSDIFrame, CXTPFrameWnd)
    //{{AFX_MSG_MAP(CMainSDIFrame)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
    ON_XTP_CREATECONTROL()
    ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
    ON_UPDATE_COMMAND_UI(XTP_ID_RIBBONCONTROLTAB, OnUpdateRibbonTab)
    ON_COMMAND(XTP_ID_RIBBONCUSTOMIZE, OnCustomizeQuickAccess)
END_MESSAGE_MAP()

CMainSDIFrame::CMainSDIFrame()
{
}

CMainSDIFrame::~CMainSDIFrame()
{
}

BOOL CMainSDIFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    return CXTPFrameWnd::PreCreateWindow(cs)
        && CMainFrame::PreCreateWindow(cs);
}

BOOL CMainSDIFrame::LoadFrame(UINT /*nIDResource*/, DWORD dwDefaultStyle,
                              CWnd* pParentWnd, CCreateContext* pContext)
{
    return CMainFrame::BeforeLoadFrame(this)
        && CXTPFrameWnd::LoadFrame(GetFrameID(), dwDefaultStyle, pParentWnd, pContext)
        && CMainFrame::AfterLoadFrame();
}

int CMainSDIFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CXTPFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!InitCommandBars() || !InitRibbonBars(GetCommandBars()))
        return -1;

    return 0;
}

void CMainSDIFrame::OnClose()
{
    CMainFrame::OnClose();
    CXTPFrameWnd::OnClose();
}

BOOL CMainSDIFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, 
                             AFX_CMDHANDLERINFO* pInfo)
{
    return CMainFrame::OnCmdMsg(nID, nCode, pExtra, pInfo)
        || CXTPFrameWnd::OnCmdMsg(nID, nCode, pExtra, pInfo);
}

int CMainSDIFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
    return CMainFrame::OnCreateControl(lpCreateControl);
}

void CMainSDIFrame::OnUpdateRibbonTab(CCmdUI* pCmdUI)
{
    CMainFrame::OnUpdateRibbonTab(pCmdUI);
}

void CMainSDIFrame::OnCustomize()
{
    CMainFrame::OnCustomize();
}

void CMainSDIFrame::OnCustomizeQuickAccess()
{
    CMainFrame::OnCustomizeQuickAccess();
}
