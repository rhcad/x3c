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

/*! \file Ix_StringTable.h
 *  \brief 定义本地化字符串表的接口 Ix_StringTable
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_XML_ISTRINGTABLE_H_
#define X3_XML_ISTRINGTABLE_H_

const XCLSID CLSID_StringTable("b8c36b29-59c3-4db2-be43-fd4982e6e71d");

//! 本地化字符串表的接口
/*! 本地化字符串XML文件存放于主程序目录的 Translations/Strings 目录下
	\interface Ix_StringTable
	\ingroup _GROUP_PLUGIN_XML_
	\see CLSID_StringTable
*/
interface Ix_StringTable
{
	//! 得到一个模块的指定ID名称对应的字符串值
	/*!
		\param[out] value 实际字符串值
		\param[in] name 包含模块名和ID名称的标识串，格式为以@开头接上“Module:IDS_XXX”
		\param[out] module 填充name中的模块名
		\param[out] id 填充name中的串ID名称
		\return 是否读取到非空值
	*/
	virtual bool GetValue(std::wstring& value, const std::wstring& name, 
		std::wstring& module, std::wstring& id) = 0;

	//! 得到一个模块的指定ID名称对应的字符串值
	/*!
		\param[out] value 实际字符串值
		\param[in] module 模块名
		\param[in] id 串ID名称
		\return 是否读取到非空值
	*/
	virtual bool GetValue(std::wstring& value, 
		const std::wstring& module, const std::wstring& id) = 0;

	//! 加载指定目录下的字符串XML文件
	/*!
		\param path 字符串XML文件所在目录的决定路径
		\return 加载的文件数
	*/
	virtual long LoadFiles(const std::wstring& path) = 0;

	//! 得到一个模块的指定ID名称对应的字符串值
	/*!
		\param[in] module 模块名
		\param[in] id 串ID名称
		\param[out] hasvalue 填充是否读取到非空值，为NULL则忽略
		\return 实际字符串值
	*/
	virtual std::wstring GetValue(const std::wstring& module, 
		const std::wstring& id, bool* hasvalue = NULL) = 0;
};

#ifdef X3_CORE_XCOMPTR_H_
//! 得到一个模块的指定ID名称对应的字符串值
/*!
	\param[in] module 模块名
	\param[in] id 串ID名称
	\param[out] hasvalue 填充是否读取到非空值，为NULL则忽略
	\return 实际字符串值，空串表示没有值
*/
inline std::wstring GetStringValue(const std::wstring& module, 
	const std::wstring& id, bool* hasvalue = NULL)
{
	Cx_Interface<Ix_StringTable> pIFTable(CLSID_StringTable);
	return pIFTable ? pIFTable->GetValue(module, id, hasvalue) : std::wstring();
}
#endif

#endif // X3_XML_ISTRINGTABLE_H_
