#pragma once

#include <Ix_Example.h>

class Cx_Example2
	: public Ix_Example
	, public Ix_Example2
{
protected:
	Cx_Example2();
	~Cx_Example2();

protected:
	// From Ix_Example
	virtual void Foo();

	// From Ix_Example2
	virtual void Foo2();
};
