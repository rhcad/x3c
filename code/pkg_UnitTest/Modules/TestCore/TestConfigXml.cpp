// x3c - C++ PluginFramework
#include <UnitTestInc.h>
#include "TestConfigXml.h"
#include <Xml/Ix_ConfigXml.h>
#include <Xml/Cx_ConfigSection.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestConfigXml );

TestConfigXml::TestConfigXml()
{
}

void TestConfigXml::setUp()
{
    VERIFY(LoadPlugins(L"ConfigXml.plugin" PLNEXT, false) >= 1);
}

void TestConfigXml::tearDown()
{
    UnloadPlugins();
}

void TestConfigXml::testSetXmlContent()
{
    Cx_Interface<Ix_ConfigXml> pIFXml(x3::CLSID_ConfigXmlFile);
    ASSERT(pIFXml.IsNotNull());
    bool ret = pIFXml->SetXmlContent(L"<?xml version=\"1.0\"?><test></test>");
    VERIFY(ret);
    ASSERT(pIFXml->GetRootName() == L"test");
}

void TestConfigXml::testNewDoc()
{
    Cx_Interface<Ix_ConfigXml> pIFXml(x3::CLSID_ConfigXmlFile);
    ASSERT(pIFXml.IsNotNull());

    Cx_ConfigSection root(pIFXml->GetData()->GetSection(L""));
    std::wstring content;

    VERIFY(pIFXml->GetXmlContent(content, root.P()));
    ASSERT(content.find(L"<") != std::wstring::npos);
}
