#pragma once

#include "NodeSelectionObserver.h"

class CNodeSelectionTestOnlyReceive : private NodeSelectionObserver
{
public:
	CNodeSelectionTestOnlyReceive()
	{
	}

private:
	virtual void OnNodeSelection(ULONG objid, void* sender)
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
			ULONG objid = 1234;
			RefreshView(objid);
			NodeSelectionObserver::Data(objid, this).Notify();
		}
	}

private:
	virtual void OnNodeSelection(ULONG objid, void* sender)
	{
		if (this != sender)
		{
			OnChanged();
			RefreshView(objid);
		}
	}

	void RefreshView(ULONG objid)
	{
		objid;
	}
};
