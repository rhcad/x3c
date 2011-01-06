#include "stdafx.h"
#include <afxdllx.h>
#include <XModuleMacro.h>
#include <XModuleImpl.h>

#include "Cx_Example2.h"

XBEGIN_DEFINE_MODULE()
	XDEFINE_CLASSMAP_ENTRY(CLSID_Example, Cx_Example2)
XEND_DEFINE_MODULE_MFCEXTDLL()
