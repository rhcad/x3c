// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// Changes:
// 2011-02-28: Add FOF_SILENT flag for SHFileOperationW.

#include <UtilFunc/PluginInc.h>
#include "Cx_FileUtility.h"
#include <UtilFunc/SysErrStr.h>
#include <UtilFunc/RelToAbs.h>

#ifdef _WIN32
#include <io.h>
#include <shellapi.h>
#ifdef _MSC_VER
#pragma comment(lib,"shell32.lib")
#endif
#endif // _WIN32

static long s_nFileOpRet = 0;   // SHFileOperationW 返回值

static inline bool IsPathSlash(wchar_t c)
{
    return L'\\' == c || L'/' == c;
}

static inline bool IsNotNull(const wchar_t* pszText)
{
    return pszText != NULL && *pszText != 0;
}

static void ReplaceSlash(wchar_t* path)
{
    for (; *path; path++)
    {
        if (L'/' == *path)
        {
            *path = L'\\';
        }
    }
}

static bool IsPathFileExists_(const wchar_t* filename, bool bWrite)
{
    if (!IsNotNull(filename))
        return false;
#ifdef _WIN32
    return _waccess(filename, bWrite ? 6 : 0) == 0;
#else
    return CheckFileAttributes(filename, NULL, NULL);
#endif
}

bool Cx_FileUtility::IsPathFileExists(const wchar_t* filename, bool bWrite)
{
    return IsPathFileExists_(filename, bWrite);
}

static bool IsPath_(const wchar_t* filename, bool bCheckExists)
{
    if (IsNotNull(filename))
    {
        if (bCheckExists)
        {
            bool folder = false;
            if (CheckFileAttributes(filename, NULL, &folder))
            {
                return folder;
            }
        }

        return IsPathSlash(filename[wcslen(filename) - 1]);
    }

    return false;
}

bool Cx_FileUtility::IsPath(const wchar_t* filename, bool bCheckExists)
{
    return IsPath_(filename, bCheckExists);
}

Cx_FileUtility::Cx_FileUtility()
    : m_hMsgBoxOwnerWnd(NULL)
{
}

bool Cx_FileUtility::CreateDirectory(const wchar_t* filename, bool bIsPath)
{
    wchar_t path[MAX_PATH];
    int i, nLen;
    wchar_t cSaveChar;

    if (!IsNotNull(filename))
    {
        return false;
    }

    wcsncpy_s(path, MAX_PATH, filename, MAX_PATH);
    ReplaceSlash(path);
    if (bIsPath)
    {
        PathRemoveBackslashW(path);
    }
    else
    {
        PathRemoveFileSpecW(path);
    }
    PathAddBackslashW(path);
    nLen = wcslen(path);

#ifdef _WIN32
    if (_waccess(path, 0) == 0)
#else
    if (CheckFileAttributes(path, NULL, NULL))
#endif
    {
        return true;
    }

    for (i = 2; i < nLen; i++)
    {
        if (IsPathSlash(path[i]) && path[i-1] != L':')
        {
            cSaveChar = path[i];
            path[i] = 0;
            ::CreateDirectoryW(path, NULL);
            ::SetFileAttributesNormal(path);
            path[i] = cSaveChar;
        }
    }

    DWORD dwError = GetLastError();
#ifdef _WIN32
    if (_waccess(path, 0) != 0)
#else
    if (!CheckFileAttributes(path, NULL, NULL))
#endif
    {
        std::wostringstream buf;
        if (dwError != 0)
        {
            buf << GetSystemErrorString(dwError) << L", ";
        }
        buf << filename;
        X3LOG_ERROR2(L"@FileUtility:IDS_CREATEDIR_FAIL", buf.str());
        return false;
    }

    return true;
}

bool Cx_FileUtility::VerifyFileCanWrite(const wchar_t* filename)
{
    if (!IsNotNull(filename))
    {
        return false;
    }
    if (!CreateDirectory(filename, false))
    {
        return false;
    }

    if (IsPathFileExists(filename)
        && !SetFileAttributesNormal(filename))
    {
        X3LOG_ERROR2(L"@FileUtility:IDS_FILE_CANNOT_WRITE", filename);
        return false;
    }

    return true;
}

bool DeletePathFile_(const wchar_t* filename, bool bRecycle, HWND hwnd)
{
    if (!IsNotNull(filename))
    {
        return true;
    }
    ASSERT(!PathIsRelativeW(filename));
    if (!IsPathFileExists_(filename, false))
    {
        return true;
    }

    wchar_t szFile[MAX_PATH];
    memset(szFile, 0, sizeof(szFile));
    wcsncpy_s(szFile, MAX_PATH, filename, MAX_PATH);
    ReplaceSlash(szFile);
    PathRemoveBackslashW(szFile);

#ifdef _WIN32
    SHFILEOPSTRUCTW op;
    memset(&op, 0, sizeof(op));
    op.hwnd = hwnd;
    op.wFunc = FO_DELETE;
    op.pFrom = szFile;
    op.pTo = NULL;
    op.fFlags = FOF_NOCONFIRMATION;
    if (bRecycle)
    {
        op.fFlags |= FOF_ALLOWUNDO;
    }
    if (NULL == hwnd)
    {
        op.fFlags |= FOF_NOERRORUI | FOF_SILENT;
    }

    InterlockedExchange(&s_nFileOpRet, SHFileOperationW(&op));
    if (s_nFileOpRet != 0)
    {
        std::wostringstream buf;
        buf << GetSystemErrorString(s_nFileOpRet) << L", " << filename;

        if (IsPath_(filename, true))
        {
            X3LOG_WARNING2(L"@FileUtility:IDS_DELFOLDER_FAIL", buf.str());
        }
        else
        {
            X3LOG_ERROR2(L"@FileUtility:IDS_DELFILE_FAIL", buf.str());
        }

        return false;
    }
#endif

    return true;
}

bool Cx_FileUtility::DeletePathFile(const wchar_t* filename, bool bRecycle)
{
    return DeletePathFile_(filename, bRecycle, m_hMsgBoxOwnerWnd);
}

bool Cx_FileUtility::TwoFileOperation(const wchar_t* oldfile,
                                      const wchar_t* newfile, int wFunc)
{
    if (!IsNotNull(oldfile))
    {
        return true;
    }
    ASSERT(!PathIsRelativeW(oldfile));
    bool bRet = true;

    if (!IsPathFileExists(oldfile))
    {
        InterlockedExchange(&s_nFileOpRet, GetLastError());
        X3LOG_INFO2(L"@FileUtility:IDS_FILE_NOTEXIST", oldfile << L", " << s_nFileOpRet);
        return false;
    }
    else
    {
#ifdef _WIN32
        wchar_t szOld[MAX_PATH], szNew[MAX_PATH];
        SHFILEOPSTRUCTW op;

        memset(szOld, 0, sizeof(szOld));
        memset(szNew, 0, sizeof(szNew));   // pTo必须以两个\0结束
        wcsncpy_s(szOld, MAX_PATH, oldfile, MAX_PATH);
        ReplaceSlash(szOld);
        PathRemoveBackslashW(szOld);
        wcsncpy_s(szNew, MAX_PATH, newfile, MAX_PATH);
        ReplaceSlash(szNew);
        PathRemoveBackslashW(szNew);

        memset(&op, 0, sizeof(op));
        op.hwnd = m_hMsgBoxOwnerWnd;
        op.wFunc = wFunc;
        op.pFrom = szOld;
        op.pTo = szNew;
        op.fFlags = FOF_NOCONFIRMATION | FOF_NOCOPYSECURITYATTRIBS;
        if (NULL == m_hMsgBoxOwnerWnd)
        {
            op.fFlags |= FOF_NOERRORUI | FOF_SILENT;
        }

        InterlockedExchange(&s_nFileOpRet, SHFileOperationW(&op));
        bRet = (0 == s_nFileOpRet);
#endif
    }

    return bRet;
}

bool Cx_FileUtility::MovePathFile(const wchar_t* oldfile, const wchar_t* newfile)
{
    if (IsPathFileExists(oldfile)
        && !CreateDirectory(newfile, false))
    {
        return false;
    }
    if (!TwoFileOperation(oldfile, newfile, 0x0001))   // FO_MOVE
    {
        if (s_nFileOpRet != 0)
        {
            std::wostringstream buf;
            buf << GetSystemErrorString(s_nFileOpRet);
            buf << L", " << oldfile << L"->" << newfile;
            X3LOG_ERROR2(L"@FileUtility:IDS_MOVEFILE_FAIL", buf.str());
        }
        return false;
    }
    return true;
}

bool Cx_FileUtility::RenamePathFile(const wchar_t* oldfile, const wchar_t* newfile)
{
    if (!TwoFileOperation(oldfile, newfile, 0x0004))  // FO_RENAME
    {
        if (s_nFileOpRet != 0)
        {
            std::wostringstream buf;
            buf << GetSystemErrorString(s_nFileOpRet);
            buf << L", " << oldfile << L"->" << newfile;
            X3LOG_ERROR2(L"@FileUtility:IDS_RENFILE_FAIL", buf.str());
        }
        return false;
    }
    return true;
}

bool Cx_FileUtility::CopyPathFile(const wchar_t* oldfile, const wchar_t* newfile)
{
    if (!IsNotNull(oldfile))
    {
        return true;
    }
    if (!IsPathFileExists(oldfile))
    {
        X3LOG_INFO2(L"@FileUtility:IDS_FILE_NOTEXIST", oldfile);
        return false;
    }

    bool ispath = IsPathSlash(oldfile[wcslen(oldfile) - 1]);

    InterlockedExchange(&s_nFileOpRet, 0);
    if (!CreateDirectory(newfile, ispath))
    {
        return false;
    }

    if (!TwoFileOperation(oldfile, newfile, 0x0002))  // FO_COPY
    {
        if (s_nFileOpRet != 0)
        {
            std::wostringstream buf;
            buf << GetSystemErrorString(s_nFileOpRet);
            buf << L", " << oldfile << L"->" << newfile;
            X3LOG_ERROR2(L"@FileUtility:IDS_COPYFILE_FAIL", buf.str());
        }
        return false;
    }

    return true;
}

void Cx_FileUtility::SetMsgBoxOwnerWnd(HWND hWnd)
{
    m_hMsgBoxOwnerWnd = hWnd;
}

HWND Cx_FileUtility::GetMsgBoxOwnerWnd()
{
    return m_hMsgBoxOwnerWnd;
}

std::wstring Cx_FileUtility::RelToAbs(const wchar_t* pszRel, bool bRelIsFile,
                                      const wchar_t* pszBase, bool bBaseIsFile)
{
    wchar_t szPath[MAX_PATH * 2] = { 0 };

    if (pszRel != NULL)
    {
        if (IsPathSlash(pszRel[0]) && !IsPathSlash(pszRel[1])   // "\xxx"
            && (!IsNotNull(pszBase) || wcschr(pszBase, L':') != NULL))
        {
            if (IsNotNull(pszBase))
            {
                wcsncpy_s(szPath, MAX_PATH, pszBase, MAX_PATH);
            }
            else
            {
                GetModuleFileNameW(x3::GetMainModuleHandle(), szPath, MAX_PATH);
            }

            wcsncpy_s(wcschr(szPath, L':') + 1, MAX_PATH, pszRel, MAX_PATH);
        }
        else if (PathIsRelativeW(pszRel))
        {
            if (IsNotNull(pszBase))
            {
                wcsncpy_s(szPath, MAX_PATH, pszBase, MAX_PATH);
                if (bBaseIsFile)
                {
                    ReplaceSlash(szPath);
                    PathRemoveFileSpecW(szPath);
                }
            }
            else
            {
                GetModuleFileNameW(x3::GetMainModuleHandle(), szPath, MAX_PATH);
                PathRemoveFileSpecW(szPath);
            }
            PathAppendW(szPath, pszRel);
        }
        else
        {
            wcsncpy_s(szPath, MAX_PATH, pszRel, MAX_PATH);
        }

        PathRemoveBackslashW(szPath);
        if (!bRelIsFile)
        {
            PathAddBackslashW(szPath);
        }
    }

    return szPath;
}

std::wstring Cx_FileUtility::AbsToRel(const wchar_t* pszAbs, bool bAbsIsFile,
                                      const wchar_t* pszBase, bool bBaseIsFile)
{
    wchar_t szPath[MAX_PATH] = { 0 };
    wchar_t szBasePath[MAX_PATH] = { 0 };

    if (pszAbs != NULL)
    {
        if (!IsNotNull(pszBase))
        {
            GetModuleFileNameW(x3::GetMainModuleHandle(), szBasePath, MAX_PATH);
            pszBase = szBasePath;
            bBaseIsFile = true;
        }
#ifdef _WIN32
        if (IsNotNull(pszBase) && PathRelativePathToW(szPath, pszBase,
            bBaseIsFile ? FILE_ATTRIBUTE_NORMAL : FILE_ATTRIBUTE_DIRECTORY,
            pszAbs,
            bAbsIsFile ? FILE_ATTRIBUTE_NORMAL : FILE_ATTRIBUTE_DIRECTORY))
        {
            if (IsPathSlash(szPath[0]))     //  \xxx  ->  .\xxx
            {
                StrCpyW(szBasePath, szPath);
                szPath[0] = L'.';
                StrCpyW(szPath + 1, szBasePath);
            }
        }
        else
#endif
        {
            wcsncpy_s(szPath, MAX_PATH, pszAbs, MAX_PATH);
        }
    }

    return szPath;
}

std::wstring Cx_FileUtility::ChangeFileNameSuffix(const wchar_t* filename,
                                                  const wchar_t* pszSuffix)
{
    wchar_t szNewFile[MAX_PATH] = { 0 };

    if (filename != NULL && pszSuffix != NULL)
    {
        ASSERT(wcschr(pszSuffix, L'.') != NULL);
        wcsncpy_s(szNewFile, MAX_PATH, filename, MAX_PATH);
        PathRenameExtensionW(szNewFile, pszSuffix);
    }

    return szNewFile;
}

std::wstring Cx_FileUtility::GetFileTitle(const wchar_t* filename)
{
    wchar_t szNewFile[MAX_PATH] = { 0 };

    if (filename != NULL)
    {
        wchar_t* pszName = PathFindFileNameW(filename);
        if (pszName != NULL)
        {
            wcsncpy_s(szNewFile, MAX_PATH, pszName, MAX_PATH);
            ReplaceSlash(szNewFile);
            PathRemoveExtensionW(szNewFile);
        }
    }

    return szNewFile;
}

std::wstring Cx_FileUtility::GetFileName(const wchar_t* filename)
{
    if (NULL == filename || 0 == filename[0])
        return L"";

    wchar_t szTemp[MAX_PATH];
    wcsncpy_s(szTemp, MAX_PATH, PathFindFileNameW(filename), MAX_PATH);
    PathRemoveBackslashW(szTemp);

    return szTemp;
}

std::wstring Cx_FileUtility::GetExtension(const wchar_t* filename)
{
    return filename ? wcsrchr(filename, '.') : L"";
}

std::wstring Cx_FileUtility::GetPathOfFile(const wchar_t* filename)
{
    wchar_t szPath[MAX_PATH] = { 0 };

    if (filename != NULL)
    {
        wcsncpy_s(szPath, MAX_PATH, filename, MAX_PATH);
        ReplaceSlash(szPath);
        PathRemoveBackslashW(szPath);
        PathRemoveFileSpecW(szPath);
        if (szPath[0] != 0)
        {
            PathAddBackslashW(szPath);
        }
    }

    return szPath;
}

std::wstring Cx_FileUtility::MakeFileName(const std::wstring& wstrPath,
                                          const std::wstring& wstrFileTitle,
                                          const std::wstring& wstrExtName)
{
    wchar_t szFileName[MAX_PATH * 2] = { 0 };

    if (wstrPath.empty() || wstrFileTitle.empty())
    {
        return szFileName;
    }
    wcsncpy_s(szFileName, MAX_PATH, wstrPath.c_str(), MAX_PATH);

    if (wstrExtName.empty())
    {
        PathAppendW(szFileName, GetFileName(wstrFileTitle.c_str()).c_str());
    }
    else if (wcsrchr(wstrExtName.c_str(), L'.') == NULL)
    {
        PathAppendW(szFileName, GetFileTitle(wstrFileTitle.c_str()).c_str());
        wcscat_s(szFileName, MAX_PATH, L".");
        wcscat_s(szFileName, MAX_PATH, wstrExtName.c_str());
    }
    else
    {
        PathAppendW(szFileName, GetFileTitle(wstrFileTitle.c_str()).c_str());
        wcscat_s(szFileName, MAX_PATH, wcsrchr(wstrExtName.c_str(), '.'));
    }

    szFileName[MAX_PATH - 1] = 0;

    return szFileName;
}

std::wstring Cx_FileUtility::CreateFileName(const std::wstring& wstrPath,
                                            const std::wstring& wstrPrefix,
                                            const std::wstring& wstrExtName,
                                            bool bReturnRel)
{
    wchar_t szFileName[MAX_PATH] = { 0 };

    for (int i = 0; i < 9999; i++)
    {
        if (0 == i)
        {
            wcscpy_s(szFileName, _countof(szFileName), wstrPrefix.c_str());
        }
        else
        {
            swprintf_s(szFileName, _countof(szFileName), L"%s%03d", wstrPrefix.c_str(), i);
        }
        if (!wstrExtName.empty())
        {
            if (wcschr(wstrExtName.c_str(), L'.') == NULL)
            {
                wcscat_s(szFileName, _countof(szFileName), L".");
            }
            wcscat_s(szFileName, _countof(szFileName), wstrExtName.c_str());
        }

        std::wstring wstrFile (RelToAbs(szFileName, true, wstrPath.c_str(), false));

        if (!x3::FileUtility()->IsPathFileExists(wstrFile.c_str()))
        {
            if (!bReturnRel)
            {
                return wstrFile;
            }
            break;
        }
    }

    return szFileName;
}

std::wstring Cx_FileUtility::GetModifyTime(const std::wstring& wstrFileName)
{
    wchar_t szTime[20] = { 0 };
    HANDLE hFile = NULL;

    if (OpenFileForRead(hFile, wstrFileName.c_str()))
    {
#ifdef _WIN32
        FILETIME ftCreate, ftAccess, ftWrite;
        SYSTEMTIME stUTC, stLocal;

        if (::GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
        {
            FileTimeToSystemTime(&ftWrite, &stUTC);
            SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

            swprintf_s(szTime, _countof(szTime), L"%04d-%02d-%02d %02d:%02d:%02d",
                stLocal.wYear, stLocal.wMonth, stLocal.wDay,
                stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
        }
#endif

        CloseFile(hFile);
    }

    return szTime;
}

DWORD Cx_FileUtility::GetFileSize(const std::wstring& wstrFileName)
{
    DWORD nFileSize = 0;
    HANDLE hFile = NULL;

    if (OpenFileForRead(hFile, wstrFileName.c_str()))
    {
        DWORD dwFileSizeHigh = 0;
        nFileSize = ::GetFileSize(hFile, &dwFileSizeHigh);
        if (dwFileSizeHigh > 0)
            nFileSize = (DWORD)-1;

        CloseFile(hFile);
    }

    return nFileSize;
}

int Cx_FileUtility::CompareFileName(const wchar_t* filename1, const wchar_t* filename2,
                                    long* pSamePartCount)
{
    int nRet = 0;

    if (!IsNotNull(filename1) || !IsNotNull(filename2))
    {
        if (IsNotNull(filename1) != IsNotNull(filename2))
        {
            nRet = (IsNotNull(filename1) > IsNotNull(filename2)) ? 1 : -1;
        }
        if (pSamePartCount)
        {
            *pSamePartCount = 0;
        }

        return nRet;
    }

    long nSamePartCount = 0;
    const wchar_t* pszFile1 = filename1;
    const wchar_t* pszFile2 = filename2;

    if (L'.' == pszFile1[0] && IsPathSlash(pszFile1[1]))
    {
        pszFile1 += 2;
    }
    if (L'.' == pszFile2[0] && IsPathSlash(pszFile2[1]))
    {
        pszFile2 += 2;
    }

    while (0 == nRet && (*pszFile1 != 0 || *pszFile2 != 0))
    {
        int nPos1 = wcscspn(pszFile1, L"\\/");
        int nPos2 = wcscspn(pszFile2, L"\\/");

        nRet = _wcsnicmp(pszFile1, pszFile2, nPos1 > nPos2 ? nPos1 : nPos2);
        if (0 == nRet && nPos1 > 0)
        {
            nSamePartCount++;
        }

        pszFile1 += pszFile1[nPos1] ? nPos1 + 1 : nPos1;
        pszFile2 += pszFile2[nPos2] ? nPos2 + 1 : nPos2;
    }

    if (pSamePartCount)
    {
        *pSamePartCount = nSamePartCount;
    }

    return nRet;
}

#ifdef _MSC_VER
#pragma comment(lib, "version.lib")
#endif

bool Cx_FileUtility::GetFileVersion(
        std::wstring& version, const std::wstring& filename)
{
    WORD ver1, ver2, ver3, ver4;

    version.resize(0);

    return GetFileVersion(ver1, ver2, ver3, ver4, filename)
        && !version.empty();
}

bool Cx_FileUtility::GetFileVersion(
        WORD& ver1, WORD& ver2, WORD& ver3, WORD& ver4,
        const std::wstring& filename)
{
    bool ret = false;

    ver1 = 0;
    ver2 = 0;
    ver3 = 0;
    ver4 = 0;

#ifdef _MSC_VER
    DWORD handle = 0;
    wchar_t *block = NULL;

    UINT size = ::GetFileVersionInfoSizeW((wchar_t*)filename.c_str(), &handle);
    if (size > 0 && NULL != (block = new wchar_t[size]))
    {
        ::GetFileVersionInfoW((wchar_t*)filename.c_str(), handle, size, block);

        VS_FIXEDFILEINFO* pFixedInfo = NULL;
        if (::VerQueryValueW(block, L"\\", (void**)&pFixedInfo, &size))
        {
            ret = true;
            ver1 = HIWORD(pFixedInfo->dwFileVersionMS);
            ver2 = LOWORD(pFixedInfo->dwFileVersionMS);
            ver3 = HIWORD(pFixedInfo->dwFileVersionLS);
            ver4 = LOWORD(pFixedInfo->dwFileVersionLS);
        }

        delete[] block;
    }
#endif

    return ret;
}

bool Cx_FileUtility::GetFileDescription(
        std::wstring& description, const std::wstring& filename)
{
    bool ret = false;

    description.resize(0);

#ifdef _MSC_VER
    DWORD handle = 0;
    wchar_t *block = NULL;

    UINT size = ::GetFileVersionInfoSizeW((wchar_t*)filename.c_str(), &handle);
    if (size > 0 && NULL != (block = new wchar_t[size]))
    {
        ::GetFileVersionInfoW((wchar_t*)filename.c_str(), handle, size, block);

        LPWORD lpTranslate = NULL;
        wchar_t szSubBlock[41] = { 0 };
        wchar_t* szStr;

        if (::VerQueryValueW(block, L"\\VarFileInfo\\Translation",
            (void**)&lpTranslate, &size))
        {
            ret = true;

            swprintf_s(szSubBlock, _countof(szSubBlock),
                L"\\StringFileInfo\\%04x%04x\\FileDescription",
                lpTranslate[0], lpTranslate[1]);
            if (::VerQueryValueW(block, szSubBlock, (void**)&szStr, &size))
            {
                description = szStr;
            }
        }

        delete[] block;
    }
#endif

    return ret;
}
