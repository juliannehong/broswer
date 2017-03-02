#pragma once

#include "BrTypes.h"

#ifndef BROWSER_INTERFACE
#define BROWSER_INTERFACE(InterfaceName, BaseInterface, ...) \
	DEFINE_BRGUID(IID_ ## InterfaceName, __VA_ARGS__); \
	struct BR_NOVTABLE InterfaceName : public BaseInterface
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
	virtual BR_NOTHROW BRRESULT BRMETHODCALLTYPE Method = 0;
#endif

#ifndef BRMETHODTYPE
#define BRMETHODTYPE(Type, Method)\
	virtual BR_NOTHROW Type BRMETHODCALLTYPE Method = 0;
#endif

// {3E21EDFD-3B6E-49BA-B4DD-3BE120C9747F}
DEFINE_BRGUID(IID_IBrUnknown,
			0x3e21edfd, 0x3b6e, 0x49ba, 0xb4, 0xdd, 0x3b, 0xe1, 0x20, 0xc9, 0x74, 0x7f);

struct BR_NOVTABLE IBrUnknown
{
	BRMETHODTYPE(U32, AddRef());
	BRMETHODTYPE(U32, Release());
};