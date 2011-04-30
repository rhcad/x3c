// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include "stdafx.h"
#include "TestFileUtil.h"
#include <Utility/Ix_FileUtility.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestFileUtil );

TestFileUtil::TestFileUtil()
{
}

void TestFileUtil::setUp()
{
    VERIFY(LoadPlugins(L"FileUtility.plugin.dll", false) >= 1);
}

void TestFileUtil::tearDown()
{
    UnloadPlugins();
}

void TestFileUtil::testCopyFolder()
{
    ASSERT(FileUtility()->CopyPathFile(L"D:\\FxData\\", L"D:\\Test\\"));
}

void TestFileUtil::testDelFolder()
{
    ASSERT(FileUtility()->DeletePathFile(L"D:\\Test\\"));
}
