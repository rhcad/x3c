// x3c - C++ PluginFramework
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
