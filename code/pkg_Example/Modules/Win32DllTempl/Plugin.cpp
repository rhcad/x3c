#include <UtilFunc/PluginInc.h>

// Optional function to initialize this plugin when loaded by the plugin manager.
OUTAPI bool x3InitializePlugin()
{
    return true;
}

// Optional function to free this plugin when unloaded by the plugin manager.
OUTAPI void x3UninitializePlugin()
{
}
