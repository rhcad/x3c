// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef _X3_CONFIGDB_SQLPARSER_H
#define _X3_CONFIGDB_SQLPARSER_H

#include "Ix_SQLParser.h"

class SQLParser_Access : public Ix_SQLParser
{
public:
    SQLParser_Access()
    {
    }

    void InterfaceRelease()
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

    void InterfaceRelease()
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
