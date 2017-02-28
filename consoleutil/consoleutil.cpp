// consoleutil.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "consoleutil.h"
#include <iostream>

using namespace std;

// This is an example of an exported variable
CONSOLEUTIL_API int nconsoleutil=0;

// This is an example of an exported function.
CONSOLEUTIL_API int fnconsoleutil(void)
{
    return 42;
}

CONSOLEUTIL_API void printStuff()
{
	cout << "printStuff function called." << endl;
}

CONSOLEUTIL_API void pause()
{
	system("pause");
}

CONSOLEUTIL_API void eraseConsole()
{
	system("cls");
}

// This is the constructor of a class that has been exported.
// see consoleutil.h for the class definition
Cconsoleutil::Cconsoleutil()
{
    return;
}
