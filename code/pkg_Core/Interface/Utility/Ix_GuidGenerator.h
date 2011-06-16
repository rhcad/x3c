/*! \file Ix_GuidGenerator.h
 *  \brief 定义GUID生成器的接口 Ix_GuidGenerator
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_IGUIDGENERATOR_H_
#define X3_UTIL_IGUIDGENERATOR_H_

#include <XComPtr.h>

X3CLSID_DEFINE(CLSID_GuidGenerator, "8c14f0c5-7795-4ec3-b13a-982f653a700a");

//! 全局唯一编号生成器的接口
/*!
    \interface Ix_GuidGenerator
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_GuidGenerator
*/
class Ix_GuidGenerator
{
public:
    virtual ~Ix_GuidGenerator() {}

    //! 生成新的GUID串
    virtual std::wstring CreateGuid(bool withBrackets = false) = 0;

    //! 得到没有两端大括号的GUID串
    virtual std::wstring RemoveGuidBrackets(const std::wstring& uid) = 0;

    //! 得到当前日期时间的字符串，格式为“YYYY-MM-DD HH:MM:SS”
    virtual std::wstring GetCurrentTimeString(bool hasYear = true) = 0;

    //! 创建唯一ID，当前进程运行时有效
    virtual ULONG CreateID(long type = 0) = 0;
};

namespace x3 {

//! 生成新的GUID串
/*!
    \ingroup _GROUP_UTILITY_
    \see RemoveGuidBrackets, Ix_GuidGenerator
*/
inline std::wstring CreateGuid(bool withBrackets = false)
{
    Cx_Interface<Ix_GuidGenerator> pIFGenerator(x3::CLSID_GuidGenerator);
#ifdef ASSERT
    ASSERT(pIFGenerator.IsNotNull());
#endif
    return pIFGenerator->CreateGuid(withBrackets);
}

//! 得到没有两端大括号的GUID串
/*!
    \ingroup _GROUP_UTILITY_
    \see CreateGuid, Ix_GuidGenerator
*/
inline std::wstring RemoveGuidBrackets(const std::wstring& uid)
{
    Cx_Interface<Ix_GuidGenerator> pIFGenerator(x3::CLSID_GuidGenerator);
#ifdef ASSERT
    ASSERT(pIFGenerator.IsNotNull());
#endif
    return pIFGenerator->RemoveGuidBrackets(uid);
}

//! 创建唯一ID，当前进程运行时有效
/*!
    \ingroup _GROUP_UTILITY_
    \see Ix_GuidGenerator
*/
inline ULONG GuidCreateID(long type = 0)
{
    Cx_Interface<Ix_GuidGenerator> pIFGenerator(x3::CLSID_GuidGenerator);
#ifdef ASSERT
    ASSERT(pIFGenerator.IsNotNull());
#endif
    return pIFGenerator->CreateID(type);
}

//! 得到当前日期时间的字符串，格式为“YYYY-MM-DD HH:MM:SS”
/*!
    \ingroup _GROUP_UTILITY_
*/
inline std::wstring GetCurrentTimeString(bool hasYear = true)
{
    Cx_Interface<Ix_GuidGenerator> pIFGenerator(x3::CLSID_GuidGenerator);
#ifdef ASSERT
    ASSERT(pIFGenerator.IsNotNull());
#endif
    return pIFGenerator->GetCurrentTimeString(hasYear);
}

} // x3

#endif // X3_UTIL_IGUIDGENERATOR_H_
