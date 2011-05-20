// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UnitTestInc.h>
#include "TestStringTable.h"
#include <Xml/Ix_StringTable.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestStringTable );

TestStringTable::TestStringTable()
{
}

void TestStringTable::setUp()
{
    VERIFY(LoadPlugins(L"StringTable.plugin.dll, ConfigXml.plugin.dll LogManager.plugin.dll", false) >= 2);
}

void TestStringTable::tearDown()
{
    UnloadPlugins();
}

void TestStringTable::testSimple()
{
    Cx_Interface<Ix_StringTable> pIFTable(CLSID_StringTable);
    ASSERT(pIFTable);

    pIFTable->LoadFiles(L"");

    std::wstring value, module, id;

    ASSERT(pIFTable->GetValue(value, L"StringTable", L"IDS_LOAD_STRFILE"));
    ASSERT(pIFTable->GetValue(value, L"@StringTable:IDS_LOAD_STRFILE", module, id)
        && module == L"StringTable" && id == L"IDS_LOAD_STRFILE");

    ASSERT(!pIFTable->GetValue(value, L"StringTable", L"XXX"));
    ASSERT(!pIFTable->GetValue(value, L"XXX", L"XXX"));
}
