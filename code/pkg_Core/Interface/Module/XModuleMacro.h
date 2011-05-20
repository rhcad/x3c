/*! \file   XModuleMacro.h
 *  \brief  Define macros of class factory registry, such as XBEGIN_DEFINE_MODULE.
 *  \note   This file and XModuleImpl.h may be included in different CPP files.\n
 *      if you don't want to use this file and XModuleImpl.h, then you can use XComCreator.h file.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_MODULEMACRO_H_
#define X3_PLUGINIMPL_MODULEMACRO_H_

// XBEGIN_DEFINE_MODULE()
//     XDEFINE_CLASSMAP_ENTRY(clsid, cls)
//     XDEFINE_CLASSMAP_ENTRY_Singleton(clsid, cls)
//     XDEFINE_SPECIAL_INTERFACE_ENTRY_Singleton(clsid, iid, cls)
// XEND_DEFINE_MODULE()
// XEND_DEFINE_MODULE_WIN32DLL()
// XEND_DEFINE_MODULE_MFCEXTDLL()
// XEND_DEFINE_MODULE_MFCDLL()

#include "XClassItem.h"
#include "Cx_Object.h"
#include "Cx_SingletonObject.h"

//! Begin group of class factory registry.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \see XEND_DEFINE_MODULE
    \see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define XBEGIN_DEFINE_MODULE()  \
    const _XCLASSMETA_ENTRY _XCLASSMETA_ENTRY::s_classes[] = {

//! Register a regular class.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \param clsid class unique id, XCLSID constant.
    \param cls implement class
*/
#define XDEFINE_CLASSMAP_ENTRY(clsid, cls)      \
    _XCLASSMETA_ENTRY(1, "Cx_Object<" #cls ">", clsid, "",  \
        reinterpret_cast<PFNXObjectCreator>(&Cx_Object<cls>::CreateObject), \
        reinterpret_cast<PFNXGetObjectCount>(&Cx_Object<cls>::GetObjectCount),  \
        reinterpret_cast<PFNXRefCountByOthers>(&Cx_Object<cls>::GetRefCountByOthers)),

//! Register a single instance class.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \param clsid class unique id, XCLSID constant.
    \param cls implement class
*/
#define XDEFINE_CLASSMAP_ENTRY_Singleton(clsid, cls)    \
    _XCLASSMETA_ENTRY(MIN_SINGLETON_TYPE,   \
        "Cx_SingletonObject<" #cls ">", clsid, "",  \
        reinterpret_cast<PFNXObjectCreator>(&Cx_SingletonObject<cls>::CreateObject),    \
        reinterpret_cast<PFNXGetObjectCount>(&Cx_SingletonObject<cls>::GetObjectCount), \
        reinterpret_cast<PFNXRefCountByOthers>(&Cx_SingletonObject<cls>::GetRefCountByOthers)),

//! Register a single instance class that support the specific interface.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \param iid the specific interface id name. char array constant.
    \param cls implement class
*/
#define XDEFINE_SPECIAL_INTERFACE_ENTRY_Singleton(iid, cls)     \
    _XCLASSMETA_ENTRY(MIN_SINGLETON_TYPE + 1,   \
        "Cx_SingletonObject<" #cls ">", XCLSID(), iid,  \
        reinterpret_cast<PFNXObjectCreator>(&Cx_SingletonObject<cls>::CreateObject),    \
        reinterpret_cast<PFNXGetObjectCount>(&Cx_SingletonObject<cls>::GetObjectCount), \
        reinterpret_cast<PFNXRefCountByOthers>(&Cx_SingletonObject<cls>::GetRefCountByOthers)),

//! End group of class factory registry.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define XEND_DEFINE_MODULE() \
        _XCLASSMETA_ENTRY() \
    };

#ifdef _MSC_VER
#pragma warning(disable:4710)   // inline function not expanded
#endif

//! End group of class factory registry and implement entry function of Win32DLL(USRDLL).
/*! Using this macro need include this file and XModuleImpl.h file.
    \ingroup _GROUP_PLUGIN_CORE_
    \see XEND_DEFINE_MODULE_MFCEXTDLL, XEND_DEFINE_MODULE_MFCDLL
*/
#ifdef _WIN32
#define XEND_DEFINE_MODULE_WIN32DLL() \
        _XCLASSMETA_ENTRY() \
    };  \
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID)   \
{   \
    if (dwReason == DLL_PROCESS_ATTACH) \
    {   \
        _xGetModuleInterface(NULL, (HMODULE)hModule);   \
    }   \
    else if (dwReason == DLL_PROCESS_DETACH)    \
    {   \
        xGetCurrentModule()->ClearModuleItems();    \
    }   \
    return TRUE;    \
}
#else
#define XEND_DEFINE_MODULE_WIN32DLL() \
        _XCLASSMETA_ENTRY() \
    };
#endif // XEND_DEFINE_MODULE_WIN32DLL

//! End group of class factory registry and implement entry function of MFC Extension DLL.
/*! Using this macro need include this file and XModuleImpl.h file.
    \ingroup _GROUP_PLUGIN_CORE_
    \see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCDLL
*/
#define XEND_DEFINE_MODULE_MFCEXTDLL() \
        _XCLASSMETA_ENTRY() \
    };  \
static AFX_EXTENSION_MODULE MFCExtDLL = { NULL, NULL }; \
extern "C" int APIENTRY \
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)    \
{   \
    if (dwReason == DLL_PROCESS_ATTACH) \
    {   \
        if (!AfxInitExtensionModule(MFCExtDLL, hInstance))  \
            return 0;   \
        new CDynLinkLibrary(MFCExtDLL); \
        _xGetModuleInterface(NULL, MFCExtDLL.hModule);  \
    }   \
    else if (dwReason == DLL_PROCESS_DETACH)    \
    {   \
        xGetCurrentModule()->ClearModuleItems();        \
        AfxTermExtensionModule(MFCExtDLL);  \
    }   \
    return 1;   \
}

//! End group of class factory registry and implement entry function of MFC regular DLL.
/*! This macro implements CPluginApp class.\n
    Using this macro need include this file and XModuleImpl.h file.
    \note Call the following statemant before call any MFC function: \n
            AFX_MANAGE_STATE(AfxGetStaticModuleState());
    \ingroup _GROUP_PLUGIN_CORE_
    \see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define XEND_DEFINE_MODULE_MFCDLL() \
        _XCLASSMETA_ENTRY() \
    };  \
class CPluginApp : public CWinApp   \
{   \
public: \
    CPluginApp()    \
    {   \
    }   \
    virtual BOOL InitInstance() \
    {   \
        CWinApp::InitInstance();    \
        _xGetModuleInterface(NULL, m_hInstance);    \
        return TRUE;    \
    }   \
    virtual int ExitInstance()  \
    {   \
        xGetCurrentModule()->ClearModuleItems();    \
        return CWinApp::ExitInstance(); \
    }   \
};

#endif // X3_PLUGINIMPL_MODULEMACRO_H_
