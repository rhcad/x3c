// x3c - C++ PluginFramework
#include <UnitTestInc.h>
#include "TestFileUtil.h"
#include <Utility/Ix_FileUtility.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestFileUtil );

TestFileUtil::TestFileUtil()
{
}

void TestFileUtil::setUp()
{
    VERIFY(LoadPlugins(L"FileUtility.plugin" PLNEXT, false) >= 1);
}

void TestFileUtil::tearDown()
{
    UnloadPlugins();
}

void TestFileUtil::testCopyFolder()
{
    std::wstring path(MakeDataPath(L"", L""));
    ASSERT(x3::FileUtility()->CopyPathFile(path.c_str(), L"D:\\Test\\"));
}

void TestFileUtil::testDelFolder()
{
    ASSERT(x3::FileUtility()->DeletePathFile(L"D:\\Test\\"));
}
