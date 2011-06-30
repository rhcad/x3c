#pragma once

#include <Ix_Example.h>

class Cx_Example
    : public Ix_Example
    , public Ix_Example2
{
    X3BEGIN_CLASS_DECLARE(Cx_Example)
        X3DEFINE_INTERFACE_ENTRY(Ix_Example)
        X3DEFINE_INTERFACE_ENTRY(Ix_Example2)
    X3END_CLASS_DECLARE()
protected:
    Cx_Example();
    virtual ~Cx_Example();

private:
    // From Ix_Example
    virtual void Foo(long& value);

    // From Ix_Example2
    virtual void Foo2(long& value);
};
