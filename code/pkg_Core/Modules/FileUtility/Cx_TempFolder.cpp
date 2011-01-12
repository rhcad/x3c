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

#include "StdAfx.h"
#include "Cx_TempFolder.h"
#include <Ix_FileUtility.h>
#include <Ix_FileTransaction.h>

std::vector<std::wstring> Cx_TempFolder::c_arrToDel;

Cx_TempFolder::Cx_TempFolder()
{
}

Cx_TempFolder::~Cx_TempFolder()
{
    DeleteFolder();
}

bool Cx_TempFolder::DeleteFolder()
{
    bool bRet = false;

    if (!m_wstrPath.empty())
    {
        Cx_Interface<Ix_FileTransaction> pIFTransaction(CLSID_FileTransaction);
        bRet = pIFTransaction->DeletePathFile(m_wstrPath.c_str());
        if (bRet)
            m_wstrPath.resize(0);
        else
            c_arrToDel.push_back(m_wstrPath);
    }

    return bRet;
}

void Cx_TempFolder::DeleteFolders()
{
    while (!c_arrToDel.empty())
    {
        std::wstring wstrPath(c_arrToDel.back());
        c_arrToDel.pop_back();
        FileUtility()->DeletePathFile(wstrPath.c_str());
    }
}

void Cx_TempFolder::SetRootPath(const std::wstring& wstrPath)
{
    m_wstrRootPath = wstrPath;
}

std::wstring Cx_TempFolder::CreateFolder(const std::wstring& wstrPrefix)
{
    ASSERT(!m_wstrRootPath.empty());

    Cx_Interface<Ix_FileUtility> pIFUtility(CLSID_FileUtility);

    DeleteFolder();
    for (int i = 1; i < 9999; i++)
    {
        wchar_t szFileName[MAX_PATH] = { 0 };
        swprintf_s(szFileName, _countof(szFileName), L"%s%03d", wstrPrefix.c_str(), i);
        std::wstring wstrPath (pIFUtility->RelToAbs(szFileName, false, m_wstrRootPath.c_str(), false));

        if (!pIFUtility->IsPathFileExists(wstrPath.c_str()))
        {
            m_wstrPath = wstrPath;
            break;
        }
    }

    bool bRet = !m_wstrPath.empty() && pIFUtility->CreateDirectory(m_wstrPath.c_str(), true);
    return bRet ? m_wstrPath : L"?";
}

std::wstring Cx_TempFolder::GetPath() const
{
    return m_wstrPath;
}

std::wstring Cx_TempFolder::CreateFileName(const std::wstring& wstrPrefix, 
                                           const std::wstring& wstrExtName)
{
    Cx_Interface<Ix_FileUtility> pIFUtility(CLSID_FileUtility);

    std::wstring strFileName;
    
    if (!m_wstrPath.empty())
    {
        strFileName = pIFUtility->CreateFileName(m_wstrPath, wstrPrefix, wstrExtName);
        strFileName = pIFUtility->RelToAbs(strFileName.c_str(), true, m_wstrPath.c_str(), false);
    }

    return strFileName;
}
