// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef _X3_CONFIGDB_CONFIGFACTORY_H
#define _X3_CONFIGDB_CONFIGFACTORY_H

#include <Xml/Ix_ConfigDBFactory.h>

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
