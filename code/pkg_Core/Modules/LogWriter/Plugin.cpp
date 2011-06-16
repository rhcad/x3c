// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#include <UtilFunc/PluginInc.h>
#include "LogObserver.h"

static CLogObserver* s_pObserver = NULL;

OUTAPI bool x3InitializePlugin()
{
    ASSERT(!s_pObserver);
    s_pObserver = new CLogObserver;

    return true;
}

OUTAPI void x3UninitializePlugin()
{
    x3::SafeDelete(s_pObserver);
}
