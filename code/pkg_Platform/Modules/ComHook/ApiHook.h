#ifndef _WIN32_APIHOOK_H
#define _WIN32_APIHOOK_H

//! Replace a API function in the import directory of the current process.
bool HookModuleFunction(LPCSTR dllname, PROC oldproc, PROC newproc);

#endif // _WIN32_APIHOOK_H
