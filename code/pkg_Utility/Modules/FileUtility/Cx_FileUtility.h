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

#ifndef _X3_UTILITY_FILEUTILITY_H
#define _X3_UTILITY_FILEUTILITY_H

#include <Ix_FileUtility.h>
#include <Ix_FileVersion.h>

class Cx_FileUtility
	: public Ix_FileUtility
	, public Ix_FileVersion
{
public:
	Cx_FileUtility();
	virtual ~Cx_FileUtility() {}

public:
	// From Ix_FileUtility
	virtual bool IsPathFileExists(LPCWSTR pszFileName, bool bWrite = false);
	virtual bool IsPath(LPCWSTR pszFileName, bool bCheckExists = false);
	virtual bool CreateDirectory(LPCWSTR pszFileName, bool bIsPath);
	virtual bool VerifyFileCanWrite(LPCWSTR pszFileName);
	virtual bool DeletePathFile(LPCWSTR pszFileName, bool bRecycle = false);
	virtual bool MovePathFile(LPCWSTR pszOldFile, LPCWSTR pszNewFile);
	virtual bool RenamePathFile(LPCWSTR pszOldFile, LPCWSTR pszNewFile);
	virtual bool CopyPathFile(LPCWSTR pszOldFile, LPCWSTR pszNewFile);
	virtual void SetMsgBoxOwnerWnd(HWND hWnd);
	virtual HWND GetMsgBoxOwnerWnd();
	virtual std::wstring RelToAbs(LPCWSTR pszRel, bool bRelIsFile, 
		LPCWSTR pszBase = NULL, bool bBaseIsFile = true);
	virtual std::wstring AbsToRel(LPCWSTR pszAbs, bool bAbsIsFile, 
		LPCWSTR pszBase = NULL, bool bBaseIsFile = true);
	virtual std::wstring ChangeFileNameSuffix(LPCWSTR pszFileName, LPCWSTR pszSuffix);
	virtual std::wstring GetFileTitle(LPCWSTR pszFileName);
	virtual std::wstring GetFileName(LPCWSTR pszFileName);
	virtual std::wstring GetExtension(LPCWSTR pszFileName);
	virtual std::wstring GetPathOfFile(LPCWSTR pszFileName);
	virtual std::wstring MakeFileName(const std::wstring& wstrPath, 
		const std::wstring& wstrFileTitle, const std::wstring& wstrExtName);
	virtual std::wstring CreateFileName(const std::wstring& wstrPath, 
		const std::wstring& wstrPrefix, const std::wstring& wstrExtName, 
		bool bReturnRel = true);
	virtual std::wstring GetModifyTime(const std::wstring& wstrFileName);
	virtual ULONG GetFileSize(const std::wstring& wstrFileName);
	virtual int CompareFileName(LPCWSTR pszFileName1, LPCWSTR pszFileName2, 
		long* pSamePartCount = NULL);

	// From Ix_FileVersion
	virtual bool GetFileVersion(std::wstring& version, const std::wstring& filename);
	virtual bool GetFileVersion(WORD& ver1, WORD& ver2, 
		WORD& ver3, WORD& ver4, const std::wstring& filename);
	virtual bool GetFileDescription(std::wstring& description, const std::wstring& filename);

private:
	bool TwoFileOperation(LPCWSTR pszOldFile, LPCWSTR pszNewFile, UINT wFunc);

private:
	HWND	m_hMsgBoxOwnerWnd;
};

#endif // _X3_UTILITY_FILEUTILITY_H
