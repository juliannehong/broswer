#include "NetRequest.h"

struct NetException
{
	int code;
	NetException(int c) : code(c) {}
	~NetException() {}
};

BrResult CNetRequest::ThreadFunc(CObjectPtr<IBrThread> pThread)
{
	//Open a network socket to the URL for HTTP.

}

bool CNetRequest::IsIIDValid(BrGuid & riid)
{
	if(riid == GET_UUID(INetRequest) || riid == GET_UUID(IBrUnknown))
	{
		return true;
	}
	return false;
}

CNetRequest::CNetRequest(char * url):
	callback(nullptr),
	iothread(CreateBrThread(std::bind(&CNetRequest::ThreadFunc, this, std::placeholders::_1))),
	complete(CreateBrEvent(true, false))
{
	//Check this URL for validity.

}

CNetRequest::~CNetRequest()
{
}

BrResult CNetRequest::Start(CompletionHandler pcallback)
{
	//initialize thread data, then spawn off the request thread.
	callback = pcallback;
	complete->Reset();
	return iothread->Start();
}

CObjectPtr<INetRequest> NETAPI_ENTRY CreateNetworkRequest(char * pURL)
{
	if(!pURL)
	{
		return nullptr;
	}
	try
	{
		return CObjectPtr<INetRequest>(new CNetRequest(pURL), true);
	}
	catch(NetRequestException e)
	{
		return nullptr;
	}
}