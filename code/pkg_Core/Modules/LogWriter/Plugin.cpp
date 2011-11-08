// x3c - C++ PluginFramework
#include <UtilFunc/PluginInc.h>
#include "LogObserver.h"

static CLogObserver* s_pObserver = NULL;

OUTAPI bool x3InitializePlugin()
{
    if (!s_pObserver)
    {
        s_pObserver = new CLogObserver;
    }

    return true;
}

OUTAPI void x3UninitializePlugin()
{
    x3::SafeDelete(s_pObserver);
}

OUTAPI Ix_LogObserver* GetLogObserver()
{
    if (!s_pObserver)
    {
        s_pObserver = new CLogObserver;
    }

    return s_pObserver;
}
