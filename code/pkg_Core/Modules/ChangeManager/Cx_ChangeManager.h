// x3c - C++ PluginFramework
// author: Zhang Yungui
// v2, 2011.1.5: Change to hash_multimap
// v3, 2011.2.8: Support delay-load feature for observer plugins.
// v4, 2011.06.30: Remove RTTI.

#ifndef _X3_CORE_CHANGEMANAGER_H
#define _X3_CORE_CHANGEMANAGER_H

#include <ChangeObserver/Ix_ChangeManager.h>

#if defined(_MSC_VER) && _MSC_VER > 1200    // not VC6
    #include <hash_map>
    using stdext::hash_multimap;
/*
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
*/
#else                                       // VC6 or others
    #define hash_multimap std::multimap
#endif

class Cx_ChangeManager : public Ix_ChangeManager
{
    X3BEGIN_CLASS_DECLARE(Cx_ChangeManager)
        X3DEFINE_INTERFACE_ENTRY(Ix_ChangeManager)
    X3END_CLASS_DECLARE()
protected:
    Cx_ChangeManager();
    virtual ~Cx_ChangeManager();

private:
    virtual void RegisterObserver(const char* type, 
        Ix_ChangeObserver* observer, HMODULE fromdll = NULL);
    virtual void UnRegisterObserver(const char* type, Ix_ChangeObserver* observer);
    virtual void ChangeNotify(const char* type, ChangeNotifyData* data);

private:
    typedef hash_multimap<std::string, Ix_ChangeObserver*> ObserverMap;
    typedef std::pair<std::string, Ix_ChangeObserver*> ObserverPair;
    typedef ObserverMap::iterator MAP_IT;
    ObserverMap     m_observers;

    std::list<std::pair<HMODULE, std::string> >     m_callers;
    std::list<std::string>                          m_types;
};

#endif // _X3_CORE_CHANGEMANAGER_H
