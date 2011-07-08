#pragma once

#include <ObserverExample/ChainObserverB.h>

class CResponsibilityB1
    : private ChainObserverB
{
    NOCOPY_CONSTRUCTOR(CResponsibilityB1);
public:
    CResponsibilityB1()
    {
    }

private:
    virtual bool OnChainWork1(int value)
    {
        return value > 0;
    }
};

class CResponsibilityB2
    : private ChainObserverB
{
    NOCOPY_CONSTRUCTOR(CResponsibilityB2);
public:
    CResponsibilityB2()
    {
    }

private:
    virtual bool OnChainWork2(char c)
    {
        return c != 'x';
    }
};
