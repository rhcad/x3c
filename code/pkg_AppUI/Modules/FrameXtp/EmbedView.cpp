// x3c - C++ PluginFramework
#include "stdafx.h"
#include "EmbedView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CEmbedView, CView)

BEGIN_MESSAGE_MAP(CEmbedView, CView)
    //{{AFX_MSG_MAP(CEmbedView)
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CEmbedView::CEmbedView()
{
}

CEmbedView::~CEmbedView()
{
}

BOOL CEmbedView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CView::PreCreateWindow(cs);
}

void CEmbedView::OnInitialUpdate()
{
    CView::OnInitialUpdate();
}

void CEmbedView::OnDestroy()
{
    CView::OnDestroy();
}
