/*! \file Ix_StringCoding.h
 *  \brief Define string coding converter interface: Ix_StringCoding
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.07.21
 */
#ifndef X3_UTIL_ISTRINGCODING_H_
#define X3_UTIL_ISTRINGCODING_H_

#include "ClsID_TextUtil.h"

//! String coding converter interface.
/*!
    \interface Ix_StringCoding
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_TextUtil, Ix_StringConvert
*/
class Ix_StringCoding : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_StringCoding)

    //! Returns the md5 hash of a string.
    /*!
        \param text the original string.
        \return the hash as a lowercase 32-character hexadecimal number.
    */
    virtual std::wstring MD5(const std::wstring& text) = 0;

    //! Encodes binary data to Base64 code.
    /*!
        \param[out] text string of encoded data.
        \param[in] data the binary data.
        \param[in] size size of binary data.
        \param[in] codetype three chars used for Base64 code: 63rd, 64th and padding char.
        \return ref to string of encoded data.
    */
    virtual std::wstring& Base64(std::wstring& text, 
        const BYTE* data, int size,
        const wchar_t* codetype = L"+/=") = 0;

    //! Decodes Base64 code to binary data.
    /*!
        \param[out] data outputs the binary data.
        \param[in] text string of encoded data.
        \param[in] codetype three chars used for Base64 code: 63rd, 64th and padding char.
        \return ref to the binary data.
    */
    virtual std::vector<BYTE>& UnBase64(std::vector<BYTE>& data, 
        const std::wstring& text, const wchar_t* codetype = L"+/=") = 0;

    //! Encodes binary data to Base64 code.
    /*!
        \param[out] text string of encoded data.
        \param[in] data the original string.
        \param[in] codetype three chars used for Base64 code: 63rd, 64th and padding char.
        \return reference to string of encoded data.
    */
    virtual std::wstring& Base64(std::wstring& text, 
        const std::string& data, const wchar_t* codetype = L"+/=") = 0;

    //! Decodes Base64 code to binary data.
    /*!
        \param[out] data outputs the original string.
        \param[in] text string of encoded data.
        \param[in] codetype three chars used for Base64 code: 63rd, 64th and padding char.
        \return reference to the original string.
    */
    virtual std::string& UnBase64(std::string& data, 
        const std::wstring& text, const wchar_t* codetype = L"+/=") = 0;
};

#endif // X3_UTIL_ISTRINGCODING_H_
