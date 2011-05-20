// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <PluginInc.h>
#include "Cx_CfgRecordset.h"
#include "Cx_CfgDatabase.h"
#include "DbFunc.h"

Cx_CfgRecordset::Cx_CfgRecordset()
    : m_bNeedExecuteSQL(true), m_lRecIndex(0), m_lRecordCount(-1)
{
}

Cx_CfgRecordset::~Cx_CfgRecordset()
{
}

void Cx_CfgRecordset::InitializeBySQL(Cx_CfgDatabase* pDB, 
                                      const std::wstring& wstrSQL)
{
    ASSERT(NULL == m_pDB && pDB != NULL);

    m_pDB = pDB;
    m_wstrSQL = wstrSQL;
}

std::wstring Cx_CfgRecordset::GetTableName() const
{
    const wchar_t* pszFrom = StrStrIW(m_wstrSQL.c_str(), L"FROM ");
    if (pszFrom != NULL)
    {
        return DbFunc::GetLevel1Name(pszFrom + 5);
    }

    return L"";
}

std::wstring Cx_CfgRecordset::GetSQLCommand() const
{
    return m_wstrSQL;
}

long Cx_CfgRecordset::GetCurIndex() const
{
    return m_lRecIndex;
}

_RecordsetPtr Cx_CfgRecordset::GetCurRecord()
{
    if (m_bNeedExecuteSQL && IsValid())
    {
        m_bNeedExecuteSQL = false;

        try
        {
            m_pRs = m_pDB->ExecuteSQL(m_wstrSQL.c_str(), __FILE__, __LINE__);
            m_lRecIndex = 0;
        }
        CATCH_DB_STR_ERROR;
    }

    return m_pRs;
}

long Cx_CfgRecordset::GetRecordCount()
{
    if (m_lRecordCount < 0)
    {
        m_pDB->GetRecordCount(m_lRecordCount, m_wstrSQL.c_str());
    }

    return m_lRecordCount;
}

bool Cx_CfgRecordset::SetCurIndex(long nIndex)
{
    ASSERT(nIndex >= 0);

    _RecordsetPtr pRs = GetCurRecord();
    if (NULL == pRs)
    {
        return false;
    }

    try
    {
        if (nIndex == m_lRecIndex + 1)
        {
            pRs->MoveNext();
        }
        else if (nIndex < m_lRecIndex && 0 == nIndex)
        {
            pRs->MoveFirst();
        }
        else if (nIndex != m_lRecIndex)
        {
            return false;
        }

        m_lRecIndex = nIndex;
        return true;
    }
    CATCH_DB_STR_ERROR;

    return false;
}

bool Cx_CfgRecordset::IsValid() const
{
    return m_pDB && !m_wstrSQL.empty();
}

std::wstring Cx_CfgRecordset::GetString(const wchar_t*, const wchar_t*)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return L"";
}

bool Cx_CfgRecordset::SetString(const wchar_t*, const wchar_t*)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

int Cx_CfgRecordset::GetInt(const wchar_t*, int)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetInt(const wchar_t*, int)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

long Cx_CfgRecordset::GetInt32(const wchar_t*, long)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetInt32(const wchar_t*, long)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

ULONG Cx_CfgRecordset::GetUInt32(const wchar_t*, ULONG)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetUInt32(const wchar_t*, ULONG)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

short Cx_CfgRecordset::GetInt16(const wchar_t*, short)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetInt16(const wchar_t*, short)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

WORD Cx_CfgRecordset::GetUInt16(const wchar_t*, WORD)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetUInt16(const wchar_t*, WORD)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::GetBool(const wchar_t*, BOOL)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetBool(const wchar_t*, BOOL)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

double Cx_CfgRecordset::GetDouble(const wchar_t*, double)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetDouble(const wchar_t*, double)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

float Cx_CfgRecordset::GetFloat(const wchar_t*, float)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetFloat(const wchar_t*, float)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

DWORD Cx_CfgRecordset::GetRGB(const wchar_t*, DWORD)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return 0;
}

bool Cx_CfgRecordset::SetRGB(const wchar_t*, DWORD)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::GetCMYK(const wchar_t*, WORD&, WORD&, WORD&, WORD&)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetCMYK(const wchar_t*, WORD, WORD, WORD, WORD)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::GetDate(const wchar_t*, int&, int&, int&)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetDate(const wchar_t*, int, int, int)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::GetDateTime(const wchar_t*, int&, int&, int&, int&, int&, int&)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

bool Cx_CfgRecordset::SetDateTime(const wchar_t*, int, int, int, int, int, int)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

long Cx_CfgRecordset::GetDoubleArray(const wchar_t*, double*, long)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return 0;
}

bool Cx_CfgRecordset::SetDoubleArray(const wchar_t*, const double*, long)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

long Cx_CfgRecordset::GetIntArray(const wchar_t*, long*, long)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return 0;
}

bool Cx_CfgRecordset::SetIntArray(const wchar_t*, const long*, long)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}

long Cx_CfgRecordset::GetBinary(const wchar_t*, void*, long)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return 0;
}

bool Cx_CfgRecordset::SetBinary(const wchar_t*, LPCVOID, long)
{
    ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
    return false;
}
