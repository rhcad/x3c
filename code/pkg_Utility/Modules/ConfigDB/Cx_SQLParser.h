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

#ifndef _X3_CONFIGDB_SQLPARSER_H
#define _X3_CONFIGDB_SQLPARSER_H

#include "Ix_SQLParser.h"

class SQLParser_Access : public Ix_SQLParser
{
public:
    SQLParser_Access()
    {
    }

    void Release()
    {
        delete this;
    }

    std::wstring GetFunc_CURDATE()
    {
        return L"Date()";
    }

    std::wstring GetFunc_CURTIME()
    {
        return L"Time()";
    }

    std::wstring GetFunc_NOW()
    {
        return L"Now()";
    }
};

class SQLParser_SQLServer : public Ix_SQLParser
{
public:
    SQLParser_SQLServer()
    {
    }

    void Release()
    {
        delete this;
    }

    std::wstring GetFunc_CURDATE()
    {
        return L"GetDate()";
    }

    std::wstring GetFunc_CURTIME()
    {
        return L"GetTime()";
    }

    std::wstring GetFunc_NOW()
    {
        return L"GetNow()";
    }
};

#endif // _X3_CONFIGDB_SQLPARSER_H
