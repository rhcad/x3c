/*! \file IFileCryptHandler.h
 *  \brief 定义文件内容加解密的接口 IFileCryptHandler
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_IFILECRYPTHANDLER_H_
#define X3_IFILECRYPTHANDLER_H_

//! 文件内容加解密的接口
interface IFileCryptHandler
{
    //! 从一个加密文件中得到文件内容
    /*!
        \param[in] filename 已加密文件的文件全名
        \param[out] buffer 输出文件内容，用 FreeBuffer 释放
        \return 0 表示执行成功，其余表示失败
    */
    virtual int Decrypt(const wchar_t* filename, wchar_t** buffer) = 0;

    //! 释放由 Decrypt 分配的内存资源
    virtual void FreeBuffer(wchar_t* buffer) = 0;

    //! 对一个明文内容的文件进行加密
    /*! 
        \param srcfile 明文内容文件的文件全名
        \param destfile 加密文件的文件全名
        \return 0 表示执行成功，其余表示失败
    */
    virtual int CryptFile(const wchar_t* srcfile, const wchar_t* destfile) = 0;
};

#endif // X3_IFILECRYPTHANDLER_H_
