// x3c - C++ PluginFramework
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
