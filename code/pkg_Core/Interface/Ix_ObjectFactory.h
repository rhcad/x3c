// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*! \file Ix_ObjectFactory.h
 *  \brief Define object creator interface: Ix_ObjectFactory
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_CORE_IOBJECTFACTORY_H_
#define X3_CORE_IOBJECTFACTORY_H_

#include "Ix_Object.h"

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_ObjectFactory
 *  \brief Object creator interface
 *  \see   Ix_Object, Ix_Module
 */
interface Ix_ObjectFactory
{
    //! Check if the class is loaded.
    virtual bool IsCreatorRegister(const XCLSID& clsid) = 0;

    //! Create an object with the class id.
    virtual HRESULT CreateObject(const XCLSID& clsid, Ix_Object** ppv, HMODULE fromdll) = 0;

    //! Create singleton objects that support the specified interface in all plugins.
    /*!
        \param iid the specified interface's id
        \return The count of plugins that support the specified interface, whether objects have created or not.
    */
    virtual long CreateSpecialInterfaceObjects(const char* iid) = 0;

    //! Get the singleton object in the plugin of the specified index.
    /*!
        \param[in] index the specified zero-base index of a plugin.
        \param[in] iid the specified interface's id
        \param[in,out] ppv fill with address of a new object, not create if zero.
        \return Return false if index is out of range, otherwise return true regardless ppv.
    */
    virtual bool QuerySpecialInterfaceObject(long index, const char* iid, Ix_Object** ppv) = 0;

    //! Return if any class factory is replaced.
    virtual bool HasCreatorReplaced(const XCLSID& clsid) = 0;
};

#endif // X3_CORE_IOBJECTFACTORY_H_
