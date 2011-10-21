/*
Module : SINSTANCE.H
Purpose: Defines the interface for an MFC wrapper class to do instance checking
Created: PJN / 29-07-1998

Copyright (c) 1996 - 2008 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


/////////////////////////// Macros / Defines //////////////////////////////////

#pragma once

#ifndef __SINSTANCE_H__
#define __SINSTANCE_H__

#ifndef CSINGLEINSTANCE_EXT_CLASS
#define CSINGLEINSTANCE_EXT_CLASS
#endif

#ifndef CSINGLEINSTANCE_EXT_API
#define CSINGLEINSTANCE_EXT_API
#endif


//////////////////////////// Includes /////////////////////////////////////////

#ifndef __AFXMT_H__
#pragma message("To avoid this message, please put afxmt.h in your pre compiled header (normally stdafx.h)")
#include <afxmt.h>
#endif


//////////////////////////// Classes //////////////////////////////////////////

class CSINGLEINSTANCE_EXT_CLASS CInstanceChecker
{
public:
//Constructors / Destructors
	CInstanceChecker(const CString& sUniqueName);
	virtual ~CInstanceChecker();

//General functions
	void ActivateChecker();
	BOOL TrackFirstInstanceRunning();
	BOOL PreviousInstanceRunning();
	HWND ActivatePreviousInstance(LPCTSTR lpCmdLine = NULL, ULONG_PTR dwCopyDataItemData = 0, DWORD dwTimeout = 30000); 
	void QuitPreviousInstance(int nExitCode = 0);

protected:
//Virtual methods
	virtual CString GetMMFFilename();
	virtual HWND GetWindowToTrack();

//Standard non-virtual methods
  void ReleaseLock();

//Data
	CMutex       m_instanceDataMutex;
	CMutex       m_executeMutex;
	CSingleLock* m_pExecuteLock;
  CString      m_sName;
};

#endif //__SINSTANCE_H__
