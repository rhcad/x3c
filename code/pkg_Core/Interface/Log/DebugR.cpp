/*! \file DebugR.cpp
 *  \brief XCrtDbgReport
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */

#ifndef _MSC_VER

int XCrtDbgReport(const char* file, long line, const char* msg)
{
#ifdef LOG_EVENT_ANSI
    Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
    if (pIFManager)
    {
        pIFManager->CrtDbgReport(msg, file, line);
    }
#else
    file;line;msg;
#endif
    return 0;
}

#else // _MSC_VER

#pragma comment(lib, "shlwapi.lib")
#if defined(_WINUSER_) && !defined(NOUSER)
    #include <stdlib.h>
    #include <stdio.h>
    #pragma comment(lib, "user32.lib")
#endif
#include <signal.h>

int XCrtDbgReport(const char* file, long line, const char* msg)
{
    file;line;msg;
    int code = 0;

#ifdef LOG_EVENT_ANSI
    {
        Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
        if (pIFManager)
        {
            code = pIFManager->CrtDbgReport(msg, file, line);
        }
    }
#endif
    if (0 == code)
    {
        code = 4;   // IDRETRY

#if defined(_WINUSER_) && !defined(NOUSER)
        char buf[512];

#if _MSC_VER <= 1200 // VC6
        sprintf(buf,
#else
        sprintf_s(buf, 512,
#endif
            "Debug Assertion Failed!\n\n"
            "Expression: %s\n"
            "File: %s\n"
            "line: %d\n"
            "\n(Press Retry to debug the application)",
            msg, file, line);

        code = ::MessageBoxA(NULL, buf, "Debug Assertion Failed",
            MB_TASKMODAL|MB_ICONHAND|MB_ABORTRETRYIGNORE|MB_SETFOREGROUND);
#endif // _WINUSER_
    }  // if

    if (3 == code)    // IDABORT: abort the program
    {
        raise(SIGABRT);
        _exit(3);
    }

    // Retry: return 1 to call the debugger
    if (4 == code)  // IDRETRY
    {
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
        if (::IsDebuggerPresent())
#endif
            return 1;
    }

    return 0;               // Ignore: continue execution
}

#endif // _MSC_VER
