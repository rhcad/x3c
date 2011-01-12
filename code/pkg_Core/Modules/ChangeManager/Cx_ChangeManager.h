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

// author: Zhang Yun Gui
// v2: 2011.1.5, change to hash_multimap

#ifndef _X3_CORE_CHANGEMANAGER_H
#define _X3_CORE_CHANGEMANAGER_H

#include <Ix_ChangeManager.h>

#if _MSC_VER > 1200 // not VC6
    #include <hash_map>
    using stdext::hash_multimap;
#else
    #define hash_multimap std::multimap
#endif

class Cx_ChangeManager : public Ix_ChangeManager
{
protected:
    Cx_ChangeManager();
    virtual ~Cx_ChangeManager();

protected:
    virtual void RegisterObserver(const char* type, Ix_ChangeObserver* observer);
    virtual void UnRegisterObserver(const char* type, Ix_ChangeObserver* observer);
    virtual void ChangeNotify(const char* type, ChangeNotifyData* data);

private:
    typedef hash_multimap<std::string, Ix_ChangeObserver*> ObserverMap;
    typedef std::pair<std::string, Ix_ChangeObserver*> ObserverPair;
    typedef ObserverMap::iterator MAP_IT;
    ObserverMap     m_observers;
};

#endif // _X3_CORE_CHANGEMANAGER_H
