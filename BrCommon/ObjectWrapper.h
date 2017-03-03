#pragma once

#include "BrCommon.h"
#include <type_traits>
#include <atomic>
#include <cassert>

template<typename T>
class ObjectWrapper :
	public T
{
	static_assert(std::is_base_of<IBrUnknown, T>::value, "T must derive from IBrUnknown!");

	//updates to refcount should be threadsafe.
	std::atomic<U32> refcount;

protected:
	virtual bool IsIIDValid(BrGuid& riid) = 0;

public:

	ObjectWrapper() : refcount(1)
	{
	}

	virtual ~ObjectWrapper()
	{
		assert(refcount == 0);
	}

	BrResult BRMETHODCALLTYPE QueryInterface(BrGuid& riid, void** ppvObject)
	{
		if(!ppvObject)
		{
			return -1; // INVALID_ARG
		}
		*ppvObject = nullptr;
		if(IsIIDValid(riid))
		{
			*ppvObject = (void*)this;
			AddRef();
			return 0; // OK
		}
		return -2; // NO_INTERFACE
	}

	U32 BRMETHODCALLTYPE AddRef()
	{
		return ++refcount;
	}
	
	U32 BRMETHODCALLTYPE Release()
	{
		U32 r = --refcount;
		if(r == 0)
		{
			delete this;
		}
		return r;
	}
};

