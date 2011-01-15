// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include "stdafx.h"
#include "Cx_TempFolder.h"

extern "C" __declspec(dllexport) void UninitializePlugin()
{
    Cx_TempFolder::DeleteFolders();
}
