// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "split.h"
#include "encrypt.h"
#include "decrypt.h"
using namespace std;
int main(int argc, char** argv) {
	string crypt;
	cout << "Do you want to encrypt or decrypt?" << endl;
	cin >> crypt;
	if (crypt == "encrypt") {
		encrypt();
	}
	if (crypt == "decrypt") {
		decrypt();
	}
	else {
		cout << "Unrecognized Option: '" + crypt + "'. ";
		main(NULL, NULL);
	}
	cin.ignore();
	cin.get();
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
