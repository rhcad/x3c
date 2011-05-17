// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef _X3_CORE_LOGMANAGER_H
#define _X3_CORE_LOGMANAGER_H

#include <Ix_LogManager.h>

class Cx_LogManager
    : public Ix_LogManager
{
protected:
    Cx_LogManager();
    virtual ~Cx_LogManager();

protected:
    virtual bool RegisterObserver(ILogObserver* observer);
    virtual void UnRegisterObserver(ILogObserver* observer);
    virtual bool PushGroup(const wchar_t* msg, const wchar_t* extra);
    virtual bool PopGroup();
    virtual bool WriteLog(kLogType type, const wchar_t* msg, 
        const wchar_t* extra, const char* file, long line);
    virtual bool WriteLog(kLogType type, const char* msg, 
        const char* extra, const char* file, long line);
    virtual int CrtDbgReport(const char* msg, const char* file, long line);

private:
    const char* TrimFileName(const char* file);
    bool CheckMsgParam(std::wstring& msg2, std::wstring& extra2, 
        std::wstring& module, std::wstring& idname, 
        const wchar_t* msg, const wchar_t* extra);

private:
    typedef std::vector<ILogObserver*>::iterator ObserverIt;
    std::vector<ILogObserver*>      m_observers;
    long                            m_groupLevel;
    long                            m_loglock;
};

#endif // _X3_CORE_LOGMANAGER_H
