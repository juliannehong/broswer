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

bool BrEvent::WaitForSignal(U32 msTimeout)
{
	DWORD ret = WaitForSingleObject(e, msTimeout);
	if(ret == WAIT_FAILED || ret == WAIT_TIMEOUT)
	{
		return false;
	}
	return true;
}

CObjectPtr<IBrEvent> CreateBrEvent(bool ManualReset, bool InitialState)
{
	return CObjectPtr<IBrEvent>(new BrEvent(ManualReset, InitialState), true);
}

bool COMMONAPI_ENTRY WaitForEvents(CObjectPtr<IBrEvent>* pEvents, U32 NumEvents, U32 & SignaledEvent, bool WaitForAll, U32 msTimeout)
{
	HANDLE* h = (HANDLE*)malloc(sizeof(HANDLE)* NumEvents); //TODO - REPLACE THIS WITH PRIVATE ALLOCATOR FOR MEMORY ISOLATION
	for(U32 i = 0; i < NumEvents; ++i)
	{
		h[i] = ((BrEvent*)(pEvents[i].GetInterface()))->GetEventHandle();
	}
	DWORD ret = WaitForMultipleObjects(NumEvents, h, WaitForAll == true ? TRUE : FALSE, msTimeout);
	if(ret == WAIT_FAILED || ret == WAIT_TIMEOUT)
	{
		return false;
	}
	SignaledEvent = ret - WAIT_OBJECT_0;
	return true;
}