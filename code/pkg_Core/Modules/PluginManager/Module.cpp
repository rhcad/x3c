// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "stdafx.h"
#include "Cx_PluginLoader.h"

class Cx_PluginLoaderOut
	: public Cx_PluginLoader
	, public Ix_Object
{
public:
	Cx_PluginLoaderOut()
	{
	}

private:
	void AddRef(HMODULE) {}
	void Release(HMODULE) {}
	const char* GetClassName() const { return "Cx_PluginLoader"; }
};

static Cx_PluginLoaderOut s_loader;

extern "C" __declspec(dllexport) Ix_ObjectFactory* xGetRegisterBank()
{
	return &s_loader;
}

extern "C" __declspec(dllexport) HMODULE xGetMainModuleHandle()
{
	return s_loader.GetMainModuleHandle();
}

HMODULE xGetModuleHandle()
{
	return NULL;
}

HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
	return s_loader.CreateObject(clsid, ppv, xGetModuleHandle());
}

#ifdef _USRDLL
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	hModule; dwReason; lpReserved;
	return TRUE;
}
#endif // _USRDLL
