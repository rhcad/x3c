// x3c - C++ PluginFramework
#pragma once

#include "BaseTest.h"

class TestHookManager : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestHookManager );
    CPPUNIT_TEST( testHookLoadString );
    CPPUNIT_TEST_SUITE_END();

public:
    TestHookManager();

    virtual void setUp();
    virtual void tearDown();

    void testHookLoadString();
};
