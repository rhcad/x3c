// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include "UnitTestInc.h"
#include "TestPluginManager.h"

#include "Log/Ix_LogManager.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestPluginManager );

TestPluginManager::TestPluginManager(void)
{
}

TestPluginManager::~TestPluginManager(void)
{
}

void TestPluginManager::setUp()
{
    VERIFY(LoadPlugins(L"PluginManagerX3.dll", false) == 0);
}

void TestPluginManager::tearDown()
{
    UnloadPlugins();
}

void TestPluginManager::testLoadUnloadPlugin()
{
    Ix_PluginLoader* pLoader = GetManagerLoader();
    VERIFY(pLoader);
    VERIFY(pLoader->LoadPlugin(L"../Plugins/LogManager.plugin.dll"));
    VERIFY(NULL!=GetModuleHandleW(L"../Plugins/LogManager.plugin.dll"));

    VERIFY(pLoader->UnloadPlugin(L"../Plugins/LogManager.plugin.dll"));
    VERIFY(NULL==GetModuleHandleW(L"../Plugins/LogManager.plugin.dll"));
}

void TestPluginManager::testLoadUnloadPlugins()
{
    Ix_PluginLoader* pLoader = GetManagerLoader();
    VERIFY(pLoader);
    VERIFY(pLoader->LoadPlugins(L"../Plugins") > 0);
    VERIFY(pLoader->UnloadPlugins() > 0);
}

void TestPluginManager::testLoadPluginFiles()
{
}

void TestPluginManager::testInitializePlugins()
{
}

void TestPluginManager::testRegisterPlugin()
{
}

void TestPluginManager::testCreateObject()
{
    Ix_ObjectFactory* pFactory = GetManagerObjectFactory();

    VERIFY(pFactory);
    Ix_PluginLoader* pLoader = dynamic_cast<Ix_PluginLoader*>(pFactory);

    VERIFY(pLoader);
    VERIFY(pLoader->LoadPlugin(L"../Plugins/LogManager.plugin.dll"));

    Ix_Object* ixObject=NULL;
    VERIFY(0==pFactory->CreateObject(CLSID_LogManager, &ixObject,NULL));
    ixObject->Release(NULL);

    VERIFY(pLoader->UnloadPlugin(L"../Plugins/LogManager.plugin.dll"));
}

void TestPluginManager::testIsCreatorRegister()
{
    Ix_ObjectFactory* pFactory = GetManagerObjectFactory();
    VERIFY(pFactory);

    VERIFY(false == pFactory->IsCreatorRegister(CLSID_LogManager));

    Ix_PluginLoader* pLoader = dynamic_cast<Ix_PluginLoader*>(pFactory);
    VERIFY(pLoader);
    VERIFY(pLoader->LoadPlugin(L"../Plugins/LogManager.plugin.dll"));

    VERIFY(true == pFactory->IsCreatorRegister(CLSID_LogManager));

    VERIFY(pLoader->UnloadPlugin(L"../Plugins/LogManager.plugin.dll"));
}

void TestPluginManager::testCreateSpecialInterfaceObjects()
{
    Ix_ObjectFactory* pFactory = GetManagerObjectFactory();
    VERIFY(pFactory);

    VERIFY(false == pFactory->IsCreatorRegister(CLSID_LogManager));

    Ix_PluginLoader* pLoader = dynamic_cast<Ix_PluginLoader*>(pFactory);
    VERIFY(pLoader);
    VERIFY(pLoader->LoadPlugin(L"../Plugins/LogManager.plugin.dll"));

    //VERIFY(pFactory->CreateSpecialInterfaceObjects("testCreateSpecialInterfaceObjects")>0);

    VERIFY(pLoader->UnloadPlugin(L"../Plugins/LogManager.plugin.dll"));
}

void TestPluginManager::testQuerySpecialInterfaceObject()
{
}

void TestPluginManager::testHasCreatorReplaced()
{
}

Ix_PluginLoader* TestPluginManager::GetManagerLoader(void)
{
    Ix_ObjectFactory* pFactory = GetManagerObjectFactory();
    VERIFY(pFactory);
    Ix_PluginLoader* pLoader = dynamic_cast<Ix_PluginLoader*>(pFactory);
    return pLoader;
}


Ix_ObjectFactory* TestPluginManager::GetManagerObjectFactory(void)
{
    typedef Ix_ObjectFactory* (*FUNC_GETREGISTERBANK)();
    FUNC_GETREGISTERBANK pfn = (FUNC_GETREGISTERBANK)GetProcAddress(GetModuleHandleW(L"PluginManagerX3.dll"), "xGetRegisterBank");
    VERIFY(pfn != NULL);

    Ix_ObjectFactory* pFactory = (*pfn)();
    return pFactory;
}
