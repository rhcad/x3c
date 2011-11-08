/*! \file Ix_LogObserver.h
 *  \brief Define logging output observer interface: Ix_LogObserver
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.11.08
 */
#ifndef X3_LOG_ILOGOBSERVER_H_
#define X3_LOG_ILOGOBSERVER_H_

#include <string>

//! logging output observer interface.
/*! Use RegisterLogObserver(Ix_LogObserver*) to register a observer,
    and use UnRegisterLogObserver to unregister.
    \interface Ix_LogObserver
    \ingroup _GROUP_PLUGIN_LOG_
    \see x3::RegisterLogObserver, UnRegisterLogObserver, Cx_LogObserverImpl
*/
class Ix_LogObserver
{
public:
    virtual ~Ix_LogObserver() {}

    //! Notification of beginning a new logging group.
    /*!
        \param level group number of the new group, base 1.
        \param msg group message text, may be localization text.
        \param extra additional context info.
        \param module module name extracting from group message text.
        \param idname string id name extracting from group message text.
        \param file source file name.
        \param line code line in source file.
    */
    virtual void OnPushGroup(long level, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname, 
        const char* file, long line) = 0;

    //! Notification of ending a logging group.
    /*!
        \param level group number same as OnPushGroup.
    */
    virtual void OnPopGroup(long level) = 0;

    //! Notification of outputting a logging info.
    /*!
        \param type logging type, see x3LogType.
        \param msg logging text, may be localization text.
        \param extra additional context info.
        \param module module name extracting from logging text.
        \param idname string id name extracting from logging text.
        \param file source file name.
        \param line code line in source file.
    */
    virtual void OnWriteLog(int type, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname, 
        const char* file, long line) = 0;
};

//! Default implement of logging output observer.
/*!
    \ingroup _GROUP_PLUGIN_LOG_
*/
class Cx_LogObserverImpl : public Ix_LogObserver
{
public:
    Cx_LogObserverImpl() {}
    virtual ~Cx_LogObserverImpl() {}

    virtual void OnPushGroup(long level, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname, 
        const char* file, long line)
    {
        level; msg; extra; module; idname; file; line;
    }

    virtual void OnPopGroup(long level)
    {
        level;
    }

    virtual void OnWriteLog(int type, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname, 
        const char* file, long line)
    {
        type; msg; extra; module; idname; file; line;
    }
};

#endif // X3_LOG_ILOGOBSERVER_H_
