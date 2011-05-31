#pragma once

#include "NodeSelectionObserver.h"

class CNodeSelectionTestOnlyReceive : private NodeSelectionObserver
{
    NOCOPY_CONSTRUCTOR(CNodeSelectionTestOnlyReceive);
public:
    CNodeSelectionTestOnlyReceive()
    {
    }

private:
    virtual void OnNodeSelection(long objid, NodeSelectionObserver* sender)
    {
        objid; sender;
    }
};

class CNodeSelectionTestSendReceive : private NodeSelectionObserver
{
    NOCOPY_CONSTRUCTOR(CNodeSelectionTestSendReceive);
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
    virtual void OnNodeSelection(long objid, NodeSelectionObserver* sender)
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
