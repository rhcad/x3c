// x3c - C++ PluginFramework
#include "stdafx.h"
#include "MainFrm.h"
#include <RawCmdMsgObserver.h>
#include <Xml/Ix_StringTable.h>
#include <UtilFunc/LockCount.h>

Cx_ConfigSection    g_factoryRoot;

#if _XTPLIB_VERSION_MAJOR <= 13
inline CXTPOffice2007Images* XTPResourceImages() { return XTPOffice2007Images(); }
#endif

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
    m_id = GetNodeID(m_frameNode, L"id");

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
    pToolTipContext->SetStyle((XTPToolTipStyle)(xtpToolTipLuna + 1));
    pToolTipContext->ShowTitleAndDescription();
    pToolTipContext->SetMargin(CRect(2, 2, 2, 2));
    pToolTipContext->SetMaxTipWidth(180);

    LoadCommandBars();

    return TRUE;
}

void CMainFrame::SetRibbonFont()
{
    CXTPOffice2007Theme* pOfficeTheme = (CXTPOffice2007Theme*)(m_pCommandBars->GetPaintManager());
    CString fontname, sizestr;

    std::wstring fontcfg(x3::GetStringValue(m_appname.c_str(), L"RibbonFont"));
    if (fontcfg.empty())
        fontcfg = x3::GetStringValue(L"FrameXtp", L"RibbonFont");

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
#if _XTPLIB_VERSION_MAJOR > 13
        pOfficeTheme->SetFontHeight(fontsize);
#else
        CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(
            CXTPRibbonBar, m_pCommandBars->GetMenuBar());
        pRibbonBar->SetFontHeight(fontsize);
#endif
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
    std::wstring themeName(m_frameNode->GetString(L"themeName"));
    std::wstring themeDll(m_frameNode->GetString(L"themeDll"));

    XTThemeManager()->SetTheme(xtThemeVisualStudio2008);
	XTPPaintManager()->SetTheme(xtpThemeVisualStudio2008);

    BOOL ret = XTPResourceImages()->SetHandle(themeDll.c_str(), themeName.c_str());
    if (ret)
    {
        XTPPaintManager()->SetTheme(xtpThemeRibbon);
        m_pCommandBars->SetTheme(xtpThemeRibbon);
    }

    return ret;
}

void CMainFrame::OnClose()
{
    SaveCommandBars();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, 
                          AFX_CMDHANDLERINFO* pInfo)
{
    static long s_nLocker = 0;
    CLockCount locker (&s_nLocker);

    if (1 == s_nLocker)
    {
        if (CN_COMMAND == nCode && pInfo && FindGalleryItems(nID))
            return TRUE;
        if (NotifyCmdMsgEvent(nID, nCode, pExtra, pInfo))
            return TRUE;
    }

    return FALSE;
}

BOOL CMainFrame::CreateStatusBar()
{
    std::vector<UINT> indicators(1, ID_SEPARATOR);
    Cx_ConfigSection items(m_frameNode.GetSection(L"statusbar/indicators"));

    for (int i = 0; ; i++)
    {
        Cx_ConfigSection item(items.GetSectionByIndex(L"item", i));
        UINT id = GetNodeID(item, L"id");
        if (0 == id)
            break;
        indicators.push_back(id);
        if (ID_SEPARATOR == id && indicators.front() == id)
            indicators.erase(indicators.begin());
    }

    VERIFY(m_wndStatusBar.Create(m_pMainWnd)
        && m_wndStatusBar.SetIndicators(&indicators[0], x3::GetSize(indicators)));

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
        UINT barID = GetNodeID(barNode, L"id");
        if (0 == barID)
            break;

        std::vector<UINT> ids;

        for (int ibtn = 0; ; ibtn++)
        {
            Cx_ConfigSection btnNode(barNode.GetSectionByIndex(L"button", ibtn));
            UINT id = GetNodeID(btnNode, L"id");
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
    SetRibbonFont();

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
        UINT id = GetNodeID(node, L"id");
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
    UINT groupID = GetNodeID(group, L"id");
    CXTPRibbonGroup* pGroup = groupID ? pTab->AddGroup(groupID)
        : pTab->AddGroup(GetLocalizationString(group->GetString(L"caption")).c_str());

    if (pTab->GetGroups()->GetCount() > 1)
        pGroup->SetControlsGrouping();

    UINT optionButtonID = GetNodeID(group, L"optionButtonID");
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
    UINT id = GetNodeID(button, L"id");

    if (type == L"combo" || type == L"combolist")
        pControl = CreateRibbonComboButton(pGroup, id, button);
    else if (type == L"popup")
        pControl = CreateRibbonPopupButton(pGroup, id, button);
    else if (type == L"checkbox")
        pControl = pGroup->Add(xtpControlCheckBox, id);
    else
        pControl = pGroup->Add(xtpControlButton, id);

    pControl->SetBeginGroup(button->GetBool(L"beginGroup", false));

    return pControl;
}

CXTPControl* CMainFrame::CreateRibbonPopupButton(CXTPRibbonGroup* pGroup, 
                                                 UINT buttonID, 
                                                 const Cx_ConfigSection& button)
{
    std::vector<UINT> popupIds;

    for (int iPopup = 0; ; iPopup++)
    {
        Cx_ConfigSection popup(button.GetSectionByIndex(L"popupButtons/button", iPopup));
        UINT id = GetNodeID(popup, L"id");
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
                                                 UINT buttonID, 
                                                 const Cx_ConfigSection& button)
{
    CXTPControlComboBox* pCombo = new CXTPControlComboBox();
    CXTPPopupBar* pPopupBarGallery = CXTPControlComboBoxGalleryPopupBar::CreateComboBoxGalleryPopupBar(m_pCommandBars);
    CXTPControlGallery* pControlGallery = new CXTPControlGallery();

    pGroup->Add(pCombo, buttonID);
    if (button->GetString(L"type") == L"combo")
    {
        pCombo->SetDropDownListStyle();     // has an edit control
    }
    pCombo->SetWidth(button->GetInt32(L"width", 50));

    pCombo->SetCommandBar(pPopupBarGallery);

    Cx_ConfigSection gallery(button.GetSection(L"gallery"));
    UINT galleryID = gallery->GetUInt32(L"id", buttonID);
    int showCount = gallery->GetInt32(L"showCount", 10);
    CXTPControlGalleryItems* pItems = AddGalleryItems(galleryID);

	pControlGallery->SetControlSize(CSize(
        gallery->GetInt32(L"width", pCombo->GetWidth()), 
        16 * min(24, max(2, 1 + showCount))));
	pControlGallery->SetResizable(FALSE, gallery->GetBool(L"resizable", TRUE));
	pControlGallery->SetItems(pItems);
	pPopupBarGallery->GetControls()->Add(pControlGallery, galleryID);

	pPopupBarGallery->InternalRelease();

    return pCombo;
}

CXTPControlGalleryItems* CMainFrame::AddGalleryItems(UINT id)
{
    CXTPControlGalleryItems* pItems = FindGalleryItems(id);

    if (!pItems)
    {
        pItems = CXTPControlGalleryItems::CreateItems(m_pCommandBars, id);
        m_mapGallery[id] = pItems;

        pItems->SetItemSize(CSize(0, 17));
        pItems->AddItem(_T("8"));
        pItems->AddItem(_T("9"));
        pItems->AddItem(_T("10"));
        pItems->AddItem(_T("11"));
        pItems->AddItem(_T("12"));
        pItems->AddItem(_T("14"));
        pItems->AddItem(_T("16"));
        pItems->AddItem(_T("18"));
        pItems->AddItem(_T("20"));
        pItems->AddItem(_T("22"));
        pItems->AddItem(_T("24"));
        pItems->AddItem(_T("26"));
        pItems->AddItem(_T("28"));
        pItems->AddItem(_T("36"));
        pItems->AddItem(_T("48"));
        pItems->AddItem(_T("72"));
    }

    return pItems;
}

CXTPControlGalleryItems* CMainFrame::FindGalleryItems(UINT id) const
{
    std::map<UINT, CXTPControlGalleryItems*>::const_iterator it = m_mapGallery.find(id);
    return it != m_mapGallery.end() ? it->second : NULL;
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

UINT CMainFrame::GetNodeID(const Cx_ConfigSection& node, LPCWSTR name)
{
    UINT id = node->GetUInt32(name);
    std::wstring str(node->GetString(name));
    size_t pos = str.find(L' ');

    if (id != 0 && pos != str.npos)
    {
        str = str.substr(pos + 1);

        TRACE2("ID %d: %s\n", id, str.c_str());
        ASSERT(str.find(L' ') == str.npos && !str.empty());

        std::map<std::wstring, UINT>::iterator it = m_idnames.find(str);
        ASSERT(it == m_idnames.end() || it->second == id);

        m_idnames[str] = id;
    }

    return id;
}

UINT CMainFrame::FindID(const std::wstring& name) const
{
    std::map<std::wstring, UINT>::const_iterator it = m_idnames.find(name);
    return it != m_idnames.end() ? it->second : 0;
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
