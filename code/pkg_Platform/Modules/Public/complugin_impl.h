/*! \file complugin_impl.h
 *  \brief Implement COM plugin.
 *  \note Include this file in dllmain.cpp instead of XModuleImpl.h or XComCreator.h .
 *  \see complugin_inc.h
 */
#ifndef X3_COMPLUGIN_IMPL_H_
#define X3_COMPLUGIN_IMPL_H_

#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>
#include <PluginManager/PluginManager.h>

XBEGIN_DEFINE_MODULE()
XEND_DEFINE_MODULE()

#if _MSC_VER <= 1200
BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()
ATL::_ATL_OBJMAP_ENTRY* GetObjectMap() { return ObjectMap; }
#endif

static CPluginManager*  s_loader = NULL;
HINSTANCE AtlPluginImpl::hInstance = NULL;

bool AtlPluginImpl::IsPluginLoaded()
{
    return x3GetObjectFactory() != NULL;
}

long AtlPluginImpl::LoadPlugins(bool delay, LPCWSTR subdir, LPCWSTR plugins)
{
    ASSERT(!x3GetObjectFactory() && !s_loader);
    ASSERT(subdir && plugins);

    long count = 0;

    s_loader = new CPluginManager;
    if (s_loader->LoadCorePlugins(subdir, hInstance, delay))
    {
        s_loader->GetPluginLoader()->RegisterPlugin(hInstance);
        count = s_loader->GetPluginLoader()->LoadPluginFiles(
            subdir, plugins, hInstance, delay);
        s_loader->GetPluginLoader()->InitializePlugins();
    }

    return count;
}

void AtlPluginImpl::UnloadPlugins()
{
    x3::SafeDelete(s_loader);
}

#endif // X3_COMPLUGIN_IMPL_H_
