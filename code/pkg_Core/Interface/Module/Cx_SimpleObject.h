/*! \file Cx_SimpleObject.h
 *  \brief Define a implement template class (Cx_SimpleObject) that can instantiate directly.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */ //
#ifndef X3_PLUGINIMPL_SIMPLEOBJECT_H_
#define X3_PLUGINIMPL_SIMPLEOBJECT_H_

#include "Cx_Object.h"
#include "XComPtr.h"

//! A implement template class that can instantiate directly.
/*! Example: \code
    Cx_Ptr MyFunc()
    {
        Cx_Ptr objRet;
        Cx_SimpleObject<Cx_MyInternal>* p = Cx_SimpleObject<Cx_MyInternal>::Create(objRet);

        p->Init();

        return objRet;
    }
    \endcode
    The implement class must be registered in X3BEGIN_MODULE group. eg:
    \code
    X3BEGIN_MODULE()
        X3_CLASS_ENTRY(X3CLSID(), Cx_MyInternal)
    X3END_MODULE()
    \endcode
    \ingroup _GROUP_PLUGIN_CORE2_
*/
template <class ClsType>
class Cx_SimpleObject : public Cx_Object<ClsType>
{
public:
    //! Create a object owned by Cx_Ptr.
    static Cx_SimpleObject<ClsType>* Create(Cx_Ptr& objOwner)
    {
        Cx_SimpleObject<ClsType>* p = new Cx_SimpleObject<ClsType>();
        objOwner.AttachInterface(p);
        return p;
    }

    //! Create a object owned by Cx_Interface.
    template <class IF_Type>
    static Cx_SimpleObject<ClsType>* Create(Cx_Interface<IF_Type>& pIFOwner)
    {
        Cx_SimpleObject<ClsType>* p = new Cx_SimpleObject<ClsType>();
        return pIFOwner.AttachInterface(static_cast<Ix_Object*>(p)) ? p : NULL;
    }

private:
    Cx_SimpleObject() {}
    Cx_SimpleObject(const Cx_SimpleObject&);
    void operator=(const Cx_SimpleObject&);
};

#endif // X3_PLUGINIMPL_SIMPLEOBJECT_H_
