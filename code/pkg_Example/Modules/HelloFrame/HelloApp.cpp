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

private:
    afx_msg void OnCommands(UINT nID);
    DECLARE_MESSAGE_MAP()
};

CHelloApp theApp;

BEGIN_MESSAGE_MAP(CHelloApp, CFrameApp)
    ON_COMMAND_RANGE(2790, 32770, CHelloApp::OnCommands)
    ON_COMMAND_RANGE(ID_EDIT_CLEAR, ID_EDIT_REDO, CHelloApp::OnCommands)
END_MESSAGE_MAP()

void CHelloApp::OnCommands(UINT nID)
{
    CString str, text;
    str.LoadString(nID);
    text.Format(L"OnCommands: %d\n%s", nID, str);
    AfxMessageBox(text);
}
