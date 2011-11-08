// x3c - C++ PluginFramework
// 2011.02.07: Using Ix_AppWorkPath to get logging path.
// 2011.02.21: Replace "\n" to "\\n" in LogWriter plugin.
// 2011.02.24: Copy log files to server if error message has fired.
// 2011.02.28: Hide progress UI in CopyLogFilesToServer.
// 2011-07-01: Support delay-load feature for logging observer plugins.
// 2011-11-08: Can work regardless no PluginManager, FileUtility or TextUtility plugins.

#include <UtilFunc/PluginInc.h>
#include "LogObserver.h"

#include <UtilFunc/RelToAbs.h>
#include <Utility/Ix_FileUtility.h>
#include <Log/Ix_LogManager.h>
#include <PluginManager/Ix_AppWorkPath.h>
#include <UtilFunc/ctrim.h>
#include <UtilFunc/ConvStr.h>

#ifdef _MSC_VER                     // hide warnings
#pragma warning (push, 3)
#pragma warning(disable:4127)       // conditional expression is constant
#endif
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>

CLogObserver::CLogObserver()
    : m_inited(false), m_level(0), m_haserr(0), m_copyflags(0)
{
#if !defined(_MSC_VER) || _MSC_VER < 1600
    // assure log4cplus can save chinese text, avoid _Wcrtomb failing.
    std::locale::global(std::locale(""));
#endif

    Cx_Interface<Ix_LogManager> pIFManager(x3::CLSID_LogManager);
    if (pIFManager.IsNotNull())
    {
        pIFManager->RegisterObserver(this, x3GetModuleHandle());
    }
}

CLogObserver::~CLogObserver()
{
    Cx_Interface<Ix_LogManager> pIFManager(x3::CLSID_LogManager);
    if (pIFManager.IsNotNull())
    {
        pIFManager->UnRegisterObserver(this);
    }

    if (m_inited)
    {
        Logger::shutdown();

        if (m_haserr)
        {
            CopyLogFilesToServer();
        }
    }
}

bool CLogObserver::CopyLogFilesToServer()
{
	bool ret = false;
#ifdef _WIN32
    Cx_Interface<Ix_FileUtility> pIFUtility(x3::CLSID_FileUtility);
    wchar_t path[MAX_PATH] = { 0 };
    wchar_t hostname[33] = { 0 };
    unsigned long namesize = 33;

    if (pIFUtility && GetServerPath(path)
        && GetComputerNameW(hostname, &namesize))
    {
        PathAppendW(path, hostname);
        PathAddBackslashW(path);

        HWND oldwnd = pIFUtility->GetMsgBoxOwnerWnd();
        pIFUtility->SetMsgBoxOwnerWnd(NULL);
        ret = pIFUtility->CopyPathFile(m_path.c_str(), path);
        pIFUtility->SetMsgBoxOwnerWnd(oldwnd);
    }
#endif
    return ret;
}

bool CLogObserver::GetServerPath(wchar_t* path)
{
#ifdef _WIN32
    wchar_t inifile[MAX_PATH];

    wcscpy_s(inifile, MAX_PATH, m_path.c_str());
    PathAppendW(inifile, L"LogWriter.ini");

    if (0 == m_copyflags)
    {
        m_copyflags = GetPrivateProfileIntW(L"Server", L"CopyFlags",
            -1, inifile) | 0x10000000;
    }

    return GetPrivateProfileStringW(L"Server", L"Path", L"",
        path, MAX_PATH, inifile) > 1;
#else
    return false;
#endif
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

        wchar_t propfile[MAX_PATH] = {0};
        wcscpy_s(propfile, MAX_PATH, m_path.c_str());
        PathAppendW(propfile, m_appname.c_str());
        wcscat_s(propfile, _countof(propfile), L".properties");

        Cx_Interface<Ix_FileUtility> pIFUtility(x3::CLSID_FileUtility);
        SafeCall(pIFUtility, CreateDirectory(m_path.c_str(), true));
        ::CreateDirectoryW(m_path.c_str(), NULL);

        if (!PathFileExistsW(propfile))
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
        Cx_Interface<Ix_AppWorkPath> pIFPath(x3::CLSID_AppWorkPath);
        if (pIFPath)
        {
            m_path = pIFPath->GetWorkPath() + L"log";
        }
        else
        {
            GetModuleFileNameW(x3::GetMainModuleHandle(), path, MAX_PATH);
            PathRemoveFileSpecW(path);
            PathAppendW(path, L"log");
            m_path = path;
        }
    }

    wcscpy_s(path, MAX_PATH, m_path.c_str());
    PathAddBackslashW(path);
    m_path = path;

    if (m_appname.empty())
    {
        GetModuleFileNameW(x3::GetMainModuleHandle(), path, MAX_PATH);
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
    buf << L"log4cplus.appender.ROOTAPPENDER.MaxFileSize=2048KB" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER.MaxBackupIndex=3" << std::endl;
    buf << L"log4cplus.appender.ROOTAPPENDER.layout=log4cplus::TTCCLayout" << std::endl;

    std::wstring content(buf.str());
    HANDLE hFile = NULL;

    if (!x3OpenFileForWrite(hFile, filename))
    {
        DWORD err = GetLastError();
        X3LOG_ERROR2(L"@TextUtility:IDS_WRITE_FAIL", err << L", " << filename);
    }
    else
    {
        ::WriteFile(hFile, content.c_str(), x3::GetSize(content), NULL, NULL);
        x3CloseFile(hFile);
    }
}

const char* CLogObserver::TrimFileName(const char* file)
{
    ASSERT(file && *file);

    const char* name = PathFindFileNameA(file);
    int folder = 0;

    while (name > file)
    {
        name--;
        if ('\\' == *name || '/' == *name)
        {
            if (++folder > 2)
            {
                name++;
                break;
            }
        }
    }

    return name;
}

void CLogObserver::OnPushGroup(long level,
                               const std::wstring& msg,
                               const std::wstring& extra,
                               const std::wstring& module,
                               const std::wstring& idname,
                               const char* file, long line)
{
    std::wostringstream buf(L"");

    for (int i = 0; i < m_level; i++)
    {
        buf << L"  ";
    }

    if (msg.find(L"\n") != std::wstring::npos)
    {
        std::wstring text(msg);
        trim::replace(text, std::wstring(L"\n"), std::wstring(L"\\n"));
        buf << text;
    }
    else
    {
        buf << msg;
    }

    if (extra.find(L"\n") != std::wstring::npos)
    {
        std::wstring text(extra);
        trim::replace(text, std::wstring(L"\n"), std::wstring(L"\\n"));
        buf << L" (" << text << L")";
    }
    else if (!extra.empty())
    {
        buf << L" (" << extra << L")";
    }

    if (!module.empty())
    {
        buf << L" @" << module << L":" << idname;
    }
    if (file && *file)
    {
        buf << L" [" << x3::a2w(TrimFileName(file)) << L" L" << line << L"]";
    }

    LOG4CPLUS_INFO_STR(GetLogger(), buf.str());
    m_level = level;
}

void CLogObserver::OnPopGroup(long level)
{
    m_level = level - 1;

    if (m_haserr & 0x01)
    {
        m_haserr &= ~0x01;
        if (m_copyflags & 0x01)
        {
            if (!CopyLogFilesToServer())
            {
                m_copyflags &= ~0x01;
            }
        }
    }
}

void CLogObserver::OnWriteLog(int type,
                              const std::wstring& msg,
                              const std::wstring& extra,
                              const std::wstring& module,
                              const std::wstring& idname,
                              const char* file,
                              long line)
{
    std::wostringstream buf;

    for (int i = 0; i < m_level; i++)
    {
        buf << L"  ";
    }

    if (msg.find(L"\n") != std::wstring::npos)
    {
        std::wstring text(msg);
        trim::replace(text, std::wstring(L"\n"), std::wstring(L"\\n"));
        buf << text;
    }
    else
    {
        buf << msg;
    }

    if (extra.find(L"\n") != std::wstring::npos)
    {
        std::wstring text(extra);
        trim::ctrim(text);
        trim::replace(text, std::wstring(L"\n"), std::wstring(L"\\n"));
        buf << L" (" << text << L")";
    }
    else if (!extra.empty())
    {
        buf << L" (" << extra << L")";
    }

    if (!module.empty())
    {
        buf << L" @" << module << L":" << idname;
    }
    buf << L" [" << x3::a2w(TrimFileName(file)) << L" L" << line << L"]";

    switch (type)
    {
    case x3LogType_Debug:
        LOG4CPLUS_DEBUG_STR(GetLogger(), buf.str());
        break;
    case x3LogType_Info:
        LOG4CPLUS_INFO_STR(GetLogger(), buf.str());
        break;
    case x3LogType_Warning:
        LOG4CPLUS_WARN_STR(GetLogger(), buf.str());
        break;
    case x3LogType_Error:
        LOG4CPLUS_ERROR_STR(GetLogger(), buf.str());
        break;
    case x3LogType_Fatal:
        LOG4CPLUS_FATAL_STR(GetLogger(), buf.str());
        break;
    }

    m_haserr |= (type > x3LogType_Info) ? 0x03 : 0x04;
}

#ifdef _MSC_VER     // hide warnings
#pragma warning(default:4127)
#pragma warning (pop)
#endif
