/*! \file FrameApp.h
 *  \brief Define the base MFC application class: CFrameApp
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.10.27
 */
#ifndef X3_UI_FRAME_APP_H_
#define X3_UI_FRAME_APP_H_

class CPluginManager;

//! The base MFC application class.
/*! This class will create the main frame window.
    \ingroup _GROUP_APPUI_
*/
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
    //! Return a unique string to indicate the application can be ran only one instance.
    virtual LPCWSTR GetSingletonAppUID() { return L""; }
    
    //! Return the config file name for creating the main window.
    virtual LPCWSTR GetFactoryFile() { return L"config/uifactory.xml"; }
    
    //! Load plugins in 'plugins' folder.
    virtual BOOL LoadPlugins();
    
    //! Check the current application instance can be ran or not.
    virtual BOOL CheckAppInstance();
    
    //! Create and show the main frame window.
    virtual BOOL CreateFrameWnd();

protected:
    DECLARE_MESSAGE_MAP()

protected:
    CPluginManager*     m_loader;       //!< for load extra plugins.
    Cx_Ptr              m_factory;      //!< Ix_FrameWndFactory object.
};

#endif // X3_UI_FRAME_APP_H_
