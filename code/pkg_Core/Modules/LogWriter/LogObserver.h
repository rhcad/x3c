// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef _X3_LOGWRITER_LOGOBSERVER_H
#define _X3_LOGWRITER_LOGOBSERVER_H

#include <Log/ILogObserver.h>

#include <log4cplus/logger.h>
using namespace log4cplus;

class CLogObserver : public CLogObserverImpl
{
public:
    CLogObserver();
    virtual ~CLogObserver();

protected:
    virtual void OnPushGroup(long level, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname);
    virtual void OnPopGroup(long level);
    virtual void OnWriteLog(int type, 
        const std::wstring& msg, const std::wstring& extra, 
        const std::wstring& module, const std::wstring& idname, 
        const std::wstring& file, long line);

private:
    Logger GetLogger();
    void InitLogFile();
    void MakerInitVars();
    void WritePropFile(const wchar_t* filename);
    bool GetServerPath(wchar_t* path);
    bool CopyLogFilesToServer();

private:
    std::wstring    m_path;         // logging path ending with backsplash.
    std::wstring    m_appname;      // application name for logging.
    bool            m_inited;       // logging file is setted or not.
    long            m_level;        // group level of current group.
    int             m_haserr;       // see OnWriteLog
    long            m_copyflags;    // flags for CopyLogFilesToServer
};

#endif // _X3_LOGWRITER_LOGOBSERVER_H
