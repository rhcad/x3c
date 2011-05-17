#pragma once

#include "NodeSelectionObserver.h"

class CNodeSelectionTestOnlyReceive : private NodeSelectionObserver
{
public:
    CNodeSelectionTestOnlyReceive()
    {
    }

private:
    virtual void OnNodeSelection(long objid, void* sender)
    {
        objid; sender;
    }
};

class CNodeSelectionTestSendReceive : private NodeSelectionObserver
{
public:
    CNodeSelectionTestSendReceive()
    {
    }

    void OnChanged()
    {
        if (!NodeSelectionObserver::IsUpdating())
        {
            long objid = 1234;
            RefreshView(objid);
            NodeSelectionObserver::Data(objid, this).Notify();
        }
    }

private:
    virtual void OnNodeSelection(long objid, void* sender)
    {
        if (this != sender)
        {
            OnChanged();
            RefreshView(objid);
        }
    }

    void RefreshView(long objid)
    {
        objid;
    }
};
