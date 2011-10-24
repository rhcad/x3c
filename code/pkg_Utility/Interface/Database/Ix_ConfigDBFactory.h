/*! \file Ix_ConfigDBFactory.h
 *  \brief Define database I/O operator's creator interface: Ix_ConfigDBFactory
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_UTIL_ICONFIGDBFACTORY_H_
#define X3_UTIL_ICONFIGDBFACTORY_H_

#include <XComPtr.h>

X3CLSID_DEFINE(CLSID_ConfigDBFactory, "6f3ca83f-6193-48ce-a188-24b2afb45432");

//! Database I/O operator's creator interface
/*! 将数据库的增删改查以数据节点(Ix_ConfigData, Cx_ConfigSection)的简化方式进行操作。\n
    Ix_ConfigData接口的部分含义重新定义了，见 Cx_CfgDatabase 对应函数的说明。\n
    在增加记录时可以使用 \@NEWID 标记某个字段取值为(最大ID+1)；\n
    在增加或修改记录时可以使用以@开头的函数名，例如 CURDATE(), CURTIME(), NOW() ，内部会自动换为对应的数据库函数名。
    \interface Ix_ConfigDBFactory
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_ConfigDBFactory, Cx_CfgDatabase
*/
class Ix_ConfigDBFactory : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_ConfigDBFactory)

    //! 打开Access数据库文件
    /*!
        \param filename 数据库文件全名(*.mdb, *.accdb)
        \param dbuser 数据库用户名
        \param password 该用户对应的密码
        \return 数据库数据访问对象(Ix_ConfigData)，为空对象时表示失败
        \see Ix_ConfigData, Ix_ConfigTransaction, Cx_CfgDatabase
    */
    virtual Cx_Ptr OpenAccessDB(
        const std::wstring& filename, 
        const std::wstring& dbuser = L"", 
        const std::wstring& password = L"") = 0;

    //! 打开SQLServer数据库
    /*!
        \param server 数据库服务器名
        \param database 数据库名
        \param dbuser 数据库用户名
        \param password 该用户对应的密码
        \return 数据库数据访问对象(Ix_ConfigData)，为空对象时表示失败
        \see Ix_ConfigData, Ix_ConfigTransaction, Cx_CfgDatabase
    */
    virtual Cx_Ptr OpenSQLServerDB(
        const std::wstring& server, 
        const std::wstring& database, 
        const std::wstring& dbuser = L"", 
        const std::wstring& password = L"") = 0;
};

#endif // X3_UTIL_ICONFIGDBFACTORY_H_
