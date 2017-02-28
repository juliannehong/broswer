#pragma once
//Network test API.

//-----------------------------------------
// Move this to a PIL library eventually.
// This is currently Windows specific!
//-----------------------------------------
#define API_EXPORT __declspec(dllexport)
#define API_IMPORT __declspec(dllimport)


#ifdef NETWORKTEST_EXPORTS
#define NETAPI_ENTRY API_EXPORT
#else
#define NETAPI_ENTRY API_IMPORT
#endif

#include <functional>

typedef std::function<int(int ResultCode)> CompletionHandler;

//use COM to hide the implementation details.
struct INetRequest
{
	virtual int Start(CompletionHandler pCompletionHandler = nullptr) = 0;
	virtual int WaitForCompletion() = 0;
	virtual void* GetResultData() = 0;
};

int
NETAPI_ENTRY
CreateNetworkRequest(
	char* pURL,
	INetRequest* &pNetRequest);

