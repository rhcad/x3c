// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#pragma once

#include "BaseTest.h"

class TestLogging : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestLogging );
    CPPUNIT_TEST( testAllMacros );
    CPPUNIT_TEST( testAllMacrosWithID );
    CPPUNIT_TEST( testMultiTypes );
    CPPUNIT_TEST( testIdFormat );
    CPPUNIT_TEST( testGroup );
    CPPUNIT_TEST( testObserver );
    CPPUNIT_TEST_SUITE_END();

public:
    TestLogging();

    virtual void setUp();
    virtual void tearDown();

    void testAllMacros();
    void testAllMacrosWithID();
    void testMultiTypes();
    void testIdFormat();
    void testGroup();
    void testObserver();
};
