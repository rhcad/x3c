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

#ifndef _X3_CONFIGXML_XMLSECTION_H
#define _X3_CONFIGXML_XMLSECTION_H

#include <Ix_ConfigSection.h>
#include <Ix_ConfigSectionXml.h>
#include <Ix_ConfigTransaction.h>
#include "XmlUtil/XmlUtil.h"

struct ConfigXmlImpl;

class Cx_XmlSection
    : public Ix_ConfigSection
    , public Ix_ConfigSectionXml
    , public Ix_ConfigTransaction
{
protected:
    Cx_XmlSection();
    virtual ~Cx_XmlSection();

public:
    ConfigXmlImpl*      m_pData;
    CXTPDOMElementPtr   m_xmlParent;
    CXTPDOMElementPtr   m_xmlNode;
    bool                m_bSubElement;

protected:
    // From Ix_ConfigSectionXml
    //
    virtual void UseSubElement(bool element);
    virtual std::wstring GetText();
    virtual bool SetText(LPCWSTR value, bool cdata = false);
    virtual IUnknown* GetDOMElement(bool addRef = false);
    virtual IUnknown* GetDOMDocument(bool addRef = false);

    // From Ix_ConfigTransaction
    //
    virtual void BeginTransaction();
    virtual bool EndTransaction();
    virtual ULONG GetModifiedCount();

    // From Ix_ConfigSection
    //
    virtual Ix_ConfigData* GetData() const;
    virtual bool IsValid() const;
    virtual std::wstring GetString(LPCWSTR name, LPCWSTR defValue = L"");
    virtual bool SetString(LPCWSTR name, LPCWSTR value);
    virtual int GetInt(LPCWSTR name, int defValue = 0);
    virtual bool SetInt(LPCWSTR name, int value);
    virtual long GetInt32(LPCWSTR name, long defValue = 0);
    virtual bool SetInt32(LPCWSTR name, long value);
    virtual ULONG GetUInt32(LPCWSTR name, ULONG defValue = 0);
    virtual bool SetUInt32(LPCWSTR name, ULONG value);
    virtual short GetInt16(LPCWSTR name, short defValue = 0);
    virtual bool SetInt16(LPCWSTR name, short value);
    virtual WORD GetUInt16(LPCWSTR name, WORD defValue = 0);
    virtual bool SetUInt16(LPCWSTR name, WORD value);
    virtual bool GetBool(LPCWSTR name, BOOL defValue);
    virtual bool SetBool(LPCWSTR name, BOOL value);
    virtual double GetDouble(LPCWSTR name, double defValue = 0);
    virtual bool SetDouble(LPCWSTR name, double value);
    virtual float GetFloat(LPCWSTR name, float defValue = 0);
    virtual bool SetFloat(LPCWSTR name, float value);
    virtual COLORREF GetRGB(LPCWSTR name, COLORREF defValue);
    virtual bool SetRGB(LPCWSTR name, COLORREF value);
    virtual bool GetCMYK(LPCWSTR name, WORD& c, WORD& m, WORD& y, WORD& k);
    virtual bool SetCMYK(LPCWSTR name, WORD c, WORD m, WORD y, WORD k);
    virtual bool GetDate(LPCWSTR name, int& year, int& month, int& day);
    virtual bool SetDate(LPCWSTR name, int year, int month, int day);
    virtual bool GetDateTime(LPCWSTR name, int& year, int& month, int& day, 
        int& hour, int& minute, int& second);
    virtual bool SetDateTime(LPCWSTR name, int year, int month, int day, 
        int hour, int minute, int second);
    virtual long GetDoubleArray(LPCWSTR name, double* items, long count);
    virtual bool SetDoubleArray(LPCWSTR name, const double* items, long count);
    virtual long GetIntArray(LPCWSTR name, long* items, long count);
    virtual bool SetIntArray(LPCWSTR name, const long* items, long count);
    virtual long GetBinary(LPCWSTR name, LPVOID buf, long size);
    virtual bool SetBinary(LPCWSTR name, LPCVOID buf, long size);
};

#endif // _X3_CONFIGXML_XMLSECTION_H
