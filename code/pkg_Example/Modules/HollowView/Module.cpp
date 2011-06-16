#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include <Cx_CreateWnd.h>
#include <ClsID_ViewExample.h>
#include "WndA.h"

X3BEGIN_MODULE()
    X3_CLASS_ENTRY_Wnd(X3CLS_ExampleWndA, CWndA)
    X3_CLASS_ENTRY_Wnd(X3CLS_ExampleWndB, CWndA)
X3END_MODULE_MFCEXTDLL()
