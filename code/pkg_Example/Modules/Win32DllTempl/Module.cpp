#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "Cx_Example.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY(CLSID_Example, Cx_Example)
XEND_DEFINE_MODULE_DLL()
