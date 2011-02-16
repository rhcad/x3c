#pragma once

#include "DocEventObserver.h"

class CDocObserverTest
    : private DocEventObserver
{
public:
    CDocObserverTest(int* data) : m_data(data)
    {
    }

private:
    virtual void OnDocEventAfterOpen()
    {
        (*m_data)++;
    }

private:
    int*    m_data;
};

class CDocObserverTestOnRun
    : private DocEventObserver
{
public:
    CDocObserverTestOnRun()
    {
    }

private:
    virtual void OnDocEventAfterOpen()
    {
        LOG_INFO(L"CDocObserverTestOnRun::OnDocEventAfterOpen");
    }
};
