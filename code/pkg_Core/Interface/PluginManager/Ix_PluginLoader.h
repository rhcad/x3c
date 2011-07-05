/*! \file Ix_PluginLoader.h
 *  \brief Define plugin loading interface: Ix_PluginLoader
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_MANAGER_IPLUGINLOADER_H_
#define X3_MANAGER_IPLUGINLOADER_H_

#include "Ix_Object.h"

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_PluginLoader
 *  \brief Plugin loading interface
 *  \see   Ix_ObjectFactory
 */
class Ix_PluginLoader : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_PluginLoader)

    //! Load all plugins in the module's path.
    /*!
        \param instance used as relative base, null as exe module.
        \param path plugin path, absolute path or relative to instance. eg: 'Plugins'.
        \param ext suffix of plugin filename, ignorecase, no * or ?, allow chars before dot.
            eg: '.plugin', '.plugin.dll', '_core.dll'.
        \param recursive true: include all child folders. false: only one folder.
        \return count of plugins loaded.
        \note need to call InitializePlugins() after.
        \see InitializePlugins, LoadPlugins, LoadPluginFiles
    */
    virtual long LoadPlugins(HMODULE instance, const wchar_t* path, 
        const wchar_t* ext = L".plugin" PLNEXT, bool recursive = true) = 0;

    //! Load all plugins in the application's path.
    /*!
        \param path plugin path, absolute path or relative to the application. eg: 'Plugins'.
        \param ext suffix of plugin filename, ignorecase, no * or ?, allow chars before dot.
            eg: '.plugin', '.plugin.dll', '_core.dll'.
        \param recursive true: include all child folders. false: only one folder.
        \return count of plugins loaded.
        \note need to call InitializePlugins() after.
        \see InitializePlugins, LoadPlugins, LoadPluginFiles
    */
    virtual long LoadPlugins(const wchar_t* path, 
        const wchar_t* ext = L".plugin" PLNEXT, bool recursive = true) = 0;

    //! Load the specified plugins in the specified path.
    /*!
        \param path relative path or empty, such as 'Plugins'.
        \param files include filename of plugins, separated by spaces or comma, such as '1.dll, 2.dll'.
        \param instance used as relative base.
        \return count of plugins loaded.
        \note need to call InitializePlugins() after.
        \see InitializePlugins, LoadPlugins
    */
    virtual long LoadPluginFiles(const wchar_t* path, const wchar_t* files, HMODULE instance = NULL) = 0;

    //! Initialize all plugins after they are loaded.
    /*! Initialize a plugin by calling it's x3InitializePlugin() export function.\n
        Automatic skip the plugin which has initialized or has not x3InitializePlugin.
        \return count of plugins which has initialized (or has not x3InitializePlugin) this time.
        \see OUTAPI bool x3InitializePlugin()
    */
    virtual long InitializePlugins() = 0;

    //! Register a plugin (not load dll).
    /*! It can used to static-link dll or main appliction module.
        \param instance the module to register.
        \return if register success.
        \note need to call InitializePlugins() after.
        \see InitializePlugins
    */
    virtual bool RegisterPlugin(HMODULE instance) = 0;

    //! Load a plugin.
    /*! Use LoadLibraryEx() and RegisterPlugin() to load.
        \param filename absolute file name or relative to the application.
        \return if load success.
        \note need to call InitializePlugins() after.
        \see InitializePlugins
    */
    virtual bool LoadPlugin(const wchar_t* filename) = 0;

    //! Unload a plugin.
    /*! Automatic call plugin's x3CanUnloadPlugin() and x3UninitializePlugin() export functions.
        \param name plugin filename regardless folder, such as 'MyData.plugin.dll'.
        \return if unload success.
        \see OUTAPI void x3UninitializePlugin()
    */
    virtual bool UnloadPlugin(const wchar_t* name) = 0;

    //! Unload all plugins.
    /*! Automatic call plugin's x3UninitializePlugin() export function.
        \return count of plugins unloaded.
        \see OUTAPI void x3UninitializePlugin()
    */
    virtual long UnloadPlugins() = 0;
};

#endif // X3_MANAGER_IPLUGINLOADER_H_
