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

#include "stdafx.h"
#include "TestConfigDB.h"

#include <Xml/Ix_ConfigTransaction.h>
#include <Xml/ConfigIOSection.h>
#include <Ix_ConfigDBFactory.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPPUNIT_TEST_SUITE_REGISTRATION( TestConfigDB );

TestConfigDB::TestConfigDB()
{
}

void TestConfigDB::setUp()
{
    VERIFY(LoadPlugins(L"LogManager.plugin.dll, ConfigDB.plugin.dll", false) > 0);
}

void TestConfigDB::tearDown()
{
    UnloadPlugins();

    VERIFY(SetFileAttributesW(m_dbfile.c_str(), FILE_ATTRIBUTE_NORMAL));
    VERIFY(DeleteFileW(m_dbfile.c_str()));
}

Cx_Ptr TestConfigDB::GetDatabase(LPCWSTR filename)
{
    Cx_Interface<Ix_ConfigDBFactory> pIFFactory(CLSID_ConfigDBFactory);
    ASSERT(pIFFactory.IsNotNull());

    std::wstring srcfile(MakeDataPath(L"Access", filename));
    m_dbfile = MakeDataPath(NULL, filename);
    ::CopyFileW(srcfile.c_str(), m_dbfile.c_str(), TRUE);

    Cx_Ptr obj(pIFFactory->OpenAccessDB(m_dbfile));
    CPPUNIT_ASSERT_MESSAGE("Can not open database file.", obj.IsNotNull());

    return obj;
}

void TestConfigDB::testOpenAccessDB()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());
    pIFDb.Release();
}

void TestConfigDB::testAddRecord()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());
    CConfigIOSection secRec(pIFDb->AddSection(NULL, L"book"));

    secRec->SetUInt32(L"id", 2);
    secRec->SetString(L"title", L"test1");
}

void TestConfigDB::testAddRecordUseMaxID()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());
    CConfigIOSection secRec(pIFDb->AddSection(NULL, L"book"));

    secRec->SetString(L"id", L"@NEWID");
    secRec->SetString(L"title", L"test2");
}

void TestConfigDB::testAddRecordUseMaxIDAndReturnNewID()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());
    CConfigIOSection secNewRec(pIFDb->AddSection(NULL, L"book"));

    secNewRec->SetString(L"id", L"@NEWID");
    secNewRec->SetString(L"title", L"test12");

    VERIFY(CConfigTransaction(Cx_Ptr(secNewRec.P())).Submit());

    ULONG nID = secNewRec->GetUInt32(L"id");
    ASSERT(nID != 0);
}

void TestConfigDB::testSelectSQL()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());
    CConfigIOSection secRecordset(pIFDb->GetSection(
        L"SELECT id,title FROM article WHERE id=4"));

    for (long iRec = 0; iRec < 99; iRec++)
    {
        CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", iRec));
        if (!secRec->IsValid())
            break;

        ULONG nID = secRec->GetUInt32(L"id");
        std::wstring wstrName = secRec->GetString(L"title");

        ASSERT(nID == 4);
    }
}

void TestConfigDB::testSQLWithOrderBy()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());
    CConfigIOSection secRecordset(pIFDb->GetSection(
        L"SELECT id,title FROM article WHERE id=4 Or id=1 ORDER BY id"));

    for (long iRec = 0; iRec < 99; iRec++)
    {
        CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", iRec));
        if (!secRec->IsValid())
            break;

        ULONG nID = secRec->GetUInt32(L"id");
        std::wstring wstrName = secRec->GetString(L"title");

        ASSERT(0 == iRec && nID == 1 || 1 == iRec && nID == 4);
    }
}

void TestConfigDB::testSQLWithLike()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());
    CConfigIOSection secRecordset(pIFDb->GetSection(
        L"SELECT id, title, author, country, times, subject, style "
        L"FROM article WHERE author like '%ку%' "));

    long nRecordCount = secRecordset.GetSectionCount(L"");
    ASSERT(nRecordCount > 0);

    for (long iRec = 0; iRec < 99; iRec++)
    {
        CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", iRec));
        if (!secRec->IsValid())
            break;

        ULONG nID = secRec->GetUInt32(L"id");
        std::wstring wstrName = secRec->GetString(L"title");
        ASSERT(nID != 0);
    }
}

void TestConfigDB::testEditRecord()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());

    CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
    CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", 0));

    CPPUNIT_ASSERT_EQUAL(1L, secRecordset.GetSectionCount(L""));

    secRec->SetString(L"title", L"test3");
}

void TestConfigDB::testEditFieldDateTime()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());

    CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
    CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", 0));

    secRec->SetDateTime(L"create_time", 2010, 3, 10, 9, 30, 10);
}

void TestConfigDB::testEditFieldDate()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());

    CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
    CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", 0));

    secRec->SetDate(L"create_time", 2010, 3, 10);
}

void TestConfigDB::testEditFieldGetCurDate()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());

    CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
    CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", 0));

    secRec->SetString(L"create_time", L"@CURDATE()");
    VERIFY(CConfigTransaction(Cx_Ptr(secRec.P())).Submit());

    secRec->SetString(L"create_time", L"@CURTIME()");
    VERIFY(CConfigTransaction(Cx_Ptr(secRec.P())).Submit());

    secRec->SetString(L"create_time", L"@NOW()");
    VERIFY(CConfigTransaction(Cx_Ptr(secRec.P())).Submit());
}

void TestConfigDB::testReadFieldDate()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());

    {
        CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
        CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", 0));

        secRec->SetDateTime(L"create_time", 2010, 3, 10, 9, 30, 10);
    }

    CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
    CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", 0));
    ASSERT(secRec->IsValid());

    int year, month, day;
    VERIFY(secRec->GetDate(L"create_time", year, month, day));
}

void TestConfigDB::testDelRecord()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());
    CPPUNIT_ASSERT_EQUAL(1L, pIFDb->RemoveChildren(NULL, L"book", L"id", 1));
}

void TestConfigDB::testRecordsetTransaction()
{
    Cx_Interface<Ix_ConfigData> pIFDb(GetDatabase());

    CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
    CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", 0));

    secRec->SetString(L"title", L"test4");

    VERIFY(CConfigTransaction(Cx_Ptr(secRec.P())).Submit());
}
