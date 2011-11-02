#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "ComCreator.h"
#include <PluginManager/Ix_PluginLoader2.h>

XBEGIN_DEFINE_MODULE()
XEND_DEFINE_MODULE_DLL()

OUTAPI bool x3InitializePlugin()
{
    Cx_Interface<Ix_PluginLoader2> loader(x3GetObjectFactory());
    HMODULE hmod;
    std::wstring file;
    int count = 0;

    for (int i = 1; loader->GetPluginFileName(i, hmod, file); i++)
    {
        if (CComCreator::Hook(hmod))
        {
            count++;
        }
    }
    if (CComCreator::Hook(NULL))
    {
        count++;
    }

    return true;
}

OUTAPI void x3UninitializePlugin()
{
    Cx_Interface<Ix_PluginLoader2> loader(x3GetObjectFactory());
    HMODULE hmod;
    std::wstring file;
    int count = 0;

    for (int i = 0; loader->GetPluginFileName(i, hmod, file); i++)
    {
        count += CComCreator::Unhook(hmod) ? 1 : 0;
    }
    count += CComCreator::Unhook(NULL) ? 1 : 0;

    CComCreator::Free();
}
