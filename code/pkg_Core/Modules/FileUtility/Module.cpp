// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "Cx_FileUtility.h"
#include "Cx_FileTransaction.h"
#include "Cx_TempFolder.h"

X3BEGIN_MODULE()
    X3_CLASS_Singleton(X3CLS_FileUtility, Cx_FileUtility)
    X3_CLASS_ENTRY(X3CLS_FileTransaction, Cx_FileTransaction)
    X3_CLASS_ENTRY(X3CLS_TempFolder, Cx_TempFolder)
X3END_MODULE_DLL()
