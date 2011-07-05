/*! \file Cx_CfgDatabase.h
 *  \brief Define database I/O operator implement class: Cx_CfgDatabase
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.9.25
 */
// Changes:
// 2010-01-12, Zhang Yun Gui: Add readonly param in OpenConnection()

#ifndef _X3_CONFIGDB_CFGDATABASE_H
#define _X3_CONFIGDB_CFGDATABASE_H

#include <Xml/Ix_ConfigData.h>
#include <Xml/Ix_ConfigTransaction.h>
#include "Ix_InitDatabase.h"
#include "Ix_SQLParser.h"
#include "msado15.tlh"

class Cx_CfgRecordset;

//! Database I/O operator implement class.
class Cx_CfgDatabase
    : public Ix_ConfigData
    , public Ix_ConfigTransaction
    , public Ix_InitDatabase
{
    X3BEGIN_CLASS_DECLARE(Cx_CfgDatabase)
        X3DEFINE_INTERFACE_ENTRY(Ix_ConfigData)
        X3DEFINE_INTERFACE_ENTRY(Ix_ConfigTransaction)
        X3DEFINE_INTERFACE_ENTRY(Ix_InitDatabase)
    X3END_CLASS_DECLARE()
protected:
    //! 构造函数
    Cx_CfgDatabase();

    //! 析构函数，自动关闭数据库
    virtual ~Cx_CfgDatabase();

public:
    //! 执行SQL语句，返回记录集
    _RecordsetPtr ExecuteSQL(LPCTSTR sql, const char* file, long line);

    //! 返回受上一语句影响的行数
    long GetRecordsAffected();

    //! 得到一个表的主键字段(整数)的新记录ID
    bool GetRecordNewID(ULONG& newid, const std::wstring& table, 
        const std::wstring& field);

    //! 给定一个SELECT语句，查询记录条数
    bool GetRecordCount(long& count, const std::wstring& sqlSelect);

    //! 执行SQL语句，返回记录集
    ConfigSection OpenRecordset(const std::wstring& sqlSelect);

    //! 返回SQL指令翻译对象
    Ix_SQLParser* GetSQLParser();

protected:
    //! 关闭数据库连接
    void CloseConnection();

    //! 创建空节点对象
    void CreateNullSection(Cx_Interface<Ix_ConfigSection>& pIFSec);

protected:
    _ConnectionPtr      m_pCon;             //!< 数据库连接对象
    Ix_SQLParser*       m_pSQLParser;       //!< SQL指令翻译对象
    long                m_nRecordsAffected; //!< 受上一语句影响的行数
    long                m_nModifiedCount;   //!< 数据库记录改动次数

protected:
    // Ix_InitDatabase
    virtual bool OpenConnection(const std::wstring& connection, 
        Ix_SQLParser* pSQLParser, bool readonly = false);

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
    ConfigSection GetSection(const wchar_t* sqlSelect, bool ignore = true);

    //! 执行SQL语句和查询条件，返回记录集
    /*! 本函数可用于根据编号条件查找并修改记录，例如： \code
    Cx_ConfigSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
    Cx_ConfigSection secRec(secRecordset.GetSectionByIndex(L"", 0));
    secRec->SetString(L"title", L"test3");
    secRec->SetString(L"create_time", L"@CURDATE()");
    secRec->SetDate(L"update_date", 2010, 3, 10);
    VERIFY(Cx_ConfigTransaction(Cx_Ptr(secRec.P())).Submit());
        \endcode
        \param nullP 必须为NULL
        \param sqlSelect SQL语句，以“SELECT ”开始，包含“FROM ”，可包含查询条件等子语句
        \param field 查询条件中的第一个比较字段
        \param condValue field对应的值，用于在查询中比较相等
        \param ignore 忽略本参数
        \return 记录集对象 Cx_CfgRecordset 或空对象 Cx_CfgDbSection
    */
    ConfigSection GetSection(
        Ix_ConfigSection* nullP, const wchar_t* sqlSelect, 
        const wchar_t* field, ULONG condValue, 
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
    ConfigSection GetSection(
        Ix_ConfigSection* nullP, const wchar_t* sqlSelect, 
        const wchar_t* field, const wchar_t* condValue, 
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
    ConfigSection GetSection(
        Ix_ConfigSection* nullP, const wchar_t* sqlSelect, 
        const wchar_t* field, const wchar_t* condValue, 
        const wchar_t* fieldName2, const wchar_t* condValue2, 
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
    ConfigSection GetSection(
        Ix_ConfigSection* nullP, const wchar_t* sqlSelect, 
        const wchar_t* field, ULONG condValue, 
        const wchar_t* fieldName2, ULONG condValue2, 
        bool ignore = true);

    //! 返回记录集的记录条数
    /*! 代码示例： \code
    Cx_ConfigSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
    if (1 == secRecordset.GetSectionCount(L"")) { }
        \endcode
        \param pRecordset 记录集对象，通过 GetSection() 得到的
        \param ignore 忽略本参数
        \return 记录条数
    */
    long GetSectionCount(Ix_ConfigSection* pRecordset, const wchar_t* ignore);

    //! 返回一个记录集的指定序号的记录对象
    /*! 本函数用于对记录集进行遍历读取，代码示例： \code
    Cx_ConfigSection secRecordset(pIFDb->GetSection(
        L"SELECT id,title FROM article WHERE id=4"));
    for (long iRec = 0; iRec < 99; iRec++)
    {
        Cx_ConfigSection secRec(secRecordset.GetSectionByIndex(L"", iRec));
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
    ConfigSection GetSectionByIndex(
        Ix_ConfigSection* pRecordset, const wchar_t* ignore, long index);

    //! 增加一个新记录，待设置各个字段的值
    /*! 此时还未在数据库中增加记录。
        可以使用 \@NEWID 标记某个字段取值为(最大ID+1)，例如： \code
    Cx_ConfigSection secRec(pIFDb->AddSection(NULL, L"table"));
    secNewRec->SetString(L"id", L"@NEWID");
    secNewRec->SetString(L"title", L"test12");
    VERIFY(Cx_ConfigTransaction(Cx_Ptr(secNewRec.P())).Submit());
    ULONG nID = secNewRec->GetUInt32(L"id");
        \endcode
        \param nullP 必须为NULL
        \param table 数据库表名，例如“book”
        \return 新记录对象 Cx_CfgRecord
    */
    ConfigSection AddSection(Ix_ConfigSection* nullP, const wchar_t* table);

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
    long RemoveChildren(Ix_ConfigSection* nullP, const wchar_t* table, 
        const wchar_t* field = L"", const wchar_t* condValue = L"");

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
    long RemoveChildren(Ix_ConfigSection* nullP, const wchar_t* table, 
        const wchar_t* field, ULONG condValue);

    //! Returns the parent node of the specified node.(This function is not supported.)
    ConfigSection GetParentSection(Ix_ConfigSection*);
};

#endif // _X3_CONFIGDB_CFGDATABASE_H
