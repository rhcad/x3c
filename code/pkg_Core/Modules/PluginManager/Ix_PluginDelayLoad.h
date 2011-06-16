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
class Ix_PluginDelayLoad
{
public:
    virtual ~Ix_PluginDelayLoad() {}

    //! Register a plugin as observer owner.
    virtual void AddObserverPlugin(HMODULE hdll, const char* obtype) = 0;

    //! Load observer plugins when the event is first fired.
    virtual void FireFirstEvent(const char* obtype) = 0;
};

#endif // X3_MANAGER_IPLUGINDELAYLOAD_H_
