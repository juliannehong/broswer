#pragma once
#include "ObjectWrapper.h"
#include <Windows.h>

class BrEvent :
	public ObjectWrapper<IBrEvent>
{
	HANDLE e;

	bool IsIIDValid(BrGuid& riid);

public:
	BrEvent(bool ManualReset, bool InitialState);
	~BrEvent();

	//This, while public, is unavailable to any code that does not know of BrEvent directly.
	HANDLE GetEventHandle() { return e; }

	bool BRMETHODCALLTYPE IsSet();
	void BRMETHODCALLTYPE Set();
	void BRMETHODCALLTYPE Reset();
	bool BRMETHODCALLTYPE WaitForSignal(U32 msTimeout = -1);
};

