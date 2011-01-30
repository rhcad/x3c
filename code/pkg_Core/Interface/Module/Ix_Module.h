/*! \file Ix_Module.h
 *  \brief Define the plugin module interface: Ix_Module
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_IMODULE_H_
#define X3_PLUGINIMPL_IMODULE_H_

#include "Ix_Object.h"

interface Ix_ObjectFactory;

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_Module
 *  \brief the plugin module interface.
 *  \note  Each plugin (DLL) has a Ix_Module object which can get from xGetCurrentModule().
 *  \see xGetCurrentModule, xIsCreatorRegister, Ix_ObjectFactory
 */
interface Ix_Module
{
    //! Free all single instance objects when this plugin is unloading.
    virtual void ClearModuleItems() = 0;

    //! Return count of unfree objects.
    virtual long GetUnfreeObjectCount() = 0;

    //! Return the plugin manager object.
    virtual Ix_ObjectFactory* GetObjectFactory() const = 0;

    //! Return DLL handle of this plugin.
    virtual HMODULE GetModuleInstance() const = 0;

    //! Return resource DLL handle of this plugin.
    virtual HMODULE GetModuleResourceHandle() const = 0;

    //! Set localization resource DLL handle.
    virtual HMODULE SetModuleResourceHandle(HMODULE hResource) = 0;
};

//! Return the module object of the current project (this plugin).
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \return the only one module object in the current project.
*/
Ix_Module* xGetCurrentModule();

//! Check the class factory of the specified class id has registered or not.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \param clsid the specified class id.
    \return the class factory has registered (plugin loaded namely) or not.
*/
bool xIsCreatorRegister(const XCLSID& clsid);

#endif // X3_PLUGINIMPL_IMODULE_H_
