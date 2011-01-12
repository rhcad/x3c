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

#ifndef _X3_UTILITY_TEMPFOLDER_H
#define _X3_UTILITY_TEMPFOLDER_H

#include "Ix_TempFolder.h"

class Cx_TempFolder : public Ix_TempFolder
{
public:
    Cx_TempFolder();
    virtual ~Cx_TempFolder();

    static void DeleteFolders();

public:
    // From Ix_TempFolder
    virtual void SetRootPath(const std::wstring& wstrPath);
    virtual bool DeleteFolder();
    virtual std::wstring CreateFolder(const std::wstring& wstrPrefix);
    virtual std::wstring GetPath() const;
    virtual std::wstring CreateFileName(const std::wstring& wstrPrefix, 
        const std::wstring& wstrExtName);

private:
    std::wstring    m_wstrPath;
    std::wstring    m_wstrRootPath;
    static std::vector<std::wstring> c_arrToDel;
};

#endif // _X3_UTILITY_TEMPFOLDER_H
