// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef _X3_UTILITY_FILEUTILITY_H
#define _X3_UTILITY_FILEUTILITY_H

#include <Utility/Ix_FileUtility.h>
#include <Utility/Ix_FileVersion.h>

class Cx_FileUtility
    : public Ix_FileUtility
    , public Ix_FileVersion
{
    X3BEGIN_CLASS_DECLARE(Cx_FileUtility)
        X3DEFINE_INTERFACE_ENTRY(Ix_FileUtility)
        X3DEFINE_INTERFACE_ENTRY(Ix_FileVersion)
    X3END_CLASS_DECLARE()
protected:
    Cx_FileUtility();
    virtual ~Cx_FileUtility() {}

private:
    // From Ix_FileUtility
    virtual bool IsPathFileExists(const wchar_t* filename, bool bWrite = false);
    virtual bool IsPath(const wchar_t* filename, bool bCheckExists = false);
    virtual bool CreateDirectory(const wchar_t* filename, bool bIsPath);
    virtual bool VerifyFileCanWrite(const wchar_t* filename);
    virtual bool DeletePathFile(const wchar_t* filename, bool bRecycle = false);
    virtual bool MovePathFile(const wchar_t* oldfile, const wchar_t* newfile);
    virtual bool RenamePathFile(const wchar_t* oldfile, const wchar_t* newfile);
    virtual bool CopyPathFile(const wchar_t* oldfile, const wchar_t* newfile);
    virtual void SetMsgBoxOwnerWnd(HWND hWnd);
    virtual HWND GetMsgBoxOwnerWnd();
    virtual std::wstring RelToAbs(const wchar_t* pszRel, bool bRelIsFile,
        const wchar_t* pszBase = NULL, bool bBaseIsFile = true);
    virtual std::wstring AbsToRel(const wchar_t* pszAbs, bool bAbsIsFile,
        const wchar_t* pszBase = NULL, bool bBaseIsFile = true);
    virtual std::wstring ChangeFileNameSuffix(const wchar_t* filename, const wchar_t* pszSuffix);
    virtual std::wstring GetFileTitle(const wchar_t* filename);
    virtual std::wstring GetFileName(const wchar_t* filename);
    virtual std::wstring GetExtension(const wchar_t* filename);
    virtual std::wstring GetPathOfFile(const wchar_t* filename);
    virtual std::wstring MakeFileName(const std::wstring& wstrPath,
        const std::wstring& wstrFileTitle, const std::wstring& wstrExtName);
    virtual std::wstring CreateFileName(const std::wstring& wstrPath,
        const std::wstring& wstrPrefix, const std::wstring& wstrExtName,
        bool bReturnRel = true);
    virtual std::wstring GetModifyTime(const std::wstring& wstrFileName);
    virtual DWORD GetFileSize(const std::wstring& wstrFileName);
    virtual int CompareFileName(const wchar_t* filename1, const wchar_t* filename2,
        long* pSamePartCount = NULL);

    // From Ix_FileVersion
    virtual bool GetFileVersion(std::wstring& version, const std::wstring& filename);
    virtual bool GetFileVersion(WORD& ver1, WORD& ver2,
        WORD& ver3, WORD& ver4, const std::wstring& filename);
    virtual bool GetFileDescription(std::wstring& description, const std::wstring& filename);

private:
    Cx_FileUtility(const Cx_FileUtility&);
    void operator=(const Cx_FileUtility&);

    bool TwoFileOperation(const wchar_t* oldfile, const wchar_t* newfile, int wFunc);

private:
    HWND    m_hMsgBoxOwnerWnd;
};

#endif // _X3_UTILITY_FILEUTILITY_H
