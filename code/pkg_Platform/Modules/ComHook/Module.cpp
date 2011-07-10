#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "ComCreator.h"

extern bool HookModuleFunction(LPCSTR dllname, PROC oldproc, PROC newproc);

XBEGIN_DEFINE_MODULE()
XEND_DEFINE_MODULE_DLL()

#ifdef _MSC_VER
#pragma comment(lib, "ole32.lib")
#endif

OUTAPI bool x3InitializePlugin()
{
    return HookModuleFunction("ole32.dll", 
        CComCreator::c_oldfunc, (PROC)CComCreator::Hook_CoCreateInstance);
}

OUTAPI void x3UninitializePlugin()
{
    HookModuleFunction("ole32.dll", 
        (PROC)CComCreator::Hook_CoCreateInstance, CComCreator::c_oldfunc);
}
