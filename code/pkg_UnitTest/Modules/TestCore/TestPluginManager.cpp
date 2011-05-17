// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include "StdAfx.h"
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
    long lPluginsNum = GetPluginsNum(L"../Plugins");

    Ix_PluginLoader* pLoader = GetManagerLoader();
    VERIFY(pLoader);
    VERIFY(pLoader->LoadPlugins(L"../Plugins") == lPluginsNum);

    VERIFY(pLoader->UnloadPlugins() == lPluginsNum);
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


long TestPluginManager::GetPluginsNum(const wchar_t* path,
        const wchar_t* ext, bool recursive)
{
    WIN32_FIND_DATAW fd;
    wchar_t szFileName[MAX_PATH];
    std::vector<std::wstring> arrSubPath;
    long nCount = 0;
    long nExtLen = wcslen(ext);

    wcsncpy_s(szFileName, MAX_PATH, path, MAX_PATH);
    PathAppendW(szFileName, L"*.*");

    HANDLE hFind = ::FindFirstFileW(szFileName, &fd);
    BOOL bContinue = (hFind != INVALID_HANDLE_VALUE);

    while (bContinue)
    {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (fd.cFileName[0] != L'.' && recursive)
            {
                wcsncpy_s(szFileName, MAX_PATH, path, MAX_PATH);
                PathAppendW(szFileName, fd.cFileName);
                arrSubPath.push_back(szFileName);
            }
        }
        else
        {
            long len = wcslen(fd.cFileName) - nExtLen;
            if (_wcsicmp(&fd.cFileName[len > 0 ? len : 0], ext) == 0)
            {
                wcsncpy_s(szFileName, MAX_PATH, path, MAX_PATH);
                PathAppendW(szFileName, fd.cFileName);
                if (wcslen(szFileName) > 0)
                {
                    nCount++;
                }
            }
        }
        bContinue = ::FindNextFileW(hFind, &fd);
    }
    ::FindClose(hFind);

    std::vector<std::wstring>::iterator it = arrSubPath.begin();
    for (; it != arrSubPath.end(); ++it)
    {
        nCount += GetPluginsNum(it->c_str(), ext, recursive);
    }

    return nCount;
}
