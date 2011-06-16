/*! \file Ix_Object.h
 *  \brief Define Ix_Object (the basic interface) and X3CLSID
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_CORE_IOBJECT_H_
#define X3_CORE_IOBJECT_H_

/*! \interface Ix_Object
 *  \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief The basic interface that all X3 class can support it.
 *  \note  DO NOT call it's function directly.\n You can use Cx_Interface or Cx_Ptr instead of using it.
 *  \see autoptr class: Cx_Ptr, Cx_Interface
 */
class Ix_Object
{
public:
    virtual ~Ix_Object() {}
    virtual void AddRef(HMODULE fromdll) = 0;
    virtual void Release(HMODULE fromdll) = 0;
    virtual const char* GetClassName() const = 0;
};

//! class unique id
/*! \ingroup _GROUP_PLUGIN_CORE_
    \code
    const X3CLSID CLSID_ExampleTool("97380b78-a3b4-4784-ba07-c928561988c8");
    \endcode
*/
class X3CLSID
{
public:
    X3CLSID()
    {
        m_clsid[0] = 0;
    }

    X3CLSID(const char* clsid)
    {
        strncpy_s(m_clsid, 40, clsid ? clsid : "", 40);
    }

    X3CLSID(const X3CLSID& src)
    {
        strncpy_s(m_clsid, 40, src.m_clsid, 40);
    }

    X3CLSID& operator=(const char* clsid)
    {
        strncpy_s(m_clsid, 40, clsid ? clsid : "", 40);
        return *this;
    }

    X3CLSID& operator=(const X3CLSID& src)
    {
        strncpy_s(m_clsid, 40, src.m_clsid, 40);
        return *this;
    }

    bool operator==(const X3CLSID& src) const
    {
        return strcmp(m_clsid, src.m_clsid) == 0;
    }

    bool operator!=(const X3CLSID& src) const
    {
        return strcmp(m_clsid, src.m_clsid) != 0;
    }

    bool operator>(const X3CLSID& src) const
    {
        return strcmp(m_clsid, src.m_clsid) > 0;
    }

    bool operator<(const X3CLSID& src) const
    {
        return strcmp(m_clsid, src.m_clsid) < 0;
    }

    const char* str() const
    {
        return m_clsid;
    }

    bool valid() const
    {
        return m_clsid[0] != 0;
    }

private:
    char m_clsid[40];
};

#define X3CLSID_DEFINE(clsid, str)  \
    namespace x3 { const X3CLSID clsid(str); }  \
    typedef int dumy_ ## clsid

#endif // X3_CORE_IOBJECT_H_
