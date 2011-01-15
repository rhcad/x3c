// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Changes:
// 2010-01-12, Zhang Yun Gui: Add readonly param in OpenConnection()
//

#ifndef _X3_CONFIGDB_INITDATABASE_INTERFACE_H
#define _X3_CONFIGDB_INITDATABASE_INTERFACE_H

interface Ix_SQLParser;

//! 初始化数据库访问对象的接口
interface Ix_InitDatabase
{
    //! 指定SQL连接串打开数据库
    virtual bool OpenConnection(const std::wstring& wstrConnection, 
        Ix_SQLParser* pSQLParser, bool readonly = false) = 0;
};

#endif // _X3_CONFIGDB_INITDATABASE_INTERFACE_H
