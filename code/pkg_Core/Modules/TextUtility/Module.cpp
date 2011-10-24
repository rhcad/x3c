// x3c - C++ PluginFramework
#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "Cx_TextUtil.h"
#include "Cx_GuidGenerator.h"
#include "Cx_ClipboardUtil.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY_Singleton(x3::CLSID_TextUtil, Cx_TextUtil)
#ifdef _WIN32
    XDEFINE_CLASSMAP_ENTRY_Singleton(x3::CLSID_GuidGenerator, Cx_GuidGenerator)
    XDEFINE_CLASSMAP_ENTRY_Singleton(x3::CLSID_ClipboardUtil, Cx_ClipboardUtil)
#endif
XEND_DEFINE_MODULE_DLL()
