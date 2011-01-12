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
    virtual bool PushGroup(const wchar_t* pszMsg, const wchar_t* pszExtra);
    virtual bool PopGroup();
    virtual bool WriteLog(kLogType nType, const wchar_t* pszMsg, 
        const wchar_t* pszExtra, LPCSTR pszFile, long nLine);
    virtual bool WriteLog(kLogType nType, LPCSTR pszMsg, 
        LPCSTR pszExtra, LPCSTR pszFile, long nLine);
    virtual int CrtDbgReport(LPCSTR szMsg, LPCSTR szFile, long nLine);

private:
    LPCSTR TrimFileName(LPCSTR pszFile);
    bool CheckMsgParam(std::wstring& wstrMsg, std::wstring& wstrExtra, 
        std::wstring& wstrModule, std::wstring& wstrID, 
        const wchar_t* pszMsg, const wchar_t* pszExtra);

private:
    typedef std::vector<ILogObserver*>::iterator ObserverIt;
    std::vector<ILogObserver*>      m_arrObserver;
    long                            m_nGroupLevel;
};

#endif // _X3_CORE_LOGMANAGER_H
