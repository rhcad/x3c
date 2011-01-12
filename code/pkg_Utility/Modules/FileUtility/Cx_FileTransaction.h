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

#ifndef _X3_UTILITY_FILETRANSACTION_H
#define _X3_UTILITY_FILETRANSACTION_H

#include "Ix_FileTransaction.h"

class Cx_FileTransaction : public Ix_FileTransaction
{
public:
    Cx_FileTransaction();
    virtual ~Cx_FileTransaction();

public:
    // From Ix_FileTransaction
    virtual void Rollback();
    virtual long GetLevel() const;
    virtual bool IsRollbacking() const;
    virtual bool DeletePathFile(LPCWSTR pszFileName, bool bRecycle = false);

private:
    long        m_lLevel;
};

#endif // _X3_UTILITY_FILETRANSACTION_H
