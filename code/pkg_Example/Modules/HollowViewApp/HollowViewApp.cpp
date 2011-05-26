#include <PluginInc.h>
#include <PluginManager.h>
#include <XComCreator.h>

#include "Resource.h"
#include "MainFrm.h"

class CHollowApp : public CWinApp
{
public:
    CHollowApp()
    {
    }

protected:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
};

CHollowApp theApp;
CPluginManager s_loader;

BOOL CHollowApp::InitInstance()
{
	INITCOMMONCONTROLSEX initctls;
	initctls.dwSize = sizeof(initctls);
	initctls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&initctls);

    VERIFY(AfxOleInit());
	CWinApp::InitInstance();

    VERIFY(s_loader.LoadPluginManager(L"../Plugins"));
    s_loader.GetPluginLoader()->LoadPluginFiles(L"../Plugins",
        L"HollowView.plugin" PLNEXT);
    s_loader.GetPluginLoader()->InitializePlugins();

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	if (!pFrame || !pFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;
    pFrame->SetIcon(LoadIcon(IDR_MAINFRAME), FALSE);

	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

int CHollowApp::ExitInstance()
{
    s_loader.Unload();

    return CWinApp::ExitInstance();
}


#if defined(_UNICODE) && _MSC_VER >= 1400
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
