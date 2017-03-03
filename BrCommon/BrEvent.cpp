#include "BrEvent.h"



bool BrEvent::IsIIDValid(BrGuid & riid)
{
	if(riid == GET_UUID(IBrEvent) || riid == GET_UUID(IBrUnknown))
	{
		return true;
	}
	return false;
}

BrEvent::BrEvent(bool ManualReset, bool InitialState) :
	e(CreateEvent(nullptr, ManualReset, InitialState, nullptr))
{
}


BrEvent::~BrEvent()
{
	CloseHandle(e);
}

bool BrEvent::IsSet()
{
	DWORD ret = WaitForSingleObject(e, 0);
	return ret == WAIT_OBJECT_0;
}

void BrEvent::Set()
{
	SetEvent(e);
}

void BrEvent::Reset()
{
	ResetEvent(e);
}


CObjectPtr<IBrEvent> CreateBrEvent(bool ManualReset, bool InitialState)
{
	return CObjectPtr<IBrEvent>(new BrEvent(ManualReset, InitialState), true);
}