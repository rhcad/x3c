/*! \file RawCmdMsgObserver.h
 *  \brief Define window's command message observer: RawCmdMsgObserver
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2010.10.29
 */
#ifndef X3_OBSERVER_RAWCMDMSG_OBSERVER_H_
#define X3_OBSERVER_RAWCMDMSG_OBSERVER_H_

#include <ChangeObserver/Cx_ChangeObserver.h>

//! Window's command message observer data.
/*!
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see RawCmdMsgObserver
*/
struct RawCmdMsgEventData : public ChangeNotifyData
{
    //! Constructor for dispatching command execute message.
    /*!
        \param _id resource id of the menu item.
        \param _test only check a handler is exist or not.
        \param _sender additional information interpreted by message sender.
    */
    RawCmdMsgEventData(UINT _id, bool _test = false, int _sender = 0)
        : ChangeNotifyData("RawCmdMsgEvent")
        , ret(false), id(_id), sender(_sender), test(_test)
        , enabled(NULL), checked(NULL), text(NULL)
    {
    }

    //! Constructor for dispatching the update of command UI message.
    /*!
        \param[in] _id resource id of the menu item.
        \param[in,out] _enabled enables or disables.
        \param[in,out] _checked checks or unchecks.
        \param[in,out] _text sets display text.
        \param[in] _sender additional information interpreted by message sender.
    */
    RawCmdMsgEventData(UINT _id, bool& _enabled, bool& _checked,
        std::wstring& _text, int _sender = 0)
        : ChangeNotifyData("RawCmdMsgEvent")
        , ret(false), id(_id), sender(_sender)
        , enabled(&_enabled), checked(&_checked), text(&_text)
    {
    }

    bool    ret;
    UINT    id;
    int     sender;
    bool    test;
    bool*   enabled;
    bool*   checked;
    std::wstring*   text;
};

//! Window's command message observer base class.
/*!
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see RawCmdMsgEventData
*/
class RawCmdMsgObserver : public Cx_ChangeObserver
{
protected:
    //! Constructor
    RawCmdMsgObserver() : Cx_ChangeObserver("RawCmdMsgEvent")
    {
    }

protected:
    //! Handle the command execute message.
    /*!
        \param id resource id of the menu item.
        \param test only check a handler is exist or not.
        \param sender additional information interpreted by message sender.
        \return The message is handled by the derived class or not.
    */
    virtual bool OnRawCommand(UINT id, bool test, int sender)
    {
        id; test; sender;
        return false;
    }

    //! Handle the update of command UI message.
    /*!
        \param[in] id resource id of the menu item.
        \param[in,out] enabled enables or disables.
        \param[in,out] checked checks or unchecks.
        \param[in,out] text sets display text.
        \param[in] sender additional information interpreted by message sender.
        \return The message is handled by the derived class or not.
    */
    virtual bool OnRawUpdateCmdUI(UINT id, bool& enabled, bool& checked,
        std::wstring& text, int sender)
    {
        id; enabled; checked; text; sender;
        return false;
    }

private:
    void DoUpdate(ChangeNotifyData* data)
    {
#ifdef _USRDLL
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
        RawCmdMsgEventData* mydata = static_cast<RawCmdMsgEventData*>(data);
#ifdef ASSERT
        ASSERT(mydata);
#endif

        if (mydata->enabled)
        {
            mydata->ret = mydata->ret || OnRawUpdateCmdUI(mydata->id,
                *mydata->enabled, *mydata->checked, *mydata->text, mydata->sender);
        }
        else
        {
            mydata->ret = mydata->ret
                || OnRawCommand(mydata->id, mydata->test, mydata->sender);
        }
    }
};

#ifdef __AFXWIN_H__
static inline BOOL NotifyCmdMsgEvent(UINT nID, int nCode, void* pExtra, 
                                     void* pHandlerInfo, int sender = 0)
{
    BOOL ret = FALSE;

    if (CN_COMMAND == nCode)
    {
        RawCmdMsgEventData data(nID, pHandlerInfo != NULL, sender);
        data.Notify();
        ret = data.ret;
    }
    else if (CN_UPDATE_COMMAND_UI == nCode)
    {
        bool enabled = true;
        bool checked = false;
        std::wstring text;

        RawCmdMsgEventData data(nID, enabled, checked, text, sender);
        CCmdUI* pCmdUI = (CCmdUI*)pExtra;

        data.Notify();
        if (data.ret)
        {
            pCmdUI->Enable(enabled);
            pCmdUI->SetCheck(checked ? 1 : 0);
            if (!text.empty())
            {
                pCmdUI->SetText(text.c_str());
            }
            ret = TRUE;
        }
    }

    return ret;
}
#endif // __AFXWIN_H__

#endif // X3_OBSERVER_RAWCMDMSG_OBSERVER_H_
