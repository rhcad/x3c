// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

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
