// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef _X3_UTILITY_GUIDGENERATOR_H
#define _X3_UTILITY_GUIDGENERATOR_H

#include <Utility/Ix_GuidGenerator.h>

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
