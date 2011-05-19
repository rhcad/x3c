// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include "stdafx.h"
#include "BaseTest.h"
#include <PluginManager.h>

static CPluginManager s_loader;
static wchar_t s_datapath[MAX_PATH] = { 0 };
static wchar_t s_temppath[MAX_PATH] = { 0 };

BaseTest::BaseTest()
{
    MakeRootPath(s_datapath, L"TestData");
    MakeRootPath(s_temppath, L"Temp");
}

long BaseTest::LoadPlugins(const wchar_t* plugins, bool loadCore)
{
    // Initialize COM
#ifdef _MSC_VER
    VERIFY(SUCCEEDED(CoInitialize(NULL)));
#endif

    // Load plugins
    VERIFY(s_loader.LoadPluginManager(L"../Plugins"));

    if (loadCore)
    {
        VERIFY(s_loader.LoadCorePlugins(L"../Plugins"));
    }

    long count = 1;

    if (plugins && *plugins)
    {
        Ix_PluginLoader* pPluginLoader = s_loader.GetPluginLoader();
        ASSERT(pPluginLoader != NULL);

        count = pPluginLoader->LoadPluginFiles(L"../Plugins", plugins);
        pPluginLoader->InitializePlugins();
    }

    return count;
}

void BaseTest::UnloadPlugins()
{
    s_loader.Unload();      // Unload plugins
#ifdef _MSC_VER
    CoUninitialize();       // Free COM resource
#endif
}

Ix_PluginLoader* BaseTest::GetPluginLoader()
{
    return s_loader.GetPluginLoader();
}

void BaseTest::MakeRootPath(wchar_t* path, const wchar_t* name)
{
    wchar_t filename[MAX_PATH];

    if (0 == path[0])
    {
        GetModuleFileNameW(NULL, filename, MAX_PATH);
        PathRemoveFileSpecW(filename);
        PathAppendW(filename, L"UnitTests.ini");

        wcsncpy_s(path, MAX_PATH, filename, MAX_PATH);
        PathRemoveFileSpecW(path);      // bin\vc80\debug\tests
        PathRemoveFileSpecW(path);      // bin\vc80\debug
        PathRemoveFileSpecW(path);      // bin\vc80
        PathRemoveFileSpecW(path);      // bin
        PathAppendW(path, name);        // bin\name

#ifdef _MSC_VER
        GetPrivateProfileStringW(L"Path", name, path,
            path, MAX_PATH, filename);
        WritePrivateProfileStringW(L"Path", name, path, filename);
#endif
        PathAddBackslashW(path);

        SetFileAttributesNormal(filename);
    }
}

std::wstring BaseTest::MakeDataPath(const wchar_t* folder, const wchar_t* file)
{
    wchar_t filename[MAX_PATH];

    if (folder && *folder)
    {
        wcsncpy_s(filename, MAX_PATH, s_datapath, MAX_PATH);
        PathAppendW(filename, folder);
    }
    else
    {
        wcsncpy_s(filename, MAX_PATH, s_temppath, MAX_PATH);
        ::CreateDirectoryW(s_temppath, NULL);
    }

    if (file && *file)
    {
        PathAppendW(filename, file);
    }
    else
    {
        PathAddBackslashW(filename);
    }

    return filename;
}
