#ifndef X3_UI_FRAME_APPIMPL_H_
#define X3_UI_FRAME_APPIMPL_H_

#include <UtilFunc/PluginInc.h>
#include "FrameApp.h"
#include "Ix_FrameWndFactory.h"
#include <PluginManager/PluginManager.h>

BEGIN_MESSAGE_MAP(CFrameApp, CWinApp)
    ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CFrameApp::CFrameApp()
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
    Cx_Interface<Ix_FrameWndFactory> pIFFactory(x3::CLSID_FrameWndFactory);
    SafeCall(pIFFactory, OnQuit());
    pIFFactory.Release();

    m_loader->Unload();

    return CWinApp::ExitInstance();
}

BOOL CFrameApp::CreateFrameWnd()
{
    Cx_Interface<Ix_FrameWndFactory> pIFFrameFactory(x3::CLSID_FrameWndFactory);
    ASSERT(pIFFrameFactory.IsNotNull());

    return pIFFrameFactory->CreateFrameWnd(GetFactoryFile());
}

BOOL CFrameApp::ProcessShellCommand()
{
    Cx_Interface<Ix_FrameWndFactory> pIFFactory(x3::CLSID_FrameWndFactory);
    return pIFFactory->ProcessShellCommand();
}

BOOL CFrameApp::OnIdle(LONG lCount)
{
    return CWinApp::OnIdle(lCount);
}

int CFrameApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
    return CWinApp::DoMessageBox(lpszPrompt, nType, nIDPrompt);
}

HINSTANCE CFrameApp::LoadAppLangResourceDLL()
{
    return NULL;
}

#endif // X3_UI_FRAME_APPIMPL_H_
