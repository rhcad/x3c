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
// XEND_DEFINE_MODULE()
// XEND_DEFINE_MODULE_DLL()
// XEND_DEFINE_MODULE_MFCEXTDLL()
// XEND_DEFINE_MODULE_MFCDLL()

#include "XClassItem.h"
#include "Cx_Object.h"
#include "Cx_SingletonObject.h"

//! Begin group of class factory registry.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \see XEND_DEFINE_MODULE
    \see XEND_DEFINE_MODULE_DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define XBEGIN_DEFINE_MODULE()  \
    const X3CLASSENTRY X3CLASSENTRY::s_classes[] = {

//! Register a regular class.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \param clsid class unique id, X3CLSID constant.
    \param cls implement class
*/
#define XDEFINE_CLASSMAP_ENTRY(clsid, cls)      \
    X3CLASSENTRY(1, "Cx_Object<" #cls ">", clsid,  \
        reinterpret_cast<PFNXObjectCreator>(&Cx_Object<cls>::CreateObject), \
        reinterpret_cast<PFNXGetObjectCount>(&Cx_Object<cls>::GetObjectCount),  \
        reinterpret_cast<PFNXRefCountByOthers>(&Cx_Object<cls>::GetRefCountByOthers)),

//! Register a single instance class.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \param clsid class unique id, X3CLSID constant.
    \param cls implement class
*/
#define XDEFINE_CLASSMAP_ENTRY_Singleton(clsid, cls)    \
    X3CLASSENTRY(MIN_SINGLETON_TYPE,   \
        "Cx_SingletonObject<" #cls ">", clsid,  \
        reinterpret_cast<PFNXObjectCreator>(&Cx_SingletonObject<cls>::CreateObject),    \
        reinterpret_cast<PFNXGetObjectCount>(&Cx_SingletonObject<cls>::GetObjectCount), \
        reinterpret_cast<PFNXRefCountByOthers>(&Cx_SingletonObject<cls>::GetRefCountByOthers)),

//! End group of class factory registry.
/*!
    \ingroup _GROUP_PLUGIN_CORE_
    \see XEND_DEFINE_MODULE_DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define XEND_DEFINE_MODULE() \
        X3CLASSENTRY() \
    };

#ifdef _MSC_VER                 // hide warnings
#pragma warning(disable:4710)   // inline function not expanded
#endif

//! End group of class factory registry and implement entry function of Win32DLL(USRDLL).
/*! Using this macro need include this file and XModuleImpl.h file.
    \ingroup _GROUP_PLUGIN_CORE_
    \see XEND_DEFINE_MODULE_MFCEXTDLL, XEND_DEFINE_MODULE_MFCDLL
*/
#if defined(_USRDLL) && defined(APIENTRY)
#define XEND_DEFINE_MODULE_DLL() \
        XEND_DEFINE_MODULE()    \
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID)   \
{   \
    if (dwReason == DLL_PROCESS_ATTACH) \
    {   \
        x3GetModuleInterface(NULL, (HMODULE)hModule);   \
    }   \
    else if (dwReason == DLL_PROCESS_DETACH)    \
    {   \
        x3GetCurrentModule()->ClearModuleItems();    \
    }   \
    return TRUE;    \
}
#else
#define XEND_DEFINE_MODULE_DLL() \
        XEND_DEFINE_MODULE()
#endif // XEND_DEFINE_MODULE_DLL

//! End group of class factory registry and implement entry function of MFC Extension DLL.
/*! Using this macro need include this file and XModuleImpl.h file.
    \ingroup _GROUP_PLUGIN_CORE_
    \see XEND_DEFINE_MODULE_DLL, XEND_DEFINE_MODULE_MFCDLL
*/
#define XEND_DEFINE_MODULE_MFCEXTDLL() \
        XEND_DEFINE_MODULE()    \
static AFX_EXTENSION_MODULE MFCExtDLL = { NULL, NULL }; \
extern "C" int APIENTRY \
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)    \
{   \
    if (dwReason == DLL_PROCESS_ATTACH) \
    {   \
        if (!AfxInitExtensionModule(MFCExtDLL, hInstance))  \
            return 0;   \
        new CDynLinkLibrary(MFCExtDLL); \
        x3GetModuleInterface(NULL, MFCExtDLL.hModule);  \
    }   \
    else if (dwReason == DLL_PROCESS_DETACH)    \
    {   \
        x3GetCurrentModule()->ClearModuleItems();        \
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
    \see XEND_DEFINE_MODULE_DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define XEND_DEFINE_MODULE_MFCDLL() \
        XEND_DEFINE_MODULE()    \
class CPluginApp : public CWinApp   \
{   \
public: \
    CPluginApp()    \
    {   \
    }   \
    virtual BOOL InitInstance() \
    {   \
        CWinApp::InitInstance();    \
        x3GetModuleInterface(NULL, m_hInstance);    \
        return TRUE;    \
    }   \
    virtual int ExitInstance()  \
    {   \
        x3GetCurrentModule()->ClearModuleItems();    \
        return CWinApp::ExitInstance(); \
    }   \
};

#endif // X3_PLUGINIMPL_MODULEMACRO_H_
