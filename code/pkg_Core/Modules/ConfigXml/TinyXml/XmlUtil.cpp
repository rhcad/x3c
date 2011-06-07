#include <UtilFunc/PluginInc.h>
#include "XmlUtil.h"
#include <UtilFunc/RoundStr.h>

// ticpp: http://ticpp.googlecode.com/svn/trunk
//
#include "tinyxml.cpp"
#include "tinyxmlerror.cpp"
#include "tinyxmlparser.cpp"

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

std::wstring CXmlUtil::GetLastErrorResult()
{
    return L"";
}

bool CXmlUtil::NewXMLFile(XMLDOMDocumentPtr& doc,
                          const wchar_t* rootName,
                          const wchar_t* encoding,
                          const wchar_t* nameSpace,
                          const wchar_t* comment)
{
    doc = NULL;

    return false;
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
    if (!IsNotEmpty(filename))
        return false;

    if (handler && handler->Decrypt(doc, filename))
    {
        ASSERT(doc != NULL);
        return true;
    }

    doc = NULL;

    return doc != NULL;
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
    if (!IsNotEmpty(filename))
        return false;

    if (handler)
    {
        handler->CryptFile(filename);
    }

    return false;
}

bool CXmlUtil::LoadXMLFromString(XMLDOMDocumentPtr& doc, const wchar_t* xmlstr)
{
    xmlstr = xmlstr ? wcschr(xmlstr, L'<') : NULL;
    if (NULL == xmlstr || 0 == xmlstr[0])
    {
        return false;
    }

    doc = NULL;

    return doc != NULL;
}

std::wstring CXmlUtil::GetXMLString(const XMLDOMDocumentPtr& doc)
{
    std::wstring str;

    return str;
}

std::wstring CXmlUtil::GetNodeXMLString(const XMLDOMElementPtr& ele)
{
    std::wstring str;

    return str;
}

std::wstring CXmlUtil::GetRootName(const XMLDOMDocumentPtr& doc)
{
    if (doc)
    {
    }
    return std::wstring();
}

bool CXmlUtil::CreateDocComment(const XMLDOMDocumentPtr& doc,
                                const wchar_t* comment)
{
    if (doc != NULL && IsNotEmpty(comment))
    {
    }

    return false;
}

bool CXmlUtil::CreateNodeComment(const XMLDOMDocumentPtr& doc,
                                 const XMLDOMElementPtr& ele,
                                 const wchar_t* comment)
{
    if (doc != NULL && ele != NULL && IsNotEmpty(comment))
    {
    }

    return false;
}

bool CXmlUtil::GetRoot(XMLDOMElementPtr& root,
                       const XMLDOMDocumentPtr& doc,
                       const wchar_t* rootName)
{
    return false;
}

static long GetChildIndex(const XMLDOMElementPtr& ele,
                          const wchar_t* childName,
                          long nMaxIndex,
                          XMLDOMElementPtr& pRet)
{
    pRet = NULL;

    if (!IsNotEmpty(childName) || NULL == ele)
        return 0;

    return 0;
}

long CXmlUtil::GetChildCount(const XMLDOMElementPtr& ele,
                             const wchar_t* childName)
{
    XMLDOMElementPtr pRet = NULL;
    return GetChildIndex(ele, childName, 99999, pRet);
}

bool CXmlUtil::GetChild(XMLDOMElementPtr& outEle,
                        const XMLDOMElementPtr& parent,
                        const wchar_t* childName,
                        long index)
{
    return outEle != NULL;
}

bool CXmlUtil::GetChildOrAdd(XMLDOMElementPtr& outEle,
                             const XMLDOMDocumentPtr& doc,
                             const XMLDOMElementPtr& parent,
                             const wchar_t* childName)
{
    outEle = NULL;

    if (!IsNotEmpty(childName) || NULL == parent)
        return false;

    XMLDOMElementPtr pRet = NULL;
    GetChildIndex(parent, childName, 0, pRet);

    if (NULL == outEle)
    {
    }

    return outEle != NULL;
}

bool CXmlUtil::AddChild(XMLDOMElementPtr& outEle,
                        const XMLDOMDocumentPtr& doc,
                        const XMLDOMElementPtr& ele,
                        const wchar_t* childName)
{
    XMLDOMElementPtr pRet = NULL;

    outEle = NULL;

    return outEle != NULL;
}

bool CXmlUtil::DelChild(const XMLDOMElementPtr& ele,
                        const wchar_t* childName,
                        long index)
{
    return false;
}

bool CXmlUtil::DelChild(const XMLDOMElementPtr& parent,
                        XMLDOMElementPtr& eleDel)
{
    bool bRet = false;

    if (parent != NULL && eleDel != NULL)
    {
    }

    return bRet;
}

long CXmlUtil::DelChildren(const XMLDOMElementPtr& ele,
                           const wchar_t* childName,
                           const wchar_t* attrName, const wchar_t* attrValue)
{
    XMLDOMElementPtr pSubItem;
    long nDel = 0;
    long nCount = GetChildCount(ele, childName);
    for (long i = nCount - 1; i >= 0; i--)
    {
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
    std::wstring wstrTagName;

    return wstrTagName;
}

std::wstring CXmlUtil::GetText(const XMLDOMElementPtr& ele, const wchar_t* defValue)
{
    NL(defValue);
    std::wstring strText(defValue);

    return strText;
}

bool CXmlUtil::SetText(const XMLDOMElementPtr& ele, const wchar_t* text)
{
    return false;
}

bool CXmlUtil::SetTextW(const XMLDOMElementPtr& ele, const wchar_t* text)
{
    return false;
}

bool CXmlUtil::GetParentNode(XMLDOMElementPtr& parent, XMLDOMElementPtr& node)
{
    XMLDOMElementPtr tmpnode = NULL;

    return parent != NULL;
}

bool CXmlUtil::DelAttribute(const XMLDOMElementPtr& ele,
                            const wchar_t* name)
{
    return false;
}

std::wstring CXmlUtil::GetAttribute(const XMLDOMElementPtr& ele,
                                    const wchar_t* name,
                                    const wchar_t* defValue)
{
    NL(defValue);
    std::wstring strValue (defValue);
    return strValue;
}

bool CXmlUtil::SetAttribute(const XMLDOMDocumentPtr&,
                            const XMLDOMElementPtr& ele,
                            const wchar_t* name,
                            const wchar_t* value)
{
    bool bRet = false;

    if (IsNotEmpty(name) && ele != NULL)
    {
        bRet = false;
    }

    return bRet;
}

int CXmlUtil::GetAttributeInt(const XMLDOMElementPtr& ele,
                               const wchar_t* name,
                               int defValue)
{
    int nRet = defValue;
    std::wstring str = GetAttribute(ele, name);

    if (_wcsicmp(str.c_str(), L"true") == 0)
        return 1;
    if (_wcsicmp(str.c_str(), L"false") == 0)
        return 0;

    if (!str.empty())
        nRet = wcstol(str.c_str(), NULL, 10);

    return nRet;
}

bool CXmlUtil::SetAttributeInt(const XMLDOMDocumentPtr& doc,
                               const XMLDOMElementPtr& ele,
                               const wchar_t* name,
                               int value)
{
    wchar_t szNum[35];
    _itow_s(value, szNum, 35, 10);
    return SetAttribute(doc, ele, name, szNum);
}

bool CXmlUtil::SetAttributeBool(const XMLDOMDocumentPtr& doc,
                                const XMLDOMElementPtr& ele,
                                const wchar_t* name,
                                int value)
{
    return SetAttribute(doc, ele, name, value ? L"true" : L"false");
}

std::wstring CXmlUtil::GetField(const XMLDOMElementPtr& ele,
                                const wchar_t* fieldName,
                                const wchar_t* defValue)
{
    NL(defValue);
    std::wstring strValue (defValue);
    XMLDOMElementPtr pRet = NULL;
    GetChildIndex(ele, fieldName, 0, pRet);
    if (pRet != NULL)
    {
    }

    return strValue;
}

bool CXmlUtil::SetField(const XMLDOMDocumentPtr& doc,
                        const XMLDOMElementPtr& ele,
                        const wchar_t* fieldName,
                        const wchar_t* value)
{
    bool bRet = false;
    XMLDOMElementPtr eleOld;

    if (GetChildOrAdd(eleOld, doc, ele, fieldName))
    {
    }

    return bRet;
}

bool CXmlUtil::GetFieldBool(const XMLDOMElementPtr& ele,
                            const wchar_t* fieldName,
                            int defValue)
{
    return GetFieldInt(ele, fieldName, defValue) != 0;
}

int CXmlUtil::GetFieldInt(const XMLDOMElementPtr& ele,
                           const wchar_t* fieldName,
                           int defValue)
{
    int nRet = defValue;
    std::wstring str = GetField(ele, fieldName);

    if (_wcsicmp(str.c_str(), L"true") == 0)
        return 1;
    if (_wcsicmp(str.c_str(), L"false") == 0)
        return 0;

    if (!str.empty())
    {
        wchar_t* endptr;
        nRet = wcstol(str.c_str(), &endptr,
            _wcsnicmp(str.c_str(), L"0x", 2) == 0 ? 16 : 10);
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
                            int value)
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
        int nLen = wcslen(buf + 8);
        nLen = 6 + nLen - (digits > nLen ? digits : nLen);
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
    XMLDOMElementPtr pCDATA;
    if (ele != NULL)
    {
    }

    return strValue;
}

std::wstring CXmlUtil::GetFieldCDATA(const XMLDOMElementPtr& ele,
                                     const wchar_t* fieldName,
                                     const wchar_t* defValue)
{
    XMLDOMElementPtr pRet = NULL;
    GetChildIndex(ele, fieldName, 0, pRet);
    return GetTextCDATA(pRet, defValue);
}

bool CXmlUtil::SetTextCDATA(const XMLDOMDocumentPtr& doc,
                            const XMLDOMElementPtr& ele,
                            const wchar_t* value)
{
    bool bRet = false;
    if (doc != NULL && ele != NULL)
    {
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
                                const wchar_t* name,
                                int defValue)
{
    return GetAttributeInt(ele, name, defValue) != 0;
}

double CXmlUtil::GetAttributeFloat(const XMLDOMElementPtr& ele,
                                   const wchar_t* name,
                                   double defValue,
                                   std::wstring* unitName)
{
    wchar_t* endptr = NULL;
    std::wstring str = GetAttribute(ele, name);
    if (!str.empty())
        defValue = wcstod(str.c_str(), &endptr);
    if (unitName != NULL)
        *unitName = (endptr != NULL) ? endptr : L"";
    return defValue;
}

bool CXmlUtil::SetAttributeFloat(const XMLDOMDocumentPtr& doc,
                                 const XMLDOMElementPtr& ele,
                                 const wchar_t* name,
                                 double value,
                                 const wchar_t* unitName,
                                 int decimal)
{
    std::wstring str (RoundStr(value, decimal));
    str += unitName;
    return SetAttribute(doc, ele, name, str.c_str());
}

double CXmlUtil::GetFieldFloat(const XMLDOMElementPtr& ele,
                               const wchar_t* fieldName,
                               double defValue,
                               std::wstring* unitName)
{
    wchar_t* endptr = NULL;
    std::wstring str = GetField(ele, fieldName);
    if (!str.empty())
        defValue = wcstod(str.c_str(), &endptr);
    if (unitName != NULL)
        *unitName = (endptr != NULL) ? endptr : L"";
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
