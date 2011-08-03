/*! \file XComPtr.h
 *  \brief Define autoptr class: Cx_Interface, Cx_Ptr
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_CORE_XCOMPTR_H_
#define X3_CORE_XCOMPTR_H_

#include "Ix_Object.h"

// Create an object with the class id.
// It is implemented in XModuleImpl.h or XComCreator.h
int x3CreateObject(const X3CLSID& clsid, X3IID iid, Ix_Object** ppv);

// Return the current module handle for making a distinction between plugins.
// It is implemented in XModuleImpl.h or XComCreator.h
HMODULE x3GetModuleHandle();

class Cx_Ptr;

//! An autoptr class with a specified interface.
/*! x3CreateObject() is implemented in XModuleImpl.h or XComCreator.h.
    \ingroup _GROUP_PLUGIN_CORE_
    \see Cx_Ptr, x3CreateObject
*/
template <class IF_Type>
class Cx_Interface
{
    typedef Cx_Interface<IF_Type> thisClass;
public:
    Cx_Interface(Ix_Object* pInterface = NULL)
        : m_pInterface(copyi(pInterface))
    {
    }

    explicit Cx_Interface(IF_Type* pInterface, bool addref = true)
        : m_pInterface(copyi(pInterface, addref))
    {
    }

    template <class IF_Type2>
    explicit Cx_Interface(const Cx_Interface<IF_Type2>& pIF)
        : m_pInterface(copyi(pIF.P()))
    {
    }

    explicit Cx_Interface(const Cx_Ptr& src);

    explicit Cx_Interface(const X3CLSID& clsid) : m_pInterface(NULL)
    {
        x3CreateObject(clsid, IF_Type::GetIID(), (Ix_Object**)&m_pInterface);
    }

    ~Cx_Interface()
    {
        Unload();
    }


    inline IF_Type* P() const
    {
        return m_pInterface;
    }

    inline IF_Type* operator->() const
    {
        return m_pInterface;
    }

    template <class IF_Type2>
    thisClass& operator=(IF_Type2* pInterface)
    {
        Unload();

        if (pInterface)
        {
            pInterface->QueryObject(IF_Type::GetIID(), (Ix_Object**)&m_pInterface, x3GetModuleHandle());
        }

        return *this;
    }

    template <class IF_Type2>
    thisClass& operator=(const Cx_Interface<IF_Type2>& pIF)
    {
        return operator=(pIF.P());
    }

    thisClass& operator=(const thisClass& src)
    {
        Load(src.m_pInterface);
        return *this;
    }

    thisClass& operator=(const Cx_Ptr& src);

    thisClass& operator=(const int)
    {
        //ASSERT(0 == nul);
        Unload();
        return *this;
    }

    bool operator==(const int) const
    {
        //ASSERT(0 == nul);
        return m_pInterface == NULL;
    }

    bool operator!=(const int) const
    {
        //ASSERT(0 == nul);
        return m_pInterface != NULL;
    }

    bool operator==(const IF_Type* pInterface) const
    {
        return m_pInterface == pInterface;
    }

    bool operator!=(const IF_Type* pInterface) const
    {
        return m_pInterface != pInterface;
    }

    bool operator==(const thisClass& src) const
    {
        return m_pInterface == src.m_pInterface;
    }

    bool operator!=(const thisClass& src) const
    {
        return m_pInterface != src.m_pInterface;
    }

    inline operator bool() const
    {
        return m_pInterface != NULL;
    }

    inline bool operator!() const
    {
        return NULL == m_pInterface;
    }

    inline bool IsNull() const
    {
        return NULL == m_pInterface;
    }

    inline bool IsNotNull() const
    {
        return m_pInterface != NULL;
    }


    long Release()
    {
        return Unload();
    }

    IF_Type* DetachInterface()
    {
        IF_Type* pIF = m_pInterface;
        m_pInterface = NULL;
        return pIF;
    }

    bool AttachInterface(IF_Type* pIF)
    {
        Unload();
        m_pInterface = pIF;
        return true;
    }

    bool AttachInterface(Ix_Object* pIF)
    {
        Unload();

        if (pIF)
        {
            if (!pIF->QueryObject(IF_Type::GetIID(), (Ix_Object**)&m_pInterface, x3GetModuleHandle()))
            {
                pIF->InterfaceRelease(x3GetModuleHandle());
                return false;
            }
        }

        return true;
    }

    bool Create(const X3CLSID& clsid)
    {
        Unload();
        return 0 == x3CreateObject(clsid, IF_Type::GetIID(), (Ix_Object**)&m_pInterface);
    }

private:
    long Unload()
    {
        long refcount = -1;

        if (m_pInterface)
        {
            refcount = m_pInterface->InterfaceRelease(x3GetModuleHandle());
            m_pInterface = NULL;
#ifdef ASSERT
            ASSERT(refcount >= 0);
#endif
        }

        return refcount;
    }

    void Load(IF_Type* pIF)
    {
        if (m_pInterface != pIF)
        {
            if (pIF)
            {
                pIF->InterfaceAddRef(x3GetModuleHandle());
            }
            if (m_pInterface)
            {
                m_pInterface->InterfaceRelease(x3GetModuleHandle());
            }
            m_pInterface = pIF;
        }
    }

    static IF_Type* copyi(IF_Type* p, bool addref = true)
    {
        if (p && addref)
        {
            p->InterfaceAddRef(x3GetModuleHandle());
        }
        return p;
    }

    static IF_Type* copyi(Ix_Object* p)
    {
        IF_Type* ret = NULL;
        if (p)
        {
            p->QueryObject(IF_Type::GetIID(), (Ix_Object**)&ret, x3GetModuleHandle());
        }
        return ret;
    }

private:
    IF_Type*    m_pInterface;
};

//! An autoptr class with the Ix_Object interface.
/*! x3CreateObject() is implemented in XModuleImpl.h or XComCreator.h.
    \ingroup _GROUP_PLUGIN_CORE_
    \see Ix_Object, Cx_Interface, x3CreateObject
*/
class Cx_Ptr
{
public:
    Cx_Ptr(Ix_Object* pInterface = NULL) : m_pInterface(copyi(pInterface))
    {
    }

    Cx_Ptr(const Cx_Ptr& src) : m_pInterface(copyi(src.m_pInterface))
    {
    }

    template <class IF_Type>
    explicit Cx_Ptr(const Cx_Interface<IF_Type>& pIF) : m_pInterface(copyi(pIF.P()))
    {
    }

    explicit Cx_Ptr(const X3CLSID& clsid, X3IID iid) : m_pInterface(NULL)
    {
        x3CreateObject(clsid, iid, &m_pInterface);
    }

    ~Cx_Ptr()
    {
        Unload();
    }


    Ix_Object* P() const
    {
        return m_pInterface;
    }

    Cx_Ptr& operator=(const Cx_Ptr& src)
    {
        if (this != &src)
        {
            Load(src.m_pInterface);
        }

        return *this;
    }

    Cx_Ptr& operator=(Ix_Object* pInterface)
    {
        Load(pInterface);
        return *this;
    }

    template <class IF_Type>
    Cx_Ptr& operator=(const Cx_Interface<IF_Type>& pIF)
    {
        Load(pIF.P());
        return *this;
    }

    Cx_Ptr& operator=(const int)
    {
        //ASSERT(0 == nul);
        Unload();
        return *this;
    }

    bool operator==(const int) const
    {
        //ASSERT(0 == nul);
        return m_pInterface == NULL;
    }

    bool operator!=(const int) const
    {
        //ASSERT(0 == nul);
        return m_pInterface != NULL;
    }

    bool operator==(const Ix_Object* pInterface) const
    {
        return m_pInterface == pInterface;
    }

    bool operator!=(const Ix_Object* pInterface) const
    {
        return m_pInterface != pInterface;
    }

    bool operator==(const Cx_Ptr& src) const
    {
        return m_pInterface == src.m_pInterface;
    }

    bool operator!=(const Cx_Ptr& src) const
    {
        return m_pInterface != src.m_pInterface;
    }

    inline operator bool() const
    {
        return m_pInterface != NULL;
    }

    inline bool operator!() const
    {
        return NULL == m_pInterface;
    }

    inline bool IsNull() const
    {
        return NULL == m_pInterface;
    }

    inline bool IsNotNull() const
    {
        return m_pInterface != NULL;
    }


    long Release()
    {
        return Unload();
    }

    Ix_Object* DetachInterface()
    {
        Ix_Object* pIF = m_pInterface;
        m_pInterface = NULL;
        return pIF;
    }

    void AttachInterface(Ix_Object* pIF)
    {
        Unload();
        m_pInterface = pIF;
    }

    bool Create(const X3CLSID& clsid, X3IID iid)
    {
        Unload();
        return 0 == x3CreateObject(clsid, iid, &m_pInterface);
    }

private:
    long Unload()
    {
        long refcount = -1;

        if (m_pInterface)
        {
            refcount = m_pInterface->InterfaceRelease(x3GetModuleHandle());
            m_pInterface = NULL;
#ifdef ASSERT
            ASSERT(refcount >= 0);
#endif
        }

        return refcount;
    }

    void Load(Ix_Object* pIF)
    {
        if (m_pInterface != pIF)
        {
            if (pIF)
            {
                pIF->InterfaceAddRef(x3GetModuleHandle());
            }
            if (m_pInterface)
            {
                m_pInterface->InterfaceRelease(x3GetModuleHandle());
            }
            m_pInterface = pIF;
        }
    }

    static Ix_Object* copyi(Ix_Object* p)
    {
        if (p)
        {
            p->InterfaceAddRef(x3GetModuleHandle());
        }
        return p;
    }

private:
    Ix_Object*  m_pInterface;
};

// Inlines for Cx_Interface
//
template <class IF_Type> inline
Cx_Interface<IF_Type>::Cx_Interface(const Cx_Ptr& src) : m_pInterface(NULL)
{
    if (src.P())
    {
        src.P()->QueryObject(IF_Type::GetIID(), (Ix_Object**)&m_pInterface, x3GetModuleHandle());
    }
}

template <class IF_Type> inline
Cx_Interface<IF_Type>& Cx_Interface<IF_Type>::operator=(const Cx_Ptr& src)
{
    Unload();

    if (src.P())
    {
        src.P()->QueryObject(IF_Type::GetIID(), (Ix_Object**)&m_pInterface, x3GetModuleHandle());
    }

    return *this;
}

#endif // X3_CORE_XCOMPTR_H_