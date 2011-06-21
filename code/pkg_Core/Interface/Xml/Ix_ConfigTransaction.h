/*! \file Ix_ConfigTransaction.h
 *  \brief Define configure transaction helper class: Cx_ConfigTransaction
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_XML_CONFIGTRANSACTION_H_
#define X3_XML_CONFIGTRANSACTION_H_

#include <XComPtr.h>

//! Configure transaction interface.
/*! Ix_ConfigSection and Ix_ConfigData can be casted to this interface.
    \see Cx_ConfigTransaction
    \see Ix_ConfigSection, Ix_ConfigData
*/
class Ix_ConfigTransaction
{
public:
    virtual ~Ix_ConfigTransaction() {}

    //! Begin to change configure data.
    virtual void BeginTransaction() = 0;

    //! End to change configure data.
    /*! The configure data will be saved when transaction counter becomes to zero.
        \return false if error occurred, otherwise returns true.
    */
    virtual bool EndTransaction() = 0;

    //! Return the total count of configure data changes.
    virtual ULONG GetModifiedCount() = 0;
};

//! Configure transaction helper class.
/*! Use this class to declare local variable in functions,
    so EndTransaction() will be automatic called to save configure data.
    \ingroup _GROUP_PLUGIN_XML_
    \see Ix_ConfigSection, Ix_ConfigData
*/
class Cx_ConfigTransaction
{
public:
    //! Begin to change configure data.
    Cx_ConfigTransaction(const Cx_Ptr& obj) : m_trans(obj)
    {
        if (m_trans)
        {
            m_trans->BeginTransaction();
        }
    }

#ifdef X3_XML_ICONFIGDATA_H_
    //! Begin to change configure data.
    Cx_ConfigTransaction(const Cx_Interface<Ix_ConfigData>& p) : m_trans(p)
    {
        if (m_trans)
        {
            m_trans->BeginTransaction();
        }
    }
#endif

    //! End to change configure data.
    ~Cx_ConfigTransaction()
    {
        Submit();
    }

    //! End to change configure data.
    bool Submit()
    {
        bool ret = false;

        if (m_trans)
        {
            ret = m_trans->EndTransaction();
            m_trans.Release();
        }

        return ret;
    }

private:
    Cx_Interface<Ix_ConfigTransaction>  m_trans;
};

#endif // X3_XML_CONFIGTRANSACTION_H_
