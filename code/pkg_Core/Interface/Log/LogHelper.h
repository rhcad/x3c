// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
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

/*! \file LogHelper.h
 *  \brief 定义日志输出的 LOG_WARNING 等宏和 CAutoLogGroup
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_LOGHELPER_H_
#define X3_LOG_LOGHELPER_H_

#include "XComPtr.h"
#include "Ix_LogManager.h"

#pragma warning (push, 1)
#include <sstream>		// std::wostringstream
#pragma warning (pop)

// LOG_DEBUG(msg)
// LOG_DEBUG2(name, extra)
// LOG_INFO(msg)
// LOG_INFO2(name, extra)
// LOG_WARNING(msg)
// LOG_WARNING2(name, extra)
// LOG_ERROR(msg)
// LOG_ERROR2(name, extra)
// LOG_FATAL(msg)
// LOG_FATAL2(name, extra)
// LOG_EVENT_ANSI(name, extra, type, file, line)
//
// void RegisterLogObserver(ILogObserver* observer)
// void UnRegisterLogObserver(ILogObserver* observer)
// CAutoLogGroup(msg)


//! 输出调试信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param msg 要输出的信息，为任意类型数值或Unicode字符串(不能是ANSI串)，
		如果是以@开头接上“Module:StrID”格式则自动换为本地化文字
*/
#define LOG_DEBUG(msg)	\
	LOG_EVENT_(msg, kLogType_Debug, __FILE__, __LINE__)


//! 输出调试信息和附加信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name Unicode字符串，以@开头接上“Module:StrID”格式
	\param extra 附加的上下文信息，为任意类型数值或Unicode字符串(不能是ANSI串)
*/
#define LOG_DEBUG2(name, extra)		\
	LOG_EVENT_2(name, extra, kLogType_Debug, __FILE__, __LINE__)


//! 输出普通信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param msg 要输出的信息，为任意类型数值或Unicode字符串(不能是ANSI串)，
		如果是以@开头接上“Module:StrID”格式则自动换为本地化文字
*/
#define LOG_INFO(msg)	\
	LOG_EVENT_(msg, kLogType_Info, __FILE__, __LINE__)


//! 输出普通信息和附加信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name Unicode字符串，以@开头接上“Module:StrID”格式
	\param extra 附加的上下文信息，为任意类型数值或Unicode字符串(不能是ANSI串)
*/
#define LOG_INFO2(name, extra)	\
	LOG_EVENT_2(name, extra, kLogType_Info, __FILE__, __LINE__)


//! 输出警告信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param msg 要输出的信息，为任意类型数值或Unicode字符串(不能是ANSI串)，
		如果是以@开头接上“Module:StrID”格式则自动换为本地化文字
*/
#define LOG_WARNING(msg)		\
	LOG_EVENT_(msg, kLogType_Warning, __FILE__, __LINE__)


//! 输出警告信息和附加信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name Unicode字符串，以@开头接上“Module:StrID”格式
	\param extra 附加的上下文信息，为任意类型数值或Unicode字符串(不能是ANSI串)
*/
#define LOG_WARNING2(name, extra)	\
	LOG_EVENT_2(name, extra, kLogType_Warning, __FILE__, __LINE__)


//! 输出错误信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param msg 要输出的信息，为任意类型数值或Unicode字符串(不能是ANSI串)，
		如果是以@开头接上“Module:StrID”格式则自动换为本地化文字
*/
#define LOG_ERROR(msg)	\
	LOG_EVENT_(msg, kLogType_Error, __FILE__, __LINE__)


//! 输出错误信息和附加信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name Unicode字符串，以@开头接上“Module:StrID”格式
	\param extra 附加的上下文信息，为任意类型数值或Unicode字符串(不能是ANSI串)
*/
#define LOG_ERROR2(name, extra)		\
	LOG_EVENT_2(name, extra, kLogType_Error, __FILE__, __LINE__)


//! 输出严重错误信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param msg 要输出的信息，为任意类型数值或Unicode字符串(不能是ANSI串)，
		如果是以@开头接上“Module:StrID”格式则自动换为本地化文字
*/
#define LOG_FATAL(msg)		\
	LOG_EVENT_(msg, kLogType_Fatal, __FILE__, __LINE__)


//! 输出严重错误信息和附加信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name Unicode字符串，以@开头接上“Module:StrID”格式
	\param extra 附加的上下文信息，为任意类型数值或Unicode字符串(不能是ANSI串)
*/
#define LOG_FATAL2(name, extra)		\
	LOG_EVENT_2(name, extra, kLogType_Fatal, __FILE__, __LINE__)

//! 注册日志输出观察者
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param observer 要注册的观察者
	\return 是否注册成功
	\see UnRegisterLogObserver
*/
inline bool RegisterLogObserver(ILogObserver* observer)
{
	Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
	if (pIFManager.IsNotNull())
	{
		return pIFManager->RegisterObserver(observer);
	}
	return false;
}

//! 注销日志输出观察者
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\see RegisterLogObserver
*/
inline void UnRegisterLogObserver(ILogObserver* observer)
{
	Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
	if (pIFManager.IsNotNull())
	{
		pIFManager->UnRegisterObserver(observer);
	}
}

//! 自动开始一组日志的辅助类，用于在函数中定义局部变量
/*!
	\ingroup _GROUP_PLUGIN_LOG_
*/
class CAutoLogGroup
{
public:
	//! 构造函数，自动开始新的一组日志
	/*!
		\param msg 日志组的文字，如果是以@开头接上“Module:StrID”格式则自动换为本地化文字
		\param extra 附加的上下文信息
	*/
	CAutoLogGroup(LPCWSTR msg, LPCWSTR extra = NULL)
	{
		Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
		if (pIFManager.IsNotNull())
		{
			pIFManager->PushGroup(msg, extra);
		}
	}
	//! 析构函数，自动结束一组日志
	~CAutoLogGroup()
	{
		Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
		if (pIFManager.IsNotNull())
		{
			pIFManager->PopGroup();
		}
	}
};

#pragma warning(disable:4127)	// conditional expression is constant

#define LOG_EVENT_(msg, type, file, line)					\
	do {														\
	Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);	\
	if (pIFManager.IsNotNull())									\
	{															\
		std::wostringstream buf;								\
		buf << msg;											\
		pIFManager->WriteLog(type, buf.str().c_str(), L"", file, line);	\
	}} while (0)

#define LOG_EVENT_2(name, extra, type, file, line)	\
	do {														\
	Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);	\
	if (pIFManager.IsNotNull())									\
	{															\
		std::wostringstream buf;								\
		buf << extra;										\
		pIFManager->WriteLog(type, name, buf.str().c_str(), file, line);	\
	}} while (0)

//! 输出ANSI串的日志信息
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name ANSI字符串，以@开头接上“Module:StrID”格式
	\param extra 附加的上下文信息，为任意类型数值或ANSI字符串
	\param type 日志类型，见 kLogType
	\param file 源代码文件名, 一般取为 __FILE__
	\param line 源代码行号, 一般取为 __LINE__
*/
#define LOG_EVENT_ANSI(name, extra, type, file, line)	\
	do {														\
	Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);	\
	if (pIFManager.IsNotNull())									\
	{															\
		std::ostringstream buf;								\
		buf << extra;										\
		pIFManager->WriteLog(type, name, buf.str().c_str(), file, line);	\
	}} while (0)

#endif // X3_LOG_LOGHELPER_H_
