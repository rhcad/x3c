#include <UtilFunc/PluginInc.h>
#include "Cx_Example.h"

Cx_Example::Cx_Example()
{
}

Cx_Example::~Cx_Example()
{
}

void Cx_Example::Foo(long& value)
{
    value = 1;
}

void Cx_Example::Foo2(long& value)
{
    value = 2;
}
