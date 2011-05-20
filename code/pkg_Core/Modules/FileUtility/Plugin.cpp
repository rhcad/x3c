// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <PluginInc.h>
#include "Cx_TempFolder.h"

OUTAPI void UninitializePlugin()
{
    Cx_TempFolder::DeleteFolders();
}
