/*! \file Cx_SingletonObject.h
 *  \brief Define single instance implement template class: Cx_SingletonObject<cls>
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_CX_SINGLETONOBJECT_H_
#define X3_CX_SINGLETONOBJECT_H_

#include "Ix_Object.h"
#include "XModuleItem.h"
#include <typeinfo>

HMODULE xGetModuleHandle();

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief Single instance implement template class used by XDEFINE_CLASSMAP_ENTRY_Singleton.
 *  \brief The template parameter is a class which implement a interface.
 *  \internal
 *  \see   Cx_Object \n
 *         XDEFINE_CLASSMAP_ENTRY_Singleton \n
 *         XDEFINE_SPECIAL_INTERFACE_ENTRY_Singleton
 */
template <class ClsType>
class Cx_SingletonObject
    : public ClsType
    , public Ix_Object
    , public CModuleItem
{
protected:
    Cx_SingletonObject(bool bRef = true) : m_lRefCount(bRef ? 1 : 0)
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
    virtual void AddRef(HMODULE fromdll)
    {
        if (fromdll != xGetModuleHandle())
        {
            InterlockedIncrement(&RefCountByOthers());
        }
        InterlockedIncrement(&m_lRefCount);
    }

    virtual void Release(HMODULE fromdll)
    {
        if (fromdll != xGetModuleHandle())
        {
            InterlockedDecrement(&RefCountByOthers());
        }
        InterlockedDecrement(&m_lRefCount);
    }

    virtual const char* GetClassName() const
    {
        return typeid(*this).name();
    }

public:
    static Ix_Object* STDMETHODCALLTYPE CreateObject(HMODULE fromdll)
    {
        if (NULL == Instance())
        {
            Cx_SingletonObject<ClsType>* p = new Cx_SingletonObject<ClsType>(false);

#ifdef InterlockedCompareExchangePointer
            if (InterlockedCompareExchangePointer(
                (PVOID volatile *)(&Instance()), p, NULL) == NULL)
#else
            if (InterlockedCompareExchange((void**)(&Instance()), p, NULL) == NULL)
#endif
            {
                p->AddRef(fromdll);
                p->AddModuleItem();
            }
            else
            {
                delete p;   // has created by another thread
            }
        }

        return Instance();
    }

    static long STDMETHODCALLTYPE GetObjectCount()
    {
        return (Instance() && Instance()->m_lRefCount > 0) ? 1 : 0;
    }

    static long STDMETHODCALLTYPE GetRefCountByOthers()
    {
        return RefCountByOthers();
    }

private:
    long        m_lRefCount;

    static Cx_SingletonObject<ClsType>*& Instance()
    {
        static Cx_SingletonObject<ClsType>* s_pSingleton = NULL;
        return s_pSingleton;
    }

    static long& RefCountByOthers()
    {
        static long s_lRefCount = 0;
        return s_lRefCount;
    }
};

#endif // X3_CX_SINGLETONOBJECT_H_
