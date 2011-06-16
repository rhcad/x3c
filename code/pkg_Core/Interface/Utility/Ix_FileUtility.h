/*! \file Ix_FileUtility.h
 *  \brief 定义文件和目录的实用操作的接口 Ix_FileUtility
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_IFILEUTILITY_H_
#define X3_UTIL_IFILEUTILITY_H_

#include <XComPtr.h>

X3CLSID_DEFINE(CLSID_FileUtility, "933b3bf9-69d0-4be7-8e49-92b73669d8db");

//! 文件和目录的实用操作的接口(文件检测)
/*!
    \interface Ix_FileUtility1
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility, FileUtility()
*/
class Ix_FileUtility1
{
public:
    virtual ~Ix_FileUtility1() {}

    //! 检查一个目录或文件是否存在
    /*!
        \param filename 目录或文件的文件全名，如果是目录则末尾要有斜号
        \param checkWrite 是否检查可写
        \return 目录或文件是否存在，如果checkWrite为true则同时要求可读写
    */
    virtual bool IsPathFileExists(const wchar_t* filename, bool checkWrite = false) = 0;

    //! 检查是否为目录名
    /*!
        \param filename 目录或文件的文件全名，
            如果checkExists为true则目录末尾的斜号可有可无
        \param checkExists 是否根据实际文件存在情况决定是否为目录名
        \return true:目录, false:文件
    */
    virtual bool IsPath(const wchar_t* filename, bool checkExists = false) = 0;

    //! 返回文件修改日期时间
    /*!
        \param filename 文件全名
        \return 日期时间，格式为“YYYY-MM-DD HH:MM:SS”，失败时为空串
    */
    virtual std::wstring GetModifyTime(const std::wstring& filename) = 0;

    //! 返回文件大小，字节
    /*!
        \param filename 文件全名
        \return 文件大小，字节，失败时为0，大于4G时为0xFFFFFFFF
        \see FileSizeToString
    */
    virtual DWORD GetFileSize(const std::wstring& filename) = 0;
};

//! 文件和目录的实用操作的接口(文件改动操作)
/*!
    \interface Ix_FileUtility2
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility, FileUtility()
*/
class Ix_FileUtility2
{
public:
    virtual ~Ix_FileUtility2() {}

    //! 为一个文件全名级联创建中间目录
    /*! 失败时会用 X3LOG_ERROR2 记录日志
        \param filename 文件或目录的全名
        \param isPath 给定的filename是路径名还是文件名
        \return 是否创建成功
    */
    virtual bool CreateDirectory(const wchar_t* filename, bool isPath) = 0;

    //! 确保一个文件名是可写的(自动创建目录和去掉只读属性)
    /*! 失败时会用 X3LOG_ERROR2 记录日志
        \param filename 文件全名
        \return 是否可创建文件或可改写
    */
    virtual bool VerifyFileCanWrite(const wchar_t* filename) = 0;

    //! 删除一个目录或文件
    /*! 失败时会用 X3LOG_ERROR2 记录日志
        \param filename 目录或文件的文件全名
        \param recycle true表示放进回收站，false表示直接删除
        \return 是否执行成功. 文件全名为空或文件不存在则返回true
    */
    virtual bool DeletePathFile(const wchar_t* filename, bool recycle = false) = 0;

    //! 移动一个目录或文件
    /*! 失败时会用 X3LOG_ERROR2 记录日志，自动创建目标文件的文件夹
        \param oldFile 原来的目录或文件的文件全名
        \param newFile 新的目录或文件的文件全名
        \return 是否执行成功. oldFile为空或原文件不存在则返回true
    */
    virtual bool MovePathFile(const wchar_t* oldFile, const wchar_t* newFile) = 0;

    //! 重命名一个目录或文件
    /*! 失败时会用 X3LOG_ERROR2 记录日志
        \param oldFile 原来的目录或文件的文件全名
        \param newFile 新的目录或文件的文件全名
        \return 是否执行成功. oldFile为空或原文件不存在则返回true
    */
    virtual bool RenamePathFile(const wchar_t* oldFile, const wchar_t* newFile) = 0;

    //! 复制一个目录或文件
    /*! 失败时会用 X3LOG_ERROR2 记录日志，自动创建目标文件的文件夹
        \param oldFile 原来的目录或文件的文件全名
        \param newFile 新的目录或文件的文件全名
        \return 是否执行成功. oldFile为空或原文件不存在则返回true
    */
    virtual bool CopyPathFile(const wchar_t* oldFile, const wchar_t* newFile) = 0;

    //! 设置消息框的拥有者窗口
    virtual void SetMsgBoxOwnerWnd(HWND hwnd) = 0;

    //! 返回消息框的拥有者窗口
    virtual HWND GetMsgBoxOwnerWnd() = 0;
};

//! 文件和目录的实用操作的接口(文件名转换)
/*!
    \interface Ix_FileUtility3
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility, FileUtility()
*/
class Ix_FileUtility3
{
public:
    virtual ~Ix_FileUtility3() {}

    //! 相对路径转换为绝对路径
    /*! 将一个相对于给定参考路径的相对路径转换为绝对路径，如果已经是绝对路径则不变
        \param relFile 要转换的相对路径，例如“./abc”、“/Root”、“../1/2.dat”
        \param relIsFile 相对路径是文件名还是路径名
        \param baseFile 参考路径，即相对哪个路径来转换，为空则取EXE路径
        \param baseIsFile 参考路径是文件名还是路径名
        \return 转换后的绝对路径，如果relIsFile为false则绝对路径末尾有斜号
    */
    virtual std::wstring RelToAbs(const wchar_t* relFile, bool relIsFile,
        const wchar_t* baseFile = NULL, bool baseIsFile = true) = 0;

    //! 绝对路径转换为相对路径
    /*! 将一个绝对路径转换为相对于给定参考路径的相对路径
        \param absFile 要转换的绝对路径
        \param absIsFile 绝对路径是文件名还是路径名
        \param baseFile 参考路径，即相对哪个路径来转换，为空则取EXE路径
        \param baseIsFile 参考路径是文件名还是路径名
        \return 转换后的相对路径，如果relIsFile为false则绝对路径末尾有斜号，
            如果失败则和原来路径相同
    */
    virtual std::wstring AbsToRel(const wchar_t* absFile, bool absIsFile,
        const wchar_t* baseFile = NULL, bool baseIsFile = true) = 0;

    //! 改变文件全名的后缀名
    /*!
        \param[in] filename 给定的文件全名，和文件是否存在无关
        \param[in] suffix 新的后缀名，必须含有点号
        \return 新的文件全名
    */
    virtual std::wstring ChangeFileNameSuffix(
        const wchar_t* filename, const wchar_t* suffix) = 0;

    //! 根据路径、文件名、后缀名形成一个文件全名
    /*!
        \param path 目录全名，非空，末尾的斜号可有可无
        \param title 文件名标题，非空，忽略路径，如果ext不为空则忽略后缀名
        \param ext 文件扩展名，忽略路径和文件名标题，可以没有点号
        \return 新的文件全名
    */
    virtual std::wstring MakeFileName(const std::wstring& path,
        const std::wstring& title, const std::wstring& ext) = 0;

    //! 计算新的相对文件名
    /*!
        \param path 目录全名，新文件在该目录将唯一，末尾的斜号可有可无
        \param prefix 文件名前缀，例如“t”，可为空
        \param ext 文件扩展名，点号可以不是第一个字符，没有点号则会自动补上，
            例如“xml”、“_s.jpg”
        \param returnRel 是否返回相对文件名，false表示返回新的绝对文件全名
        \return 新的相对文件名，例如“t12.xml”
    */
    virtual std::wstring CreateFileName(const std::wstring& path,
        const std::wstring& prefix, const std::wstring& ext,
        bool returnRel = true) = 0;
};

//! 文件和目录的实用操作的接口(文件名提取)
/*!
    \interface Ix_FileUtility4
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility, FileUtility()
*/
class Ix_FileUtility4
{
public:
    virtual ~Ix_FileUtility4() {}

    //! 得到文件名标题，无路径和后缀名
    virtual std::wstring GetFileTitle(const wchar_t* filename) = 0;

    //! 得到文件或目录的文件名，无路径
    virtual std::wstring GetFileName(const wchar_t* filename) = 0;

    //! 得到文件扩展名，含有点号
    virtual std::wstring GetExtension(const wchar_t* filename) = 0;

    //! 得到文件或目录所在的目录，末尾有斜号
    /*!
        \param filename 文件或目录的文件全名，目录末尾的斜号可有可无
        \return 所在的目录，末尾有斜号
    */
    virtual std::wstring GetPathOfFile(const wchar_t* filename) = 0;

    //! 判断两个文件名是否相同
    /*! 本函数比较两个文件全名或两个相对文件名，自动区分目录分隔符
        \param[in] filename1 第一个文件夹或文件的文件名
        \param[in] filename2 第二个文件夹或文件的文件名
        \param[out] samePartCount 如果不为NULL则填充文件名中有几部分是相同的，
            其中文件全名的各部分是指中间文件夹名及文件标题名
        \return 0表示文件名相同，1或-1表示文件名不同
    */
    virtual int CompareFileName(const wchar_t* filename1, const wchar_t* filename2,
        long* samePartCount = NULL) = 0;
};

//! 文件和目录的实用操作的接口
/*!
    \interface Ix_FileUtility
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_FileUtility
    \see x3::FileUtility()->xxx(), RelToAbs.h 文件实用函数
*/
class Ix_FileUtility
    : public Ix_FileUtility1
    , public Ix_FileUtility2
    , public Ix_FileUtility3
    , public Ix_FileUtility4
{
public:
    virtual ~Ix_FileUtility() {}
};

namespace x3 {

//! 得到文件操作对象
/*!
    \ingroup _GROUP_UTILITY_
    \see RelToAbs.h 文件实用函数
*/
inline Cx_Interface<Ix_FileUtility> FileUtility()
{
    Cx_Interface<Ix_FileUtility> pIFUtility(x3::CLSID_FileUtility);
#ifdef ASSERT
    ASSERT(pIFUtility.IsNotNull());
#endif
    return pIFUtility;
}

} // x3

#endif // X3_UTIL_IFILEUTILITY_H_
