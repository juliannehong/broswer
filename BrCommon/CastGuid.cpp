#include "BrCommon.h"

#ifdef _WIN32

#include <guiddef.h>

BrGuid BRCOMMON_API CastGuid(const struct _GUID& g)
{
	static_assert(sizeof(BrGuid) == sizeof(_GUID), "BRGUID and GUID are not the same size!");
	BrGuid ret;
	memcpy(&ret, &g, sizeof(BrGuid));
	return ret;
}

#else

#include <memory>

static const BrGuid zero = { 0,0,0,{0,0,0,0,0,0,0,0} };

template<typename T> 
bool ParseValue(T& val, const char* c)
{
	val = 0;
	for(int i = 0; i < (sizeof(T) << 1); ++i)
	{
		if((c[i] < '0' || c[i] > '9') || (c[i] < 'A' || c[i] > 'F'))
		{
			return false;
		}
		if(c[i] >= 'A')
		{
			val |= ((c[i] - 'A') + 10);
		}
		else
		{
			val |= (c[i] - '0');
		}
		val <<= 4;
	}
	return true;
}

BrGuid BRCOMMON_API CastGuid(const char * c)
{
	BrGuid ret;
	memset(&ret, 0, sizeof(ret));
	//strlen it first.
	size_t sz = strlen(c);
	if(sz != 38)
	{
		//not a guid.
		return zero;
	}
	// {3E21EDFD-3B6E-49BA-B4DD-3BE120C9747F}
	//check chars that should be constant.
	if(c[0] != '{' || c[9] != '-' || c[14] != '-' || c[19] != '-' || c[24] != '-' || c[37] != '}')
	{
		return zero;
	}
	//Now parse each part.
	if(!ParseValue(ret.Data1, &c[1])) return zero;
	if(!ParseValue(ret.Data2, &c[10])) return zero;
	if(!ParseValue(ret.Data3, &c[15])) return zero;
	if(!ParseValue(ret.Data4[0], &c[20])) return zero;
	if(!ParseValue(ret.Data4[1], &c[22])) return zero;
	for(int i = 0; i < 6; ++i)
	{
		if(!ParseValue(ret.Data4[2 + i], &c[25 + (i << 1)])) return zero;
	}
	return ret;
}

#endif