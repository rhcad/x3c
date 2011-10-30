// x3c - C++ PluginFramework
#pragma once

#include <FrameApp/Ix_FrameWndFactory.h>

class Cx_ConfigSection;

class Cx_FrameWndFactory : public Ix_FrameWndFactory
{
    X3BEGIN_CLASS_DECLARE(Cx_FrameWndFactory)
        X3DEFINE_INTERFACE_ENTRY(Ix_FrameWndFactory)
    X3END_CLASS_DECLARE()
protected:
    Cx_FrameWndFactory();
    virtual ~Cx_FrameWndFactory();

private:
    virtual bool CheckAppInstance(LPCWSTR appid);
    virtual bool CreateFrameWnd(LPCWSTR factoryFile);
    virtual void OnQuit();
    virtual bool OnIdle(long count);

private:
    void RegisterDocTemplate(bool mdi, const Cx_ConfigSection& node);
    bool ProcessShellCommand();

private:
    std::wstring    m_appid;
};
