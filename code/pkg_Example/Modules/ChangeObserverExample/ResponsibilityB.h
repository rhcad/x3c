#pragma once

#include "ChainObserverB.h"

class CResponsibilityB1
	: private ChainObserverB
{
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
