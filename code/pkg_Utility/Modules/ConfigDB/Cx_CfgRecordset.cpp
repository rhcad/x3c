// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
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

#include "StdAfx.h"
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
	LPCWSTR pszFrom = StrStrIW(m_wstrSQL.c_str(), L"FROM ");
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

std::wstring Cx_CfgRecordset::GetString(LPCWSTR, LPCWSTR)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return L"";
}

bool Cx_CfgRecordset::SetString(LPCWSTR, LPCWSTR)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

int Cx_CfgRecordset::GetInt(LPCWSTR, int)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetInt(LPCWSTR, int)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

long Cx_CfgRecordset::GetInt32(LPCWSTR, long)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetInt32(LPCWSTR, long)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

ULONG Cx_CfgRecordset::GetUInt32(LPCWSTR, ULONG)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetUInt32(LPCWSTR, ULONG)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

short Cx_CfgRecordset::GetInt16(LPCWSTR, short)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetInt16(LPCWSTR, short)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

WORD Cx_CfgRecordset::GetUInt16(LPCWSTR, WORD)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetUInt16(LPCWSTR, WORD)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::GetBool(LPCWSTR, BOOL)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetBool(LPCWSTR, BOOL)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

double Cx_CfgRecordset::GetDouble(LPCWSTR, double)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetDouble(LPCWSTR, double)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

float Cx_CfgRecordset::GetFloat(LPCWSTR, float)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetFloat(LPCWSTR, float)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

COLORREF Cx_CfgRecordset::GetRGB(LPCWSTR, COLORREF)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return 0;
}

bool Cx_CfgRecordset::SetRGB(LPCWSTR, COLORREF)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::GetCMYK(LPCWSTR, WORD&, WORD&, WORD&, WORD&)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetCMYK(LPCWSTR, WORD, WORD, WORD, WORD)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::GetDate(LPCWSTR, int&, int&, int&)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetDate(LPCWSTR, int, int, int)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::GetDateTime(LPCWSTR, int&, int&, int&, int&, int&, int&)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

bool Cx_CfgRecordset::SetDateTime(LPCWSTR, int, int, int, int, int, int)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

long Cx_CfgRecordset::GetDoubleArray(LPCWSTR, double*, long)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return 0;
}

bool Cx_CfgRecordset::SetDoubleArray(LPCWSTR, const double*, long)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

long Cx_CfgRecordset::GetIntArray(LPCWSTR, long*, long)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return 0;
}

bool Cx_CfgRecordset::SetIntArray(LPCWSTR, const long*, long)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}

long Cx_CfgRecordset::GetBinary(LPCWSTR, LPVOID, long)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return 0;
}

bool Cx_CfgRecordset::SetBinary(LPCWSTR, LPCVOID, long)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Recordset::GetXXX/SetXXX]");
	return false;
}
