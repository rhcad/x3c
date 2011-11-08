// x3c - C++ PluginFramework
#include <UnitTestInc.h>
#include "TestLogging.h"
#include <Log/LogHelper.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestLogging );

TestLogging::TestLogging()
{
}

void TestLogging::setUp()
{
    VERIFY(LoadPlugins(L"LogManager.plugin" PLNEXT
        L",LogWriter.plugin" PLNEXT
        L",FileUtility.plugin" PLNEXT
        L",TextUtility.plugin" PLNEXT, false) > 0);
}

void TestLogging::tearDown()
{
    UnloadPlugins();
}

void TestLogging::testAllMacros()
{
    X3LOG_DEBUG(L"test");
    X3LOG_DEBUG2(L"test", L"extra");
    X3LOG_INFO(L"test");
    X3LOG_INFO2(L"test", L"extra");
    X3LOG_WARNING(L"test");
    X3LOG_WARNING2(L"test", L"extra");
    X3LOG_ERROR(L"test");
    X3LOG_ERROR2(L"test", L"extra");
    X3LOG_FATAL(L"test");
    X3LOG_FATAL2(L"test", L"extra");
    X3LOG_EVENT_ANSI("test", L"extra", x3LogType_Error, "xxx", 100);
}

void TestLogging::testAllMacrosWithID()
{
    X3LOG_DEBUG(L"@Test:debug");
    X3LOG_DEBUG2(L"@Test:IDS_DEBUG", L"extra");
    X3LOG_INFO(L"@Test:Name");
    X3LOG_INFO2(L"@Test:Name", L"extra");
    X3LOG_WARNING(L"@Test:Name");
    X3LOG_WARNING2(L"@Test:Name", L"extra");
    X3LOG_ERROR(L"@Test:Name");
    X3LOG_ERROR2(L"@Test:Name", L"extra");
    X3LOG_FATAL(L"@Test:Name");
    X3LOG_FATAL2(L"@Test:Name", L"extra");
    X3LOG_EVENT_ANSI("@Test:Name", L"extra", x3LogType_Debug, __FILE__, __LINE__);
}

void TestLogging::testMultiTypes()
{
    X3LOG_WARNING2(L"Name", L"Name");
    X3LOG_WARNING2(L"Name", "Name");
    //X3LOG_WARNING2(L"Name", CString(L"Name"));
    X3LOG_WARNING2(L"Name", std::wstring(L"Name"));
    //X3LOG_WARNING2(L"Name", std::string("Name"));
    X3LOG_WARNING2(L"Name", 10);
    X3LOG_WARNING2(L"Name", 10L);
    X3LOG_WARNING2(L"Name", GetLastError());
    X3LOG_WARNING2(L"Name", 10.2);
    X3LOG_WARNING2(L"Name", 10.2f);
    X3LOG_WARNING2(L"Name", true);
    X3LOG_WARNING2(L"Name", this);
    X3LOG_EVENT_ANSI("@Test:Name", 10, x3LogType_Info, __FILE__, __LINE__);
}

void TestLogging::testIdFormat()
{
    X3LOG_INFO(L"@Test:");
    X3LOG_INFO(L"@Test");
    X3LOG_INFO(L"@Test ");
    X3LOG_INFO(L"@Test:Name");
    X3LOG_INFO(L"@Test:NAME");
    X3LOG_INFO(L"@Test:Name ");
    X3LOG_INFO(L"@@");
    X3LOG_INFO(L"@");
    X3LOG_INFO(L"");
    X3LOG_INFO(L" ");
    X3LOG_INFO(L"Test");
}

void TestLogging::testGroup()
{
    {
        X3LogGroup group(L"testGroup1");
    }
    {
        X3LogGroup group(L"testGroup2", L"message");
    }
    {
        X3LogGroup group(L"testGroup3", NULL);
    }
    {
        X3LogGroup group(L"@Test:Name");
    }
    {
        X3LogGroup group(L"testGroup4");
        X3LOG_INFO(L"test");
    }
    {
        X3LogGroup group(L"testGroup5");
        X3LOG_WARNING2(L"test", L"message");
    }
    {
        X3LogGroup group(L"testGroup6");
        X3LOG_WARNING2(L"test", L"message");
        {
            X3LogGroup group2(L"testGroup7");
            X3LOG_INFO(L"test");
        }
    }
}

#include <Log/Ix_LogObserver.h>

class MyLogObserver : public Cx_LogObserverImpl
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
        const std::wstring& wstrModule, const std::wstring& wstrID,
        const char* file, long line)
    {
        nLevel; wstrMsg; wstrExtra; wstrModule; wstrID; file; line;
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

    VERIFY(x3::RegisterLogObserver(&observer));
    testAllMacros();
    x3::UnRegisterLogObserver(&observer);

    ASSERT(observer.GetCount() > 0);
}
