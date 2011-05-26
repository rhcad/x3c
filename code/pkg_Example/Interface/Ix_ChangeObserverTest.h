#ifndef CHANGEOBSERVERTEST_INTERFACE_H
#define CHANGEOBSERVERTEST_INTERFACE_H

const XCLSID CLSID_ChangeObserverTest("e57cc552-b227-4c2c-bf19-099083b79bf4");

interface Ix_ChangeObserverTest
{
    virtual bool TestResponsibilityChain() = 0;
    virtual bool TestResponsibilityChain2(int value, char c) = 0;
    virtual bool TestEventObserver() = 0;
    virtual bool TestSelectionObserver() = 0;
};

#endif // CHANGEOBSERVERTEST_INTERFACE_H