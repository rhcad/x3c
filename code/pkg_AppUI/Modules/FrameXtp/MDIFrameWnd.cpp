// x3c - C++ PluginFramework
#include "stdafx.h"
#include "MDIFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainMDIFrame, CXTPMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainMDIFrame, CXTPMDIFrameWnd)
    //{{AFX_MSG_MAP(CMainMDIFrame)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
    ON_XTP_CREATECONTROL()
    ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
    ON_UPDATE_COMMAND_UI(XTP_ID_RIBBONCONTROLTAB, OnUpdateRibbonTab)
    ON_COMMAND(XTP_ID_RIBBONCUSTOMIZE, OnCustomizeQuickAccess)
END_MESSAGE_MAP()

CMainMDIFrame::CMainMDIFrame()
{
}

CMainMDIFrame::~CMainMDIFrame()
{
}

BOOL CMainMDIFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    return CXTPMDIFrameWnd::PreCreateWindow(cs)
        && CMainFrame::PreCreateWindow(cs);
}

BOOL CMainMDIFrame::LoadFrame(UINT /*nIDResource*/, DWORD dwDefaultStyle,
                              CWnd* pParentWnd, CCreateContext* pContext)
{
    return CMainFrame::BeforeLoadFrame(this)
        && CXTPMDIFrameWnd::LoadFrame(GetFrameID(), dwDefaultStyle, pParentWnd, pContext)
        && CMainFrame::AfterLoadFrame();
}

int CMainMDIFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CXTPMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!InitCommandBars() || !InitRibbonBars(GetCommandBars()))
        return -1;

    m_wndClient.Attach(this, FALSE);
    m_wndClient.GetToolTipContext()->SetStyle((XTPToolTipStyle)(xtpToolTipLuna + 1));

    return 0;
}

void CMainMDIFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
    GetCommandBars()->OnSetPreviewMode(bPreview);
    m_wndClient.ShowWorkspace(!bPreview);

    CXTPMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CMainMDIFrame::OnClose()
{
    CMainFrame::OnClose();
    CXTPMDIFrameWnd::OnClose();
}

BOOL CMainMDIFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, 
                             AFX_CMDHANDLERINFO* pInfo)
{
    return CMainFrame::OnCmdMsg(nID, nCode, pExtra, pInfo)
        || CXTPMDIFrameWnd::OnCmdMsg(nID, nCode, pExtra, pInfo);
}

int CMainMDIFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
    return CMainFrame::OnCreateControl(lpCreateControl);
}

void CMainMDIFrame::OnUpdateRibbonTab(CCmdUI* pCmdUI)
{
    CMainFrame::OnUpdateRibbonTab(pCmdUI);
}

void CMainMDIFrame::OnCustomize()
{
    CMainFrame::OnCustomize();
}

void CMainMDIFrame::OnCustomizeQuickAccess()
{
    CMainFrame::OnCustomizeQuickAccess();
}
