#pragma once

#include <ObserverExample/ChainObserver.h>

class CResponsibility1
    : private ChainObserver
{
    NOCOPY_CONSTRUCTOR(CResponsibility1);
public:
    CResponsibility1()
    {
    }

private:
    virtual void OnChain(int& sum)
    {
        sum += 1;
    }
};

class CResponsibility2
    : private ChainObserver
{
    NOCOPY_CONSTRUCTOR(CResponsibility2);
public:
    CResponsibility2()
    {
    }

private:
    virtual void OnChain(int& sum)
    {
        sum += 10;
    }
};
