#include "Thread.h"

struct ThreadException
{
	U32 code;
};

UINT CThread::ThreadEntry(void * me)
{
	if(!me)
	{
		//This should never happen. If it does, fail out.
		if(IsDebuggerPresent())
		{
			__debugbreak();
		}
		ExitProcess(DBG_TERMINATE_PROCESS);
	}
	return ((CThread*)me)->ThreadEntrypoint();
}

UINT CThread::ThreadEntrypoint()
{
	//Call the user's thread function here - pass this to the function as well.
	//Should allow them to check for cancellation.
	//First check to see if the event is signaled.
	if(cancel->IsSet())
	{
		//we canceled before we got the chance to run. Oh well. cancel the thread.
		return 0;
	}
	//Nope. Call the thread function.
	return threadfunc(CObjectPtr<IBrThread>(this));
}


CThread::CThread(ThreadFunction pThreadFunc, bool StartImmediate):
	threadfunc(pThreadFunc),
	cancel(CreateBrEvent(false,false)),
	thread(INVALID_HANDLE_VALUE)
{
	if(StartImmediate)
	{
		Start();
	}
}

CThread::~CThread()
{
}

bool CThread::IsIIDValid(BrGuid & iid)
{
	if(iid == GET_UUID(IBrThread) || iid == GET_UUID(IBrUnknown))
	{
		return true;
	}
	return false;
}

CObjectPtr<IBrThread> CreateBrThread(ThreadFunction pThreadFunction, bool StartImmediately)
{
	CObjectPtr<IBrThread> t;
	try
	{
		t = CObjectPtr<IBrThread>(new CThread(pThreadFunction, StartImmediately), true);
	}
	catch(ThreadException e)
	{
		return nullptr;
	}
	return t;
}