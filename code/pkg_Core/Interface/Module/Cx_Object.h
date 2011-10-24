/*! \file Cx_Object.h
 *  \brief Define the regular implement template class: Cx_Object<cls>
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_PLUGINIMPL_OBJECT_H_
#define X3_PLUGINIMPL_OBJECT_H_

#include "Ix_Object.h"

HMODULE x3GetModuleHandle();

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief The regular implement template class used by XDEFINE_CLASSMAP_ENTRY.
 *  \note  The template parameter is a class which implement a interface.
 *  \see   Cx_SingletonObject, XDEFINE_CLASSMAP_ENTRY
 *  \internal
 */
template <class ClsType>
class Cx_Object : public ClsType
{
protected:
    Cx_Object() : m_refcount(1)
    {
        InterlockedIncrement(&ObjectCount());
    }

    virtual ~Cx_Object()
    {
        InterlockedDecrement(&ObjectCount());
    }

protected:
    virtual long InterfaceAddRef(HMODULE fromdll)
    {
        if (fromdll != x3GetModuleHandle())
        {
            InterlockedIncrement(&RefCountByOthers());
        }
        return InterlockedIncrement(&m_refcount);
    }

    virtual long InterfaceRelease(HMODULE fromdll)
    {
        if (fromdll != x3GetModuleHandle())
        {
            InterlockedDecrement(&RefCountByOthers());
        }

        long ret = InterlockedDecrement(&m_refcount);

        if (0 == ret)
        {
            delete this;
        }

        return ret;
    }

    virtual bool QueryObject(X3IID iid, Ix_Object** ppv, HMODULE fromdll)
    {
        return ClsType::DoQueryInterface(this, iid, ppv, fromdll);
    }

    virtual const char* GetClassName() const
    {
        return ClsType::DoGetClassName();
    }

public:
    static Ix_Object* CreateObject(X3IID iid, HMODULE fromdll)
    {
        Ix_Object* ret = NULL;
        Cx_Object<ClsType>* p = new Cx_Object<ClsType>();

        p->QueryObject(iid, &ret, fromdll);
        p->InterfaceRelease(fromdll);

        return ret;
    }

    static long GetObjectCount()
    {
        return ObjectCount();
    }

    static long GetRefCountByOthers()
    {
        return RefCountByOthers();
    }

private:
    Cx_Object(const Cx_Object&);
    void operator=(const Cx_Object&);

    long        m_refcount;

    static long& ObjectCount()
    {
        static long s_objcount = 0;
        return s_objcount;
    }

    static long& RefCountByOthers()
    {
        static long s_refcount = 0;
        return s_refcount;
    }
};

#endif // X3_PLUGINIMPL_OBJECT_H_
