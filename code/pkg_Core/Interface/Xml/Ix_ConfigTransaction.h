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

/*! \file Ix_ConfigTransaction.h
 *  \brief 定义写配置事务的辅助类 CConfigTransaction
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_XML_CONFIGTRANSACTION_H_
#define X3_XML_CONFIGTRANSACTION_H_

#include <XComPtr.h>

//! 配置数据保存事务的接口
/*! Ix_ConfigSection 和 Ix_ConfigData 一般都可转换到该接口
	\see CConfigTransaction
*/
interface Ix_ConfigTransaction
{
	//! 准备写配置
	virtual void BeginTransaction() = 0;

	//! 结束写配置
	virtual bool EndTransaction() = 0;

	//! 返回内容改变的总次数，可用于比较某次是否改变
	virtual ULONG GetModifiedCount() = 0;
};

//! 写配置事务的辅助类
/*! 在要保存配置的函数中，用本类在函数内定义局部变量，
	标明即将调用改变内容的函数，退出函数析构时就可永久保存配置
	\ingroup _GROUP_PLUGIN_XML_
	\see Ix_ConfigSection, Ix_ConfigData
*/
class CConfigTransaction
{
public:
	//! 构造函数，准备写配置
	CConfigTransaction(const Cx_Ptr& obj) : m_trans(obj)
	{
		if (m_trans)
		{
			m_trans->BeginTransaction();
		}
	}

#ifdef X3_XML_ICONFIGDATA_H_
	//! 构造函数，准备写配置
	CConfigTransaction(const Cx_Interface<Ix_ConfigData>& p) : m_trans(p)
	{
		if (m_trans)
		{
			m_trans->BeginTransaction();
		}
	}
#endif

	//! 析构函数，结束写配置
	~CConfigTransaction()
	{
		Submit();
	}

	//! 结束写配置
	bool Submit()
	{
		bool ret = false;

		if (m_trans)
		{
			ret = m_trans->EndTransaction();
			m_trans.Release();
		}

		return ret;
	}

private:
	Cx_Interface<Ix_ConfigTransaction>	m_trans;
};

#endif // X3_XML_CONFIGTRANSACTION_H_
