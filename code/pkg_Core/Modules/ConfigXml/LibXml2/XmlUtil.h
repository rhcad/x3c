// Copyright 2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

//! \file XmlUtil.h
//! \brief 定义使用LibXml2实现的 XMLDOM 操作类 CXmlUtil

#ifndef __XMLUTIL_LIBXML2_INCLUDED_
#define __XMLUTIL_LIBXML2_INCLUDED_
#define USE_LIBXML2

#include <libxml++/parsers/parser.h>
#include <libxml++/document.h>
using namespace xmlpp;

typedef Document* XMLDOMDocumentPtr;
typedef Element* XMLDOMElementPtr;
typedef Node* XMLDOMNodePtr;

//! XML文件加解密的接口
interface IXmlFileCrypt
{
    //! 装载一个加密的XML文件
    /*!
        \param[out] doc 输出新的XML文档对象
        \param[in] filename 文件全名，可以是能输出XML内容的URL地址
        \return 是否装载成功，如果失败将由CXmlUtil按普通方式装载
    */
    virtual bool Decrypt(XMLDOMDocumentPtr& doc, const wchar_t* filename) = 0;

    //! 对一个刚保存的XML文件进行加密
    /*!
        \param[in] filename 本地的文件全名
        \return 是否执行成功
    */
    virtual bool CryptFile(const wchar_t* filename) = 0;
};

//! MSXML DOM 操作类, 不需要MFC支持
class CXmlUtil
{
public:

//--------------------------------------
// 文件操作
//--------------------------------------

    //! 创建一个XML文档对象
    /*! 新创建的XML文档对象还未保存到文件中
        \param[out] doc 输出新的XML文档对象
        \param[in] rootName 根节点名称，用于自动创建根节点
        \param[in] encoding XML语言编码，默认为Unicode格式的“UTF-8”
        \param[in] nameSpace XML命名空间
        \param[in] comment 根节点的说明内容
        \return 是否创建成功
    */
    static bool NewXMLFile(
        XMLDOMDocumentPtr& doc,
        const wchar_t* rootName,
        const wchar_t* encoding = L"UTF-8",
        const wchar_t* nameSpace = L"",
        const wchar_t* comment = L"");

    //! 创建一个XML文档对象，并得到根节点
    /*! 新创建的XML文档对象还未保存到文件中
        \param[out] doc 输出新的XML文档对象
        \param[in] root 输出根节点对象
        \param[in] rootName 根节点名称，用于自动创建根节点
        \param[in] encoding XML语言编码，默认为Unicode格式的“UTF-8”
        \param[in] nameSpace XML命名空间
        \return 是否创建成功
    */
    static bool NewXMLFile2(
        XMLDOMDocumentPtr& doc,
        XMLDOMElementPtr& root,
        const wchar_t* rootName,
        const wchar_t* encoding = L"UTF-8",
        const wchar_t* nameSpace = L"");

    //! 装载一个XML文件
    /*!
        \param[out] doc 输出新的XML文档对象
        \param[in] filename 文件全名，可以是能输出XML内容的URL地址
        \param[in] handler 加解密的操作对象
        \return 是否装载成功，失败原因是不能读取文件或不能创建XML文档对象
    */
    static bool LoadXMLFile(
        XMLDOMDocumentPtr& doc,
        const wchar_t* filename,
        IXmlFileCrypt* handler = NULL);

    //! 装载一个XML文件，并检查根节点
    /*!
        \param[out] doc 输出新的XML文档对象
        \param[in] filename 文件全名，可以是能输出XML内容的URL地址
        \param[in] root 输出根节点对象
        \param[in] rootName 根节点名称
        \param[in] handler 加解密的操作对象
        \return 是否装载成功，失败原因是不存在指定的根节点等错误
    */
    static bool LoadXMLFile(
        XMLDOMDocumentPtr& doc,
        const wchar_t* filename,
        XMLDOMElementPtr& root,
        const wchar_t* rootName,
        IXmlFileCrypt* handler = NULL);

    //! 保存到一个XML文件
    /*!
        \param[in] doc 要保存的XML文档对象
        \param[in] filename 文件全名
        \param[in] handler 加解密的操作对象
        \return 是否保存成功
    */
    static bool SaveXMLFile(
        const XMLDOMDocumentPtr& doc,
        const wchar_t* filename,
        IXmlFileCrypt* handler = NULL);

    //! 从字符串中装载XML文件
    /*!
        \param[out] doc 输出新创建的XML文档对象
        \param[in] xmlstr XML格式的字符串
        \return 是否装载成功
    */
    static bool LoadXMLFromString(
        XMLDOMDocumentPtr& doc,
        const wchar_t* xmlstr);

    //! 获取XML字符串
    /*!
        \param[in] doc XML文档对象
        \return XML格式的字符串
        \see GetNodeXMLString
    */
    static std::wstring GetXMLString(
        const XMLDOMDocumentPtr& doc);

    //! 获取根节点名称
    /*!
        \param[in] doc XML文档对象
        \return 根节点名称
        \see GetTagName
    */
    static std::wstring GetRootName(
        const XMLDOMDocumentPtr& doc);

//--------------------------------------
// 节点操作
//--------------------------------------

    //! 得到根节点
    /*!
        \param[out] root 输出XML根节点对象
        \param[in] doc XML文档对象
        \param[in] rootName 根节点名称
        \return 是否存在给定名称的根节点
        \see GetRootName
    */
    static bool GetRoot(
        XMLDOMElementPtr& root,
        const XMLDOMDocumentPtr& doc,
        const wchar_t* rootName);

    //! 得到子节点个数
    /*!
        \param[in] ele XML元素对象
        \param[in] childName 子元素名称
        \return 给定元素ele下的名称为childName的子节点个数
    */
    static long GetChildCount(
        const XMLDOMElementPtr& ele,
        const wchar_t* childName);

    //! 得到一个子节点
    /*!
        \param[out] outEle 输出子元素对象
        \param[in] parent XML元素对象
        \param[in] childName 子元素名称
        \param[in] index 第几个子元素，从0开始
        \return 是否有对应的子元素对象
    */
    static bool GetChild(
        XMLDOMElementPtr& outEle,
        const XMLDOMElementPtr& parent,
        const wchar_t* childName,
        long index = 0);

    //! 得到或创建一个子节点
    /*!
        \param[out] outEle 输出子元素对象
        \param[in] doc XML文档对象
        \param[in] parent XML元素对象
        \param[in] childName 子元素名称
        \return 是否执行成功
    */
    static bool GetChildOrAdd(
        XMLDOMElementPtr& outEle,
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& parent,
        const wchar_t* childName);

    //! 添加一个子节点
    /*!
        \param[out] outEle 输出子元素对象
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] childName 子元素名称
        \return 是否执行成功
    */
    static bool AddChild(
        XMLDOMElementPtr& outEle,
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* childName);

    //! 删除一个子节点
    /*!
        \param[in] ele XML元素对象
        \param[in] childName 子元素名称
        \param[in] index 要删除第几个子元素，从0开始
        \return 是否有对应的子元素对象被删除
    */
    static bool DelChild(
        const XMLDOMElementPtr& ele,
        const wchar_t* childName,
        long index);

    //! 删除一个子节点
    /*!
        \param[in] parent XML父元素对象
        \param[in,out] eleDel 要删除的XML子元素对象
        \return 是否有对应的子元素对象被删除
    */
    static bool DelChild(
        const XMLDOMElementPtr& parent,
        XMLDOMElementPtr& eleDel);

    //! 删除所有子节点
    /*! 删除给定元素下的所有名称为childName的子节点
        \param[in] ele XML元素对象
        \param[in] childName 子元素名称
        \param[in] attrName 子元素的标识属性名，可选值
        \param[in] attrValue 标识属性名对应的值，attrName不为空时有效
        \return 删除的子元素个数
    */
    static long DelChildren(
        const XMLDOMElementPtr& ele,
        const wchar_t* childName,
        const wchar_t* attrName = L"", const wchar_t* attrValue = L"");

    //! 查找节点数组中的子节点序号
    /*!
        \param[out] outEle 输出查找到的子元素对象
        \param[in] parent XML元素对象，在该节点下查找
        \param[in] childName 子元素名称
        \param[in] fieldName 子元素的下一级元素名称
        \param[in] value 子元素的下一级元素的内容
        \return 找到的是第几个子元素，-1表示找不到
    */
    static long FindElement(
        XMLDOMElementPtr& outEle,
        const XMLDOMElementPtr& parent,
        const wchar_t* childName,
        const wchar_t* fieldName,
        const wchar_t* value);

    //! 查找节点数组中的子节点序号
    /*! 查找元素parent的子元素节点，条件是该子元素中有名称为attr1、
        内容为value1的属性节点，可以有两个属性条件。\n
        下面是数组内容示例：\n
        　\<parent_item\>\n
        　　　\<item id="12" type="font" other=""\>\<otherinfo/\>\</item\>\n
        　　　\<item id="34" type="char" other=".."\>\<otherinfo/\>\</item\>\n
        　　　\<item id="34" type="para" other="info"\>\<otherinfo/\>\</item\>\n
        　\</parent_item\>\n
        调用FindElement(outEle, parent, "item", "id", "34", "type", "char")返回1

        \param[out] outEle 输出查找到的子元素对象
        \param[in] parent XML元素对象，在该节点下查找
        \param[in] childName 子元素名称
        \param[in] attr1 子元素的属性名称
        \param[in] value1 子元素的属性值
        \param[in] attr2 子元素的另一个属性名称，为空则忽略
        \param[in] value2 子元素的另一个属性对应的值，attr2不为空时有效
        \return 找到的是第几个子元素，-1表示找不到
    */
    static long FindElementByAttr(
        XMLDOMElementPtr& outEle,
        const XMLDOMElementPtr& parent,
        const wchar_t* childName,
        const wchar_t* attr1,
        const wchar_t* value1,
        const wchar_t* attr2,
        const wchar_t* value2);

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
        const XMLDOMElementPtr& ele);

    //! 得到节点内容，识别CDATA
    /*! 节点的内容既可以是简单的文字内容，也可以是CDATA节点
        \param[in] pNode XML元素对象
        \param[in] defValue 节点内容的默认值
        \return 给定节点的内容
    */
    static std::wstring GetText(
        const XMLDOMNodePtr& pNode,
        const wchar_t* defValue = L"");

    //! 得到一个节点的CDATA值
    /*!
        \param[in] ele XML元素对象
        \param[in] defValue 节点的CDATA内容的默认值
        \return 该节点的CDATA内容
    */
    static std::wstring GetTextCDATA(
        const XMLDOMElementPtr& ele,
        const wchar_t* defValue = L"");

    //! 设置节点内容
    /*!
        \param[in] pNode XML元素对象
        \param[in] pszText 给定节点的内容
        \return 是否设置成功
    */
    static bool SetText(
        const XMLDOMNodePtr& pNode,
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
        const XMLDOMNodePtr& pNode,
        const wchar_t* pszText);

    //! 设置一个节点的CDATA值
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] value 节点的CDATA内容
        \return 是否设置成功
    */
    static bool SetTextCDATA(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* value);

    //! 获取一个节点的XML字符串
    /*!
        \param[in] ele XML元素对象
        \return XML字符串
        \see GetXMLString
    */
    static std::wstring GetNodeXMLString(
        const XMLDOMElementPtr& ele);

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
        const XMLDOMElementPtr& ele,
        const wchar_t* pszName);

    //! 得到一个属性节点内容
    /*!
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称
        \param[in] defValue 属性内容的默认值
        \return 该元素的属性内容
    */
    static std::wstring GetAttribute(
        const XMLDOMElementPtr& ele,
        const wchar_t* pszName,
        const wchar_t* defValue = L"");

    //! 得到一个属性节点整数内容
    /*!
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称
        \param[in] defValue 属性内容的默认整数值
        \return 该元素的属性内容整数值
    */
    static int GetAttributeInt(
        const XMLDOMElementPtr& ele,
        const wchar_t* pszName,
        int defValue = 0);

    //! 得到一个属性节点布尔值内容
    /*!
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称
        \param[in] defValue 属性内容的默认布尔值
        \return 该元素的属性内容布尔值
    */
    static bool GetAttributeBool(
        const XMLDOMElementPtr& ele,
        const wchar_t* pszName,
        int defValue = 0);

    //! 得到一个属性节点浮点型内容
    /*!
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称
        \param[in] defValue 属性内容的默认浮点型值
        \param[out] pstrUnit 如果传入变量地址，则存放属性内容尾部的的单位名称
        \return 该元素的属性内容浮点型值
    */
    static double GetAttributeFloat(
        const XMLDOMElementPtr& ele,
        const wchar_t* pszName,
        double defValue = 0,
        std::wstring* pstrUnit = NULL);

    //! 设置一个属性节点内容
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称，没有则自动创建属性节点
        \param[in] value 属性内容
        \return 是否设置成功
    */
    static bool SetAttribute(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* pszName,
        const wchar_t* value);

    //! 设置一个属性节点整数内容
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称，没有则自动创建属性节点
        \param[in] value 属性的整数内容
        \return 是否设置成功
    */
    static bool SetAttributeInt(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* pszName,
        int value);

    //! 设置一个属性节点布尔值属性值
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称，没有则自动创建属性节点
        \param[in] value 属性的布尔内容，自动转换成“true”或“false”
        \return 是否设置成功
    */
    static bool SetAttributeBool(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* pszName,
        int value);

    //! 设置一个属性节点浮点型内容
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] pszName 该元素的属性节点名称，没有则自动创建属性节点
        \param[in] value 属性的浮点型内容
        \param[in] unitName 在属性内容尾部附加的单位名称，为空则忽略
        \param[in] decimal 保留小数点后第几位数，超出部分四舍五入
        \return 是否设置成功
    */
    static bool SetAttributeFloat(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* pszName,
        double value,
        const wchar_t* unitName = L"",
        int decimal = 4);

    //! 得到一个节点的属性值，识别CDATA
    /*! 子节点的内容既可以是简单的文字内容，也可以是CDATA节点
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称
        \param[in] defValue 子节点内容的默认值
        \return 该子节点的内容
    */
    static std::wstring GetField(
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        const wchar_t* defValue = L"");

    //! 设置一个节点的属性值
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] value 子节点内容
        \return 是否设置成功
    */
    static bool SetField(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        const wchar_t* value);

    //! 得到一个节点的整数属性值，识别十六进制数
    /*!
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称
        \param[in] defValue 子节点内容的默认整数值
        \return 该子节点内容整数值
    */
    static int GetFieldInt(
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        int defValue = 0);

    //! 得到一个节点的布尔值属性值
    /*!
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称
        \param[in] defValue 子节点内容的默认布尔值
        \return 该子节点内容布尔值
    */
    static bool GetFieldBool(
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        int defValue = 0);

    //! 得到一个节点的浮点型属性值
    /*!
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称
        \param[in] defValue 子节点内容的默认浮点型值
        \param[out] pstrUnit 如果传入变量地址，则存放子节点内容尾部的的单位名称
        \return 该子节点内容浮点型值
    */
    static double GetFieldFloat(
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        double defValue = 0,
        std::wstring* pstrUnit = NULL);

    //! 设置一个节点的整数属性值
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] value 子节点的整数内容
        \return 是否设置成功
    */
    static bool SetFieldInt(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        int value);

    //! 设置一个节点的布尔值属性值
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] value 子节点的布尔内容，自动转换成“true”或“false”
        \return 是否设置成功
    */
    static bool SetFieldBool(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        int value);

    //! 设置一个节点的浮点型属性值
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] value 子节点的浮点型内容
        \param[in] unitName 在子节点内容尾部附加的单位名称，为空则忽略
        \param[in] decimal 保留小数点后第几位数，超出部分四舍五入
        \return 是否设置成功
    */
    static bool SetFieldFloat(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        double value,
        const wchar_t* unitName = L"",
        int decimal = 4);

    //! 设置一个节点的十六进制属性值
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] value 子节点的整数内容
        \param[in] digits 当为1到6时，整数字符串至少有指定个数字，不够就在前补零，例如"0x00012A"
        \return 是否设置成功
    */
    static bool SetFieldHex(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        int value,
        int digits = 0);

    //! 得到一个节点的CDATA属性值
    /*!
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称
        \param[in] defValue 子节点的CDATA内容的默认值
        \return 该子节点的CDATA内容
    */
    static std::wstring GetFieldCDATA(
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        const wchar_t* defValue = L"");

    //! 设置一个节点的CDATA属性值
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] fieldName 该元素的子元素节点名称，没有则自动创建节点
        \param[in] value 子节点的CDATA内容
        \return 是否设置成功
    */
    static bool SetFieldCDATA(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* fieldName,
        const wchar_t* value);

//--------------------------------------
// 其他操作
//--------------------------------------

    //! 返回上次调用的int值
    static int GetLastErrorResult();

    //! 在根节点前创建注释节点
    /*!
        \param[in] doc XML文档对象
        \param[in] comment 注释内容
        \return 是否执行成功
    */
    static bool CreateDocComment(
        const XMLDOMDocumentPtr& doc,
        const wchar_t* comment);

    //! 在指定节点前创建注释节点
    /*!
        \param[in] doc XML文档对象
        \param[in] ele XML元素对象
        \param[in] comment 注释内容
        \return 是否执行成功
    */
    static bool CreateNodeComment(
        const XMLDOMDocumentPtr& doc,
        const XMLDOMElementPtr& ele,
        const wchar_t* comment);

    //! 返回上一级节点
    static XMLDOMNodePtr GetParentNode(XMLDOMNodePtr node);
};

#endif // __XMLUTIL_LIBXML2_INCLUDED_
