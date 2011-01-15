/*! \file Ix_StringConvert.h
 *  \brief 定义文本转换实用操作的接口 Ix_StringConvert
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.12.28
 */
#ifndef X3_UTIL_ISTRINGCONVERT_H_
#define X3_UTIL_ISTRINGCONVERT_H_

#include "ClsID_TextUtil.h"

//! 文本转换实用操作的接口
/*!
    \interface Ix_StringConvert
    \ingroup _GROUP_UTILITY_
    \see CLSID_TextUtil, StringConvert(), Ix_TextFileUtil, ConvStr.h
*/
interface Ix_StringConvert
{
    //! 去掉文字两端的空白字符（半角空格、全角空格、换行符）
    /*!
        \param[in,out] text 待转换的字符串
        \param[in] targets 要去掉字符的字符集合，为NULL则取为默认的空白字符
        \return 是否改变了文本
    */
    virtual bool TrimSpace(std::wstring& text, const wchar_t* targets = NULL) = 0;

    //! 去掉文字开头的空白字符（半角空格、全角空格、换行符）
    /*!
        \param[in,out] text 待转换的字符串
        \param[in] targets 要去掉字符的字符集合，为NULL则取为默认的空白字符
        \return 是否改变了文本
    */
    virtual bool TrimLeft(std::wstring& text, const wchar_t* targets = NULL) = 0;

    //! 去掉文字末尾的空白字符（半角空格、全角空格、换行符）
    /*!
        \param[in,out] text 待转换的字符串
        \param[in] targets 要去掉字符的字符集合，为NULL则取为默认的空白字符
        \return 是否改变了文本
    */
    virtual bool TrimRight(std::wstring& text, const wchar_t* targets = NULL) = 0;

    //! 去掉非法字符
    /*! 去掉ASCII码小于0x20的字符（制表符、换行符和回车符除外）
        \param[in,out] text 待检测转换的字符串
        \param[in] targets 要去掉字符的字符集合，为NULL则取为小于0x20的字符
        \return 是否改变了文本
    */
    virtual bool RemoveInvalidChars(std::wstring& text, const wchar_t* targets = NULL) = 0;

    //! 替换文本，将找到的所有子串替换为新的内容
    /*!
        \param[in,out] text 待替换的字符串
        \param[in] match 匹配内容
        \param[in] newtext 对匹配到的内容换为该项内容
        \return 是否改变了文本
    */
    virtual bool ReplaceAll(std::wstring& text, 
        const std::wstring& match, 
        const std::wstring& newtext) = 0;

    //! 将一个文本中的特定字符替换为对应的其他字符
    /*! 在text中查找match中的任何字符，对找到的字符替换为chars中对应序号的字符
        \param[in,out] text 待替换的字符串
        \param[in] match 匹配内容，只要和其中任何一个字符相同就算匹配成功
        \param[in] chars 要替换成的新字符的集合，字符数必须和match相同
        \return 是否改变了文本
    */
    virtual bool ReplaceChar(std::wstring& text, 
        const std::wstring& match, 
        const std::wstring& chars) = 0;

    //! 将全角字符转换为半角字符
    /*!
        \param[in,out] text 待转换的字符串
        \param[in] punct 是否连同标点符号也一起转换
        \return 是否改变了文本
    */
    virtual bool ToDBC(std::wstring& text, bool punct = false) = 0;

    //! UNICODE串转换为ANSI串
    /*!
        \param text 要转换的内容，为UNICODE串，即UTF16编码
        \param codepage 要返回哪种编码的ANSI编码串，
            例如 CP_UTF8 表示UTF-8格式编码，默认为CP_ACP
        \return ANSI编码串
    */
    virtual std::string ToAnsi(const std::wstring& text, UINT codepage = CP_ACP) = 0;

    //! ANSI串转换为UNICODE串
    /*!
        \param text 要转换的内容，为ANSI串，其编码为codepage
        \param codepage text为哪种编码，例如 CP_UTF8 表示UTF-8格式编码，默认为CP_ACP
        \return UNICODE串，即UTF16编码
    */
    virtual std::wstring ToUnicode(const std::string& text, UINT codepage = CP_ACP) = 0;
};

//! 得到文本转换操作对象
/*!
    \ingroup _GROUP_UTILITY_
    \see Ix_TextFileUtil
*/
inline Cx_Interface<Ix_StringConvert> StringConvert()
{
    Cx_Interface<Ix_StringConvert> pIFUtility(CLSID_TextUtil);
#ifdef ASSERT
    ASSERT(pIFUtility.IsNotNull());
#endif
    return pIFUtility;
}

#endif // X3_UTIL_ISTRINGCONVERT_H_
