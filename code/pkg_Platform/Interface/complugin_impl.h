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
#include "complugin_inc.h"

XBEGIN_DEFINE_MODULE()
XEND_DEFINE_MODULE()

#if _MSC_VER <= 1200
BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()
#endif

static CPluginManager*  s_loader = NULL;

bool AtlPluginImpl::IsInitialized()
{
    return x3GetObjectFactory() != NULL;
}

long AtlPluginImpl::Initialize(bool delay, LPCWSTR subdir, LPCWSTR plugins)
{
    ASSERT(!x3GetObjectFactory() && !s_loader);
    ASSERT(subdir && plugins);

    long count = 0;
    HMODULE instance = _AtlBaseModule.GetModuleInstance();

    s_loader = new CPluginManager;
    if (s_loader->LoadCorePlugins(subdir, instance, delay))
    {
        s_loader->GetPluginLoader()->RegisterPlugin(instance);
        count = s_loader->GetPluginLoader()->LoadPluginFiles(
            subdir, plugins, instance, delay);
        s_loader->GetPluginLoader()->InitializePlugins();
    }

    return count;
}

void AtlPluginImpl::Uninitialize()
{
    x3::SafeDelete(s_loader);
}

#endif // X3_COMPLUGIN_IMPL_H_
