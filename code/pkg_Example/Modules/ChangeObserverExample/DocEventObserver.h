//! \file DocEventObserver.h
//! \brief 定义文档事件观察者类 DocEventObserver

#ifndef EXAMPLE_DOCEVENT_OBSERVER_H_
#define EXAMPLE_DOCEVENT_OBSERVER_H_
#pragma once

#include <ChangeNotifyData.h>
#include <typeinfo>

//! 文档事件类型
enum kDocEventType
{
    kDocEvent_BeforeOpen,       //!< 文档打开之前
    kDocEvent_AfterOpen,        //!< 文档打开之后
    kDocEvent_OpenFail,         //!< 文档打开失败
};

//! 作为例子的文档事件观察者类
/*! 本例子用于让派生类都能响应多个事件通知
    \note 建议派生类从本类私有继承
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
class DocEventObserver : public ChangeObserver
{
public:
    //! DocEventObserver 观察者的通知数据类
    class Data : public ChangeNotifyData
    {
    public:
        Data(kDocEventType _event)
            : ChangeNotifyData(typeid(DocEventObserver).name()), event(_event)
        {
        }

        kDocEventType event;
    };

protected:
    DocEventObserver() : ChangeObserver(typeid(DocEventObserver).name())
    {
    }

    //! 响应文档打开之前的通知
    virtual void OnDocEventBeforeOpen() {}

    //! 响应文档打开之后的通知
    virtual void OnDocEventAfterOpen() {}

    //! 响应文档打开失败的通知
    virtual void OnDocEventOpenFail() {}

private:
    void DoUpdate(ChangeNotifyData* data)
    {
        Data* mydata = dynamic_cast<Data*>(data);
        ASSERT(mydata);
        
        switch (mydata->event)
        {
        case kDocEvent_BeforeOpen:
            OnDocEventBeforeOpen();
            break;

        case kDocEvent_AfterOpen:
            OnDocEventAfterOpen();
            break;

        case kDocEvent_OpenFail:
            OnDocEventOpenFail();
            break;

        default:
            ASSERT(FALSE);
        }
    }
};

#endif // EXAMPLE_DOCEVENT_OBSERVER_H_
