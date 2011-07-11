#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "ComCreator.h"

XBEGIN_DEFINE_MODULE()
XEND_DEFINE_MODULE_DLL()

OUTAPI bool x3InitializePlugin()
{
    return CComCreator::Init();
}

OUTAPI void x3UninitializePlugin()
{
    CComCreator::Free();
}
