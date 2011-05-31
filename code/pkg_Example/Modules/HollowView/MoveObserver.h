#ifndef EXAMPLE_MOVE_OBSERVER_H_
#define EXAMPLE_MOVE_OBSERVER_H_

#include <ChangeObserver/ChangeNotifyData.h>
#include <typeinfo>

class MoveObserver : public ChangeObserver
{
    NOCOPY_CONSTRUCTOR(MoveObserver);
public:
    class Data : public ChangeNotifyData
    {
        NOCOPY_CONSTRUCTOR(Data);
    public:
        Data(long _x, long _y, MoveObserver* _sender)
            : ChangeNotifyData(typeid(MoveObserver).name())
            , x(_x), y(_y), sender(_sender)
        {
        }

        long    x;
        long    y;
        MoveObserver*   sender;
    };

protected:
    MoveObserver() : ChangeObserver(typeid(MoveObserver).name())
    {
    }

    virtual void OnMove(long x, long y, MoveObserver* sender)
    {
        x; y; sender;
    }

private:
    void DoUpdate(ChangeNotifyData* data)
    {
        Data* mydata = dynamic_cast<Data*>(data);
        ASSERT(mydata);
        OnMove(mydata->x, mydata->y, mydata->sender);
    }
};

#endif // EXAMPLE_MOVE_OBSERVER_H_
