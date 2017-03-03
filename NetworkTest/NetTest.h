#pragma once
//Network test API.

#include <BrCommon.h>

#ifdef NETWORKTEST_EXPORTS
#define NETAPI_ENTRY BR_EXPORT
#else
#define NETAPI_ENTRY BR_IMPORT
#endif

#include <functional>

typedef std::function<int(int ResultCode)> CompletionHandler;

//use COM to hide the implementation details.

BROWSER_INTERFACE("{0991DED7-6055-4317-B247-7BA635CBF032}")
INetRequest : public IBrUnknown
{
	BRMETHOD(Start(CompletionHandler pCompletionHandler = nullptr));
	BRMETHOD(WaitForCompletion());
	BRMETHODTYPE(void*,GetResultData());
};

CObjectPtr<INetRequest>
NETAPI_ENTRY
CreateNetworkRequest(
	char* pURL);

