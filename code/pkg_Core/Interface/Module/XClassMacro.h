/*! \file   XClassMacro.h
 *  \brief  Define macros of class definition in plugin, such as X3BEGIN_CLASS_DECLARE.
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_PLUGINIMPL_CLASSMACRO_H_
#define X3_PLUGINIMPL_CLASSMACRO_H_

// X3BEGIN_CLASS_DECLARE(cls)
//     X3DEFINE_INTERFACE_ENTRY(_Interface)
//     X3USE_INTERFACE_ENTRY(_BaseClass)
// X3END_CLASS_DECLARE()

#include "Ix_Object.h"

//! Begin definition group of how many interfaces supported by the class.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \param cls class name.
    \see X3END_CLASS_DECLARE, X3DEFINE_INTERFACE_ENTRY, X3USE_INTERFACE_ENTRY
    \code
    class Cx_Example : public Cx_Base, public Ix_Example
    {
        X3BEGIN_CLASS_DECLARE(Cx_Example)
            X3DEFINE_INTERFACE_ENTRY(Ix_Example)
            X3USE_INTERFACE_ENTRY(Cx_Base)
        X3END_CLASS_DECLARE()
    protected:
        Cx_Example();
        virtual ~Cx_Example();
    private:
        virtual void foo();
    };
    \endcode
*/
#define X3BEGIN_CLASS_DECLARE(cls)  \
public: \
    const char* DoGetClassName() const { return #cls; }    \
    static bool DoQueryInterface(cls* self, X3IID iid, Ix_Object** ppv, HMODULE fromdll)  \
    {

//! Indicate a interface is supported by the class.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \param _Interface interface name.
    \see X3BEGIN_CLASS_DECLARE, X3USE_INTERFACE_ENTRY
*/
#define X3DEFINE_INTERFACE_ENTRY(_Interface)    \
        if (iid == _Interface::GetIID())        \
        {   \
            *ppv = static_cast<Ix_Object*>(static_cast<_Interface*>(self)); \
            (*ppv)->InterfaceAddRef(fromdll);            \
            return true;    \
        }

//! Indicate this class is derived from a implement class.
/*! All interfaces of the base class are supported by this class.
    \ingroup _GROUP_PLUGIN_CORE_
    \param _BaseClass base class that has the group declared using X3BEGIN_CLASS_DECLARE.
    \see X3BEGIN_CLASS_DECLARE, X3DEFINE_INTERFACE_ENTRY
*/
#define X3USE_INTERFACE_ENTRY(_BaseClass)       \
        if (_BaseClass::DoQueryInterface(self, iid, ppv, fromdll))  \
        {   \
            return true;    \
        }

//! End group of class definition.
/*!
    \see X3BEGIN_CLASS_DECLARE, X3DEFINE_INTERFACE_ENTRY
*/
#define X3END_CLASS_DECLARE() \
        return false; \
    }

#endif // X3_PLUGINIMPL_CLASSMACRO_H_
