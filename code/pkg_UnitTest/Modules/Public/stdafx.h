// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// Changes:
// 2011.2.14, ooyg: Support MFC dialog application and console application.
//

#ifndef _UNITTEST_PUBLIC_STDAFX_H
#define _UNITTEST_PUBLIC_STDAFX_H

#ifdef _CONSOLE                 // Console application
#undef _AFXDLL
#endif

#include <UtilFunc/X3Portability.h>

#ifdef _CONSOLE                 // Console application

#include <tchar.h>

#ifdef _MSC_VER
#pragma warning(disable:4710)   // function not inlined
#pragma warning(disable:4786)   // identifier was truncated
#pragma warning(push, 1)
#pragma warning(disable:4511 4512)
#endif
#include <iostream>
#include <cppunit/config/SourcePrefix.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // _AFXDLL

#ifdef _MSC_VER
#pragma warning(disable:4097)   // typedef-name used as synonym for TestFixture class
#pragma warning (push, 3)
#endif
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#ifdef _MSC_VER
#pragma warning (pop)
#endif

#undef ASSERT
#undef VERIFY
#define ASSERT CPPUNIT_ASSERT
#define VERIFY CPPUNIT_ASSERT

#include <XComPtr.h>

#endif // _UNITTEST_PUBLIC_STDAFX_H
