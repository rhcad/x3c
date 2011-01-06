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

/*! \file Cx_CfgDatabase.h
 *  \brief 定义数据库访问的实现类 Cx_CfgDatabase
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.9.25
 */
#ifndef _X3_CONFIGDB_CFGDATABASE_H
#define _X3_CONFIGDB_CFGDATABASE_H

#include <Ix_ConfigData.h>
#include <Ix_ConfigTransaction.h>
#include "Ix_InitDatabase.h"
#include "Ix_SQLParser.h"

class Cx_CfgRecordset;

//! 数据库访问的实现类
class Cx_CfgDatabase
	: public Ix_ConfigData
	, public Ix_ConfigTransaction
	, public Ix_InitDatabase
{
public:
	//! 构造函数
	Cx_CfgDatabase();

	//! 析构函数，自动关闭数据库
	virtual ~Cx_CfgDatabase();

public:
	//! 执行SQL语句，返回记录集
	_RecordsetPtr ExecuteSQL(LPCTSTR sql, LPCSTR file, long line);

	//! 返回受上一语句影响的行数
	long GetRecordsAffected();

	//! 得到一个表的主键字段(整数)的新记录ID
	bool GetRecordNewID(ULONG& newid, const std::wstring& table, 
		const std::wstring& field);

	//! 给定一个SELECT语句，查询记录条数
	bool GetRecordCount(long& count, const std::wstring& sqlSelect);

	//! 执行SQL语句，返回记录集
	ConfigIOSection OpenRecordset(const std::wstring& sqlSelect);

	//! 返回SQL指令翻译对象
	Ix_SQLParser* GetSQLParser();

protected:
	//! 关闭数据库连接
	void CloseConnection();

	//! 创建空节点对象
	void CreateNullSection(Cx_Interface<Ix_ConfigSection>& pIFSec);

protected:
	_ConnectionPtr		m_pCon;				//!< 数据库连接对象
	Ix_SQLParser*		m_pSQLParser;		//!< SQL指令翻译对象
	long				m_nRecordsAffected;	//!< 受上一语句影响的行数
	long				m_nModifiedCount;	//!< 数据库记录改动次数

protected:
	// Ix_InitDatabase
	virtual bool OpenConnection(const std::wstring& connection, 
		Ix_SQLParser* pSQLParser);

	// From Ix_ConfigTransaction
	virtual void BeginTransaction();
	virtual bool EndTransaction();
	virtual ULONG GetModifiedCount();

// From Ix_ConfigData
protected:
	//! 执行SQL语句，返回记录集
	/*! 本函数常用于读取多条记录，可以使用记录集的 GetSectionByIndex() 进行遍历读取，见 GetSectionByIndex() 的代码示例。
		\param sqlSelect SQL语句，以“SELECT ”开始，包含“FROM ”，可包含查询条件或排序等子语句
		\param ignore 忽略本参数
		\return 记录集对象 Cx_CfgRecordset 或空对象 Cx_CfgDbSection
	*/
	ConfigIOSection GetSection(LPCWSTR sqlSelect, bool ignore = true);

	//! 执行SQL语句和查询条件，返回记录集
	/*! 本函数可用于根据编号条件查找并修改记录，例如： \code
	CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
	CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", 0));
	secRec->SetString(L"title", L"test3");
	secRec->SetString(L"create_time", L"@CURDATE()");
	secRec->SetDate(L"update_date", 2010, 3, 10);
	VERIFY(CConfigTransaction(Cx_Ptr(secRec.P())).Submit());
		\endcode
		\param nullP 必须为NULL
		\param sqlSelect SQL语句，以“SELECT ”开始，包含“FROM ”，可包含查询条件等子语句
		\param field 查询条件中的第一个比较字段
		\param condValue field对应的值，用于在查询中比较相等
		\param ignore 忽略本参数
		\return 记录集对象 Cx_CfgRecordset 或空对象 Cx_CfgDbSection
	*/
	ConfigIOSection GetSection(
		Ix_ConfigSection* nullP, LPCWSTR sqlSelect, 
		LPCWSTR field, ULONG condValue, 
		bool ignore = true);

	//! 执行SQL语句和查询条件，返回记录集
	/*! 本函数常用于读取多条记录，可以使用记录集的 GetSectionByIndex() 进行遍历读取，见 GetSectionByIndex() 的代码示例。
		\param nullP 必须为NULL
		\param sqlSelect SQL语句，以“SELECT ”开始，包含“FROM ”，可包含查询条件等子语句
		\param field 查询条件中的第一个比较字段
		\param condValue field对应的值，用于在查询中比较相等
		\param ignore 忽略本参数
		\return 记录集对象 Cx_CfgRecordset 或空对象 Cx_CfgDbSection
	*/
	ConfigIOSection GetSection(
		Ix_ConfigSection* nullP, LPCWSTR sqlSelect, 
		LPCWSTR field, LPCWSTR condValue, 
		bool ignore = true);

	//! 执行SQL语句和查询条件，返回记录集
	/*!
		\param nullP 必须为NULL
		\param sqlSelect SQL语句，以“SELECT ”开始，包含“FROM ”，可包含查询条件等子语句
		\param field 查询条件中的第一个比较字段
		\param condValue field对应的值，用于在查询中比较相等
		\param fieldName2 查询条件中的第二个比较字段，为空则忽略该条件
		\param condValue2 fieldName2对应的值，用于在查询中比较相等，fieldName2非空时有效
		\param ignore 忽略本参数
		\return 记录集对象 Cx_CfgRecordset 或空对象 Cx_CfgDbSection
	*/
	ConfigIOSection GetSection(
		Ix_ConfigSection* nullP, LPCWSTR sqlSelect, 
		LPCWSTR field, LPCWSTR condValue, 
		LPCWSTR fieldName2, LPCWSTR condValue2, 
		bool ignore = true);

	//! 执行SQL语句和查询条件，返回记录集
	/*!
		\param nullP 必须为NULL
		\param sqlSelect SQL语句，以“SELECT ”开始，包含“FROM ”，可包含查询条件等子语句
		\param field 查询条件中的第一个比较字段
		\param condValue field对应的值，用于在查询中比较相等
		\param fieldName2 查询条件中的第二个比较字段，为空则忽略该条件
		\param condValue2 fieldName2对应的值，用于在查询中比较相等，fieldName2非空时有效
		\param ignore 忽略本参数
		\return 记录集对象 Cx_CfgRecordset 或空对象 Cx_CfgDbSection
	*/
	ConfigIOSection GetSection(
		Ix_ConfigSection* nullP, LPCWSTR sqlSelect, 
		LPCWSTR field, ULONG condValue, 
		LPCWSTR fieldName2, ULONG condValue2, 
		bool ignore = true);

	//! 返回记录集的记录条数
	/*! 代码示例： \code
	CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
	if (1 == secRecordset.GetSectionCount(L"")) { }
		\endcode
		\param pRecordset 记录集对象，通过 GetSection() 得到的
		\param ignore 忽略本参数
		\return 记录条数
	*/
	long GetSectionCount(Ix_ConfigSection* pRecordset, LPCWSTR ignore);

	//! 返回一个记录集的指定序号的记录对象
	/*! 本函数用于对记录集进行遍历读取，代码示例： \code
	CConfigIOSection secRecordset(pIFDb->GetSection(
		L"SELECT id,title FROM article WHERE id=4"));
	for (long iRec = 0; iRec < 99; iRec++)
	{
		CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", iRec));
		if (!secRec->IsValid())
			break;
		ULONG nID = secRec->GetUInt32(L"id");
		std::wstring wstrName = secRec->GetString(L"title");
	}
		\endcode
		\param pRecordset 记录集对象，通过 GetSection() 得到的
		\param ignore 忽略本参数
		\param index 记录的序号，取值必须为0、记录集的当前序号、或当前序号+1
		\return 记录对象 Cx_CfgRecord ,不为空
	*/
	ConfigIOSection GetSectionByIndex(
		Ix_ConfigSection* pRecordset, LPCWSTR ignore, long index);

	//! 增加一个新记录，待设置各个字段的值
	/*! 此时还未在数据库中增加记录。
		可以使用 \@NEWID 标记某个字段取值为(最大ID+1)，例如： \code
	CConfigIOSection secRec(pIFDb->AddSection(NULL, L"table"));
	secNewRec->SetString(L"id", L"@NEWID");
	secNewRec->SetString(L"title", L"test12");
	VERIFY(CConfigTransaction(Cx_Ptr(secNewRec.P())).Submit());
	ULONG nID = secNewRec->GetUInt32(L"id");
		\endcode
		\param nullP 必须为NULL
		\param table 数据库表名，例如“book”
		\return 新记录对象 Cx_CfgRecord
	*/
	ConfigIOSection AddSection(Ix_ConfigSection* nullP, LPCWSTR table);

	//! 不支持本函数
	bool RemoveSection(Ix_ConfigSection*);

	//! 删除指定条件的记录
	/*! 代码示例： \code
	pIFDb->RemoveChildren(NULL, L"book", L"type", L"sometype");
		\endcode
		\param nullP 必须为NULL
		\param table 数据库表名
		\param field 查询条件中的第一个比较字段，通常是主键字段
		\param condValue field对应的值，用于在查询中比较相等
		\return 删除的记录数
	*/
	long RemoveChildren(Ix_ConfigSection* nullP, LPCWSTR table, 
		LPCWSTR field = L"", LPCWSTR condValue = L"");

	//! 删除指定条件的记录
	/*! 代码示例： \code
	pIFDb->RemoveChildren(NULL, L"book", L"id", 1);
		\endcode
		\param nullP 必须为NULL
		\param table 数据库表名
		\param field 查询条件中的第一个比较字段，通常是主键字段
		\param condValue field对应的值，用于在查询中比较相等
		\return 删除的记录数
	*/
	long RemoveChildren(Ix_ConfigSection* nullP, LPCWSTR table, 
		LPCWSTR field, ULONG condValue);

	//! 得到一个数据节点的上一级节点(本函数不支持)
	ConfigIOSection GetParentSection(Ix_ConfigSection*);
};

#endif // _X3_CONFIGDB_CFGDATABASE_H
