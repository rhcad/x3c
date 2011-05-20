// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// Changes:
// 2011-02-24: Set modified flag only if actually changed in Cx_XmlSection::SetXXX().

#include <PluginInc.h>
#include "Cx_XmlSection.h"
#include "ConfigXmlImpl.h"
#include <ReadInts.h>
#include <Ix_ConfigData.h>
#include <math.h>

static const LPCWSTR EMPTYDEFSTR = L"~&*^0@!";

Cx_XmlSection::Cx_XmlSection()
    : m_pData(NULL), m_bSubElement(false)
{
}

Cx_XmlSection::~Cx_XmlSection()
{
}

void Cx_XmlSection::UseSubElement(bool element)
{
    m_bSubElement = element;
}

std::wstring Cx_XmlSection::GetText()
{
    return CXmlUtil::GetText(m_xmlNode);
}

bool Cx_XmlSection::SetText(const wchar_t* value, bool cdata)
{
    bool changed = false;
    std::wstring oldvalue(CXmlUtil::GetText(m_xmlNode, EMPTYDEFSTR));

    if (0 != wcscmp(value, oldvalue.c_str()))
    {
        if (cdata)
        {
            changed = CXmlUtil::SetTextCDATA(
                m_pData->m_xmlDoc, m_xmlNode, value);
        }
        else
        {
            changed = CXmlUtil::SetText(m_xmlNode, value);
        }
        if (changed)
        {
            m_pData->SetModified();
        }
    }

    return changed;
}

IUnknown* Cx_XmlSection::GetDOMElement(bool addRef)
{
    if (m_xmlNode != NULL && addRef)
        m_xmlNode->AddRef();
    return m_xmlNode;
}

IUnknown* Cx_XmlSection::GetDOMDocument(bool addRef)
{
    if (m_pData->m_xmlDoc != NULL && addRef)
        m_pData->m_xmlDoc->AddRef();
    return m_pData->m_xmlDoc;
}

void Cx_XmlSection::BeginTransaction()
{
    Cx_Interface<Ix_ConfigTransaction> pTrans(m_pData->m_pThis);
    ASSERT(pTrans.IsNotNull());
    pTrans->BeginTransaction();
}

bool Cx_XmlSection::EndTransaction()
{
    Cx_Interface<Ix_ConfigTransaction> pTrans(m_pData->m_pThis);
    ASSERT(pTrans.IsNotNull());
    return pTrans->EndTransaction();
}

ULONG Cx_XmlSection::GetModifiedCount()
{
    Cx_Interface<Ix_ConfigTransaction> pTrans(m_pData->m_pThis);
    ASSERT(pTrans.IsNotNull());
    return pTrans->GetModifiedCount();
}

Ix_ConfigData* Cx_XmlSection::GetData() const
{
    ASSERT(m_pData != NULL);
    return m_pData->m_pThis;
}

bool Cx_XmlSection::IsValid() const
{
    return m_xmlNode != NULL;
}

std::wstring Cx_XmlSection::GetString(const wchar_t* name, const wchar_t* defValue)
{
    if (!m_bSubElement)
    {
        return CXmlUtil::GetAttribute(m_xmlNode, name, defValue);
    }
    return CXmlUtil::GetField(m_xmlNode, name, defValue);
}

bool Cx_XmlSection::SetString(const wchar_t* name, const wchar_t* value)
{
    bool changed = false;
    std::wstring oldvalue(GetString(name, EMPTYDEFSTR));

    if (0 != wcscmp(value, oldvalue.c_str()))
    {
        if (!m_bSubElement)
        {
            changed = !!CXmlUtil::SetAttribute(m_pData->m_xmlDoc,
                m_xmlNode, name, value);
        }
        else
        {
            changed = !!CXmlUtil::SetField(m_pData->m_xmlDoc,
                m_xmlNode, name, value);
        }
        if (changed)
        {
            m_pData->SetModified();
        }
    }

    return changed;
}

int Cx_XmlSection::GetInt(const wchar_t* name, int defValue)
{
    if (!m_bSubElement)
    {
        return CXmlUtil::GetAttributeInt(m_xmlNode, name, defValue);
    }
    return CXmlUtil::GetFieldInt(m_xmlNode, name, defValue);
}

bool Cx_XmlSection::SetInt(const wchar_t* name, int value)
{
    bool changed = false;
    std::wstring oldvalue(GetString(name, EMPTYDEFSTR));

    if (oldvalue.compare(EMPTYDEFSTR) == 0
        || value != (int)GetInt(name))
    {
        if (!m_bSubElement)
        {
            changed = !!CXmlUtil::SetAttributeInt(m_pData->m_xmlDoc,
                m_xmlNode, name, value);
        }
        else
        {
            changed = !!CXmlUtil::SetFieldInt(m_pData->m_xmlDoc,
                m_xmlNode, name, value);
        }
        if (changed)
        {
            m_pData->SetModified();
        }
    }

    return changed;
}

long Cx_XmlSection::GetInt32(const wchar_t* name, long defValue)
{
    return GetInt(name, defValue);
}

bool Cx_XmlSection::SetInt32(const wchar_t* name, long value)
{
    return SetInt(name, value);
}

ULONG Cx_XmlSection::GetUInt32(const wchar_t* name, ULONG defValue)
{
    return GetInt(name, defValue);
}

bool Cx_XmlSection::SetUInt32(const wchar_t* name, ULONG value)
{
    return SetInt(name, value);
}

short Cx_XmlSection::GetInt16(const wchar_t* name, short defValue)
{
    return static_cast<short>(GetInt(name, defValue));
}

bool Cx_XmlSection::SetInt16(const wchar_t* name, short value)
{
    return SetInt(name, value);
}

WORD Cx_XmlSection::GetUInt16(const wchar_t* name, WORD defValue)
{
    return static_cast<WORD>(GetInt(name, defValue));
}

bool Cx_XmlSection::SetUInt16(const wchar_t* name, WORD value)
{
    return SetInt(name, value);
}

bool Cx_XmlSection::GetBool(const wchar_t* name, int defValue)
{
    if (!m_bSubElement)
    {
        return !!CXmlUtil::GetAttributeBool(
            m_xmlNode, name, defValue);
    }
    return !!CXmlUtil::GetFieldBool(m_xmlNode, name, defValue);
}

bool Cx_XmlSection::SetBool(const wchar_t* name, int value)
{
    bool changed = false;

    if (value != (int)GetInt(name, 9))
    {
        if (!m_bSubElement)
        {
            changed = !!CXmlUtil::SetAttributeBool(m_pData->m_xmlDoc,
                m_xmlNode, name, value);
        }
        else
        {
            changed = !!CXmlUtil::SetFieldBool(m_pData->m_xmlDoc,
                m_xmlNode, name, value);
        }
        if (changed)
        {
            m_pData->SetModified();
        }
    }

    return changed;
}

double Cx_XmlSection::GetDouble(const wchar_t* name, double defValue)
{
    if (!m_bSubElement)
    {
        return CXmlUtil::GetAttributeFloat(m_xmlNode, name, defValue);
    }
    return CXmlUtil::GetFieldFloat(m_xmlNode, name, defValue);
}

bool Cx_XmlSection::SetDouble(const wchar_t* name, double value)
{
    bool changed = false;

    if (!m_bSubElement)
    {
        if (1e-5 < fabs(value - CXmlUtil::GetAttributeFloat(
            m_xmlNode, name, 1.2345e20)))
        {
            changed = !!CXmlUtil::SetAttributeFloat(m_pData->m_xmlDoc,
                m_xmlNode, name, value);
        }
    }
    else
    {
        if (1e-5 < fabs(value - CXmlUtil::GetFieldFloat(
            m_xmlNode, name, 1e20)))
        {
            changed = !!CXmlUtil::SetFieldFloat(m_pData->m_xmlDoc,
                m_xmlNode, name, value);
        }
    }
    if (changed)
    {
        m_pData->SetModified();
    }

    return changed;
}

float Cx_XmlSection::GetFloat(const wchar_t* name, float defValue)
{
    return static_cast<float>(GetDouble(name, defValue));
}

bool Cx_XmlSection::SetFloat(const wchar_t* name, float value)
{
    return SetDouble(name, value);
}

DWORD Cx_XmlSection::GetRGB(const wchar_t* name, DWORD defValue)
{
    BYTE nums[3] = { 0, 0, 0 };
    if (ReadInts(GetString(name).c_str(), nums, 3) == 3)
        defValue = RGB(nums[0], nums[1], nums[2]);
    return defValue;
}

bool Cx_XmlSection::SetRGB(const wchar_t* name, DWORD value)
{
    wchar_t szBuf[32];
    swprintf_s(szBuf, _countof(szBuf), L"%d, %d, %d",
        GetRValue(value), GetGValue(value), GetBValue(value));
    return SetString(name, szBuf);
}

bool Cx_XmlSection::GetCMYK(const wchar_t* name, WORD& c, WORD& m, WORD& y, WORD& k)
{
    WORD nums[4] = { 0, 0, 0, 0 };
    bool bRet = (ReadInts(GetString(name).c_str(), nums, 4) == 4);
    if (bRet)
    {
        c = nums[0];
        m = nums[1];
        y = nums[2];
        k = nums[3];
    }
    return bRet;
}

bool Cx_XmlSection::SetCMYK(const wchar_t* name, WORD c, WORD m, WORD y, WORD k)
{
    wchar_t szBuf[40];
    swprintf_s(szBuf, _countof(szBuf), L"%d, %d, %d, %d", c, m, y, k);
    return SetString(name, szBuf);
}

bool Cx_XmlSection::GetDate(const wchar_t* name, int& year, int& month, int& day)
{
    int nums[3] = { 0, 0, 0 };

    bool bRet = (ReadInts(GetString(name).c_str(), nums, 3) == 3);

    bRet = bRet && (nums[0] >= 1980 && nums[0] <= 2099);
    bRet = bRet && (nums[1] >= 0 && nums[1] <= 12);
    bRet = bRet && (nums[2] >= 0 && nums[2] <= 31);

    if (bRet)
    {
        year = nums[0];
        month = nums[1];
        day = nums[2];
    }

    return bRet;
}

bool Cx_XmlSection::SetDate(const wchar_t* name, int year, int month, int day)
{
    wchar_t szBuf[40];
    swprintf_s(szBuf, _countof(szBuf), L"%d-%d-%d", year, month, day);
    return SetString(name, szBuf);
}

bool Cx_XmlSection::GetDateTime(const wchar_t* name, int& year, int& month, int& day,
    int& hour, int& minute, int& second)
{
    int nums[6] = { 0, 0, 0, 0, 0, 0 };

    bool bRet = (ReadInts(GetString(name).c_str(), nums, 6) >= 3);

    bRet = bRet && (nums[0] >= 1980 && nums[0] <= 2099);
    bRet = bRet && (nums[1] >= 0 && nums[1] <= 12);
    bRet = bRet && (nums[2] >= 0 && nums[2] <= 31);

    if (bRet)
    {
        year = nums[0];
        month = nums[1];
        day = nums[2];
        hour = nums[3];
        minute = nums[4];
        second = nums[5];
    }

    return bRet;
}

bool Cx_XmlSection::SetDateTime(const wchar_t* name, int year, int month, int day,
    int hour, int minute, int second)
{
    wchar_t szBuf[60];
    swprintf_s(szBuf, _countof(szBuf), L"%d-%d-%d %d:%d:%d",
        year, month, day, hour, minute, second);
    return SetString(name, szBuf);
}

long Cx_XmlSection::GetDoubleArray(const wchar_t* name, double* items, long count)
{
    return ReadDoubleArray(GetString(name).c_str(), items, count);
}

bool Cx_XmlSection::SetDoubleArray(const wchar_t* name, const double* items, long count)
{
    std::wostringstream sbuf;
    for (int i = 0; i < count; i++)
    {
        if (i > 0)
            sbuf << L", ";
        sbuf << CXmlUtil::RoundStr(items[i]);
    }
    return SetString(name, sbuf.str().c_str());
}

long Cx_XmlSection::GetIntArray(const wchar_t* name, long* items, long count)
{
    return ReadInts(GetString(name).c_str(), items, count);
}

bool Cx_XmlSection::SetIntArray(const wchar_t* name, const long* items, long count)
{
    std::wostringstream sbuf;
    for (int i = 0; i < count; i++)
    {
        if (i > 0)
            sbuf << L", ";
        sbuf << CXmlUtil::RoundStr(items[i], 0);
    }
    return SetString(name, sbuf.str().c_str());
}

long Cx_XmlSection::GetBinary(const wchar_t* name, void* buf, long size)
{
    std::wstring wstrText(GetString(name));
    size_t nLen = wstrText.size();
    const wchar_t* pszText = wstrText.c_str();

    wchar_t szNum[3] = L"00";
    int nRet = 0;
    BYTE* items = (BYTE*)buf;
    wchar_t* endptr;

    for (size_t i = 0; i + 1 < nLen && nRet < size; i += 2)
    {
        szNum[0] = pszText[i];
        szNum[1] = pszText[i + 1];
        items[nRet++] = static_cast<BYTE>(wcstol(szNum, &endptr, 16));
    }

    return nRet;
}

bool Cx_XmlSection::SetBinary(const wchar_t* name, const void* buf, long size)
{
    std::wostringstream sbuf;
    wchar_t szNum[20];
    BYTE* items = (BYTE*)buf;

    for (int i = 0; i < size; i++)
    {
        _itow_s(items[i], szNum, _countof(szNum), 16);
        if (0 == szNum[1])
            sbuf << L"0";
        sbuf << szNum;
    }
    return SetString(name, sbuf.str().c_str());
}
