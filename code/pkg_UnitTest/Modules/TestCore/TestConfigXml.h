// x3c - C++ PluginFramework
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
