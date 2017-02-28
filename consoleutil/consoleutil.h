// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CONSOLEUTIL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CONSOLEUTIL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CONSOLEUTIL_EXPORTS
#define CONSOLEUTIL_API __declspec(dllexport)
#else
#define CONSOLEUTIL_API __declspec(dllimport)
#endif

// This class is exported from the consoleutil.dll
class CONSOLEUTIL_API Cconsoleutil {
public:
	Cconsoleutil(void);

	// TODO: add your methods here.
};

extern CONSOLEUTIL_API int nconsoleutil;

CONSOLEUTIL_API int fnconsoleutil(void);


CONSOLEUTIL_API void printStuff();
CONSOLEUTIL_API void pause();

CONSOLEUTIL_API void eraseConsole();
