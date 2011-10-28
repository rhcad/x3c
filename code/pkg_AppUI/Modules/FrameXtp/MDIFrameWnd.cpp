#include "stdafx.h"
#include "MDIFrameWnd.h"
#include <Xml/Ix_StringTable.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMainMDIFrame, CXTPMDIFrameWnd)
    //{{AFX_MSG_MAP(CMainMDIFrame)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
    ON_UPDATE_COMMAND_UI(XTP_ID_RIBBONCONTROLTAB, OnUpdateRibbonTab)
    ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
    ON_COMMAND(XTP_ID_RIBBONCUSTOMIZE, OnCustomizeQuickAccess)
END_MESSAGE_MAP()

CMainMDIFrame::CMainMDIFrame() : m_id(0)
{
}

CMainMDIFrame::~CMainMDIFrame()
{
}

BOOL CMainMDIFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CXTPMDIFrameWnd::PreCreateWindow(cs))
        return FALSE;

    cs.lpszClass = m_appid.empty() ? _T("XTPMainFrame") : m_appid.c_str();
    cs.lpszName = m_appid.c_str();
    CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
        CS_DBLCLKS, AfxGetApp()->LoadIcon(m_id));

    return TRUE;
}

BOOL CMainMDIFrame::LoadFrame(const std::wstring& appid, const Cx_ConfigSection& root)
{
    m_appid = appid;
    m_frameNode = root.GetSection(L"mainframe");
    m_ribbonNode = root.GetSection(L"ribbon");
    m_id = m_frameNode->GetUInt32(L"id");
    m_appname = root->GetString(L"appname");

    BOOL ret = CXTPMDIFrameWnd::LoadFrame(m_id);

    m_frameNode.Release();
    m_ribbonNode.Release();

    return ret;
}

int CMainMDIFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CXTPMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!InitCommandBars())
        return -1;

    if (!CreateStatusBar())
        return -1;

    CXTPCommandBars* pCommandBars = GetCommandBars();

    CXTPToolTipContext* pToolTipContext = pCommandBars->GetToolTipContext();
    pToolTipContext->SetStyle(xtpToolTipResource);
    pToolTipContext->ShowTitleAndDescription();
    pToolTipContext->SetMargin(CRect(2, 2, 2, 2));
    pToolTipContext->SetMaxTipWidth(180);
    pToolTipContext->SetFont(pCommandBars->GetPaintManager()->GetIconFont());

    pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);
    pCommandBars->GetCommandBarsOptions()->bToolBarAccelTips = TRUE;

    pCommandBars->GetShortcutManager()->SetAccelerators(m_id);

    if (InitRibbonTheme() &&
        (!LoadRibbonIcons() || !CreateRibbonBar()))
    {
        TRACE0("Failed to create ribbon\n");
        return -1;
    }

    XTPPaintManager()->SetFontHeight(-12);  // for win7

    m_wndClient.Attach(this, FALSE);
    m_wndClient.GetToolTipContext()->SetStyle(xtpToolTipResource);

    LoadCommandBars(_T("CommandBars"));

    return 0;
}

BOOL CMainMDIFrame::InitRibbonTheme()
{
    CXTPCommandBars* pCommandBars = GetCommandBars();
    CXTPOffice2007Theme* pOfficeTheme = (CXTPOffice2007Theme*)(pCommandBars->GetPaintManager());

    HMODULE hThemeDll = LoadLibrary(m_frameNode->GetString(L"themeDll").c_str());
    if (hThemeDll != NULL)
    {
        pOfficeTheme->SetImages(XTPResourceImages());
        pOfficeTheme->SetImageHandle(hThemeDll, m_frameNode->GetString(L"themeName").c_str());

        XTPPaintManager()->SetTheme(xtpThemeRibbon);
        pCommandBars->SetTheme(xtpThemeRibbon);
    }
    else
    {
        XTPPaintManager()->SetTheme(xtpThemeWhidbey);
        pCommandBars->SetTheme(xtpThemeWhidbey);
    }

    return hThemeDll != NULL;
}

BOOL CMainMDIFrame::CreateStatusBar()
{
    static UINT indicators[] =
    {
        ID_SEPARATOR,
        ID_INDICATOR_CAPS,
        ID_INDICATOR_NUM,
        ID_INDICATOR_SCRL,
    };

    VERIFY(m_wndStatusBar.Create(this)
        && m_wndStatusBar.SetIndicators(indicators, _countof(indicators)));

    m_wndStatusBar.SetCommandBars(GetCommandBars());
    m_wndStatusBar.SetDrawDisabledText(FALSE);
    m_wndStatusBar.GetStatusBarCtrl().SetMinHeight(22);
    m_wndStatusBar.GetPane(0)->SetMargins(8, 1, 2, 1);

    return TRUE;
}

BOOL CMainMDIFrame::LoadRibbonIcons()
{
    CXTPImageManager* pImageManager = GetCommandBars()->GetImageManager();

    for (int ibar = 0; ; ibar++)
    {
        Cx_ConfigSection barNode(m_frameNode.GetSectionByIndex(L"toolbars/toolbar", ibar));
        UINT barID = barNode->GetUInt32(L"id");
        if (0 == barID)
            break;

        std::vector<UINT> ids;

        for (int ibtn = 0; ; ibtn++)
        {
            Cx_ConfigSection btnNode(barNode.GetSectionByIndex(L"button", ibtn));
            UINT id = btnNode->GetUInt32(L"id");
            if (0 == id)
                break;
            ids.push_back(id);
        }

        if (ids.empty())
        {
            UINT nIDResourceToolBar = barID;
            pImageManager->SetIcons(nIDResourceToolBar);
        }
        else
        {
            UINT nIDResourceBitmap = barID;
            long cy = barNode->GetBool(L"large", false) ? 32 : 16;

            pImageManager->SetIcons(nIDResourceBitmap, 
                &ids.front(), x3::GetSize(ids), CSize(cy, cy));
        }
    }

    return TRUE;
}

BOOL CMainMDIFrame::CreateRibbonBar()
{
    CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->Add(
        x3::GetStringValue(L"FrameXtp", L"RibbonTitle").c_str(), 
        xtpBarTop, RUNTIME_CLASS(CXTPRibbonBar));

    if (!pRibbonBar)
    {
        return FALSE;
    }

    pRibbonBar->EnableDocking(0);

    CMenu menu;
    menu.Attach(::GetMenu(m_hWnd));
    SetMenu(NULL);

    CXTPControlPopup* pControlFile = (CXTPControlPopup*)pRibbonBar->AddSystemButton(0);
    pControlFile->SetCommandBar(menu.GetSubMenu(0));

    SetSystemButtonStyle(menu);
    CreateRibbonTabs(pRibbonBar);

    CXTPControl* pControlAbout = pRibbonBar->GetControls()->Add(xtpControlButton, ID_APP_ABOUT);
    pControlAbout->SetFlags(xtpFlagRightAlign);

    for (int iQuick = 0; ; iQuick++)
    {
        Cx_ConfigSection node(m_ribbonNode.GetSectionByIndex(
            L"originalQuickAccessControls/button", iQuick));
        UINT id = node->GetUInt32(L"id");
        if (0 == id)
            break;
        pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, id);
    }
    pRibbonBar->EnableFrameTheme();

    return TRUE;
}

std::wstring CMainMDIFrame::GetLocalizationString(const std::wstring& name) const
{
    std::wstring text(x3::GetStringValue(m_appname.c_str(), name.c_str()));

    if (text.empty())
    {
        size_t pos = name.rfind(L'|');
        text = (pos != name.npos) ? name.substr(pos + 1) : name;
    }

    return text;
}

void CMainMDIFrame::CreateRibbonTabs(CXTPRibbonBar* pRibbonBar)
{
    for (int iTab = 0; ; iTab++)
    {
        Cx_ConfigSection tabNode(m_ribbonNode.GetSectionByIndex(L"tabs/tab", iTab));
        std::wstring caption(tabNode->GetString(L"caption"));
        if (caption.empty())
            break;

        CXTPRibbonTab* pTab = pRibbonBar->AddTab(GetLocalizationString(caption).c_str());

        for (int iGroup = 0; ; iGroup++)
        {
            Cx_ConfigSection group(tabNode.GetSectionByIndex(L"group", iGroup));
            if (!group->IsValid())
                break;
            CreateRibbonGroup(pTab, group);
        }
    }
}

void CMainMDIFrame::CreateRibbonGroup(CXTPRibbonTab* pTab, 
                                      const Cx_ConfigSection& group)
{
    UINT groupID = group->GetUInt32(L"id");
    CXTPRibbonGroup* pGroup = groupID ? pTab->AddGroup(groupID)
        : pTab->AddGroup(GetLocalizationString(group->GetString(L"caption")).c_str());

    if (pTab->GetGroups()->GetCount() > 1)
    {
        pGroup->SetControlsGrouping();
    }

    UINT optionButtonID = group->GetUInt32(L"optionButtonID");
    if (optionButtonID != 0)
    {
        pGroup->ShowOptionButton();
        pGroup->GetControlGroupOption()->SetID(optionButtonID);
    }

    for (int iButton = 0; ; iButton++)
    {
        Cx_ConfigSection button(group.GetSectionByIndex(L"button", iButton));
        if (!button->IsValid())
            break;

        CreateRibbonButton(pGroup, button);
    }
}

CXTPControl* CMainMDIFrame::CreateRibbonButton(CXTPRibbonGroup* pGroup, 
                                               const Cx_ConfigSection& button)
{
    CXTPControl* pControl = NULL;
    const std::wstring type(button->GetString(L"type"));    

    if (type == L"combo" || type == L"combolist")
    {
        pControl = CreateRibbonComboButton(pGroup, button);
    }
    else if (type == L"popup")
    {
        pControl = CreateRibbonPopupButton(pGroup, button);
    }
    else
    {
        pControl = pGroup->Add(xtpControlButton, button->GetUInt32(L"id"));
    }

    pControl->SetBeginGroup(button->GetBool(L"beginGroup", false));

    return pControl;
}

CXTPControl* CMainMDIFrame::CreateRibbonPopupButton(CXTPRibbonGroup* pGroup, 
                                                    const Cx_ConfigSection& button)
{
    UINT buttonID = button->GetUInt32(L"id");
    std::vector<UINT> popupIds;

    for (int iPopup = 0; ; iPopup++)
    {
        Cx_ConfigSection popup(button.GetSectionByIndex(L"popupButtons/button", iPopup));
        UINT id = popup->GetUInt32(L"id");
        if (0 == id)
            break;
        popupIds.push_back(id);
    }

    CXTPControlPopup* pControl = (CXTPControlPopup*)pGroup->Add(xtpControlSplitButtonPopup, buttonID);
    while (!popupIds.empty())
    {
        pControl->GetCommandBar()->GetControls()->Add(xtpControlButton, popupIds.front());
        popupIds.erase(popupIds.begin());
    }

    const std::wstring style(button->GetString(L"style"));
    if (style == L"icon")
        pControl->SetStyle(xtpButtonIcon);

    return pControl;
}

CXTPControl* CMainMDIFrame::CreateRibbonComboButton(CXTPRibbonGroup* pGroup, 
                                                    const Cx_ConfigSection& button)
{
    CXTPControlComboBox* pCombo = new CXTPControlComboBox();

    pGroup->Add(pCombo, button->GetUInt32(L"id"));
    if (button->GetString(L"type") == L"combolist")
    {
        pCombo->SetDropDownListStyle();
    }
    pCombo->SetWidth(button->GetInt32(L"width", 50));

    return pCombo;
}

void CMainMDIFrame::OnUpdateRibbonTab(CCmdUI* pCmdUI)
{
    CXTPRibbonControlTab* pControl = DYNAMIC_DOWNCAST(
        CXTPRibbonControlTab, CXTPControl::FromUI(pCmdUI));
    if (!pControl)
        return;

    //CXTPRibbonTab* pTab = pControl->FindTab(ID_TAB_EDIT);
    //pTab->SetVisible(MDIGetActive() != NULL);
}

void CMainMDIFrame::SetSystemButtonStyle(const CMenu& menu)
{
    CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(
        CXTPRibbonBar, GetCommandBars()->GetMenuBar());
    std::wstring themeName(m_frameNode->GetString(L"themeName"));

    if (themeName.find(L"WINDOWS7") != std::wstring::npos
        || themeName.find(L"OFFICE2010") != std::wstring::npos)
    {
        CString caption;
        menu.GetMenuString(0, caption, MF_BYPOSITION);
        pRibbonBar->GetSystemButton()->SetCaption(caption);
        pRibbonBar->GetSystemButton()->SetStyle(xtpButtonCaption);
    }
}

void CMainMDIFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
    GetCommandBars()->OnSetPreviewMode(bPreview);
    m_wndClient.ShowWorkspace(!bPreview);

    CXTPMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CMainMDIFrame::OnClose() 
{   
    /*  CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));

    if (px.OnBeforeExchange()) 
    {
    CXTPPropExchangeSection pxCommandBars(px.GetSection(_T("CommandBars")));
    XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; 
    param.bSerializeControls = TRUE; 
    param.bSaveOriginalControls = FALSE;
    param.bSerializeOptions = TRUE;
    GetCommandBars()->DoPropExchange(&pxCommandBars, &param);

    px.SaveToFile(_T("C:\\save.xml"));
    }*/

    SaveCommandBars(_T("CommandBars"));

    CXTPMDIFrameWnd::OnClose();
}

void CMainMDIFrame::ShowCustomizeDialog(int nSelectedPage)
{
    CXTPCustomizeSheet cs(GetCommandBars());
    UINT resid = m_id;

    CXTPRibbonCustomizeQuickAccessPage pageQuickAccess(&cs);
    cs.AddPage(&pageQuickAccess);
    pageQuickAccess.AddCategories(resid);

    CXTPCustomizeKeyboardPage pageKeyboard(&cs);
    cs.AddPage(&pageKeyboard);
    pageKeyboard.AddCategories(resid);

    CXTPCustomizeOptionsPage pageOptions(&cs);
    cs.AddPage(&pageOptions);

    CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
    pCommands->AddCategories(resid);

    cs.SetActivePage(nSelectedPage);

    cs.DoModal();
}

void CMainMDIFrame::OnCustomize()
{
    ShowCustomizeDialog(0);
}

void CMainMDIFrame::OnCustomizeQuickAccess()
{
    ShowCustomizeDialog(2);
}
