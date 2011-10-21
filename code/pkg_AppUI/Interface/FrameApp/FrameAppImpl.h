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
        && CheckAppInstance()
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

BOOL CFrameApp::CheckAppInstance()
{
    if (*GetSingletonAppUID())
    {
        Cx_Interface<Ix_FrameWndFactory> pIFFrameFactory(x3::CLSID_FrameWndFactory);
        ASSERT(pIFFrameFactory.IsNotNull());

        return pIFFrameFactory->CheckAppInstance(GetSingletonAppUID());
    }

    return TRUE;
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

// <exepath>\translations\<exename>Chs.dll
HINSTANCE CFrameApp::LoadAppLangResourceDLL()
{
    HINSTANCE hResDll = NULL;

#if _MSC_VER > 1400     // not VC6
    TCHAR szPath[MAX_PATH], szTitle[60];

    GetModuleFileName(m_hInstance, szPath, MAX_PATH);
    StrCpyN(szTitle, PathFindFileName(szPath), _countof(szTitle));
    PathRemoveExtension(szTitle);
    PathRemoveFileSpec(szPath);
    PathAppendW(szPath, L"translations");
    PathAppendW(szPath, szTitle);

    hResDll = AfxLoadLangResourceDLL(_T("%s%s.dll"), szPath);
    TRACE2("Load resource file: %s (%s)\n", szPath, hResDll ? L"ok" : L"fail");
#endif

    return hResDll;
}


#if _MSC_VER > 1400     // not VC6
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
