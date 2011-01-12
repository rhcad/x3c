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

#ifndef _UNITTEST_PUBLIC_STDAFX_H
#define _UNITTEST_PUBLIC_STDAFX_H

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#if _MSC_VER >= 1600        // VC2010
#include <SDKDDKVer.h>      // Defines the highest available Windows platform.
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <shlwapi.h>        // Windows light-weight utility APIs

#pragma warning(disable:4786)   // identifier was truncated
#pragma warning(disable:4097)   // typedef-name used as synonym for TestFixture class
#pragma warning (push, 3)
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#pragma warning (pop)

#undef ASSERT
#undef VERIFY
#define ASSERT CPPUNIT_ASSERT
#define VERIFY CPPUNIT_ASSERT

#include <XComPtr.h>

#endif // _UNITTEST_PUBLIC_STDAFX_H
