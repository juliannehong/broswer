#pragma once

#include "BrTypes.h"

#ifndef BROWSER_INTERFACE
#define BROWSER_INTERFACE(x) \
	struct BR_NOVTABLE BR_UUID(x)
#endif

#ifndef BRMETHODCALLTYPE
#ifdef _WIN32
#define BRMETHODCALLTYPE __stdcall
#else
#define BRMETHODCALLTYPE 
#endif
#endif

#ifndef BRMETHODVCALLTYPE
#ifdef _WIN32
#define BRMETHODVCALLTYPE __cdecl
#else
#define BRMETHODVCALLTYPE 
#endif
#endif

#ifndef BRMETHOD
#define BRMETHOD(Method)\
	virtual BR_NOTHROW BrResult BRMETHODCALLTYPE Method = 0;
#endif

#ifndef BRMETHODTYPE
#define BRMETHODTYPE(Type, Method)\
	virtual BR_NOTHROW Type BRMETHODCALLTYPE Method = 0;
#endif

// {3E21EDFD-3B6E-49BA-B4DD-3BE120C9747F}
BROWSER_INTERFACE("{3E21EDFD-3B6E-49BA-B4DD-3BE120C9747F}")
IBrUnknown
{
	BRMETHOD(QueryInterface(BrGuid& rIID, void** ppvObject));
	BRMETHODTYPE(U32, AddRef());
	BRMETHODTYPE(U32, Release());
};

#ifndef CAST_UUID
#ifdef _WIN32
BrGuid COMMONAPI_ENTRY CastGuid(const struct _GUID& g);
#else
BrGuid COMMONAPI_ENTRY CastGuid(const char* c);
#endif
#define CAST_UUID(U) CastGuid(U)
#endif

#define GET_UUID(T) CAST_UUID(BR_UUIDOF(T))