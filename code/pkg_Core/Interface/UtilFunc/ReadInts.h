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

/*! \file ReadInts.h
 *  \brief 定义从串中分离出多个整数的函数 ReadInts 和 ReadDoubleArray
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef UTILFUNC_READINTS_H_
#define UTILFUNC_READINTS_H_

//! 返回一个字符是否为形成整数的字符
/*!
	\param c 要检查的字符
	\param signchar 整数是否允许包含正负号，如果为false则仅当为数字才返回true
	\return 是否为形成整数的字符
*/
inline bool IsIntChar(WCHAR c, bool signchar = false)
{
	return iswdigit(c) || signchar && ('+' == c || '-' == c);
}

//! 从字符串中分离出多个整数
/*!
	\ingroup _GROUP_UTILFUNC
	\param[in] str 包含多个整数的字符串，用标点符号、空白等字符分隔
	\param[out] arr 填充多个整数，最多填充size个整数
	\param[in] size 最多填充多少个整数，数组arr的元素个数
	\param[in] signchar 整数是否允许包含正负号，如果为false则仅当为数字才返回true
	\return 分离出的整数个数
	\see IsIntChar
*/
template <class IntType> inline
long ReadInts(LPCWSTR str, IntType* arr, long size, bool signchar = false)
{
	if (NULL == str)
	{
		return 0;
	}

	int i, j, count;
	WCHAR buf[13];

	for (i = 0, count = 0; str[i] != 0 && count < size; )
	{
		while (str[i] != 0 && !IsIntChar(str[i], signchar))
		{
			i++;
		}
		for (j = i; IsIntChar(str[j], signchar); j++)
		{
		}
		if (j > i)
		{
			lstrcpynW(buf, str + i, min(_countof(buf), 1 + j - i));
			arr[count++] = static_cast<IntType>(_wtoi(buf));
		}
		i = j;
	}

	return count;
}

//! 返回一个字符是否为形成浮点数的字符
inline bool IsDblChar(WCHAR c)
{
	return iswdigit(c) || '+' == c || '-' == c
		|| '.' == c || 'E' == c || 'e' == c;
}

//! 从字符串中分离出多个浮点数
/*!
	\ingroup _GROUP_UTILFUNC
	\param[in] str 包含多个浮点数的字符串，用标点符号、空白等字符分隔
	\param[out] arr 填充多个浮点数，最多填充size个浮点数
	\param[in] size 最多填充多少个浮点数，数组arr的元素个数
	\return 分离出的浮点数个数
	\see IsDblChar
*/
inline long ReadDoubleArray(LPCWSTR str, double* arr, long size)
{
	if (NULL == str)
	{
		return 0;
	}

	int i, j, count;
	WCHAR buf[32];
	LPWSTR endptr;

	for (i = 0, count = 0; str[i] != 0 && count < size; )
	{
		while (str[i] != 0 && !IsDblChar(str[i]))
		{
			i++;
		}
		for (j = i; IsDblChar(str[j]); j++)
		{
		}
		if (j > i)
		{
			lstrcpynW(buf, str + i, min(_countof(buf), 1 + j - i));
			arr[count++] = wcstod(buf, &endptr);
		}
		i = j;
	}

	return count;
}

#endif // UTILFUNC_READINTS_H_
