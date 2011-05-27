/*! \file LockCount.h
 *  \brief Define helper class to auto increment and decrement: CLockCount
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.5.19
 */
#ifndef UTILFUNC_LOCKCOUNT_H_
#define UTILFUNC_LOCKCOUNT_H_

//! Helper class to auto increment and decrement.
/*! Use this to declare local variable in functions,
    then counter will be auto decreased (--counter;) when leave from the function.
    So you can check the counter with initial value to known some status.
    \ingroup _GROUP_UTILFUNC
*/
class CLockCount
{
public:
    //! Auto add counter.
    /*!
        \param p address of counter, the initial value of counter is usually zero.
    */
    CLockCount(long* p) : m_count(p)
    {
        InterlockedIncrement(m_count);
    }

    //! Auto decrease counter.
    ~CLockCount()
    {
        Unlock();
    }

    //! Auto decrease counter.
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
