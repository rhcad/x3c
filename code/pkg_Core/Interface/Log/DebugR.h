/*! \file DebugR.h
 *  \brief 重定义ASSERT和VERIFY以便在Release下也可显示断言信息
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
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
