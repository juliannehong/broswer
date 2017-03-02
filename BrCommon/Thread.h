#pragma once

#include "ObjectWrapper.h"

class CThread :
	public ObjectWrapper<IBrThread>
{


public:
	CThread();
	~CThread();
};

