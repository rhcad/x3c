// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// Changes:
// 2011-02-28: Avoid reenter in WriteLog.

#include "StdAfx.h"
#include "Cx_LogManager.h"
#include <ILogObserver.h>
#include <ConvStr.h>
#include <Xml/Ix_StringTable.h>
#include <LockCount.h>

Cx_LogManager::Cx_LogManager()
    : m_groupLevel(0), m_loglock(0)
{
}

Cx_LogManager::~Cx_LogManager()
{
}

bool Cx_LogManager::RegisterObserver(ILogObserver* observer)
{
    if (observer != NULL && find_value(m_observers, observer) < 0)
    {
        m_observers.push_back(observer);
        return true;
    }
    return false;
}

void Cx_LogManager::UnRegisterObserver(ILogObserver* observer)
{
    erase_value(m_observers, observer);
}

bool Cx_LogManager::PushGroup(const wchar_t* msg, const wchar_t* extra)
{
    std::wstring msg2, extra2, module, idname;
    CheckMsgParam(msg2, extra2, module, idname, msg, extra);

    InterlockedIncrement(&m_groupLevel);
    for (ObserverIt it = m_observers.begin(); it != m_observers.end(); ++it)
    {
        (*it)->OnPushGroup(m_groupLevel, msg2, extra2, module, idname);
    }

    return true;
}

bool Cx_LogManager::PopGroup()
{
    for (ObserverIt it = m_observers.begin(); it != m_observers.end(); ++it)
    {
        (*it)->OnPopGroup(m_groupLevel);
    }
    InterlockedDecrement(&m_groupLevel);

    return true;
}

bool Cx_LogManager::WriteLog(kLogType type, const wchar_t* msg, 
    const wchar_t* extra, const char* file, long line)
{
    CLockCount locker(&m_loglock);
    if (m_loglock > 1)
    {
        return false;
    }

    std::wstring wstrFile(std::a2w(TrimFileName(file)));
    std::wstring msg2, extra2, module, idname;
    CheckMsgParam(msg2, extra2, module, idname, msg, extra);

    for (ObserverIt it = m_observers.begin(); it != m_observers.end(); ++it)
    {
        (*it)->OnWriteLog(type, msg2, extra2, 
            module, idname, wstrFile, line);
    }

#ifdef _DEBUG
    const wchar_t* names[] = { L"> LogInfo: ", 
        L"> LogWarning: ", L"> LogError: ", L"> FatalError: " };
    if (type >= kLogType_Info && type <= kLogType_Fatal)
    {
        OutputDebugStringW(names[type - kLogType_Info]);
        OutputDebugStringW(msg);
        if (!extra2.empty())
        {
            OutputDebugStringW(L", ");
            OutputDebugStringW(extra);
        }
        OutputDebugStringW(L"\n");
    }
#endif

    return true;
}

bool Cx_LogManager::WriteLog(kLogType type, const char* msg, 
    const char* extra, const char* file, long line)
{
    return WriteLog(type, std::a2w(msg).c_str(), 
        std::a2w(extra).c_str(), file, line);
}

int Cx_LogManager::CrtDbgReport(const char* msg, const char* file, long line)
{
    WriteLog(kLogType_Fatal, L"@LogManager:IDS_ASSERTION_FAILED", 
        std::a2w(msg).c_str(), file, line);

#ifndef _MSC_VER
    return 3;
#else
    wchar_t buf[512];

    swprintf_s(buf, 512, 
        L"Debug Assertion Failed!\n"
        L"\nExpression: %s"
        L"\nFile: %s"
        L"\nLine: %d"
        L"\n\n(Press Retry to debug the application)",
        std::a2w(msg).c_str(), 
        std::a2w(TrimFileName(file)).c_str(), line);

    return MessageBoxW(NULL, buf, L"Debug Assertion Failed", 
        MB_TASKMODAL|MB_ICONHAND|MB_ABORTRETRYIGNORE|MB_SETFOREGROUND);
#endif
}

const char* Cx_LogManager::TrimFileName(const char* file)
{
    ASSERT(file && *file);

    const char* pszName = PathFindFileNameA(file);
    int folder = 0;

    while (pszName > file)
    {
        pszName--;
        if ('\\' == *pszName || '/' == *pszName)
        {
            if (++folder > 2)
            {
                pszName++;
                break;
            }
        }
    }

    return pszName;
}

bool Cx_LogManager::CheckMsgParam(std::wstring& msg2, 
    std::wstring& extra2, std::wstring& module, std::wstring& idname, 
    const wchar_t* msg, const wchar_t* extra)
{
    bool ret = false;

    msg2 = msg ? msg : L"";
    extra2 = extra ? extra : L"";

    if (!msg2.empty() && L'@' == msg2[0])  // @Module:IDS_XXX
    {
        Cx_Interface<Ix_StringTable> pIFTable(CLSID_StringTable);
        ret = pIFTable && pIFTable->GetValue(msg2, msg2, module, idname);

        if (msg2.empty())
        {
            msg2 = idname;
        }
    }

    return ret;
}
