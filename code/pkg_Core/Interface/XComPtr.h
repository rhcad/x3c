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

/*! \file XComPtr.h
 *  \brief 定义智能指针类 Cx_Interface 和 Cx_Ptr
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_CORE_XCOMPTR_H_
#define X3_CORE_XCOMPTR_H_

#include "Ix_Object.h"

// 创建类ID对应的对象. 在 XModuleImpl.h 或 XComCreator.h 中实现
HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv);

// 返回当前模块的DLL句柄. 在 XModuleImpl.h 或 XComCreator.h 中实现
HMODULE xGetModuleHandle();

#ifndef _CPPRTTI
#error must enable RTTI (compiled with /GR)
#endif

class Cx_Ptr;

//! 封装特定接口的智能指针类
/*! 模板参数 IF_Type 为非 Ix_Object 的接口名。\n
	本类用到的 xCreateObject() 在 XModuleImpl.h 或 XComCreator.h 中实现。
	\ingroup _GROUP_PLUGIN_CORE_
	\see Cx_Ptr, xCreateObject
*/
template <class IF_Type>
class Cx_Interface
{
	typedef Cx_Interface<IF_Type> thisClass;
public:
	//! 缺省构造函数，构造空对象
	Cx_Interface() : m_pInterface(NULL), m_pObj(NULL)
	{
	}

	//! 从一个Cx_Ptr对象构造
	Cx_Interface(const Cx_Ptr& src) : m_pInterface(NULL), m_pObj(NULL)
	{
		if (src.P())
		{
			m_pInterface = dynamic_cast<IF_Type*>(src.P());
			if (m_pInterface)
			{
				m_pObj = src.P();
				m_pObj->AddRef(xGetModuleHandle());
			}
		}
	}

#if _MSC_VER > 1200 // not VC60

	//! 拷贝构造函数
	Cx_Interface(const thisClass& src)
		: m_pInterface(src.m_pInterface), m_pObj(src.m_pObj)
	{
		if (m_pInterface)
		{
			m_pObj->AddRef(xGetModuleHandle());
		}
	}

	//! 从一个同类型的接口指针构造
	Cx_Interface(IF_Type* pInterface) : m_pInterface(pInterface), m_pObj(NULL)
	{
		if (m_pInterface)
		{
			m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
			//ASSERT(m_pObj != NULL);
			m_pObj->AddRef(xGetModuleHandle());
		}
	}

#endif // _MSC_VER
	
	//! 从一个接口指针构造
	template <class IF_Type2>
	explicit Cx_Interface(IF_Type2* pInterface) : m_pInterface(NULL), m_pObj(NULL)
	{
		if (pInterface)
		{
			m_pInterface = dynamic_cast<IF_Type*>(pInterface);
			if (m_pInterface)
			{
				m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
				//ASSERT(m_pObj != NULL);
				m_pObj->AddRef(xGetModuleHandle());
			}
		}
	}

	//! 从一个智能指针构造
	template <class IF_Type2>
	explicit Cx_Interface(const Cx_Interface<IF_Type2>& pIF)
		: m_pInterface(NULL), m_pObj(NULL)
	{
		if (pIF)
		{
			m_pInterface = dynamic_cast<IF_Type*>(pIF.P());
			if (m_pInterface)
			{
				m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
				//ASSERT(m_pObj != NULL);
				m_pObj->AddRef(xGetModuleHandle());
			}
		}
	}
	
	//! 给定组件类ID创建对象实例
	explicit Cx_Interface(const XCLSID& clsid) : m_pInterface(NULL), m_pObj(NULL)
	{
		if (S_OK == xCreateObject(clsid, &m_pObj))
		{
			m_pInterface = dynamic_cast<IF_Type*>(m_pObj);
			if (NULL == m_pInterface)
			{
				m_pObj->Release(xGetModuleHandle());
				m_pObj = NULL;
			}
		}
	}
	
	//! 析构函数
	~Cx_Interface()
	{
		Unload();
	}
	
	
	//! 返回对象接口指针
	inline IF_Type* P() const
	{
		return m_pInterface;
	}
	
	//! 调用对象接口函数的操作符
	inline IF_Type* operator->() const
	{
		return m_pInterface;
	}

	//! 拷贝赋值操作符，复制一个接口指针
	template <class IF_Type2>
	thisClass& operator=(IF_Type2* pInterface)
	{
		Unload();

		if (pInterface)
		{
			m_pInterface = dynamic_cast<IF_Type*>(pInterface);
			if (m_pInterface)
			{
				m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
				//ASSERT(m_pObj != NULL);
				m_pObj->AddRef(xGetModuleHandle());
			}
		}

		return *this;
	}

	//! 拷贝赋值操作符，复制一个智能指针
	template <class IF_Type2>
	thisClass& operator=(const Cx_Interface<IF_Type2>& pIF)
	{
		return operator=(pIF.P());
	}

	//! 拷贝赋值操作符，复制同类型的智能指针
	thisClass& operator=(const thisClass& src)
	{
		if (this != &src)
		{
			Load(src.m_pInterface);
		}

		return *this;
	}
	
	//! 拷贝赋值操作符，复制Cx_Ptr智能指针
	thisClass& operator=(const Cx_Ptr& src)
	{
		Unload();

		if (src.P())
		{
			m_pInterface = dynamic_cast<IF_Type*>(src.P());
			if (m_pInterface)
			{
				m_pObj = src.P();
				m_pObj->AddRef(xGetModuleHandle());
			}
		}

		return *this;
	}

	//! 赋值为NULL的操作符
	thisClass& operator=(const int nul)
	{
		nul;//ASSERT(0 == nul);
		Unload();
		return *this;
	}

	//! 与 NULL 比较是否相等
	bool operator==(const int nul) const
	{
		nul;//ASSERT(0 == nul);
		return m_pInterface == NULL;
	}

	//! 与 NULL 比较是否相等
	bool operator!=(const int nul) const
	{
		nul;//ASSERT(0 == nul);
		return m_pInterface != NULL;
	}
	
	//! 返回两个对象指针是否指向相同的对象
	bool operator==(const IF_Type* pInterface) const
	{
		return m_pInterface == pInterface;
	}
	
	//! 返回两个对象指针是否指向不同的对象
	bool operator!=(const IF_Type* pInterface) const
	{
		return m_pInterface != pInterface;
	}
	
	//! 返回两个对象指针是否指向相同的对象
	bool operator==(const thisClass& src) const
	{
		return m_pInterface == src.m_pInterface;
	}
	
	//! 返回两个对象指针是否指向不同的对象
	bool operator!=(const thisClass& src) const
	{
		return m_pInterface != src.m_pInterface;
	}

	//! 相当于 IsNotNull 的转换操作符函数
	inline operator bool() const
	{
		return m_pInterface != NULL;
	}

	//! 相当于 IsNull 的转换操作符函数
	inline bool operator!() const
	{
		return NULL == m_pInterface;
	}
	
	//! 返回是否没有对象
	inline bool IsNull() const
	{
		return NULL == m_pInterface;
	}
	
	//! 返回是否有对象
	inline bool IsNotNull() const
	{
		return m_pInterface != NULL;
	}
	
	
	//! 立即释放对象指针的引用
	/*! 本对象析构时会自动调用本函数，当对象不再被引用时会自动释放
	*/
	void Release()
	{
		Unload();
	}
	
	//! 分离接口指针
	IF_Type* DetachInterface()
	{
		IF_Type* pIF = m_pInterface;
		m_pInterface = NULL;
		m_pObj = NULL;
		return pIF;
	}
	
	//! 接管一个接口指针
	bool AttachInterface(IF_Type* pIF)
	{
		Unload();
		m_pInterface = pIF;
		m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
		return (m_pObj != NULL || NULL == m_pInterface);
	}
	
	//! 接管一个接口指针
	bool AttachInterface(Ix_Object* pIF)
	{
		Unload();

		if (pIF)
		{
			m_pInterface = dynamic_cast<IF_Type*>(pIF);
			if (m_pInterface)
			{
				m_pObj = dynamic_cast<Ix_Object*>(m_pInterface);
				//ASSERT(m_pObj != NULL);
			}
			else
			{
				pIF->Release(xGetModuleHandle());
				pIF = NULL;
				return false;
			}
		}

		return true;
	}
	
	//! 给定组件类ID创建有本接口的对象实例
	bool Create(const XCLSID& clsid)
	{
		Unload();
		
		if (S_OK == xCreateObject(clsid, &m_pObj))
		{
			m_pInterface = dynamic_cast<IF_Type*>(m_pObj);
			if (NULL == m_pInterface)
			{
				m_pObj->Release(xGetModuleHandle());
				m_pObj = NULL;
			}
		}
		
		return m_pInterface != NULL;
	}
	
private:
	void Unload()
	{
		if (m_pObj)
		{
			m_pObj->Release(xGetModuleHandle());
			m_pObj = NULL;
			m_pInterface = NULL;
		}
	}
	
	void Load(IF_Type* pIF)
	{
		Ix_Object* pObj = dynamic_cast<Ix_Object*>(pIF);
		if (m_pObj != pObj)
		{
			if (pObj)
			{
				pObj->AddRef(xGetModuleHandle());
			}
			if (m_pObj)
			{
				m_pObj->Release(xGetModuleHandle());
			}
			m_pObj = pObj;
			m_pInterface = pIF;
		}
	}
	
private:
	IF_Type*	m_pInterface;
	Ix_Object*	m_pObj;
};

//! 封装Ix_Object接口的智能指针类
/*! 本类用到的 xCreateObject() 在 XModuleImpl.h 或 XComCreator.h 中实现。
	\ingroup _GROUP_PLUGIN_CORE_
	\see Ix_Object, Cx_Interface, xCreateObject
*/
class Cx_Ptr
{
public:
	//! 默认构造函数
	Cx_Ptr() : m_pInterface(NULL)
	{
	}

	//! 拷贝构造函数
	Cx_Ptr(const Cx_Ptr& src) : m_pInterface(src.m_pInterface)
	{
		if (m_pInterface)
		{
			m_pInterface->AddRef(xGetModuleHandle());
		}
	}
	
	//! 从一个接口指针构造
	template <class IF_Type>
	explicit Cx_Ptr(IF_Type* pInterface) : m_pInterface(NULL)
	{
		m_pInterface = dynamic_cast<Ix_Object*>(pInterface);
		if (m_pInterface)
		{
			m_pInterface->AddRef(xGetModuleHandle());
		}
	}

	//! 从一个特定类型的智能指针构造
	template <class IF_Type>
	explicit Cx_Ptr(const Cx_Interface<IF_Type>& pIF) : m_pInterface(NULL)
	{
		m_pInterface = dynamic_cast<Ix_Object*>(pIF.P());
		if (m_pInterface)
		{
			m_pInterface->AddRef(xGetModuleHandle());
		}
	}
	
	//! 给定组件类ID创建对象实例
	explicit Cx_Ptr(const XCLSID& clsid) : m_pInterface(NULL)
	{
		xCreateObject(clsid, &m_pInterface);
	}
	
	//! 析构函数
	~Cx_Ptr()
	{
		Unload();
	}
	
	
	//! 返回对象接口指针
	Ix_Object* P() const
	{
		return m_pInterface;
	}
	
	//! 拷贝赋值操作符，复制一个接口指针
	template <class IF_Type>
	Cx_Ptr& operator=(IF_Type* pInterface)
	{
		Unload();

		m_pInterface = dynamic_cast<Ix_Object*>(pInterface);
		if (m_pInterface)
		{
			m_pInterface->AddRef(xGetModuleHandle());
		}

		return *this;
	}

	//! 拷贝赋值操作符，复制一个特定类型的智能指针
	template <class IF_Type>
	Cx_Ptr& operator=(const Cx_Interface<IF_Type>& pIF)
	{
		return operator=(pIF.P());
	}
	
	//! 拷贝赋值操作符，复制同类型的智能指针
	Cx_Ptr& operator=(const Cx_Ptr& src)
	{
		if (this != &src)
		{
			Load(src.m_pInterface);
		}

		return *this;
	}

	//! 赋值为NULL的操作符
	Cx_Ptr& operator=(const int nul)
	{
		nul;//ASSERT(0 == nul);
		Unload();
		return *this;
	}

	//! 与 NULL 比较是否相等
	bool operator==(const int nul) const
	{
		nul;//ASSERT(0 == nul);
		return m_pInterface == NULL;
	}

	//! 与 NULL 比较是否相等
	bool operator!=(const int nul) const
	{
		nul;//ASSERT(0 == nul);
		return m_pInterface != NULL;
	}
	
	//! 返回两个对象指针是否指向相同的对象
	bool operator==(const Ix_Object* pInterface) const
	{
		return m_pInterface == pInterface;
	}
	
	//! 返回两个对象指针是否指向不同的对象
	bool operator!=(const Ix_Object* pInterface) const
	{
		return m_pInterface != pInterface;
	}
	
	//! 返回两个对象指针是否指向相同的对象
	bool operator==(const Cx_Ptr& src) const
	{
		return m_pInterface == src.m_pInterface;
	}
	
	//! 返回两个对象指针是否指向不同的对象
	bool operator!=(const Cx_Ptr& src) const
	{
		return m_pInterface != src.m_pInterface;
	}

	//! 相当于 IsNotNull 的转换操作符函数
	inline operator bool() const
	{
		return m_pInterface != NULL;
	}

	//! 相当于 IsNull 的转换操作符函数
	inline bool operator!() const
	{
		return NULL == m_pInterface;
	}
	
	//! 返回是否没有对象
	inline bool IsNull() const
	{
		return NULL == m_pInterface;
	}
	
	//! 返回是否有对象
	inline bool IsNotNull() const
	{
		return m_pInterface != NULL;
	}
	
	
	//! 立即释放对象指针的引用
	/*! 本对象析构时会自动调用本函数，当对象不再被引用时会自动释放
	*/
	void Release()
	{
		Unload();
	}
	
	//! 分离接口指针
	Ix_Object* DetachInterface()
	{
		Ix_Object* pIF = m_pInterface;
		m_pInterface = NULL;
		return pIF;
	}
	
	//! 接管一个接口指针
	void AttachInterface(Ix_Object* pIF)
	{
		Unload();
		m_pInterface = pIF;
	}
	
	//! 给定组件类ID创建对象实例
	bool Create(const XCLSID& clsid)
	{
		Unload();
		return S_OK == xCreateObject(clsid, &m_pInterface);
	}
	
private:
	void Unload()
	{
		if (m_pInterface)
		{
			m_pInterface->Release(xGetModuleHandle());
			m_pInterface = NULL;
		}
	}
	
	void Load(Ix_Object* pIF)
	{
		if (m_pInterface != pIF)
		{
			if (pIF)
			{
				pIF->AddRef(xGetModuleHandle());
			}
			if (m_pInterface)
			{
				m_pInterface->Release(xGetModuleHandle());
			}
			m_pInterface = pIF;
		}
	}
	
private:
	Ix_Object*	m_pInterface;
};

#endif // X3_CORE_XCOMPTR_H_
