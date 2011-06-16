#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "Cx_ChangeManager.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY_Singleton(x3::CLSID_ChangeManager, Cx_ChangeManager)
XEND_DEFINE_MODULE_DLL()
