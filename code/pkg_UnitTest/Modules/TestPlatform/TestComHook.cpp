// x3c - C++ PluginFramework
#include <UnitTestInc.h>
#include "TestComHook.h"

#ifdef _WIN32

CPPUNIT_TEST_SUITE_REGISTRATION( TestComHook );

TestComHook::TestComHook()
{
}

void TestComHook::setUp()
{
    VERIFY(LoadPlugins(L"ComHook.plugin" PLNEXT
        L" LogManager.plugin" PLNEXT, false) == 2);
}

void TestComHook::tearDown()
{
    UnloadPlugins();
}

const IID IID_IUnknown = {0,0,0,{0xC0,0,0,0,0,0,0,0x46}};

const CLSID CLSID_ATLCOM = {0xBDE3B7B3, 0x1AA2, 0x44C1,{
    0xA0,0x2F,0xD1,0xA7,0x2D,0x3E,0xDD,0x2A}};

void TestComHook::testSimpleAtlCom()
{
    IUnknown* pIUnknown = NULL;

    HRESULT hrCreate = ::CoCreateInstance(CLSID_ATLCOM, NULL,
        CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);

    ASSERT(S_OK == hrCreate || REGDB_E_CLASSNOTREG == hrCreate);
    ASSERT(SUCCEEDED(hrCreate));

    pIUnknown->Release();
}

void TestComHook::testMultiCreate()
{
    IUnknown* pIUnknown = NULL;

    for (int i = 0; i < 1000; i++)
    {
        if (SUCCEEDED(::CoCreateInstance(CLSID_ATLCOM, NULL,
            CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown)))
        {
            pIUnknown->Release();
        }
    }
}

void TestComHook::testX3CoreCom()
{
    VERIFY(LoadPlugins(L"x3core.com.dll", false) > 0);
}

#endif // _WIN32
