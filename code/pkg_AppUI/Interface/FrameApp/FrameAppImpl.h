#ifndef X3_UI_FRAME_APPIMPL_H_
#define X3_UI_FRAME_APPIMPL_H_

#include "FrameApp.h"
#include "Ix_FrameWndFactory.h"
#include <PluginManager/PluginManager.h>

BEGIN_MESSAGE_MAP(CFrameApp, CWinApp)
END_MESSAGE_MAP()

CFrameApp::CFrameApp(bool mdi)
    : m_mdi(mdi)
{
    m_loader = new CPluginManager;
}

CFrameApp::~CFrameApp()
{
    delete m_loader;
}

BOOL CFrameApp::InitInstance()
{
    // Enable visual styles on Windows XP or later
    INITCOMMONCONTROLSEX initCtrls;
    initCtrls.dwSize = sizeof(initCtrls);
    initCtrls.dwICC = ICC_WIN95_CLASSES | ICC_DATE_CLASSES;
    InitCommonControlsEx(&initCtrls);

    CWinApp::InitInstance();
    VERIFY(AfxOleInit());

    return LoadPlugins()
        && CreateFrameWnd()
        && ProcessShellCommand();
}

BOOL CFrameApp::LoadPlugins()
{
    return m_loader->LoadCorePlugins(L"plugins")
        && m_loader->GetPluginLoader()->LoadPlugins(L"plugins") > 0
        && m_loader->GetPluginLoader()->InitializePlugins() > 0;
}

int CFrameApp::ExitInstance()
{
    m_loader->Unload();

    return CWinApp::ExitInstance();
}

BOOL CFrameApp::CreateFrameWnd()
{
    Cx_Interface<Ix_FrameWndFactory> pIFFactory(x3::CLSID_FrameWndFactory);
    ASSERT(pIFFactory.IsNotNull());

    return m_mdi ? pIFFactory->CreateMDIFrame() : pIFFactory->CreateSDIFrame();
}

BOOL CFrameApp::ProcessShellCommand()
{
    return TRUE;
}

BOOL CFrameApp::OnIdle(LONG lCount)
{
    return CWinApp::OnIdle(lCount);
}

int CFrameApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
    return CWinApp::DoMessageBox(lpszPrompt, nType, nIDPrompt);
}

#endif // X3_UI_FRAME_APPIMPL_H_
