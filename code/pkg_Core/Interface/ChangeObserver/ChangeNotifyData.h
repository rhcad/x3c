/*! \file ChangeNotifyData.h
 *  \brief 定义改变通知消息数据基类 ChangeNotifyData 和 ChangeObserver
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_OBSERVER_CHANGENOTIFYDATA_H_
#define X3_OBSERVER_CHANGENOTIFYDATA_H_

#include "XComPtr.h"
#include "Ix_ChangeManager.h"

//! 改变通知消息数据的基类
/*!
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see ChangeObserver
*/
class ChangeNotifyData
{
protected:
    //! 构造函数，由派生数据类传入type(唯一标识)
    ChangeNotifyData(const char* type) : m_type(type)
    {
    }

public:
    //! 广播改变通知
    void Notify()
    {
        Cx_Interface<Ix_ChangeManager> pIFManager(CLSID_ChangeManager);
        if (pIFManager.IsNotNull())
        {
            pIFManager->ChangeNotify(m_type, this);
        }
    }

    //! 返回改变通知类型
    const char* GetChangeType() const
    {
        return m_type;
    }

    //! 析构函数(以便可动态转换为具体类型)
    virtual ~ChangeNotifyData()
    {
    }

private:
    ChangeNotifyData();
    const char*     m_type;
};

//! 改变通知观察者基类
/*! 具体一种改变通知观察者类需要实现 DoUpdate() 私有函数
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see ChangeNotifyData
*/
class ChangeObserver : public Ix_ChangeObserver
{
private:
    //! 分发改变通知，由具体改变通知观察者类实现
    /*!
        \param data 通知参数，为一个局部变量的地址，可动态转换为具体类型
    */
    virtual void DoUpdate(ChangeNotifyData* data) = 0;

protected:
    //! 构造函数，由派生观察者类传入type(唯一标识)
    ChangeObserver(const char* type, bool register_now = true)
        : m_type(type), m_times(0)
    {
        if (register_now)
        {
            RegisterObserver();
        }
    }

    //! 返回改变通知类型
    const char* GetChangeType() const
    {
        return m_type;
    }

    //! 返回是否正在执行改变通知的分发过程
    bool IsUpdating() const
    {
        return m_times != 0;
    }

    //! 注册观察者
    void RegisterObserver()
    {
        Cx_Interface<Ix_ChangeManager> pIFManager(CLSID_ChangeManager);
        if (pIFManager.IsNotNull())
        {
            pIFManager->RegisterObserver(GetChangeType(), this);
        }
    }

public:
    //! 析构函数
    virtual ~ChangeObserver()
    {
        Cx_Interface<Ix_ChangeManager> pIFManager(CLSID_ChangeManager);
        if (pIFManager.IsNotNull())
        {
            pIFManager->UnRegisterObserver(GetChangeType(), this);
        }
    }

private:
    void Update(ChangeNotifyData* data)
    {
        //ASSERT(data && 0 == strcmp(data->GetChangeType(), GetChangeType()));
        ++m_times;
        DoUpdate(data);
        --m_times;
    }

private:
    ChangeObserver();
    const char* m_type;
    long        m_times;
};

#endif // X3_OBSERVER_CHANGENOTIFYDATA_H_
