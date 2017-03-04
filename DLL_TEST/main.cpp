#include <iostream>
#include "consoleutil.h"
#include "../BrCommon/BrCommon.h"
using namespace std;

BrResult ThreadFunc(CObjectPtr<IBrThread> CurrentThread, CObjectPtr<IBrEvent> CloseEvent)
{
	cout << "Started Thread!" << endl;
	CObjectPtr<IBrEvent> evts[] = { CurrentThread->GetCancellationEvent(), CloseEvent };
	U32 signaledEvent = 0;
	while(WaitForEvents(evts, signaledEvent, false))
	{
		if(signaledEvent == 0)
		{
			cout << "Thread canceled." << endl;
			return 0;
		}
		else if(signaledEvent == 1)
		{
			cout << "Event signaled." << endl;
			CloseEvent->Reset();
		}
	}
	return -1;
}

int main()
{
	CObjectPtr<IBrEvent> evt = CreateBrEvent(true, false);
	//Note that we must use a lambda here - bind only works if the arguments we specify are first.
	// bind(Func, Arg1, placeholders::_1) is ok, but
	// bind(Func, placeholders::_1, Arg1) is not.
	CObjectPtr<IBrThread> th = CreateBrThread([&evt](auto t) -> BrResult
	{
		return ThreadFunc(t, evt);
	});
	cout << "Hello" << endl;
	th->Start();
	char c = 0;
	do
	{
		cout << "enter a character (x to cancel): ";
		cin >> c;
		if(c == 'x')
		{
			break;
		}
		evt->Set();
	} while(c != 0);
	th->CancelAndWait(10'000);
	pause();
	return 0;
}