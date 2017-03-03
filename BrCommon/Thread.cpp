#include "Thread.h"
#include <process.h>

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

bool CThread::IsIIDValid(BrGuid & iid)
{
	if(iid == GET_UUID(IBrThread) || iid == GET_UUID(IBrUnknown))
	{
		return true;
	}
	return false;
}

CThread::CThread(ThreadFunction pThreadFunc, bool StartImmediate):
	threadfunc(pThreadFunc),
	cancel(CreateBrEvent(true, false)),
	thread(INVALID_HANDLE_VALUE)
{
	if(StartImmediate)
	{
		Start();
	}
}

CThread::~CThread()
{
	if(thread != INVALID_HANDLE_VALUE)
	{
		Terminate(-10); // TERMINATE_THREAD
	}
	CloseHandle(thread);
}

BrResult CThread::Start()
{
	if(thread != INVALID_HANDLE_VALUE)
	{
		//thread might be running.
		//is it?
		if(GetExitCode() == -4) // STILL_RUNNING
		{
			//we're still running. fail out.
			return -4;
		}
		//nope. We closed. Destroy the thread handle and prep for reinitialize.
		CloseHandle(thread);
		thread = INVALID_HANDLE_VALUE;
	}
	cancel->Reset();
	thread = (HANDLE)_beginthreadex(nullptr, 0, ThreadEntry, this, CREATE_SUSPENDED, nullptr);
	ResumeThread(thread);
	return 0;
}

CObjectPtr<IBrEvent> CThread::GetCancellationEvent()
{
	return cancel;
}

BrResult CThread::Cancel()
{
	cancel->Set();
	return 0; // OK
}

BrResult CThread::Terminate(BrResult ExitCode)
{
	if(thread != INVALID_HANDLE_VALUE)
	{
		TerminateThread(thread, (DWORD)ExitCode);
		return 0; // OK
	}
	return -5; // THREAD_NOT_CREATED
}

BrResult CThread::GetExitCode()
{
	if(thread == INVALID_HANDLE_VALUE)
	{
		return -5; // THREAD_NOT_CREATED
	}
	DWORD ex;
	GetExitCodeThread(thread, &ex);
	if(ex == STILL_ACTIVE)
	{
		return -4; //STILL_RUNNING
	}
	return (BrResult)ex;
}

CObjectPtr<IBrThread> CreateBrThread(ThreadFunction pThreadFunction, bool StartImmediately)
{
	return CObjectPtr<IBrThread>(new CThread(pThreadFunction, StartImmediately), true);
}