#include <UtilFunc/PluginInc.h>
#include <PluginManager/PluginManager.h>
#include <PluginManager/XComCreator.h>
#include <UtilFunc/ConvStr.h>
#include <PluginManager/Ix_PluginLoader2.h>

#ifdef _MSC_VER                 // hide warnings
#pragma warning(disable:4505)   // unreferenced local function has been removed
#pragma warning (push, 2)
#pragma warning(disable:4701)   // potentially uninitialized local variable used
#pragma warning(disable:4706)   // assignment within conditional expression
#endif
#include "x3core_wrap.cxx"
#ifdef _MSC_VER                 // hide warnings
#pragma warning (pop)
#endif

static CPluginManager   s_loader;
static HMODULE          s_hmod = NULL;

#ifdef APIENTRY
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        s_hmod = (HMODULE)hModule;
    }
    return TRUE;
}
#endif

bool LoadCorePlugins()
{
    return s_loader.LoadCorePlugins(L"../plugins", s_hmod);
}

bool LoadAllPlugins()
{
    if (!s_loader.LoadCorePlugins(L"../plugins", s_hmod))
        return false;

    Ix_PluginLoader* loader = s_loader.GetPluginLoader();
    long n;

    n = loader->LoadPlugins(L"../plugins");
    n = loader->LoadPlugins(L"../plugins", L".pyd");
    n = loader->InitializePlugins();

    return n >= 0;
}

bool LoadPluginFiles(const char* files)
{
    if (!s_loader.Handle())
    {
        s_loader.LoadPluginManager(L"../plugins", s_hmod);
    }

    Ix_PluginLoader* loader = s_loader.GetPluginLoader();
    
    return loader->LoadPluginFiles(L"../plugins", x3::a2w(files).c_str(), s_hmod) > 0
        && loader->InitializePlugins() > 0;
}

void UnloadPlugins()
{
    s_loader.Unload();
}

std::vector<std::string> GetPluginFiles()
{
    Cx_Interface<Ix_PluginLoader2> loader(s_loader.GetPluginLoader());
    ASSERT(loader.IsNotNull());

    std::vector<std::string> filenames;
    HMODULE hdll;
    std::wstring filename;

    for (int i = 0; loader->GetPluginFileName(i, hdll, filename); i++)
    {
        filenames.push_back(x3::w2a(filename));
    }

    return filenames;
}
