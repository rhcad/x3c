#include <UtilFunc/PluginInc.h>
#include "DocObserverTest.h"

static CDocObserverTestOnRun* s_observer = NULL;

// Optional function to initialize this plugin when loaded by the plugin manager.
OUTAPI bool x3InitializePlugin()
{
    s_observer = new CDocObserverTestOnRun;
    return true;
}

// Optional function to free this plugin when unloaded by the plugin manager.
OUTAPI void x3UninitializePlugin()
{
    x3::SafeDelete(s_observer);
}
