/*! \file Cx_Module.h
 *  \brief Define the implement class of plugin module. (for internal use only)
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_MODULE_H_
#define X3_PLUGINIMPL_MODULE_H_

#include "Ix_Module.h"

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief the implement class of plugin module.
 *  \note  Each plugin has a object of this class. The object is defined in XModuleImpl.h .
 *  \internal
 */
class Cx_Module : public Ix_Module
{
public:
    Cx_Module();
    virtual ~Cx_Module();

    //! Initialize this plugin. Used by _xGetModuleInterface().
    void Initialize(Ix_ObjectFactory* pFactory, HMODULE hModule);

public:
    void ClearModuleItems();
    long GetUnfreeObjectCount();
    Ix_ObjectFactory* GetObjectFactory() const { return m_pFactory; }
    HMODULE GetModuleInstance() const { return m_hModule; }
    HMODULE GetModuleResourceHandle() const { return m_hResource; }
    HMODULE SetModuleResourceHandle(HMODULE hResource);

private:
    Cx_Module(const Cx_Module&);
    void operator=(const Cx_Module&);

    Ix_ObjectFactory*   m_pFactory;
    HMODULE         m_hModule;
    HMODULE         m_hResource;
};

#endif // X3_PLUGINIMPL_MODULE_H_
