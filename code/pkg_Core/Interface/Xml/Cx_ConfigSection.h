/*! \file Cx_ConfigSection.h
 *  \brief 定义配置读写接口的封装类 Cx_ConfigSection
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_XML_CONFIGIOSECTION_H_
#define X3_XML_CONFIGIOSECTION_H_

#include "Ix_ConfigData.h"

//! 配置读写接口的封装类，对应于一个数据节点
/*! 本接口所操作的数据对象相当于是在树状层次结构中的一个数据节点，
    而 Ix_ConfigData 则对应于全部数据节点。
    \ingroup _GROUP_PLUGIN_XML_
*/
class Cx_ConfigSection : public Cx_Interface<Ix_ConfigSection>
{
public:
    //! 构造函数
    Cx_ConfigSection()
    {
    }

    //! 拷贝构造函数
    Cx_ConfigSection(const Cx_Interface<Ix_ConfigSection>& src)
        : Cx_Interface<Ix_ConfigSection>(src)
    {
    }

    //! 从Cx_Ptr构造
    Cx_ConfigSection(const Cx_Ptr& objConfigIO)
    {
        Cx_Interface<Ix_ConfigSection> pIFSec(objConfigIO);
        if (pIFSec.IsNotNull())
        {
            Cx_Interface<Ix_ConfigSection>::operator=(pIFSec);
        }
    }

    //! 赋值操作符函数
    Cx_ConfigSection& operator=(const Cx_Interface<Ix_ConfigSection>& src)
    {
        if (&src != this)
        {
            Cx_Interface<Ix_ConfigSection>::operator=(src);
        }
        return *this;
    }

    //! 析构函数
    virtual ~Cx_ConfigSection()
    {
        Release();
    }

    //! 得到一个子数据节点
    /*!
        \param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
        \param autoCreate 不存在时是否自动添加
        \return 新的数据节点，不存在则自动添加
    */
    Cx_ConfigSection GetSection(
        const wchar_t* name, bool autoCreate = true) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSection(P(), name, L"", L"", autoCreate);
    }

    //! 得到带整数标识属性参数的一个数据节点
    /*!
        \param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
        \param attrName 标识一个子数据节点的属性名称
        \param attrValue 该标识项对应的属性值
        \param autoCreate 不存在时是否自动添加
        \return 新的数据节点，不存在则自动添加
    */
    Cx_ConfigSection GetSection(const wchar_t* name,
        const wchar_t* attrName, ULONG attrValue, bool autoCreate = true) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSection(P(), name, attrName, attrValue, autoCreate);
    }

    //! 得到带属性参数的一个数据节点
    /*!
        \param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
        \param attrName 标识一个子数据节点的属性名称
        \param attrValue 该标识项对应的属性值
        \param autoCreate 不存在时是否自动添加
        \return 新的数据节点，不存在则自动添加
    */
    Cx_ConfigSection GetSection(const wchar_t* name,
        const wchar_t* attrName, const wchar_t* attrValue,
        bool autoCreate = true) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSection(P(), name, attrName, attrValue, autoCreate);
    }

    //! 得到带属性参数的一个数据节点
    /*!
        \param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
        \param attrName 标识一个子数据节点的第一个属性名称
        \param attrValue 该标识项对应的属性值
        \param attrName2 标识一个子数据节点的第二个属性名称
        \param attrValue2 该标识项对应的attrName2的属性值
        \param autoCreate 不存在时是否自动添加
        \return 新的数据节点，不存在则自动添加
    */
    Cx_ConfigSection GetSection(const wchar_t* name,
        const wchar_t* attrName, const wchar_t* attrValue,
        const wchar_t* attrName2, const wchar_t* attrValue2,
        bool autoCreate = true) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSection(P(), name, attrName, attrValue,
            attrName2, attrValue2, autoCreate);
    }

    //! 得到带整数标识属性参数的一个数据节点
    /*!
        \param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
        \param attrName 标识一个子数据节点的第一个属性名称
        \param attrValue 该标识项对应的属性值
        \param attrName2 标识一个子数据节点的第二个属性名称
        \param attrValue2 该标识项对应的attrName2的属性值
        \param autoCreate 不存在时是否自动添加
        \return 新的数据节点，不存在则自动添加
    */
    Cx_ConfigSection GetSection(const wchar_t* name,
        const wchar_t* attrName, ULONG attrValue,
        const wchar_t* attrName2, ULONG attrValue2,
        bool autoCreate = true)
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSection(P(), name, attrName, attrValue,
            attrName2, attrValue2, autoCreate);
    }

    //! 得到节点名对应的子节点个数
    /*!
        \param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
        \return 子数据节点的个数
        \see GetSectionByIndex
    */
    long GetSectionCount(const wchar_t* name) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSectionCount(P(), name);
    }

    //! 在节点名对应的子节点中得到指定序号的子数据节点
    /*!
        \param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
        \param index 要取的子数据节点的序号
        \return 新的数据节点，如果不存在则对该对象的读写操作将忽略，可以用 IsValid() 来检查是否为无效节点
        \see GetSectionCount
    */
    Cx_ConfigSection GetSectionByIndex(const wchar_t* name, long index) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSectionByIndex(P(), name, index);
    }

    //! 添加一个数据节点
    /*!
        \param name 数据节点名称，以正斜号或反斜号分隔多级相对路径
        \return 新的数据节点
    */
    Cx_ConfigSection AddSection(const wchar_t* name)
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->AddSection(P(), name);
    }

    //! 删除本数据节点的所有子节点
    /*!
        \param name 子节点数据节点名称，不能包含正斜号或反斜号
        \param attrName 子节点的标识属性名，可选值
        \param attrValue 标识属性名对应的值，attrName不为空时有效
        \return 删除的子节点个数
    */
    long RemoveChildren(const wchar_t* name, const wchar_t* attrName = L"", const wchar_t* attrValue = L"")
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->RemoveChildren(P(), name, attrName, attrValue);
    }

    //! 删除本数据节点的所有子节点
    /*!
        \param name 子节点数据节点名称，不能包含正斜号或反斜号
        \param attrName 子节点的标识属性名，不为空
        \param attrValue 标识属性名attrName对应的值
        \return 删除的子节点个数
    */
    long RemoveChildren(const wchar_t* name, const wchar_t* attrName, ULONG attrValue)
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->RemoveChildren(P(), name, attrName, attrValue);
    }

    //! 得到上一级节点
    /*! 如果本节点为根节点，则返回节点为无效节点(IsValid()==false)
        \return 上一级数据节点对象
    */
    Cx_ConfigSection GetParentSection()
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetParentSection(P());
    }
};

#endif // X3_XML_CONFIGIOSECTION_H_
