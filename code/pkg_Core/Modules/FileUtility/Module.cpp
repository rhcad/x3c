// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "Cx_FileUtility.h"
#include "Cx_FileTransaction.h"
#include "Cx_TempFolder.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY_Singleton(x3::CLSID_FileUtility, Cx_FileUtility)
    XDEFINE_CLASSMAP_ENTRY(x3::CLSID_FileTransaction, Cx_FileTransaction)
    XDEFINE_CLASSMAP_ENTRY(x3::CLSID_TempFolder, Cx_TempFolder)
XEND_DEFINE_MODULE_DLL()
