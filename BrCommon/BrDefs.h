#pragma once

#ifndef BR_EXPORT
#ifdef _WIN32
//PE exports will be from a DLL.
#define BR_EXPORT __declspec(dllexport)
#else
//ELF platforms should have everything hidden by default - we expose only what we want.
#define BR_EXPORT __attribute__((visibility="default"))
#endif
#endif

#ifndef BR_IMPORT
#ifdef _WIN32
//PE imports will be from a DLL.
#define BR_IMPORT __declspec(dllimport)
#else
//ELF platforms don't have a concept of import.
#define BR_IMPORT 
#endif
#endif

#ifndef BR_INLINE
#define BR_INLINE inline
#endif

#ifndef BR_FORCEINLINE
#ifdef _WIN32
#define BR_FORCEINLINE BR_INLINE __forceinline
#else
#define BR_FORCEINLINE BR_INLINE __attribute__((always_inline))
#endif
#endif

#ifndef BR_NOVTABLE
#ifdef _WIN32
#define BR_NOVTABLE __declspec(novtable)
#else
//GCC has no concept of novtable. 
#define BR_NOVTABLE 
#endif
#endif

#ifndef BR_NOTHROW
#ifdef _WIN32
#define BR_NOTHROW __declspec(nothrow)
#else
#define BR_NOTHROW __attribute__((nothrow))
#endif
#endif

#ifndef BR_UUID
#ifdef _WIN32
#define BR_UUID(x) __declspec(uuid(x))
#else
#define BR_UUID(x) __attribute__((uuid(x)))
#endif
#endif

#ifndef BR_UUIDOF
#ifdef _WIN32
#define BR_UUIDOF(T) __uuidof(T)
#else
#define BR_UUIDOF(T) __builtin_uuidof(T)
#endif
#endif

// Token pasting macro for identifier generation.
#ifndef CONCAT
#define CONCAT_INT(x, y) x ## y
#define CONCAT(x, y) CONCAT_INT(x, y)
#endif
