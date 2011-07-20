// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "x3core_i.c"
#include "dllmain.h"
#include <complugin_impl.h>

CoreComModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	return ATLDLLMAIN(hInstance, dwReason, lpReserved);
}
