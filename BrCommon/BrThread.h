#pragma once

#include "BrCommon.h"
#include <functional>

#ifndef __IBrEvent__FWD_DEFINED__
#define __IBrEvent__FWD_DEFINED__
typedef struct IBrEvent IBrEvent;
#endif

#ifndef __IBrThread__FWD_DEFINED__
#define __IBrThread__FWD_DEFINED__
typedef struct IBrThread IBrThread;
#endif

#ifndef __IBrThreadPool__FWD_DEFINED__
#define __IBrThreadPool__FWD_DEFINED__
typedef struct IBrThreadPool IBrThreadPool;
#endif

BROWSER_INTERFACE("{9D4A64E6-D647-43D9-9C81-E72A10045F8E}")
IBrEvent : public IBrUnknown
{
	BRMETHODTYPE(bool, IsSet());
	BRMETHODTYPE(void, Set());
	BRMETHODTYPE(void, Reset());
	BRMETHODTYPE(bool, WaitForSignal(U32 msTimeout = -1));
};

bool
COMMONAPI_ENTRY
WaitForEvents(
	CObjectPtr<IBrEvent>* pEvents,
	U32 NumEvents,
	U32 &SignaledEvent,
	bool WaitForAll,
	U32 msTimeout = -1
);

#ifdef __cplusplus

template<U32 N>
BR_INLINE bool WaitForEvents(CObjectPtr<IBrEvent> (&pEvents)[N], U32 &SignaledEvent, bool WaitForAll, U32 msTimeout = -1)
{
	return WaitForEvents(pEvents, N, SignaledEvent, WaitForAll, msTimeout);
}

#endif

typedef std::function<BrResult(CObjectPtr<IBrThread> pThread)> ThreadFunction;

BROWSER_INTERFACE("{C5552C11-1EEF-4F7F-B768-6FB2F39C3AB8}")
IBrThread : public IBrUnknown
{
	BRMETHOD(Start());
	BRMETHODTYPE(CObjectPtr<IBrEvent>, GetCancellationEvent());
	BRMETHOD(Cancel());
	BRMETHOD(CancelAndWait(U32 msTimeout));
	BRMETHOD(WaitForExit(U32 msTimeout));
	BRMETHOD(Terminate(BrResult ResultCode));
	BRMETHOD(GetExitCode());
};

CObjectPtr<IBrEvent>
COMMONAPI_ENTRY
CreateBrEvent(
	bool ManualReset,
	bool InitialState
);

CObjectPtr<IBrThread>
COMMONAPI_ENTRY
CreateBrThread(
	ThreadFunction pThreadFunction,
	bool StartImmediately = false
);
