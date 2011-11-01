// x3c - C++ PluginFramework
#include "stdafx.h"
#include "MainFrm.h"
#include <RawCmdMsgObserver.h>
#include <Xml/Ix_StringTable.h>
#include <UtilFunc/LockCount.h>

Cx_ConfigSection    g_factoryRoot;

CMainFrame::CMainFrame() : m_id(0), m_pMainWnd(NULL), m_pCommandBars(NULL)
{
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.lpszClass = m_appid.empty() ? _T("XTPMainFrame") : m_appid.c_str();
    cs.lpszName = m_appid.c_str();
    CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
        CS_DBLCLKS, AfxGetApp()->LoadIcon(m_id));

    return TRUE;
}

BOOL CMainFrame::BeforeLoadFrame(CFrameWnd* pMainWnd)
{
    m_pMainWnd = pMainWnd;
    m_frameNode = g_factoryRoot.GetSection(L"mainframe");
    m_ribbonNode = g_factoryRoot.GetSection(L"ribbon");
    m_appid = g_factoryRoot->GetString(L"appid");
    m_appname = g_factoryRoot->GetString(L"appname");
    m_id = m_frameNode->GetUInt32(L"id");

    return TRUE;
}

BOOL CMainFrame::AfterLoadFrame()
{
    m_frameNode.Release();
    m_ribbonNode.Release();
    g_factoryRoot.Release();
    AfxGetApp()->m_pMainWnd = m_pMainWnd;

    return TRUE;
}

BOOL CMainFrame::InitRibbonBars(CXTPCommandBars* pCommandBars)
{
    m_pCommandBars = pCommandBars;

    m_pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);
    m_pCommandBars->GetCommandBarsOptions()->bToolBarAccelTips = TRUE;
    m_pCommandBars->GetCommandBarsOptions()->bShowKeyboardTips = TRUE;
    m_pCommandBars->GetShortcutManager()->SetAccelerators(m_id);

    if (InitRibbonTheme() &&
        (!LoadRibbonIcons() || !CreateRibbonBar()))
    {
        TRACE0("Failed to create ribbon\n");
        return FALSE;
    }

    if (!CreateStatusBar())
        return FALSE;

    CXTPToolTipContext* pToolTipContext = m_pCommandBars->GetToolTipContext();
    pToolTipContext->SetStyle(xtpToolTipResource);
    pToolTipContext->ShowTitleAndDescription();
    pToolTipContext->SetMargin(CRect(2, 2, 2, 2));
    pToolTipContext->SetMaxTipWidth(180);

    LoadCommandBars();

    return TRUE;
}

void CMainFrame::SetRibbonFont()
{
    CXTPOffice2007Theme* pOfficeTheme = (CXTPOffice2007Theme*)(m_pCommandBars->GetPaintManager());
    std::wstring fontcfg(x3::GetStringValue(L"FrameXtp", L"RibbonFont"));
    CString fontname, sizestr;

    AfxExtractSubString(fontname, fontcfg.c_str(), 0, ',');
    AfxExtractSubString(sizestr, fontcfg.c_str(), 1, ',');
    long fontsize = _wtol(sizestr);

    if (!fontname.IsEmpty() && pOfficeTheme->FontExists(fontname))
    {
        pOfficeTheme->m_strOfficeFont = fontname;
        XTPPaintManager()->m_strOfficeFont = fontname;
    }
    if (fontsize != 0)
    {
        pOfficeTheme->SetFontHeight(fontsize);
    }
    else
    {
        pOfficeTheme->UpdateFonts();
    }

    m_pCommandBars->GetToolTipContext()->SetFont(m_pCommandBars->GetPaintManager()->GetRegularFont());
}

void CMainFrame::LoadCommandBars()
{
    LPCTSTR profileName = _T("CommandBars");
    m_pCommandBars->LoadOptions(profileName);
    m_pCommandBars->LoadBarState(profileName, FALSE);
    m_pCommandBars->GetShortcutManager()->LoadShortcuts(profileName);
}

void CMainFrame::SaveCommandBars()
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

    LPCTSTR profileName = _T("CommandBars");
    m_pCommandBars->SaveOptions(profileName);
    m_pCommandBars->SaveBarState(profileName);
    m_pCommandBars->GetShortcutManager()->SaveShortcuts(profileName);
}

BOOL CMainFrame::InitRibbonTheme()
{
    CXTPOffice2007Theme* pOfficeTheme = (CXTPOffice2007Theme*)(m_pCommandBars->GetPaintManager());

    HMODULE hThemeDll = LoadLibrary(m_frameNode->GetString(L"themeDll").c_str());
    if (hThemeDll != NULL)
    {
        pOfficeTheme->SetImages(XTPResourceImages());
        pOfficeTheme->SetImageHandle(hThemeDll, m_frameNode->GetString(L"themeName").c_str());

        XTPPaintManager()->SetTheme(xtpThemeRibbon);
        m_pCommandBars->SetTheme(xtpThemeRibbon);
    }
    else
    {
        XTPPaintManager()->SetTheme(xtpThemeWhidbey);
        m_pCommandBars->SetTheme(xtpThemeWhidbey);
    }

    SetRibbonFont();

    return hThemeDll != NULL;
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, 
                          AFX_CMDHANDLERINFO* pInfo)
{
    static long s_nLocker = 0;
    CLockCount locker (&s_nLocker);

    if (1 == s_nLocker)
    {
        if (NotifyCmdMsgEvent(nID, nCode, pExtra, pInfo))
            return TRUE;
    }

    return FALSE;
}

BOOL CMainFrame::CreateStatusBar()
{
    static UINT indicators[] =
    {
        ID_SEPARATOR,
        ID_INDICATOR_CAPS,
        ID_INDICATOR_NUM,
        ID_INDICATOR_SCRL,
    };

    VERIFY(m_wndStatusBar.Create(m_pMainWnd)
        && m_wndStatusBar.SetIndicators(indicators, _countof(indicators)));

    m_wndStatusBar.SetCommandBars(m_pCommandBars);
    m_wndStatusBar.SetDrawDisabledText(FALSE);
    m_wndStatusBar.GetStatusBarCtrl().SetMinHeight(22);
    m_wndStatusBar.GetPane(0)->SetMargins(8, 1, 2, 1);

    return TRUE;
}

BOOL CMainFrame::LoadRibbonIcons()
{
    CXTPImageManager* pImageManager = m_pCommandBars->GetImageManager();

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

BOOL CMainFrame::CreateRibbonBar()
{
    CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)m_pCommandBars->Add(
        x3::GetStringValue(L"FrameXtp", L"RibbonTitle").c_str(), 
        xtpBarTop, RUNTIME_CLASS(CXTPRibbonBar));

    if (!pRibbonBar)
        return FALSE;

    pRibbonBar->EnableDocking(0);

    CMenu menu;
    menu.Attach(::GetMenu(m_pMainWnd->GetSafeHwnd()));
    m_pMainWnd->SetMenu(NULL);

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

void CMainFrame::CreateRibbonTabs(CXTPRibbonBar* pRibbonBar)
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

void CMainFrame::CreateRibbonGroup(CXTPRibbonTab* pTab, 
                                   const Cx_ConfigSection& group)
{
    UINT groupID = group->GetUInt32(L"id");
    CXTPRibbonGroup* pGroup = groupID ? pTab->AddGroup(groupID)
        : pTab->AddGroup(GetLocalizationString(group->GetString(L"caption")).c_str());

    if (pTab->GetGroups()->GetCount() > 1)
        pGroup->SetControlsGrouping();

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

CXTPControl* CMainFrame::CreateRibbonButton(CXTPRibbonGroup* pGroup, 
                                            const Cx_ConfigSection& button)
{
    CXTPControl* pControl = NULL;
    const std::wstring type(button->GetString(L"type"));
    UINT id = button->GetUInt32(L"id");

    if (type == L"combo" || type == L"combolist")
        pControl = CreateRibbonComboButton(pGroup, button);
    else if (type == L"popup")
        pControl = CreateRibbonPopupButton(pGroup, button);
    else if (type == L"checkbox")
        pControl = pGroup->Add(xtpControlCheckBox, id);
    else
        pControl = pGroup->Add(xtpControlButton, id);

    pControl->SetBeginGroup(button->GetBool(L"beginGroup", false));

    return pControl;
}

CXTPControl* CMainFrame::CreateRibbonPopupButton(CXTPRibbonGroup* pGroup, 
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

CXTPControl* CMainFrame::CreateRibbonComboButton(CXTPRibbonGroup* pGroup, 
                                                 const Cx_ConfigSection& button)
{
    CXTPControlComboBox* pCombo = new CXTPControlComboBox();

    pGroup->Add(pCombo, button->GetUInt32(L"id"));
    if (button->GetString(L"type") == L"combo")
        pCombo->SetDropDownListStyle();     // has an edit control
    pCombo->SetWidth(button->GetInt32(L"width", 50));

    return pCombo;
}

void CMainFrame::OnUpdateRibbonTab(CCmdUI* pCmdUI)
{
    CXTPRibbonControlTab* pControl = DYNAMIC_DOWNCAST(
        CXTPRibbonControlTab, CXTPControl::FromUI(pCmdUI));
    if (!pControl)
        return;

    //CXTPRibbonTab* pTab = pControl->FindTab(ID_TAB_EDIT);
    //pTab->SetVisible(MDIGetActive() != NULL);
}

void CMainFrame::SetSystemButtonStyle(const CMenu& menu)
{
    CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(
        CXTPRibbonBar, m_pCommandBars->GetMenuBar());
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

void CMainFrame::ShowCustomizeDialog(int nSelectedPage)
{
    CXTPCustomizeSheet cs(m_pCommandBars);
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

void CMainFrame::OnCustomize()
{
    ShowCustomizeDialog(0);
}

void CMainFrame::OnCustomizeQuickAccess()
{
    ShowCustomizeDialog(2);
}

std::wstring CMainFrame::GetLocalizationString(const std::wstring& name) const
{
    std::wstring text(x3::GetStringValue(m_appname.c_str(), name.c_str()));

    if (text.empty())
    {
        size_t pos = name.rfind(L'|');
        text = (pos != name.npos) ? name.substr(pos + 1) : name;
    }

    return text;
}

int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
    return FALSE;
}
