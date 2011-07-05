/*! \file Ix_TextFileUtil.h
 *  \brief Define text format file I/O operation interface: Ix_TextFileUtil
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_UTIL_ITEXTFILEUTIL_H_
#define X3_UTIL_ITEXTFILEUTIL_H_

#include "ClsID_TextUtil.h"

//! Text format file I/O operation interface.
/*!
    \interface Ix_TextFileUtil
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_TextUtil, TextFileUtil(), Ix_StringConvert
*/
class Ix_TextFileUtil : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_TextFileUtil)

    //! 读取一个文本文件
    /*!
        \param[out] content 读取到的内容
        \param[in] filename 文件全名
        \param[in] limitMB 文件长度上限，单位为MB，超出则截断
        \param[in] codepage 如果文件以前是ANSI编码，则指定是哪种编码，
            例如 CP_UTF8 表示UTF-8格式编码，默认为CP_ACP
        \return 是否取到了内容
        \see GetLineCount, SaveTextFile
    */
    virtual bool ReadTextFile(std::wstring& content, 
        const std::wstring& filename, 
        ULONG limitMB = 16, int codepage = 0) = 0;

    //! 将一个宽字符串内容保存到文件中
    /*!
        \param content 要保存的内容
        \param filename 文件全名
        \param utf16 文件编码格式, true: UTF16, false: ANSI/ASCII
        \param codepage 如果要保存为ANSI编码文件，则指定是哪种编码，
            例如 CP_UTF8 表示UTF-8格式编码，默认为CP_ACP
        \return 是否保存成功
        \see ReadTextFile
    */
    virtual bool SaveTextFile(const std::wstring& content, 
        const std::wstring& filename, 
        bool utf16 = true, int codepage = 0) = 0;

    //! 将一个ANSI字符串内容保存到文件中
    /*!
        \param content 要保存的内容
        \param filename 文件全名
        \param utf16 文件编码格式, true: UTF16, false: ANSI/ASCII
        \param codepage 如果要保存为UNICODE编码文件(UTF16)，则指定传入
            的content是哪种编码，例如 CP_UTF8 表示UTF-8格式编码，默认为CP_ACP
        \return 是否保存成功
    */
    virtual bool SaveTextFile(const std::string& content, 
        const std::wstring& filename, 
        bool utf16 = true, int codepage = 0) = 0;

    //! 检查一个文件是否为UNICODE文件
    /*! 检查文件前面几个字符是否为FFFE，即 UTF-16 (little-endian)
        \param[in] filename 文件全名
        \param[out] utf16 文件编码格式, true: UTF16, false: ANSI/ASCII
        \return 是否检查成功
    */
    virtual bool IsUTF16File(const std::wstring& filename, bool& utf16) = 0;

    //! 检查一个文件是否为UTF8的ANSI格式文件
    /*! 检查文件前面几个字符是否为EFBBBF，即 UTF-8
        \param[in] filename 文件全名
        \param[out] utf8 文件编码格式是否为UTF8
        \return 是否检查成功
    */
    virtual bool IsUTF8File(const std::wstring& filename, bool& utf8) = 0;

    //! 如果是UTF16文件则转换为指定编码的ANSI编码文件
    /*!
        \param filename 文件全名
        \param codepage 要保存为哪种编码的ANSI编码文件，
            例如 CP_UTF8 表示UTF-8格式编码，默认为CP_ACP
        \return true if successful.
    */
    virtual bool UnicodeToAnsi(const std::wstring& filename, int codepage = 0) = 0;

    //! 如果是ANSI编码文件则转换为UTF16文件
    /*!
        \param filename 文件全名
        \param codepage 如果文件以前是ANSI编码，则指定是哪种编码，
            例如 CP_UTF8 表示UTF-8格式编码，默认为CP_ACP
        \return true if successful.
    */
    virtual bool AnsiToUnicode(const std::wstring& filename, int codepage = 0) = 0;

    //! 得到文本内容的行数
    virtual long GetLineCount(const std::wstring& text) = 0;

    //! 得到文本内容的一行文字
    /*!
        \param[in] text 文本内容
        \param[in] line 行号，0表示第一行
        \param[out] nextLine 填充下一行文字(无则NULL)的起始地址，为NULL则忽略
        \return 该行号对应的一行文字
        \see ReadTextFile
    */
    virtual std::wstring GetLine(const std::wstring& text, 
        long line, const wchar_t** nextLine = NULL) = 0;

    //! 返回是否为空白文字行（由半角空格、全角空格、换行符组成）
    virtual bool IsSpaceLine(const std::wstring& text) = 0;
};

namespace x3 {

//! Get text format file I/O operator object.
/*!
    \ingroup _GROUP_UTILITY_
    \see Ix_StringConvert
*/
inline Cx_Interface<Ix_TextFileUtil> TextFileUtil()
{
    Cx_Interface<Ix_TextFileUtil> pIFUtility(x3::CLSID_TextUtil);
#ifdef ASSERT
    ASSERT(pIFUtility.IsNotNull());
#endif
    return pIFUtility;
}

} // x3

#endif // X3_UTIL_ITEXTFILEUTIL_H_
