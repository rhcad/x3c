//! \file ChainObserverB.h
//! \brief 定义职责链观察者类 ChainObserverB

#ifndef EXAMPLE_CHAINB_OBSERVER_H_
#define EXAMPLE_CHAINB_OBSERVER_H_

#include <ChangeObserver/Cx_ChangeObserver.h>

//! 作为例子的职责链观察者类
/*! 本例子用于让多个派生类都能处理同一个调用，有多种通知函数
    \note 建议派生类从本类私有继承
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
class ChainObserverB : public Cx_ChangeObserver
{
    NOCOPY_CONSTRUCTOR(ChainObserverB);
public:
    //! ChainObserverB 观察者的通知数据类
    class Data : public ChangeNotifyData
    {
        NOCOPY_CONSTRUCTOR(Data);
    public:
        //! 第一种职责链通知
        static bool DoWork1(int value)
        {
            Data data(1, &value, NULL);
            data.Notify();
            return data.ret;
        }

        //! 第二种职责链通知
        static bool DoWork2(char c)
        {
            Data data(2, NULL, &c);
            data.Notify();
            return data.ret;
        }

        int     type;
        bool    ret;
        int*    value;
        char*   c;

    private:
        Data(int _type, int* _value, char* _c)
            : ChangeNotifyData("ChainObserverB")
            , type(_type), ret(false), value(_value), c(_c)
        {
        }
    };

protected:
    ChainObserverB() : Cx_ChangeObserver("ChainObserverB")
    {
    }

    //! 让派生类响应第一种职责链通知
    virtual bool OnChainWork1(int value)
    {
        value; return false;
    }

    //! 让派生类响应第二种职责链通知
    virtual bool OnChainWork2(char c)
    {
        c; return false;
    }

private:
    void DoUpdate(ChangeNotifyData* data)
    {
        Data* mydata = static_cast<Data*>(data);

        switch (mydata->type)
        {
        case 1:
            mydata->ret = OnChainWork1(*(mydata->value)) || mydata->ret;
            break;

        case 2:
            mydata->ret = OnChainWork2(*(mydata->c)) || mydata->ret;
            break;

        default:
            ASSERT(0);
        }
    }
};

#endif // EXAMPLE_CHAINB_OBSERVER_H_
