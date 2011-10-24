/*! \file ScanFiles.h
 *  \brief Define directory scanning function (ScanFiles) and callback class CScanFilesCallback.
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef UTILFUNC_SCANFILES_H_
#define UTILFUNC_SCANFILES_H_

#include <string>

namespace x3 {

//! Callback interface for directory scanning.
class IScanFilesCallback
{
public:
    virtual ~IScanFilesCallback() {}

    //! Notify when a subfolder is found.
    /*!
        \param[in] path absolute path ending with slash char.
        \param[in,out] recursive True if need to include all child folders. The default value is passed by ScanFiles.
        \param[in,out] cancel If you want to stop scanning then set it as true.
    */
    virtual void OnCheckPath(const wchar_t* path, bool& recursive, bool& cancel) = 0;

    //! Notify when a file is found.
    /*!
        \param[in] filename absolute file name.
        \param[in] ext The postfix of the file beginning with dot, or empty string if the file has not postfix.
        \param[in,out] cancel If you want to stop scanning then set it as true.
    */
    virtual void OnCheckFile(const wchar_t* filename, const wchar_t* ext, bool& cancel) = 0;
};

//! The default implement class of IScanFilesCallback.
/*!
    \ingroup _GROUP_UTILFUNC
    \see ScanFiles
*/
class CScanFilesCallback : public IScanFilesCallback
{
public:
    CScanFilesCallback() {}
    virtual ~CScanFilesCallback() {}

    virtual void OnCheckPath(const wchar_t* path, bool& recursive, bool& cancel)
        { path; recursive; cancel; }
    virtual void OnCheckFile(const wchar_t* filename, const wchar_t* ext, bool& cancel)
        { filename; ext; cancel; }

private:
    CScanFilesCallback(const CScanFilesCallback&);
    void operator=(const CScanFilesCallback&);
};

//! Scans all files in a directory.
/*!
    \ingroup _GROUP_UTILFUNC
    \param back Object address of scanning callback.
    \param path Absolute path to scan. It must be not empty and the end slash char is unnecessary.
    \param recursive True if need to include all child folders. False if only one folder.
    \return count of files found.
    \see CScanFilesCallback
*/
inline long ScanFiles(IScanFilesCallback* back,
                      const wchar_t* path, bool recursive)
{
    long count = 0;
#ifdef _WIN32
    WIN32_FIND_DATAW fd;
    wchar_t filename[MAX_PATH];

    lstrcpynW(filename, path, MAX_PATH);
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
            if (fd.cFileName[0] != L'.')
            {
                lstrcpynW(filename, path, MAX_PATH);
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
            lstrcpynW(filename, path, MAX_PATH);
            PathAppendW(filename, fd.cFileName);

            count++;
            back->OnCheckFile(filename,
                PathFindExtensionW(filename), cancel);
        }

        loop = ::FindNextFileW(hfind, &fd);
    }
    ::FindClose(hfind);
#endif

    return count;
}

//! Callback class for scanning files of the specified postfix.
/*!
    \ingroup _GROUP_UTILFUNC
    \see ScanFiles
*/
class CScanFilesByExtension : public CScanFilesCallback
{
public:
    //! Constructor.
    /*!
        \param files Filling with filenames found.
        \param ext The specified postfix beginning with dot.
    */
    CScanFilesByExtension(std::vector<std::wstring>* files, const std::wstring& ext)
        : m_files(files), m_ext(ext)
    {
    }

protected:
    virtual void OnCheckFile(const wchar_t* filename, const wchar_t* ext, bool& cancel)
    {
        cancel;
        if (_wcsicmp(m_ext.c_str(), ext) == 0)
        {
            m_files->push_back(filename);
        }
    }

protected:
    std::vector<std::wstring>*  m_files;    //!< Filling with filenames found.
    std::wstring                m_ext;      //!< The specified postfix beginning with dot.

private:
    CScanFilesByExtension();
    CScanFilesByExtension(const CScanFilesByExtension&);
    void operator=(const CScanFilesByExtension&);
};

} // x3
#endif // UTILFUNC_SCANFILES_H_
