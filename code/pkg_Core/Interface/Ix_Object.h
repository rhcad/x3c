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

/*! \file Ix_Object.h
 *  \brief 定义对象基本接口 Ix_Object 和 XCLSID
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_CORE_IOBJECT_H_
#define X3_CORE_IOBJECT_H_

//! \cond IGNORED
#ifndef interface
#include <objbase.h>
#endif
//! \endcond

/*! \interface Ix_Object
 *  \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief 对象基本接口
 *  \note  外界不要直接调用其接口函数。\n 所有组件类都通过 Cx_Object 和 Cx_SingletonObject 等
 *         模板类来实现该接口，该接口供智能指针类 Cx_Ptr 和 Cx_Interface 使用。
 *  \see 智能指针类: Cx_Ptr, Cx_Interface
 */
interface Ix_Object
{
	//! 增加引用计数, 由智能指针类调用
	virtual void AddRef(HMODULE fromdll) = 0;

	//! 减少引用计数, 自动释放对象, 由智能指针类调用
	virtual void Release(HMODULE fromdll) = 0;

	//! 获取对应的对象类名
	virtual const char* GetClassName() const = 0;
};

//! 组件类唯一编号
/*! \ingroup _GROUP_PLUGIN_CORE_
    例如 \code
	const XCLSID CLSID_ExampleTool("97380b78-a3b4-4784-ba07-c928561988c8");
	\endcode
*/
class XCLSID
{
public:
	//! 默认构造函数
	XCLSID()
	{
		m_clsid[0] = 0;
	}

	//! 给定UUID串构造
	XCLSID(const char* clsid)
	{
		lstrcpynA(m_clsid, clsid ? clsid : "", 40);
	}

	//! 拷贝构造函数
	XCLSID(const XCLSID& src)
	{
		lstrcpyA(m_clsid, src.m_clsid);
	}

	//! 赋值为一个UUID串的操作符函数
	XCLSID& operator=(const char* clsid)
	{
		lstrcpynA(m_clsid, clsid ? clsid : "", 40);
		return *this;
	}

	//! 赋值操作符函数
	XCLSID& operator=(const XCLSID& src)
	{
		lstrcpyA(m_clsid, src.m_clsid);
		return *this;
	}

	//! 相等操作符函数
	bool operator==(const XCLSID& src) const
	{
		return lstrcmpA(m_clsid, src.m_clsid) == 0;
	}

	//! 不相等操作符函数
	bool operator!=(const XCLSID& src) const
	{
		return lstrcmpA(m_clsid, src.m_clsid) != 0;
	}

	//! 大于操作符函数
	bool operator>(const XCLSID& src) const
	{
		return lstrcmpA(m_clsid, src.m_clsid) > 0;
	}

	//! 小于操作符函数
	bool operator<(const XCLSID& src) const
	{
		return lstrcmpA(m_clsid, src.m_clsid) < 0;
	}

	//! 返回内部的ID串值
	const char* str() const
	{
		return m_clsid;
	}

	//! 返回是否为非空的UUID串
	bool valid() const
	{
		return m_clsid[0] != 0;
	}

private:
	char m_clsid[40];
};

#endif // X3_CORE_IOBJECT_H_
