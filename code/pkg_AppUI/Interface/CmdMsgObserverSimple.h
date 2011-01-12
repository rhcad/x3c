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

/*! \file CmdMsgObserverSimple.h
 *  \brief 定义命令消息观察者类 RawCmdMsgObserver
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.29
 */
#ifndef X3_OBSERVER_CMDMSG_OBSERVER_SIMPLE_H_
#define X3_OBSERVER_CMDMSG_OBSERVER_SIMPLE_H_

#include <RawCmdMsgObserver.h>

struct MENU_MSG_MAP;

//! 命令消息观察者基类
/*! 在派生类定义中加上 DECLARE_MENU_MSG_MAP() \n
    在实现文件中指定响应函数，说明见 MenuMsgMapFunctions 
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see MenuMsgMapFunctions
*/
class CmdMsgObserverSimple : public RawCmdMsgObserver
{
protected:
    CmdMsgObserverSimple() : m_sender(0)
    {
    }

protected:
    int GetCurrentCommandSender() const;

private:
    bool OnRawCommand(UINT id, int sender);
    bool OnRawUpdateCmdUI(UINT id, bool& enabled, bool& checked, 
        std::wstring& text, int sender);
    virtual const MENU_MSG_MAP* GetMsgMapEntry() const = 0;

private:
    int m_sender;
};

typedef void (CmdMsgObserverSimple::*PFN_MSG)(void);

//! 菜单命令响应函数的类型
/*! 在CmdMsgObserverSimple的派生类定义中加上 DECLARE_MENU_MSG_MAP() \n
    在实现文件中指定响应函数，如下所示：
    \code
    BEGIN_MENU_MSG_MAP(class)
        ON_MENU_COMMAND(id, memberFxn)
        ON_MENU_COMMAND_RANGE(idMin, idMax, memberFxn)
        ON_MENU_UPDATE_CMDUI(id, memberFxn)
        ON_MENU_UPDATE_CMDUI_RANGE(idMin, idMax, memberFxn)
    END_MENU_MSG_MAP()
    \endcode
    \see CmdMsgObserverSimple
*/
union MenuMsgMapFunctions
{
    PFN_MSG pfn;

    //! 普通命令响应函数，对应于 ON_MENU_COMMAND
    void (CmdMsgObserverSimple::*pfn_COMMAND)();

    //! 连续ID范围的命令响应函数，对应于 ON_MENU_COMMAND_RANGE
    void (CmdMsgObserverSimple::*pfn_COMMAND_RANGE)(UINT id);

    //! 普通命令的菜单更新函数，对应于 ON_MENU_UPDATE_CMDUI
    void (CmdMsgObserverSimple::*pfn_UPDATE_CMDUI)(
        bool& enabled, bool& checked, std::wstring& text);

    //! 连续ID范围的菜单更新函数，对应于 ON_MENU_UPDATE_CMDUI_RANGE
    void (CmdMsgObserverSimple::*pfn_UPDATE_CMDUI_RANGE)(
        UINT id, bool& enabled, bool& checked, std::wstring& text);
};

//! 命令响应函数的类型
enum MenuMsgType
{
    kMenuMsgNull,
    kMenuMsgCommand,
    kMenuMsgCommandRange,
    kMenuMsgUpdateUI,
    kMenuMsgUpdateUIRange,
};

//! 命令响应函数入口项
struct MENU_MSG_MAP
{
    UINT        id;
    UINT        lastid;
    MenuMsgType type;
    PFN_MSG     pfn;
};

//! 在H文件中定义命令响应函数入口项的数组
/*!
    \see MenuMsgMapFunctions, BEGIN_MENU_MSG_MAP
*/
#define DECLARE_MENU_MSG_MAP()  \
private:    \
    const MENU_MSG_MAP* GetMsgMapEntry() const; \
    static const MENU_MSG_MAP messageMap[];

//! 在CPP中实现命令响应函数入口项的数组
/*!
    \see MenuMsgMapFunctions, END_MENU_MSG_MAP, DECLARE_MENU_MSG_MAP
*/
#define BEGIN_MENU_MSG_MAP(theClass)    \
    const MENU_MSG_MAP* theClass::GetMsgMapEntry() const    \
        { return messageMap; }  \
    const MENU_MSG_MAP theClass::messageMap[] = {

//! 登记一个单一命令的响应函数
/*!
    \see BEGIN_MENU_MSG_MAP, MenuMsgMapFunctions
*/
#define ON_MENU_COMMAND(id, memberFxn)  \
        { id, id, kMenuMsgCommand, (PFN_MSG)&memberFxn },

//! 登记一个范围命令的响应函数
/*!
    \see BEGIN_MENU_MSG_MAP, MenuMsgMapFunctions
*/
#define ON_MENU_COMMAND_RANGE(idMin, idMax, memberFxn)  \
        { idMin, idMax, kMenuMsgCommandRange, \
        (PFN_MSG)(void (CmdMsgObserverSimple::*)(UINT))&memberFxn },

//! 登记一个单一命令的更新函数
/*!
    \see BEGIN_MENU_MSG_MAP, MenuMsgMapFunctions
*/
#define ON_MENU_UPDATE_CMDUI(id, memberFxn) \
        { id, id, kMenuMsgUpdateUI, \
        (PFN_MSG)(void (CmdMsgObserverSimple::*)(bool&,bool&,std::wstring&))&memberFxn },

//! 登记一个范围命令的更新函数
/*!
    \see BEGIN_MENU_MSG_MAP, MenuMsgMapFunctions
*/
#define ON_MENU_UPDATE_CMDUI_RANGE(idMin, idMax, memberFxn) \
        { idMin, idMax, kMenuMsgUpdateUIRange, \
        (PFN_MSG)(void (CmdMsgObserverSimple::*)(UINT,bool&,bool&,std::wstring&))&memberFxn },

//! BEGIN_MENU_MSG_MAP对应的结束项
/*!
    \see BEGIN_MENU_MSG_MAP, MenuMsgMapFunctions
*/
#define END_MENU_MSG_MAP()  \
        { 0, 0, kMenuMsgNull, (PFN_MSG)0 }  \
    };

inline int CmdMsgObserverSimple::GetCurrentCommandSender() const
{
    return m_sender;
}

inline bool CmdMsgObserverSimple::OnRawCommand(UINT id, int sender)
{
    const MENU_MSG_MAP* pMsgMap = GetMsgMapEntry();

    m_sender = sender;
    for (int i = 0; pMsgMap[i].id != 0; i++)
    {
        union MenuMsgMapFunctions mmf;
        mmf.pfn = pMsgMap[i].pfn;

        if (pMsgMap[i].type == kMenuMsgCommand
            && id == pMsgMap[i].id)
        {
            (this->*mmf.pfn_COMMAND)();
            return true;
        }
        else if (pMsgMap[i].type == kMenuMsgCommandRange
            && id >= pMsgMap[i].id && id <= pMsgMap[i].lastid)
        {
            (this->*mmf.pfn_COMMAND_RANGE)(id);
            return true;
        }
    }

    return false;
}

inline bool CmdMsgObserverSimple::OnRawUpdateCmdUI(
    UINT id, bool& enabled, bool& checked, std::wstring& text, int sender)
{
    int i = 0;
    const MENU_MSG_MAP* pMsgMap = GetMsgMapEntry();

    m_sender = sender;
    for (; pMsgMap[i].id != 0; i++)
    {
        union MenuMsgMapFunctions mmf;
        mmf.pfn = pMsgMap[i].pfn;

        if (pMsgMap[i].type == kMenuMsgUpdateUI
            && id == pMsgMap[i].id)
        {
            (this->*mmf.pfn_UPDATE_CMDUI)(enabled, checked, text);
            break;
        }
        else if (pMsgMap[i].type == kMenuMsgUpdateUIRange
            && id >= pMsgMap[i].id && id <= pMsgMap[i].lastid)
        {
            (this->*mmf.pfn_UPDATE_CMDUI_RANGE)(id, enabled, checked, text);
            break;
        }
    }

    if (pMsgMap[i].id == 0)
    {
        for (i = 0; pMsgMap[i].id != 0; i++)
        {
            if (id >= pMsgMap[i].id && id <= pMsgMap[i].lastid)
                break;
        }
    }

    return pMsgMap[i].id != 0;
}

#endif // X3_OBSERVER_CMDMSG_OBSERVER_SIMPLE_H_
