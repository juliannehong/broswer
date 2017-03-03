#pragma once

#include "ObjectWrapper.h"
#include <Windows.h>

class CThread :
	public ObjectWrapper<IBrThread>
{
	ThreadFunction threadfunc;
	CObjectPtr<IBrEvent> cancel;
	HANDLE thread;

	static UINT CALLBACK ThreadEntry(void* me);

	UINT ThreadEntrypoint();

	//ObjectWrapper<T>
	bool IsIIDValid(BrGuid& iid);

public:
	CThread(ThreadFunction pThreadFunc, bool StartImmediate);
	~CThread();
	
	//IBrThread
	BrResult BRMETHODCALLTYPE Start();
	CObjectPtr<IBrEvent> BRMETHODCALLTYPE GetCancellationEvent();
	BrResult BRMETHODCALLTYPE Cancel();
	BrResult BRMETHODCALLTYPE Terminate(BrResult ExitCode);
	BrResult BRMETHODCALLTYPE GetExitCode();
};

