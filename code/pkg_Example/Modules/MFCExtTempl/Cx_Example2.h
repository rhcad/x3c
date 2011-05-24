#pragma once

#include <Ix_Example.h>

class Cx_Example2
    : public Ix_Example
    , public Ix_Example2
{
protected:
    Cx_Example2();
    virtual ~Cx_Example2();

private:
    // From Ix_Example
    virtual void Foo(long& value);

    // From Ix_Example2
    virtual void Foo2(long& value);
};
