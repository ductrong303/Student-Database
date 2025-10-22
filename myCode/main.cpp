// Standard (system) header files
#include <iostream>
#include <cstdlib>
#include "SimpleUI.h"
#include "StudentDB.h"
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
// #include "CFraction.h"

// Main program
int main ()
{
    // TODO: Add your program code here
	cout << "APT_Lab_3_StudentDB started." << endl << endl;
	StudentDB db;
    SimpleUI ui(db);
    while(true) ui.run();
    cout << "APT_Lab_3_StudentDB ends." << endl << endl;
	return 0;
}
