#include "stdafx.h"

// Optional function to initialize this plugin when loaded by the plugin manager.
extern "C" __declspec(dllexport) bool InitializePlugin()
{
    return true;
}

// Optional function to free this plugin when unloaded by the plugin manager.
extern "C" __declspec(dllexport) void UninitializePlugin()
{
}
