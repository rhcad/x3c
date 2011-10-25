#ifndef X3_UI_FRAME_APP_H_
#define X3_UI_FRAME_APP_H_

class CPluginManager;

class CFrameApp : public CWinApp
{
public:
    CFrameApp();
    virtual ~CFrameApp();

public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual BOOL OnIdle(LONG lCount);
    virtual HINSTANCE LoadAppLangResourceDLL();

protected:
    virtual LPCWSTR GetSingletonAppUID() { return L""; }
    virtual LPCWSTR GetFactoryFile() { return L"config/uifactory.xml"; }
    virtual BOOL LoadPlugins();
    virtual BOOL CheckAppInstance();
    virtual BOOL CreateFrameWnd();
    virtual BOOL ProcessShellCommand();

protected:
    DECLARE_MESSAGE_MAP()

protected:
    CPluginManager*     m_loader;
    Cx_Ptr              m_factory;
};

#endif // X3_UI_FRAME_APP_H_
