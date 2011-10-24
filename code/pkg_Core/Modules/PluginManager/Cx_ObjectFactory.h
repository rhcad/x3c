// x3c - C++ PluginFramework
#ifndef _X3_CORE_OBJECTFACTORY_H
#define _X3_CORE_OBJECTFACTORY_H

#include <Module/XClassItem.h>
#include <Module/Ix_Module.h>
#include <Ix_ObjectFactory.h>

#if defined(_MSC_VER) && _MSC_VER > 1200    // not VC6
    #include <hash_map>
    using stdext::hash_map;
/*
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
*/
#else                                       // VC6 or others
    #define hash_map std::map
#endif

class Cx_ObjectFactory
    : public Ix_ObjectFactory
{
    X3BEGIN_CLASS_DECLARE(Cx_ObjectFactory)
        X3DEFINE_INTERFACE_ENTRY(Ix_ObjectFactory)
    X3END_CLASS_DECLARE()
public:
    Cx_ObjectFactory();
    virtual ~Cx_ObjectFactory();

public:
    virtual bool IsCreatorRegister(const X3CLSID& clsid);
    virtual int CreateObject(const X3CLSID& clsid, X3IID iid, Ix_Object** ppv, HMODULE fromdll);

protected:
    typedef std::vector<X3CLSID>         CLSIDS;
    typedef std::pair<X3CLASSENTRY, long>  MAPITEM;     //!< entry+moduleIndex
    typedef hash_map<std::string, MAPITEM>    CLSMAP;   //!< clsid+item

    struct MODULE                       //!< plugin module info
    {
        HMODULE             hdll;       //!< DLL handle of the plugin
        Ix_Module*          module;     //!< plugin module object
        CLSIDS              clsids;     //!< all classes of the plugin
        bool                owned;      //!< the DLL is loaded by this class or not
        bool                inited;     //!< InitializePlugins() has been called or not
        wchar_t             filename[MAX_PATH];   //!< plugin filename

        MODULE() : hdll(NULL), module(NULL), owned(false), inited(false) {}
    };

    std::vector<MODULE*>    m_modules;      //!< all plugin modules
    CLSMAP                  m_clsmap;       //!< map from clsid to class factory
    long                    m_unloading;    //!< positive if a a plugin is unloading
    long                    m_loading;      //!< positive if a a plugin is loading

protected:
    int FindModule(HMODULE hModule);
    Ix_Module* GetModule(HMODULE hModule);
    long RegisterClassEntryTable(int moduleIndex);
    void ReleaseModule(HMODULE hModule);
    X3CLASSENTRY* FindEntry(const X3CLSID& clsid, int* moduleIndex = NULL);

private:
    Cx_ObjectFactory(const Cx_ObjectFactory&);
    void operator=(const Cx_ObjectFactory&);

    bool RegisterClass(int moduleIndex, const X3CLASSENTRY& cls);
    virtual bool LoadDelayedPlugin_(const wchar_t* filename) = 0;
};

#endif // _X3_CORE_OBJECTFACTORY_H
