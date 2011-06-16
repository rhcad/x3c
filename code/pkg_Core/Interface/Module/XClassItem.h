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
 *  \see   x3GetClassEntryTable, X3BEGIN_MODULE
 *  \internal
 */
struct X3CLASSENTRY
{
    BYTE                type;               //!< see MIN_SINGLETON_TYPE and XModuleMacro.h
    const char*         className;          //!< implement class name
    X3CLSID             clsid;              //!< class id. may be empty if iidSpecial is valid.
    const char*         iidSpecial;         //!< special interface name, see X3_INTERFACE_Singleton.
    PFNXObjectCreator   pfnObjectCreator;   //!< class factory function
    PFNXGetObjectCount  pfnGetObjectCount;  //!< object count of this class
    PFNXRefCountByOthers    pfnRefCountByOthers;    //!< count of objects used by other modules

    //! Used by X3_CLASS_ENTRY, X3_CLASS_Singleton
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

    //! Used by X3END_MODULE
    X3CLASSENTRY()
        : type(0), className(""), clsid(""), iidSpecial("")
        , pfnObjectCreator(NULL), pfnGetObjectCount(NULL)
        , pfnRefCountByOthers(NULL)
    {
    }

    //! class factory registries. filled by X3BEGIN_MODULE.
    static const X3CLASSENTRY s_classes[];
};

#pragma pack(pop)
#endif // X3_PLUGINIMPL_CLASSITEM_H_
