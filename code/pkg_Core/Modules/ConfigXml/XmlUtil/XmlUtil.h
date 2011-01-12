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

//! \file XmlUtil.h
//! \brief 定义MSXML4.0 DOM 操作类CXmlUtil

#ifndef __XMLUTIL_NONMFC_INCLUDED_
#define __XMLUTIL_NONMFC_INCLUDED_
#pragma once

#include "XTPXMLhelpers.h"

//! XML文件加解密的接口
interface IXmlFileCrypt
{
    //! 装载一个加密的XML文件
    /*! 
        \param[out] doc 输出新的XML文档对象
        \param[in] pszFileName 文件全名，可以是能输出XML内容的URL地址
        \return 是否装载成功，如果失败将由CXmlUtil按普通方式装载
    */
    virtual bool Decrypt(CXTPDOMDocumentPtr& doc, const wchar_t* pszFileName) = 0;

    //! 对一个刚保存的XML文件进行加密
    /*! 
        \param[in] pszFileName 本地的文件全名
        \return 是否执行成功
    */
    virtual bool CryptFile(const wchar_t* pszFileName) = 0;
};

//! MSXML4.0 DOM 操作类, 不需要MFC支持
class CXmlUtil
{
public:
    
//--------------------------------------
// 文件操作
//--------------------------------------
    
    //! 创建一个XML文档对象
    /*! 新创建的XML文档对象还未保存到文件中
        \param[out] doc 输出新的XML文档对象
        \param[in] pszRootName 根节点名称，用于自动创建根节点
        \param[in] pszEncoding XML语言编码，默认为Unicode格式的“UTF-8”
        \param[in] pszNameSpace XML命名空间
        \param[in] pszComment 根节点的说明内容
        \return 是否创建成功
    */
    static bool NewXMLFile(
        CXTPDOMDocumentPtr& doc, 
        const wchar_t* pszRootName, 
        const wchar_t* pszEncoding = L"UTF-8", 
        const wchar_t* pszNameSpace = L"", 
        const wchar_t* pszComment = L"");
    
    //! 创建一个XML文档对象，并得到根节点
    /*! 新创建的XML文档对象还未保存到文件中
        \param[out] doc 输出新的XML文档对象
        \param[in] root 输出根节点对象
        \param[in] pszRootName 根节点名称，用于自动创建根节点
        \param[in] pszEncoding XML语言编码，默认为Unicode格式的“UTF-8”
        \param[in] pszNameSpace XML命名空间
        \return 是否创建成功
    */
    static bool NewXMLFile2(
        CXTPDOMDocumentPtr& doc, 
        CXTPDOMElementPtr& root, 
        const wchar_t* pszRootName, 
        const wchar_t* pszEncoding = L"UTF-8", 
        const wchar_t* pszNameSpace = L"");
    
    //! 装载一个XML文件
    /*! 
        \param[out] doc 输出新的XML文档对象
        \param[in] pszFileName 文件全名，可以是能输出XML内容的URL地址
        \param[in] pCryptHandler 加解密的操作对象
        \return 是否装载成功，失败原因是不能读取文件或不能创建XML文档对象
    */
    static bool LoadXMLFile(
        CXTPDOMDocumentPtr& doc, 
        const wchar_t* pszFileName, 
        IXmlFileCrypt* pCryptHandler = NULL);
    
    //! 装载一个XML文件，并检查根节点
    /*! 
        \param[out] doc 输出新的XML文档对象
        \param[in] pszFileName 文件全名，可以是能输出XML内容的URL地址
        \param[in] root 输出根节点对象
        \param[in] pszRootName 根节点名称
        \param[in] pCryptHandler 加解密的操作对象
        \return 是否装载成功，失败原因是不存在指定的根节点等错误
    */
    static bool LoadXMLFile(
        CXTPDOMDocumentPtr& doc, 
        const wchar_t* pszFileName, 
        CXTPDOMElementPtr& root, 
        const wchar_t* pszRootName, 
        IXmlFileCrypt* pCryptHandler = NULL);
    
    //! 保存到一个XML文件
    /*! 
        \param[in] doc 要保存的XML文档对象
        \param[in] pszFileName 文件全名
        \param[in] pCryptHandler 加解密的操作对象
        \return 是否保存成功
    */
    static bool SaveXMLFile(
        const CXTPDOMDocumentPtr& doc, 
        const wchar_t* pszFileName, 
        IXmlFileCrypt* pCryptHandler = NULL);
    
    //! 从字符串中装载XML文件
    /*! 
        \param[out] doc 输出新创建的XML文档对象
        \param[in] pszXML XML格式的字符串
        \return 是否装载成功
    */
    static bool LoadXMLFromString(
        CXTPDOMDocumentPtr& doc, 
        LPCSTR pszXML);

    //! 从字符串中装载XML文件，自动跳过Unicode前缀标志
    /*! 
        \param[out] doc 输出新创建的XML文档对象
        \param[in] pszXML XML格式的字符串
        \return 是否装载成功
    */
    static bool LoadXMLFromString(
        CXTPDOMDocumentPtr& doc, 
        const wchar_t* pszXML);
    
    //! 获取XML字符串
    /*! 
        \param[in] doc XML文档对象
        \return XML格式的字符串
        \see GetNodeXMLString
    */
    static std::wstring GetXMLString(
        const CXTPDOMDocumentPtr& doc);

    //! 获取根节点名称
    /*! 
        \param[in] doc XML文档对象
        \return 根节点名称
        \see GetTagName
    */
    static std::wstring GetRootName(
        const CXTPDOMDocumentPtr& doc);
    
//--------------------------------------
// 节点操作
//--------------------------------------
    
    //! 得到根节点
    /*! 
        \param[out] root 输出XML根节点对象
        \param[in] doc XML文档对象
        \param[in] pszRootName 根节点名称
        \return 是否存在给定名称的根节点
        \see GetRootName
    */
    static bool GetRoot(
        CXTPDOMElementPtr& root, 
        const CXTPDOMDocumentPtr& doc, 
        const wchar_t* pszRootName);
    
    //! 得到子节点个数
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszChildName 子元素名称
        \return 给定元素ele下的名称为pszChildName的子节点个数
    */
    static long GetChildCount(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszChildName);
    
    //! 得到一个子节点
    /*! 
        \param[out] outEle 输出子元素对象
        \param[in] parent XML元素对象
        \param[in] pszChildName 子元素名称
        \param[in] nIndex 第几个子元素，从0开始
        \return 是否有对应的子元素对象
    */
    static bool GetChild(
        CXTPDOMElementPtr& outEle, 
        const CXTPDOMElementPtr& parent, 
        const wchar_t* pszChildName, 
        long nIndex = 0);
    
    //! 得到或创建一个子节点
    /*! 
        \param[out] outEle 输出子元素对象
        \param[in] doc XML文档对象
        \param[in] parent XML元素对象
        \param[in] pszChildName 子元素名称
        \return 是否执行成功
    */
    static bool GetChildOrAdd(
        CXTPDOMElementPtr& outEle, 
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& parent, 
        const wchar_t* pszChildName);
    
    //! 添加一个子节点
    /*! 
        \param[out] outEle 输出子元素对象
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszChildName 子元素名称
        \return 是否执行成功
    */
    static bool AddChild(
        CXTPDOMElementPtr& outEle, 
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszChildName);
    
    //! 删除一个子节点
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszChildName 子元素名称
        \param[in] nIndex 要删除第几个子元素，从0开始
        \return 是否有对应的子元素对象被删除
    */
    static bool DelChild(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszChildName, 
        long nIndex);

    //! 删除一个子节点
    /*! 
        \param[in] parent XML父元素对象
        \param[in,out] eleDel 要删除的XML子元素对象
        \return 是否有对应的子元素对象被删除
    */
    static bool DelChild(
        const CXTPDOMElementPtr& parent, 
        CXTPDOMElementPtr& eleDel);
    
    //! 删除所有子节点
    /*! 删除给定元素下的所有名称为pszChildName的子节点
        \param[in] ele XML元素对象
        \param[in] pszChildName 子元素名称
        \param[in] pszAttrName 子元素的标识属性名，可选值
        \param[in] pszAttrValue 标识属性名对应的值，pszAttrName不为空时有效
        \return 删除的子元素个数
    */
    static long DelChildren(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszChildName, 
        const wchar_t* pszAttrName = L"", const wchar_t* pszAttrValue = L"");
    
    //! 查找节点数组中的子节点序号
    /*! 
        \param[out] outEle 输出查找到的子元素对象
        \param[in] parent XML元素对象，在该节点下查找
        \param[in] pszElement 子元素名称
        \param[in] pszField 子元素的下一级元素名称
        \param[in] pszValue 子元素的下一级元素的内容
        \return 找到的是第几个子元素，-1表示找不到
    */
    static long FindElement(
        CXTPDOMElementPtr& outEle, 
        const CXTPDOMElementPtr& parent, 
        const wchar_t* pszElement, 
        const wchar_t* pszField, 
        const wchar_t* pszValue);
    
    //! 查找节点数组中的子节点序号
    /*! 查找元素parent的子元素节点，条件是该子元素中有名称为pszAttr1、
        内容为pszValue1的属性节点，可以有两个属性条件。\n
        下面是数组内容示例：\n
        　\<parent_item\>\n
        　　　\<item id="12" type="font" other=""\>\<otherinfo/\>\</item\>\n
        　　　\<item id="34" type="char" other=".."\>\<otherinfo/\>\</item\>\n
        　　　\<item id="34" type="para" other="info"\>\<otherinfo/\>\</item\>\n
        　\</parent_item\>\n
        调用FindElement(outEle, parent, "item", "id", "34", "type", "char")返回1
        
        \param[out] outEle 输出查找到的子元素对象
        \param[in] parent XML元素对象，在该节点下查找
        \param[in] pszElement 子元素名称
        \param[in] pszAttr1 子元素的属性名称
        \param[in] pszValue1 子元素的属性值
        \param[in] pszAttr2 子元素的另一个属性名称，为空则忽略
        \param[in] pszValue2 子元素的另一个属性对应的值，pszAttr2不为空时有效
        \return 找到的是第几个子元素，-1表示找不到
    */
    static long FindElementByAttr(
        CXTPDOMElementPtr& outEle, 
        const CXTPDOMElementPtr& parent, 
        const wchar_t* pszElement, 
        const wchar_t* pszAttr1, 
        const wchar_t* pszValue1, 
        const wchar_t* pszAttr2, 
        const wchar_t* pszValue2);
    
//--------------------------------------
// 节点内容
//--------------------------------------

    //! 得到节点的名称
    /*! 
        \param[in] ele XML元素对象
        \return 给定节点的XML标记名称
        \see GetRootName
    */
    static std::wstring GetTagName(
        const CXTPDOMElementPtr& ele);
    
    //! 得到节点内容，识别CDATA
    /*! 节点的内容既可以是简单的文字内容，也可以是CDATA节点
        \param[in] pNode XML元素对象
        \param[in] pszDefault 节点内容的默认值
        \return 给定节点的内容
    */
    static std::wstring GetText(
        const CXTPDOMNodePtr& pNode, 
        const wchar_t* pszDefault = L"");

    //! 得到一个节点的CDATA值
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszDefault 节点的CDATA内容的默认值
        \return 该节点的CDATA内容
    */
    static std::wstring GetTextCDATA(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszDefault = L"");
    
    //! 设置节点内容
    /*! 
        \param[in] pNode XML元素对象
        \param[in] pszText 给定节点的内容
        \return 是否设置成功
    */
    static bool SetText(
        const CXTPDOMNodePtr& pNode, 
        const wchar_t* pszText);
    
    //! 设置节点内容
    /*! 
        本函数用于不论是否定义了_UNICODE条件编译宏，都能直接设置宽字节字符串内容，
        避免在ANSI编译模式下将LPCWSTR转换为BSTR时自动进行编码转换而出现乱码。

        使用情况举例：从非UNICODE文本文件中读取单字节字符流，用MultiByteToWideChar
        函数转换为宽字节字符串，再用本函数设置节点内容，这样就能将特定语言编码的
        内容转换为UNICODE的XML内容。

        \param[in] pNode XML元素对象
        \param[in] pszText 给定节点的UNICODE内容，末尾有零结束符
        \return 是否设置成功
    */
    static bool SetTextW(
        const CXTPDOMNodePtr& pNode, 
        const wchar_t* pszText);

    //! 设置一个节点的CDATA值
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszValue 节点的CDATA内容
        \return 是否设置成功
    */
    static bool SetTextCDATA(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszValue);

    //! 获取一个节点的XML字符串
    /*! 
        \param[in] ele XML元素对象
        \return XML字符串
        \see GetXMLString
    */
    static std::wstring GetNodeXMLString(
        const CXTPDOMElementPtr& ele);

//--------------------------------------
// 属性操作
//--------------------------------------

    //! 删除一个属性
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszName 要删除的属性名称
        \return 是否删除了属性
    */
    static bool DelAttribute(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszName);
    
    //! 得到一个属性节点内容
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称
        \param[in] pszDefault 属性内容的默认值
        \return 该元素的属性内容
    */
    static std::wstring GetAttribute(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszName, 
        const wchar_t* pszDefault = L"");
    
    //! 得到一个属性节点整数内容
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称
        \param[in] nDef 属性内容的默认整数值
        \return 该元素的属性内容整数值
    */
    static UINT GetAttributeInt(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszName, 
        INT nDef = 0);
    
    //! 得到一个属性节点布尔值内容
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称
        \param[in] bDef 属性内容的默认布尔值
        \return 该元素的属性内容布尔值
    */
    static bool GetAttributeBool(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszName, 
        BOOL bDef = FALSE);
    
    //! 得到一个属性节点浮点型内容
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称
        \param[in] dDef 属性内容的默认浮点型值
        \param[out] pstrUnit 如果传入变量地址，则存放属性内容尾部的的单位名称
        \return 该元素的属性内容浮点型值
    */
    static double GetAttributeFloat(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszName, 
        double dDef = 0, 
        std::wstring* pstrUnit = NULL);
    
    //! 设置一个属性节点内容
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称，没有则自动创建属性节点
        \param[in] pszValue 属性内容
        \return 是否设置成功
    */
    static bool SetAttribute(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszName, 
        const wchar_t* pszValue);
    
    //! 设置一个属性节点整数内容
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称，没有则自动创建属性节点
        \param[in] nVal 属性的整数内容
        \return 是否设置成功
    */
    static bool SetAttributeInt(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszName, 
        INT nVal);
    
    //! 设置一个属性节点布尔值属性值
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称，没有则自动创建属性节点
        \param[in] bVal 属性的布尔内容，自动转换成“true”或“false”
        \return 是否设置成功
    */
    static bool SetAttributeBool(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszName, 
        BOOL bVal);
    
    //! 设置一个属性节点浮点型内容
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称，没有则自动创建属性节点
        \param[in] dVal 属性的浮点型内容
        \param[in] pszUnit 在属性内容尾部附加的单位名称，为空则忽略
        \param[in] decimal 保留小数点后第几位数，超出部分四舍五入
        \return 是否设置成功
    */
    static bool SetAttributeFloat(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszName, 
        double dVal, 
        const wchar_t* pszUnit = L"", 
        int decimal = 4);
    
    //! 得到一个节点的属性值，识别CDATA
    /*! 子节点的内容既可以是简单的文字内容，也可以是CDATA节点
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称
        \param[in] pszDefault 子节点内容的默认值
        \return 该子节点的内容
    */
    static std::wstring GetField(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        const wchar_t* pszDefault = L"");
    
    //! 设置一个节点的属性值
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] pszValue 子节点内容
        \return 是否设置成功
    */
    static bool SetField(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        const wchar_t* pszValue);
    
    //! 得到一个节点的整数属性值，识别十六进制数
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称
        \param[in] nDef 子节点内容的默认整数值
        \return 该子节点内容整数值
    */
    static UINT GetFieldInt(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        INT nDef = 0);
    
    //! 得到一个节点的布尔值属性值
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称
        \param[in] bDef 子节点内容的默认布尔值
        \return 该子节点内容布尔值
    */
    static bool GetFieldBool(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        BOOL bDef = FALSE);
    
    //! 得到一个节点的浮点型属性值
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称
        \param[in] dDef 子节点内容的默认浮点型值
        \param[out] pstrUnit 如果传入变量地址，则存放子节点内容尾部的的单位名称
        \return 该子节点内容浮点型值
    */
    static double GetFieldFloat(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        double dDef = 0, 
        std::wstring* pstrUnit = NULL);
    
    //! 设置一个节点的整数属性值
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] nVal 子节点的整数内容
        \return 是否设置成功
    */
    static bool SetFieldInt(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        INT nVal);
    
    //! 设置一个节点的布尔值属性值
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] bVal 子节点的布尔内容，自动转换成“true”或“false”
        \return 是否设置成功
    */
    static bool SetFieldBool(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        BOOL bVal);
    
    //! 设置一个节点的浮点型属性值
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] dVal 子节点的浮点型内容
        \param[in] pszUnit 在子节点内容尾部附加的单位名称，为空则忽略
        \param[in] decimal 保留小数点后第几位数，超出部分四舍五入
        \return 是否设置成功
    */
    static bool SetFieldFloat(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        double dVal, 
        const wchar_t* pszUnit = L"", 
        int decimal = 4);
    
    //! 设置一个节点的十六进制属性值
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] nVal 子节点的整数内容
        \param[in] nDigits 当为1到6时，整数字符串至少有指定个数字，不够就在前补零，例如"0x00012A"
        \return 是否设置成功
    */
    static bool SetFieldHex(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        INT nVal, 
        INT nDigits = 0);
    
    //! 得到一个节点的CDATA属性值
    /*! 
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称
        \param[in] pszDefault 子节点的CDATA内容的默认值
        \return 该子节点的CDATA内容
    */
    static std::wstring GetFieldCDATA(
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        const wchar_t* pszDefault = L"");
    
    //! 设置一个节点的CDATA属性值
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszFieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] pszValue 子节点的CDATA内容
        \return 是否设置成功
    */
    static bool SetFieldCDATA(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszFieldName, 
        const wchar_t* pszValue);
    
//--------------------------------------
// 其他操作
//--------------------------------------

    //! 返回上次调用的HRESULT值
    static HRESULT GetLastErrorResult();

    //! 在根节点前创建注释节点
    /*! 
        \param[in] doc XML文档对象
        \param[in] pszComment 注释内容
        \return 是否执行成功
    */
    static bool CreateDocComment(
        const CXTPDOMDocumentPtr& doc, 
        const wchar_t* pszComment);

    //! 在指定节点前创建注释节点
    /*! 
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszComment 注释内容
        \return 是否执行成功
    */
    static bool CreateNodeComment(
        const CXTPDOMDocumentPtr& doc, 
        const CXTPDOMElementPtr& ele, 
        const wchar_t* pszComment);

    //! 得到四舍五入的字符串（去掉小数点后末尾的'0'）
    /*! 
        \param[in] value 要转换的浮点数
        \param[in] decimal 保留小数点后第几位数，超出部分四舍五入
        \return 转换后的字符串
    */
    static std::wstring RoundStr(
        double value, 
        int decimal = 4);
};

#endif // __XMLUTIL_NONMFC_INCLUDED_