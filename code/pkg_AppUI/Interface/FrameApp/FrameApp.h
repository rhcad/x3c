#ifndef X3_UI_FRAME_APP_H_
#define X3_UI_FRAME_APP_H_

class CPluginManager;

class CFrameApp : public CWinApp
{
public:
    CFrameApp(bool mdi = false);
    virtual ~CFrameApp();

public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual BOOL OnIdle(LONG lCount);
    virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);

    DECLARE_MESSAGE_MAP()

protected:
    virtual BOOL LoadPlugins();
    virtual BOOL CreateFrameWnd();
    virtual BOOL ProcessShellCommand();

protected:
    CPluginManager*     m_loader;

private:
    bool                m_mdi;
};

#endif // X3_UI_FRAME_APP_H_
