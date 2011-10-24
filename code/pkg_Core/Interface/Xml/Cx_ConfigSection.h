/*! \file Cx_ConfigSection.h
 *  \brief the configure data node class: Cx_ConfigSection
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_XML_CONFIGIOSECTION_H_
#define X3_XML_CONFIGIOSECTION_H_

#include "Ix_ConfigData.h"

//! The configure data node wrapper class.
/*! This class object is represented as a data node in hierarchical structure nodes.\n
    Ix_ConfigData object is represented as all nodes.
    \ingroup _GROUP_PLUGIN_XML_
*/
class Cx_ConfigSection : public Cx_Interface<Ix_ConfigSection>
{
public:
    Cx_ConfigSection(Ix_Object* pInterface = NULL)
        : Cx_Interface<Ix_ConfigSection>(pInterface)
    {
    }

    explicit Cx_ConfigSection(Ix_ConfigSection* p)
        : Cx_Interface<Ix_ConfigSection>(p)
    {
    }

    explicit Cx_ConfigSection(const Cx_Interface<Ix_ConfigSection>& src)
        : Cx_Interface<Ix_ConfigSection>(src.P())
    {
    }

    explicit Cx_ConfigSection(const Cx_ConfigSection& src)
        : Cx_Interface<Ix_ConfigSection>(src.P())
    {
    }

    explicit Cx_ConfigSection(const Cx_Ptr& objConfigIO)
        : Cx_Interface<Ix_ConfigSection>(objConfigIO)
    {
    }

    Cx_ConfigSection& operator=(const Cx_Interface<Ix_ConfigSection>& src)
    {
        Cx_Interface<Ix_ConfigSection>::operator=(src);
        return *this;
    }

    Cx_ConfigSection& operator=(const Cx_Ptr& src)
    {
        Cx_Interface<Ix_ConfigSection>::operator=(src);
        return *this;
    }

    ~Cx_ConfigSection()
    {
        Release();
    }

    //! Returns a child node by node name.
    /*!
        \return the child node (Cx_ConfigSection). The node will be created when not exist and autoCreate is true.
        \param name the child node name. the name may contains slash chars for multiple levels.
        \param autoCreate true if enable to auto create new node.
    */
    Cx_Ptr GetSection(
        const wchar_t* name, bool autoCreate = true) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSection(P(), name, L"", L"", autoCreate);
    }

    //! Returns a child node by node name and integer property value.
    /*!
        \return the child node (Cx_ConfigSection). The node will be created when not exist and autoCreate is true.
        \param name the child node name. the name may contains slash chars for multiple levels.
        \param attrName a field name of the child node.
        \param attrValue the field value of the child node.
        \param autoCreate true if enable to auto create new node.
    */
    Cx_Ptr GetSection(const wchar_t* name,
        const wchar_t* attrName, ULONG attrValue, bool autoCreate = true) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSection(P(), name, attrName, attrValue, autoCreate);
    }

    //! Returns a child node by node name and string property value.
    /*!
        \return the child node (Cx_ConfigSection). The node will be created when not exist and autoCreate is true.
        \param name the child node name. the name may contains slash chars for multiple levels.
        \param attrName a field name of the child node.
        \param attrValue the field value of the child node.
        \param autoCreate true if enable to auto create new node.
    */
    Cx_Ptr GetSection(const wchar_t* name,
        const wchar_t* attrName, const wchar_t* attrValue,
        bool autoCreate = true) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSection(P(), name, attrName, attrValue, autoCreate);
    }

    //! Returns a child node by node name and string property value.
    /*!
        \return the child node (Cx_ConfigSection). The node will be created when not exist and autoCreate is true.
        \param name the child node name. the name may contains slash chars for multiple levels.
        \param attrName a field name of the child node.
        \param attrValue the field value of the child node.
        \param attrName2 another field name of the child node.
        \param attrValue2 the field value of attrName2.
        \param autoCreate true if enable to auto create new node.
    */
    Cx_Ptr GetSection(const wchar_t* name,
        const wchar_t* attrName, const wchar_t* attrValue,
        const wchar_t* attrName2, const wchar_t* attrValue2,
        bool autoCreate = true) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSection(P(), name, attrName, attrValue,
            attrName2, attrValue2, autoCreate);
    }

    //! Returns a child node by node name and integer property value.
    /*!
        \return the child node (Cx_ConfigSection). The node will be created when not exist and autoCreate is true.
        \param name the child node name. the name may contains slash chars for multiple levels.
        \param attrName a field name of the child node.
        \param attrValue the field value of the child node.
        \param attrName2 another field name of the child node.
        \param attrValue2 the field value of attrName2.
        \param autoCreate true if enable to auto create new node.
    */
    Cx_Ptr GetSection(const wchar_t* name,
        const wchar_t* attrName, ULONG attrValue,
        const wchar_t* attrName2, ULONG attrValue2,
        bool autoCreate = true)
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSection(P(), name, attrName, attrValue,
            attrName2, attrValue2, autoCreate);
    }

    //! Returns the child count by child node name.
    /*!
        \param name the child node name. the name may contains slash chars for multiple levels.
        \return the child count.
        \see GetSectionByIndex
    */
    long GetSectionCount(const wchar_t* name) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSectionCount(P(), name);
    }

    //! Returns the child node of the specified order.
    /*!
        \return the child node (Cx_ConfigSection) even not exist actually.\n
             I/O operations will be ignored when the internal object is not exist.\n
        \param name the child node name. the name may contains slash chars for multiple levels.
        \param index the child index (0 to GetSectionCount()).
        \see GetSectionCount, Ix_ConfigSection::IsValid().
    */
    Cx_Ptr GetSectionByIndex(const wchar_t* name, long index) const
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetSectionByIndex(P(), name, index);
    }

    //! Add a child node.
    /*!
        \return the new node (Cx_ConfigSection).
        \param name the child node name. the name may contains slash chars for multiple levels.
    */
    Cx_Ptr AddSection(const wchar_t* name)
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->AddSection(P(), name);
    }

    //! Removes all child nodes.
    /*!
        \param name the child node name that can not contains slash chars.
        \param attrName the optional field name of the child node.
        \param attrValue the field value valid if attrName is not empty.
        \return the count of nodes removed.
    */
    long RemoveChildren(const wchar_t* name, const wchar_t* attrName = L"", const wchar_t* attrValue = L"")
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->RemoveChildren(P(), name, attrName, attrValue);
    }

    //! Removes all child nodes.
    /*!
        \param name the child node name that can not contains slash chars.
        \param attrName the field name of the child node, not empty.
        \param attrValue the field value of attrName.
        \return the count of nodes removed.
    */
    long RemoveChildren(const wchar_t* name, const wchar_t* attrName, ULONG attrValue)
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->RemoveChildren(P(), name, attrName, attrValue);
    }

    //! Returns the parent node.
    /*!
        \return the parent node. The result node will be invalid
            (Ix_ConfigSection::IsValid()==false) if sec is root node.
    */
    Cx_Ptr GetParentSection()
    {
        Ix_ConfigData* pIFData = P()->GetData();
        return pIFData->GetParentSection(P());
    }
};

#endif // X3_XML_CONFIGIOSECTION_H_
