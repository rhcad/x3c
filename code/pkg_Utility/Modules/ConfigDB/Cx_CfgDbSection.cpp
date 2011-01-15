// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

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

std::wstring Cx_CfgDbSection::GetString(const wchar_t*, const wchar_t* pszDefault)
{
    return pszDefault;
}

bool Cx_CfgDbSection::SetString(const wchar_t*, const wchar_t*)
{
    return false;
}

int Cx_CfgDbSection::GetInt(const wchar_t*, int nDefault)
{
    return nDefault;
}

bool Cx_CfgDbSection::SetInt(const wchar_t*, int)
{
    return false;
}

long Cx_CfgDbSection::GetInt32(const wchar_t*, long nDefault)
{
    return nDefault;
}

bool Cx_CfgDbSection::SetInt32(const wchar_t*, long)
{
    return false;
}

ULONG Cx_CfgDbSection::GetUInt32(const wchar_t*, ULONG nDefault)
{
    return nDefault;
}

bool Cx_CfgDbSection::SetUInt32(const wchar_t*, ULONG)
{
    return false;
}

short Cx_CfgDbSection::GetInt16(const wchar_t*, short nDefault)
{
    return nDefault;
}

bool Cx_CfgDbSection::SetInt16(const wchar_t*, short)
{
    return false;
}

WORD Cx_CfgDbSection::GetUInt16(const wchar_t*, WORD nDefault)
{
    return nDefault;
}

bool Cx_CfgDbSection::SetUInt16(const wchar_t*, WORD)
{
    return false;
}

bool Cx_CfgDbSection::GetBool(const wchar_t*, BOOL bDefault)
{
    return !!bDefault;
}

bool Cx_CfgDbSection::SetBool(const wchar_t*, BOOL)
{
    return false;
}

double Cx_CfgDbSection::GetDouble(const wchar_t*, double dDefault)
{
    return dDefault;
}

bool Cx_CfgDbSection::SetDouble(const wchar_t*, double)
{
    return false;
}

float Cx_CfgDbSection::GetFloat(const wchar_t*, float fDefault)
{
    return fDefault;
}

bool Cx_CfgDbSection::SetFloat(const wchar_t*, float)
{
    return false;
}

COLORREF Cx_CfgDbSection::GetRGB(const wchar_t*, COLORREF crDefault)
{
    return crDefault;
}

bool Cx_CfgDbSection::SetRGB(const wchar_t*, COLORREF)
{
    return false;
}

bool Cx_CfgDbSection::GetCMYK(const wchar_t*, WORD&, WORD&, WORD&, WORD&)
{
    return false;
}

bool Cx_CfgDbSection::SetCMYK(const wchar_t*, WORD, WORD, WORD, WORD)
{
    return false;
}

bool Cx_CfgDbSection::GetDate(const wchar_t*, int&, int&, int&)
{
    return false;
}

bool Cx_CfgDbSection::SetDate(const wchar_t*, int, int, int)
{
    return false;
}

bool Cx_CfgDbSection::GetDateTime(const wchar_t*, int&, int&, int&, int&, int&, int&)
{
    return false;
}

bool Cx_CfgDbSection::SetDateTime(const wchar_t*, int, int, int, int, int, int)
{
    return false;
}

long Cx_CfgDbSection::GetDoubleArray(const wchar_t*, double*, long)
{
    return 0;
}

bool Cx_CfgDbSection::SetDoubleArray(const wchar_t*, const double*, long)
{
    return false;
}

long Cx_CfgDbSection::GetIntArray(const wchar_t*, long*, long)
{
    return 0;
}

bool Cx_CfgDbSection::SetIntArray(const wchar_t*, const long*, long)
{
    return false;
}

long Cx_CfgDbSection::GetBinary(const wchar_t*, LPVOID, long)
{
    return 0;
}

bool Cx_CfgDbSection::SetBinary(const wchar_t*, LPCVOID, long)
{
    return false;
}
