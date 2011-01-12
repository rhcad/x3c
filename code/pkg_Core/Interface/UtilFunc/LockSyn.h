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

//! \file LockSyn.h
//! \brief 定义同步控制的辅助类 CLockCs 和 CLockRW

#ifndef UTILFUNC_LOCKSYN_H_
#define UTILFUNC_LOCKSYN_H_

class CLockCs;
class CReaderWriterLock;
class CLockRW;

//! 对临界区自动锁定和解锁的辅助类
/*! 临界区变量可以用 CLockCs::CS 来定义.
    使用本类在函数中定义局部变量，超出函数作用范围后自动解锁
    \ingroup _GROUP_UTILFUNC
*/
class CLockCs
{
public:
    //! 临界区类型
    struct CS : public CRITICAL_SECTION
    {
        //! 构造函数, 初始化临界区
        CS()
        {
#if (_WIN32_WINNT >= 0x0403)
            InitializeCriticalSectionAndSpinCount(this, 400);
#else
            InitializeCriticalSection(this);
#endif
        }
        
        //! 析构函数, 销毁临界区
        ~CS()
        {
            DeleteCriticalSection(this);
        }
    };
    
public:
    //! 构造函数，自动进入临界区
    /*!
        \param pCs 临界区变量的地址，为NULL时本类将不起作用
        \param bTry 是否仅尝试进入临界区而不等待，默认为false表示要等待进入
            临界区；true表示如果临界区被其他线程锁定时将仅尝试锁定而不等待，
            此时必须用 IsLocked() 函数检查是否进入了临界区。
    */
    CLockCs(CRITICAL_SECTION* pCs, bool bTry = false) : m_pcs(pCs)
    {
        if (NULL == m_pcs)
            return;

        try
        {
#if (_WIN32_WINNT >= 0x0400)
            if (bTry)
            {
                if (!::TryEnterCriticalSection(m_pcs))
                    m_pcs = NULL;
            }
            else
                ::EnterCriticalSection(m_pcs);
#else
            bTry;
            ::EnterCriticalSection(m_pcs);
#endif
        }
        catch (...)
        {
            m_pcs = NULL;
        }
    }

    //! 析构函数，自动离开临界区
    ~CLockCs()
    {
        Unlock();
    }

    //! 离开临界区
    void Unlock()
    {
        if (m_pcs != NULL)
        {
            ::LeaveCriticalSection(m_pcs);
            m_pcs = NULL;
        }
    }

    //! 返回是否已进入临界区
    bool IsLocked() const
    {
        return m_pcs != NULL;
    }

private:
    CRITICAL_SECTION*   m_pcs;
};

//! 定义支持单个写线程和多个读线程的锁
/*!
    使用本类定义线程锁管理对象，要锁定时使用 CLockRW 在函数中定义局部变量
    \ingroup _GROUP_UTILFUNC
    \see CLockRW
*/
class CReaderWriterLock
{
public:
    //! 构造函数, 需要再用 Init() 初始化本对象
    CReaderWriterLock()
        : hWriteWaiting(NULL), hMutex(NULL), hDataLock(NULL)
        , nReadCount(0), nWriterSeqNum(0)
    {
    }
    
    //! 析构函数
    ~CReaderWriterLock()
    {
        if (NULL != hDataLock)
            ::CloseHandle(hDataLock);
        if (NULL != hMutex)
            ::CloseHandle(hMutex);
        if (NULL != hWriteWaiting)
            ::CloseHandle(hWriteWaiting);
    }
    
    //! 初始化本对象
    bool Init()
    {
        if (NULL != hMutex)     // 已经初始化
            return true;
        
        // 创建二值信号量: 最初未被拥有，最多仅一个线程可锁定它
        hDataLock = ::CreateSemaphore(NULL, 1, 1, NULL);
        if (NULL != hDataLock)
        {
            // 创建二值信号量，用于声明正等待写
            hWriteWaiting = ::CreateSemaphore(NULL, 1, 1, NULL);
            if (NULL == hWriteWaiting)
            {
                ::CloseHandle(hDataLock);
                hDataLock = NULL;
            }
            else
            {
                hMutex = ::CreateMutex(NULL, false, NULL);  // 创建互斥量
                if (NULL == hMutex)
                {
                    ::CloseHandle(hDataLock);
                    hDataLock = NULL;
                    ::CloseHandle(hWriteWaiting);
                    hWriteWaiting = NULL;
                }
            }
        }
        
        return (NULL != hMutex);
    }
    
    //! 返回是否初始化
    bool IsInited() const
    {
        return (NULL != hMutex);
    }
    
    //! 获取读线程锁, 供 CLockRW 构造函数使用, 不建议直接调用
    /*!
        \param nMaxWait 获取锁的等待极限时间，毫秒
        \return 是否执行成功
    */
    bool _AcquireReaderLock(DWORD nMaxWait = 5000)
    {
        bool bRet;
        
        // 如果正等待写，就挂起新的读操作
        bRet = Wait(hWriteWaiting, nMaxWait);
        if (bRet)                                       // 没有等待写的
            ::ReleaseSemaphore(hWriteWaiting, 1, NULL);
        
        if (bRet && Wait(hMutex, nMaxWait))         // 锁定互斥量
        {
            // 增加读计数. 如果是第一个读操作则禁止写
            if (1 == InterlockedIncrement(&nReadCount))
            {
                bRet = Wait(hDataLock, nMaxWait);       // 禁止写
                if (!bRet)                              // 超时，正在写
                    InterlockedDecrement(&nReadCount);
            }
            
            ::ReleaseMutex(hMutex);                     // 解除互斥量锁定
        }
        else
            bRet = false;               // 超时，前一读者正等待写的完成
        
        return bRet;
    }
    
    //! 释放读线程锁, 供 CLockRW 使用, 不建议直接调用
    /*!
        \return 是否执行成功
    */
    bool _ReleaseReaderLock()
    {
        bool bRet = false;
        LONG lPrevCount;
        
        if (Wait(hMutex))                               // 锁定互斥量
        {
            bRet = true;
            if (0 == InterlockedDecrement(&nReadCount)) // 减少读计数，没有读操作了
                bRet = ::ReleaseSemaphore(hDataLock, 1, &lPrevCount);   // 允许写
            ::ReleaseMutex(hMutex);                     // 解除互斥量锁定
        }
        
        return bRet;
    }
    
    //! 获取写线程锁, 供 CLockRW 构造函数使用, 不建议直接调用
    /*!
        \param nMaxWait 获取锁的等待极限时间，毫秒
        \return 是否执行成功
    */
    bool _AcquireWriterLock(DWORD nMaxWait = 15000)
    {
        bool bRet = Wait(hWriteWaiting, nMaxWait);

        if (bRet)                                       // 声明正等待写
        {
            bRet = Wait(hDataLock, nMaxWait);           // 禁止读和再写
            if (bRet)
            {
                InterlockedIncrement(&nWriterSeqNum);   // 获取写锁时增加序列号
            }
            ::ReleaseSemaphore(hWriteWaiting, 1, NULL);
        }

        return bRet;
    }
    
    //! 释放写线程锁, 供 CLockRW 使用, 不建议直接调用
    /*!
        \param bCancelWriterSeq 是否取消序列号的增加，_AcquireWriterLock会自动增加序列号
        \return 是否执行成功
    */
    bool _ReleaseWriterLock(bool bCancelWriterSeq = false)
    {
        bool bRet;
        LONG lPrevCount;
        
        if (bCancelWriterSeq)
        {
            InterlockedDecrement(&nWriterSeqNum);       // 取消序列号的增加
        }
        bRet = ::ReleaseSemaphore(hDataLock, 1, &lPrevCount);   // 允许读写
#ifdef TRACE0
        if (0 != lPrevCount)
        {
            TRACE0("ReleasingWriteLock - Semaphore was not locked!\n");
        }
#endif
        
        return bRet;
    }

    //! 将读线程锁升级为写线程锁，失败时已释放读线程锁
    /*! 本函数供 CLockRW 的同名函数使用, 不建议直接调用
        \param nMaxWait 获取写锁的等待极限时间，毫秒
        \return 是否执行成功
    */
    bool _UpgradeToWriterLock(DWORD nMaxWait = 15000)
    {
        bool bRet = Wait(hWriteWaiting, nMaxWait);      // 禁止新的读写

        _ReleaseReaderLock();                           // 释放读线程锁

        if (bRet)                                       // 已禁止新的读写
        {
            bRet = Wait(hDataLock, nMaxWait);           // 获取写线程锁
            if (bRet)
            {
                InterlockedIncrement(&nWriterSeqNum);   // 获取写锁时增加序列号
            }
            ::ReleaseSemaphore(hWriteWaiting, 1, NULL);
        }

        return bRet;
    }

    //! 将线程的锁状态还原为调用 _UpgradeToWriterLock 前的状态，失败时未释放锁
    /*! 本函数供 CLockRW 的同名函数使用, 不建议直接调用
        \param nMaxWait 获取读锁的等待极限时间，毫秒
        \return 是否执行成功
    */
    bool _DowngradeFromWriterLock(DWORD nMaxWait = 15000)
    {
        bool bRet;

        bRet = Wait(hMutex, nMaxWait);                  // 锁定读计数互斥量
        if (bRet)
        {
            VERIFY(1 == InterlockedIncrement(&nReadCount)); // 增加读计数
            ::ReleaseMutex(hMutex);                     // 解除互斥量锁定
        }

        return bRet;
    }
    
    //! 指示当前线程是否持有读线程锁
    bool IsReaderLockHeld() const
    {
        return (nReadCount > 0);
    }
    
    //! 指示当前线程是否持有写线程锁
    bool IsWriterLockHeld() const
    {
        DWORD dwResult;
        
        // 第一个读操作可能在等待解除锁定，但多个则不能写
        if (nReadCount > 1)
        {
            return false;
        }
        
        dwResult = ::WaitForSingleObject(hDataLock, 0); // 锁定读写
        if (WAIT_TIMEOUT == dwResult)                   // 还没有读或写锁定
        {
            return true;
        }
        
        dwResult = ReleaseSemaphore(hDataLock, 1, NULL);    // 还原
#ifdef TRACE0
        if (0 == dwResult)                                  // 失败
        {
            TRACE0("IsWriterLockHeld - ReleaseSemaphore failed\n");
        }
#endif
        return false;
    }

    //! 得到当前写序列号
    LONG GetWriterSeqNum() const
    {
        return nWriterSeqNum;
    }

    //! 指示获取序列号之后是否已将写线程锁授予某个线程
    /*!
        \param nSecNum 上次获得锁时从GetWriterSeqNum()取的序列号
        \return 是否已被其他写线程增加了序列号
    */
    bool AnyWritersSince(LONG nSecNum) const
    {
        return nWriterSeqNum > nSecNum;
    }
    
    //! 等待并锁定互斥量或信号量
    /*!
        \param hObject 同步对象句柄，互斥量或信号量
        \param nMaxWait 锁定的等待极限时间，毫秒
        \return 是否执行成功
    */
    static bool Wait(HANDLE hObject, DWORD nMaxWait = 5000)
    {
        DWORD dwResult = ::WaitForSingleObject(hObject, nMaxWait);
#ifdef TRACE0
        if (WAIT_OBJECT_0 != dwResult)
        {
            TRACE0("Wait - forgot to call release?\n");
        }
#endif
        
        return (WAIT_OBJECT_0 == dwResult);
    }

private:
    HANDLE  hMutex;         // 互斥量，用于互斥更新读计数
    HANDLE  hDataLock;      // 二值信号量，用于写时不能读和再写，读时不能写
    LONG    nReadCount;     // 读计数，写锁定时允许为0或1
    HANDLE  hWriteWaiting;  // 二值信号量，用于声明正等待写
    LONG    nWriterSeqNum;  // 当前写序列号
};

//! 读写锁类，共享读和独占写的锁定辅助类
/*!
    使用本类在函数中定义局部变量，超出函数作用范围后自动解锁
    \ingroup _GROUP_UTILFUNC
*/
class CLockRW
{
public:
    //! 构造函数，自动获取线程锁
    /*!
        \param data 线程锁管理对象
        \param bWriter true: 独占写, false: 共享读
        \param nMaxWait 获取锁的等待极限时间，毫秒，为 0 时取默认值
    */
    CLockRW(CReaderWriterLock& data, bool bWriter, DWORD nMaxWait = 0)
        : m_pData(NULL), m_bWriter(bWriter), m_bCancelWriterSeq(false)
    {
        if (data.IsInited())
        {
            if (0 == nMaxWait)
            {
                if (bWriter && data._AcquireWriterLock()
                    || !bWriter && data._AcquireReaderLock())
                {
                    m_pData = &data;
                }
            }
            else
            {
                if (bWriter && data._AcquireWriterLock(nMaxWait)
                    || !bWriter && data._AcquireReaderLock(nMaxWait))
                {
                    m_pData = &data;
                }
            }
        }
    }

    //! 析构函数，自动释放线程锁
    ~CLockRW()
    {
        Unlock();
    }

    //! 释放线程锁
    void Unlock()
    {
        if (m_pData != NULL)
        {
            if (m_bWriter)
            {
                m_pData->_ReleaseWriterLock(m_bCancelWriterSeq);
            }
            else
            {
                m_pData->_ReleaseReaderLock();
            }
            m_pData = NULL;
        }
    }

    //! 返回是否已获取线程锁
    bool IsLocked() const
    {
        return (m_pData != NULL);
    }

    //! 返回线程锁管理对象
    CReaderWriterLock* GetData()
    {
        return m_pData;
    }

    //! 释放写锁时取消写序列号的增加
    void CancelWriterSeq()
    {
        m_bCancelWriterSeq = true;
    }

    //! 将读线程锁升级为写线程锁，失败时已释放读线程锁
    /*!
        \param nMaxWait 获取写锁的等待极限时间，毫秒
        \return 是否执行成功
    */
    bool UpgradeToWriterLock(DWORD nMaxWait = 15000)
    {
        ASSERT(m_pData != NULL);

        bool bRet = m_bWriter;

        if (!m_bWriter)
        {
            bRet = m_pData && m_pData->_UpgradeToWriterLock(nMaxWait);
            if (bRet)
            {
                m_bWriter = true;
            }
            else
            {
                m_pData = NULL;
            }
        }

        return bRet;
    }

    //! 将线程的锁状态还原为调用 _UpgradeToWriterLock 前的状态，失败时未释放锁
    /*!
        \param nMaxWait 获取读锁的等待极限时间，毫秒
        \return 是否执行成功
    */
    bool DowngradeFromWriterLock(DWORD nMaxWait = 15000)
    {
        ASSERT(m_pData != NULL);

        bool bRet = !m_bWriter;

        if (m_bWriter)
        {
            bRet = m_pData && m_pData->_DowngradeFromWriterLock(nMaxWait);
            if (bRet)
            {
                m_bWriter = false;
            }
        }

        return bRet;
    }

private:
    CReaderWriterLock*  m_pData;
    bool                m_bWriter;
    bool                m_bCancelWriterSeq;
};

#endif // UTILFUNC_LOCKSYN_H_
