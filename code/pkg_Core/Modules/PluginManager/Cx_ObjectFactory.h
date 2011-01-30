// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

// author: Zhang Yun Gui, Tao Jian Lin
// v2: 2011.1.5, ooyg: change class-table to hash_map

#ifndef _X3_CORE_OBJECTFACTORY_H
#define _X3_CORE_OBJECTFACTORY_H

#include <XClassItem.h>
#include <Ix_Module.h>
#include <Ix_ObjectFactory.h>

#if _MSC_VER > 1200 // not VC6
    #include <hash_map>
    using stdext::hash_map;
#else
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
    virtual HRESULT CreateObject(const XCLSID& clsid, Ix_Object** ppv, HMODULE fromdll);
    virtual long CreateSpecialInterfaceObjects(const char* iid);
    virtual bool QuerySpecialInterfaceObject(long index, const char* iid, Ix_Object** ppv);
    virtual bool HasCreatorReplaced(const XCLSID& clsid);

protected:
    typedef std::vector<XCLSID>         CLSIDS;
    typedef hash_map<std::string, _XCLASSMETA_ENTRY>    CLSMAP;
    
    struct MODULEINFO                   //!< plugin module info
    {
        HMODULE             hdll;       //!< DLL handle of the plugin
        Ix_Module*          module;     //!< plugin module object
        CLSIDS              clsids;     //!< all classes of the plugin
        bool                owned;      //!< the DLL is loaded by this class or not
        bool                inited;     //!< InitializePlugins() has been called or not
    };
    
    std::vector<MODULEINFO> m_modules;  //!< all plugin modules
    CLSMAP                  m_clsmap;   //!< map from clsid to class factory

protected:
    int FindModule(HMODULE hModule);
    Ix_Module* GetModule(HMODULE hModule);
    long RegisterClassEntryTable(HMODULE hModule);
    void ReleaseModule(HMODULE hModule);

private:
    _XCLASSMETA_ENTRY* FindEntry(const XCLSID& clsid);
    bool RegisterClass(int moduleIndex, const _XCLASSMETA_ENTRY& cls);
};

#endif // _X3_CORE_OBJECTFACTORY_H
