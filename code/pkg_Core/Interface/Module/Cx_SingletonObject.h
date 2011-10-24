/*! \file Cx_SingletonObject.h
 *  \brief Define single instance implement template class: Cx_SingletonObject<cls>
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_CX_SINGLETONOBJECT_H_
#define X3_CX_SINGLETONOBJECT_H_

#include "Ix_Object.h"
#include "XModuleItem.h"

HMODULE x3GetModuleHandle();

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief Single instance implement template class used by XDEFINE_CLASSMAP_ENTRY_Singleton.
 *  \brief The template parameter is a class which implement a interface.
 *  \internal
 *  \see   Cx_Object, XDEFINE_CLASSMAP_ENTRY_Singleton
 */
template <class ClsType>
class Cx_SingletonObject
    : public ClsType
    , public Cx_ModuleItem
{
protected:
    Cx_SingletonObject(bool bRef = true) : m_refcount(bRef ? 1 : 0)
    {
    }

    virtual ~Cx_SingletonObject()
    {
        if (Instance() == this)
        {
            Instance() = NULL;
        }
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
        return InterlockedDecrement(&m_refcount);
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
        if (NULL == Instance())
        {
            Cx_SingletonObject<ClsType>* p = new Cx_SingletonObject<ClsType>(false);

            if (1 == InterlockedIncrement(&Locker()))
            {
                Instance() = p;
                p->InterfaceAddRef(fromdll);
                p->AddModuleItem();
            }
            else
            {
                delete p;   // has created by another thread
            }
            InterlockedDecrement(&Locker());
        }

        Ix_Object* ret = NULL;
        Instance()->QueryObject(iid, &ret, fromdll);

        return ret;
    }

    static long GetObjectCount()
    {
        return (Instance() && Instance()->m_refcount > 0) ? 1 : 0;
    }

    static long GetRefCountByOthers()
    {
        return RefCountByOthers();
    }

private:
    Cx_SingletonObject(const Cx_SingletonObject&);
    void operator=(const Cx_SingletonObject&);

    long        m_refcount;

    static Cx_SingletonObject<ClsType>*& Instance()
    {
        static Cx_SingletonObject<ClsType>* s_obj = NULL;
        return s_obj;
    }

    static long& RefCountByOthers()
    {
        static long s_refcount = 0;
        return s_refcount;
    }

    static long& Locker()
    {
        static long s_locker = 0;
        return s_locker;
    }
};

#endif // X3_CX_SINGLETONOBJECT_H_
