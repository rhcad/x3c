#pragma once

#include <ObserverExample/DocEventObserver.h>

class CDocObserverTest
    : private DocEventObserver
{
    NOCOPY_CONSTRUCTOR(CDocObserverTest);
public:
    CDocObserverTest(int* data) : m_data(data)
    {
    }

private:
    virtual bool OnDocEventAfterOpen()
    {
        (*m_data)++;
        return true;
    }

private:
    int*    m_data;
};

class CDocObserverTestOnRun
    : private DocEventObserver
{
    NOCOPY_CONSTRUCTOR(CDocObserverTestOnRun);
public:
    CDocObserverTestOnRun()
    {
    }

private:
    virtual bool OnDocEventAfterOpen()
    {
        X3LOG_INFO(L"CDocObserverTestOnRun::OnDocEventAfterOpen");
        return true;
    }
};
