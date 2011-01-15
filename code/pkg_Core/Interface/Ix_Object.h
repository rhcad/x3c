/*! \file Ix_Object.h
 *  \brief Define Ix_Object (the basic interface) and XCLSID
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_CORE_IOBJECT_H_
#define X3_CORE_IOBJECT_H_

//! \cond IGNORED
#ifndef interface
#include <objbase.h>
#endif
//! \endcond

/*! \interface Ix_Object
 *  \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief The basic interface that all X3 class can support it.
 *  \note  DO NOT call it's function directly.\n You can use Cx_Interface or Cx_Ptr instead of using it.
 *  \see autoptr class: Cx_Ptr, Cx_Interface
 */
interface Ix_Object
{
    virtual void AddRef(HMODULE fromdll) = 0;
    virtual void Release(HMODULE fromdll) = 0;
    virtual const char* GetClassName() const = 0;
};

//! class unique id
/*! \ingroup _GROUP_PLUGIN_CORE_
    \code
    const XCLSID CLSID_ExampleTool("97380b78-a3b4-4784-ba07-c928561988c8");
    \endcode
*/
class XCLSID
{
public:
    XCLSID()
    {
        m_clsid[0] = 0;
    }

    XCLSID(const char* clsid)
    {
        lstrcpynA(m_clsid, clsid ? clsid : "", 40);
    }

    XCLSID(const XCLSID& src)
    {
        lstrcpyA(m_clsid, src.m_clsid);
    }

    XCLSID& operator=(const char* clsid)
    {
        lstrcpynA(m_clsid, clsid ? clsid : "", 40);
        return *this;
    }

    XCLSID& operator=(const XCLSID& src)
    {
        lstrcpyA(m_clsid, src.m_clsid);
        return *this;
    }

    bool operator==(const XCLSID& src) const
    {
        return lstrcmpA(m_clsid, src.m_clsid) == 0;
    }

    bool operator!=(const XCLSID& src) const
    {
        return lstrcmpA(m_clsid, src.m_clsid) != 0;
    }

    bool operator>(const XCLSID& src) const
    {
        return lstrcmpA(m_clsid, src.m_clsid) > 0;
    }

    bool operator<(const XCLSID& src) const
    {
        return lstrcmpA(m_clsid, src.m_clsid) < 0;
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

#endif // X3_CORE_IOBJECT_H_
