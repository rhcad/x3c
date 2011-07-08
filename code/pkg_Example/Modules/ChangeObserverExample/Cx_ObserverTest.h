#pragma once

#include <ObserverExample/Ix_ChangeObserverTest.h>

class Cx_ObserverTest
    : public Ix_ChangeObserverTest
{
    X3BEGIN_CLASS_DECLARE(Cx_ObserverTest)
        X3DEFINE_INTERFACE_ENTRY(Ix_ChangeObserverTest)
    X3END_CLASS_DECLARE()
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
