// x3c - C++ PluginFramework
#pragma once

#include <xml/Cx_ConfigSection.h>

class CMainFrame
{
public:
    CMainFrame();
    ~CMainFrame();

public:
    UINT GetFrameID() const { return m_id; }
    std::wstring GetLocalizationString(const std::wstring& name) const;

protected:
    BOOL PreCreateWindow(CREATESTRUCT& cs);
    BOOL BeforeLoadFrame(CFrameWnd* pThis);
    BOOL AfterLoadFrame();
    BOOL InitRibbonBars(CXTPCommandBars* pCommandBars);
    BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO*);
    void LoadCommandBars();
    void SaveCommandBars();

    BOOL InitRibbonTheme();
    BOOL CreateStatusBar();
    BOOL CreateRibbonBar();
    BOOL LoadRibbonIcons();
    void CreateRibbonTabs(CXTPRibbonBar* pRibbonBar);
    void CreateRibbonGroup(CXTPRibbonTab* pTab, const Cx_ConfigSection& group);
    CXTPControl* CreateRibbonButton(CXTPRibbonGroup* pGroup, const Cx_ConfigSection& button);
    CXTPControl* CreateRibbonPopupButton(CXTPRibbonGroup* pGroup, const Cx_ConfigSection& button);
    CXTPControl* CreateRibbonComboButton(CXTPRibbonGroup* pGroup, const Cx_ConfigSection& button);

    afx_msg void OnUpdateRibbonTab(CCmdUI* pCmdUI);
    afx_msg void OnCustomize();
    afx_msg void OnCustomizeQuickAccess();
    int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
    void SetSystemButtonStyle(const CMenu& menu);
    void ShowCustomizeDialog(int nSelectedPage);

protected:
    CXTPStatusBar       m_wndStatusBar;
    Cx_ConfigSection    m_frameNode;
    Cx_ConfigSection    m_ribbonNode;
    UINT                m_id;
    std::wstring        m_appid;
    std::wstring        m_appname;

private:
    CFrameWnd*          m_this;
    CXTPCommandBars*    m_cmdbars;
};
