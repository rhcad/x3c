#pragma once

class CEmbedView : public CView
{
protected: // create from serialization only
    CEmbedView();
    DECLARE_DYNCREATE(CEmbedView)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CEmbedView)
    public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    protected:
    virtual void OnInitialUpdate(); // called first time after construct
    virtual void OnDraw(CDC*) {};
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CEmbedView();

// Generated message map functions
protected:
    //{{AFX_MSG(CEmbedView)
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
