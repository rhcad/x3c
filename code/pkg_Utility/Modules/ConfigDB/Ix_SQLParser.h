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

#pragma once

//! 不同数据库提供源的SQL指令的接口
interface Ix_SQLParser
{
    //! 销毁本对象
    virtual void Release() = 0;

    //! 返回当前的系统日期
    virtual std::wstring GetFunc_CURDATE() = 0;

    //! 返回当前的系统时间
    virtual std::wstring GetFunc_CURTIME() = 0;

    //! 返回当前的系统日期和时间
    virtual std::wstring GetFunc_NOW() = 0;
};
