//! \file vecfunc.h
//! \brief 包含STL常用文件和定义数组函数

#ifndef __STL_VECTOR_FUNCTIONS_H
#define __STL_VECTOR_FUNCTIONS_H

#pragma warning(disable:4710)	// inline function not expanded
#pragma warning(disable:4786)	// identifier was truncated
#pragma warning (push, 3)
#pragma warning(disable:4018)	// signed/unsigned mismatch
#pragma warning(disable:4702)	// unreachable code
#include <algorithm>
#include <xstring>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <sstream>
#pragma warning (pop)

#ifdef __AFX_H__
//! 将CString安全的转换为wstring，避免空地址问题
inline std::wstring towstr(const CString& str)
{
	return str.IsEmpty() ? L"" : (LPCTSTR)str;
}
#endif

//! 根据条件删除数组元素
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL数组变量，例如" vector<Ix_xxx*> arr; "
	\param _P 要删除的条件表达式，例如" std::bind2nd(std::equal_to<Ix_xxx*>(), pObj) "
	\return 是否已删除
*/
template<class _Ta, class _Pr> inline
bool erase_if(_Ta& arr, _Pr _P)
{
	_Ta::iterator it = std::find_if(arr.begin(), arr.end(), _P);
	bool b = (it != arr.end());

	if (b)
	{
		arr.erase(it);
	}

	return b;
};

//! 根据元素值删除数组元素
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL数组变量，类型为vector< _Tp >，例如" vector<Ix_xxx*> arr; "
	\param p 要删除的元素值，其类型和arr数组元素类型相同，例如" Ix_xxx* pObj"
	\return 是否已删除
*/
template<class _Ta, class _Tp> inline
bool erase_value(_Ta& arr, _Tp& p)
{
	return erase_if(arr, std::bind2nd(std::equal_to<_Tp>(), p));
}

//! 根据条件查找数组元素的位置
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL数组变量，例如" vector<Ix_xxx*> arr; "
	\param _P 要查找的条件表达式，例如" std::bind2nd(std::equal_to<Ix_xxx*>(), pObj) "
	\return 元素位置，-1表示没找到
*/
template<class _Ta, class _Pr> inline
long find_if(const _Ta& arr, _Pr _P)
{
	_Ta::const_iterator it = std::find_if(arr.begin(), arr.end(), _P);
	return (it != arr.end()) ? (long)(it - arr.begin()) : -1;
}

//! 根据元素值查找数组元素的位置
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL数组变量，类型为vector< _Tp >，例如" vector<Ix_xxx*> arr; "
	\param p 元素值，其类型和arr数组元素类型相同，例如" Ix_xxx* pObj"
	\return 元素位置，-1表示没找到
*/
template<class _Ta, class _Tp> inline
long find_value(const _Ta& arr, const _Tp& p)
{
	return find_if(arr, std::bind2nd(std::equal_to<_Tp>(), p));
}

//! 返回数组或字串的长度
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL数组变量或字串
	\return 元素个数
*/
template<class _Ta> inline
long GetSize(const _Ta& arr)
{
	return static_cast<long>(arr.size());
}

//! 判断数组元素索引是否超出数组范围
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL数组变量，例如" vector<Ix_xxx*> arr; "
	\param index 数组元素索引序号
	\return 是否超出数组范围
*/
template<class _Ta> inline
bool IsValidIndexOf(const _Ta& arr, long index)
{
	return index >= 0 && index < static_cast<long>(arr.size());
}

#if _MSC_VER <= 1200 // VC6
#include "func_s.h"
#endif

#endif // __STL_VECTOR_FUNCTIONS_H
