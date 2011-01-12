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

#ifndef _X3_CONFIGDB_CFGDBSECTION_H
#define _X3_CONFIGDB_CFGDBSECTION_H

#include <Ix_ConfigSection.h>
#include <Ix_ConfigTransaction.h>

class Cx_CfgDatabase;

class Cx_CfgDbSection
    : public Ix_ConfigSection
    , public Ix_ConfigTransaction
{
public:
    Cx_CfgDbSection();
    virtual ~Cx_CfgDbSection();

    void InitializeNullObject(Cx_CfgDatabase* pDB);

protected:
    Cx_CfgDatabase*     m_pDB;

protected:
    // From Ix_ConfigTransaction
    //
    virtual void BeginTransaction();
    virtual bool EndTransaction();
    virtual ULONG GetModifiedCount();

    // From Ix_ConfigSection
    //
    virtual Ix_ConfigData* GetData() const;
    virtual bool IsValid() const;
    virtual std::wstring GetString(LPCWSTR pszEntry, LPCWSTR pszDefault = L"");
    virtual bool SetString(LPCWSTR pszEntry, LPCWSTR pszValue);
    virtual int GetInt(LPCWSTR pszEntry, int nDefault = 0);
    virtual bool SetInt(LPCWSTR pszEntry, int nValue);
    virtual long GetInt32(LPCWSTR pszEntry, long nDefault = 0);
    virtual bool SetInt32(LPCWSTR pszEntry, long nValue);
    virtual ULONG GetUInt32(LPCWSTR pszEntry, ULONG nDefault = 0);
    virtual bool SetUInt32(LPCWSTR pszEntry, ULONG nValue);
    virtual short GetInt16(LPCWSTR pszEntry, short nDefault = 0);
    virtual bool SetInt16(LPCWSTR pszEntry, short nValue);
    virtual WORD GetUInt16(LPCWSTR pszEntry, WORD nDefault = 0);
    virtual bool SetUInt16(LPCWSTR pszEntry, WORD nValue);
    virtual bool GetBool(LPCWSTR pszEntry, BOOL bDefault);
    virtual bool SetBool(LPCWSTR pszEntry, BOOL bValue);
    virtual double GetDouble(LPCWSTR pszEntry, double dDefault = 0);
    virtual bool SetDouble(LPCWSTR pszEntry, double dValue);
    virtual float GetFloat(LPCWSTR pszEntry, float fDefault = 0);
    virtual bool SetFloat(LPCWSTR pszEntry, float fValue);
    virtual COLORREF GetRGB(LPCWSTR pszEntry, COLORREF crDefault);
    virtual bool SetRGB(LPCWSTR pszEntry, COLORREF crValue);
    virtual bool GetCMYK(LPCWSTR pszEntry, WORD& c, WORD& m, WORD& y, WORD& k);
    virtual bool SetCMYK(LPCWSTR pszEntry, WORD c, WORD m, WORD y, WORD k);
    virtual bool GetDate(LPCWSTR pszEntry, int& year, int& month, int& day);
    virtual bool SetDate(LPCWSTR pszEntry, int year, int month, int day);
    virtual bool GetDateTime(LPCWSTR pszEntry, int& year, int& month, int& day, 
        int& hour, int& minute, int& second);
    virtual bool SetDateTime(LPCWSTR pszEntry, int year, int month, int day, 
        int hour, int minute, int second);
    virtual long GetDoubleArray(LPCWSTR pszEntry, double* pItems, long nCount);
    virtual bool SetDoubleArray(LPCWSTR pszEntry, const double* pItems, long nCount);
    virtual long GetIntArray(LPCWSTR pszEntry, long* pItems, long nCount);
    virtual bool SetIntArray(LPCWSTR pszEntry, const long* pItems, long nCount);
    virtual long GetBinary(LPCWSTR pszEntry, LPVOID pBuf, long nSize);
    virtual bool SetBinary(LPCWSTR pszEntry, LPCVOID pBuf, long nSize);
};

#endif // _X3_CONFIGDB_CFGDBSECTION_H
