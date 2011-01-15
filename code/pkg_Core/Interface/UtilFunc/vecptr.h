/*! \file vecptr.h
 *  \brief 定义对象数组函数
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef UTILFUNC_VECPTR_H_
#define UTILFUNC_VECPTR_H_

#include "vecfunc.h"
#include <XComPtr.h>

//! 得到对象数组中指定序号的对象
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL数组变量，例如" vector<ObjPtr> arr; "
    \param index 元素序号
    \return 数组中的元素对象，或空对象表示越界
*/
template<class _Ta> inline
Cx_Ptr GetPtrIndexOf(const _Ta& arr, long index)
{
    return IsValidIndexOf(arr, index) ? Cx_Ptr(arr[index]) : Cx_Ptr();
}

//! Cx_Ptr数组的查找算法函数
template<class IF_Type>
struct FindByPtr : std::binary_function<Cx_Ptr, Cx_Ptr, bool>
{
    bool operator()(const Cx_Ptr& p1, const Cx_Ptr& p2) const
    {
        if (p1.P() == p2.P())
            return true;

        if (p1.IsNotNull() != p2.IsNotNull())
            return false;

        Cx_Interface<IF_Type> pIF1 (p1);
        Cx_Interface<IF_Type> pIF2 (p2);

        return pIF1 == pIF2;
    }
};

//! 数值对的数组的查找算法函数，数值对的第二项为Cx_Ptr
template<class IF_Type, class Pair_Type>
struct FindPairByPtr : std::binary_function<Pair_Type, Pair_Type, bool>
{
    bool operator()(const Pair_Type& v1, const Pair_Type& v2) const
    {
        const Cx_Ptr& p1 = v1.second;
        const Cx_Ptr& p2 = v2.second;

        if (p1.P() == p2.P())
            return true;

        if (p1.IsNotNull() != p2.IsNotNull())
            return false;

        Cx_Interface<IF_Type> pIF1 (p1);
        Cx_Interface<IF_Type> pIF2 (p2);

        return pIF1 == pIF2;
    }
};

//! 根据元素值删除数组元素
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL数组变量，元素类型为Cx_Ptr，例如 vector<Cx_Ptr>
    \param p 要删除的元素值
    \return 是否已删除
*/
template<class IF_Type, class _Ta> inline
bool erase_value(_Ta& arr, Cx_Ptr& p)
{
    return erase_if(arr, std::bind2nd(FindByPtr<IF_Type>(), p));
}

//! 根据元素值删除数组元素
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL数组变量，元素类型为Pair_Type，例如 vector<Pair_Type>
    \param p 要删除的数值对，第二项为Cx_Ptr
    \return 是否已删除
*/
template<class IF_Type, class _Ta, class Pair_Type> inline
bool erase_pair(_Ta& arr, Pair_Type& p)
{
    return erase_if(arr, std::bind2nd(FindPairByPtr<IF_Type, Pair_Type>(), p));
}

//! 根据元素值查找数组元素的位置
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL数组变量，元素类型为Cx_Ptr，例如 vector<Cx_Ptr>
    \param p 元素值
    \return 元素位置，-1表示没找到
*/
template<class IF_Type, class _Ta> inline
long find_value(const _Ta& arr, const Cx_Ptr& p)
{
    return find_if(arr, std::bind2nd(FindByPtr<IF_Type>(), p));
}

//! 根据元素值查找数组元素的位置
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL数组变量，元素类型为Pair_Type，例如 vector<Pair_Type>
    \param p 元素值，数值对，第二项为Cx_Ptr
    \return 元素位置，-1表示没找到
*/
template<class IF_Type, class _Ta, class Pair_Type> inline
long find_pair(_Ta& arr, Pair_Type& p)
{
    return find_if(arr, std::bind2nd(FindPairByPtr<IF_Type, Pair_Type>(), p));
}

#endif // UTILFUNC_VECPTR_H_
