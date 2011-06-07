// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#pragma once

#include "BaseTest.h"

class TestConfigXml : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestConfigXml );
    CPPUNIT_TEST( testSetXmlContent );
    CPPUNIT_TEST( testNewDoc );
    CPPUNIT_TEST_SUITE_END();

public:
    TestConfigXml();

    virtual void setUp();
    virtual void tearDown();

    void testSetXmlContent();
    void testNewDoc();
};
