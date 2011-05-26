#ifndef EXAMPLE_INTERFACE_H
#define EXAMPLE_INTERFACE_H

#include <ClsID_Example.h>

interface Ix_Example
{
    virtual void Foo(long& value) = 0;
};

interface Ix_Example2
{
    virtual void Foo2(long& value) = 0;
};

#endif // EXAMPLE_INTERFACE_H