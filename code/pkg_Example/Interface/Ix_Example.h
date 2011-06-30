#ifndef EXAMPLE_INTERFACE_H
#define EXAMPLE_INTERFACE_H

#include <ClsID_Example.h>

class Ix_Example : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_Example)
    virtual void Foo(long& value) = 0;
};

class Ix_Example2 : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_Example2)
    virtual void Foo2(long& value) = 0;
};

#endif // EXAMPLE_INTERFACE_H