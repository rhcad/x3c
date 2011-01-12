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

#include "StdAfx.h"
#include "Cx_LogManager.h"
#include <ILogObserver.h>
#include <ConvStr.h>
#include <Xml/Ix_StringTable.h>

Cx_LogManager::Cx_LogManager()
    : m_nGroupLevel(0)
{
}

Cx_LogManager::~Cx_LogManager()
{
}

bool Cx_LogManager::RegisterObserver(ILogObserver* observer)
{
    if (observer != NULL && find_value(m_arrObserver, observer) < 0)
    {
        m_arrObserver.push_back(observer);
        return true;
    }
    return false;
}

void Cx_LogManager::UnRegisterObserver(ILogObserver* observer)
{
    erase_value(m_arrObserver, observer);
}

bool Cx_LogManager::PushGroup(LPCWSTR pszMsg, LPCWSTR pszExtra)
{
    std::wstring wstrMsg, wstrExtra, wstrModule, wstrID;
    CheckMsgParam(wstrMsg, wstrExtra, wstrModule, wstrID, pszMsg, pszExtra);

    InterlockedIncrement(&m_nGroupLevel);
    for (ObserverIt it = m_arrObserver.begin(); it != m_arrObserver.end(); ++it)
    {
        (*it)->OnPushGroup(m_nGroupLevel, wstrMsg, wstrExtra, wstrModule, wstrID);
    }

    return true;
}

bool Cx_LogManager::PopGroup()
{
    for (ObserverIt it = m_arrObserver.begin(); it != m_arrObserver.end(); ++it)
    {
        (*it)->OnPopGroup(m_nGroupLevel);
    }
    InterlockedDecrement(&m_nGroupLevel);

    return true;
}

bool Cx_LogManager::WriteLog(kLogType nType, LPCWSTR pszMsg, 
    LPCWSTR pszExtra, LPCSTR pszFile, long nLine)
{
    std::wstring wstrFile(std::a2w(TrimFileName(pszFile)));
    std::wstring wstrMsg, wstrExtra, wstrModule, wstrID;
    CheckMsgParam(wstrMsg, wstrExtra, wstrModule, wstrID, pszMsg, pszExtra);

    for (ObserverIt it = m_arrObserver.begin(); it != m_arrObserver.end(); ++it)
    {
        (*it)->OnWriteLog(nType, wstrMsg, wstrExtra, 
            wstrModule, wstrID, wstrFile, nLine);
    }

#ifdef _DEBUG
    LPCWSTR names[] = { L"> LogInfo: ", 
        L"> LogWarning: ", L"> LogError: ", L"> LogError: " };
    if (nType >= kLogType_Info && nType <= kLogType_Fatal)
    {
        OutputDebugStringW(names[nType - kLogType_Info]);
        OutputDebugStringW(pszMsg);
        if (!wstrExtra.empty())
        {
            OutputDebugStringW(L", ");
            OutputDebugStringW(pszExtra);
        }
        OutputDebugStringW(L"\n");
    }
#endif

    return true;
}

bool Cx_LogManager::WriteLog(kLogType nType, LPCSTR pszMsg, 
    LPCSTR pszExtra, LPCSTR pszFile, long nLine)
{
    return WriteLog(nType, std::a2w(pszMsg).c_str(), 
        std::a2w(pszExtra).c_str(), pszFile, nLine);
}

int Cx_LogManager::CrtDbgReport(LPCSTR szMsg, LPCSTR szFile, long nLine)
{
    WriteLog(kLogType_Fatal, L"@LogManager:IDS_ASSERTION_FAILED", 
        std::a2w(szMsg).c_str(), szFile, nLine);

    WCHAR buf[512];

    swprintf_s(buf, 512, 
        L"Debug Assertion Failed!\n"
        L"\nExpression: %s"
        L"\nFile: %s"
        L"\nLine: %d"
        L"\n\n(Press Retry to debug the application)",
        std::a2w(szMsg).c_str(), 
        std::a2w(TrimFileName(szFile)).c_str(), nLine);

    return MessageBoxW(NULL, buf, L"Debug Assertion Failed", 
        MB_TASKMODAL|MB_ICONHAND|MB_ABORTRETRYIGNORE|MB_SETFOREGROUND);
}

LPCSTR Cx_LogManager::TrimFileName(LPCSTR pszFile)
{
    ASSERT(pszFile && *pszFile);

    LPCSTR pszName = PathFindFileNameA(pszFile);
    int folder = 0;

    while (pszName > pszFile)
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

bool Cx_LogManager::CheckMsgParam(std::wstring& wstrMsg, 
    std::wstring& wstrExtra, std::wstring& wstrModule, std::wstring& wstrID, 
    LPCWSTR pszMsg, LPCWSTR pszExtra)
{
    bool ret = false;

    wstrMsg = pszMsg ? pszMsg : L"";
    wstrExtra = pszExtra ? pszExtra : L"";

    if (!wstrMsg.empty() && '@' == wstrMsg[0])  // @Module:IDS_XXX
    {
        Cx_Interface<Ix_StringTable> pIFTable(CLSID_StringTable);
        ret = pIFTable && pIFTable->GetValue(wstrMsg, pszMsg, wstrModule, wstrID);

        if (wstrMsg.empty())
        {
            wstrMsg = wstrID;
        }
    }

    return ret;
}
