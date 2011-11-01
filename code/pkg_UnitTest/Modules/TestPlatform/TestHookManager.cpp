// x3c - C++ PluginFramework
#include <UnitTestInc.h>
#include "TestHookManager.h"
#include <Ix_HookManager.h>

#ifdef _WIN32

CPPUNIT_TEST_SUITE_REGISTRATION( TestHookManager );

TestHookManager::TestHookManager()
{
}

void TestHookManager::setUp()
{
    VERIFY(LoadPlugins(L"HookManager.plugin" PLNEXT
        L" LogManager.plugin" PLNEXT, false) == 2);
}

void TestHookManager::tearDown()
{
    UnloadPlugins();
}

void TestHookManager::testHookLoadString()
{
    Cx_Interface<Ix_HookManager> pIFHook(x3::CLSID_HookManager);
    ASSERT(pIFHook.IsNotNull());
}

#endif // _WIN32
