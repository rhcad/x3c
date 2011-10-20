#ifndef X3_UI_FRAMEWND_FACTORY_H_
#define X3_UI_FRAMEWND_FACTORY_H_

#include <Ix_Object.h>

X3CLSID_DEFINE(CLSID_FrameWndFactory, "5c784623-69b4-4551-8e80-85d7997e194d");

class Ix_FrameWndFactory : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_FrameWndFactory)

    virtual bool CreateFrameWnd(LPCWSTR factoryFile) = 0;
    virtual bool ProcessShellCommand() = 0;
    virtual void OnQuit() = 0;
};

#endif // X3_UI_FRAMEWND_FACTORY_H_
