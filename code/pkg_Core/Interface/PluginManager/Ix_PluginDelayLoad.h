/*! \file Ix_PluginDelayLoad.h
 *  \brief Define plugin delay-loading interface: Ix_PluginDelayLoad
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.02.08
 */
#ifndef X3_MANAGER_IPLUGINDELAYLOAD_H_
#define X3_MANAGER_IPLUGINDELAYLOAD_H_

#include "Ix_Object.h"

X3CLSID_DEFINE(CLSID_PluginDelayLoad, "8f2a7b90-8134-4e16-9830-861df9b7f42a");

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_PluginDelayLoad
 *  \brief Plugin delay-loading interface.
 *  \see   x3::CLSID_PluginDelayLoad
 */
class Ix_PluginDelayLoad : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_PluginDelayLoad)

    //! Register a plugin as observer owner.
    virtual void AddObserverPlugin(HMODULE hdll, const char* obtype, const wchar_t* subtype = L"") = 0;

    //! Load observer plugins when the event is first fired.
    virtual void FireFirstEvent(const char* obtype, const wchar_t* subtype = L"") = 0;

    //! Load plugin immediately which is marked as delay-loading.
    /*!
        \param filename plugin filename regardless folder.
        \return true if the plugin is loaded.
    */
    virtual bool LoadDelayedPlugin(const std::wstring& filename) = 0;
};

#endif // X3_MANAGER_IPLUGINDELAYLOAD_H_
