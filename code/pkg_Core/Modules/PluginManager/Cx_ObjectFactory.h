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

// author: Zhang Yun Gui, Tao Jian Lin
// v2: 2011.1.5, change class-table to hash_map

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
    typedef std::vector<XCLSID>         VCLSID;
    typedef hash_map<std::string, _XCLASSMETA_ENTRY>    CLSMAP;
    struct MODULEINFO                   //!< 插件模块登记项
    {
        HMODULE             hModule;    //!< 插件DLL句柄
        Ix_Module*          pModule;    //!< 插件模块对象
        VCLSID              clsids;     //!< 注册了类工厂的所有类ID
        bool                bOwner;     //!< 是否由本类加载了该DLL
        bool                bInit;      //!< 是否已由 InitializePlugins 调用
    };
    std::vector<MODULEINFO> m_vecModule;    //!< 所有插件模块
    CLSMAP                  m_mapEntry;     //!< 类ID到登记项的映射表

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
