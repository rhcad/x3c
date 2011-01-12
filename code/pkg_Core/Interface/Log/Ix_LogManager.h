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

/*! \file Ix_LogManager.h
 *  \brief 定义日志管理器的接口 Ix_LogManager
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_ILOGMANAGER_H_
#define X3_LOG_ILOGMANAGER_H_

#include "Ix_Object.h"

//! 日志类型
enum kLogType
{
    kLogType_Debug,     //!< 调试信息
    kLogType_Info,      //!< 普通信息
    kLogType_Warning,   //!< 警告信息
    kLogType_Error,     //!< 错误信息
    kLogType_Fatal      //!< 严重错误
};

interface ILogObserver;

const XCLSID CLSID_LogManager("bbf48a97-9aef-4368-9dc0-2d2937c326ec");

//! 日志管理器接口
/*! 该接口供 RegisterLogObserver, CAutoLogGroup, LOG_WARNING 等使用。
    \interface Ix_LogManager
    \ingroup _GROUP_PLUGIN_LOG_
    \see CLSID_LogManager, Ix_StringTable
*/
interface Ix_LogManager
{
    //! 注册日志输出观察者
    /*!
        \param observer 要注册的观察者
        \return 是否注册成功
        \see RegisterLogObserver, UnRegisterObserver
    */
    virtual bool RegisterObserver(ILogObserver* observer) = 0;

    //! 注销日志输出观察者
    /*!
        \param observer 要注销的观察者
        \see UnRegisterLogObserver, RegisterObserver
    */
    virtual void UnRegisterObserver(ILogObserver* observer) = 0;

    //! 开始新的一组日志
    /*!
        \param msg 日志组的文字，如果是以@开头接上“Module:StrID”格式则自动换为本地化文字
        \param extra 附加的上下文信息
        \return 是否执行成功
        \see CAutoLogGroup, PopGroup
    */
    virtual bool PushGroup(LPCWSTR msg, LPCWSTR extra) = 0;

    //! 结束一组日志
    /*!
        \return 是否执行成功
        \see CAutoLogGroup, PushGroup
    */
    virtual bool PopGroup() = 0;

    //! 输出日志信息
    /*!
        \param type 日志类型
        \param msg 信息文字，如果是以@开头接上“Module:StrID”格式则自动换为本地化文字
        \param extra 附加的可选文字，用于输出附加的上下文信息
        \param file 源代码文件名, __FILE__
        \param line 源代码行号, __LINE__
        \return 是否执行成功
        \see LOG_WARNING, LOG_WARNING2, LOG_ERROR, LOG_ERROR2
    */
    virtual bool WriteLog(kLogType type, LPCWSTR msg, 
        LPCWSTR extra, LPCSTR file, long line) = 0;

    //! 输出日志信息(ANSI串)
    /*!
        \param type 日志类型
        \param msg 信息文字，如果是以@开头接上“Module:StrID”格式则自动换为本地化文字
        \param extra 附加的可选文字，用于输出附加的上下文信息
        \param file 源代码文件名, __FILE__
        \param line 源代码行号, __LINE__
        \return 是否执行成功
        \see LOG_WARNING, LOG_WARNING2, LOG_ERROR, LOG_ERROR2
    */
    virtual bool WriteLog(kLogType type, LPCSTR msg, 
        LPCSTR extra, LPCSTR file, long line) = 0;

    //! 显示断言错误信息，供 XCrtDbgReport() 调用
    virtual int CrtDbgReport(LPCSTR msg, LPCSTR file, long line) = 0;
};

#endif // X3_LOG_ILOGMANAGER_H_
