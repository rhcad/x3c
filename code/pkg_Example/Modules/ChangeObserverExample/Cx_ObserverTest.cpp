#include "StdAfx.h"
#include "Cx_ObserverTest.h"
#include <AutoNew.h>
#include "Responsibility.h"
#include "ResponsibilityB.h"
#include "DocObserverTest.h"
#include "SelectionObserverTest.h"

Cx_ObserverTest::Cx_ObserverTest()
{
}

Cx_ObserverTest::~Cx_ObserverTest()
{
}

bool Cx_ObserverTest::TestResponsibilityChain()
{
    KAutoNew<CResponsibility1> pExample1(new CResponsibility1);
    KAutoNew<CResponsibility2> pExample2(new CResponsibility2);

    int sum = 0;
    ChainObserver::Data(&sum).Notify();

    return sum > 0;
}

bool Cx_ObserverTest::TestResponsibilityChain2(int value, char c)
{
    KAutoNew<CResponsibilityB1> pExample1(new CResponsibilityB1);
    KAutoNew<CResponsibilityB2> pExample2(new CResponsibilityB2);

    return ChainObserverB::Data::DoWork1(value)
        || ChainObserverB::Data::DoWork2(c);
}

bool Cx_ObserverTest::TestEventObserver()
{
    int data = 0;
    CDocObserverTest test(&data);

    DocEventObserver::Data(kDocEvent_BeforeOpen).Notify();
    DocEventObserver::Data(kDocEvent_AfterOpen).Notify();

    return data > 0;
}

bool Cx_ObserverTest::TestSelectionObserver()
{
    KAutoNew<CNodeSelectionTestOnlyReceive> pExample1(new CNodeSelectionTestOnlyReceive);
    KAutoNew<CNodeSelectionTestSendReceive> pExample2(new CNodeSelectionTestSendReceive);

    pExample2->OnChanged();

    NodeSelectionObserver::Data(123, NULL).Notify();

    return true;
}
