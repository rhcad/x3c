// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
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

/*! \file XModuleMacro.h
 *  \brief 定义组件类注册的 XBEGIN_DEFINE_MODULE 等宏
 *  \note XModuleImpl.h 和本文件可以不需要同时包含在一个CPP文件中。\n
 *        如果不希望使用本文件和 XModuleImpl.h 等文件，可使用 XComCreator.h 文件。
 *  \author Zhang Yun Gui, C++ Plugin Framework
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

//! 开始组件类注册的宏
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\see XEND_DEFINE_MODULE
	\see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define XBEGIN_DEFINE_MODULE()	\
	const _XCLASSMETA_ENTRY _XCLASSMETA_ENTRY::s_classes[] = {

//! 对普通组件类进行注册的宏
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\param clsid 组件类ID，必须是LPCSTR或CHAR数组的常量
	\param cls 组件类名
*/
#define XDEFINE_CLASSMAP_ENTRY(clsid, cls)		\
	_XCLASSMETA_ENTRY(1, "Cx_Object<" #cls ">", clsid, "",	\
		reinterpret_cast<PFNXObjectCreator>(&Cx_Object<cls>::CreateObject),	\
		reinterpret_cast<PFNXGetObjectCount>(&Cx_Object<cls>::GetObjectCount),	\
		reinterpret_cast<PFNXRefCountByOthers>(&Cx_Object<cls>::GetRefCountByOthers)), 

//! 对单实例组件类进行注册的宏
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\param clsid 组件类ID，必须是LPCSTR或CHAR数组的常量
	\param cls 组件类名
*/
#define XDEFINE_CLASSMAP_ENTRY_Singleton(clsid, cls)	\
	_XCLASSMETA_ENTRY(MIN_SINGLETON_TYPE,	\
		"Cx_SingletonObject<" #cls ">", clsid, "",	\
		reinterpret_cast<PFNXObjectCreator>(&Cx_SingletonObject<cls>::CreateObject),	\
		reinterpret_cast<PFNXGetObjectCount>(&Cx_SingletonObject<cls>::GetObjectCount),	\
		reinterpret_cast<PFNXRefCountByOthers>(&Cx_SingletonObject<cls>::GetRefCountByOthers)), 

//! 对支持特定通用接口的单实例组件类进行注册的宏
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\param iid 特定通用接口的接口ID名称，必须是LPCSTR或CHAR数组的常量
	\param cls 组件类名
*/
#define XDEFINE_SPECIAL_INTERFACE_ENTRY_Singleton(iid, cls)		\
	_XCLASSMETA_ENTRY(MIN_SINGLETON_TYPE + 1,	\
		"Cx_SingletonObject<" #cls ">", XCLSID(), iid,	\
		reinterpret_cast<PFNXObjectCreator>(&Cx_SingletonObject<cls>::CreateObject),	\
		reinterpret_cast<PFNXGetObjectCount>(&Cx_SingletonObject<cls>::GetObjectCount),	\
		reinterpret_cast<PFNXRefCountByOthers>(&Cx_SingletonObject<cls>::GetRefCountByOthers)), 

//! 结束组件类注册的宏
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define	XEND_DEFINE_MODULE() \
		_XCLASSMETA_ENTRY()	\
	};

#pragma warning(disable:4710)	// inline function not expanded

//! 结束组件类注册的宏，并实现Win32DLL(USRDLL)默认的入口函数
/*! 要使用本宏的话，需要同时包含本文件和 XModuleImpl.h 文件
	\ingroup _GROUP_PLUGIN_CORE_
	\see XEND_DEFINE_MODULE_MFCEXTDLL, XEND_DEFINE_MODULE_MFCDLL
*/
#define	XEND_DEFINE_MODULE_WIN32DLL() \
		_XCLASSMETA_ENTRY()	\
	};	\
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID)	\
{	\
	if (dwReason == DLL_PROCESS_ATTACH)	\
	{	\
		_xGetModuleInterface(NULL, (HMODULE)hModule);	\
	}	\
	else if (dwReason == DLL_PROCESS_DETACH)	\
	{	\
		xGetCurrentModule()->ClearModuleItems();	\
	}	\
	return TRUE;	\
}

//! 结束组件类注册的宏，并实现MFC扩展DLL默认的DLL入口函数
/*! 要使用本宏的话，需要同时包含本文件和 XModuleImpl.h 文件
	\ingroup _GROUP_PLUGIN_CORE_
	\see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCDLL
*/
#define	XEND_DEFINE_MODULE_MFCEXTDLL() \
		_XCLASSMETA_ENTRY()	\
	};	\
static AFX_EXTENSION_MODULE MFCExtDLL = { NULL, NULL };	\
extern "C" int APIENTRY	\
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)	\
{	\
	if (dwReason == DLL_PROCESS_ATTACH)	\
	{	\
		if (!AfxInitExtensionModule(MFCExtDLL, hInstance))	\
			return 0;	\
		new CDynLinkLibrary(MFCExtDLL);	\
		_xGetModuleInterface(NULL, MFCExtDLL.hModule);	\
	}	\
	else if (dwReason == DLL_PROCESS_DETACH)	\
	{	\
		xGetCurrentModule()->ClearModuleItems();		\
		AfxTermExtensionModule(MFCExtDLL);	\
	}	\
	return 1;	\
}

//! 结束组件类注册的宏，并实现MFC常规DLL默认的DLL程序基类 CPluginApp
/*! 要使用本宏的话，需要同时包含本文件和 XModuleImpl.h 文件
	\note 在MFC常规DLL的任何导出函数和可供外部调用的函数中，必须在使用MFC的语句前
		先调用 AFX_MANAGE_STATE(AfxGetStaticModuleState());
	\ingroup _GROUP_PLUGIN_CORE_
	\see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define	XEND_DEFINE_MODULE_MFCDLL() \
		_XCLASSMETA_ENTRY()	\
	};	\
class CPluginApp : public CWinApp	\
{	\
public:	\
	CPluginApp()	\
	{	\
	}	\
	virtual BOOL InitInstance()	\
	{	\
		CWinApp::InitInstance();	\
		_xGetModuleInterface(NULL, m_hInstance);	\
		return TRUE;	\
	}	\
	virtual int ExitInstance()	\
	{	\
		xGetCurrentModule()->ClearModuleItems();	\
		return CWinApp::ExitInstance();	\
	}	\
};

#endif // X3_PLUGINIMPL_MODULEMACRO_H_
