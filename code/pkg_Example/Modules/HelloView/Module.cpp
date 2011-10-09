#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include <Cx_CreateWnd.h>
#include <ClsID_ViewExample.h>
#include "WndA.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY_Wnd(CLSID_ExampleWndA, CWndA)
    XDEFINE_CLASSMAP_ENTRY_Wnd(CLSID_ExampleWndB, CWndA)
XEND_DEFINE_MODULE_MFCEXTDLL()
