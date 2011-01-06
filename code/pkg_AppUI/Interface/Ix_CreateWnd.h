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

/*! \file Ix_CreateWnd.h
 *  \brief 定义窗口创建的接口 Ix_CreateWnd
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_VIEW_ICREATEWND_H_
#define X3_VIEW_ICREATEWND_H_
#pragma once

//! 窗口创建的接口
/*! 窗口类采用 Cx_CreateWnd 来实现本接口，父窗口类在创建子窗口时不需要关心子窗口类型和细节。
	\interface Ix_CreateWnd
	\ingroup _GROUP_VIEW_
*/
interface Ix_CreateWnd
{
	//! 返回窗口句柄
	virtual HWND GetWindow() const = 0;
	
	//! 创建窗口
	virtual bool CreateWnd(HWND hwndParent, UINT nID) = 0;

	//! 销毁窗口
	virtual void DestroyWnd() = 0;
	
	//! 传递 OnCmdMsg 通知
	virtual BOOL DoCmdMsg(UINT nID, int nCode, void* pExtra, void* pInfo) = 0;

	//! 刷新显示内容
	virtual void Refresh() = 0;
};

#endif // X3_VIEW_ICREATEWND_H_
