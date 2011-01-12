// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
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

/*! \file Ix_ClipboardUtil.h
 *  \brief 剪贴板实用操作的接口 Ix_ClipboardUtil
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_ICLIPBOARDUTIL_H_
#define X3_UTIL_ICLIPBOARDUTIL_H_

#include <Ix_Object.h>

const XCLSID CLSID_ClipboardUtil("fc957aed-3c48-461e-b9b8-6ff255f2e71d");

//! 剪贴板实用操作的单实例接口
/*!
    \interface Ix_ClipboardUtil
    \ingroup _GROUP_UTILITY_
    \see CLSID_ClipboardUtil
*/
interface Ix_ClipboardUtil
{
    //! 将给定文本复制到剪贴板
    /*!
        \param wndOwner 当前窗口句柄，将关联到剪贴板上
        \param text 要复制的文本，非空
        \return 是否复制了文本
    */
    virtual bool CopyText(HWND wndOwner, const std::wstring& text) = 0;

    //! 从剪贴板获取文本内容
    /*!
        \param[in] wndOwner 当前窗口句柄
        \param[out] text 要填充的文本
        \param[in] clear 获取文本是否清除剪贴板内容
        \return 是否复制了文本
    */
    virtual bool PasteText(HWND wndOwner, std::wstring& text, bool clear = false) = 0;

    //! 返回是否可以粘贴文本
    virtual bool CanPasteText() = 0;
};

#endif // X3_UTIL_ICLIPBOARDUTIL_H_
