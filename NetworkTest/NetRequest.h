#pragma once
#include "NetTest.h"
#include <ObjectWrapper.h>

class CNetRequest :
	public ObjectWrapper<INetRequest>
{
	CompletionHandler callback;
	CObjectPtr<IBrThread> iothread;
	CObjectPtr<IBrEvent> complete;


	BrResult ThreadFunc(CObjectPtr<IBrThread> pThread);

	bool IsIIDValid(BrGuid& riid);

public:
	CNetRequest(char* url);
	~CNetRequest();

	BrResult BRMETHODCALLTYPE Start(CompletionHandler pcallback = nullptr);
	BrResult BRMETHODCALLTYPE WaitForCompletion();
	void* BRMETHODCALLTYPE GetResultData();
};

