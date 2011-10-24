// x3c - C++ PluginFramework
#pragma once

#include "BaseTest.h"

class TestComHook : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestComHook );
    CPPUNIT_TEST( testSimpleAtlCom );
    CPPUNIT_TEST( testMultiCreate );
    CPPUNIT_TEST( testX3CoreCom );
    CPPUNIT_TEST_SUITE_END();

public:
    TestComHook();

    virtual void setUp();
    virtual void tearDown();

    void testSimpleAtlCom();
    void testMultiCreate();
    void testX3CoreCom();
};
