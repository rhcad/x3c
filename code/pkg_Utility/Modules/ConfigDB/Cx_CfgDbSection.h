// x3c - C++ PluginFramework
#ifndef _X3_CONFIGDB_CFGDBSECTION_H
#define _X3_CONFIGDB_CFGDBSECTION_H

#include <Xml/Ix_ConfigSection.h>
#include <Xml/Ix_ConfigTransaction.h>
#include "msado15.tlh"

class Cx_CfgDatabase;

const X3CLSID CLSID_NullObject("6c24d79d-ab0b-49f7-a9d5-cc76115aac6f");

class Cx_CfgDbSection
    : public Ix_ConfigSection
    , public Ix_ConfigTransaction
{
    X3BEGIN_CLASS_DECLARE(Cx_CfgDbSection)
        X3DEFINE_INTERFACE_ENTRY(Ix_ConfigSection)
        X3DEFINE_INTERFACE_ENTRY(Ix_ConfigTransaction)
    X3END_CLASS_DECLARE()
protected:
    Cx_CfgDbSection();
    virtual ~Cx_CfgDbSection();

public:
    void InitializeNullObject(Cx_CfgDatabase* pDB);

protected:
    Cx_CfgDatabase*     m_pDB;

private:
    // From Ix_ConfigTransaction
    //
    virtual void BeginTransaction();
    virtual bool EndTransaction();
    virtual ULONG GetModifiedCount();

    // From Ix_ConfigSection
    //
    virtual Ix_ConfigData* GetData() const;
    virtual bool IsValid() const;
    virtual std::wstring GetString(const wchar_t* pszEntry, const wchar_t* pszDefault = L"");
    virtual bool SetString(const wchar_t* pszEntry, const wchar_t* pszValue);
    virtual int GetInt(const wchar_t* pszEntry, int nDefault = 0);
    virtual bool SetInt(const wchar_t* pszEntry, int nValue);
    virtual long GetInt32(const wchar_t* pszEntry, long nDefault = 0);
    virtual bool SetInt32(const wchar_t* pszEntry, long nValue);
    virtual ULONG GetUInt32(const wchar_t* pszEntry, ULONG nDefault = 0);
    virtual bool SetUInt32(const wchar_t* pszEntry, ULONG nValue);
    virtual short GetInt16(const wchar_t* pszEntry, short nDefault = 0);
    virtual bool SetInt16(const wchar_t* pszEntry, short nValue);
    virtual WORD GetUInt16(const wchar_t* pszEntry, WORD nDefault = 0);
    virtual bool SetUInt16(const wchar_t* pszEntry, WORD nValue);
    virtual bool GetBool(const wchar_t* pszEntry, BOOL bDefault);
    virtual bool SetBool(const wchar_t* pszEntry, BOOL bValue);
    virtual double GetDouble(const wchar_t* pszEntry, double dDefault = 0);
    virtual bool SetDouble(const wchar_t* pszEntry, double dValue);
    virtual float GetFloat(const wchar_t* pszEntry, float fDefault = 0);
    virtual bool SetFloat(const wchar_t* pszEntry, float fValue);
    virtual DWORD GetRGB(const wchar_t* pszEntry, DWORD crDefault);
    virtual bool SetRGB(const wchar_t* pszEntry, DWORD crValue);
    virtual bool GetCMYK(const wchar_t* pszEntry, WORD& c, WORD& m, WORD& y, WORD& k);
    virtual bool SetCMYK(const wchar_t* pszEntry, WORD c, WORD m, WORD y, WORD k);
    virtual bool GetDate(const wchar_t* pszEntry, int& year, int& month, int& day);
    virtual bool SetDate(const wchar_t* pszEntry, int year, int month, int day);
    virtual bool GetDateTime(const wchar_t* pszEntry, int& year, int& month, int& day, 
        int& hour, int& minute, int& second);
    virtual bool SetDateTime(const wchar_t* pszEntry, int year, int month, int day, 
        int hour, int minute, int second);
    virtual long GetDoubleArray(const wchar_t* pszEntry, double* pItems, long nCount);
    virtual bool SetDoubleArray(const wchar_t* pszEntry, const double* pItems, long nCount);
    virtual long GetIntArray(const wchar_t* pszEntry, long* pItems, long nCount);
    virtual bool SetIntArray(const wchar_t* pszEntry, const long* pItems, long nCount);
    virtual long GetBinary(const wchar_t* pszEntry, void* pBuf, long nSize);
    virtual bool SetBinary(const wchar_t* pszEntry, LPCVOID pBuf, long nSize);
};

#endif // _X3_CONFIGDB_CFGDBSECTION_H
