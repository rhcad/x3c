#pragma once

#include "ChainObserver.h"

class CResponsibility1
	: private ChainObserver
{
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
