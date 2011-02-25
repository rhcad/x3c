// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// v2: 2011.02.07, ooyg: Using Ix_AppWorkPath to get logging path.
// v3: 2011.02.21, ooyg: Replace "\n" to "\\n " in LogWriter plugin.
// v4: 2011.02.24, ooyg: Copy log files to server if error message has fired.

#include "stdafx.h"
#include "LogObserver.h"

#include <RelToAbs.h>
#include <Ix_FileUtility.h>
#include <Ix_TextFileUtil.h>
#include <Ix_LogManager.h>
#include <PluginManager/Ix_AppWorkPath.h>
#include <ctrim.h>

#pragma warning(disable:4127)       // conditional expression is constant
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>

CLogObserver::CLogObserver()
    : m_inited(false), m_level(0), m_haserr(false)
{
#if !defined(_MSC_VER) || _MSC_VER < 1600
    // assure log4cplus can save chinese text, avoid _Wcrtomb failing.
    std::locale::global(std::locale(""));
#endif

    Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
    if (pIFManager.IsNotNull())
    {
        pIFManager->RegisterObserver(this);
    }
}

CLogObserver::~CLogObserver()
{
    Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
    if (pIFManager.IsNotNull())
    {
        pIFManager->UnRegisterObserver(this);
    }

    if (m_inited)
    {
        Logger::shutdown();

        if (m_haserr)
        {
            Cx_Interface<Ix_FileUtility> pIFUtility(CLSID_FileUtility);
            wchar_t path[MAX_PATH] = { 0 };
            wchar_t hostname[33] = { 0 };
            unsigned long namesize = 33;

            if (pIFUtility && GetServerPath(path)
#ifdef GetComputerName
                && GetComputerNameW(hostname, &namesize)
#endif
                )
            {
                PathAppendW(path, hostname);
                PathAddBackslashW(path);
                pIFUtility->CopyPathFile(m_path.c_str(), path);
            }
        }
    }
}

bool CLogObserver::GetServerPath(wchar_t* path)
{
    wchar_t inifile[MAX_PATH];

    lstrcpynW(inifile, m_path.c_str(), MAX_PATH);
    PathAppendW(inifile, L"LogWriter.ini");

    return GetPrivateProfileStringW(L"Server", L"Path", L"", 
        path, MAX_PATH, inifile) > 1;
}

Logger CLogObserver::GetLogger()
{
    InitLogFile();
    return Logger::getRoot();
}

void CLogObserver::InitLogFile()
{
    if (!m_inited)
    {
        m_inited = true;

        MakerInitVars();

        Cx_Interface<Ix_FileUtility> pIFUtility(CLSID_FileUtility);
        if (pIFUtility && !pIFUtility->CreateDirectory(m_path.c_str(), true))
        {
            m_path = MakeTempFileName(L"Log", false);
            pIFUtility->CreateDirectory(m_path.c_str(), true);
        }

        wchar_t propfile[MAX_PATH] = {0};
        lstrcpynW(propfile, m_path.c_str(), MAX_PATH);
        PathAppendW(propfile, m_appname.c_str());
        StrCatW(propfile, L".properties");

        if (pIFUtility && !pIFUtility->IsPathFileExists(propfile))
        {
            WritePropFile(propfile);
        }

        PropertyConfigurator::doConfigure(propfile);
    }
}

void CLogObserver::MakerInitVars()
{
    wchar_t path[MAX_PATH] = {0};
    
    if (m_path.empty())
    {
        m_path = GetAppWorkPath() + L"log";
    }
    
    lstrcpynW(path, m_path.c_str(), MAX_PATH);
    PathAddBackslashW(path);
    m_path = path;
    
    if (m_appname.empty())
    {
        GetModuleFileNameW(GetMainModuleHandle(), path, MAX_PATH);
        wchar_t* name = PathFindFileNameW(path);
        PathRemoveExtensionW(name);
        m_appname = helpers::toLower(name);
    }
}

void CLogObserver::WritePropFile(const wchar_t* filename)
{
    std::wostringstream buf;

    buf << L"#root logger" << std::endl;
    buf << L"log4cplus.rootLogger=DEBUG,ROOTAPPENDER" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER=log4cplus::RollingFileAppender" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER.File="
        << m_path << m_appname << L".log" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER.MaxFileSize=1024KB" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER.MaxBackupIndex=3" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER.layout=log4cplus::TTCCLayout" << std::endl;

    Cx_Interface<Ix_TextFileUtil> pIFTextUtil(CLSID_TextUtil);
    InterfaceSafeCall(pIFTextUtil, SaveTextFile(buf.str(), filename, false));
}

void CLogObserver::OnPushGroup(long level, 
                               const std::wstring& msg, 
                               const std::wstring& extra, 
                               const std::wstring& module, 
                               const std::wstring& idname)
{
    std::wostringstream buf(L"");

    for (int i = 0; i < m_level; i++)
    {
        buf << L"  ";
    }
    buf << msg;
    if (!extra.empty())
    {
        buf << L" (" << extra << L")";
    }
    if (!module.empty())
    {
        buf << L" @" << module << L":" << idname;
    }

    LOG4CPLUS_INFO_STR(GetLogger(), buf.str());
    m_level = level;
}

void CLogObserver::OnPopGroup(long level)
{
    m_level = level - 1;
}

void CLogObserver::OnWriteLog(int type, 
                              const std::wstring& msg, 
                              const std::wstring& extra, 
                              const std::wstring& module, 
                              const std::wstring& idname, 
                              const std::wstring& file, 
                              long line)
{
    std::wostringstream buf;

    for (int i = 0; i < m_level; i++)
    {
        buf << L"  ";
    }

    if (!module.empty())
    {
        buf << L"@" << module << L":" << idname << L", ";
    }

    if (msg.find(L"\n") != std::wstring::npos)
    {
        std::wstring text(msg);
        trim::replace(text, std::wstring(L"\n"), std::wstring(L"\\n "));
        buf << text;
    }
    else
    {
        buf << msg;
    }

    if (extra.find(L"\n") != std::wstring::npos)
    {
        std::wstring text(extra);
        trim::replace(text, std::wstring(L"\n"), std::wstring(L"\\n "));
        buf << L" (" << text << L")";
    }
    else if (!extra.empty())
    {
        buf << L" (" << extra << L")";
    }

    buf << L" [" << file << L" L" << line << L"]";

    switch (type)
    {
    case kLogType_Debug:
        LOG4CPLUS_DEBUG_STR(GetLogger(), buf.str());
        break;
    case kLogType_Info:
        LOG4CPLUS_INFO_STR(GetLogger(), buf.str());
        break;
    case kLogType_Warning:
        LOG4CPLUS_WARN_STR(GetLogger(), buf.str());
        m_haserr = true;
        break;
    case kLogType_Error:
        LOG4CPLUS_ERROR_STR(GetLogger(), buf.str());
        m_haserr = true;
        break;
    case kLogType_Fatal:
        LOG4CPLUS_FATAL_STR(GetLogger(), buf.str());
        m_haserr = true;
        break;
    }
}

#pragma warning(default:4127)
