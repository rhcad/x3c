// x3c - C++ PluginFramework
#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "Cx_StringTable.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY_Singleton(x3::CLSID_StringTable, Cx_StringTable)
XEND_DEFINE_MODULE_DLL()
