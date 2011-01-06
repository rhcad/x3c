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

/*! \file ScanFiles.h
 *  \brief 定义扫描目录文件的函数 ScanFiles 及回调类 CScanFilesCallback
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef UTILFUNC_SCANFILES_H_
#define UTILFUNC_SCANFILES_H_

//! 扫描目录文件时的回调接口
interface IScanFilesCallback
{
	//! 扫描到一个子目录的通知
	/*!
		\param[in] path 扫描到的子目录的文件全名，末尾有反斜号
		\param[in,out] recursive 是否扫描该子目录下的文件，默认为 ScanFiles() 传入的值
		\param[in,out] cancel 如果要停止所有扫描则设置为 true
	*/
	virtual void OnCheckPath(LPCWSTR path, bool& recursive, bool& cancel) = 0;

	//! 扫描到一个文件的通知
	/*!
		\param[in] filename 扫描到的文件的文件全名
		\param[in] ext 如果有后缀名则以点号开头，否则为空串
		\param[in,out] cancel 如果要停止所有扫描则设置为 true
	*/
	virtual void OnCheckFile(LPCWSTR filename, LPCWSTR ext, bool& cancel) = 0;
};

//! 扫描目录文件时的回调接口的默认实现类
/*!
	\ingroup _GROUP_UTILFUNC
	\see ScanFiles
*/
class CScanFilesCallback : public IScanFilesCallback
{
public:
	CScanFilesCallback() {}
	virtual ~CScanFilesCallback() {}

	virtual void OnCheckPath(LPCWSTR path, bool& recursive, bool& cancel)
		{ path; recursive; cancel; }
	virtual void OnCheckFile(LPCWSTR filename, LPCWSTR ext, bool& cancel)
		{ filename; ext; cancel; }
};

//! 扫描目录下的所有文件
/*!
	\ingroup _GROUP_UTILFUNC
	\param back 传入回调接口的实现对象的地址
	\param path 目录的文件全名，非空，末尾的反斜号可有可无
	\param recursive 是否扫描子目录下的文件
	\return 扫描过的文件总数
	\see CScanFilesCallback
*/
inline long ScanFiles(IScanFilesCallback* back, 
					  LPCWSTR path, bool recursive)
{
	WIN32_FIND_DATAW fd;
	WCHAR filename[MAX_PATH];
	long count = 0;
	
	StrCpyNW(filename, path, MAX_PATH);
	PathAppendW(filename, L"*.*");
	
	HANDLE hfind = ::FindFirstFileW(filename, &fd);
	BOOL loop = (hfind != INVALID_HANDLE_VALUE);
	bool cancel = false;

	while (loop && !cancel)
	{
		if (fd.dwFileAttributes & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM))
		{
			loop = ::FindNextFileW(hfind, &fd);
			continue;
		}

		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (fd.cFileName[0] != '.')
			{
				StrCpyNW(filename, path, MAX_PATH);
				PathAppendW(filename, fd.cFileName);
				PathAddBackslashW(filename);

				bool bTempRecursive = recursive;
				back->OnCheckPath(filename, bTempRecursive, cancel);
				if (bTempRecursive && !cancel)
				{
					count += ScanFiles(back, filename, recursive);
				}
			}
		}
		else
		{
			StrCpyNW(filename, path, MAX_PATH);
			PathAppendW(filename, fd.cFileName);

			count++;
			back->OnCheckFile(filename, 
				PathFindExtensionW(filename), cancel);
		}
		
		loop = ::FindNextFileW(hfind, &fd);
	}
	::FindClose(hfind);
	
	return count;
}

//! 扫描特定后缀名文件的回调类
/*!
	\ingroup _GROUP_UTILFUNC
	\see ScanFiles
*/
class CScanFilesByExtension : public CScanFilesCallback
{
public:
	//! 构造函数
	/*!
		\param files 用于存放找到的文件全名
		\param ext 特定的后缀名，以点号开头
	*/
	CScanFilesByExtension(std::vector<std::wstring>* files, const std::wstring& ext)
		: m_files(files), m_ext(ext)
	{
		ASSERT(m_files != NULL);
	}

protected:
	virtual void OnCheckFile(LPCWSTR filename, LPCWSTR ext, bool& cancel)
	{
		cancel;
		if (StrCmpIW(m_ext.c_str(), ext) == 0)
		{
			m_files->push_back(filename);
		}
	}

protected:
	std::vector<std::wstring>*	m_files;	//!< 存放找到的文件全名
	std::wstring				m_ext;		//!< 特定的后缀名，以点号开头
};

#endif // UTILFUNC_SCANFILES_H_