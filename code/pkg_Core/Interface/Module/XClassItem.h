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

/*! \file XClassItem.h
 *  \brief 定义组件类注册数组的元素结构，内部文件
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_CLASSITEM_H_
#define X3_PLUGINIMPL_CLASSITEM_H_

#include "Ix_Object.h"

//! 组件类的对象创建函数
typedef Ix_Object* (STDMETHODCALLTYPE *PFNXObjectCreator)(HMODULE);

//! 组件类的正在使用的对象个数函数
typedef long (STDMETHODCALLTYPE *PFNXGetObjectCount)();

//! 组件类对象被其他模块使用计数函数
typedef long (STDMETHODCALLTYPE *PFNXRefCountByOthers)();

#define MIN_SINGLETON_TYPE	10

#pragma pack(push, 8)

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief 组件类的对象创建信息项
 *  \see   _xGetClassEntryTable, XBEGIN_DEFINE_MODULE
 */
struct _XCLASSMETA_ENTRY
{
	BYTE				type;				//!< 项类型, 见 MIN_SINGLETON_TYPE, XModuleMacro.h
	LPCSTR				className;			//!< 实现类的类名
	XCLSID				clsid;				//!< 组件类ID
	const char*			iidSpecial;			//!< 特定的单实例接口
	PFNXObjectCreator	pfnObjectCreator;	//!< 对象创建函数的地址
	PFNXGetObjectCount	pfnGetObjectCount;	//!< 未释放的对象个数
	PFNXRefCountByOthers	pfnRefCountByOthers;	//!< 被其他模块使用计数

	//! 供 XDEFINE_CLASSMAP_ENTRY 等宏使用的构造函数
	_XCLASSMETA_ENTRY(BYTE      _type, 
		LPCSTR                  _className, 
		const XCLSID&           _clsid, 
		const char*             _iidSpecial, 
		PFNXObjectCreator       _pfnObjectCreator, 
		PFNXGetObjectCount      _pfnGetObjectCount = NULL, 
		PFNXRefCountByOthers    _pfnRefCountByOthers = NULL)

		: type(_type), className(_className)
		, clsid(_clsid), iidSpecial(_iidSpecial)
		, pfnObjectCreator(_pfnObjectCreator)
		, pfnGetObjectCount(_pfnGetObjectCount)
		, pfnRefCountByOthers(_pfnRefCountByOthers)
	{
	}

	//! 默认构造函数，供 XEND_DEFINE_MODULE 使用
	_XCLASSMETA_ENTRY()
		: type(0), className(""), clsid(""), iidSpecial("")
		, pfnObjectCreator(NULL), pfnGetObjectCount(NULL)
		, pfnRefCountByOthers(NULL)
	{
	}

	//! 组件类信息项的数组，由 XBEGIN_DEFINE_MODULE 填充元素
	static const _XCLASSMETA_ENTRY s_classes[];
};

#pragma pack(pop)
#endif // X3_PLUGINIMPL_CLASSITEM_H_
