// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UnitTestInc.h>
#include "TestComHook.h"

#ifdef _WIN32

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

extern "C" const CLSID CLSID_ATLCOM = 
    {0xBDE3B7B3, 0x1AA2, 0x44C1, {0xA0,0x2F,0xD1,0xA7,0x2D,0x3E,0xDD,0x2A}};

void TestComHook::testSimpleAtlCom()
{
    IUnknown* pIUnknown = NULL;

    HRESULT hrCreate = ::CoCreateInstance(CLSID_ATLCOM, NULL, 
        CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
    VERIFY(SUCCEEDED(hrCreate));
    pIUnknown->Release();
}

#endif // _WIN32
