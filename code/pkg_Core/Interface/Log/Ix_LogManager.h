/*! \file Ix_LogManager.h
 *  \brief Define interface of logging output observer manager: Ix_LogManager
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_ILOGMANAGER_H_
#define X3_LOG_ILOGMANAGER_H_

#include "Ix_Object.h"

//! Logging type.
enum x3LogType
{
    x3LogType_Debug,     //!< debug info
    x3LogType_Info,      //!< infomation
    x3LogType_Warning,   //!< warning info.
    x3LogType_Error,     //!< error info.
    x3LogType_Fatal      //!< fatal error info.
};

class Ix_LogObserver;

X3CLSID_DEFINE(CLSID_LogManager, "bbf48a97-9aef-4368-9dc0-2d2937c326ec");

//! interface of logging output observer manager.
/*! Used by RegisterLogObserver, X3LogGroup and X3LOG_WARNING.
    \interface Ix_LogManager
    \ingroup _GROUP_PLUGIN_LOG_
    \see x3::CLSID_LogManager, Ix_StringTable
    \see x3::RegisterLogObserver, UnRegisterObserver
*/
class Ix_LogManager
{
public:
    virtual ~Ix_LogManager() {}

    //! Add a logging output observer.
    virtual bool RegisterObserver(Ix_LogObserver* observer) = 0;

    //! Remove a logging output observer.
    virtual void UnRegisterObserver(Ix_LogObserver* observer) = 0;

    //! Beginning a new logging group.
    /*!
        \param msg group message text. 
            if the first char is '@' and leading as 'Module:StrID' format 
            then the manager will translate into localization text using Ix_StringTable.
        \param extra additional context info.
        \return true if successful.
        \see X3LogGroup, PopGroup
    */
    virtual bool PushGroup(const wchar_t* msg, const wchar_t* extra) = 0;

    //! Ending a logging group.
    /*!
        \return true if successful.
        \see X3LogGroup, PushGroup
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
        \see X3LOG_WARNING, X3LOG_WARNING2, X3LOG_ERROR, X3LOG_ERROR2
    */
    virtual bool WriteLog(x3LogType type, const wchar_t* msg, 
        const wchar_t* extra, const char* file, long line) = 0;

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
        \see X3LOG_WARNING, X3LOG_WARNING2, X3LOG_ERROR, X3LOG_ERROR2
    */
    virtual bool WriteLog(x3LogType type, const char* msg, 
        const char* extra, const char* file, long line) = 0;

    //! Show assert info, used by XCrtDbgReport.
    virtual int CrtDbgReport(const char* msg, const char* file, long line) = 0;
};

#endif // X3_LOG_ILOGMANAGER_H_
