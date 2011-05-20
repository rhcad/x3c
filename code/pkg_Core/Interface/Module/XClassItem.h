/*! \file   XClassItem.h
 *  \brief  Internal used definitions of class factory.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_CLASSITEM_H_
#define X3_PLUGINIMPL_CLASSITEM_H_

#include "Ix_Object.h"

//! class factory function.
typedef Ix_Object* (STDCALL *PFNXObjectCreator)(HMODULE);

//! object count of a class.
typedef long (STDCALL *PFNXGetObjectCount)();

//! object (used by other modules) count of a class.
typedef long (STDCALL *PFNXRefCountByOthers)();

#define MIN_SINGLETON_TYPE  10

#pragma pack(push, 8)

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief class factory registry.
 *  \see   _xGetClassEntryTable, XBEGIN_DEFINE_MODULE
 *  \internal
 */
struct _XCLASSMETA_ENTRY
{
    BYTE                type;               //!< see MIN_SINGLETON_TYPE and XModuleMacro.h
    const char*         className;          //!< implement class name
    XCLSID              clsid;              //!< class id. may be empty if iidSpecial is valid.
    const char*         iidSpecial;         //!< special interface name, see XDEFINE_SPECIAL_INTERFACE_ENTRY_Singleton.
    PFNXObjectCreator   pfnObjectCreator;   //!< class factory function
    PFNXGetObjectCount  pfnGetObjectCount;  //!< object count of this class
    PFNXRefCountByOthers    pfnRefCountByOthers;    //!< count of objects used by other modules

    //! Used by XDEFINE_CLASSMAP_ENTRY, XDEFINE_CLASSMAP_ENTRY_Singleton
    _XCLASSMETA_ENTRY(BYTE      _type,
        const char*             _className,
        const XCLSID&           _clsid,
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
    _XCLASSMETA_ENTRY()
        : type(0), className(""), clsid(""), iidSpecial("")
        , pfnObjectCreator(NULL), pfnGetObjectCount(NULL)
        , pfnRefCountByOthers(NULL)
    {
    }

    //! class factory registries. filled by XBEGIN_DEFINE_MODULE.
    static const _XCLASSMETA_ENTRY s_classes[];
};

#pragma pack(pop)
#endif // X3_PLUGINIMPL_CLASSITEM_H_
