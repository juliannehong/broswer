#pragma once

#include "BrDefs.h"
#include <cstdint>

typedef int8_t		I8;
typedef uint8_t		U8;
typedef int16_t		I16;
typedef uint16_t	U16;
typedef int32_t		I32;
typedef uint32_t	U32;
typedef int64_t		I64;
typedef uint64_t	U64;

typedef struct _BRGUID
{
	U32 Data1;
	U16 Data2;
	U16 Data3;
	U8 Data4[8];
} BRGUID;

#ifndef DEFINE_BRGUID
#define DEFINE_BRGUID(Name, Data1, Data2, Data3, B1, B2, B3, B4, B5, B6, B7, B8) \
BR_SELECTANY BRGUID BR_WEAK Name = {Data1, Data2, Data3, { B1, B2, B3, B4, B5, B6, B7, B8}}
#endif

typedef I32 BRRESULT;
