// x3c - C++ PluginFramework
#include <UnitTestInc.h>
#include "TestTextUtil.h"
#include <Utility/Ix_StringCoding.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestTextUtil );

TestTextUtil::TestTextUtil()
{
}

void TestTextUtil::setUp()
{
    VERIFY(LoadPlugins(L"TextUtility.plugin" PLNEXT, false) >= 1);
}

void TestTextUtil::tearDown()
{
    UnloadPlugins();
}

void TestTextUtil::testMD5()
{
    Cx_Interface<Ix_StringCoding> pIFCoding(x3::CLSID_TextUtil);
    ASSERT(pIFCoding.IsNotNull());
    
    ASSERT(pIFCoding->MD5(L"apple") == L"1f3870be274f6c49b3e31a0c6728957f");
    ASSERT(pIFCoding->MD5(L"").size() == 32);
}

void TestTextUtil::testBase64()
{
    Cx_Interface<Ix_StringCoding> pIFCoding(x3::CLSID_TextUtil);
    ASSERT(pIFCoding.IsNotNull());
    std::wstring text;

    ASSERT(pIFCoding->Base64(text, "AAwww.baidu.com/img/sslm1_logo.gifZZ")
        == L"QUF3d3cuYmFpZHUuY29tL2ltZy9zc2xtMV9sb2dvLmdpZlpa");
    ASSERT(pIFCoding->Base64(text, "") == L"");
}

void TestTextUtil::testUnBase64()
{
    Cx_Interface<Ix_StringCoding> pIFCoding(x3::CLSID_TextUtil);
    ASSERT(pIFCoding.IsNotNull());
    std::string data;

    ASSERT(pIFCoding->UnBase64(data, L"QUF3d3cuYmFpZHUuY29tL2ltZy9zc2xtMV9sb2dvLmdpZlpa")
        == "AAwww.baidu.com/img/sslm1_logo.gifZZ");
    ASSERT(pIFCoding->UnBase64(data, L"") == "");
}
