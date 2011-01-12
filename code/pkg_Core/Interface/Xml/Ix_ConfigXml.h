// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
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

/*! \file Ix_ConfigXml.h
 *  \brief 定义XML配置初始化的接口 Ix_ConfigXml
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_XML_ICONFIGXML_H_
#define X3_XML_ICONFIGXML_H_

#include <XComPtr.h>

//! XML配置数据对象的类ID
const XCLSID CLSID_ConfigXmlFile("c93e1e3d-0362-4856-9a4a-31c119e324f7");

interface Ix_ConfigData;
interface Ix_ConfigSection;
interface IFileCryptHandler;

//! XML配置数据初始化的接口
/*! 使用 IFileCryptHandler 可拦截XML文件读写过程
    \interface Ix_ConfigXml
    \ingroup _GROUP_PLUGIN_XML_
    \see CLSID_ConfigXmlFile, Ix_ConfigData, Ix_ConfigTransaction
*/
interface Ix_ConfigXml
{
    //! 返回配置管理接口对象
    virtual Ix_ConfigData* GetData() = 0;

    //! 返回配置文件全名
    virtual std::wstring GetFileName() const = 0;

    //! 设置配置文件全名
    /*! 读写XML文件之前必须设置文件全名
        \param filename 文件全名，也可以是WebService的URL
    */
    virtual void SetFileName(LPCWSTR filename) = 0;

    //! 返回实际根节点名称
    /*! 没有装载XML文件时会临时加载XML文件
        \return 实际根节点名称，在没有装载XML文件时不一定和 SetRootName() 的结果相同
        \see SetRootName, Reload
    */
    virtual std::wstring GetRootName() const = 0;

    //! 设置根节点名称和XML语言编码
    /*!
        \param rootName 根节点名称，用于新建XML或在读取XML时检查合法性，
            为空则不检查XML内容的根节点
        \param encoding XML语言编码，新建XML文件时使用
        \param nmspace XML命名空间，新建XML文件时使用
        \see GetRootName, Reload
    */
    virtual void SetRootName(LPCWSTR rootName = L"root", 
        LPCWSTR encoding = L"UTF-8", 
        LPCWSTR nmspace = L"") = 0;

    //! 设置引用的Schema文件的位置
    /*! 如果设置了该属性，则在新建XML文档时使用
        \param location Schema文件的位置，可以为相对文件名
        \see GetRootName, Reload
    */
    virtual void SetSchemaLocation(LPCWSTR location) = 0;

    //! 重新装载XML文件
    /*! 放弃当前XML文档的内容，重新装载XML文档。
        如果调用过 SetRootName() 且其结果与XML内容的根节点不同则返回false；
        如果没有调用过 SetRootName()，则自动识别根节点名称
        \return 是否成功装载XML文件，失败时将新建XML文档内容
    */
    virtual bool Reload() = 0;

    //! 保存XML内容到指定的文件
    /*! 本函数不改变文档的待保存状态，也不受该状态影响
        \param filename 文件全名，空串表示使用当前文件全名
        \return 是否保存成功
    */
    virtual bool Save(LPCWSTR filename = L"") const = 0;

    //! 得到整个文档的XML内容
    /*! 如果还未新建或加载XML文件，则自动调用 Reload()
        \param[out] content XML内容，没有“UTF-8”之类的XML语言编码部分
        \return 是否获取成功
    */
    virtual bool GetXmlContent(std::wstring& content) const = 0;

    //! 装载XML内容
    /*! 如果调用过 SetRootName() 且其结果与XML内容的根节点不同则返回false
        \param content XML内容，自动跳过Unicode前缀标志
        \return 是否装载成功
    */
    virtual bool SetXmlContent(const std::wstring& content) = 0;

    //! 得到一个节点的XML内容
    /*!
        \param[out] content XML内容，没有“UTF-8”之类的XML语言编码部分
        \param[in] node 指定的一个节点
        \return 是否获取成功
    */
    virtual bool GetXmlContent(std::wstring& content, Ix_ConfigSection* node) const = 0;

    //! 设置XML文件加解密的操作对象
    /*!
        \param[in] handler 新的加解密的操作对象
        \return 原来的加解密的操作对象
    */
    virtual IFileCryptHandler* SetCryptHandler(IFileCryptHandler* handler) = 0;
};

#endif // X3_XML_ICONFIGXML_H_
