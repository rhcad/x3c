// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Changes:
// 2010-01-12, Zhang Yun Gui: Add readonly param in OpenConnection()
// 2011.06.30: Remove RTTI.

#ifndef _X3_CONFIGDB_INITDATABASE_INTERFACE_H
#define _X3_CONFIGDB_INITDATABASE_INTERFACE_H

class Ix_SQLParser;

//! 初始化数据库访问对象的接口
class Ix_InitDatabase : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_InitDatabase)

    //! 指定SQL连接串打开数据库
    virtual bool OpenConnection(const std::wstring& wstrConnection, 
        Ix_SQLParser* pSQLParser, bool readonly = false) = 0;
};

#endif // _X3_CONFIGDB_INITDATABASE_INTERFACE_H
