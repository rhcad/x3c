#include "stdafx.h"
#include <XModuleMacro.h>
#include <XModuleImpl.h>

#include "Cx_Example.h"

XBEGIN_DEFINE_MODULE()
	XDEFINE_CLASSMAP_ENTRY(CLSID_Example, Cx_Example)
XEND_DEFINE_MODULE_WIN32DLL()
