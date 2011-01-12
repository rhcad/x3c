#pragma once

#include <Ix_ChangeObserverTest.h>

class Cx_ObserverTest
    : public Ix_ChangeObserverTest
{
protected:
    Cx_ObserverTest();
    ~Cx_ObserverTest();

private:
    // From Ix_Example
    bool TestResponsibilityChain();
    bool TestResponsibilityChain2(int value, char c);
    bool TestEventObserver();
    bool TestSelectionObserver();
};
