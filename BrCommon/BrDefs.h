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

//These next two are for weak symbols (multiple definitions, all the same). Both need to be used.
//E.x. BR_SELECTANY int BR_WEAK WeakSymbolInHeader = 10;
//This allows us to place variables in a header and initialize them without violating the one-definition rule.
//NOTE THIS ONLY WORKS RELIABLY IF ALL DEFINITIONS ARE THE SAME!

#ifndef BR_WEAK
#ifdef _WIN32
#define BR_WEAK 
#else
#define BR_WEAK __attribute__((weak))
#endif
#endif

#ifndef BR_SELECTANY
#ifdef _WIN32
#define BR_SELECTANY __declspec(selectany)
#else
#define BR_SELECTANY 
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

