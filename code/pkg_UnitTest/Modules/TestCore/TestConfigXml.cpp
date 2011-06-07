// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UnitTestInc.h>
#include "TestConfigXml.h"
#include <Xml/Ix_ConfigXml.h>
#include <Xml/ConfigIOSection.h>

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
    Cx_Interface<Ix_ConfigXml> pIFXml(CLSID_ConfigXmlFile);
    ASSERT(pIFXml.IsNotNull());
    VERIFY(pIFXml->SetXmlContent(L"<?xml version=\"1.0\"?><test></test>"));
    ASSERT(pIFXml->GetRootName() == L"test");
}

void TestConfigXml::testNewDoc()
{
    Cx_Interface<Ix_ConfigXml> pIFXml(CLSID_ConfigXmlFile);
    ASSERT(pIFXml.IsNotNull());

    CConfigIOSection root(pIFXml->GetData()->GetSection(L""));
    std::wstring content;

    VERIFY(pIFXml->GetXmlContent(content, root.P()));
    ASSERT(content.find(L"<") != std::wstring::npos);
}
