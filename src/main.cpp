// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "split.h"
#include "new/new.h"
#include "old/old.h"
using namespace std;
int main(int argc, char** argv) {
	int cryptMethod;
	cout << "Which Encryption Method would you like to use:\n1. Newer Encryption Method (More Secure, but not compatible with BlazeEncryptions v1.x)\n2. Older Encryption Method (Less Secure, but compatible with BlazeEncryptions v1.x)\nPlease type 1 or 2 and press enter." << endl;
	cin >> cryptMethod;
	if (cryptMethod == 1) {
		New();
		return 0;
	}
	if (cryptMethod == 2) {
		old();
		return 0;
	}
	else {
		cout << "Unrecognized Option: '" + to_string(cryptMethod) + "'. \n";
		main(NULL, NULL);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
