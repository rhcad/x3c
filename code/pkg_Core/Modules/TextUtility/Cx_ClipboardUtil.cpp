// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#define _NEED_STDIO
#include <PluginInc.h>
#include "Cx_ClipboardUtil.h"
#ifdef _WIN32
#include <ConvStr.h>
#include <SysErrStr.h>

bool Cx_ClipboardUtil::CopyText(HWND wndOwner, const std::wstring& text)
{
    bool bRet = false;
    DWORD err = 0;

    if (!text.empty() && ::OpenClipboard(wndOwner))
    {
        HANDLE hMem = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(wchar_t) * (text.size() + 1));
        if (hMem != NULL)
        {
            wchar_t* str = (wchar_t*)::GlobalLock(hMem);
            if (NULL == str)
            {
                ::GlobalFree(hMem);
            }
            else
            {
                wcscpy_s(str, text.size() + 1, text.c_str());
                ::GlobalUnlock(hMem);

                ::EmptyClipboard();
                if (::SetClipboardData(CF_UNICODETEXT, hMem))
                {
                    bRet = true;
                }
                else
                {
                    err = GetLastError();
                    LOG_WARNING2(L"@TextUtility:IDS_SETCLIP_FAIL", GetSystemErrorString(err));
                }
            }
        }
        else
        {
            err = GetLastError();
            LOG_WARNING2(L"@TextUtility:IDS_ALLOCMEM_FAIL", GetSystemErrorString(err));
        }

        ::CloseClipboard();
    }
    else
    {
        err = GetLastError();
        LOG_WARNING2(L"@TextUtility:IDS_OPENCLIP_FAIL", GetSystemErrorString(err));
    }

    return bRet;
}

bool Cx_ClipboardUtil::PasteText(HWND wndOwner, std::wstring& text, bool clear)
{
    text.resize(0);

    if (!::IsClipboardFormatAvailable(CF_UNICODETEXT)
        && !::IsClipboardFormatAvailable(CF_TEXT))
    {
        LOG_INFO(L"@TextUtility:IDS_CLIP_NOTEXT");
        return false;
    }

    if (!::OpenClipboard(wndOwner))
    {
        DWORD err = GetLastError();
        LOG_WARNING2(L"@TextUtility:IDS_OPENCLIP_FAIL", GetSystemErrorString(err));
    }
    else
    {
        if (::IsClipboardFormatAvailable(CF_UNICODETEXT))
        {
            HANDLE hMem = ::GetClipboardData(CF_UNICODETEXT);
            if (hMem != NULL)
            {
                const wchar_t* lpStr = (const wchar_t*)::GlobalLock(hMem);
                if (lpStr != NULL)
                {
                    text = lpStr;
                    ::GlobalUnlock(hMem);
                }
            }
        }
        else if (::IsClipboardFormatAvailable(CF_TEXT))
        {
            HANDLE hMem = ::GetClipboardData(CF_UNICODETEXT);
            if (hMem != NULL)
            {
                const char* lpStr = (const char*)::GlobalLock(hMem);
                if (lpStr != NULL)
                {
                    text = x3::a2w(lpStr);
                    ::GlobalUnlock(hMem);
                }
            }
        }

        if (clear)
        {
            ::EmptyClipboard();
        }

        ::CloseClipboard();
    }

    return !text.empty();
}

bool Cx_ClipboardUtil::CanPasteText()
{
    return ::IsClipboardFormatAvailable(CF_UNICODETEXT)
        || ::IsClipboardFormatAvailable(CF_TEXT);
}

#endif // _WIN32