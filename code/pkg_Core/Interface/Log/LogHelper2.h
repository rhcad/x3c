/*! \file LogHelper2.h
 *  \brief Define logging macros such as LOG_GROUP2 and LOG_INFO for non-plugin projects.
 *  \note Just need LogWriter.plugin for non-plugin system to use logging function.
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.11.08
 */
#ifndef X3_LOG_LOGHELPER2_H_
#define X3_LOG_LOGHELPER2_H_

// msg: UNICODE string. eg: L"some text".
// extra: additional context info, can be UNICODE string or aother type number (not ANSI string).
//        eg: L"message" << intvalue << L", " << floatnum);
//
// LOG_GROUP0;
// LOG_GROUP1(msg);
// LOG_GROUP2(msg, extra);
// LOG_INFO(msg);
// LOG_INFO2(msg, extra);
// LOG_WARNING(msg);
// LOG_WARNING2(msg, extra);
// LOG_ERROR(msg);
// LOG_ERROR2(msg, extra);
//

#include <sstream>

#define LOG_GROUP1(msg)             \
    CLogGroup log##__LINE__(msg, L"", __FILE__, __LINE__)

#define LOG_GROUP0          LOG_GROUP1(L"")

#define LOG_GROUP2(name, extra)     \
    std::wostringstream _buf;       \
    _buf << extra;                  \
    CLogGroup log##__LINE__(name, _buf.str().c_str(), __FILE__, __LINE__)

#define LOG_INFO(msg)               \
    LOG_EVENT_(1, msg, __FILE__, __LINE__)

#define LOG_INFO2(name, extra)      \
    LOG_EVENT_2(1, name, extra, __FILE__, __LINE__)

#define LOG_WARNING(msg)            \
    LOG_EVENT_(2, msg, __FILE__, __LINE__)

#define LOG_WARNING2(name, extra)   \
    LOG_EVENT_2(2, name, extra, __FILE__, __LINE__)

#define LOG_ERROR(msg)              \
    LOG_EVENT_(3, msg, __FILE__, __LINE__)

#define LOG_ERROR2(name, extra)     \
    LOG_EVENT_2(3, name, extra, __FILE__, __LINE__)

//-------------------------------

void PushLogGroup(const wchar_t* name, const wchar_t* extra, const char* file, int line);
void PopLogGroup();
void WriteLogItem(int type, const wchar_t* name, const wchar_t* extra, const char*, int);

class CLogGroup
{
public:
    CLogGroup(const wchar_t* name, const wchar_t* extra, const char* file, int line)
    {
        PushLogGroup(name, extra, file, line);
    }
    ~CLogGroup()
    {
        PopLogGroup();
    }
};

#define LOG_EVENT_(type, msg, file, line)                           \
    do {                                                            \
        std::wostringstream _buf;                                   \
        _buf << msg;                                                \
        WriteLogItem(type, _buf.str().c_str(), L"", file, line);    \
    } while (0)

#define LOG_EVENT_2(type, name, extra, file, line)                  \
    do {                                                            \
        std::wostringstream _buf;                                   \
        _buf << extra;                                              \
        WriteLogItem(type, name, _buf.str().c_str(), file, line);   \
    } while (0)

//-------------------------------

#include "Ix_LogObserver.h"

class LogPluginHelper
{
private:
    HMODULE         dll;
    Ix_LogObserver* observer;

    LogPluginHelper() : dll(NULL), observer(NULL)
    {
    }

public:
    ~LogPluginHelper()
    {
        if (dll)
        {
            FreeLibrary(dll);
        }
    }

    Ix_LogObserver* GetObserver(bool load = false)
    {
        if (load && !observer)
        {
            typedef Ix_LogObserver* (*FUNC)();
            dll = LoadLibraryW(L"LogWriter.plugin.dll");
            FUNC func = (FUNC)GetProcAddress(dll, "GetLogObserver");
            observer = func ? func() : NULL;
        }

        return observer;
    }

    static LogPluginHelper& Instance()
    {
        static LogPluginHelper obj;
        obj.GetObserver(true);
        return obj;
    }

    static long& Level()
    {
        static long level = 0;
        return level;
    }
};

inline void PushLogGroup(const wchar_t* name, const wchar_t* extra, 
                         const char* file, int line)
{
    Ix_LogObserver* observer = LogPluginHelper::Instance().GetObserver();
    if (observer)
    {
        observer->OnPushGroup(
            ++LogPluginHelper::Instance().Level(), name, extra, L"", L"", file, line);
    }
}

inline void PopLogGroup()
{
    Ix_LogObserver* observer = LogPluginHelper::Instance().GetObserver();
    if (observer)
    {
        observer->OnPopGroup(LogPluginHelper::Instance().Level()--);
    }
}

inline void WriteLogItem(int type, const wchar_t* name, const wchar_t* extra, 
                         const char* file, int line)
{
    Ix_LogObserver* observer = LogPluginHelper::Instance().GetObserver();
    if (observer)
    {
        observer->OnWriteLog(type, name, extra, L"", L"", file, line);
    }
}

#endif // X3_LOG_LOGHELPER2_H_