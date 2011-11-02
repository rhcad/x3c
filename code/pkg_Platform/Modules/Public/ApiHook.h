#ifndef _WIN32_APIHOOK_H
#define _WIN32_APIHOOK_H

//! Replace a API function in the import directory of the specified module.
/*! The functions and module are all in the current process.
    \param dllname Name of the module imported by hmod, such as 'user32.dll'.
        If dllname is empty or null then auto search in all modules.
    \param oldproc A function of the module of 'dllname'.
    \param newproc A function to be used.
    \param hmod The specified module whose import directory will be replaced.
        If hmod is null then use the main application module.
    \return true if replaced successful.
*/
bool HookModuleFunction(LPCSTR dllname, PROC oldproc, PROC newproc, HMODULE hmod = NULL);

#endif // _WIN32_APIHOOK_H
