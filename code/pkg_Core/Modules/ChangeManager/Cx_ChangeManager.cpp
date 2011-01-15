// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// author: Zhang Yun Gui
// v2: 2011.1.5, change to hash_multimap

#include "StdAfx.h"
#include "Cx_ChangeManager.h"

Cx_ChangeManager::Cx_ChangeManager()
{
}

Cx_ChangeManager::~Cx_ChangeManager()
{
}

void Cx_ChangeManager::RegisterObserver(const char* type, Ix_ChangeObserver* observer)
{
    ASSERT(observer && type);

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

    std::pair<MAP_IT, MAP_IT> range (m_observers.equal_range(type));

    for (ObserverMap::const_iterator it = range.first; it != range.second; ++it)
    {
        if (it->second)
        {
            it->second->Update(data);
        }
    }
}
