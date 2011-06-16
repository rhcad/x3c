// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "Cx_TextUtil.h"
#include "Cx_GuidGenerator.h"
#include "Cx_ClipboardUtil.h"

X3BEGIN_MODULE()
    X3_CLASS_Singleton(X3CLS_TextUtil, Cx_TextUtil)
#ifdef _WIN32
    X3_CLASS_Singleton(X3CLS_GuidGenerator, Cx_GuidGenerator)
    X3_CLASS_Singleton(X3CLS_ClipboardUtil, Cx_ClipboardUtil)
#endif
X3END_MODULE_DLL()
