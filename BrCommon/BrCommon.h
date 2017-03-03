#pragma once

#include "BrDefs.h"

#ifdef BRCOMMON_EXPORTS
#define COMMONAPI_ENTRY BR_EXPORT
#else
#define COMMONAPI_ENTRY BR_IMPORT
#endif

#include "BrTypes.h"
#include "BrInterface.h"
#include "BrObjPtr.h"

#include "BrThread.h"
#include "BrFile.h"
