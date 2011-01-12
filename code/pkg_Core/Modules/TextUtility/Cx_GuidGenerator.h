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

#ifndef _X3_UTILITY_GUIDGENERATOR_H
#define _X3_UTILITY_GUIDGENERATOR_H

#include "Ix_GuidGenerator.h"

class Cx_GuidGenerator : public Ix_GuidGenerator
{
public:
    Cx_GuidGenerator() {}
    virtual ~Cx_GuidGenerator() {}

public:
    // From Ix_GuidGenerator
    virtual std::wstring CreateGuid(bool withBrackets = false);
    virtual std::wstring RemoveGuidBrackets(const std::wstring& uid);
    virtual std::wstring GetCurrentTimeString(bool hasYear = true);
    virtual ULONG CreateID(long type = 0);
};

#endif // _X3_UTILITY_GUIDGENERATOR_H
