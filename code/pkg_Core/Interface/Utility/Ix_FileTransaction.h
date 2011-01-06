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

/*! \file Ix_FileTransaction.h
 *  \brief 定义文件事务实用操作的接口 Ix_FileTransaction
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_IFILETRANSACTION_H_
#define X3_UTIL_IFILETRANSACTION_H_

#include <Ix_Object.h>

const XCLSID CLSID_FileTransaction("66087749-6a2d-40b7-86d9-687664f91e1b");

//! 文件操作事务的接口
/*!
	\interface Ix_FileTransaction
	\ingroup _GROUP_UTILITY_
	\see CLSID_FileTransaction
*/
interface Ix_FileTransaction
{
	//! 从挂起状态回滚事务
	virtual void Rollback() = 0;

	//! 得到该事务的深度序号
	virtual long GetLevel() const = 0;

	//! 返回是否正在回滚事务
	virtual bool IsRollbacking() const = 0;

	//! 删除一个目录或文件
	/*!
		\param filename 目录或文件的文件全名
		\param recycle true表示放进回收站，false表示直接删除
		\return 是否能删除该目录或文件. 文件全名为空或文件不存在则返回true
	*/
	virtual bool DeletePathFile(LPCWSTR filename, bool recycle = false) = 0;
};

#endif // X3_UTIL_IFILETRANSACTION_H_
