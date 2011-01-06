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

/*! \file Ix_ObjectFactory.h
 *  \brief 定义创建对象的接口 Ix_ObjectFactory
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_CORE_IOBJECTFACTORY_H_
#define X3_CORE_IOBJECTFACTORY_H_

#include "Ix_Object.h"

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_ObjectFactory
 *  \brief 创建插件接口对象的接口
 *  \see   Ix_Object, Ix_Module
 */
interface Ix_ObjectFactory
{
	//! 返回指定的组件类是否已加载
	virtual bool IsCreatorRegister(const XCLSID& clsid) = 0;

	//! 创建一个组件类ID对应的对象实例
	virtual HRESULT CreateObject(const XCLSID& clsid, Ix_Object** ppv, HMODULE fromdll) = 0;

	//! 在所有插件模块中创建特定接口的单实例对象
	/*!
		\param iid 指定的接口ID
		\return 支持该接口的插件的个数，不论是否已创建
	*/
	virtual long CreateSpecialInterfaceObjects(const char* iid) = 0;

	//! 得到指定序号的插件模块中的指定接口的单实例对象
	/*!
		\param[in] index 指定的插件序号，与插件实际加载顺序有关，小于插件总数
		\param[in] iid 指定的接口ID
		\param[in,out] ppv 传入变量的地址，传回创建的对象，为NULL则不去创建
		\return 指定的插件序号越界时返回false，否则返回true，返回值与ppv无关
	*/
	virtual bool QuerySpecialInterfaceObject(long index, const char* iid, Ix_Object** ppv) = 0;

	//! 返回是否有类工厂函数被替换
	virtual bool HasCreatorReplaced(const XCLSID& clsid) = 0;
};

#endif // X3_CORE_IOBJECTFACTORY_H_
