// x3c - C++ PluginFramework
#pragma once

#include "BaseTest.h"

class TestStringTable : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestStringTable );
    CPPUNIT_TEST( testSimple );
    CPPUNIT_TEST_SUITE_END();

public:
    TestStringTable();

    virtual void setUp();
    virtual void tearDown();

    void testSimple();
};
