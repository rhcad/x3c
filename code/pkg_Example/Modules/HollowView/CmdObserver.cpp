#include <PluginInc.h>
#include <CmdMsgObserverSimple.h>
#include <HollowViewRes.h>

class CCmdObserver : private CmdMsgObserverSimple
{
public:
    CCmdObserver() {}

private:
    void OnCmdObserver();
    DECLARE_MENU_MSG_MAP()
};

static CCmdObserver*    s_observer = NULL;

OUTAPI bool InitializePlugin()
{
    s_observer = new CCmdObserver;
    return true;
}

OUTAPI void UninitializePlugin()
{
    SafeDelete(s_observer);
}

BEGIN_MENU_MSG_MAP(CCmdObserver)
    ON_MENU_COMMAND(IDM_DEMO_OBSERVER, OnCmdObserver)
END_MENU_MSG_MAP()

void CCmdObserver::OnCmdObserver()
{
    AfxMessageBox(L"CCmdObserver::OnCmdObserver()");
}
