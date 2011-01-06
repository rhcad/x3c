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
#include "TestChangeObserver.h"
#include <../../pkg_Example/Interface/Ix_ChangeObserverTest.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestChangeObserver );

TestChangeObserver::TestChangeObserver()
{
}

void TestChangeObserver::setUp()
{
	VERIFY(2 == LoadPlugins(
		L"ChangeManager.plugin.dll, ChangeObserverExample.plugin.dll", false));
}

void TestChangeObserver::tearDown()
{
	UnloadPlugins();
}

void TestChangeObserver::testResponsibilityChain()
{
	Cx_Interface<Ix_ChangeObserverTest> pIFTest(CLSID_ChangeObserverTest);
	ASSERT(pIFTest.IsNotNull());
	VERIFY(pIFTest->TestResponsibilityChain());
}

void TestChangeObserver::testResponsibilityChain2()
{
	Cx_Interface<Ix_ChangeObserverTest> pIFTest(CLSID_ChangeObserverTest);
	ASSERT(pIFTest.IsNotNull());
	VERIFY(pIFTest->TestResponsibilityChain2(1, 'x'));
	VERIFY(pIFTest->TestResponsibilityChain2(0, '-'));
	VERIFY(!pIFTest->TestResponsibilityChain2(0, 'x'));
}

void TestChangeObserver::testEventObserver()
{
	Cx_Interface<Ix_ChangeObserverTest> pIFTest(CLSID_ChangeObserverTest);
	ASSERT(pIFTest.IsNotNull());
	VERIFY(pIFTest->TestEventObserver());
}

void TestChangeObserver::testSelectionObserver()
{
	Cx_Interface<Ix_ChangeObserverTest> pIFTest(CLSID_ChangeObserverTest);
	ASSERT(pIFTest.IsNotNull());
	VERIFY(pIFTest->TestSelectionObserver());
}
