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

/*! \file Cx_CreateWnd.h
 *  \brief 定义 Ix_CreateWnd 的模板实现类 Cx_CreateWnd
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_VIEW_CREATEWND_IMPL_H_
#define X3_VIEW_CREATEWND_IMPL_H_
#pragma once

#pragma warning(disable:4097)	// typedef-name used as synonym

#include "Ix_CreateWnd.h"

//! 对界面组件类进行注册的宏
/*!
	\ingroup _GROUP_VIEW_
	\param clsid 组件类ID
	\param cls 窗口类名，一般是从CWnd及其派生窗口类派生的
	\see Cx_CreateWnd, XDEFINE_CLASSMAP_ENTRY
*/
#if defined(XDEFINE_CLASSMAP_ENTRY) && !defined(XDEFINE_CLASSMAP_ENTRY_Wnd)
#define XDEFINE_CLASSMAP_ENTRY_Wnd(clsid, cls) \
	_XCLASSMETA_ENTRY(1, "Cx_Object<Cx_CreateWnd<" #cls ">>", clsid, "",	\
		reinterpret_cast<PFNXObjectCreator>(&Cx_Object<Cx_CreateWnd<cls> >::CreateObject),	\
		reinterpret_cast<PFNXGetObjectCount>(&Cx_Object<Cx_CreateWnd<cls> >::GetObjectCount),	\
		reinterpret_cast<PFNXRefCountByOthers>(&Cx_Object<Cx_CreateWnd<cls> >::GetRefCountByOthers)), 
#endif

//! Ix_CreateWnd 的模板实现类
/*! BASEWND 为窗口类，要实现下面两个函数: \n
	BOOL CreateWnd(CWnd* pParentWnd, UINT nID); \n
	void Refresh();
	\ingroup _GROUP_VIEW_
	\see XDEFINE_CLASSMAP_ENTRY_Wnd
*/
template <class BASEWND>
class Cx_CreateWnd : public Ix_CreateWnd
{
public:
	typedef Cx_CreateWnd<BASEWND> Cx_BaseWnd;

	Cx_CreateWnd()
	{
#ifdef _USRDLL
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
		m_pWnd = new BASEWND();
	}

	virtual ~Cx_CreateWnd()
	{
		ASSERT(NULL == m_pWnd);
	}
	
	virtual HWND GetWindow() const
	{
		return m_pWnd->GetSafeHwnd();
	}

	// BASEWND实现函数: BOOL CreateWnd(CWnd* pParentWnd, UINT nID)
	virtual bool CreateWnd(HWND hwndParent, UINT nID)
	{
#ifdef _USRDLL
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
		return !!m_pWnd->CreateWnd(CWnd::FromHandle(hwndParent), nID);
	}
	
	virtual void DestroyWnd()
	{
#ifdef _USRDLL
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
		if (m_pWnd != NULL)
		{
			m_pWnd->DestroyWindow();
			delete m_pWnd;
			m_pWnd = NULL;
		}
	}
	
	virtual BOOL DoCmdMsg(UINT nID, int nCode, void* pExtra, void* pInfo)
	{
#ifdef _USRDLL
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
		AFX_CMDHANDLERINFO* pHandlerInfo = static_cast<AFX_CMDHANDLERINFO*>(pInfo);
		return m_pWnd->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}

	// BASEWND实现函数: void Refresh()
	virtual void Refresh()
	{
#ifdef _USRDLL
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
#if _MSC_VER > 1300
		__if_exists(BASEWND::Refresh)
#endif
		{
			m_pWnd->Refresh();
		}
	}

protected:
	BASEWND*	m_pWnd;
};

#endif // X3_VIEW_CREATEWND_IMPL_H_
