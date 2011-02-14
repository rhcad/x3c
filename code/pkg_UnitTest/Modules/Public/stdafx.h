// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// Changes:
// 2011.2.14, ooyg: Support MFC dialog application and console application.
//

#ifndef _UNITTEST_PUBLIC_STDAFX_H
#define _UNITTEST_PUBLIC_STDAFX_H

#ifdef _AFXDLL              // MFC dialog application

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#else                       // Console application

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

#pragma warning(disable:4710)   // function not inlined
#pragma warning(disable:4786)   // identifier was truncated

#pragma warning(push, 1)
#include <iostream>
#pragma warning(disable:4511 4512)
#include <cppunit/config/SourcePrefix.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#pragma warning(pop)

#endif // _AFXDLL

#pragma warning(disable:4097)   // typedef-name used as synonym for TestFixture class
#pragma warning (push, 3)
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#pragma warning (pop)

#undef ASSERT
#undef VERIFY
#define ASSERT CPPUNIT_ASSERT
#define VERIFY CPPUNIT_ASSERT

#include <shlwapi.h>        // Windows light-weight utility APIs
#include <XComPtr.h>

#endif // _UNITTEST_PUBLIC_STDAFX_H
