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
//
// Changes:
// 2010-01-12, Zhang Yun Gui: Remove Ix_FileUtility.
//      Open access connection readonly if file is readonly.
//

#include "StdAfx.h"
#include "Cx_ConfigFactory.h"
#include "Cx_CfgDatabase.h"
#include "ClsID_Internal.h"
#include "Ix_InitDatabase.h"
#include "Cx_SQLParser.h"

Cx_ConfigFactory::Cx_ConfigFactory()
{
}

Cx_ConfigFactory::~Cx_ConfigFactory()
{
}

Cx_Ptr Cx_ConfigFactory::OpenAccessDB(const std::wstring& filename, 
                                      const std::wstring& user, 
                                      const std::wstring& password)
{
    DWORD attr = GetFileAttributesW(filename.c_str());
    bool readonly = (attr & FILE_ATTRIBUTE_READONLY) != 0;

    if (attr == (DWORD)-1)
    {
        LOG_ERROR2(LOGHEAD L"IDS_NO_FILE", filename);
        return Cx_Ptr();
    }
    if (readonly)
    {
        LOG_INFO2(LOGHEAD L"IDS_FILE_READONLY", filename);
    }

    std::wostringstream conn;

    if (StrCmpIW(PathFindExtensionW(filename.c_str()), L".accdb") == 0)
    {
        conn << L"Provider=Microsoft.ACE.OLEDB.12.0;" ;
    }
    else
    {
        conn << L"Provider=Microsoft.Jet.OLEDB.4.0;" ;
    }
    conn << L"Data Source=" << filename << L";" ;

    if (!user.empty())
    {
        conn << L"User Id=" << user << L";" ;
    }
    if (password.empty())
    {
        conn << L"Password=" << password << L";" ;
    }
    else
    {
        conn << L"Jet OLEDB:Database Password=" << password << L";" ;
    }

    Cx_Interface<Ix_InitDatabase> pIFDB(CLSID_CfgDatabase);
    ASSERT(pIFDB.IsNotNull());
    Ix_SQLParser* pSQLParser = new SQLParser_Access();

    return pIFDB->OpenConnection(conn.str(), pSQLParser, readonly)
        ? Cx_Ptr(pIFDB) : Cx_Ptr();
}

Cx_Ptr Cx_ConfigFactory::OpenSQLServerDB(const std::wstring& server, 
                                         const std::wstring& database, 
                                         const std::wstring& user, 
                                         const std::wstring& password)
{
    if (server.empty() || database.empty())
    {
        return Cx_Ptr();
    }

    std::wostringstream conn;

    conn << L"Provider=SQLOLEDB;"
        << L"Data Source=" << server << L";"
        << L"Initial Catalog=" << database << L";";

    if (!user.empty())
    {
        conn << L"User ID=" << user << L";" ;
        conn << L"Password=" << password << L";" ;
    }

    Cx_Interface<Ix_InitDatabase> pIFDB(CLSID_CfgDatabase);
    ASSERT(pIFDB.IsNotNull());
    Ix_SQLParser* pSQLParser = new SQLParser_SQLServer();

    return pIFDB->OpenConnection(conn.str(), pSQLParser)
        ? Cx_Ptr(pIFDB) : Cx_Ptr();
}
