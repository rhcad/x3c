/*! \file   XClassItem.h
 *  \brief  Internal used definitions of class factory.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_CLASSITEM_H_
#define X3_PLUGINIMPL_CLASSITEM_H_

#include "Ix_Object.h"

//! class factory function.
typedef Ix_Object* (*PFNXObjectCreator)(HMODULE);

//! object count of a class.
typedef long (*PFNXGetObjectCount)();

//! object (used by other modules) count of a class.
typedef long (*PFNXRefCountByOthers)();

#define MIN_SINGLETON_TYPE  10

#pragma pack(push, 8)

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief class factory registry.
 *  \see   x3GetClassEntryTable, XBEGIN_DEFINE_MODULE
 *  \internal
 */
struct X3CLASSENTRY
{
    BYTE                type;               //!< see MIN_SINGLETON_TYPE and XModuleMacro.h
    const char*         className;          //!< implement class name
    X3CLSID             clsid;              //!< class id. may be empty if iidSpecial is valid.
    const char*         iidSpecial;         //!< special interface name, see XDEFINE_SPECIAL_INTERFACE_ENTRY_Singleton.
    PFNXObjectCreator   pfnObjectCreator;   //!< class factory function
    PFNXGetObjectCount  pfnGetObjectCount;  //!< object count of this class
    PFNXRefCountByOthers    pfnRefCountByOthers;    //!< count of objects used by other modules

    //! Used by XDEFINE_CLASSMAP_ENTRY, XDEFINE_CLASSMAP_ENTRY_Singleton
    X3CLASSENTRY(BYTE      _type,
        const char*             _className,
        const X3CLSID&          _clsid,
        const char*             _iidSpecial,
        PFNXObjectCreator       _pfnObjectCreator,
        PFNXGetObjectCount      _pfnGetObjectCount = NULL,
        PFNXRefCountByOthers    _pfnRefCountByOthers = NULL)

        : type(_type), className(_className)
        , clsid(_clsid), iidSpecial(_iidSpecial)
        , pfnObjectCreator(_pfnObjectCreator)
        , pfnGetObjectCount(_pfnGetObjectCount)
        , pfnRefCountByOthers(_pfnRefCountByOthers)
    {
    }

    //! Used by XEND_DEFINE_MODULE
    X3CLASSENTRY()
        : type(0), className(""), clsid(""), iidSpecial("")
        , pfnObjectCreator(NULL), pfnGetObjectCount(NULL)
        , pfnRefCountByOthers(NULL)
    {
    }

    //! class factory registries. filled by XBEGIN_DEFINE_MODULE.
    static const X3CLASSENTRY s_classes[];
};

#pragma pack(pop)
#endif // X3_PLUGINIMPL_CLASSITEM_H_
