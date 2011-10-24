// x3c - C++ PluginFramework
#pragma once

#include "BaseTest.h"

class TestFileUtil : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestFileUtil );
    CPPUNIT_TEST( testCopyFolder );
    CPPUNIT_TEST( testDelFolder );
    CPPUNIT_TEST_SUITE_END();

public:
    TestFileUtil();

    virtual void setUp();
    virtual void tearDown();

    void testCopyFolder();
    void testDelFolder();
};
