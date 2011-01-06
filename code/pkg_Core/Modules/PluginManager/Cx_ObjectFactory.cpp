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

// author: Zhang Yun Gui, Tao Jian Lin
// v2: 2011.1.5, change class-table to hash_map

#include "StdAfx.h"
#include "Cx_ObjectFactory.h"

Cx_ObjectFactory::Cx_ObjectFactory()
{
}

Cx_ObjectFactory::~Cx_ObjectFactory()
{
}

bool Cx_ObjectFactory::IsCreatorRegister(const XCLSID& clsid)
{
	_XCLASSMETA_ENTRY* pEntry = FindEntry(clsid);
	return pEntry && pEntry->pfnObjectCreator;
}

HRESULT Cx_ObjectFactory::CreateObject(const XCLSID& clsid, Ix_Object** ppv, 
									   HMODULE fromdll)
{
	ASSERT(clsid.valid() && ppv != NULL);
	*ppv = NULL;

	_XCLASSMETA_ENTRY* pEntry = FindEntry(clsid);

	if (pEntry && pEntry->pfnObjectCreator)
	{
		*ppv = pEntry->pfnObjectCreator(fromdll);
		ASSERT(*ppv);
		return S_OK;
	}
	else
	{
		return E_NOTIMPL;
	}
}

long Cx_ObjectFactory::CreateSpecialInterfaceObjects(const char* iid)
{
	ASSERT(iid && *iid);

	long count = 0;
	CLSMAP::const_iterator it = m_mapEntry.begin();

	for (; it != m_mapEntry.end(); ++it)
	{
		const _XCLASSMETA_ENTRY& cls = it->second;
		if (lstrcmpiA(iid, cls.iidSpecial) == 0)
		{
			Ix_Object* pIF = NULL;
			pIF = (cls.pfnObjectCreator)(xGetModuleHandle());
			ASSERT(pIF);
			pIF->Release(xGetModuleHandle());
			count++;
		}
	}

	return count;
}

bool Cx_ObjectFactory::QuerySpecialInterfaceObject(
		long index, const char* iid, Ix_Object** ppv)
{
	bool bRet = IsValidIndexOf(m_vecModule, index) && ppv != NULL;
	if (!bRet)
	{
		return false;
	}

	*ppv = NULL;

	const VCLSID& clsids = m_vecModule[index].clsids;
	VCLSID::const_iterator it = clsids.begin();

	for (; it != clsids.end(); ++it)
	{
		CLSMAP::const_iterator mit = m_mapEntry.find(it->str());

		if (mit != m_mapEntry.end()
			&& lstrcmpiA(iid, mit->second.iidSpecial) == 0)
		{
			*ppv = (mit->second.pfnObjectCreator)(xGetModuleHandle());
			return true;
		}
	}

	return false;
}

bool Cx_ObjectFactory::HasCreatorReplaced(const XCLSID& clsid)
{
	clsid;
	return false;
}

_XCLASSMETA_ENTRY* Cx_ObjectFactory::FindEntry(const XCLSID& clsid)
{
	CLSMAP::iterator it = m_mapEntry.find(clsid.str());
	return (it == m_mapEntry.end()) ? NULL : &it->second;
}

int Cx_ObjectFactory::FindModule(HMODULE hModule)
{
	int i = GetSize(m_vecModule);
	while (--i >= 0 && m_vecModule[i].hModule != hModule) ;

	return i;
}

Ix_Module* Cx_ObjectFactory::GetModule(HMODULE hModule)
{
	int index = FindModule(hModule);
	if (index >= 0)
	{
		return m_vecModule[index].pModule;
	}

	typedef Ix_Module* (*FUNC_MODULE)(Ix_ObjectFactory*, HMODULE);
	FUNC_MODULE pfn = (FUNC_MODULE)GetProcAddress(hModule, "_xGetModuleInterface");

	if (pfn != NULL)
	{
		Ix_Module* pModule = (*pfn)(this, hModule);
		return pModule;
	}
	else
	{
		return NULL;
	}
}

long Cx_ObjectFactory::RegisterClassEntryTable(HMODULE hModule)
{
	int index = FindModule(hModule);
	ASSERT(index >= 0);	// must call RegisterPlugin before

	Ix_Module* pModule = GetModule(hModule);
	ASSERT(pModule);	// must call RegisterPlugin before

	if (!m_vecModule[index].clsids.empty())
	{
		return GetSize(m_vecModule[index].clsids);
	}

	typedef DWORD (*FUNC_GET)(DWORD*, DWORD*, _XCLASSMETA_ENTRY*, DWORD);
	FUNC_GET pfn = (FUNC_GET)GetProcAddress(hModule, "_xGetClassEntryTable");

	if (!pfn)		// is not a plugin
	{
		return -1;
	}

	DWORD buildInfo = 0;
	int nClassCount = (*pfn)(&buildInfo, NULL, NULL, 0);

	if (nClassCount <= 0)
	{
		return 0;
	}

	std::vector<_XCLASSMETA_ENTRY> table(nClassCount);
	DWORD size = sizeof(_XCLASSMETA_ENTRY);

	nClassCount = (*pfn)(NULL, &size, &table[0], nClassCount);

	for (int i = 0; i < nClassCount; i++)
	{
		_XCLASSMETA_ENTRY& cls = table[i];

		if (cls.clsid.valid())
		{
			RegisterClass(index, cls);
		}
		if (cls.iidSpecial && *cls.iidSpecial)
		{
			char tmpclsid[40] = { 0 };

			sprintf_s(tmpclsid, 40, "iid%lx:%d", hModule, i);
			cls.clsid = XCLSID(tmpclsid);
			RegisterClass(index, cls);
		}
	}

	return nClassCount;
}

bool Cx_ObjectFactory::RegisterClass(int moduleIndex, const _XCLASSMETA_ENTRY& cls)
{
	ASSERT(moduleIndex >= 0 && cls.clsid.valid() && cls.pfnObjectCreator);
	_XCLASSMETA_ENTRY* pOldCls = FindEntry(cls.clsid);

	if (pOldCls)
	{
		char msg[256] = { 0, 0 };
		sprintf_s(msg, 256, 
			"The classid '%s' is already registered by '%s', then '%s' register fail.", 
			cls.clsid.str(), pOldCls->className, cls.className);
		ASSERT_MESSAGE(false, msg);
		return false;
	}

	m_mapEntry[cls.clsid.str()] = cls;
	m_vecModule[moduleIndex].clsids.push_back(cls.clsid);

	return true;
}

void Cx_ObjectFactory::ReleaseModule(HMODULE hModule)
{
	int index = FindModule(hModule);
	ASSERT(index >= 0);

	const VCLSID& clsids = m_vecModule[index].clsids;
	VCLSID::const_iterator it = clsids.begin();

	for (; it != clsids.end(); ++it)
	{
		CLSMAP::iterator mit = m_mapEntry.find(it->str());
		if (mit != m_mapEntry.end())
		{
			m_mapEntry.erase(mit);
		}
	}

	if (m_vecModule[index].bOwner)
	{
		FreeLibrary(hModule);
	}

	m_vecModule.erase(m_vecModule.begin() + index);
}
