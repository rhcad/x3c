// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#pragma once

#include "BaseTest.h"

class TestTextUtil : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestTextUtil );
    CPPUNIT_TEST( testMD5 );
    CPPUNIT_TEST( testBase64 );
    CPPUNIT_TEST( testUnBase64 );
    CPPUNIT_TEST_SUITE_END();

public:
    TestTextUtil();

    virtual void setUp();
    virtual void tearDown();

    void testMD5();
    void testBase64();
    void testUnBase64();
};
