/*! \file Ix_FileTransaction.h
 *  \brief Define interface of file operation with transaction: Ix_FileTransaction
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_UTIL_IFILETRANSACTION_H_
#define X3_UTIL_IFILETRANSACTION_H_

#include <Ix_Object.h>

X3CLSID_DEFINE(CLSID_FileTransaction, "66087749-6a2d-40b7-86d9-687664f91e1b");

//! interface of file operation with transaction.
/*!
    \interface Ix_FileTransaction
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileTransaction
*/
class Ix_FileTransaction : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_FileTransaction)

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
    virtual bool DeletePathFile(const wchar_t* filename, bool recycle = false) = 0;
};

#endif // X3_UTIL_IFILETRANSACTION_H_
