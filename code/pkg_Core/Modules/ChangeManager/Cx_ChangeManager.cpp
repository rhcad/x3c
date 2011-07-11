// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// author: Zhang Yun Gui
// v2, 2011.1.5: Change to hash_multimap
// v3, 2011.2.8: Support delay-load feature for observer plugins.

#include <UtilFunc/PluginInc.h>
#include "Cx_ChangeManager.h"
#include <PluginManager/Ix_PluginDelayLoad.h>

Cx_ChangeManager::Cx_ChangeManager()
{
}

Cx_ChangeManager::~Cx_ChangeManager()
{
}

void Cx_ChangeManager::RegisterObserver(const char* type, 
                                        Ix_ChangeObserver* observer, 
                                        HMODULE fromdll)
{
    ASSERT(observer && type);

    std::pair<HMODULE, std::string> key(fromdll, type);
    if (fromdll && !x3::has_value(m_callers, key))
    {
        m_callers.push_back(key);

        Cx_Interface<Ix_PluginDelayLoad> pIFLoader(x3::CLSID_PluginDelayLoad);
        if (pIFLoader)
        {
            pIFLoader->AddObserverPlugin(fromdll, type);
        }
    }

    std::pair<MAP_IT, MAP_IT> range (m_observers.equal_range(type));

    for (MAP_IT it = range.first; it != range.second; ++it)
    {
        if (NULL == it->second)
        {
            it->second = observer;
            return;
        }
    }

    m_observers.insert(ObserverPair(type, observer));
}

void Cx_ChangeManager::UnRegisterObserver(const char* type, Ix_ChangeObserver* observer)
{
    std::pair<MAP_IT, MAP_IT> range (m_observers.equal_range(type));

    for (MAP_IT it = range.first; it != range.second; ++it)
    {
        if (it->second == observer)
        {
            it->second = NULL;  //m_observers.erase(it);
            break;
        }
    }
}

void Cx_ChangeManager::ChangeNotify(const char* type, ChangeNotifyData* data)
{
    ASSERT(data != NULL);

    if (!x3::has_value(m_types, std::string(type)))
    {
        m_types.push_back(type);

        Cx_Interface<Ix_PluginDelayLoad> pIFLoader(x3::CLSID_PluginDelayLoad);
        if (pIFLoader)
        {
            pIFLoader->FireFirstEvent(type);
        }
    }

    std::pair<MAP_IT, MAP_IT> range (m_observers.equal_range(type));

    for (ObserverMap::const_iterator it = range.first; it != range.second; ++it)
    {
        if (it->second)
        {
            it->second->Update(data);
        }
    }
}
