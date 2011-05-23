// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// author: Zhang Yun Gui
// v2, 2011.1.5: Change to hash_multimap
// v3, 2011.2.8: Support delay-load feature for observer plugins.

#ifndef _X3_CORE_CHANGEMANAGER_H
#define _X3_CORE_CHANGEMANAGER_H

#include <Ix_ChangeManager.h>

#if defined(_MSC_VER) && _MSC_VER > 1200    // not VC6
    #include <hash_map>
    using stdext::hash_multimap;
#elif defined(__GNUC__)                     // gcc
    #include <hash_map>
    using __gnu_cxx::hash_multimap;
    namespace __gnu_cxx {
        template<> struct hash<std::string>
        {
            size_t operator()(const std::string& s) const
            {
                return hash<char*>()(s.c_str());
            }
        };
    } // of namespace __gnu_cxx
#else                                       // VC6 or others
    #define hash_multimap std::multimap
#endif

class Cx_ChangeManager : public Ix_ChangeManager
{
protected:
    Cx_ChangeManager();
    virtual ~Cx_ChangeManager();

protected:
    virtual void RegisterObserver(const char* type, 
        Ix_ChangeObserver* observer, HMODULE fromdll = NULL);
    virtual void UnRegisterObserver(const char* type, Ix_ChangeObserver* observer);
    virtual void ChangeNotify(const char* type, ChangeNotifyData* data);

private:
    typedef hash_multimap<std::string, Ix_ChangeObserver*> ObserverMap;
    typedef std::pair<std::string, Ix_ChangeObserver*> ObserverPair;
    typedef ObserverMap::iterator MAP_IT;
    ObserverMap     m_observers;

    std::vector<std::pair<HMODULE, std::string> >   m_callers;
    std::vector<std::string>                        m_types;
};

#endif // _X3_CORE_CHANGEMANAGER_H
