// x3c - C++ PluginFramework
#ifndef _X3_UTILITY_CLIPBOARDUTIL_H
#define _X3_UTILITY_CLIPBOARDUTIL_H

#include <Utility/Ix_ClipboardUtil.h>

class Cx_ClipboardUtil : public Ix_ClipboardUtil
{
    X3BEGIN_CLASS_DECLARE(Cx_ClipboardUtil)
        X3DEFINE_INTERFACE_ENTRY(Ix_ClipboardUtil)
    X3END_CLASS_DECLARE()
protected:
    Cx_ClipboardUtil() {}
    virtual ~Cx_ClipboardUtil() {}

private:
    // From Ix_ClipboardUtil
    virtual bool CopyText(HWND wndOwner, const std::wstring& text);
    virtual bool PasteText(HWND wndOwner, std::wstring& text, bool clear = false);
    virtual bool CanPasteText();
};

#endif // _X3_UTILITY_CLIPBOARDUTIL_H
