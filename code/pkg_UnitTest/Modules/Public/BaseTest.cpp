// x3c - C++ PluginFramework
#include <UnitTestInc.h>
#include "BaseTest.h"
#include <PluginManager/PluginManager.h>
#include <PluginManager/Ix_AppWorkPath.h>

static CPluginManager s_loader;
static wchar_t s_datapath[MAX_PATH] = { 0 };
static wchar_t s_temppath[MAX_PATH] = { 0 };

BaseTest::BaseTest()
{
}

long BaseTest::LoadPlugins(const wchar_t* plugins, bool loadCore)
{
    if (NULL == s_loader.Handle())
    {
#ifdef _WIN32
        VERIFY(SUCCEEDED(CoInitialize(NULL)));
#endif
        VERIFY(s_loader.LoadPluginManager(L"../plugins"));
    }

    if (loadCore)
    {
        VERIFY(s_loader.LoadCorePlugins(L"../plugins"));
    }

    long count = 1;

    if (plugins && *plugins)
    {
        Ix_PluginLoader* pPluginLoader = s_loader.GetPluginLoader();
        ASSERT(pPluginLoader != NULL);

        count = pPluginLoader->LoadPluginFiles(L"../plugins", plugins);
        pPluginLoader->InitializePlugins();
    }

    return count;
}

void BaseTest::UnloadPlugins()
{
    s_loader.Unload();      // Unload plugins
#ifdef _WIN32
    CoUninitialize();       // Free COM resource
#endif
}

void BaseTest::MakeRootPath(wchar_t* path, const wchar_t* name)
{
    if (0 == path[0])
    {
        wchar_t filename[MAX_PATH];

        wcscpy_s(filename, MAX_PATH, x3::GetAppWorkPath().c_str());
        PathAppendW(filename, L"tests.ini");

        wcscpy_s(path, MAX_PATH, filename);
        PathRemoveFileSpecW(path);      // bin\vc80\debug
        if (_wcsicmp(name, L"temp") != 0)
        {
            PathRemoveFileSpecW(path);  // bin\vc80
            PathRemoveFileSpecW(path);  // bin
        }
        PathAppendW(path, name);        // bin\name

#ifdef _WIN32
        x3SetFileAttributesNormal(filename);
        GetPrivateProfileStringW(L"Path", name, path,
            path, MAX_PATH, filename);
        WritePrivateProfileStringW(L"Path", name, path, filename);
#endif
        PathAddBackslashW(path);
    }
}

std::wstring BaseTest::MakeDataPath(const wchar_t* folder, const wchar_t* file)
{
    wchar_t filename[MAX_PATH] = { 0 };

    if (folder && *folder && _wcsicmp(folder, L"temp") != 0)
    {
        MakeRootPath(s_datapath, L"testdata");
        wcscpy_s(filename, MAX_PATH, s_datapath);
        PathAppendW(filename, folder);
    }
    else
    {
        if (0 == s_temppath[0])
        {
            MakeRootPath(s_temppath, L"temp");
            ::CreateDirectoryW(s_temppath, NULL);
        }
        wcscpy_s(filename, MAX_PATH, s_temppath);
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
