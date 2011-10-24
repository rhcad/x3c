/*! \file Ix_GuidGenerator.h
 *  \brief Define GUID generator interface: Ix_GuidGenerator
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_UTIL_IGUIDGENERATOR_H_
#define X3_UTIL_IGUIDGENERATOR_H_

#include <XComPtr.h>

X3CLSID_DEFINE(CLSID_GuidGenerator, "8c14f0c5-7795-4ec3-b13a-982f653a700a");

//! GUID generator interface.
/*!
    \interface Ix_GuidGenerator
    \ingroup _GROUP_UTILITY_
    \see x3::CLSID_GuidGenerator
*/
class Ix_GuidGenerator : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_GuidGenerator)

    //! Get new GUID string.
    virtual std::wstring CreateGuid(bool withBrackets = false) = 0;

    //! Get GUID string without braces.
    virtual std::wstring RemoveGuidBrackets(const std::wstring& uid) = 0;

    //! Get string of current date and time as format "YYYY-MM-DD HH:MM:SS".
    virtual std::wstring GetCurrentTimeString(bool hasYear = true) = 0;

    //! Get new unique id (valid in current process).
    virtual ULONG CreateID(long type = 0) = 0;
};

namespace x3 {

//! Get new GUID string.
/*!
    \ingroup _GROUP_UTILITY_
    \see RemoveGuidBrackets, Ix_GuidGenerator
*/
inline std::wstring CreateGuid(bool withBrackets = false)
{
    Cx_Interface<Ix_GuidGenerator> pIFGenerator(x3::CLSID_GuidGenerator);
#ifdef ASSERT
    ASSERT(pIFGenerator.IsNotNull());
#endif
    return pIFGenerator->CreateGuid(withBrackets);
}

//! Get GUID string without braces.
/*!
    \ingroup _GROUP_UTILITY_
    \see CreateGuid, Ix_GuidGenerator
*/
inline std::wstring RemoveGuidBrackets(const std::wstring& uid)
{
    Cx_Interface<Ix_GuidGenerator> pIFGenerator(x3::CLSID_GuidGenerator);
#ifdef ASSERT
    ASSERT(pIFGenerator.IsNotNull());
#endif
    return pIFGenerator->RemoveGuidBrackets(uid);
}

//! Get new unique id (valid in current process).
/*!
    \ingroup _GROUP_UTILITY_
    \see Ix_GuidGenerator
*/
inline ULONG GuidCreateID(long type = 0)
{
    Cx_Interface<Ix_GuidGenerator> pIFGenerator(x3::CLSID_GuidGenerator);
#ifdef ASSERT
    ASSERT(pIFGenerator.IsNotNull());
#endif
    return pIFGenerator->CreateID(type);
}

//! Get string of current date and time as format "YYYY-MM-DD HH:MM:SS".
/*!
    \ingroup _GROUP_UTILITY_
*/
inline std::wstring GetCurrentTimeString(bool hasYear = true)
{
    Cx_Interface<Ix_GuidGenerator> pIFGenerator(x3::CLSID_GuidGenerator);
#ifdef ASSERT
    ASSERT(pIFGenerator.IsNotNull());
#endif
    return pIFGenerator->GetCurrentTimeString(hasYear);
}

} // x3

#endif // X3_UTIL_IGUIDGENERATOR_H_
