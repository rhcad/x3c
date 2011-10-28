#pragma once

#include <xml/Cx_ConfigSection.h>

class CMainMDIFrame : public CXTPMDIFrameWnd
{
public:
    CMainMDIFrame();
    virtual ~CMainMDIFrame();

// Attributes
public:
    UINT GetFrameID() const { return m_id; }

// Operations
public:
    BOOL LoadFrame(const std::wstring& appid, const Cx_ConfigSection& root);
    std::wstring GetLocalizationString(const std::wstring& name) const;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMainMDIFrame)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO*);
    //}}AFX_VIRTUAL
    
private:
    BOOL InitRibbonTheme();
    BOOL CreateStatusBar();
    BOOL CreateRibbonBar();
    BOOL LoadRibbonIcons();
    void CreateRibbonTabs(CXTPRibbonBar* pRibbonBar);
    void CreateRibbonGroup(CXTPRibbonTab* pTab, const Cx_ConfigSection& group);
    CXTPControl* CreateRibbonButton(CXTPRibbonGroup* pGroup, 
        const Cx_ConfigSection& button);
    CXTPControl* CreateRibbonPopupButton(CXTPRibbonGroup* pGroup, 
        const Cx_ConfigSection& button);
    CXTPControl* CreateRibbonComboButton(CXTPRibbonGroup* pGroup, 
        const Cx_ConfigSection& button);

    void SetSystemButtonStyle(const CMenu& menu);
    void ShowCustomizeDialog(int nSelectedPage);

// Implementation
private:
    CXTPStatusBar       m_wndStatusBar;
    CXTPTabClientWnd    m_wndClient;
    Cx_ConfigSection    m_frameNode;
    Cx_ConfigSection    m_ribbonNode;

    UINT                m_id;
    std::wstring        m_appid;
    std::wstring        m_appname;

// Generated message map functions
protected:
    //{{AFX_MSG(CMainMDIFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnClose();
    //}}AFX_MSG
    afx_msg void OnUpdateRibbonTab(CCmdUI* pCmdUI);
    afx_msg void OnCustomize();
    afx_msg void OnCustomizeQuickAccess();
    DECLARE_MESSAGE_MAP()
};
