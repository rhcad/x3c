//! \file NodeSelectionObserver.h
//! \brief 定义节点选择改变观察者类 NodeSelectionObserver

#ifndef EXAMPLE_NODESELECTION_OBSERVER_H_
#define EXAMPLE_NODESELECTION_OBSERVER_H_
#pragma once

#include <ChangeNotifyData.h>
#include <typeinfo>

//! 作为例子的节点选择改变观察者类
/*! 本例子用于让派生类都响应节点变化，并可避免连锁循环变化
    \note 建议派生类从本类私有继承
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
class NodeSelectionObserver : public ChangeObserver
{
public:
    //! NodeSelectionObserver 观察者的通知数据类
    class Data : public ChangeNotifyData
    {
    public:
        Data(ULONG _objid, NodeSelectionObserver* _sender)
            : ChangeNotifyData(typeid(NodeSelectionObserver).name())
            , objid(_objid), sender(_sender)
        {
        }

        ULONG   objid;
        void*   sender;
    };

protected:
    NodeSelectionObserver() : ChangeObserver(typeid(NodeSelectionObserver).name())
    {
    }

    //! 让派生类响应节点选择改变通知
    virtual void OnNodeSelection(ULONG objid, void* sender)
    {
        objid; sender;
    }

private:
    void DoUpdate(ChangeNotifyData* data)
    {
        Data* mydata = dynamic_cast<Data*>(data);
        ASSERT(mydata);
        OnNodeSelection(mydata->objid, mydata->sender);
    }
};

#endif // EXAMPLE_NODESELECTION_OBSERVER_H_
