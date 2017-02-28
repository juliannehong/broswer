#include "NetRequest.h"



CNetRequest::CNetRequest()
{
}


CNetRequest::~CNetRequest()
{
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
		pNetRequest = new CNetRequest(pUrl);
	}
	catch(NetException e)
	{
		//return the error code associated with the object.
		return e.code;
	}
	return 0;
}