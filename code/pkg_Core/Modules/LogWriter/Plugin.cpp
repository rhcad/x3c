// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include "stdafx.h"
#include "LogObserver.h"

static CLogObserver* s_pObserver = NULL;

extern "C" __declspec(dllexport) bool InitializePlugin()
{
    ASSERT(!s_pObserver);
    s_pObserver = new CLogObserver;

    return true;
}

extern "C" __declspec(dllexport) void UninitializePlugin()
{
    SafeDelete(s_pObserver);
}
