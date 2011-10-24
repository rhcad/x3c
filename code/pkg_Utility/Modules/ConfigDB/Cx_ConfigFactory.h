// x3c - C++ PluginFramework
#ifndef _X3_CONFIGDB_CONFIGFACTORY_H
#define _X3_CONFIGDB_CONFIGFACTORY_H

#include <Ix_ConfigDBFactory.h>

class Cx_ConfigFactory
    : public Ix_ConfigDBFactory
{
    X3BEGIN_CLASS_DECLARE(Cx_ConfigFactory)
        X3DEFINE_INTERFACE_ENTRY(Ix_ConfigDBFactory)
    X3END_CLASS_DECLARE()
protected:
    Cx_ConfigFactory();
    virtual ~Cx_ConfigFactory();

private:
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
