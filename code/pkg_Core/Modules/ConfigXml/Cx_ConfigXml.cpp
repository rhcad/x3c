// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// Changes:
// 2011-01-18: Delay call CoUninitialize until plugin is unloading.
// 2011-02-18: Not call CoUninitialize if another plugin (eg. StringTable) is using this plugin.
// 2011-02-24: Check NULL string in Cx_ConfigXml::GetSection().
// 2011-05-12: Output error info when saving file.

#define _NEED_STDIO
#include <PluginInc.h>
#include "Cx_ConfigXml.h"
#include "Cx_XmlSection.h"
#include "ConfigXmlImpl.h"
#include <Cx_SimpleObject.h>
#include <IFileCryptHandler.h>
#include <math.h>

#define Cx_Section Cx_Interface<Ix_ConfigSection>

#ifndef WIN32
#include <ConvStr.h>
static inline int _wrename (const wchar_t *oldfile, const wchar_t *newfile)
{
    return rename(x3::w2a(oldfile).c_str(), x3::w2a(newfile).c_str());
}
#endif

class CXmlFileCrypt : public IXmlFileCrypt
{
    IFileCryptHandler*  m_pCryptHandler;
public:
    CXmlFileCrypt(IFileCryptHandler* pCryptHandler)
        : m_pCryptHandler(pCryptHandler)
    {
    }

    virtual bool Decrypt(XMLDOMDocumentPtr& doc, const wchar_t* filename)
    {
        if (NULL == m_pCryptHandler)
            return false;

        wchar_t* pszBuffer = NULL;
        bool bRet = false;

        m_pCryptHandler->Decrypt(filename, &pszBuffer);
        if (pszBuffer != NULL)
        {
            bRet = CXmlUtil::LoadXMLFromString(doc, pszBuffer);
            m_pCryptHandler->FreeBuffer(pszBuffer);
        }

        return bRet;
    }

    virtual bool CryptFile(const wchar_t* filename)
    {
        if (NULL == m_pCryptHandler)
            return false;

        wchar_t tmpfile[256] = { 0 };
        wcsncpy_s(tmpfile, _countof(tmpfile), filename, _countof(tmpfile));
        tmpfile[_countof(tmpfile) - 5] = 0;
        wcscat_s(tmpfile, _countof(tmpfile), L".tmp");

        int nRet = _wrename(filename, tmpfile);
        if (0 == nRet)
        {
            if (0 == m_pCryptHandler->CryptFile(tmpfile, filename))
                return true;

            _wrename(tmpfile, filename);
        }

        return false;
    }
};

bool ConfigXmlImpl::Reload()
{
    bool bRet = false;

    if (!m_bNeedLoad)
        return (m_xmlDoc != NULL);

    m_bNeedLoad = false;

    CXmlFileCrypt crypt(m_pCryptHandler);
    if (CXmlUtil::LoadXMLFile(m_xmlDoc, m_strFileName.c_str(), &crypt))
    {
        if (m_strRootName.empty())
            m_strRootName = CXmlUtil::GetRootName(m_xmlDoc);
        if (CXmlUtil::GetRoot(m_xmlRoot, m_xmlDoc, m_strRootName.c_str()))
        {
            bRet = true;
        }
        else
        {
            m_xmlDoc = NULL;
            LOG_WARNING2(L"@ConfigXml:IDS_LOADXML_ROOT_MISMATCH", m_strFileName);
        }
    }
    else
    {
        if (PathFileExistsW(m_strFileName.c_str()))
            LOG_WARNING2(L"@ConfigXml:IDS_LOADXML_FAIL", m_strFileName);
    }

    if (NULL == m_xmlDoc || NULL == m_xmlRoot)
    {
        NewDoc();
    }
    m_bModified = false;

    return bRet;
}

void ConfigXmlImpl::NewDoc()
{
    std::wstring strRootName(m_strRootName);
    if (strRootName.empty())
        strRootName = L"root";

    CXmlUtil::NewXMLFile2(m_xmlDoc, m_xmlRoot, strRootName.c_str(),
        m_strEncoding.c_str(), m_strNameSpace.c_str());

    if (!m_strSchemaLocation.empty())
    {
        CXmlUtil::SetAttribute(m_xmlDoc, m_xmlRoot,
            L"xmlns:xsi", L"http://www.w3.org/2001/XMLSchema-instance");
        CXmlUtil::SetAttribute(m_xmlDoc, m_xmlRoot,
            L"xsi:noNamespaceSchemaLocation", m_strSchemaLocation.c_str());
    }
}

XMLDOMElementPtr ConfigXmlImpl::GetParentNode(Ix_ConfigSection* parent,
                                              std::wstring& strSection)
{
    XMLDOMElementPtr xmlParent = GetRoot();
    if (parent)
    {
        Cx_XmlSection* p = dynamic_cast<Cx_XmlSection*>(parent);
        ASSERT_MESSAGE(p != NULL, "type mismatch: Ix_ConfigSection");

        xmlParent = p->m_xmlNode;
    }

    return GetParentNode(xmlParent, strSection);
}

XMLDOMElementPtr ConfigXmlImpl::GetParentNode(XMLDOMElementPtr xmlParent,
                                              std::wstring& strSection)
{
    const wchar_t* pStart = strSection.c_str();
    const wchar_t* pEnd;
    const wchar_t* pEnd2;
    std::wstring strTemp, strName;

    for ( ; pStart != NULL && *pStart != 0; pStart = pEnd)
    {
        pEnd = wcschr(pStart, L'\\');
        pEnd2 = wcschr(pStart, L'/');
        if (!pEnd || (pEnd2 && pEnd2 < pEnd))
            pEnd = pEnd2;

        if (NULL == pEnd)
            strTemp = pStart;
        else
        {
            strTemp = std::wstring(pStart, static_cast<long>(pEnd - pStart));
            pEnd++;
        }

        if (!strTemp.empty())
        {
            if (!strName.empty())
            {
                XMLDOMElementPtr xmlNode = xmlParent;
                CXmlUtil::GetChildOrAdd(xmlParent, m_xmlDoc,
                    xmlNode, strName.c_str());
            }
            strName = strTemp;
        }
    }

    strSection = strName;

    return xmlParent;
}

Cx_ConfigXml::Cx_ConfigXml()
{
    m_pImpl = new ConfigXmlImpl(this);
}

Cx_ConfigXml::~Cx_ConfigXml()
{
    delete m_pImpl;
}

Ix_ConfigData* Cx_ConfigXml::GetData()
{
    return this;
}

std::wstring Cx_ConfigXml::GetFileName() const
{
    return m_pImpl->m_strFileName;
}

void Cx_ConfigXml::SetFileName(const wchar_t* filename)
{
    m_pImpl->m_strFileName = filename;
    m_pImpl->m_bNeedLoad = true;
}

std::wstring Cx_ConfigXml::GetRootName() const
{
    std::wstring strRootName(m_pImpl->m_strRootName);

    if (NULL == m_pImpl->m_xmlDoc)
    {
        CXmlFileCrypt crypt(m_pImpl->m_pCryptHandler);
        XMLDOMDocumentPtr xmlDoc;

        if (CXmlUtil::LoadXMLFile(xmlDoc,
            m_pImpl->m_strFileName.c_str(), &crypt))
        {
            strRootName = CXmlUtil::GetRootName(xmlDoc);
        }
    }

    return strRootName;
}

void Cx_ConfigXml::SetRootName(const wchar_t* rootName,
                               const wchar_t* encoding,
                               const wchar_t* nmspace)
{
    m_pImpl->m_strRootName = rootName;
    m_pImpl->m_strEncoding = encoding;
    m_pImpl->m_strNameSpace = nmspace;
}

void Cx_ConfigXml::SetSchemaLocation(const wchar_t* location)
{
    m_pImpl->m_strSchemaLocation = location;
}

bool Cx_ConfigXml::Reload()
{
    m_pImpl->m_bNeedLoad = true;
    return m_pImpl->Reload();
}

bool Cx_ConfigXml::GetXmlContent(std::wstring& content) const
{
    if (NULL == m_pImpl->m_xmlRoot)
    {
        Cx_ConfigXml* pThis = const_cast<Cx_ConfigXml*>(this);
        pThis->m_pImpl->Reload();
    }
    content = CXmlUtil::GetXMLString(m_pImpl->m_xmlDoc);

    return !content.empty();
}

bool Cx_ConfigXml::SetXmlContent(const std::wstring& content)
{
    bool bRet = false;

    if (CXmlUtil::LoadXMLFromString(m_pImpl->m_xmlDoc, content.c_str()))
    {
        if (m_pImpl->m_strRootName.empty())
        {
            m_pImpl->m_strRootName = CXmlUtil::GetRootName(m_pImpl->m_xmlDoc);
        }
        bRet = CXmlUtil::GetRoot(m_pImpl->m_xmlRoot, m_pImpl->m_xmlDoc,
            m_pImpl->m_strRootName.c_str());
        if (!bRet)
        {
            m_pImpl->m_xmlDoc = NULL;
            LOG_WARNING2(L"@ConfigXml:IDS_LOADXML_ROOT_MISMATCH",
                CXmlUtil::GetRootName(m_pImpl->m_xmlDoc));
        }
    }
    else if (content.empty())
    {
        LOG_WARNING(L"@ConfigXml:IDS_LOADXML_EMPTY");
    }
    else
    {
        wchar_t buf[81];
        wcsncpy_s(buf, _countof(buf), content.c_str(), _countof(buf));
        LOG_WARNING2(L"@ConfigXml:IDS_LOADXMLSTR_FAIL", buf);
    }

    if (!bRet)
        m_pImpl->NewDoc();
    m_pImpl->m_bModified = false;

    return bRet;
}

bool Cx_ConfigXml::GetXmlContent(std::wstring& content,
                                 Ix_ConfigSection* node) const
{
    content.resize(0);

    if (node)
    {
        Cx_XmlSection* p = dynamic_cast<Cx_XmlSection*>(node);
        ASSERT_MESSAGE(p != NULL, "type mismatch: Ix_ConfigSection");

        content = CXmlUtil::GetNodeXMLString(p->m_xmlNode);
    }

    return !content.empty();
}

IFileCryptHandler* Cx_ConfigXml::SetCryptHandler(IFileCryptHandler* handler)
{
    IFileCryptHandler* pOld = m_pImpl->m_pCryptHandler;
    m_pImpl->m_pCryptHandler = handler;
    return pOld;
}

void Cx_ConfigXml::BeginTransaction()
{
    m_pImpl->m_nTransaction++;
    if (NULL == m_pImpl->m_xmlRoot)
        m_pImpl->Reload();
}

bool Cx_ConfigXml::EndTransaction()
{
    bool bRet = true;

    if (--m_pImpl->m_nTransaction == 0 && m_pImpl->m_bModified
        && !m_pImpl->m_strFileName.empty())
    {
        m_pImpl->m_bModified = false;
        SetFileAttributesNormal(m_pImpl->m_strFileName.c_str());

        CXmlFileCrypt crypt(m_pImpl->m_pCryptHandler);
        bRet = CXmlUtil::SaveXMLFile(m_pImpl->m_xmlDoc,
            m_pImpl->m_strFileName.c_str(), &crypt);

        if (bRet)
        {
            LOG_DEBUG2(L"@ConfigXml:IDS_SAVEXML_OK", m_pImpl->m_strFileName);
        }
        else
        {
            LOG_WARNING2(L"@ConfigXml:IDS_SAVEXML_FAIL",
                CXmlUtil::GetLastErrorResult()
                << L", " << m_pImpl->m_strFileName);
        }
    }

    return bRet;
}

ULONG Cx_ConfigXml::GetModifiedCount()
{
    return m_pImpl->m_nModifiedCount;
}

bool Cx_ConfigXml::Save(const wchar_t* filename) const
{
    bool bRet = false;
    std::wstring strFileName(filename && filename[0] ? filename
        : m_pImpl->m_strFileName.c_str());

    if (strFileName.empty())
    {
        LOG_WARNING2(L"@ConfigXml:IDS_SAVEXML_FAIL", L"--");
        return false;
    }

    SetFileAttributesNormal(strFileName.c_str());
    CXmlFileCrypt crypt(m_pImpl->m_pCryptHandler);
    bRet = CXmlUtil::SaveXMLFile(m_pImpl->m_xmlDoc,
        strFileName.c_str(), &crypt);

    if (bRet)
    {
        if (_wcsicmp(strFileName.c_str(), m_pImpl->m_strFileName.c_str()) == 0)
            m_pImpl->m_bModified = false;
    }
    else
    {
        LOG_WARNING2(L"@ConfigXml:IDS_SAVEXML_FAIL",
            CXmlUtil::GetLastErrorResult() << L", " << strFileName);
    }

    return bRet;
}

Cx_Section Cx_ConfigXml::GetSection(const wchar_t* name, bool autoCreate)
{
    Cx_Interface<Ix_ConfigSection> pIFRet;
    Cx_XmlSection* pIFCfg = Cx_SimpleObject<Cx_XmlSection>::Create(pIFRet);

    std::wstring strName (name ? name : L"");
    pIFCfg->m_pData = m_pImpl;
    pIFCfg->m_xmlParent = m_pImpl->GetParentNode(m_pImpl->GetRoot(), strName);
    if (strName.empty())
    {
        pIFCfg->m_xmlNode = pIFCfg->m_xmlParent;
    }
    else if (autoCreate)
    {
        CXmlUtil::GetChildOrAdd(pIFCfg->m_xmlNode, m_pImpl->m_xmlDoc,
            pIFCfg->m_xmlParent, strName.c_str());
    }
    else
    {
        CXmlUtil::GetChild(pIFCfg->m_xmlNode,
            pIFCfg->m_xmlParent, strName.c_str());
    }

    return pIFRet;
}

Cx_Section Cx_ConfigXml::GetSection(Ix_ConfigSection* parent,
                                    const wchar_t* name,
                                    const wchar_t* attrName,
                                    ULONG attrValue,
                                    bool autoCreate)
{
    wchar_t buf[35] = { 0 };
    _ultow_s(attrValue, buf, 35, 10);
    return GetSection(parent, name, attrName, buf, autoCreate);
}

Cx_Section Cx_ConfigXml::GetSection(Ix_ConfigSection* parent,
                                    const wchar_t* name,
                                    const wchar_t* attrName,
                                    ULONG attrValue,
                                    const wchar_t* attrName2,
                                    ULONG attrValue2,
                                    bool autoCreate)
{
    wchar_t buf1[35] = { 0 };
    wchar_t buf2[35] = { 0 };
    _ultow_s(attrValue, buf1, 35, 10);
    _ultow_s(attrValue2, buf2, 35, 10);
    return GetSection(parent, name, attrName, buf1, attrName2, buf2, autoCreate);
}

Cx_Section Cx_ConfigXml::GetSection(Ix_ConfigSection* parent,
                                    const wchar_t* name,
                                    const wchar_t* attrName,
                                    const wchar_t* attrValue,
                                    bool autoCreate)
{
    return GetSection(parent, name,
        attrName, attrValue, L"", L"", autoCreate);
}

Cx_Section Cx_ConfigXml::GetSection(Ix_ConfigSection* parent,
                                    const wchar_t* name,
                                    const wchar_t* attrName,
                                    const wchar_t* attrValue,
                                    const wchar_t* attrName2,
                                    const wchar_t* attrValue2,
                                    bool autoCreate)
{
    std::wstring strName (name ? name : L"");
    XMLDOMElementPtr xmlParent = m_pImpl->GetParentNode(parent, strName);
    XMLDOMElementPtr xmlNode;

    if (CXmlUtil::FindElementByAttr(xmlNode, xmlParent,
        strName.c_str(), attrName, attrValue,
        attrName2, attrValue2) < 0
        && autoCreate)
    {
        if (CXmlUtil::AddChild(xmlNode, m_pImpl->m_xmlDoc,
            xmlParent, strName.c_str()))
        {
            CXmlUtil::SetAttribute(m_pImpl->m_xmlDoc, xmlNode,
                attrName, attrValue);
            CXmlUtil::SetAttribute(m_pImpl->m_xmlDoc, xmlNode,
                attrName2, attrValue2);
            m_pImpl->SetModified();
        }
    }

    Cx_Interface<Ix_ConfigSection> pIFRet;
    Cx_XmlSection* pIFCfg = Cx_SimpleObject<Cx_XmlSection>::Create(pIFRet);

    pIFCfg->m_pData = m_pImpl;
    pIFCfg->m_xmlParent = xmlParent;
    pIFCfg->m_xmlNode = xmlNode;

    return pIFRet;
}

long Cx_ConfigXml::GetSectionCount(Ix_ConfigSection* parent,
                                   const wchar_t* name)
{
    std::wstring strName (name ? name : L"");
    XMLDOMElementPtr xmlParent = m_pImpl->GetParentNode(parent, strName);
    return CXmlUtil::GetChildCount(xmlParent, strName.c_str());
}

Cx_Section Cx_ConfigXml::GetSectionByIndex(
    Ix_ConfigSection* parent, const wchar_t* name, long index)
{
    std::wstring strName (name ? name : L"");
    Cx_Interface<Ix_ConfigSection> pIFRet;
    Cx_XmlSection* pIFCfg = Cx_SimpleObject<Cx_XmlSection>::Create(pIFRet);

    pIFCfg->m_pData = m_pImpl;
    pIFCfg->m_xmlParent = m_pImpl->GetParentNode(parent, strName);
    CXmlUtil::GetChild(pIFCfg->m_xmlNode, pIFCfg->m_xmlParent,
        strName.c_str(), index);

    return pIFRet;
}

Cx_Section Cx_ConfigXml::GetParentSection(Ix_ConfigSection* sec)
{
    std::wstring strName(L"");
    Cx_Interface<Ix_ConfigSection> pIFRet;
    Cx_XmlSection* pIFCfg = Cx_SimpleObject<Cx_XmlSection>::Create(pIFRet);

    pIFCfg->m_pData = m_pImpl;
    pIFCfg->m_xmlNode = m_pImpl->GetParentNode(sec, strName);
    if (pIFCfg->m_xmlNode)
    {
        CXmlUtil::GetParentNode(pIFCfg->m_xmlParent, pIFCfg->m_xmlNode);
    }
    if (pIFCfg->m_xmlParent == NULL
        || pIFCfg->m_xmlParent == pIFCfg->m_xmlNode)
    {
        pIFCfg->m_xmlNode = NULL;
    }

    return pIFRet;
}

Cx_Section Cx_ConfigXml::AddSection(Ix_ConfigSection* parent,
                                    const wchar_t* name)
{
    std::wstring strName (name ? name : L"");
    Cx_Interface<Ix_ConfigSection> pIFRet;
    Cx_XmlSection* pIFCfg = Cx_SimpleObject<Cx_XmlSection>::Create(pIFRet);

    pIFCfg->m_pData = m_pImpl;
    pIFCfg->m_xmlParent = m_pImpl->GetParentNode(parent, strName);

    if (CXmlUtil::AddChild(pIFCfg->m_xmlNode, m_pImpl->m_xmlDoc,
        pIFCfg->m_xmlParent, strName.c_str()))
    {
        m_pImpl->SetModified();
    }

    return pIFRet;
}

bool Cx_ConfigXml::RemoveSection(Ix_ConfigSection* sec)
{
    bool bRet = false;

    if (sec != NULL)
    {
        Cx_XmlSection* p = dynamic_cast<Cx_XmlSection*>(sec);
        ASSERT_MESSAGE(p != NULL, "type mismatch: Ix_ConfigSection");

        if (CXmlUtil::DelChild(p->m_xmlParent, p->m_xmlNode))
        {
            bRet = true;
            m_pImpl->SetModified();
        }
    }

    return bRet;
}

long Cx_ConfigXml::RemoveChildren(Ix_ConfigSection* parent,
                                  const wchar_t* name,
                                  const wchar_t* attrName,
                                  ULONG attrValue)
{
    wchar_t buf[35] = { 0 };
    _ultow_s(attrValue, buf, 35, 10);
    return RemoveChildren(parent, name, attrName, buf);
}

long Cx_ConfigXml::RemoveChildren(Ix_ConfigSection* parent,
                                  const wchar_t* name,
                                  const wchar_t* attrName,
                                  const wchar_t* attrValue)
{
    long count = 0;

    if (parent && name)
    {
        Cx_XmlSection* p = dynamic_cast<Cx_XmlSection*>(parent);
        ASSERT_MESSAGE(p != NULL, "type mismatch: Ix_ConfigSection");

        count = CXmlUtil::DelChildren(p->m_xmlNode,
            name, attrName, attrValue);
        if (count > 0)
            m_pImpl->SetModified();
    }

    return count;
}
