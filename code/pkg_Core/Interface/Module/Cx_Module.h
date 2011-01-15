/*! \file Cx_Module.h
 *  \brief 定义插件模块实现类 Cx_Module
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_MODULE_H_
#define X3_PLUGINIMPL_MODULE_H_

#include "Ix_Module.h"

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief 插件模块实现类，仅内部使用
 *  \note  每个插件模块中有唯一的本类对象，在 XModuleImpl.h 中定义了该对象
 */
class Cx_Module : public Ix_Module
{
public:
    Cx_Module();
    ~Cx_Module();

    //! 初始化本插件，供 _xGetModuleInterface() 调用
    void Initialize(Ix_ObjectFactory* pFactory, HMODULE hModule);

public:
    void ClearModuleItems();
    long GetUnfreeObjectCount();
    Ix_ObjectFactory* GetObjectFactory() const { return m_pFactory; }
    HMODULE GetModuleInstance() const { return m_hModule; }
    HMODULE GetModuleResourceHandle() const { return m_hResource; }
    HMODULE SetModuleResourceHandle(HMODULE hResource);

private:
    Ix_ObjectFactory*   m_pFactory;
    HMODULE         m_hModule;
    HMODULE         m_hResource;
};

#endif // X3_PLUGINIMPL_MODULE_H_
