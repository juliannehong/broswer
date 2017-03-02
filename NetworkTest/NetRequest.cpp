#include "NetRequest.h"

struct NetException
{
	int code;
	NetException(int c) : code(c) {}
	~NetException() {}
};

CNetRequest::CNetRequest(char * url):
	iothread(CNetRequest::ThreadEntry)
{
	//Check this URL for validity.

}

CNetRequest::~CNetRequest()
{
}

int CNetRequest::Start(CompletionHandler pcallback)
{
	//initialize thread data, then spawn off the request thread.
	
	return 0;
}


int NETAPI_ENTRY CreateNetworkRequest(char* pURL, INetRequest *& pNetRequest)
{
	if(pNetRequest)
	{
		//delete this request.

	}
	//check the URL to see if it's valid. << no checks for now.
	try
	{
		pNetRequest = new CNetRequest(pURL);
	}
	catch(NetException e)
	{
		//return the error code associated with the object.
		return e.code;
	}
	return 0;
}