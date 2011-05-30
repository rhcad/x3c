// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// author: Zhang Yun Gui, Tao Jian Lin
// v2: 2011.01.05, ooyg: Change class-table to hash_map
// v3: 2011.02.04, ooyg: Add filename in MODULEINFO. Add module index in class map.
// v4: 2011.02.07, ooyg: Implement the delay-loaded feature.
// v5: 2011.02.16, ooyg: Avoid plugin loading when a plugin is unloading.

#ifndef _X3_CORE_OBJECTFACTORY_H
#define _X3_CORE_OBJECTFACTORY_H

#include <Module/XClassItem.h>
#include <Module/Ix_Module.h>
#include <Ix_ObjectFactory.h>

#if defined(_MSC_VER) && _MSC_VER > 1200    // not VC6
    #include <hash_map>
    using stdext::hash_map;
#elif defined(__GNUC__)                     // gcc
    #include <ext/hash_map>
    using __gnu_cxx::hash_map;
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
    #define hash_map std::map
#endif

class Cx_ObjectFactory
    : public Ix_ObjectFactory
{
public:
    Cx_ObjectFactory();
    virtual ~Cx_ObjectFactory();

public:
    virtual bool IsCreatorRegister(const XCLSID& clsid);
    virtual int CreateObject(const XCLSID& clsid, Ix_Object** ppv, HMODULE fromdll);
    virtual long CreateSpecialInterfaceObjects(const char* iid);
    virtual bool QuerySpecialInterfaceObject(long index, const char* iid, Ix_Object** ppv);
    virtual bool HasCreatorReplaced(const XCLSID& clsid);

protected:
    typedef std::vector<XCLSID>         CLSIDS;
    typedef std::pair<_XCLASSMETA_ENTRY, long>  MAPITEM;    //!< entry+moduleIndex
    typedef hash_map<std::string, MAPITEM>    CLSMAP;       //!< clsid+item

    struct MODULEINFO                   //!< plugin module info
    {
        HMODULE             hdll;       //!< DLL handle of the plugin
        Ix_Module*          module;     //!< plugin module object
        CLSIDS              clsids;     //!< all classes of the plugin
        bool                owned;      //!< the DLL is loaded by this class or not
        bool                inited;     //!< InitializePlugins() has been called or not
        wchar_t             filename[MAX_PATH];   //!< plugin filename

        MODULEINFO() : hdll(NULL), module(NULL), owned(false), inited(false) {}
    };

    std::vector<MODULEINFO> m_modules;  //!< all plugin modules
    CLSMAP                  m_clsmap;   //!< map from clsid to class factory
    long                    m_unloading;    //!< positive if a a plugin is unloading

protected:
    int FindModule(HMODULE hModule);
    Ix_Module* GetModule(HMODULE hModule);
    long RegisterClassEntryTable(HMODULE hModule);
    void ReleaseModule(HMODULE hModule);
    _XCLASSMETA_ENTRY* FindEntry(const XCLSID& clsid, int* moduleIndex = NULL);

private:
    Cx_ObjectFactory(const Cx_ObjectFactory&);
    void operator=(const Cx_ObjectFactory&);

    bool RegisterClass(int moduleIndex, const _XCLASSMETA_ENTRY& cls);
    virtual bool LoadDelayPlugin(const wchar_t* filename) = 0;
};

#endif // _X3_CORE_OBJECTFACTORY_H
