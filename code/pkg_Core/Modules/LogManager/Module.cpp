// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "Cx_LogManager.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY_Singleton(x3::CLSID_LogManager, Cx_LogManager)
XEND_DEFINE_MODULE_DLL()
