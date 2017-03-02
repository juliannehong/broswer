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

public:

	ObjectWrapper() : refcount(1)
	{
	}

	virtual ~ObjectWrapper()
	{
		assert(refcount == 0);
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

