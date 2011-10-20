#pragma once

class CChildFrame : public CMDIChildWnd, CXTPOffice2007FrameHook
{
protected:
    CChildFrame();
    DECLARE_DYNCREATE(CChildFrame)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CChildFrame)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CChildFrame();

// Generated message map functions
protected:
    //{{AFX_MSG(CChildFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
