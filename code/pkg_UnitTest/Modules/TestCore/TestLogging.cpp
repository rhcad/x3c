// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "stdafx.h"
#include "TestLogging.h"
#include <Log/LogHelper.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestLogging );

TestLogging::TestLogging()
{
}

void TestLogging::setUp()
{
    VERIFY(LoadPlugins(L"LogManager.plugin.dll, LogWriter.plugin.dll, "
        L"FileUtility.plugin.dll, TextUtility.plugin.dll", false) > 0);
}

void TestLogging::tearDown()
{
    UnloadPlugins();
}

void TestLogging::testAllMacros()
{
    LOG_DEBUG(L"test");
    LOG_DEBUG2(L"test", L"extra");
    LOG_INFO(L"test");
    LOG_INFO2(L"test", L"extra");
    LOG_WARNING(L"test");
    LOG_WARNING2(L"test", L"extra");
    LOG_ERROR(L"test");
    LOG_ERROR2(L"test", L"extra");
    LOG_FATAL(L"test");
    LOG_FATAL2(L"test", L"extra");
    LOG_EVENT_ANSI("test", L"extra", kLogType_Error, "xxx", 100);
}

void TestLogging::testAllMacrosWithID()
{
    LOG_DEBUG(L"@Test:debug");
    LOG_DEBUG2(L"@Test:IDS_DEBUG", L"extra");
    LOG_INFO(L"@Test:Name");
    LOG_INFO2(L"@Test:Name", L"extra");
    LOG_WARNING(L"@Test:Name");
    LOG_WARNING2(L"@Test:Name", L"extra");
    LOG_ERROR(L"@Test:Name");
    LOG_ERROR2(L"@Test:Name", L"extra");
    LOG_FATAL(L"@Test:Name");
    LOG_FATAL2(L"@Test:Name", L"extra");
    LOG_EVENT_ANSI("@Test:Name", L"extra", kLogType_Debug, __FILE__, __LINE__);
}

void TestLogging::testMultiTypes()
{
    LOG_WARNING2(L"Name", L"Name");
    LOG_WARNING2(L"Name", "Name");
    LOG_WARNING2(L"Name", CString(L"Name"));
    LOG_WARNING2(L"Name", std::wstring(L"Name"));
    //LOG_WARNING2(L"Name", std::string("Name"));
    LOG_WARNING2(L"Name", 10);
    LOG_WARNING2(L"Name", 10L);
    LOG_WARNING2(L"Name", GetLastError());
    LOG_WARNING2(L"Name", 10.2);
    LOG_WARNING2(L"Name", 10.2f);
    LOG_WARNING2(L"Name", true);
    LOG_WARNING2(L"Name", this);
    LOG_WARNING2(L"Name", NULL);
    LOG_EVENT_ANSI("@Test:Name", 10, kLogType_Info, __FILE__, __LINE__);
}

void TestLogging::testIdFormat()
{
    LOG_INFO(L"@Test:");
    LOG_INFO(L"@Test");
    LOG_INFO(L"@Test ");
    LOG_INFO(L"@Test:Name");
    LOG_INFO(L"@Test:NAME");
    LOG_INFO(L"@Test:Name ");
    LOG_INFO(L"@@");
    LOG_INFO(L"@");
    LOG_INFO(L"");
    LOG_INFO(L" ");
    LOG_INFO(L"Test");
    LOG_INFO(NULL);
}

void TestLogging::testGroup()
{
    {
        CAutoLogGroup group(L"testGroup1");
    }
    {
        CAutoLogGroup group(L"testGroup2", L"message");
    }
    {
        CAutoLogGroup group(L"testGroup3", NULL);
    }
    {
        CAutoLogGroup group(L"@Test:Name");
    }
    {
        CAutoLogGroup group(L"testGroup4");
        LOG_INFO(L"test");
    }
    {
        CAutoLogGroup group(L"testGroup5");
        LOG_WARNING2(L"test", L"message");
    }
    {
        CAutoLogGroup group(L"testGroup6");
        LOG_WARNING2(L"test", L"message");
        {
            CAutoLogGroup group2(L"testGroup7");
            LOG_INFO(L"test");
        }
    }
}

#include <Log/ILogObserver.h>

class MyLogObserver : public CLogObserverImpl
{
public:
    MyLogObserver() : m_count(0)
    {
    }

    int GetCount()
    {
        return m_count;
    }

private:
    virtual void OnPushGroup(long nLevel, 
        const std::wstring& wstrMsg, const std::wstring& wstrExtra, 
        const std::wstring& wstrModule, const std::wstring& wstrID)
    {
        nLevel; wstrMsg; wstrExtra; wstrModule; wstrID;
        m_count++;
    }

    virtual void OnPopGroup(long nLevel)
    {
        nLevel;
        m_count++;
    }

    virtual void OnWriteLog(int nType, 
        const std::wstring& wstrMsg, const std::wstring& wstrExtra, 
        const std::wstring& wstrModule, const std::wstring& wstrID, 
        const std::wstring& wstrFile, long nLine)
    {
        nType; wstrMsg; wstrExtra; wstrModule; wstrID; wstrFile; nLine;
        m_count++;
    }

private:
    int     m_count;
};

void TestLogging::testObserver()
{
    MyLogObserver observer;

    VERIFY(RegisterLogObserver(&observer));
    testAllMacros();
    UnRegisterLogObserver(&observer);

    ASSERT(observer.GetCount() > 0);
}
