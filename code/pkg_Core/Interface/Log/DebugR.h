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

/*! \file DebugR.h
 *  \brief 重定义ASSERT和VERIFY以便在Release下也可显示断言信息
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_DEBUGR_H_
#define X3_LOG_DEBUGR_H_

int XCrtDbgReport(const char* file, long line, const char* msg);

#if _MSC_VER <= 1200 // VC6
#define __debugbreak DebugBreak
#endif

#undef ASSERT
#undef VERIFY

#define ASSERT(expr)    \
    (void) ((!!(expr)) || \
    (1 != XCrtDbgReport(__FILE__, __LINE__, #expr)) || \
    (__debugbreak(), 0))

#define VERIFY  ASSERT

#define ASSERT_MESSAGE(expr, msg)   \
    (void) ((!!(expr)) || \
    (1 != XCrtDbgReport(__FILE__, __LINE__, msg)) || \
    (__debugbreak(), 0))

#endif // X3_LOG_DEBUGR_H_
