#include "stdafx.h"
#include <XModuleMacro.h>
#include <XModuleImpl.h>

#include "Cx_ChangeManager.h"

XBEGIN_DEFINE_MODULE()
	XDEFINE_CLASSMAP_ENTRY_Singleton(CLSID_ChangeManager, Cx_ChangeManager)
XEND_DEFINE_MODULE_WIN32DLL()
