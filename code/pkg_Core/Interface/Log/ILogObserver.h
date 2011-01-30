/*! \file ILogObserver.h
 *  \brief Define logging output observer interface: ILogObserver
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_ILOGOBSERVER_H_
#define X3_LOG_ILOGOBSERVER_H_

#include "Ix_Object.h"

//! logging output observer interface.
/*! Use RegisterLogObserver(ILogObserver*) to register a observer,
    and use UnRegisterLogObserver to unregister.
    \interface ILogObserver
    \ingroup _GROUP_PLUGIN_LOG_
    \see RegisterLogObserver, UnRegisterLogObserver, CLogObserverImpl
*/
interface ILogObserver
{
    //! Notification of beginning a new logging group.
    /*!
        \param level group number of the new group, base 1.
        \param msg group message text, may be localization text.
        \param extra additional context info.
        \param module module name extracting from group message text.
        \param idname string id name extracting from group message text.
    */
    virtual void OnPushGroup(long level, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname) = 0;

    //! Notification of ending a logging group.
    /*!
        \param level group number same as OnPushGroup.
    */
    virtual void OnPopGroup(long level) = 0;

    //! Notification of outputting a logging info.
    /*!
        \param type logging type, see kLogType.
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
        const std::wstring& file, long line) = 0;
};

//! Default implement of logging output observer.
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
