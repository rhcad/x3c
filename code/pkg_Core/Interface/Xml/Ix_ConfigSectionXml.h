/*! \file Ix_ConfigSectionXml.h
 *  \brief 定义XML数据节点接口 Ix_ConfigSectionXml
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_XML_ICONFIGSECTIONXML_H_
#define X3_XML_ICONFIGSECTIONXML_H_

#include "Ix_Object.h"

//! XML数据节点接口
/*! XML数据节点支持 Ix_ConfigSectionXml 和 Ix_ConfigSection 接口
    \interface Ix_ConfigSectionXml
    \ingroup _GROUP_PLUGIN_XML_
    \see Ix_ConfigSection
*/
interface Ix_ConfigSectionXml
{
    //! 设置每个配置项是否为子元素项
    /*! 默认值为false（每个配置项对应于一个XML属性）
        \param element true表示每个配置项(例如 GetString(L"Name") )为一个XML子元素项，
            false表示每个配置项对应于一个XML属性
    */
    virtual void UseSubElement(bool element) = 0;

    //! 得到配置项元素文字，不带配置属性名称
    /*!
        \return 本对象对应的XML节点的文字内容，支持CDATA值
    */
    virtual std::wstring GetText() = 0;

    //! 设置配置项元素文字，不带配置属性名称
    /*!
        \param value 本对象对应的XML节点的文字内容
        \param cdata 保存为CDATA值还是普通内容
        \return 是否改变了内容
    */
    virtual bool SetText(const wchar_t* value, bool cdata = false) = 0;

#ifdef _OLE2_H_
    //! 返回内部的XML元素节点(IXMLDOMElement)
    virtual IUnknown* GetDOMElement(bool addRef = false) = 0;

    //! 返回内部的XML文档对象(IXMLDOMDocument)
    virtual IUnknown* GetDOMDocument(bool addRef = false) = 0;
#endif // _OLE2_H_
};

#endif // X3_XML_ICONFIGSECTIONXML_H_
