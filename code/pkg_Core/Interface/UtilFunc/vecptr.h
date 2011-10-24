/*! \file vecptr.h
 *  \brief Define functions of pointer container.
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef UTILFUNC_VECPTR_H_
#define UTILFUNC_VECPTR_H_

#include "vecfunc.h"
#include <XComPtr.h>

namespace x3 {

//! Returns a object of the specified index in a array container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL vector variable. eg: " vector<ObjPtr> arr; "
    \param index The specified index of element.
    \return a object in a array container or null object if out of range.
*/
template<class _Ta> inline
Cx_Ptr GetPtrIndexOf(const _Ta& arr, long index)
{
    return IsValidIndexOf(arr, index) ? Cx_Ptr(arr[index]) : Cx_Ptr();
}

//! Matching function for STL container whose element type is Cx_Ptr.
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

//! Matching function for STL container whose element type is std::pair and the second item of pair is Cx_Ptr.
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

//! Removes an element that match a element value in a container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL container variable (vector, list, map) whose element type is Cx_Ptr. eg:  vector<Cx_Ptr>
    \param p The element value for matching. It's type is same as the element type of 'arr'.
    \return The element is removed or not.
*/
template<class IF_Type, class _Ta> inline
bool erase_value(_Ta& arr, Cx_Ptr& p)
{
    return erase_if(arr, std::bind2nd(FindByPtr<IF_Type>(), p));
}

//! Removes an element that match a element value in a container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL container variable (vector, list, map) whose element type is Pair_Type. eg:  vector<Pair_Type>
    \param p The element value for matching. It's type is Pair_Type whose second item is Cx_Ptr.
    \return The element is removed or not.
*/
template<class IF_Type, class _Ta, class Pair_Type> inline
bool erase_pair(_Ta& arr, Pair_Type& p)
{
    return erase_if(arr, std::bind2nd(FindPairByPtr<IF_Type, Pair_Type>(), p));
}

//! Finds the position index of an element that match a element value in a container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL vector variable whose element type is Cx_Ptr. eg:  vector<Cx_Ptr>
    \param p The element value for matching. It's type is same as the element type of 'arr'.
    \return the position index of an element, or -1 if not found.
*/
template<class IF_Type, class _Ta> inline
long find_value(const _Ta& arr, const Cx_Ptr& p)
{
    return find_if(arr, std::bind2nd(FindByPtr<IF_Type>(), p));
}

//! Finds the position index of an element that match a element value in a container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL vector variable whose element type is Pair_Type. eg:  vector<Pair_Type>
    \param p The element value for matching. It's type is Pair_Type whose second item is Cx_Ptr.
    \return the position index of an element, or -1 if not found.
*/
template<class IF_Type, class _Ta, class Pair_Type> inline
long find_pair(_Ta& arr, Pair_Type& p)
{
    return find_if(arr, std::bind2nd(FindPairByPtr<IF_Type, Pair_Type>(), p));
}

} // x3
#endif // UTILFUNC_VECPTR_H_
