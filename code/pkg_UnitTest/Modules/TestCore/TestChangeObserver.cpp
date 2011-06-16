// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UnitTestInc.h>
#include "TestChangeObserver.h"
#include <../../pkg_Example/Interface/Ix_ChangeObserverTest.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestChangeObserver );

TestChangeObserver::TestChangeObserver()
{
}

void TestChangeObserver::setUp()
{
    VERIFY(2 == LoadPlugins(
        L"ChangeManager.plugin" PLNEXT
        L",ChangeObserverExample.plugin" PLNEXT, false));
}

void TestChangeObserver::tearDown()
{
    UnloadPlugins();
}

void TestChangeObserver::testResponsibilityChain()
{
    Cx_Interface<Ix_ChangeObserverTest> pIFTest(X3CLS_ChangeObserverTest);
    ASSERT(pIFTest.IsNotNull());
    VERIFY(pIFTest->TestResponsibilityChain());
}

void TestChangeObserver::testResponsibilityChain2()
{
    Cx_Interface<Ix_ChangeObserverTest> pIFTest(X3CLS_ChangeObserverTest);
    ASSERT(pIFTest.IsNotNull());
    VERIFY(pIFTest->TestResponsibilityChain2(1, 'x'));
    VERIFY(pIFTest->TestResponsibilityChain2(0, '-'));
    VERIFY(!pIFTest->TestResponsibilityChain2(0, 'x'));
}

void TestChangeObserver::testEventObserver()
{
    Cx_Interface<Ix_ChangeObserverTest> pIFTest(X3CLS_ChangeObserverTest);
    ASSERT(pIFTest.IsNotNull());
    VERIFY(pIFTest->TestEventObserver());
}

void TestChangeObserver::testSelectionObserver()
{
    Cx_Interface<Ix_ChangeObserverTest> pIFTest(X3CLS_ChangeObserverTest);
    ASSERT(pIFTest.IsNotNull());
    VERIFY(pIFTest->TestSelectionObserver());
}
