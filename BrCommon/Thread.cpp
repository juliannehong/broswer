#include "Thread.h"

struct ThreadException
{
	U32 code;
};

CThread::CThread()
{

}


CThread::~CThread()
{
}

CBrObjectPtr<IBrThread> CreateBrThread()
{
	CBrObjectPtr<IBrThread> t;
	try
	{
		t = CBrObjectPtr<IBrThread>(new CThread(), true);
	}
	catch(ThreadException e)
	{
		return nullptr;
	}
	return t;
}