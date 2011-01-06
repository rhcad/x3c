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

/*! \file Cx_Object.h
 *  \brief 定义普通组件类的模板实现类 Cx_Object
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_OBJECT_H_
#define X3_PLUGINIMPL_OBJECT_H_

#include "Ix_Object.h"
#include <typeinfo.h>

HMODULE xGetModuleHandle();

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief 普通组件类的模板实现类，内部使用
 *  \note  供宏 XDEFINE_CLASSMAP_ENTRY 使用，模板参数 ClsType 为某个接口实现类
 *  \see   Cx_SingletonObject, XDEFINE_CLASSMAP_ENTRY
 */
template <class ClsType>
class Cx_Object
	: public ClsType
	, public Ix_Object
{
protected:
	Cx_Object(bool bRef = true) : m_lRefCount(bRef ? 1 : 0)
	{
		InterlockedIncrement(&ObjectCount());
	}

	virtual ~Cx_Object()
	{
		InterlockedDecrement(&ObjectCount());
	}

protected:
	virtual void AddRef(HMODULE fromdll)
	{
		if (fromdll != xGetModuleHandle())
		{
			InterlockedIncrement(&RefCountByOthers());
		}
		InterlockedIncrement(&m_lRefCount);
	}

	virtual void Release(HMODULE fromdll)
	{
		if (fromdll != xGetModuleHandle())
		{
			InterlockedDecrement(&RefCountByOthers());
		}
		if (0 == InterlockedDecrement(&m_lRefCount))
		{
			delete this;
		}
	}

	virtual const char* GetClassName() const
	{
		return typeid(*this).name();
	}

public:
	static Ix_Object* STDMETHODCALLTYPE CreateObject(HMODULE fromdll)
	{
		Cx_Object<ClsType>* p = new Cx_Object<ClsType>(false);
		p->AddRef(fromdll);
		return p;
	}

	static long STDMETHODCALLTYPE GetObjectCount()
	{
		return ObjectCount();
	}

	static long STDMETHODCALLTYPE GetRefCountByOthers()
	{
		return RefCountByOthers();
	}

private:
	long		m_lRefCount;

	static long& ObjectCount()
	{
		static long s_lObjCount = 0;
		return s_lObjCount;
	}

	static long& RefCountByOthers()
	{
		static long s_lRefCount = 0;
		return s_lRefCount;
	}
};

#endif // X3_PLUGINIMPL_OBJECT_H_
