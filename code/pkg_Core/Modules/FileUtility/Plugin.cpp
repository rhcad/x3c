// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include "Cx_TempFolder.h"

OUTAPI void x3UninitializePlugin()
{
    Cx_TempFolder::DeleteFolders();
}
