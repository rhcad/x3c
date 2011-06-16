// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#pragma once

//! 不同数据库提供源的SQL指令的接口
class Ix_SQLParser
{
public:
    virtual ~Ix_SQLParser() {}

    //! 销毁本对象
    virtual void Release() = 0;

    //! 返回当前的系统日期
    virtual std::wstring GetFunc_CURDATE() = 0;

    //! 返回当前的系统时间
    virtual std::wstring GetFunc_CURTIME() = 0;

    //! 返回当前的系统日期和时间
    virtual std::wstring GetFunc_NOW() = 0;
};
