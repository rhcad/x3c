// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UnitTestInc.h>
#include "TestLoadPlugin.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestLoadPlugin );

TestLoadPlugin::TestLoadPlugin()
{
}

void TestLoadPlugin::setUp()
{
    VERIFY(LoadPlugins(L"", false) > 0);
}

void TestLoadPlugin::tearDown()
{
    UnloadPlugins();
}

void TestLoadPlugin::testLoadByNames()
{
}
