#pragma once
#include "NetTest.h"
#include <boost\thread.hpp>

class CNetRequest :
	public INetRequest
{

	int ThreadEntry();

public:
	CNetRequest(char* url);
	~CNetRequest();

	int Start(CompletionHandler pcallback = nullptr);
	int WaitForCompletion();
	void* GetResultData();
};

