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

#ifndef _X3_CONFIGDB_CONFIGFACTORY_H
#define _X3_CONFIGDB_CONFIGFACTORY_H

#include <Ix_ConfigDBFactory.h>

class Cx_ConfigFactory
    : public Ix_ConfigDBFactory
{
public:
    Cx_ConfigFactory();
    virtual ~Cx_ConfigFactory();

protected:
    // From Ix_ConfigDBFactory
    //
    virtual Cx_Ptr OpenAccessDB(
        const std::wstring& filename, 
        const std::wstring& user = L"", 
        const std::wstring& password = L"");
    virtual Cx_Ptr OpenSQLServerDB(
        const std::wstring& server, 
        const std::wstring& database, 
        const std::wstring& user = L"", 
        const std::wstring& password = L"");
};

#endif // _X3_CONFIGDB_CONFIGFACTORY_H
