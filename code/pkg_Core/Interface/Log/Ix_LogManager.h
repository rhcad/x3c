/*! \file Ix_LogManager.h
 *  \brief Define interface of logging output observer manager: Ix_LogManager
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_ILOGMANAGER_H_
#define X3_LOG_ILOGMANAGER_H_

#include "Ix_Object.h"

//! Logging type.
enum kLogType
{
    kLogType_Debug,     //!< debug info
    kLogType_Info,      //!< infomation
    kLogType_Warning,   //!< warning info.
    kLogType_Error,     //!< error info.
    kLogType_Fatal      //!< fatal error info.
};

interface ILogObserver;

const XCLSID CLSID_LogManager("bbf48a97-9aef-4368-9dc0-2d2937c326ec");

//! interface of logging output observer manager.
/*! Used by RegisterLogObserver, CAutoLogGroup and LOG_WARNING.
    \interface Ix_LogManager
    \ingroup _GROUP_PLUGIN_LOG_
    \see CLSID_LogManager, Ix_StringTable
    \see RegisterLogObserver, UnRegisterObserver
*/
interface Ix_LogManager
{
    //! Add a logging output observer.
    virtual bool RegisterObserver(ILogObserver* observer) = 0;

    //! Remove a logging output observer.
    virtual void UnRegisterObserver(ILogObserver* observer) = 0;

    //! Beginning a new logging group.
    /*!
        \param msg group message text. 
            if the first char is '@' and leading as 'Module:StrID' format 
            then the manager will translate into localization text using Ix_StringTable.
        \param extra additional context info.
        \return true if successful.
        \see CAutoLogGroup, PopGroup
    */
    virtual bool PushGroup(const wchar_t* msg, const wchar_t* extra) = 0;

    //! Ending a logging group.
    /*!
        \return true if successful.
        \see CAutoLogGroup, PushGroup
    */
    virtual bool PopGroup() = 0;

    //! Output a logging info.(UNICODE string)
    /*!
        \param type logging type.
        \param msg logging text.
            if the first char is '@' and leading as 'Module:StrID' format 
            then the manager will translate into localization text using Ix_StringTable.
        \param extra additional context info.
        \param file source file name, __FILE__
        \param line code line, __LINE__
        \return true if successful.
        \see LOG_WARNING, LOG_WARNING2, LOG_ERROR, LOG_ERROR2
    */
    virtual bool WriteLog(kLogType type, const wchar_t* msg, 
        const wchar_t* extra, LPCSTR file, long line) = 0;

    //! Output a logging info.(ANSI string)
    /*!
        \param type logging type.
        \param msg logging text.
            if the first char is '@' and leading as 'Module:StrID' format 
            then the manager will translate into localization text using Ix_StringTable.
        \param extra additional context info.
        \param file source file name, __FILE__
        \param line code line, __LINE__
        \return true if successful.
        \see LOG_WARNING, LOG_WARNING2, LOG_ERROR, LOG_ERROR2
    */
    virtual bool WriteLog(kLogType type, LPCSTR msg, 
        LPCSTR extra, LPCSTR file, long line) = 0;

    //! Show assert info, used by XCrtDbgReport.
    virtual int CrtDbgReport(LPCSTR msg, LPCSTR file, long line) = 0;
};

#endif // X3_LOG_ILOGMANAGER_H_
