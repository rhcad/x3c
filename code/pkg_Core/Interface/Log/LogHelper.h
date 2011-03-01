/*! \file LogHelper.h
 *  \brief Define logging macros such as LOG_WARNING and CAutoLogGroup.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_LOGHELPER_H_
#define X3_LOG_LOGHELPER_H_

#include "XComPtr.h"
#include "Ix_LogManager.h"

#pragma warning (push, 1)
#include <sstream>      // std::wostringstream
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


//! Output a debug info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param msg logging text, can be UNICODE string or other type number (not ANSI string).
        if the first char is '@' and leading as 'Module:StrID' format, 
        then the manager will translate into localization text.
*/
#define LOG_DEBUG(msg)  \
    LOG_EVENT_(msg, kLogType_Debug, __FILE__, __LINE__)


//! Output a debug info with additional context info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param name UNICODE string, the first char is '@' and leading as 'Module:StrID' format.
    \param extra additional context info, can be UNICODE string or other type number (not ANSI string).
*/
#define LOG_DEBUG2(name, extra)     \
    LOG_EVENT_2(name, extra, kLogType_Debug, __FILE__, __LINE__)


//! Output a normal info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param msg logging text, can be UNICODE string or other type number (not ANSI string).
        if the first char is '@' and leading as 'Module:StrID' format, 
        then the manager will translate into localization text.
*/
#define LOG_INFO(msg)   \
    LOG_EVENT_(msg, kLogType_Info, __FILE__, __LINE__)


//! Output a normal info with additional context info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param name UNICODE string, the first char is '@' and leading as 'Module:StrID' format.
    \param extra additional context info, can be UNICODE string or other type number (not ANSI string).
*/
#define LOG_INFO2(name, extra)  \
    LOG_EVENT_2(name, extra, kLogType_Info, __FILE__, __LINE__)


//! Output a warnning info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param msg logging text, can be UNICODE string or other type number (not ANSI string).
        if the first char is '@' and leading as 'Module:StrID' format, 
        then the manager will translate into localization text.
*/
#define LOG_WARNING(msg)        \
    LOG_EVENT_(msg, kLogType_Warning, __FILE__, __LINE__)


//! Output a warnning info with additional context info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param name UNICODE string, the first char is '@' and leading as 'Module:StrID' format.
    \param extra additional context info, can be UNICODE string or other type number (not ANSI string).
*/
#define LOG_WARNING2(name, extra)   \
    LOG_EVENT_2(name, extra, kLogType_Warning, __FILE__, __LINE__)


//! Output a error info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param msg logging text, can be UNICODE string or other type number (not ANSI string).
        if the first char is '@' and leading as 'Module:StrID' format, 
        then the manager will translate into localization text.
*/
#define LOG_ERROR(msg)  \
    LOG_EVENT_(msg, kLogType_Error, __FILE__, __LINE__)


//! Output a error info with additional context info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param name UNICODE string, the first char is '@' and leading as 'Module:StrID' format.
    \param extra additional context info, can be UNICODE string or other type number (not ANSI string).
*/
#define LOG_ERROR2(name, extra)     \
    LOG_EVENT_2(name, extra, kLogType_Error, __FILE__, __LINE__)


//! Output a fatal error info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param msg logging text, can be UNICODE string or other type number (not ANSI string).
        if the first char is '@' and leading as 'Module:StrID' format, 
        then the manager will translate into localization text.
*/
#define LOG_FATAL(msg)      \
    LOG_EVENT_(msg, kLogType_Fatal, __FILE__, __LINE__)


//! Output a fatal error info with additional context info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param name UNICODE string, the first char is '@' and leading as 'Module:StrID' format.
    \param extra additional context info, can be UNICODE string or other type number (not ANSI string).
*/
#define LOG_FATAL2(name, extra)     \
    LOG_EVENT_2(name, extra, kLogType_Fatal, __FILE__, __LINE__)

//! Register a logging output observer.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
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

//! Unregister a logging output observer.
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

//! Helper class for logging group, auto begin and end group.
/*! Use this class to define variable in local function, eg: 
    \code
    void MyFunc()
    {
        CAutoLogGroup group(L"@MyPlugin:GROUP_MYNAME");
        ...
    }
    \endcode
    \ingroup _GROUP_PLUGIN_LOG_
*/
class CAutoLogGroup
{
public:
    //! Constructor, auto begin a new logging group.
    /*!
        \param msg group message text. 
            if the first char is '@' and leading as 'Module:StrID' format 
            then the manager will translate into localization text using Ix_StringTable.
        \param extra additional context info.
    */
    CAutoLogGroup(const wchar_t* msg, const wchar_t* extra = NULL)
    {
        Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
        if (pIFManager.IsNotNull())
        {
            pIFManager->PushGroup(msg, extra);
        }
    }
    //! Destructor, auto end the logging group.
    ~CAutoLogGroup()
    {
        Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
        if (pIFManager.IsNotNull())
        {
            pIFManager->PopGroup();
        }
    }
};

#pragma warning(disable:4127)   // conditional expression is constant

#define LOG_EVENT_(msg, type, file, line)                   \
    do {                                                        \
    Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);   \
    if (pIFManager.IsNotNull())                                 \
    {                                                           \
        std::wostringstream _buf;                                \
        _buf << msg;                                         \
        pIFManager->WriteLog(type, _buf.str().c_str(), L"", file, line); \
    }} while (0)

#define LOG_EVENT_2(name, extra, type, file, line)  \
    do {                                                        \
    Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);   \
    if (pIFManager.IsNotNull())                                 \
    {                                                           \
        std::wostringstream _buf;                                \
        _buf << extra;                                       \
        pIFManager->WriteLog(type, name, _buf.str().c_str(), file, line);    \
    }} while (0)

//! Output a ANSI string with additional context info.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
    \param name ANSI string, the first char is '@' and leading as 'Module:StrID' format.
    \param extra additional context info, can be ANSI string or other type number.
    \param type logging type, see kLogType.
    \param file source file name, __FILE__
    \param line code line, __LINE__
*/
#define LOG_EVENT_ANSI(name, extra, type, file, line)   \
    do {                                                        \
    Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);   \
    if (pIFManager.IsNotNull())                                 \
    {                                                           \
        std::ostringstream _buf;                             \
        _buf << extra;                                       \
        pIFManager->WriteLog(type, name, _buf.str().c_str(), file, line);    \
    }} while (0)

#endif // X3_LOG_LOGHELPER_H_
