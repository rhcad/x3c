// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "stdafx.h"
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
