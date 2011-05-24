// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

//! \file LockCount.h
//! \brief 定义自动锁定计数的辅助类 CLockCount

#ifndef UTILFUNC_LOCKCOUNT_H_
#define UTILFUNC_LOCKCOUNT_H_

//! 自动锁定计数的辅助类
/*! 使用本类在函数内定义局部变量，在退出函数析构时自动减少计数。
    在其他函数中就可以通过判断该计数变量是否为初始值而知道是否进入特点状态。
    \ingroup _GROUP_UTILFUNC
*/
class CLockCount
{
public:
    //! 构造函数，自动增加计数
    /*!
        \param p 已有计数变量的地址，该计数变量的初始值一般为0
    */
    CLockCount(long* p) : m_count(p)
    {
        InterlockedIncrement(m_count);
    }

    //! 析构函数，自动减少计数
    ~CLockCount()
    {
        Unlock();
    }

    //! 解除锁定，自动减少计数
    void Unlock()
    {
        if (m_count)
        {
            InterlockedDecrement(m_count);
            m_count = NULL;
        }
    }

private:
    CLockCount(const CLockCount&);
    void operator=(const CLockCount&);

    long*   m_count;
};

#endif // UTILFUNC_LOCKCOUNT_H_
