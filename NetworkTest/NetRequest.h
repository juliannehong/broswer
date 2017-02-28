#pragma once
#include "NetTest.h"
class CNetRequest :
	public INetRequest
{



public:
	CNetRequest(char* url);
	~CNetRequest();

	int Start(CompletionHandler pcallback = nullptr);
	int WaitForCompletion();
	void* GetResultData();
};

