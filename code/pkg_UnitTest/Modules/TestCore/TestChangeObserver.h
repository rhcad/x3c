// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#pragma once

#include "BaseTest.h"

class TestChangeObserver : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestChangeObserver );
    CPPUNIT_TEST( testNotifyEvent );
    CPPUNIT_TEST( testResponsibilityChain );
    CPPUNIT_TEST( testResponsibilityChain2 );
    CPPUNIT_TEST( testEventObserver );
    CPPUNIT_TEST( testSelectionObserver );
    CPPUNIT_TEST_SUITE_END();

public:
    TestChangeObserver();

    virtual void setUp();
    virtual void tearDown();

    void testNotifyEvent();
    void testResponsibilityChain();
    void testResponsibilityChain2();
    void testEventObserver();
    void testSelectionObserver();
};
