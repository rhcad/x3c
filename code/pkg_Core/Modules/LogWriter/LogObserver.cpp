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

#include "stdafx.h"
#include "LogObserver.h"

#include <RelToAbs.h>
#include <Ix_FileUtility.h>
#include <Ix_TextFileUtil.h>
#include <Ix_LogManager.h>

#pragma warning(disable:4127)       // conditional expression is constant
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>

CLogObserver::CLogObserver()
    : m_bInited(false), m_nGroupLevel(0)
{
#if _MSC_VER < 1600
    // 确保log4cplus能保存中文字符，否则 _Wcrtomb 失败
    std::locale::global(std::locale(""));
#endif

    Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
    if (pIFManager.IsNotNull())
        pIFManager->RegisterObserver(this);
}

CLogObserver::~CLogObserver()
{
    if (m_bInited)
        Logger::shutdown();
    
    Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
    if (pIFManager.IsNotNull())
        pIFManager->UnRegisterObserver(this);
}

Logger CLogObserver::GetLogger()
{
    InitLogFile();
    return Logger::getRoot();
}

void CLogObserver::InitLogFile()
{
    if (!m_bInited)
    {
        m_bInited = true;

        MakerInitVars();

        Cx_Interface<Ix_FileUtility> pIFUtility(CLSID_FileUtility);
        if (pIFUtility && !pIFUtility->CreateDirectory(m_wstrPath.c_str(), true))
        {
            m_wstrPath = MakeTempFileName(L"Log", false);
            pIFUtility->CreateDirectory(m_wstrPath.c_str(), true);
        }

        wchar_t szPropFile[MAX_PATH] = {0};
        lstrcpynW(szPropFile, m_wstrPath.c_str(), MAX_PATH);
        PathAppendW(szPropFile, m_wstrAppName.c_str());
        StrCatW(szPropFile, L".properties");

        if (pIFUtility && !pIFUtility->IsPathFileExists(szPropFile))
        {
            WritePropFile(szPropFile);
        }

        PropertyConfigurator::doConfigure(szPropFile);
    }
}

void CLogObserver::MakerInitVars()
{
    wchar_t szPath[MAX_PATH] = {0};
    
    if (m_wstrPath.empty())
    {
        m_wstrPath = RelToAbsWithPlugin(L"../log", false);
    }
    else if (PathIsRelativeW(m_wstrPath.c_str()))
    {
        m_wstrPath = FileNameRelToAbs(m_wstrPath.c_str(), false);
    }
    
    lstrcpynW(szPath, m_wstrPath.c_str(), MAX_PATH);
    PathAddBackslashW(szPath);
    m_wstrPath = szPath;
    
    if (m_wstrAppName.empty())
    {
        GetModuleFileNameW(GetMainModuleHandle(), szPath, MAX_PATH);
        wchar_t* pszName = PathFindFileNameW(szPath);
        PathRemoveExtensionW(pszName);
        m_wstrAppName = helpers::toLower(pszName);
    }
}

void CLogObserver::WritePropFile(const wchar_t* pszFileName)
{
    std::wostringstream buf;

    buf << L"#root logger" << std::endl;
    buf << L"log4cplus.rootLogger=DEBUG,ROOTAPPENDER" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER=log4cplus::RollingFileAppender" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER.File="
        << m_wstrPath << m_wstrAppName << L".log" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER.MaxFileSize=1024KB" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER.MaxBackupIndex=3" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER.layout=log4cplus::TTCCLayout" << std::endl;

    Cx_Interface<Ix_TextFileUtil> pIFTextUtil(CLSID_TextUtil);
    InterfaceSafeCall(pIFTextUtil, SaveTextFile(buf.str(), pszFileName, false));
}

void CLogObserver::OnPushGroup(long nLevel, 
                               const std::wstring& wstrMsg, 
                               const std::wstring& wstrExtra, 
                               const std::wstring& wstrModule, 
                               const std::wstring& wstrID)
{
    std::wostringstream buf(L"");

    for (int i = 0; i < m_nGroupLevel; i++)
    {
        buf << L"  ";
    }
    buf << wstrMsg;
    if (!wstrExtra.empty())
    {
        buf << L" (" << wstrExtra << L")";
    }
    if (!wstrModule.empty())
    {
        buf << L" @" << wstrModule << L":" << wstrID;
    }

    LOG4CPLUS_INFO_STR(GetLogger(), buf.str());
    m_nGroupLevel = nLevel;
}

void CLogObserver::OnPopGroup(long nLevel)
{
    m_nGroupLevel = nLevel - 1;
}

void CLogObserver::OnWriteLog(int nType, 
                              const std::wstring& wstrMsg, 
                              const std::wstring& wstrExtra, 
                              const std::wstring& wstrModule, 
                              const std::wstring& wstrID, 
                              const std::wstring& wstrFile, 
                              long nLine)
{
    std::wostringstream buf;

    for (int i = 0; i < m_nGroupLevel; i++)
    {
        buf << L"  ";
    }
    buf << wstrMsg;
    if (!wstrExtra.empty())
    {
        buf << L" (" << wstrExtra << L")";
    }
    if (!wstrModule.empty())
    {
        buf << L" @" << wstrModule << L":" << wstrID;
    }
    buf << L" [" << wstrFile << L" L" << nLine << L"]";

    switch (nType)
    {
    case kLogType_Debug:
        LOG4CPLUS_DEBUG_STR(GetLogger(), buf.str());
        break;
    case kLogType_Info:
        LOG4CPLUS_INFO_STR(GetLogger(), buf.str());
        break;
    case kLogType_Warning:
        LOG4CPLUS_WARN_STR(GetLogger(), buf.str());
        break;
    case kLogType_Error:
        LOG4CPLUS_ERROR_STR(GetLogger(), buf.str());
        break;
    case kLogType_Fatal:
        LOG4CPLUS_FATAL_STR(GetLogger(), buf.str());
        break;
    }
}

#pragma warning(default:4127)
