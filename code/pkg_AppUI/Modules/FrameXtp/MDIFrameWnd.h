#pragma once

#include <xml/Cx_ConfigSection.h>

class CMainMDIFrame : public CXTPMDIFrameWnd
{
public:
    CMainMDIFrame();
    virtual ~CMainMDIFrame();

// Attributes
public:
    UINT GetFrameID() const;

// Operations
public:
    BOOL LoadFrame(const Cx_ConfigSection& root);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMainMDIFrame)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);
    //}}AFX_VIRTUAL
    
private:
    BOOL InitRibbonTheme();
    BOOL CreateStatusBar();
    BOOL CreateRibbonBar();
    BOOL LoadRibbonIcons();
    void CreateRibbonTabs(CXTPRibbonBar* pRibbonBar);
    void SetSystemButtonStyle(const CMenu& menu);
    void ShowCustomizeDialog(int nSelectedPage);

// Implementation
private:
    CXTPStatusBar       m_wndStatusBar;
    CXTPTabClientWnd    m_wndClient;
    Cx_ConfigSection    m_frameNode;
    Cx_ConfigSection    m_ribbonNode;

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
