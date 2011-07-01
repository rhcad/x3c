// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// Changes:
// 2011-02-28: Avoid reenter in WriteLog.
// 2011-07-01: Support delay-load feature for logging observer plugins.

#include <UtilFunc/PluginInc.h>
#include "Cx_LogManager.h"
#include <Log/Ix_LogObserver.h>
#include <UtilFunc/ConvStr.h>
#include <Xml/Ix_StringTable.h>
#include <UtilFunc/LockCount.h>
#include "../PluginManager/Ix_PluginDelayLoad.h"

Cx_LogManager::Cx_LogManager()
    : m_groupLevel(0), m_loglock(0)
{
}

Cx_LogManager::~Cx_LogManager()
{
}

bool Cx_LogManager::RegisterObserver(Ix_LogObserver* observer, HMODULE fromdll)
{
    ITEM item(observer, fromdll);

    if (observer != NULL && x3::find_value(m_observers, item) < 0)
    {
        m_observers.push_back(item);

        Cx_Interface<Ix_PluginDelayLoad> pIFLoader(x3::CLSID_PluginDelayLoad);
        if (pIFLoader)
        {
            pIFLoader->AddObserverPlugin(fromdll, "x3::LogObserver");
        }

        return true;
    }

    return false;
}

void Cx_LogManager::UnRegisterObserver(Ix_LogObserver* observer)
{
    for (ObserverIt it = m_observers.begin(); it != m_observers.end(); ++it)
    {
        if (it->first == observer)
        {
            m_observers.erase(it);
            break;
        }
    }
}

void Cx_LogManager::FireFirstEvent()
{
    static bool fired = false;
    if (!fired)
    {
        fired = true;
        Cx_Interface<Ix_PluginDelayLoad> pIFLoader(x3::CLSID_PluginDelayLoad);
        if (pIFLoader)
        {
            pIFLoader->FireFirstEvent("x3::LogObserver");
        }
    }
}

bool Cx_LogManager::PushGroup(const wchar_t* msg, const wchar_t* extra)
{
    std::wstring msg2, extra2, module, idname;
    CheckMsgParam(msg2, extra2, module, idname, msg, extra);

    InterlockedIncrement(&m_groupLevel);
    FireFirstEvent();

    for (ObserverIt it = m_observers.begin(); it != m_observers.end(); ++it)
    {
        it->first->OnPushGroup(m_groupLevel, msg2, extra2, module, idname);
    }

    return true;
}

bool Cx_LogManager::PopGroup()
{
    for (ObserverIt it = m_observers.begin(); it != m_observers.end(); ++it)
    {
        it->first->OnPopGroup(m_groupLevel);
    }
    InterlockedDecrement(&m_groupLevel);

    return true;
}

bool Cx_LogManager::WriteLog(x3LogType type, const wchar_t* msg,
    const wchar_t* extra, const char* file, long line)
{
    CLockCount locker(&m_loglock);
    if (m_loglock > 1)
    {
        return false;
    }

    std::wstring wstrFile(x3::a2w(TrimFileName(file)));
    std::wstring msg2, extra2, module, idname;

    CheckMsgParam(msg2, extra2, module, idname, msg, extra);
    FireFirstEvent();

    for (ObserverIt it = m_observers.begin(); it != m_observers.end(); ++it)
    {
        it->first->OnWriteLog(type, msg2, extra2,
            module, idname, wstrFile, line);
    }

#if defined(_DEBUG) && defined(OutputDebugString)
    const wchar_t* names[] = { L"> LogInfo: ",
        L"> LogWarning: ", L"> LogError: ", L"> FatalError: " };
    if (type >= x3LogType_Info && type <= x3LogType_Fatal)
    {
        OutputDebugStringW(names[type - x3LogType_Info]);
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

bool Cx_LogManager::WriteLog(x3LogType type, const char* msg,
    const char* extra, const char* file, long line)
{
    return WriteLog(type, x3::a2w(msg).c_str(),
        x3::a2w(extra).c_str(), file, line);
}

int Cx_LogManager::CrtDbgReport(const char* msg, const char* file, long line)
{
    WriteLog(x3LogType_Fatal, L"@LogManager:IDS_ASSERTION_FAILED",
        x3::a2w(msg).c_str(), file, line);

#ifndef _WIN32
    return 3;
#else
    wchar_t buf[512];

    swprintf_s(buf, 512,
        L"Debug Assertion Failed!\n"
        L"\nExpression: %s"
        L"\nFile: %s"
        L"\nLine: %d"
        L"\n\n(Press Retry to debug the application)",
        x3::a2w(msg).c_str(),
        x3::a2w(TrimFileName(file)).c_str(), line);

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
        Cx_Interface<Ix_StringTable> pIFTable(x3::CLSID_StringTable);
        ret = pIFTable && pIFTable->GetValue(msg2, msg2, module, idname);

        if (msg2.empty())
        {
            msg2 = idname;
        }
    }

    return ret;
}
