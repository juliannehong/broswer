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

	bool BRMETHODCALLTYPE IsSet();
	void BRMETHODCALLTYPE Set();
	void BRMETHODCALLTYPE Reset();
};

