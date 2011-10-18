// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef _X3_CONFIGXML_CONFIGXML_H
#define _X3_CONFIGXML_CONFIGXML_H

#include <Xml/Ix_ConfigData.h>
#include <Xml/Ix_ConfigXml.h>
#include <Xml/Ix_ConfigTransaction.h>

struct ConfigXmlImpl;

class Cx_ConfigXml
    : public Ix_ConfigData
    , public Ix_ConfigXml
    , public Ix_ConfigTransaction
{
    X3BEGIN_CLASS_DECLARE(Cx_ConfigXml)
        X3DEFINE_INTERFACE_ENTRY(Ix_ConfigData)
        X3DEFINE_INTERFACE_ENTRY(Ix_ConfigXml)
        X3DEFINE_INTERFACE_ENTRY(Ix_ConfigTransaction)
    X3END_CLASS_DECLARE()
protected:
    Cx_ConfigXml();
    virtual ~Cx_ConfigXml();

private:
    // From Ix_ConfigXml
    //
    virtual Ix_ConfigData* GetData();
    virtual std::wstring GetFileName() const;
    virtual void SetFileName(const wchar_t* filename);
    virtual std::wstring GetRootName() const;
    virtual void SetRootName(const wchar_t* rootName = L"root",
        const wchar_t* encoding = L"UTF-8",
        const wchar_t* nmspace = L"");
    virtual void SetSchemaLocation(const wchar_t* location);
    virtual bool Reload();
    virtual bool Save(const wchar_t* filename = L"") const;
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
    virtual Cx_Ptr GetSection(
        const wchar_t* name, bool autoCreate = true);
    virtual Cx_Ptr GetSection(
        Ix_ConfigSection* parent, const wchar_t* name,
        const wchar_t* attrName, ULONG attrValue,
        bool autoCreate = true);
    virtual Cx_Ptr GetSection(
        Ix_ConfigSection* parent, const wchar_t* name,
        const wchar_t* attrName, const wchar_t* attrValue,
        bool autoCreate = true);
    virtual Cx_Ptr GetSection(
        Ix_ConfigSection* parent, const wchar_t* name,
        const wchar_t* attrName, const wchar_t* attrValue,
        const wchar_t* attrName2, const wchar_t* attrValue2,
        bool autoCreate = true);
    virtual Cx_Ptr GetSection(
        Ix_ConfigSection* parent, const wchar_t* name,
        const wchar_t* attrName, ULONG attrValue,
        const wchar_t* attrName2, ULONG attrValue2,
        bool autoCreate = true);
    virtual long GetSectionCount(
        Ix_ConfigSection* parent, const wchar_t* name);
    virtual Cx_Ptr GetSectionByIndex(
        Ix_ConfigSection* parent, const wchar_t* name, long index);
    virtual Cx_Ptr AddSection(
        Ix_ConfigSection* parent, const wchar_t* name);
    virtual bool RemoveSection(Ix_ConfigSection* sec);
    virtual long RemoveChildren(Ix_ConfigSection* parent, const wchar_t* name,
        const wchar_t* attrName = L"", const wchar_t* attrValue = L"");
    virtual long RemoveChildren(Ix_ConfigSection* parent, const wchar_t* name,
        const wchar_t* attrName, ULONG attrValue);
    virtual Cx_Ptr GetParentSection(Ix_ConfigSection* sec);

private:
    Cx_ConfigXml(const Cx_ConfigXml&);
    void operator=(const Cx_ConfigXml&);

    ConfigXmlImpl*  m_pImpl;
};

#endif // _X3_CONFIGXML_CONFIGXML_H
