/*! \file Ix_ClipboardUtil.h
 *  \brief 剪贴板实用操作的接口 Ix_ClipboardUtil
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_ICLIPBOARDUTIL_H_
#define X3_UTIL_ICLIPBOARDUTIL_H_

#include <Ix_Object.h>

X3CLSID_DEFINE(CLSID_ClipboardUtil, "fc957aed-3c48-461e-b9b8-6ff255f2e71d");

//! 剪贴板实用操作的单实例接口
/*!
    \interface Ix_ClipboardUtil
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_ClipboardUtil
*/
class Ix_ClipboardUtil
{
public:
    virtual ~Ix_ClipboardUtil() {}

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
