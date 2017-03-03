#pragma once

#include "BrDefs.h"
#include <cstdint>
#include <memory>

typedef int8_t		I8;
typedef uint8_t		U8;
typedef int16_t		I16;
typedef uint16_t	U16;
typedef int32_t		I32;
typedef uint32_t	U32;
typedef int64_t		I64;
typedef uint64_t	U64;

typedef struct _BrGuid
{
	U32 Data1;
	U16 Data2;
	U16 Data3;
	U8 Data4[8];
} BrGuid;

BR_INLINE bool IsBrGUIDEqual(BrGuid& rhs, BrGuid& lhs)
{
	return !memcmp(&rhs, &lhs, sizeof(BrGuid));
}

BR_INLINE bool InlineIsBrGUIDEqual(BrGuid& rhs, BrGuid& lhs)
{
	return ((((U32*)&rhs)[0] == ((U32*)&lhs)[0]) &&
			(((U32*)&rhs)[1] == ((U32*)&lhs)[1]) &&
			(((U32*)&rhs)[2] == ((U32*)&lhs)[2]) &&
			(((U32*)&rhs)[3] == ((U32*)&lhs)[3]));
}

#ifdef __cplusplus
BR_INLINE bool operator==(BrGuid& lhs, BrGuid& rhs)
{
	return IsBrGUIDEqual(lhs, rhs);
}

BR_INLINE bool operator!=(BrGuid& lhs, BrGuid& rhs)
{
	return !(lhs == rhs);
}
#endif

#ifndef DEFINE_BRGUID
#define DEFINE_BRGUID(Name, Data1, Data2, Data3, B1, B2, B3, B4, B5, B6, B7, B8) \
DEFINE_WEAK_SYMBOL(BrGuid, Name) = {Data1, Data2, Data3, { B1, B2, B3, B4, B5, B6, B7, B8}}
#endif

typedef I32 BrResult;
