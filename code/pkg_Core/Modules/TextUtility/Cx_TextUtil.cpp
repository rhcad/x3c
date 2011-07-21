// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Changes:
// 2011-01-15, Zhang Yun Gui: IsSpaceChar() support '\r' and '\n'.
//

#include <UtilFunc/PluginInc.h>
#include "Cx_TextUtil.h"
#include <UtilFunc/ConvStr.h>
#include <UtilFunc/SysErrStr.h>
#include <UtilFunc/ctrim.h>
#include <UtilFunc/AutoNew.h>

// First bytes      Encoding assumed:
// EF BB BF         UTF-8
// FE FF            UTF-16 (big-endian)
// FF FE            UTF-16 (little-endian)
// 00 00 FE FF      UTF-32 (big-endian)
// FF FE 00 00      UTF-32 (little-endian)

DWORD Cx_TextUtil::GetHeadBytes(const std::wstring& filename, BYTE head[5])
{
    DWORD dwBytesRead = 0;
    HANDLE hFile = NULL;

    if (OpenFileForRead(hFile, filename.c_str()))
    {
        ::ReadFile(hFile, head, 5, &dwBytesRead, NULL);
        CloseFile(hFile);
    }
    else
    {
        DWORD err = GetLastError();
        X3LOG_ERROR2(L"@TextUtility:IDS_OPEN_FAIL",
            x3::GetSystemErrorString(err) << L", " << filename);
    }

    return dwBytesRead;
}

bool Cx_TextUtil::IsUTF16File(const std::wstring& filename, bool& utf16)
{
    BYTE head[5] = { 0, 0, 0, 0, 0 };
    DWORD dwBytesRead = GetHeadBytes(filename, head);
    bool bRet = false;

    if (dwBytesRead > 2)
    {
        utf16 = (0xFF == head[0] && 0xFE == head[1]);
        bRet = (utf16 || !(0xFE == head[0] && 0xFF == head[1]));
    }

    return bRet;
}

bool Cx_TextUtil::IsUTF8File(const std::wstring& filename, bool& bUTF8)
{
    BYTE head[5] = { 0, 0, 0, 0, 0 };
    DWORD dwBytesRead = GetHeadBytes(filename, head);
    bool bRet = (dwBytesRead > 0);

    bUTF8 = (dwBytesRead > 3) && (0xEF == head[0] && 0xBB == head[1] && 0xBF == head[2]);

    return bRet;
}

bool Cx_TextUtil::UnicodeToAnsi(const std::wstring& filename, int codepage)
{
    BYTE head[5] = { 0, 0, 0, 0, 0 };
    DWORD dwBytesRead = GetHeadBytes(filename, head);
    bool bRet = true;

    if (dwBytesRead > 2 && (0xFF == head[0] && 0xFE == head[1]))
    {
        std::wstring content;
        bRet = ReadTextFile(content, filename)
            && SaveTextFile(content, filename, false, codepage);
    }

    return bRet;
}

bool Cx_TextUtil::AnsiToUnicode(const std::wstring& filename, int codepage)
{
    bool bRet = false;
    BYTE head[5];
    std::wstring content;

    if (ReadTextFile(head, content, filename, 16, codepage))
    {
        bRet = (0xFF == head[0] && 0xFE == head[1])
            || SaveTextFile(content, filename, true);
    }

    return bRet;
}

bool Cx_TextUtil::GetFileContent(std::wstring& content, BYTE* buf, long size, int codepage)
{
    bool bRet = true;

    if (0xFF == buf[0] && 0xFE == buf[1])   // UTF-16 (little-endian)
    {
        content.resize((size - 2) / 2);
        memcpy((void*)content.c_str(), buf + 2, content.size() * sizeof(wchar_t));
    }
    else            // ANSI/ASCII
    {
        bRet = (buf[0] != 0xFE || buf[0] != 0xFF);

        if (size > 3 && (0xEF == buf[0] && 0xBB == buf[1] && 0xBF == buf[2]))
        {
            codepage = 65001;//CP_UTF8
        }
        content = x3::a2w((const char*)buf, codepage);
    }

    return bRet;
}

bool Cx_TextUtil::ReadTextFile(BYTE head[5], std::wstring& content,
                               const std::wstring& filename,
                               ULONG nLenLimitMB, int codepage)
{
    memset(head, 0, sizeof(BYTE) * 5);
    content.resize(0);

    bool bRet = false;
    HANDLE hFile = NULL;

    if (!OpenFileForRead(hFile, filename.c_str()))
    {
        DWORD err = GetLastError();
        X3LOG_ERROR2(L"@TextUtility:IDS_OPEN_FAIL",
            x3::GetSystemErrorString(err) << L", " << filename);
    }
    else
    {
        DWORD dwLength = ::GetFileSize(hFile, NULL);
        KAutoNewArr<BYTE> buf;

        if ((long)dwLength > 0)
        {
            if (dwLength > nLenLimitMB * 1024L * 1024L)
            {
                X3LOG_WARNING2(L"@TextUtility:IDS_HUGE_FILE",
                    (dwLength / (1024.0*1024.0)) << L"MB, " << filename);
                dwLength = nLenLimitMB * 1024L * 1024L;
            }
            buf.Realloc(dwLength + 8);
            memset(buf.ptr, 0, buf.count);
        }

        if (buf)
        {
            DWORD dwBytesRead = 0;
            ::ReadFile(hFile, buf.ptr, dwLength, &dwBytesRead, NULL);
            if (dwBytesRead > 0)
            {
                memcpy(head, buf.ptr, 5 < dwBytesRead ? 5 : dwBytesRead);
                bRet = GetFileContent(content, buf.ptr, dwBytesRead, codepage);
                if (!bRet)
                {
                    X3LOG_WARNING2(L"@TextUtility:IDS_NOT_ANSIFILE", filename);
                }
            }
        }

        CloseFile(hFile);
    }

    return bRet;
}

bool Cx_TextUtil::ReadTextFile(std::wstring& content,
                               const std::wstring& filename,
                               ULONG nLenLimitMB, int codepage)
{
    BYTE head[5];
    return ReadTextFile(head, content, filename, nLenLimitMB, codepage);
}

bool Cx_TextUtil::SaveTextFile(const std::wstring& content,
                               const std::wstring& filename,
                               bool utf16, int codepage)
{
    bool bRet = false;
    HANDLE hFile = NULL;

    ::SetFileAttributesNormal(filename.c_str());

    if (!OpenFileForWrite(hFile, filename.c_str()))
    {
        DWORD err = GetLastError();
        X3LOG_ERROR2(L"@TextUtility:IDS_WRITE_FAIL",
            x3::GetSystemErrorString(err) << L", " << filename);
    }
    else
    {
        DWORD dwLen, dwBytes;

        if (utf16)
        {
            BYTE head[] = { 0xFF, 0xFE };
            ::WriteFile(hFile, head, 2, &dwBytes, NULL);

            dwLen = (DWORD)(content.size() * sizeof(wchar_t));
            ::WriteFile(hFile, content.c_str(), dwLen, &dwBytes, NULL);
            bRet = (dwBytes == dwLen);
        }
        else
        {
            std::string strAnsi (x3::w2a(content, codepage));

            dwLen = x3::GetSize(strAnsi);
            ::WriteFile(hFile, strAnsi.c_str(), dwLen, &dwBytes, NULL);
            bRet = (dwBytes == dwLen);
        }

        CloseFile(hFile);
    }

    return bRet;
}

bool Cx_TextUtil::SaveTextFile(const std::string& content,
                               const std::wstring& filename,
                               bool utf16, int codepage)
{
    bool bRet = false;
    HANDLE hFile = NULL;

    ::SetFileAttributesNormal(filename.c_str());

    if (!OpenFileForWrite(hFile, filename.c_str()))
    {
        DWORD err = GetLastError();
        X3LOG_ERROR2(L"@TextUtility:IDS_WRITE_FAIL",
            x3::GetSystemErrorString(err) << L", " << filename);
    }
    else
    {
        DWORD dwLen, dwBytes;

        if (utf16)
        {
            std::wstring wstrUnicode (x3::a2w(content, codepage));

            BYTE head[] = { 0xFF, 0xFE };
            ::WriteFile(hFile, head, 2, &dwBytes, NULL);

            dwLen = (DWORD)(wstrUnicode.size() * sizeof(wchar_t));
            ::WriteFile(hFile, wstrUnicode.c_str(), dwLen, &dwBytes, NULL);
            bRet = (dwBytes == dwLen);
        }
        else
        {
            dwLen = x3::GetSize(content);
            ::WriteFile(hFile, content.c_str(), dwLen, &dwBytes, NULL);
            bRet = (dwBytes == dwLen);
        }

        CloseFile(hFile);
    }

    return bRet;
}

long Cx_TextUtil::GetLineCount(const std::wstring& text)
{
    if (text.empty())
    {
        return 0;
    }

    long nCount = 1;
    const wchar_t* pszStart = text.c_str();
    const wchar_t* pszEnd;

    for (; (pszEnd = wcsstr(pszStart, L"\n\r")) != NULL; nCount++)
    {
        pszStart = pszEnd + 1;
        if (*pszStart != *pszEnd
            && (L'\n' == *pszStart || L'\r' == *pszStart))
        {
            pszStart++;
        }
    }

    return nCount;
}

std::wstring Cx_TextUtil::GetLine(const std::wstring& text,
                                  long line, const wchar_t** nextline)
{
    if (line < 0)
    {
        if (nextline != NULL)
        {
            *nextline = NULL;
        }
        return L"";
    }

    long nCount = 0;
    const wchar_t* pszStart = text.c_str();
    const wchar_t* pszEnd = pszStart + wcscspn(pszStart, L"\n\r");

    while (line > nCount && *pszEnd != 0)
    {
        pszStart = pszEnd + 1;
        if (*pszStart != *pszEnd
            && (L'\n' == *pszStart || L'\r' == *pszStart))
        {
            pszStart++;
        }
        pszEnd = pszStart + wcscspn(pszStart, L"\n\r");
        nCount++;
    }

    if (nextline != NULL)
    {
        if (0 == *pszEnd)
        {
            *nextline = NULL;
        }
        else
        {
            const wchar_t* p = pszEnd + 1;
            if (*p != *pszEnd && (L'\n' == *p || L'\r' == *p))
            {
                p++;
            }
            *nextline = p;
        }
    }

    return std::wstring(pszStart, pszEnd - pszStart);
}

static inline bool IsSpaceChar(wchar_t cChar, const wchar_t* targets = NULL)
{
    return targets ? (wcschr(targets, cChar) != NULL)
        : (0x0020 == cChar || 0x3000 == cChar || L'\t' == cChar
        || L'\n' == cChar || L'\r' == cChar);
}

bool Cx_TextUtil::IsSpaceLine(const std::wstring& text)
{
    int i = x3::GetSize(text);
    while (--i >= 0 && IsSpaceChar(text[i])) {}
    return i < 0;
}

bool Cx_TextUtil::TrimSpace(std::wstring& text, const wchar_t* targets)
{
    const int nOldLen = x3::GetSize(text);
    int i = nOldLen;
    while (--i >= 0 && IsSpaceChar(text[i], targets)) {}

    if (i + 1 < nOldLen)
    {
        text.erase(text.begin() + (i + 1), text.end());
    }

    int n = x3::GetSize(text);
    for (i = 0; i < n && IsSpaceChar(text[i], targets); i++) {}

    if (i > 0)
    {
        text.erase(text.begin(), text.begin() + i);
    }

    return nOldLen > x3::GetSize(text);
}

bool Cx_TextUtil::TrimLeft(std::wstring& text, const wchar_t* targets)
{
    const int len = x3::GetSize(text);
    int i = 0;

    for (; i < len && IsSpaceChar(text[i], targets); i++) {}
    if (i > 0)
    {
        text.erase(text.begin(), text.begin() + i);
    }

    return i > 0;
}

bool Cx_TextUtil::TrimRight(std::wstring& text, const wchar_t* targets)
{
    const int len = x3::GetSize(text);
    int i = len;
    while (--i >= 0 && IsSpaceChar(text[i], targets)) {}

    if (i + 1 < len)
    {
        text.erase(text.begin() + (i + 1), text.end());
    }

    return i + 1 < len;
}

bool Cx_TextUtil::RemoveInvalidChars(std::wstring& text, const wchar_t* targets)
{
    std::vector<long> arrIndex;
    long i = x3::GetSize(text);

    while (--i >= 0)
    {
        wchar_t ch = text[i];

        if (targets && IsSpaceChar(ch, targets))
        {
            arrIndex.push_back(i);
        }
        else if (!targets)
        {
            if ( (ch >= 0x0001 && ch <= 0x0008)
                || (ch >= 0x000b && ch <= 0x000c)
                || (ch >= 0x000e && ch <= 0x001f)
                || (ch == 0xDBC0) )
            {
                arrIndex.push_back(i);
            }
        }
    }

    long nCount = x3::GetSize(arrIndex);
    for (i = 0; i < nCount; i++)
    {
        text.erase(arrIndex[i]);
    }

    return nCount > 0;
}

bool Cx_TextUtil::ReplaceAll(std::wstring& text,
                             const std::wstring& match,
                             const std::wstring& newtext)
{
    long count = 0;
    size_t index = text.find(match);

    while (index != std::wstring::npos)
    {
        count++;
        text.replace(index, match.size(), newtext);
        index = text.find(match, index + newtext.size());
    }

    return count > 0;
}

bool Cx_TextUtil::ReplaceChar(std::wstring& text,
                              const std::wstring& match,
                              const std::wstring& chars)
{
    return trim::replace_each(text, match, chars) > 0;
}

bool Cx_TextUtil::ToDBC(std::wstring& text, bool punct)
{
    bool changed = false;
    std::wstring dest(L'\0', text.size() + 1);

#ifdef _WIN32
    if (!text.empty() && punct)
    {
        int ret = LCMapStringW(
            MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED),
            LCMAP_HALFWIDTH,
            text.c_str(), text.size(),
            &dest[0], dest.size() + 1);

        if (ret > 0 && dest != text)
        {
            text = dest;
            changed = true;
        }
    } else
#endif
    if (!text.empty())
    {
        const wchar_t* psrc = text.c_str();
        wchar_t* pdest = &dest[0];
        int i = 0, n = 0;

        for (; psrc[i] != 0; i++)
        {
            if (psrc[i] >= 0xA3B0 && psrc[i] <= 0xA3B9)     // Chinese 0..9
            {
                pdest[i] = wchar_t(L'0' + psrc[i] - 0xA3B0);
                n++;
            }
            else if (psrc[i] >= 0xA3C1 && psrc[i] <= 0xA3DA)    // A..Z
            {
                pdest[i] = wchar_t(L'A' + psrc[i] - 0xA3C1);
                n++;
            }
            else if (psrc[i] >= 0xA3E1 && psrc[i] <= 0xA3FA)    // a..z
            {
                pdest[i] = wchar_t(L'a' + psrc[i] - 0xA3E1);
                n++;
            }
            else
            {
                pdest[i] = psrc[i];
            }
        }
        pdest[i] = 0;

        if (n > 0)
        {
            text = dest;
            changed = true;
        }
    }

    return changed;
}

std::string Cx_TextUtil::ToAnsi(const std::wstring& text, int codepage)
{
    return x3::w2a(text, codepage);
}

std::wstring Cx_TextUtil::ToUnicode(const std::string& text, int codepage)
{
    return x3::a2w(text, codepage);
}

#include "md5.h"
#include "Base64.h"

std::wstring Cx_TextUtil::MD5(const std::wstring& text)
{
    return x3::a2w(CMD5().MD5(x3::w2a(text).c_str()));
}

class CReadMD5 : public CMD5::IRead
{
public:
    CReadMD5(const std::wstring& filename) : m_hFile(NULL)
    {
        if (!OpenFileForRead(m_hFile, filename.c_str()))
        {
            DWORD err = GetLastError();
            X3LOG_ERROR2(L"@TextUtility:IDS_OPEN_FAIL",
                x3::GetSystemErrorString(err) << L", " << filename);
        }
    }

    ~CReadMD5()
    {
        if (m_hFile)
        {
            CloseFile(m_hFile);
        }
    }

    bool IsOpened() const
    {
        return !!m_hFile;
    }

private:
    HANDLE  m_hFile;

    virtual bool Read(void* buf, DWORD size, DWORD* readed)
    {
        return !!ReadFile(m_hFile, buf, size, readed, NULL);
    }
};

bool Cx_TextUtil::FileMD5(std::wstring& md5, const std::wstring& filename)
{
    CReadMD5 file(filename);

    md5.resize(0);
    if (file.IsOpened())
    {
        md5 = x3::a2w(CMD5().MD5(&file));
    }

    return !md5.empty();
}

std::wstring& Cx_TextUtil::Base64(std::wstring& text, 
                                  const BYTE* data, int size,
                                  const wchar_t* codetype)
{
    Base64::Encode(data, size, text,
        codetype[0], codetype[1], codetype[2]);
    return text;
}

std::vector<BYTE>& Cx_TextUtil::UnBase64(std::vector<BYTE>& data, 
                                         const std::wstring& text,
                                         const wchar_t* codetype)
{
    data.resize(Base64::GetDataLength(text.size()));
    if (!data.empty())
    {
        Base64::Decode(text, text.size(), &data[0],
            codetype[0], codetype[1], codetype[2]);
    }
    return data;
}

std::wstring& Cx_TextUtil::Base64(std::wstring& text, 
                                  const std::string& data, 
                                  const wchar_t* codetype)
{
    return Base64(text, (const BYTE*)data.c_str(), data.size(), codetype);
}

std::string& Cx_TextUtil::UnBase64(std::string& data, 
                                   const std::wstring& text, 
                                   const wchar_t* codetype)
{
    data.resize(Base64::GetDataLength(text.size()));
    if (!data.empty())
    {
        Base64::Decode(text, text.size(), (BYTE*)&data[0],
            codetype[0], codetype[1], codetype[2]);
    }
    return data;
}
