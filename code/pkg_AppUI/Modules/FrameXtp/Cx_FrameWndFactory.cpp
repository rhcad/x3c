// x3c - C++ PluginFramework
#include "stdafx.h"
#include "Cx_FrameWndFactory.h"
#include <xml/Ix_ConfigXml.h>
#include <UtilFunc/RelToAbs.h>
#include <PluginManager/Ix_AppWorkPath.h>

#include "DummyDoc.h"
#include "ChildFrm.h"
#include "EmbedView.h"
#include "SDIFrameWnd.h"
#include "MDIFrameWnd.h"
#include "../Public/sinstance.cpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CInstanceChecker*    s_checker = NULL;
extern Cx_ConfigSection     g_factoryRoot;

Cx_FrameWndFactory::Cx_FrameWndFactory()
{
}

Cx_FrameWndFactory::~Cx_FrameWndFactory()
{
    delete s_checker;
}

bool Cx_FrameWndFactory::CheckAppInstance(LPCWSTR appid)
{
    m_appid = appid;

    ASSERT(NULL == s_checker);
    s_checker = new CInstanceChecker(appid);

    s_checker->ActivateChecker();
    if (s_checker->PreviousInstanceRunning())
    {
        CCommandLineInfo cmdInfo;
        AfxGetApp()->ParseCommandLine(cmdInfo);
        s_checker->ActivatePreviousInstance(cmdInfo.m_strFileName);

        return false;
    }

    return true;
}

bool Cx_FrameWndFactory::CreateFrameWnd(LPCWSTR factoryFile)
{
    CXTPWinDwmWrapper().SetProcessDPIAware();   // Support high DPI on Vista or above.

    std::wstring xtpfile(x3::GetTranslationsPath(L"ToolkitPro.Resource.xml"));
    TRACE1("Load resource file: %s\n", xtpfile);
	XTPResourceManager()->SetResourceFile(xtpfile.c_str());

    Cx_Interface<Ix_ConfigXml> pIFXml(x3::CLSID_ConfigXmlFile);
    ASSERT(pIFXml.IsNotNull());
    pIFXml->SetFileName(x3::FileNameRelToAbs(factoryFile).c_str());

    Cx_ConfigSection root(pIFXml->GetData()->GetSection(L""));
    Cx_ConfigSection mainframe(root.GetSection(L"mainframe"));
    bool mdi = root->GetBool(L"mdi", false);

    g_factoryRoot = root;
    g_factoryRoot->SetString(L"appid", m_appid.c_str());
    RegisterDocTemplate(mdi, mainframe);

    if (mdi)
    {
        CMainMDIFrame* pFrame = new CMainMDIFrame;
        if (!pFrame->LoadFrame(0))
            return FALSE;
    }

    return ProcessShellCommand();
}

void Cx_FrameWndFactory::RegisterDocTemplate(bool mdi, const Cx_ConfigSection& node)
{
    CDocTemplate* pDocTemplate;

    if (mdi)
    {
        pDocTemplate = new CMultiDocTemplate(
            node->GetUInt32(L"id"),
            RUNTIME_CLASS(CDummyDoc),
            RUNTIME_CLASS(CChildFrame),
            RUNTIME_CLASS(CEmbedView));
    }
    else
    {
        pDocTemplate = new CSingleDocTemplate(
            node->GetUInt32(L"id"),
            RUNTIME_CLASS(CDummyDoc),
            RUNTIME_CLASS(CMainSDIFrame),
            RUNTIME_CLASS(CEmbedView));
    }
    AfxGetApp()->AddDocTemplate(pDocTemplate);
}

bool Cx_FrameWndFactory::ProcessShellCommand()
{
    CCommandLineInfo cmdInfo;
    AfxGetApp()->ParseCommandLine(cmdInfo);

    if (!AfxGetApp()->ProcessShellCommand(cmdInfo))
        return false;

    ASSERT(dynamic_cast<CMainFrame*>(AfxGetMainWnd()));
    AfxGetMainWnd()->ShowWindow(AfxGetApp()->m_nCmdShow);
    AfxGetMainWnd()->UpdateWindow();

    // The first instance of our app is running
	SafeCall(s_checker, TrackFirstInstanceRunning());

    return true;
}

void Cx_FrameWndFactory::OnQuit()
{
}

bool Cx_FrameWndFactory::OnIdle(long)
{
    bool more = false;

    return more;
}
