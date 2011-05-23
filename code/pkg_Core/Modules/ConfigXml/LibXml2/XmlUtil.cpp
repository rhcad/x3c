// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// XmlUtil.cpp: implementation of the CXmlUtil class.
//

#include <PluginInc.h>
#include "XmlUtil.h"

#if !defined(_MSC_VER) || _MSC_VER < 1400 // not VC8
#define _itow_s(defValue, szNum, nSize, nRadix) _itow(defValue, szNum, nRadix)
#endif // _MSC_VER

static int s_hr = S_OK;

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
    int m_hr;

    LocalHResult(int hr = S_OK) : m_hr(hr)
    {
    }
    ~LocalHResult()
    {
        InterlockedExchange((LPLONG)&s_hr, m_hr);
    }
    int& operator=(int hr)
    {
        m_hr = hr;
        return m_hr;
    }
    operator int&()
    {
        return m_hr;
    }
};

int CXmlUtil::GetLastErrorResult()
{
    return s_hr;
}

bool CXmlUtil::NewXMLFile(XMLDOMDocumentPtr& doc, 
                          const wchar_t* rootName, 
                          const wchar_t* encoding, 
                          const wchar_t* nameSpace, 
                          const wchar_t* comment)
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

    XMLDOMNodePtr pDocNode (doc);
    
    std::wstring strHeader = L"version=\"1.0\" encoding=\"";
    strHeader += encoding;
    strHeader += L"\"";
    XMLDOMProcessingInstructionPtr pHeader;
    hr = doc->createProcessingInstruction(
        _bstr_t(L"xml"), _bstr_t(strHeader.c_str()), &pHeader);
    hr = pDocNode->appendChild(pHeader, NULL);

    if (IsNotEmpty(comment))
    {
        XMLDOMComment* pComment = NULL;
        hr = doc->createComment(_bstr_t(comment), &pComment);
        if (pComment != NULL)
        {
            hr = doc->appendChild(XMLDOMNodePtr(pComment), NULL);
            pComment->Release();
        }
    }
    
    // Create root node
    if (IsNotEmpty(rootName))
    {
        VARIANT type;
        V_VT(&type) = VT_int;
        V_int(&type) = XML::NODE_ELEMENT;
        XMLDOMNodePtr pRoot;
        hr = doc->createNode(type, _bstr_t(rootName), _bstr_t(nameSpace), &pRoot);
        hr = pDocNode->appendChild(pRoot, NULL);
    }
    
    return true;
}

bool CXmlUtil::NewXMLFile2(XMLDOMDocumentPtr& doc, 
                           XMLDOMElementPtr& root, 
                           const wchar_t* rootName, 
                           const wchar_t* encoding, 
                           const wchar_t* nameSpace)
{
    root = NULL;
    if (NewXMLFile(doc, rootName, encoding, nameSpace))
    {
        if (!GetRoot(root, doc, rootName))
            doc = NULL;
    }
    return doc != NULL;
}

bool CXmlUtil::LoadXMLFile(XMLDOMDocumentPtr& doc, 
                           const wchar_t* filename, 
                           IXmlFileCrypt* handler)
{
    LocalHResult hr;
    if (!IsNotEmpty(filename))
        return false;

    if (handler && handler->Decrypt(doc, filename))
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
    V_BSTR(&vt) = ::SysAllocString(filename);
    
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

bool CXmlUtil::LoadXMLFile(XMLDOMDocumentPtr& doc, 
                           const wchar_t* filename, 
                           XMLDOMElementPtr& root, 
                           const wchar_t* rootName, 
                           IXmlFileCrypt* handler)
{
    root = NULL;
    if (LoadXMLFile(doc, filename, handler))
    {
        if (!GetRoot(root, doc, rootName))
            doc = NULL;
    }
    return doc != NULL;
}

bool CXmlUtil::SaveXMLFile(const XMLDOMDocumentPtr& doc, 
                           const wchar_t* filename, 
                           IXmlFileCrypt* handler)
{
    LocalHResult hr = E_INVALIDARG;
    if (!IsNotEmpty(filename))
        return false;

    VARIANT vt;
    V_VT(&vt) = VT_BSTR;
    V_BSTR(&vt) = ::SysAllocString(filename);
    
    try
    {
        hr = doc->save(vt);
    }
    catch (...)
    {
        hr = E_FAIL;
    }
    
    if (vt.bstrVal != NULL)
    {
        ::SysFreeString(vt.bstrVal);
    }

    if (SUCCEEDED(hr) && handler)
    {
        handler->CryptFile(filename);
    }
    
    return SUCCEEDED(hr);
}

bool CXmlUtil::LoadXMLFromString(XMLDOMDocumentPtr& doc, const wchar_t* xmlstr)
{
    LocalHResult hr;

    xmlstr = xmlstr ? StrChrA(xmlstr, '<') : NULL;
    if (NULL == xmlstr || 0 == xmlstr[0])
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
    if (FAILED(hr = doc->loadXML(_bstr_t(xmlstr), &bRet)) || !bRet)
    {
        doc = NULL;
    }
    
    return doc != NULL;
}

bool CXmlUtil::LoadXMLFromString(XMLDOMDocumentPtr& doc, const wchar_t* xmlstr)
{
    LocalHResult hr;

    xmlstr = xmlstr ? StrChrW(xmlstr, L'<') : NULL;
    if (NULL == xmlstr || 0 == xmlstr[0])
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
    if (FAILED(hr = doc->loadXML(_bstr_t(xmlstr), &bRet)) || !bRet)
    {
        doc = NULL;
    }
    
    return doc != NULL;
}

std::wstring CXmlUtil::GetXMLString(const XMLDOMDocumentPtr& doc)
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

std::wstring CXmlUtil::GetNodeXMLString(const XMLDOMElementPtr& ele)
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

std::wstring CXmlUtil::GetRootName(const XMLDOMDocumentPtr& doc)
{
    LocalHResult hr;
    if (doc)
    {
        XMLDOMElementPtr ele;
        hr = doc->get_documentElement(&ele);
        return GetTagName(ele);
    }
    return std::wstring();
}

bool CXmlUtil::CreateDocComment(const XMLDOMDocumentPtr& doc, 
                                const wchar_t* comment)
{
    LocalHResult hr;
    if (doc != NULL && IsNotEmpty(comment))
    {
        XMLDOMElementPtr ele;
        hr = doc->get_documentElement(&ele);

        XMLDOMComment* pComment = NULL;
        hr = doc->createComment(_bstr_t(comment), &pComment);
        if (pComment != NULL)
        {
            hr = doc->insertBefore(XMLDOMNodePtr(pComment), _variant_t(ele), NULL);
            pComment->Release();

            return true;
        }
    }

    return false;
}

bool CXmlUtil::CreateNodeComment(const XMLDOMDocumentPtr& doc, 
                                 const XMLDOMElementPtr& ele, 
                                 const wchar_t* comment)
{
    LocalHResult hr;
    if (doc != NULL && ele != NULL && IsNotEmpty(comment))
    {
        XMLDOMComment* pComment = NULL;
        hr = doc->createComment(_bstr_t(comment), &pComment);
        if (pComment != NULL)
        {
            hr = ele->appendChild(XMLDOMNodePtr(pComment), NULL);
            pComment->Release();

            return true;
        }
    }

    return false;
}

bool CXmlUtil::GetRoot(XMLDOMElementPtr& root, 
                       const XMLDOMDocumentPtr& doc, 
                       const wchar_t* rootName)
{
    LocalHResult hr;
    XMLDOMNodeListPtr nl;
    long nCount = 0;
    XMLDOMNodePtr pRet = NULL;
    
    if (doc != NULL)
        hr = doc->getElementsByTagName(_bstr_t(rootName), &nl);
    
    if (nl != NULL)
    {
        hr = nl->get_length(&nCount);
        if (nCount > 0)
            hr = nl->get_item(0, &pRet);
    }
    
    root = pRet;

    return pRet != NULL;
}

static long GetChildIndex(const XMLDOMElementPtr& ele, 
                          const wchar_t* childName, 
                          long nMaxIndex, 
                          XMLDOMNodePtr& pRet)
{
    LocalHResult hr;
    pRet = NULL;

    if (!IsNotEmpty(childName) || NULL == ele)
        return 0;

    long n = 0, nCount = 0;
    XMLDOMNodeListPtr nl;

    hr = ele->get_childNodes(&nl);
    if (nl != NULL)
    {
        hr = nl->get_length(&n);
        for (int i = 0; i < n; i++)
        {
            XMLDOMNodePtr pNode;
            hr = nl->get_item(i, &pNode);
            if (NULL == pNode)
                continue;

            BSTR bstr = NULL;
            hr = pNode->get_nodeName(&bstr);
            if (bstr != NULL && _wcsicmp(bstr, childName) == 0)
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

long CXmlUtil::GetChildCount(const XMLDOMElementPtr& ele, 
                             const wchar_t* childName)
{
    XMLDOMNodePtr pRet = NULL;
    return GetChildIndex(ele, childName, 99999, pRet);
}

bool CXmlUtil::GetChild(XMLDOMElementPtr& outEle, 
                        const XMLDOMElementPtr& parent, 
                        const wchar_t* childName, 
                        long index)
{
    XMLDOMNodePtr pRet = NULL;
    GetChildIndex(parent, childName, index, pRet);
    outEle = pRet;
    return outEle != NULL;
}

bool CXmlUtil::GetChildOrAdd(XMLDOMElementPtr& outEle, 
                             const XMLDOMDocumentPtr& doc, 
                             const XMLDOMElementPtr& parent, 
                             const wchar_t* childName)
{
    LocalHResult hr;
    outEle = NULL;

    if (!IsNotEmpty(childName) || NULL == parent)
        return false;

    XMLDOMNodePtr pRet = NULL;
    GetChildIndex(parent, childName, 0, pRet);
    outEle = pRet;

    if (NULL == outEle)
    {
        hr = doc->createElement(_bstr_t(childName), &outEle);
        hr = parent->appendChild(outEle, NULL);
    }

    return outEle != NULL;
}

bool CXmlUtil::AddChild(XMLDOMElementPtr& outEle, 
                        const XMLDOMDocumentPtr& doc, 
                        const XMLDOMElementPtr& ele, 
                        const wchar_t* childName)
{
    LocalHResult hr;
    XMLDOMElementPtr pRet = NULL;
    
    outEle = NULL;
    if (doc != NULL && ele != NULL && IsNotEmpty(childName))
        hr = doc->createElement(_bstr_t(childName), &pRet);
    if (pRet != NULL)
    {
        hr = ele->appendChild(pRet, NULL);
        outEle = pRet;
    }
    
    return outEle != NULL;
}

bool CXmlUtil::DelChild(const XMLDOMElementPtr& ele, 
                        const wchar_t* childName, 
                        long index)
{
    LocalHResult hr;
    XMLDOMElementPtr pItem;
    bool bRet = GetChild(pItem, ele, childName, index);

    if (bRet)
    {
        hr = ele->removeChild(pItem, NULL);
        pItem = NULL;
    }

    return bRet;
}

bool CXmlUtil::DelChild(const XMLDOMElementPtr& parent, 
                        XMLDOMElementPtr& eleDel)
{
    LocalHResult hr;
    bool bRet = false;

    if (parent != NULL && eleDel != NULL)
    {
        XMLDOMNodePtr pNode;
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

long CXmlUtil::DelChildren(const XMLDOMElementPtr& ele, 
                           const wchar_t* childName, 
                           const wchar_t* attrName, const wchar_t* attrValue)
{
    LocalHResult hr;
    XMLDOMElementPtr pSubItem;
    long nDel = 0;
    long nCount = GetChildCount(ele, childName);
    for (long i = nCount - 1; i >= 0; i--)
    {
        if (GetChild(pSubItem, ele, childName, i))
        {
            if (attrName != NULL && attrValue != NULL
                && _wcsicmp(GetAttribute(pSubItem, attrName).c_str(), attrValue) != 0)
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

long CXmlUtil::FindElement(XMLDOMElementPtr& outEle, 
                           const XMLDOMElementPtr& parent, 
                           const wchar_t* childName, 
                           const wchar_t* fieldName, 
                           const wchar_t* value)
{
    NL(value);
    XMLDOMElementPtr ele;
    long nCount = GetChildCount(parent, childName);
    long i;
    
    outEle = NULL;
    for (i = nCount - 1; i >= 0; i--)
    {
        if (GetChild(ele, parent, childName, i)
            && _wcsicmp(GetField(ele, fieldName).c_str(), value) == 0)
        {
            outEle = ele;
            break;
        }
    }
    
    return i;
}

long CXmlUtil::FindElementByAttr(XMLDOMElementPtr& outEle, 
                                 const XMLDOMElementPtr& parent, 
                                 const wchar_t* childName, 
                                 const wchar_t* attr1, 
                                 const wchar_t* value1, 
                                 const wchar_t* attr2, 
                                 const wchar_t* value2)
{
    NL(attr1); NL(value1); NL(attr2); NL(value2);
    XMLDOMElementPtr ele;
    long i = GetChildCount(parent, childName);
    
    outEle = NULL;
    while (--i >= 0)
    {
        if (GetChild(ele, parent, childName, i))
        {
            if (_wcsicmp(GetAttribute(ele, attr1).c_str(), value1) == 0
                && (!IsNotEmpty(attr2) || _wcsicmp(
                    GetAttribute(ele, attr2).c_str(), value2) == 0))
            {
                outEle = ele;
                break;
            }
        }
    }
    
    return i;
}

std::wstring CXmlUtil::GetTagName(const XMLDOMElementPtr& ele)
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

std::wstring CXmlUtil::GetText(const XMLDOMNodePtr& pNode, const wchar_t* defValue)
{
    LocalHResult hr;
    NL(defValue);
    std::wstring strText(defValue);
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
            strText = GetTextCDATA(pNode, defValue);
        }
    }
    
    return strText;
}

bool CXmlUtil::SetText(const XMLDOMNodePtr& pNode, const wchar_t* pszText)
{
    LocalHResult hr;
    bool bRet = false;
    if (pNode != NULL)
        bRet = SUCCEEDED(hr = pNode->put_text(_bstr_t(pszText)));
    return bRet;
}

bool CXmlUtil::SetTextW(const XMLDOMNodePtr& pNode, const wchar_t* pszText)
{
    LocalHResult hr;
    bool bRet = false;
    if (pNode != NULL)
        bRet = SUCCEEDED(hr = pNode->put_text(_bstr_t(pszText)));
    return bRet;
}

bool CXmlUtil::DelAttribute(const XMLDOMElementPtr& ele, 
                            const wchar_t* pszName)
{
    LocalHResult hr;
    XMLDOMAttributePtr pNode = NULL;

    if (ele != NULL && IsNotEmpty(pszName))
        hr = ele->getAttributeNode(_bstr_t(pszName), &pNode);

    if (pNode != NULL)
    {
        XMLDOMElementPtr pItem(pNode);
        return SUCCEEDED(hr = ele->removeChild(pItem, NULL));
    }

    return false;
}

std::wstring CXmlUtil::GetAttribute(const XMLDOMElementPtr& ele, 
                                    const wchar_t* pszName, 
                                    const wchar_t* defValue)
{
    NL(defValue);
    std::wstring strValue (defValue);
    XMLDOMAttributePtr pNode = NULL;
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

bool CXmlUtil::SetAttribute(const XMLDOMDocumentPtr&, 
                            const XMLDOMElementPtr& ele, 
                            const wchar_t* pszName, 
                            const wchar_t* value)
{
    LocalHResult hr;
    bool bRet = false;
    
    if (IsNotEmpty(pszName) && ele != NULL)
    {
        hr = ele->setAttribute(_bstr_t(pszName), _variant_t(value));
        bRet = SUCCEEDED(hr);
    }
    
    return bRet;
}

int CXmlUtil::GetAttributeInt(const XMLDOMElementPtr& ele, 
                               const wchar_t* pszName, 
                               int defValue)
{
    int nRet = defValue;
    std::wstring str = GetAttribute(ele, pszName);

    if (_wcsicmp(str.c_str(), L"true") == 0)
        return 1;
    if (_wcsicmp(str.c_str(), L"false") == 0)
        return 0;

    if (!str.empty())
        nRet = _wtoi(str.c_str());

    return nRet;
}

bool CXmlUtil::SetAttributeInt(const XMLDOMDocumentPtr& doc, 
                               const XMLDOMElementPtr& ele, 
                               const wchar_t* pszName, 
                               int value)
{
    wchar_t szNum[35];
    _itow_s(value, szNum, 35, 10);
    return SetAttribute(doc, ele, pszName, szNum);
}

bool CXmlUtil::SetAttributeBool(const XMLDOMDocumentPtr& doc, 
                                const XMLDOMElementPtr& ele, 
                                const wchar_t* pszName, 
                                BOOL value)
{
    return SetAttribute(doc, ele, pszName, value ? L"true" : L"false");
}

std::wstring CXmlUtil::GetField(const XMLDOMElementPtr& ele, 
                                const wchar_t* fieldName, 
                                const wchar_t* defValue)
{
    NL(defValue);
    std::wstring strValue (defValue);
    LocalHResult hr;
    
    XMLDOMNodePtr pRet = NULL;
    GetChildIndex(ele, fieldName, 0, pRet);
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
            strValue = GetFieldCDATA(ele, fieldName, defValue);
        }
    }
    
    return strValue;
}

bool CXmlUtil::SetField(const XMLDOMDocumentPtr& doc, 
                        const XMLDOMElementPtr& ele, 
                        const wchar_t* fieldName, 
                        const wchar_t* value)
{
    bool bRet = false;
    XMLDOMElementPtr pNode;
    LocalHResult hr;

    if (GetChildOrAdd(pNode, doc, ele, fieldName))
    {
        bRet = SUCCEEDED(hr = pNode->put_text(_bstr_t(value)));
    }
    
    return bRet;
}

bool CXmlUtil::GetFieldBool(const XMLDOMElementPtr& ele, 
                            const wchar_t* fieldName, 
                            BOOL defValue)
{
    return GetFieldInt(ele, fieldName, defValue) != 0;
}

Uint CXmlUtil::GetFieldInt(const XMLDOMElementPtr& ele, 
                           const wchar_t* fieldName, 
                           int defValue)
{
    Uint nRet = defValue;
    std::wstring str = GetField(ele, fieldName);

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

bool CXmlUtil::SetFieldInt(const XMLDOMDocumentPtr& doc, 
                           const XMLDOMElementPtr& ele, 
                           const wchar_t* fieldName, 
                           int value)
{
    wchar_t szNum[35];
    _itow_s(value, szNum, 35, 10);
    return SetField(doc, ele, fieldName, szNum);
}

bool CXmlUtil::SetFieldBool(const XMLDOMDocumentPtr& doc, 
                            const XMLDOMElementPtr& ele, 
                            const wchar_t* fieldName, 
                            BOOL value)
{
    return SetField(doc, ele, fieldName, value ? L"true" : L"false");
}

bool CXmlUtil::SetFieldHex(const XMLDOMDocumentPtr& doc, 
                           const XMLDOMElementPtr& ele, 
                           const wchar_t* fieldName, 
                           int value, 
                           int digits)
{
    wchar_t buf[20] = L"0x000000";
    
    if (digits > 0 && digits <= 6)
    {
        _itow_s(value, buf + 8, 20 - 8, 16);
        int nLen = lstrlenW(buf + 8);
        nLen = 6 + nLen - max(digits, nLen);
        for (int i = 0; buf[2+i-1] != 0; i++)
            buf[2+i] = buf[2+nLen+i];
    }
    else
    {
        _itow_s(value, buf + 2, 20 - 2, 16);
    }
    
    return SetField(doc, ele, fieldName, buf);
}

std::wstring CXmlUtil::GetTextCDATA(const XMLDOMElementPtr& ele, const wchar_t* defValue)
{
    NL(defValue);
    std::wstring strValue (defValue);
    XMLDOMNodePtr pCDATA;
    LocalHResult hr;

    if (ele != NULL)
    {
        hr = ele->get_firstChild(&pCDATA);
        if (pCDATA != NULL)
        {
            XMLDOMNodeType type;
            if (SUCCEEDED(hr = pCDATA->get_nodeType(&type))
                && type == XML::NODE_CDATA_SECTION)
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

std::wstring CXmlUtil::GetFieldCDATA(const XMLDOMElementPtr& ele, 
                                     const wchar_t* fieldName, 
                                     const wchar_t* defValue)
{
    XMLDOMNodePtr pRet = NULL;
    GetChildIndex(ele, fieldName, 0, pRet);
    return GetTextCDATA(pRet, defValue);
}

bool CXmlUtil::SetTextCDATA(const XMLDOMDocumentPtr& doc, 
                            const XMLDOMElementPtr& ele, 
                            const wchar_t* value)
{
    bool bRet = false;
    VARIANT_BOOL bHasChild;
    LocalHResult hr;

    if (doc != NULL && ele != NULL)
    {
        if (SUCCEEDED(hr = ele->hasChildNodes(&bHasChild)) && bHasChild)
        {
            XMLDOMNodePtr pCDATA, pNewNode;
            hr = ele->get_firstChild(&pCDATA);
            hr = ele->removeChild(pCDATA, &pNewNode);
        }

        VARIANT type;
        V_VT(&type) = VT_int;
        V_int(&type) = XML::NODE_CDATA_SECTION;

        XMLDOMNodePtr pCDATA = NULL;
        hr = doc->createNode(type, NULL, NULL, &pCDATA);
        if (pCDATA != NULL)
        {
            hr = pCDATA->put_text(_bstr_t(value));
            bRet = SUCCEEDED(hr = ele->appendChild(pCDATA, NULL));
        }
    }

    return bRet;
}

bool CXmlUtil::SetFieldCDATA(const XMLDOMDocumentPtr& doc, 
                             const XMLDOMElementPtr& ele, 
                             const wchar_t* fieldName, 
                             const wchar_t* value)
{
    bool bRet = false;
    XMLDOMElementPtr pChild;

    if (GetChildOrAdd(pChild, doc, ele, fieldName))
    {
        bRet = SetTextCDATA(doc, pChild, value);
    }
    
    return bRet;
}

bool CXmlUtil::GetAttributeBool(const XMLDOMElementPtr& ele, 
                                const wchar_t* pszName, 
                                BOOL defValue)
{
    return GetAttributeInt(ele, pszName, defValue) != 0;
}

double CXmlUtil::GetAttributeFloat(const XMLDOMElementPtr& ele, 
                                   const wchar_t* pszName, 
                                   double defValue, 
                                   std::wstring* pstrUnit)
{
    wchar_t* endptr = NULL;
    std::wstring str = GetAttribute(ele, pszName);
    if (!str.empty())
        defValue = wcstod(str.c_str(), &endptr);
    if (pstrUnit != NULL)
        *pstrUnit = (endptr != NULL) ? endptr : L"";
    return defValue;
}

bool CXmlUtil::SetAttributeFloat(const XMLDOMDocumentPtr& doc, 
                                 const XMLDOMElementPtr& ele, 
                                 const wchar_t* pszName, 
                                 double value, 
                                 const wchar_t* unitName, 
                                 int decimal)
{
    std::wstring str (RoundStr(value, decimal));
    str += unitName;
    return SetAttribute(doc, ele, pszName, str.c_str());
}

double CXmlUtil::GetFieldFloat(const XMLDOMElementPtr& ele, 
                               const wchar_t* fieldName, 
                               double defValue, 
                               std::wstring* pstrUnit)
{
    wchar_t* endptr = NULL;
    std::wstring str = GetField(ele, fieldName);
    if (!str.empty())
        defValue = wcstod(str.c_str(), &endptr);
    if (pstrUnit != NULL)
        *pstrUnit = (endptr != NULL) ? endptr : L"";
    return defValue;
}

bool CXmlUtil::SetFieldFloat(const XMLDOMDocumentPtr& doc, 
                             const XMLDOMElementPtr& ele, 
                             const wchar_t* fieldName, 
                             double value, 
                             const wchar_t* unitName, 
                             int decimal)
{
    std::wstring str (RoundStr(value, decimal));
    str += unitName;
    return SetField(doc, ele, fieldName, str.c_str());
}
