/*! \file RelToAbs.h
 *  \brief 定义相对文件名转换到绝对文件名的函数 RelToAbsWithPlugin, FileNameRelToAbs
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef UTILFUNC_RELTOABS_H_
#define UTILFUNC_RELTOABS_H_

#include "XComPtr.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

//! 得到主程序的模块句柄，通常为EXE，是主动加载插件的模块
inline HMODULE GetMainModuleHandle()
{
    HMODULE hModule = GetModuleHandleW(L"PluginManagerX3.dll");
    typedef HMODULE (*FUNC_GET)();
    FUNC_GET fn = (FUNC_GET)GetProcAddress(hModule, "xGetMainModuleHandle");
    return fn ? (*fn)() : NULL;
}

//! 相对文件名转换到绝对文件名，相对于当前插件文件
/*!
    \ingroup _GROUP_UTILFUNC
    \param relname 要转换的相对路径
    \param isfile 相对路径是文件名还是路径名
    \return 转换后的绝对路径，如果isfile为false则绝对路径末尾有斜号
    \see FileNameRelToAbs
*/
inline std::wstring RelToAbsWithPlugin(const wchar_t* relname, bool isfile = true)
{
    wchar_t path[MAX_PATH] = { 0 };
    
    GetModuleFileNameW(xGetModuleHandle(), path, MAX_PATH);
    PathRemoveFileSpecW(path);
    PathAppendW(path, relname);
    
    PathRemoveBackslashW(path);
    if (!isfile)
    {
        PathAddBackslashW(path);
    }
    
    return path;
}

//! 相对文件名转换到绝对文件名
/*! 相对于主模块文件（通常为EXE，是主动加载插件的模块）
    \ingroup _GROUP_UTILFUNC
    \param relname 要转换的相对路径
    \param isfile 相对路径是文件名还是路径名
    \return 转换后的绝对路径，如果isfile为false则绝对路径末尾有斜号
    \see GetMainModuleHandle
*/
inline std::wstring FileNameRelToAbs(const wchar_t* relname, bool isfile = true)
{
    wchar_t path[MAX_PATH] = { 0 };
    
    GetModuleFileNameW(GetMainModuleHandle(), path, MAX_PATH);
    PathRemoveFileSpecW(path);
    PathAppendW(path, relname);
    
    PathRemoveBackslashW(path);
    if (!isfile)
    {
        PathAddBackslashW(path);
    }
    
    return path;
}

//! 构造临时文件全名
/*! 相对于主模块文件（通常为EXE，是主动加载插件的模块）
    \ingroup _GROUP_UTILFUNC
    \param relname 要转换的相对路径，可以包含子目录名，例如“Log.txt”
    \param isfile 相对路径是文件名还是路径名
    \return 转换后的绝对路径，如果isfile为false则绝对路径末尾有斜号
    \see GetMainModuleHandle
*/
inline std::wstring MakeTempFileName(const wchar_t* relname = L"", bool isfile = true)
{
    wchar_t path[MAX_PATH] = { 0 };
    wchar_t exename[MAX_PATH] = { 0 };
    
    GetModuleFileNameW(GetMainModuleHandle(), exename, MAX_PATH);
    PathStripPath(exename);
    PathRemoveExtension(exename);

    GetTempPathW(MAX_PATH - 1, path);
    PathAppendW(path, exename);
    if (relname && *relname)
    {
        PathAppendW(path, relname);
    }
    
    PathRemoveBackslashW(path);
    if ( !(isfile && relname && *relname) )
    {
        PathAddBackslashW(path);
    }
    
    return path;
}

//! 确保路径末尾有反斜号
/*!
    \ingroup _GROUP_UTILFUNC
    \param[in,out] wstrPath 路径文件全名
    \return 和wstrPath相同
*/
inline std::wstring EnsurePathHasSlash(std::wstring& wstrPath)
{
    if (!wstrPath.empty())
    {
        wchar_t c = wstrPath[wstrPath.size() - 1];
        if (c != '\\' && c != '/')
        {
            wstrPath += '\\';
        }
    }
    return wstrPath;
}

#endif // UTILFUNC_RELTOABS_H_
