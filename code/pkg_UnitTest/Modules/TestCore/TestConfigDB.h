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

#pragma once

#include "BaseTest.h"

class TestConfigDB : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestConfigDB );
    CPPUNIT_TEST( testOpenAccessDB );
    CPPUNIT_TEST( testAddRecord );
    CPPUNIT_TEST( testAddRecordUseMaxID );
    CPPUNIT_TEST( testAddRecordUseMaxIDAndReturnNewID );
    CPPUNIT_TEST( testSelectSQL );
    CPPUNIT_TEST( testSQLWithOrderBy );
    CPPUNIT_TEST( testSQLWithLike );
    CPPUNIT_TEST( testEditRecord );
    CPPUNIT_TEST( testEditFieldDateTime );
    CPPUNIT_TEST( testEditFieldDate );
    CPPUNIT_TEST( testEditFieldGetCurDate );
    CPPUNIT_TEST( testReadFieldDate );
    CPPUNIT_TEST( testRecordsetTransaction );
    CPPUNIT_TEST( testDelRecord );
    CPPUNIT_TEST_SUITE_END();

public:
    TestConfigDB();

    virtual void setUp();
    virtual void tearDown();

    void testOpenAccessDB();
    void testAddRecord();
    void testAddRecordUseMaxID();
    void testAddRecordUseMaxIDAndReturnNewID();
    void testSelectSQL();
    void testSQLWithOrderBy();
    void testSQLWithLike();
    void testEditRecord();
    void testEditFieldDateTime();
    void testEditFieldDate();
    void testEditFieldGetCurDate();
    void testReadFieldDate();
    void testDelRecord();
    void testRecordsetTransaction();

private:
    Cx_Ptr GetDatabase(const wchar_t* filename = L"TestAccess.mdb");

private:
    std::wstring    m_dbfile;
};
