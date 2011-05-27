/*! \file IFileCryptHandler.h
 *  \brief Define interface of file encryption and decryption: IFileCryptHandler
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_IFILECRYPTHANDLER_H_
#define X3_IFILECRYPTHANDLER_H_

//! Interface of file encryption and decryption.
interface IFileCryptHandler
{
    //! Read decrypted content from a file encrypted.
    /*!
        \param[in] filename full filename of the file encrypted.
        \param[out] buffer the decrypted content readed, need free using FreeBuffer.
        \return 0 to indicate success.
    */
    virtual int Decrypt(const wchar_t* filename, wchar_t** buffer) = 0;

    //! Free buffer returned by Decrypt.
    virtual void FreeBuffer(wchar_t* buffer) = 0;

    //! Enrypt a file.
    /*! Reads content from srcfile, encrypt the content, then save to destfile.
        \param srcfile full filename of the source file whose content is decrypted.
        \param destfile full filename of the target file encrypted.
        \return 0 to indicate success.
    */
    virtual int CryptFile(const wchar_t* srcfile, const wchar_t* destfile) = 0;
};

#endif // X3_IFILECRYPTHANDLER_H_
