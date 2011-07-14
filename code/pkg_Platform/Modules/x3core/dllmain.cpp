// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "x3core_i.c"
#include "dllmain.h"

CoreComModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}

#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

XBEGIN_DEFINE_MODULE()
XEND_DEFINE_MODULE()
