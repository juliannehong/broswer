#include <iostream>
#include "consoleutil.h"

using namespace std;



int main()
{
	cout << "Hello" << endl;
	printStuff();
	for (int i = 0; i < 1000; ++i)
	{
		cout << i << endl;
	}
	pause();
	eraseConsole();
	pause();
	return 0;
}