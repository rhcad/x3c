// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef _X3_UTILITY_CLIPBOARDUTIL_H
#define _X3_UTILITY_CLIPBOARDUTIL_H

#include <Ix_ClipboardUtil.h>

class Cx_ClipboardUtil : public Ix_ClipboardUtil
{
public:
    Cx_ClipboardUtil() {}
    virtual ~Cx_ClipboardUtil() {}

public:
    // From Ix_ClipboardUtil
    virtual bool CopyText(HWND wndOwner, const std::wstring& text);
    virtual bool PasteText(HWND wndOwner, std::wstring& text, bool clear = false);
    virtual bool CanPasteText();
};

#endif // _X3_UTILITY_CLIPBOARDUTIL_H
