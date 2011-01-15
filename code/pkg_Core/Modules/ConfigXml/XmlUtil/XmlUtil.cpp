// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// XmlUtil.cpp: implementation of the CXmlUtil class.
// changes:
//    2011-01-10, Zhang Yun Gui: support MSXML6 and MSXML4
//

#include "stdafx.h"
#include "XmlUtil.h"

#if _MSC_VER < 1400 // not VC8
#define _itow_s(nVal, szNum, nSize, nRadix) _itow(nVal, szNum, nRadix)
#endif // _MSC_VER

static HRESULT s_hr = S_OK;

static inline void NL(const wchar_t*& psz)
{
    if (NULL == psz)
    {
        static const wchar_t nullStr[] = L"";
        psz = nullStr;
    }
}

static inline bool IsNotEmpty(const wchar_t* sz)
{
    return sz != NULL && *sz != 0;
}

static const CLSID CLSID_XmlDocument60 = 
    { 0x88d96a05, 0xf192, 0x11d4,{0xa6,0x5f,0x00,0x40,0x96,0x32,0x51,0xe5}};
static const CLSID CLSID_XmlDocument40 = 
    { 0x88d969c0, 0xf192, 0x11d4,{0xa6,0x5f,0x00,0x40,0x96,0x32,0x51,0xe5}};

class LocalHResult
{
public:
    HRESULT m_hr;

    LocalHResult() : m_hr(S_OK)
    {
    }
    ~LocalHResult()
    {
        InterlockedExchange((LPLONG)&s_hr, m_hr);
    }
    HRESULT& operator=(HRESULT hr)
    {
        m_hr = hr;
        return m_hr;
    }
    operator HRESULT&()
    {
        return m_hr;
    }
};

HRESULT CXmlUtil::GetLastErrorResult()
{
    return s_hr;
}

bool CXmlUtil::NewXMLFile(CXTPDOMDocumentPtr& doc, 
                          const wchar_t* pszRootName, 
                          const wchar_t* pszEncoding, 
                          const wchar_t* pszNameSpace, 
                          const wchar_t* pszComment)
{
    LocalHResult hr;

    doc = NULL;
    if (FAILED(hr = doc.CreateInstance(CLSID_XmlDocument60))
        && FAILED(hr = doc.CreateInstance(CLSID_XmlDocument40)))
    {
#ifdef LOGHEAD
        LOG_ERROR2(LOGHEAD L"IDS_CREATEINSTANCE_FAIL", L"CLSID_XmlDocument");
#endif
        return false;
    }

    XTPXML::IXMLDOMNodePtr pDocNode (doc);
    
    std::wstring strHeader = L"version=\"1.0\" encoding=\"";
    strHeader += pszEncoding;
    strHeader += L"\"";
    XTPXML::IXMLDOMProcessingInstructionPtr pHeader;
    hr = doc->createProcessingInstruction(
        _bstr_t(L"xml"), _bstr_t(strHeader.c_str()), &pHeader);
    hr = pDocNode->appendChild(pHeader, NULL);

    if (IsNotEmpty(pszComment))
    {
        XTPXML::IXMLDOMComment* pComment = NULL;
        hr = doc->createComment(_bstr_t(pszComment), &pComment);
        if (pComment != NULL)
        {
            hr = doc->appendChild(CXTPDOMNodePtr(pComment), NULL);
            pComment->Release();
        }
    }
    
    // Create root node
    if (IsNotEmpty(pszRootName))
    {
        VARIANT type;
        V_VT(&type) = VT_INT;
        V_INT(&type) = XTPXML::NODE_ELEMENT;
        XTPXML::IXMLDOMNodePtr pRoot;
        hr = doc->createNode(type, _bstr_t(pszRootName), _bstr_t(pszNameSpace), &pRoot);
        hr = pDocNode->appendChild(pRoot, NULL);
    }
    
    return true;
}

bool CXmlUtil::NewXMLFile2(CXTPDOMDocumentPtr& doc, 
                           CXTPDOMElementPtr& root, 
                           const wchar_t* pszRootName, 
                           const wchar_t* pszEncoding, 
                           const wchar_t* pszNameSpace)
{
    root = NULL;
    if (NewXMLFile(doc, pszRootName, pszEncoding, pszNameSpace))
    {
        if (!GetRoot(root, doc, pszRootName))
            doc = NULL;
    }
    return doc != NULL;
}

bool CXmlUtil::LoadXMLFile(CXTPDOMDocumentPtr& doc, 
                           const wchar_t* pszFileName, 
                           IXmlFileCrypt* pCryptHandler)
{
    LocalHResult hr;
    if (!IsNotEmpty(pszFileName))
        return false;

    if (pCryptHandler && pCryptHandler->Decrypt(doc, pszFileName))
    {
        ASSERT(doc != NULL);
        return true;
    }

    VARIANT_BOOL bLoad;
    
    doc = NULL;
    if (FAILED(hr = doc.CreateInstance(CLSID_XmlDocument60))
        && FAILED(hr = doc.CreateInstance(CLSID_XmlDocument40)))
    {
#ifdef LOGHEAD
        LOG_ERROR2(LOGHEAD L"IDS_CREATEINSTANCE_FAIL", L"CLSID_XmlDocument");
#endif
        return false;
    }
    
    VARIANT vt;
    V_VT(&vt) = VT_BSTR;
    V_BSTR(&vt) = ::SysAllocString(pszFileName);
    
    try
    {
        hr = doc->put_async(VARIANT_FALSE);
        if (FAILED(hr = doc->load(vt, &bLoad)) || !bLoad)
        {
            doc = NULL;
        }
    }
    catch (...)
    {
        hr = E_FAIL;
    }
    
    if (vt.bstrVal != NULL)
        ::SysFreeString(vt.bstrVal);
    
    return SUCCEEDED(hr) && (doc != NULL);
}

bool CXmlUtil::LoadXMLFile(CXTPDOMDocumentPtr& doc, 
                           const wchar_t* pszFileName, 
                           CXTPDOMElementPtr& root, 
                           const wchar_t* pszRootName, 
                           IXmlFileCrypt* pCryptHandler)
{
    root = NULL;
    if (LoadXMLFile(doc, pszFileName, pCryptHandler))
    {
        if (!GetRoot(root, doc, pszRootName))
            doc = NULL;
    }
    return doc != NULL;
}

bool CXmlUtil::SaveXMLFile(const CXTPDOMDocumentPtr& doc, 
                           const wchar_t* pszFileName, 
                           IXmlFileCrypt* pCryptHandler)
{
    LocalHResult hr;
    if (!IsNotEmpty(pszFileName))
        return false;

    VARIANT vt;
    V_VT(&vt) = VT_BSTR;
    V_BSTR(&vt) = ::SysAllocString(pszFileName);
    
    try
    {
        hr = doc->save(vt);
    }
    catch (...)
    {
        hr = E_FAIL;
    }
    
    if (vt.bstrVal != NULL)
        ::SysFreeString(vt.bstrVal);

    if (SUCCEEDED(hr) && pCryptHandler)
    {
        pCryptHandler->CryptFile(pszFileName);
    }
    
    return SUCCEEDED(hr);
}

bool CXmlUtil::LoadXMLFromString(CXTPDOMDocumentPtr& doc, LPCSTR pszXML)
{
    LocalHResult hr;

    pszXML = pszXML ? StrChrA(pszXML, '<') : NULL;
    if (NULL == pszXML || 0 == pszXML[0])
    {
        return false;
    }
    
    doc = NULL;
    if (FAILED(hr = doc.CreateInstance(CLSID_XmlDocument60))
        && FAILED(hr = doc.CreateInstance(CLSID_XmlDocument40)))
    {
#ifdef LOGHEAD
        LOG_ERROR2(LOGHEAD L"IDS_CREATEINSTANCE_FAIL", L"CLSID_XmlDocument");
#endif
        return false;
    }
    
    VARIANT_BOOL bRet;
    hr = doc->put_async(VARIANT_FALSE);
    if (FAILED(hr = doc->loadXML(_bstr_t(pszXML), &bRet)) || !bRet)
    {
        doc = NULL;
    }
    
    return doc != NULL;
}

bool CXmlUtil::LoadXMLFromString(CXTPDOMDocumentPtr& doc, const wchar_t* pszXML)
{
    LocalHResult hr;

    pszXML = pszXML ? StrChrW(pszXML, '<') : NULL;
    if (NULL == pszXML || 0 == pszXML[0])
    {
        return false;
    }
    
    doc = NULL;
    if (FAILED(hr = doc.CreateInstance(CLSID_XmlDocument60))
        && FAILED(hr = doc.CreateInstance(CLSID_XmlDocument40)))
    {
#ifdef LOGHEAD
        LOG_ERROR2(LOGHEAD L"IDS_CREATEINSTANCE_FAIL", L"CLSID_XmlDocument");
#endif
        return false;
    }
    
    VARIANT_BOOL bRet;
    hr = doc->put_async(VARIANT_FALSE);
    if (FAILED(hr = doc->loadXML(_bstr_t(pszXML), &bRet)) || !bRet)
    {
        doc = NULL;
    }
    
    return doc != NULL;
}

std::wstring CXmlUtil::GetXMLString(const CXTPDOMDocumentPtr& doc)
{
    LocalHResult hr;
    std::wstring str;
    BSTR bstr = NULL;
    
    if (doc != NULL)
        hr = doc->get_xml(&bstr);
    if (bstr != NULL)
    {
        str = bstr;
        ::SysFreeString(bstr);
    }
    
    return str;
}

std::wstring CXmlUtil::GetNodeXMLString(const CXTPDOMElementPtr& ele)
{
    LocalHResult hr;
    std::wstring str;
    BSTR bstr = NULL;
    
    if (ele != NULL)
        hr = ele->get_xml(&bstr);
    if (bstr != NULL)
    {
        str = bstr;
        ::SysFreeString(bstr);
    }
    
    return str;
}

std::wstring CXmlUtil::GetRootName(const CXTPDOMDocumentPtr& doc)
{
    LocalHResult hr;
    if (doc)
    {
        CXTPDOMElementPtr ele;
        hr = doc->get_documentElement(&ele);
        return GetTagName(ele);
    }
    return std::wstring();
}

bool CXmlUtil::CreateDocComment(const CXTPDOMDocumentPtr& doc, 
                                const wchar_t* pszComment)
{
    LocalHResult hr;
    if (doc != NULL && IsNotEmpty(pszComment))
    {
        CXTPDOMElementPtr ele;
        hr = doc->get_documentElement(&ele);

        XTPXML::IXMLDOMComment* pComment = NULL;
        hr = doc->createComment(_bstr_t(pszComment), &pComment);
        if (pComment != NULL)
        {
            hr = doc->insertBefore(CXTPDOMNodePtr(pComment), _variant_t(ele), NULL);
            pComment->Release();

            return true;
        }
    }

    return false;
}

bool CXmlUtil::CreateNodeComment(const CXTPDOMDocumentPtr& doc, 
                                 const CXTPDOMElementPtr& ele, 
                                 const wchar_t* pszComment)
{
    LocalHResult hr;
    if (doc != NULL && ele != NULL && IsNotEmpty(pszComment))
    {
        XTPXML::IXMLDOMComment* pComment = NULL;
        hr = doc->createComment(_bstr_t(pszComment), &pComment);
        if (pComment != NULL)
        {
            hr = ele->appendChild(CXTPDOMNodePtr(pComment), NULL);
            pComment->Release();

            return true;
        }
    }

    return false;
}

bool CXmlUtil::GetRoot(CXTPDOMElementPtr& root, 
                       const CXTPDOMDocumentPtr& doc, 
                       const wchar_t* pszRootName)
{
    LocalHResult hr;
    XTPXML::IXMLDOMNodeListPtr nl;
    long nCount = 0;
    XTPXML::IXMLDOMNodePtr pRet = NULL;
    
    if (doc != NULL)
        hr = doc->getElementsByTagName(_bstr_t(pszRootName), &nl);
    
    if (nl != NULL)
    {
        hr = nl->get_length(&nCount);
        if (nCount > 0)
            hr = nl->get_item(0, &pRet);
    }
    
    root = pRet;

    return pRet != NULL;
}

static long GetChildIndex(const CXTPDOMElementPtr& ele, 
                          const wchar_t* pszChildName, 
                          long nMaxIndex, 
                          XTPXML::IXMLDOMNodePtr& pRet)
{
    LocalHResult hr;
    pRet = NULL;

    if (!IsNotEmpty(pszChildName) || NULL == ele)
        return 0;

    long n = 0, nCount = 0;
    XTPXML::IXMLDOMNodeListPtr nl;

    hr = ele->get_childNodes(&nl);
    if (nl != NULL)
    {
        hr = nl->get_length(&n);
        for (int i = 0; i < n; i++)
        {
            XTPXML::IXMLDOMNodePtr pNode;
            hr = nl->get_item(i, &pNode);
            if (NULL == pNode)
                continue;

            BSTR bstr = NULL;
            hr = pNode->get_nodeName(&bstr);
            if (bstr != NULL && _wcsicmp(bstr, pszChildName) == 0)
            {
                nCount++;
                if (nCount > nMaxIndex)
                {
                    pRet = pNode;
                    ::SysFreeString(bstr);
                    break;
                }
            }
            ::SysFreeString(bstr);
        }
    }
    
    return nCount;
}

long CXmlUtil::GetChildCount(const CXTPDOMElementPtr& ele, 
                             const wchar_t* pszChildName)
{
    XTPXML::IXMLDOMNodePtr pRet = NULL;
    return GetChildIndex(ele, pszChildName, 99999, pRet);
}

bool CXmlUtil::GetChild(CXTPDOMElementPtr& outEle, 
                        const CXTPDOMElementPtr& parent, 
                        const wchar_t* pszChildName, 
                        long nIndex)
{
    XTPXML::IXMLDOMNodePtr pRet = NULL;
    GetChildIndex(parent, pszChildName, nIndex, pRet);
    outEle = pRet;
    return outEle != NULL;
}

bool CXmlUtil::GetChildOrAdd(CXTPDOMElementPtr& outEle, 
                             const CXTPDOMDocumentPtr& doc, 
                             const CXTPDOMElementPtr& parent, 
                             const wchar_t* pszChildName)
{
    LocalHResult hr;
    outEle = NULL;

    if (!IsNotEmpty(pszChildName) || NULL == parent)
        return false;

    XTPXML::IXMLDOMNodePtr pRet = NULL;
    GetChildIndex(parent, pszChildName, 0, pRet);
    outEle = pRet;

    if (NULL == outEle)
    {
        hr = doc->createElement(_bstr_t(pszChildName), &outEle);
        hr = parent->appendChild(outEle, NULL);
    }

    return outEle != NULL;
}

bool CXmlUtil::AddChild(CXTPDOMElementPtr& outEle, 
                        const CXTPDOMDocumentPtr& doc, 
                        const CXTPDOMElementPtr& ele, 
                        const wchar_t* pszChildName)
{
    LocalHResult hr;
    CXTPDOMElementPtr pRet = NULL;
    
    outEle = NULL;
    if (doc != NULL && ele != NULL && IsNotEmpty(pszChildName))
        hr = doc->createElement(_bstr_t(pszChildName), &pRet);
    if (pRet != NULL)
    {
        hr = ele->appendChild(pRet, NULL);
        outEle = pRet;
    }
    
    return outEle != NULL;
}

bool CXmlUtil::DelChild(const CXTPDOMElementPtr& ele, 
                        const wchar_t* pszChildName, 
                        long nIndex)
{
    LocalHResult hr;
    CXTPDOMElementPtr pItem;
    bool bRet = GetChild(pItem, ele, pszChildName, nIndex);

    if (bRet)
    {
        hr = ele->removeChild(pItem, NULL);
        pItem = NULL;
    }

    return bRet;
}

bool CXmlUtil::DelChild(const CXTPDOMElementPtr& parent, 
                        CXTPDOMElementPtr& eleDel)
{
    LocalHResult hr;
    bool bRet = false;

    if (parent != NULL && eleDel != NULL)
    {
        XTPXML::IXMLDOMNodePtr pNode;
        hr = eleDel->get_parentNode(&pNode);
        if (pNode == parent)
        {
            bRet = SUCCEEDED(hr = parent->removeChild(eleDel, NULL));
            if (bRet)
                eleDel = NULL;
        }
    }

    return bRet;
}

long CXmlUtil::DelChildren(const CXTPDOMElementPtr& ele, 
                           const wchar_t* pszChildName, 
                           const wchar_t* pszAttrName, const wchar_t* pszAttrValue)
{
    LocalHResult hr;
    CXTPDOMElementPtr pSubItem;
    long nDel = 0;
    long nCount = GetChildCount(ele, pszChildName);
    for (long i = nCount - 1; i >= 0; i--)
    {
        if (GetChild(pSubItem, ele, pszChildName, i))
        {
            if (pszAttrName != NULL && pszAttrValue != NULL
                && _wcsicmp(GetAttribute(pSubItem, pszAttrName).c_str(), pszAttrValue) != 0)
            {
                continue;
            }
            hr = ele->removeChild(pSubItem, NULL);
            pSubItem = NULL;
            nDel++;
        }
    }
    
    return nDel;
}

long CXmlUtil::FindElement(CXTPDOMElementPtr& outEle, 
                           const CXTPDOMElementPtr& parent, 
                           const wchar_t* pszElement, 
                           const wchar_t* pszField, 
                           const wchar_t* pszValue)
{
    NL(pszValue);
    CXTPDOMElementPtr ele;
    long nCount = GetChildCount(parent, pszElement);
    long i;
    
    outEle = NULL;
    for (i = nCount - 1; i >= 0; i--)
    {
        if (GetChild(ele, parent, pszElement, i)
            && _wcsicmp(GetField(ele, pszField).c_str(), pszValue) == 0)
        {
            outEle = ele;
            break;
        }
    }
    
    return i;
}

long CXmlUtil::FindElementByAttr(CXTPDOMElementPtr& outEle, 
                                 const CXTPDOMElementPtr& parent, 
                                 const wchar_t* pszElement, 
                                 const wchar_t* pszAttr1, 
                                 const wchar_t* pszValue1, 
                                 const wchar_t* pszAttr2, 
                                 const wchar_t* pszValue2)
{
    NL(pszAttr1); NL(pszValue1); NL(pszAttr2); NL(pszValue2);
    CXTPDOMElementPtr ele;
    long i = GetChildCount(parent, pszElement);
    
    outEle = NULL;
    while (--i >= 0)
    {
        if (GetChild(ele, parent, pszElement, i))
        {
            if (_wcsicmp(GetAttribute(ele, pszAttr1).c_str(), pszValue1) == 0
                && (!IsNotEmpty(pszAttr2) || _wcsicmp(
                    GetAttribute(ele, pszAttr2).c_str(), pszValue2) == 0))
            {
                outEle = ele;
                break;
            }
        }
    }
    
    return i;
}

std::wstring CXmlUtil::GetTagName(const CXTPDOMElementPtr& ele)
{
    LocalHResult hr;
    std::wstring wstrTagName;
    BSTR bstr = NULL;
    
    if (ele != NULL)
        hr = ele->get_tagName(&bstr);
    if (bstr != NULL)
    {
        wstrTagName = bstr;
        ::SysFreeString(bstr);
    }
    
    return wstrTagName;
}

std::wstring CXmlUtil::GetText(const CXTPDOMNodePtr& pNode, const wchar_t* pszDefault)
{
    LocalHResult hr;
    NL(pszDefault);
    std::wstring strText(pszDefault);
    BSTR bstr = NULL;
    
    if (pNode != NULL)
    {
        hr = pNode->get_text(&bstr);
        if (bstr != NULL)
        {
            strText = bstr;
            ::SysFreeString(bstr);
        }

        VARIANT_BOOL bHasChild;
        if (strText.empty()
            && SUCCEEDED(hr = pNode->hasChildNodes(&bHasChild)) && bHasChild)
        {
            strText = GetTextCDATA(pNode, pszDefault);
        }
    }
    
    return strText;
}

bool CXmlUtil::SetText(const CXTPDOMNodePtr& pNode, const wchar_t* pszText)
{
    LocalHResult hr;
    bool bRet = false;
    if (pNode != NULL)
        bRet = SUCCEEDED(hr = pNode->put_text(_bstr_t(pszText)));
    return bRet;
}

bool CXmlUtil::SetTextW(const CXTPDOMNodePtr& pNode, const wchar_t* pszText)
{
    LocalHResult hr;
    bool bRet = false;
    if (pNode != NULL)
        bRet = SUCCEEDED(hr = pNode->put_text(_bstr_t(pszText)));
    return bRet;
}

bool CXmlUtil::DelAttribute(const CXTPDOMElementPtr& ele, 
                            const wchar_t* pszName)
{
    LocalHResult hr;
    XTPXML::IXMLDOMAttributePtr pNode = NULL;

    if (ele != NULL && IsNotEmpty(pszName))
        hr = ele->getAttributeNode(_bstr_t(pszName), &pNode);

    if (pNode != NULL)
    {
        CXTPDOMElementPtr pItem(pNode);
        return SUCCEEDED(hr = ele->removeChild(pItem, NULL));
    }

    return false;
}

std::wstring CXmlUtil::GetAttribute(const CXTPDOMElementPtr& ele, 
                                    const wchar_t* pszName, 
                                    const wchar_t* pszDefault)
{
    NL(pszDefault);
    std::wstring strValue (pszDefault);
    XTPXML::IXMLDOMAttributePtr pNode = NULL;
    LocalHResult hr;
    
    if (IsNotEmpty(pszName) && ele != NULL)
        hr = ele->getAttributeNode(_bstr_t(pszName), &pNode);
    if (pNode != NULL)
    {
        BSTR bstr = NULL;
        hr = pNode->get_text(&bstr);
        if (bstr != NULL)
        {
            strValue = bstr;
            ::SysFreeString(bstr);
        }
    }
    
    return strValue;
}

bool CXmlUtil::SetAttribute(const CXTPDOMDocumentPtr&, 
                            const CXTPDOMElementPtr& ele, 
                            const wchar_t* pszName, 
                            const wchar_t* pszValue)
{
    LocalHResult hr;
    bool bRet = false;
    
    if (IsNotEmpty(pszName) && ele != NULL)
    {
        hr = ele->setAttribute(_bstr_t(pszName), _variant_t(pszValue));
        bRet = SUCCEEDED(hr);
    }
    
    return bRet;
}

UINT CXmlUtil::GetAttributeInt(const CXTPDOMElementPtr& ele, 
                               const wchar_t* pszName, 
                               INT nDef)
{
    UINT nRet = nDef;
    std::wstring str = GetAttribute(ele, pszName);

    if (_wcsicmp(str.c_str(), L"true") == 0)
        return 1;
    if (_wcsicmp(str.c_str(), L"false") == 0)
        return 0;

    if (!str.empty())
        nRet = _wtoi(str.c_str());

    return nRet;
}

bool CXmlUtil::SetAttributeInt(const CXTPDOMDocumentPtr& doc, 
                               const CXTPDOMElementPtr& ele, 
                               const wchar_t* pszName, 
                               INT nVal)
{
    wchar_t szNum[35];
    _itow_s(nVal, szNum, 35, 10);
    return SetAttribute(doc, ele, pszName, szNum);
}

bool CXmlUtil::SetAttributeBool(const CXTPDOMDocumentPtr& doc, 
                                const CXTPDOMElementPtr& ele, 
                                const wchar_t* pszName, 
                                BOOL bVal)
{
    return SetAttribute(doc, ele, pszName, bVal ? L"true" : L"false");
}

std::wstring CXmlUtil::GetField(const CXTPDOMElementPtr& ele, 
                                const wchar_t* pszFieldName, 
                                const wchar_t* pszDefault)
{
    NL(pszDefault);
    std::wstring strValue (pszDefault);
    LocalHResult hr;
    
    XTPXML::IXMLDOMNodePtr pRet = NULL;
    GetChildIndex(ele, pszFieldName, 0, pRet);
    if (pRet != NULL)
    {
        BSTR bstr = NULL;
        hr = pRet->get_text(&bstr);
        if (bstr != NULL)
        {
            strValue = bstr;
            ::SysFreeString(bstr);
        }

        VARIANT_BOOL bHasChild;
        if (strValue.empty()
            && SUCCEEDED(hr = pRet->hasChildNodes(&bHasChild)) && bHasChild)
        {
            strValue = GetFieldCDATA(ele, pszFieldName, pszDefault);
        }
    }
    
    return strValue;
}

bool CXmlUtil::SetField(const CXTPDOMDocumentPtr& doc, 
                        const CXTPDOMElementPtr& ele, 
                        const wchar_t* pszFieldName, 
                        const wchar_t* pszValue)
{
    bool bRet = false;
    CXTPDOMElementPtr pNode;
    LocalHResult hr;

    if (GetChildOrAdd(pNode, doc, ele, pszFieldName))
    {
        bRet = SUCCEEDED(hr = pNode->put_text(_bstr_t(pszValue)));
    }
    
    return bRet;
}

bool CXmlUtil::GetFieldBool(const CXTPDOMElementPtr& ele, 
                            const wchar_t* pszFieldName, 
                            BOOL bDef)
{
    return GetFieldInt(ele, pszFieldName, bDef) != 0;
}

UINT CXmlUtil::GetFieldInt(const CXTPDOMElementPtr& ele, 
                           const wchar_t* pszFieldName, 
                           INT nDef)
{
    UINT nRet = nDef;
    std::wstring str = GetField(ele, pszFieldName);

    if (_wcsicmp(str.c_str(), L"true") == 0)
        return 1;
    if (_wcsicmp(str.c_str(), L"false") == 0)
        return 0;
    
    if (!str.empty())
    {
        wchar_t* endptr;
        if (_wcsnicmp(str.c_str(), L"0x", 2) == 0)
            nRet = wcstol(str.c_str(), &endptr, 16);
        else
            nRet = _wtoi(str.c_str());
    }
    
    return nRet;
}

bool CXmlUtil::SetFieldInt(const CXTPDOMDocumentPtr& doc, 
                           const CXTPDOMElementPtr& ele, 
                           const wchar_t* pszFieldName, 
                           INT nVal)
{
    wchar_t szNum[35];
    _itow_s(nVal, szNum, 35, 10);
    return SetField(doc, ele, pszFieldName, szNum);
}

bool CXmlUtil::SetFieldBool(const CXTPDOMDocumentPtr& doc, 
                            const CXTPDOMElementPtr& ele, 
                            const wchar_t* pszFieldName, 
                            BOOL bVal)
{
    return SetField(doc, ele, pszFieldName, bVal ? L"true" : L"false");
}

bool CXmlUtil::SetFieldHex(const CXTPDOMDocumentPtr& doc, 
                           const CXTPDOMElementPtr& ele, 
                           const wchar_t* pszFieldName, 
                           INT nVal, 
                           INT nDigits)
{
    wchar_t buf[20] = L"0x000000";
    
    if (nDigits > 0 && nDigits <= 6)
    {
        _itow_s(nVal, buf + 8, 20 - 8, 16);
        int nLen = lstrlenW(buf + 8);
        nLen = 6 + nLen - max(nDigits, nLen);
        for (int i = 0; buf[2+i-1] != 0; i++)
            buf[2+i] = buf[2+nLen+i];
    }
    else
    {
        _itow_s(nVal, buf + 2, 20 - 2, 16);
    }
    
    return SetField(doc, ele, pszFieldName, buf);
}

std::wstring CXmlUtil::GetTextCDATA(const CXTPDOMElementPtr& ele, const wchar_t* pszDefault)
{
    NL(pszDefault);
    std::wstring strValue (pszDefault);
    XTPXML::IXMLDOMNodePtr pCDATA;
    LocalHResult hr;

    if (ele != NULL)
    {
        hr = ele->get_firstChild(&pCDATA);
        if (pCDATA != NULL)
        {
            XTPXML::DOMNodeType type;
            if (SUCCEEDED(hr = pCDATA->get_nodeType(&type))
                && type == XTPXML::NODE_CDATA_SECTION)
            {
                BSTR bstr = NULL;
                hr = pCDATA->get_text(&bstr);
                if (bstr != NULL)
                {
                    strValue = bstr;
                    ::SysFreeString(bstr);
                }
            }
        }
    }

    return strValue;
}

std::wstring CXmlUtil::GetFieldCDATA(const CXTPDOMElementPtr& ele, 
                                     const wchar_t* pszFieldName, 
                                     const wchar_t* pszDefault)
{
    XTPXML::IXMLDOMNodePtr pRet = NULL;
    GetChildIndex(ele, pszFieldName, 0, pRet);
    return GetTextCDATA(pRet, pszDefault);
}

bool CXmlUtil::SetTextCDATA(const CXTPDOMDocumentPtr& doc, 
                            const CXTPDOMElementPtr& ele, 
                            const wchar_t* pszValue)
{
    bool bRet = false;
    VARIANT_BOOL bHasChild;
    LocalHResult hr;

    if (doc != NULL && ele != NULL)
    {
        if (SUCCEEDED(hr = ele->hasChildNodes(&bHasChild)) && bHasChild)
        {
            XTPXML::IXMLDOMNodePtr pCDATA, pNewNode;
            hr = ele->get_firstChild(&pCDATA);
            hr = ele->removeChild(pCDATA, &pNewNode);
        }

        VARIANT type;
        V_VT(&type) = VT_INT;
        V_INT(&type) = XTPXML::NODE_CDATA_SECTION;

        XTPXML::IXMLDOMNodePtr pCDATA = NULL;
        hr = doc->createNode(type, NULL, NULL, &pCDATA);
        if (pCDATA != NULL)
        {
            hr = pCDATA->put_text(_bstr_t(pszValue));
            bRet = SUCCEEDED(hr = ele->appendChild(pCDATA, NULL));
        }
    }

    return bRet;
}

bool CXmlUtil::SetFieldCDATA(const CXTPDOMDocumentPtr& doc, 
                             const CXTPDOMElementPtr& ele, 
                             const wchar_t* pszFieldName, 
                             const wchar_t* pszValue)
{
    bool bRet = false;
    CXTPDOMElementPtr pChild;

    if (GetChildOrAdd(pChild, doc, ele, pszFieldName))
    {
        bRet = SetTextCDATA(doc, pChild, pszValue);
    }
    
    return bRet;
}

bool CXmlUtil::GetAttributeBool(const CXTPDOMElementPtr& ele, 
                                const wchar_t* pszName, 
                                BOOL bDef)
{
    return GetAttributeInt(ele, pszName, bDef) != 0;
}

double CXmlUtil::GetAttributeFloat(const CXTPDOMElementPtr& ele, 
                                   const wchar_t* pszName, 
                                   double dDef, 
                                   std::wstring* pstrUnit)
{
    wchar_t* endptr = NULL;
    std::wstring str = GetAttribute(ele, pszName);
    if (!str.empty())
        dDef = wcstod(str.c_str(), &endptr);
    if (pstrUnit != NULL)
        *pstrUnit = (endptr != NULL) ? endptr : L"";
    return dDef;
}

bool CXmlUtil::SetAttributeFloat(const CXTPDOMDocumentPtr& doc, 
                                 const CXTPDOMElementPtr& ele, 
                                 const wchar_t* pszName, 
                                 double dVal, 
                                 const wchar_t* pszUnit, 
                                 int decimal)
{
    std::wstring str (RoundStr(dVal, decimal));
    str += pszUnit;
    return SetAttribute(doc, ele, pszName, str.c_str());
}

double CXmlUtil::GetFieldFloat(const CXTPDOMElementPtr& ele, 
                               const wchar_t* pszFieldName, 
                               double dDef, 
                               std::wstring* pstrUnit)
{
    wchar_t* endptr = NULL;
    std::wstring str = GetField(ele, pszFieldName);
    if (!str.empty())
        dDef = wcstod(str.c_str(), &endptr);
    if (pstrUnit != NULL)
        *pstrUnit = (endptr != NULL) ? endptr : L"";
    return dDef;
}

bool CXmlUtil::SetFieldFloat(const CXTPDOMDocumentPtr& doc, 
                             const CXTPDOMElementPtr& ele, 
                             const wchar_t* pszFieldName, 
                             double dVal, 
                             const wchar_t* pszUnit, 
                             int decimal)
{
    std::wstring str (RoundStr(dVal, decimal));
    str += pszUnit;
    return SetField(doc, ele, pszFieldName, str.c_str());
}

std::wstring CXmlUtil::RoundStr(double value, int decimal)
{
    wchar_t buf[65] = { 0 };
    
    wchar_t szFmt[] = L"%.2lf";
    if (decimal < 1) decimal = 1;
    if (decimal > 5) decimal = 5;
    szFmt[2] = (wchar_t)('0' + decimal);
#if _MSC_VER <= 1200 // VC6
    swprintf(buf, szFmt, value);
#else
    swprintf_s(buf, 65, szFmt, value);  
#endif
    
    wchar_t* p = wcschr(buf, '.');
    if (p != NULL)
    {
        int i = decimal;
        for (; i > 0 && p[i] == '0'; i--)
            p[i] = 0;
        if (p[i] == '.')
            p[i] = 0;
    }
    
    return buf;
}
