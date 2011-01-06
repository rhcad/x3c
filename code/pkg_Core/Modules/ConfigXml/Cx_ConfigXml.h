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

#ifndef _X3_CONFIGXML_CONFIGXML_H
#define _X3_CONFIGXML_CONFIGXML_H

#include <Ix_ConfigData.h>
#include <Ix_ConfigXml.h>
#include <Ix_ConfigTransaction.h>

struct ConfigXmlImpl;

class Cx_ConfigXml
	: public Ix_ConfigData
	, public Ix_ConfigXml
	, public Ix_ConfigTransaction
{
protected:
	Cx_ConfigXml();
	virtual ~Cx_ConfigXml();

protected:
	// From Ix_ConfigXml
	//
	virtual Ix_ConfigData* GetData();
	virtual std::wstring GetFileName() const;
	virtual void SetFileName(LPCWSTR filename);
	virtual std::wstring GetRootName() const;
	virtual void SetRootName(LPCWSTR rootName = L"root", 
		LPCWSTR encoding = L"UTF-8", 
		LPCWSTR nmspace = L"");
	virtual void SetSchemaLocation(LPCWSTR location);
	virtual bool Reload();
	virtual bool Save(LPCWSTR filename = L"") const;
	virtual bool GetXmlContent(std::wstring& content) const;
	virtual bool SetXmlContent(const std::wstring& content);
	virtual bool GetXmlContent(std::wstring& content, Ix_ConfigSection* node) const;
	virtual IFileCryptHandler* SetCryptHandler(IFileCryptHandler* handler);

	// From Ix_ConfigTransaction
	//
	virtual void BeginTransaction();
	virtual bool EndTransaction();
	virtual ULONG GetModifiedCount();

	// From Ix_ConfigData
	//
	virtual ConfigIOSection GetSection(
		LPCWSTR name, bool autoCreate = true);
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, ULONG attrValue, 
		bool autoCreate = true);
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, LPCWSTR attrValue, 
		bool autoCreate = true);
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, LPCWSTR attrValue, 
		LPCWSTR attrName2, LPCWSTR attrValue2, 
		bool autoCreate = true);
	virtual ConfigIOSection GetSection(
		Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, ULONG attrValue, 
		LPCWSTR attrName2, ULONG attrValue2, 
		bool autoCreate = true);
	virtual long GetSectionCount(
		Ix_ConfigSection* parent, LPCWSTR name);
	virtual ConfigIOSection GetSectionByIndex(
		Ix_ConfigSection* parent, LPCWSTR name, long index);
	virtual ConfigIOSection AddSection(
		Ix_ConfigSection* parent, LPCWSTR name);
	virtual bool RemoveSection(Ix_ConfigSection* sec);
	virtual long RemoveChildren(Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName = L"", LPCWSTR attrValue = L"");
	virtual long RemoveChildren(Ix_ConfigSection* parent, LPCWSTR name, 
		LPCWSTR attrName, ULONG attrValue);
	virtual ConfigIOSection GetParentSection(Ix_ConfigSection* sec);

private:
	ConfigXmlImpl*	m_pImpl;
};

#endif // _X3_CONFIGXML_CONFIGXML_H
