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

#ifndef _X3_CONFIGDB_DBFUNC_H
#define _X3_CONFIGDB_DBFUNC_H

#include <ctrim.h>

//! 数据库常用函数
class DbFunc
{
public:
    //! 显示COM错误信息
    static void PrintComError(_com_error &e, LPCSTR file, long lLine, LPCWSTR pszSQL = NULL);

    //! 显示错误信息
    static void PrintError(CException* e, LPCSTR file, long lLine);

    //! 显示信息文字
    static void PrintInfo(LPCWSTR pszMsg, LPCSTR file, long lLine, bool bError = false);

    //! 返回斜号分隔的第一部分子串
    static std::wstring GetLevel1Name(LPCWSTR name);

    static bool IsDBName(LPCWSTR name);

    static bool IsSelectSQL(LPCWSTR name);

    //! BOOL值转换为字符'y'或'n'
    static CHAR BoolToChar(BOOL bValue);

    //! 将变量转换为CString，并去掉从数据库读出的多余空格
    static CString GetBSTR(const _variant_t &v, LPCTSTR pszDefault = NULL);

    //! 将变量转换为日期
    static bool GetDate(COleDateTime& dt, const _variant_t &v);

    //! 将变量转换为日期时间
    static bool GetDateTime(COleDateTime& dt, const _variant_t &v);

    //! 转换成含时分秒的时间
    static COleDateTime GetTimeNew(const _variant_t &v);

    //! 将变量转换为整数
    static long GetLong(const _variant_t &v, long lDefault = 0);

    //! 将变量转换为整数
    static short GetShort(const _variant_t &v, short nDefault = 0);

    //! 将变量转换为浮点数
    static double GetDouble(const _variant_t &v, double dDefault = 0.0);

    //! 将字符串变量转换为布尔值，字符串为'y'或'n'
    static BOOL GetBool(const _variant_t &v, BOOL bDefault = FALSE);
};

//! 将字符串变量转换为字符值
inline CHAR GetChar(const _variant_t &v, CHAR cDefault)
{
    CHAR cRet = cDefault;
    if (v.vt != VT_NULL)
    {
        if (NULL != v.bstrVal)
            cRet = (CHAR)v.bstrVal[0];
    }
    return cRet;
}

#define CATCH_DB_STR_ERROR                                  \
    catch (_com_error &e)                                   \
    {                                                       \
        DbFunc::PrintComError(e, __FILE__, __LINE__);       \
    }                                                       \
    catch (CString str)                                     \
    {                                                       \
        if (str.GetLength() > 0)                            \
            DbFunc::PrintInfo(str, __FILE__, __LINE__);     \
    }                                                       \
    catch (CException* e)                                   \
    {                                                       \
        DbFunc::PrintError(e, __FILE__, __LINE__);          \
        e->Delete();                                        \
    }                                                       \
    catch (...)                                             \
    {                                                           \
        DbFunc::PrintInfo(L"Unknown exception", __FILE__, __LINE__, true);  \
    }

#endif // _X3_CONFIGDB_DBFUNC_H
