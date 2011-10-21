#include <FrameApp/FrameAppImpl.h>
#include <PluginManager/XComCreator.h>

class CHelloApp : public CFrameApp
{
public:
    CHelloApp()
    {
    }

    virtual LPCWSTR GetSingletonAppUID()
    {
        return L"f5352210-c5d9-4809-af72-e898107d27d8";
    }
};

CHelloApp theApp;
