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

#ifndef _X3_CORE_STRINGTABLE_H
#define _X3_CORE_STRINGTABLE_H

#include <Ix_StringTable.h>

class Cx_StringTable : public Ix_StringTable
{
protected:
    Cx_StringTable();
    ~Cx_StringTable();

private:
    bool GetValue(std::wstring& value, const std::wstring& name, 
        std::wstring& module, std::wstring& id);
    bool GetValue(std::wstring& value, 
        const std::wstring& module, const std::wstring& id);
    long LoadFiles(const std::wstring& path);
    long RegisterFile(const std::wstring& filename);
    std::wstring GetValue(const std::wstring& module, 
        const std::wstring& id, bool* hasvalue = NULL);

private:
    struct ITEM
    {
        std::wstring    module;
        Cx_Ptr          group;  // Ix_ConfigSection
        Cx_Ptr          file;   // Ix_ConfigData
    };
    typedef std::vector<ITEM>::iterator IT_ITEM;

    IT_ITEM Find(const std::wstring& module)
    {
        IT_ITEM it = m_groups.begin();
        for (; it != m_groups.end(); ++it)
        {
            if (StrCmpIW(it->module.c_str(), module.c_str()) == 0)
            {
                break;
            }
        }

        return it;
    }

private:
    std::vector<ITEM>   m_groups;
    bool                m_loaded;
};

#endif // _X3_CORE_STRINGTABLE_H
