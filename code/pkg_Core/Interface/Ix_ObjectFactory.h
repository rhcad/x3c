/*! \file Ix_ObjectFactory.h
 *  \brief Define object creator interface: Ix_ObjectFactory
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_CORE_IOBJECTFACTORY_H_
#define X3_CORE_IOBJECTFACTORY_H_

#include "Ix_Object.h"

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_ObjectFactory
 *  \brief Object creator interface
 *  \see   Ix_Object, Ix_Module
 */
class Ix_ObjectFactory : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_ObjectFactory)

    //! Check if the class is loaded.
    virtual bool IsCreatorRegister(const X3CLSID& clsid) = 0;

    //! Create an object with the class id.
    virtual int CreateObject(const X3CLSID& clsid, X3IID iid, Ix_Object** ppv, HMODULE fromdll) = 0;
};

#endif // X3_CORE_IOBJECTFACTORY_H_
