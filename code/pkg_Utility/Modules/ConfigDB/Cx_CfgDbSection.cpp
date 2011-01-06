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
#include "Cx_CfgDbSection.h"
#include "Cx_CfgDatabase.h"

Cx_CfgDbSection::Cx_CfgDbSection()
	: m_pDB(NULL)
{
}

Cx_CfgDbSection::~Cx_CfgDbSection()
{
}

void Cx_CfgDbSection::InitializeNullObject(Cx_CfgDatabase* pDB)
{
	ASSERT(NULL == m_pDB && pDB != NULL);

	m_pDB = pDB;
}

Ix_ConfigData* Cx_CfgDbSection::GetData() const
{
	return m_pDB;
}

bool Cx_CfgDbSection::IsValid() const
{
	return false;
}

void Cx_CfgDbSection::BeginTransaction()
{
}

bool Cx_CfgDbSection::EndTransaction()
{
	return false;
}

ULONG Cx_CfgDbSection::GetModifiedCount()
{
	return 0;
}

std::wstring Cx_CfgDbSection::GetString(LPCWSTR, LPCWSTR pszDefault)
{
	return pszDefault;
}

bool Cx_CfgDbSection::SetString(LPCWSTR, LPCWSTR)
{
	return false;
}

int Cx_CfgDbSection::GetInt(LPCWSTR, int nDefault)
{
	return nDefault;
}

bool Cx_CfgDbSection::SetInt(LPCWSTR, int)
{
	return false;
}

long Cx_CfgDbSection::GetInt32(LPCWSTR, long nDefault)
{
	return nDefault;
}

bool Cx_CfgDbSection::SetInt32(LPCWSTR, long)
{
	return false;
}

ULONG Cx_CfgDbSection::GetUInt32(LPCWSTR, ULONG nDefault)
{
	return nDefault;
}

bool Cx_CfgDbSection::SetUInt32(LPCWSTR, ULONG)
{
	return false;
}

short Cx_CfgDbSection::GetInt16(LPCWSTR, short nDefault)
{
	return nDefault;
}

bool Cx_CfgDbSection::SetInt16(LPCWSTR, short)
{
	return false;
}

WORD Cx_CfgDbSection::GetUInt16(LPCWSTR, WORD nDefault)
{
	return nDefault;
}

bool Cx_CfgDbSection::SetUInt16(LPCWSTR, WORD)
{
	return false;
}

bool Cx_CfgDbSection::GetBool(LPCWSTR, BOOL bDefault)
{
	return !!bDefault;
}

bool Cx_CfgDbSection::SetBool(LPCWSTR, BOOL)
{
	return false;
}

double Cx_CfgDbSection::GetDouble(LPCWSTR, double dDefault)
{
	return dDefault;
}

bool Cx_CfgDbSection::SetDouble(LPCWSTR, double)
{
	return false;
}

float Cx_CfgDbSection::GetFloat(LPCWSTR, float fDefault)
{
	return fDefault;
}

bool Cx_CfgDbSection::SetFloat(LPCWSTR, float)
{
	return false;
}

COLORREF Cx_CfgDbSection::GetRGB(LPCWSTR, COLORREF crDefault)
{
	return crDefault;
}

bool Cx_CfgDbSection::SetRGB(LPCWSTR, COLORREF)
{
	return false;
}

bool Cx_CfgDbSection::GetCMYK(LPCWSTR, WORD&, WORD&, WORD&, WORD&)
{
	return false;
}

bool Cx_CfgDbSection::SetCMYK(LPCWSTR, WORD, WORD, WORD, WORD)
{
	return false;
}

bool Cx_CfgDbSection::GetDate(LPCWSTR, int&, int&, int&)
{
	return false;
}

bool Cx_CfgDbSection::SetDate(LPCWSTR, int, int, int)
{
	return false;
}

bool Cx_CfgDbSection::GetDateTime(LPCWSTR, int&, int&, int&, int&, int&, int&)
{
	return false;
}

bool Cx_CfgDbSection::SetDateTime(LPCWSTR, int, int, int, int, int, int)
{
	return false;
}

long Cx_CfgDbSection::GetDoubleArray(LPCWSTR, double*, long)
{
	return 0;
}

bool Cx_CfgDbSection::SetDoubleArray(LPCWSTR, const double*, long)
{
	return false;
}

long Cx_CfgDbSection::GetIntArray(LPCWSTR, long*, long)
{
	return 0;
}

bool Cx_CfgDbSection::SetIntArray(LPCWSTR, const long*, long)
{
	return false;
}

long Cx_CfgDbSection::GetBinary(LPCWSTR, LPVOID, long)
{
	return 0;
}

bool Cx_CfgDbSection::SetBinary(LPCWSTR, LPCVOID, long)
{
	return false;
}
