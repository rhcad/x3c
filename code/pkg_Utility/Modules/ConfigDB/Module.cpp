// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "ClsID_Internal.h"
#include "Cx_ConfigFactory.h"
#include "Cx_CfgDatabase.h"

X3BEGIN_MODULE()
    X3_CLASS_Singleton(X3CLS_ConfigDBFactory, Cx_ConfigFactory)
    X3_CLASS_ENTRY(X3CLS_CfgDatabase, Cx_CfgDatabase)
X3END_MODULE_MFCEXTDLL()
