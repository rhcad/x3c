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
    virtual bool ProcessShellCommand();
    virtual void OnQuit();

private:
    void RegisterDocTemplate(const Cx_ConfigSection& node);
};
