// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UnitTestInc.h>
#include "TestComHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
#endif

CPPUNIT_TEST_SUITE_REGISTRATION( TestComHook );

TestComHook::TestComHook()
{
}

void TestComHook::setUp()
{
    VERIFY(LoadPlugins(L"ComHook.plugin" PLNEXT, false) > 0);
}

void TestComHook::tearDown()
{
    UnloadPlugins();
}

void TestComHook::testSimpleAtlCom()
{
}
