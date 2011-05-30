// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include "Cx_CfgRecord.h"
#include "Cx_CfgDatabase.h"
#include "DbFunc.h"
#include <UtilFunc/RoundStr.h>
#include <UtilFunc/ReadInts.h>

Cx_CfgRecord::Cx_CfgRecord()
    : m_bAdd(false), m_lTransaction(0), m_nKeyNewID(0)
{
}

Cx_CfgRecord::~Cx_CfgRecord()
{
    SubmitRecord();
}

void Cx_CfgRecord::InitializeForAdd(Cx_CfgDatabase* pDB, const std::wstring& wstrTable)
{
    ASSERT(NULL == m_pDB && pDB != NULL);
    ASSERT(DbFunc::IsDBName(wstrTable.c_str()));

    m_pDB = pDB;
    m_wstrSQL = wstrTable;
    m_bAdd = true;
}

void Cx_CfgRecord::InitializeForRead(Cx_CfgDatabase* pDB, _RecordsetPtr pRs, 
                                     const std::wstring& wstrSQL)
{
    ASSERT(NULL == m_pDB && pDB != NULL && pRs != NULL);
    ASSERT(StrStrIW(wstrSQL.c_str(), L"SELECT ") == wstrSQL.c_str());

    m_pDB = pDB;
    m_pRs = pRs;
    m_wstrSQL = wstrSQL;
    m_bAdd = false;
}

bool Cx_CfgRecord::IsValid() const
{
    return m_pDB && (!m_wstrSQL.empty() || m_pRs != NULL);
}

void Cx_CfgRecord::BeginTransaction()
{
    ++m_lTransaction;
}

bool Cx_CfgRecord::EndTransaction()
{
    bool bRet = true;

    if (--m_lTransaction == 0)
    {
        bRet = SubmitRecord() > 0;
    }

    return bRet;
}

ULONG Cx_CfgRecord::GetModifiedCount()
{
    return static_cast<ULONG>(m_arrValue.size());
}

static std::wstring GetSQLFunc(const wchar_t* pszFunc, Ix_SQLParser* pParser)
{
    if (_wcsicmp(pszFunc, L"CURDATE()") == 0)
        return pParser->GetFunc_CURDATE();

    if (_wcsicmp(pszFunc, L"CURTIME()") == 0)
        return pParser->GetFunc_CURTIME();

    if (_wcsicmp(pszFunc, L"NOW()") == 0)
        return pParser->GetFunc_NOW();

    return pszFunc;
}

long Cx_CfgRecord::SubmitRecord()
{
    if (m_arrValue.empty())
        return 0;

    std::vector<FieldValue> arrValue(m_arrValue);
    std::wostringstream sql, ssField, ssValues;

    m_arrValue.clear();

    if (m_bAdd)
    {
        ASSERT(DbFunc::IsDBName(m_wstrSQL.c_str()));

        sql << L"INSERT INTO " << m_wstrSQL << L" (";
        ssValues << L") VALUES (";
    }
    else
    {
        ASSERT(StrStrIW(m_wstrSQL.c_str(), L"SELECT ") == m_wstrSQL.c_str());

        const wchar_t* pszFrom = StrStrIW(m_wstrSQL.c_str(), L"FROM ");
        ASSERT_MESSAGE(pszFrom != NULL, "The SQL command must contains 'FROM' keyword.");

        std::wstring table(DbFunc::GetLevel1Name(pszFrom + 5));
        sql << L"UPDATE " << table;
        ssValues << L" SET ";
    }

    std::vector<FieldValue>::iterator it = arrValue.begin();
    for (long i = 0; it != arrValue.end(); ++it, ++i)
    {
        std::wstring wstrField(it->first);
        std::wstring wstrValue(it->second);
        ASSERT(!wstrValue.empty());

        if (StrCmpW(L"@NEWID", wstrValue.c_str()) == 0)
        {
            ASSERT(m_bAdd);

            m_wstrKeyField = wstrField;
            m_nKeyNewID = 0;
            if (!m_pDB->GetRecordNewID(m_nKeyNewID, m_wstrSQL, wstrField))
            {
                return 0;
            }

            wchar_t szNum[35];
            _ltow_s(m_nKeyNewID, szNum, _countof(szNum), 10);
            wstrValue = szNum;
        }
        else if (L'@' == wstrValue[0])
        {
            wstrValue = GetSQLFunc(wstrValue.c_str() + 1, m_pDB->GetSQLParser());
        }

        if (i > 0)
        {
            ssField << L",";
            ssValues << L",";
        }
        if (m_bAdd)
        {
            ssField << wstrField;
            ssValues << wstrValue;
        }
        else
        {
            ssValues << wstrField << L"=" << wstrValue;
        }
    }

    if (m_bAdd)
    {
        sql << ssField.str() << ssValues.str() << L") ";
    }
    else
    {
        sql << ssValues.str();

        const wchar_t* pszWhere = StrStrIW(m_wstrSQL.c_str(), L" WHERE");
        if (pszWhere != NULL)
        {
            sql << pszWhere;
        }
    }

    bool bRet = false;
    long nAffected = 0;

    try
    {
        bRet = (m_pDB->ExecuteSQL(sql.str().c_str(), __FILE__, __LINE__) != NULL);
        nAffected = m_pDB->GetRecordsAffected();
    }
    CATCH_DB_STR_ERROR;

    return nAffected;
}

bool Cx_CfgRecord::HasFieldValue(const std::wstring& wstrField) const
{
    std::vector<FieldValue>::const_iterator it = m_arrValue.begin();
    for (; it != m_arrValue.end(); ++it)
    {
        if (_wcsicmp(it->first.c_str(), wstrField.c_str()) == 0)
        {
            return true;
        }
    }

    return false;
}

bool Cx_CfgRecord::AddFieldValue(const std::wstring& wstrField, 
                                 const std::wstring& wstrValue)
{
    ASSERT(IsValid() && !wstrValue.empty());
    ASSERT_MESSAGE(DbFunc::IsDBName(wstrField.c_str()), "Invalid field name.");
    ASSERT_MESSAGE(!HasFieldValue(wstrField), "The field has already set value.");

    m_arrValue.push_back(FieldValue(wstrField, wstrValue));

    return true;
}

std::wstring Cx_CfgRecord::GetString(const wchar_t* pszEntry, const wchar_t* pszDefault)
{
    ASSERT_MESSAGE(m_pRs != NULL, "The record is write-only.");

    if (m_pRs != NULL)
    {
        try
        {
            _variant_t var(m_pRs->GetFields()->GetItem(pszEntry)->GetValue());
            return towstr(DbFunc::GetBSTR(var, pszDefault));
        }
        CATCH_DB_STR_ERROR
    }

    return pszDefault;
}

bool Cx_CfgRecord::SetString(const wchar_t* pszEntry, const wchar_t* pszValue)
{
    std::wstring wstrValue;

    if (pszValue[0] != L'@')
    {
        wstrValue += L"'";
        wstrValue += pszValue;
        wstrValue += L"'";
    }
    else
    {
        wstrValue += pszValue;
    }

    return AddFieldValue(pszEntry, wstrValue);
}

int Cx_CfgRecord::GetInt(const wchar_t* pszEntry, int nDefault)
{
    if (_wcsicmp(m_wstrKeyField.c_str(), pszEntry) == 0)
    {
        ASSERT(NULL == m_pRs);
        return m_nKeyNewID;
    }

    ASSERT_MESSAGE(m_pRs != NULL, "The record is write-only.");
    if (m_pRs != NULL)
    {
        try
        {
            _variant_t var(m_pRs->GetFields()->GetItem(pszEntry)->GetValue());
            return DbFunc::GetLong(var, nDefault);
        }
        CATCH_DB_STR_ERROR
    }

    return nDefault;
}

bool Cx_CfgRecord::SetInt(const wchar_t* pszEntry, int nValue)
{
    wchar_t szNum[35];
    _itow_s(nValue, szNum, _countof(szNum), 10);
    return AddFieldValue(pszEntry, szNum);
}

long Cx_CfgRecord::GetInt32(const wchar_t* pszEntry, long nDefault)
{
    return GetInt(pszEntry, nDefault);
}

bool Cx_CfgRecord::SetInt32(const wchar_t* pszEntry, long nValue)
{
    wchar_t szNum[35];
    _ltow_s(nValue, szNum, _countof(szNum), 10);
    return AddFieldValue(pszEntry, szNum);
}

ULONG Cx_CfgRecord::GetUInt32(const wchar_t* pszEntry, ULONG nDefault)
{
    return GetInt(pszEntry, nDefault);
}

bool Cx_CfgRecord::SetUInt32(const wchar_t* pszEntry, ULONG nValue)
{
    wchar_t szNum[35];
    _ultow_s(nValue, szNum, _countof(szNum), 10);
    return AddFieldValue(pszEntry, szNum);
}

short Cx_CfgRecord::GetInt16(const wchar_t* pszEntry, short nDefault)
{
    return (short)GetInt(pszEntry, nDefault);
}

bool Cx_CfgRecord::SetInt16(const wchar_t* pszEntry, short nValue)
{
    wchar_t szNum[35];
    _itow_s(nValue, szNum, _countof(szNum), 10);
    return AddFieldValue(pszEntry, szNum);
}

WORD Cx_CfgRecord::GetUInt16(const wchar_t* pszEntry, WORD nDefault)
{
    return (WORD)GetInt(pszEntry, nDefault);
}

bool Cx_CfgRecord::SetUInt16(const wchar_t* pszEntry, WORD nValue)
{
    wchar_t szNum[35];
    _ultow_s(nValue, szNum, _countof(szNum), 10);
    return AddFieldValue(pszEntry, szNum);
}

bool Cx_CfgRecord::GetBool(const wchar_t* pszEntry, BOOL bDefault)
{
    ASSERT_MESSAGE(m_pRs != NULL, "The record is write-only.");

    if (m_pRs != NULL)
    {
        try
        {
            _variant_t var(m_pRs->GetFields()->GetItem(pszEntry)->GetValue());
            return !!DbFunc::GetBool(var, bDefault);
        }
        CATCH_DB_STR_ERROR
    }

    return !!bDefault;
}

bool Cx_CfgRecord::SetBool(const wchar_t* pszEntry, BOOL bValue)
{
    return AddFieldValue(pszEntry, bValue ? L"'y'" : L"'n'");
}

double Cx_CfgRecord::GetDouble(const wchar_t* pszEntry, double dDefault)
{
    ASSERT_MESSAGE(m_pRs != NULL, "The record is write-only.");

    if (m_pRs != NULL)
    {
        try
        {
            _variant_t var(m_pRs->GetFields()->GetItem(pszEntry)->GetValue());
            return DbFunc::GetDouble(var, dDefault);
        }
        CATCH_DB_STR_ERROR
    }

    return dDefault;
}

bool Cx_CfgRecord::SetDouble(const wchar_t* pszEntry, double dValue)
{
    return AddFieldValue(pszEntry, RoundStr(dValue, 5).c_str());
}

float Cx_CfgRecord::GetFloat(const wchar_t* pszEntry, float fDefault)
{
    return (float)GetDouble(pszEntry, fDefault);
}

bool Cx_CfgRecord::SetFloat(const wchar_t* pszEntry, float fValue)
{
    return AddFieldValue(pszEntry, RoundStr(fValue, 5).c_str());
}

DWORD Cx_CfgRecord::GetRGB(const wchar_t* pszEntry, DWORD crDefault)
{
    return GetUInt32(pszEntry, crDefault);
}

bool Cx_CfgRecord::SetRGB(const wchar_t* pszEntry, DWORD crValue)
{
    return SetUInt32(pszEntry, crValue);
}

bool Cx_CfgRecord::GetCMYK(const wchar_t* pszEntry, WORD& c, WORD& m, WORD& y, WORD& k)
{
    WORD nums[4] = { 0, 0, 0, 0 };
    bool bRet = (ReadInts(GetString(pszEntry).c_str(), nums, 4) == 4);
    if (bRet)
    {
        c = nums[0];
        m = nums[1];
        y = nums[2];
        k = nums[3];
    }
    return bRet;
}

bool Cx_CfgRecord::SetCMYK(const wchar_t* pszEntry, WORD c, WORD m, WORD y, WORD k)
{
    wchar_t szBuf[60];
    swprintf_s(szBuf, _countof(szBuf), L"'%d-%d-%d-%d'", c, m, y, k);
    return AddFieldValue(pszEntry, szBuf);
}

bool Cx_CfgRecord::GetDate(const wchar_t* pszEntry, int& year, int& month, int& day)
{
    ASSERT_MESSAGE(m_pRs != NULL, "The record is write-only.");

    if (m_pRs != NULL)
    {
        try
        {
            _variant_t var(m_pRs->GetFields()->GetItem(pszEntry)->GetValue());
            COleDateTime dt;

            if (DbFunc::GetDate(dt, var))
            {
                year = dt.GetYear();
                month = dt.GetMonth();
                day = dt.GetDay();

                return true;
            }
        }
        CATCH_DB_STR_ERROR
    }

    return false;
}

bool Cx_CfgRecord::SetDate(const wchar_t* pszEntry, int year, int month, int day)
{
    wchar_t szBuf[60];
    swprintf_s(szBuf, _countof(szBuf), L"'%d-%d-%d'", year, month, day);
    return AddFieldValue(pszEntry, szBuf);
}

bool Cx_CfgRecord::GetDateTime(const wchar_t* pszEntry, int& year, int& month, int& day, 
                                  int& hour, int& minute, int& second)
{
    ASSERT_MESSAGE(m_pRs != NULL, "The record is write-only.");

    if (m_pRs != NULL)
    {
        try
        {
            _variant_t var(m_pRs->GetFields()->GetItem(pszEntry)->GetValue());
            COleDateTime dt;

            if (DbFunc::GetDateTime(dt, var))
            {
                year = dt.GetYear();
                month = dt.GetMonth();
                day = dt.GetDay();
                hour = dt.GetHour();
                minute = dt.GetMinute();
                second = dt.GetSecond();

                return true;
            }
        }
        CATCH_DB_STR_ERROR
    }

    return false;
}

bool Cx_CfgRecord::SetDateTime(const wchar_t* pszEntry, int year, int month, int day, 
                               int hour, int minute, int second)
{
    wchar_t szBuf[60];
    swprintf_s(szBuf, _countof(szBuf), L"'%d-%d-%d %d:%d:%d'", 
        year, month, day, hour, minute, second);
    return AddFieldValue(pszEntry, szBuf);
}

long Cx_CfgRecord::GetDoubleArray(const wchar_t* pszEntry, double* pItems, long count)
{
    pszEntry;pItems;count;
    ASSERT_MESSAGE(0, "TODO: GetDoubleArray 还未实现");
    return false;
}

bool Cx_CfgRecord::SetDoubleArray(const wchar_t* pszEntry, const double* pItems, long count)
{
    pszEntry;pItems;count;
    ASSERT_MESSAGE(0, "TODO: SetDoubleArray 还未实现");
    return false;
}

long Cx_CfgRecord::GetIntArray(const wchar_t* pszEntry, long* pItems, long count)
{
    pszEntry;pItems;count;
    ASSERT_MESSAGE(0, "TODO: GetIntArray 还未实现");
    return false;
}

bool Cx_CfgRecord::SetIntArray(const wchar_t* pszEntry, const long* pItems, long count)
{
    pszEntry;pItems;count;
    ASSERT_MESSAGE(0, "TODO: SetIntArray 还未实现");
    return false;
}

long Cx_CfgRecord::GetBinary(const wchar_t* pszEntry, void* pBuf, long nSize)
{
    pszEntry;pBuf;nSize;
    ASSERT_MESSAGE(0, "TODO: GetBinary 还未实现");
    return false;
}

bool Cx_CfgRecord::SetBinary(const wchar_t* pszEntry, LPCVOID pBuf, long nSize)
{
    pszEntry;pBuf;nSize;
    ASSERT_MESSAGE(0, "TODO: SetBinary 还未实现");
    return false;
}
