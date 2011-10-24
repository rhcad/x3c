// x3c - C++ PluginFramework
#ifndef _X3_CORE_LOGMANAGER_H
#define _X3_CORE_LOGMANAGER_H

#include <Log/Ix_LogManager.h>

class Cx_LogManager
    : public Ix_LogManager
{
    X3BEGIN_CLASS_DECLARE(Cx_LogManager)
        X3DEFINE_INTERFACE_ENTRY(Ix_LogManager)
    X3END_CLASS_DECLARE()
protected:
    Cx_LogManager();
    virtual ~Cx_LogManager();

private:
    virtual bool RegisterObserver(Ix_LogObserver* observer, HMODULE fromdll);
    virtual void UnRegisterObserver(Ix_LogObserver* observer);
    virtual bool PushGroup(const wchar_t* msg, const wchar_t* extra);
    virtual bool PopGroup();
    virtual bool WriteLog(x3LogType type, const wchar_t* msg, 
        const wchar_t* extra, const char* file, long line);
    virtual bool WriteLog(x3LogType type, const char* msg, 
        const char* extra, const char* file, long line);
    virtual int CrtDbgReport(const char* msg, const char* file, long line);

private:
    const char* TrimFileName(const char* file);
    bool CheckMsgParam(std::wstring& msg2, std::wstring& extra2, 
        std::wstring& module, std::wstring& idname, 
        const wchar_t* msg, const wchar_t* extra);
    void FireFirstEvent();

private:
    typedef std::pair<Ix_LogObserver*, HMODULE> ITEM;
    typedef std::vector<ITEM>::iterator ObserverIt;
    std::vector<ITEM>               m_observers;
    long                            m_groupLevel;
    long                            m_loglock;
};

#endif // _X3_CORE_LOGMANAGER_H
