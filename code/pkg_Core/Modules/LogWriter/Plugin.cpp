// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <PluginInc.h>
#include "LogObserver.h"

static CLogObserver* s_pObserver = NULL;

OUTAPI bool InitializePlugin()
{
    ASSERT(!s_pObserver);
    s_pObserver = new CLogObserver;

    return true;
}

OUTAPI void UninitializePlugin()
{
    SafeDelete(s_pObserver);
}
