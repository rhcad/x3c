// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*! \file RawCmdMsgObserver.h
 *  \brief 定义命令消息观察者类 RawCmdMsgObserver
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.29
 */
#ifndef X3_OBSERVER_RAWCMDMSGOBSERVER_H_
#define X3_OBSERVER_RAWCMDMSGOBSERVER_H_
#pragma once

#include <ChangeNotifyData.h>

//! 命令消息数据
/*!
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see RawCmdMsgObserver
*/
struct RawCmdMsgEventData : public ChangeNotifyData
{
    //! 广播执行命令消息的构造函数
    /*!
        \param _id 菜单项资源ID
        \param _sender 消息发送者的类型信息，由具体应用决定其含义
    */
    RawCmdMsgEventData(UINT _id, int _sender = 0)
        : ChangeNotifyData("RawCmdMsgEvent")
        , ret(false), id(_id), sender(_sender)
        , enabled(NULL), checked(NULL), text(NULL)
    {
    }

    //! 广播命令更新消息的构造函数
    /*!
        \param[in] _id 菜单项资源ID
        \param[in,out] _enabled 由响应者设置命令是否可用
        \param[in,out] _checked 由响应者设置命令是否打勾
        \param[in,out] _text 由响应者设置命令的显示文本
        \param[in] _sender 消息发送者的类型信息，由具体应用决定其含义
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
    bool*   enabled;
    bool*   checked;
    std::wstring*   text;
};

//! 命令消息观察者基类
/*!
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see RawCmdMsgEventData
*/
class RawCmdMsgObserver : public ChangeObserver
{
protected:
    //! 构造函数
    RawCmdMsgObserver() : ChangeObserver("RawCmdMsgEvent")
    {
    }

protected:
    //! 响应命令执行消息
    /*!
        \param id 菜单项资源ID
        \param sender 消息发送者的类型信息，由具体应用决定其含义
        \return 是否响应了本通知
    */
    virtual bool OnRawCommand(UINT id, int sender)
    {
        id; sender;
        return false;
    }

    //! 响应命令更新消息
    /*!
        \param[in] id 菜单项资源ID
        \param[in,out] enabled 由响应者设置命令是否可用
        \param[in,out] checked 由响应者设置命令是否打勾
        \param[in,out] text 由响应者设置命令的显示文本
        \param[in] sender 消息发送者的类型信息，由具体应用决定其含义
        \return 是否响应了本通知
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
        RawCmdMsgEventData* mydata = dynamic_cast<RawCmdMsgEventData*>(data);
        ASSERT(mydata);

        if (mydata->enabled)
        {
            mydata->ret = mydata->ret || OnRawUpdateCmdUI(mydata->id, 
                *mydata->enabled, *mydata->checked, *mydata->text, mydata->sender);
        }
        else
        {
            mydata->ret = mydata->ret
                || OnRawCommand(mydata->id, mydata->sender);
        }
    }
};

#endif // X3_OBSERVER_RAWCMDMSGOBSERVER_H_
