#include "stdafx.h"
#include "Cx_FrameWndFactory.h"
#include <xml/Ix_ConfigXml.h>
#include <UtilFunc/RelToAbs.h>

#include "DummyDoc.h"
#include "ChildFrm.h"
#include "EmbedView.h"
#include "MDIFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Cx_FrameWndFactory::Cx_FrameWndFactory()
{
}

Cx_FrameWndFactory::~Cx_FrameWndFactory()
{
}

bool Cx_FrameWndFactory::CreateFrameWnd(LPCWSTR factoryFile)
{
    CXTPWinDwmWrapper().SetProcessDPIAware();   // Support high DPI on Vista or above.

    Cx_Interface<Ix_ConfigXml> pIFXml(x3::CLSID_ConfigXmlFile);
    ASSERT(pIFXml.IsNotNull());
    pIFXml->SetFileName(x3::FileNameRelToAbs(factoryFile).c_str());
    Cx_ConfigSection root(pIFXml->GetData()->GetSection(L""));

    RegisterDocTemplate(Cx_ConfigSection(root.GetSection(L"mainframe")));

    CMainMDIFrame* pFrame = new CMainMDIFrame;
    if (!pFrame->LoadFrame(root))
        return false;
    AfxGetApp()->m_pMainWnd = pFrame;

    return true;
}

void Cx_FrameWndFactory::RegisterDocTemplate(const Cx_ConfigSection& node)
{
    CDocTemplate* pDocTemplate;

    pDocTemplate = new CMultiDocTemplate(
        node->GetUInt32(L"id"),
        RUNTIME_CLASS(CDummyDoc),
        RUNTIME_CLASS(CChildFrame),
        RUNTIME_CLASS(CEmbedView));
    AfxGetApp()->AddDocTemplate(pDocTemplate);
}

bool Cx_FrameWndFactory::ProcessShellCommand()
{
    CCommandLineInfo cmdInfo;
    AfxGetApp()->ParseCommandLine(cmdInfo);

    if (!AfxGetApp()->ProcessShellCommand(cmdInfo))
        return false;

    AfxGetMainWnd()->ShowWindow(AfxGetApp()->m_nCmdShow);
    AfxGetMainWnd()->UpdateWindow();

    return true;
}

void Cx_FrameWndFactory::OnQuit()
{
}
