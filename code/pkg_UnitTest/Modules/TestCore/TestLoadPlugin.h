// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#pragma once

#include "BaseTest.h"

class TestLoadPlugin : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestLoadPlugin );
    CPPUNIT_TEST( testLoadByNames );
    CPPUNIT_TEST_SUITE_END();

public:
    TestLoadPlugin();

    virtual void setUp();
    virtual void tearDown();

    void testLoadByNames();
};
