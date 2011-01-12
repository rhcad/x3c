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

#ifndef _X3_CONFIGXML_CONFIGXMLIMPL_H
#define _X3_CONFIGXML_CONFIGXMLIMPL_H

#include <comdef.h>

interface IFileCryptHandler;
interface Ix_ConfigData;

struct ConfigXmlImpl
{
    long                m_nTransaction;
    ULONG               m_nModifiedCount;
    std::wstring        m_strFileName;
    std::wstring        m_strRootName;
    std::wstring        m_strEncoding;
    std::wstring        m_strNameSpace;
    std::wstring        m_strSchemaLocation;
    bool                m_bModified;
    bool                m_bNeedLoad;
    CXTPDOMDocumentPtr  m_xmlDoc;
    CXTPDOMElementPtr   m_xmlRoot;
    IFileCryptHandler*  m_pCryptHandler;
    Ix_ConfigData*      m_pThis;
    bool                m_bInitCom;

    ConfigXmlImpl(Ix_ConfigData* pThis) : m_pThis(pThis)
    {
        m_nTransaction = 0;
        m_nModifiedCount = 0;
        m_bModified = false;
        m_bNeedLoad = true;
        m_strEncoding = L"UTF-8";
        m_pCryptHandler = NULL;
        m_bInitCom = SUCCEEDED(CoInitializeEx(NULL, COINIT_MULTITHREADED));
    }

    ~ConfigXmlImpl()
    {
        m_xmlRoot.Release();
        m_xmlDoc.Release();
        if (m_bInitCom)
        {
            CoUninitialize();
        }
    }

    CXTPDOMElementPtr GetRoot()
    {
        if (NULL == m_xmlRoot)
            Reload();
        return m_xmlRoot;
    }

    void SetModified(bool bModified = true)
    {
        m_bModified = bModified;
        if (bModified)
            m_nModifiedCount++;
    }

    bool Reload();
    void NewDoc();
    CXTPDOMElementPtr GetParentNode(Ix_ConfigSection* pParent, std::wstring& strSection);
    CXTPDOMElementPtr GetParentNode(CXTPDOMElementPtr xmlParent, std::wstring& strSection);
};

#endif // _X3_CONFIGXML_CONFIGXMLIMPL_H
