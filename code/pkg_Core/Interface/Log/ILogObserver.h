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

/*! \file ILogObserver.h
 *  \brief 定义日志输出观察者的接口 ILogObserver
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_ILOGOBSERVER_H_
#define X3_LOG_ILOGOBSERVER_H_

#include "Ix_Object.h"

//! 日志输出观察者的接口
/*! 使用 RegisterLogObserver(ILogObserver*)注册观察者，
    使用 UnRegisterLogObserver 注销观察者
    \interface ILogObserver
    \ingroup _GROUP_PLUGIN_LOG_
    \see RegisterLogObserver, UnRegisterLogObserver, CLogObserverImpl
*/
interface ILogObserver
{
    //! 开始新的一组日志
    /*!
        \param level 新的一组日志的组号，从1开始
        \param msg 组信息，已本地化
        \param extra 附加的上下文信息
        \param module 模块名
        \param idname 串ID名称
    */
    virtual void OnPushGroup(long level, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname) = 0;

    //! 结束一组日志
    /*!
        \param level 要结束的一组日志的组号，和相应的 OnPushGroup 同值
    */
    virtual void OnPopGroup(long level) = 0;

    //! 响应日志信息的输出通知
    /*!
        \param type 日志类型, kLogType 枚举值
        \param msg 日志内容信息，已本地化
        \param extra 附加的上下文信息
        \param module 模块名
        \param idname 串ID名称
        \param file 源代码文件名
        \param line 源代码行号
    */
    virtual void OnWriteLog(int type, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname, 
        const std::wstring& file, long line) = 0;
};

//! 日志输出观察者的默认实现
/*!
    \ingroup _GROUP_PLUGIN_LOG_
*/
class CLogObserverImpl : public ILogObserver
{
public:
    CLogObserverImpl() {}
    virtual ~CLogObserverImpl() {}

    virtual void OnPushGroup(long level, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname)
    {
        level; msg; extra; module; idname;
    }

    virtual void OnPopGroup(long level)
    {
        level;
    }

    virtual void OnWriteLog(int type, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname, 
        const std::wstring& file, long line)
    {
        type; msg; extra; module; idname; file; line;
    }
};

#endif // X3_LOG_ILOGOBSERVER_H_
