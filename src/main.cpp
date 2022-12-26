// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define VERSION "BlazeEncryptions v2.0.5"
#define USAGE "\
Usage: BlazeEncryptions [--old] [--new] [--encrypt] [--decrypt] [--keygen] [-h] [--help] [--version]\n\
Options: --old (Uses the older Encryption/Decryption method for compatibility with BlazeEncryptions v1.x and less secure) --new (Uses the Newer Encryption/Decryption method which is more secure but not compatible with v1.x) --encrypt (Encrypt a message) --decrypt (Decrypt a message) --help or -h (Prints this exact messaage) --version (Prints out the version of this Scalc binary)"
#define COPYRIGHT "Copyright (c) 2022 winexe0 <aryan.chandna@icloud.com> Albert Nguyen <azero2113@gmail.com>"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "split.h"
#include "new/new.h"
#include "new/encrypt.h"
#include "new/decrypt.h"
#include "new/keygen.h"
#include "old/old.h"
#include "old/decrypt.h"
#include "old/encrypt.h"
using namespace std;
int main(int argc, char** argv) {
	string cryptMethod;
	for (int i = 1; i < argc; ++i) {
		string arg = argv[i];
		if (arg == "--help" || arg == "-h") {
			cout << VERSION << endl;
			cout << USAGE << endl;
			exit(0);
		}
		if (arg == "--version") {
			cout << VERSION << endl;
			cout << COPYRIGHT << endl;
			exit(0);
		}
		if (arg == "--old") {
			old();
			return 0;
		}
		if (arg == "--new") {
			New();
			return 0;
		}
		if (arg == "--encrypt") {
			cout << "Which Encryption Method would you like to use:\n1. Newer Encryption Method (More Secure, but not compatible with BlazeEncryptions v1.x)\n2. Older Encryption Method (Less Secure, but compatible with BlazeEncryptions v1.x)\nPlease type 1 or 2 and press enter." << endl;
			cin >> cryptMethod;
			if (stoi(cryptMethod) == 1) {
				Newencrypt();
				return 0;
			}
			if (stoi(cryptMethod) == 2) {
				encrypt();
				return 0;
			}
		}
		if (arg == "--decrypt") {
			cout << "Are you decrypting for:\n1. The Newer Encryption Method \n2. The Older Encryption Method\nPlease type 1 or 2 and press enter." << endl;
			cin >> cryptMethod;
			if (stoi(cryptMethod) == 1) {
				Newencrypt();
				return 0;
			}
			if (stoi(cryptMethod) == 2) {
				encrypt();
				return 0;
			}
		}
		if (arg == "--keygen") {
			keygen();
		}
		else {
			cout << VERSION << endl;
			cout << "Invalid argument" << endl;
			cout << USAGE << endl;
			exit(0);
		}
	}
	cout << VERSION << endl;
	cout << "Which Encryption Method would you like to use:\n1. Newer Encryption Method (More Secure, but not compatible with BlazeEncryptions v1.x)\n2. Older Encryption Method (Less Secure, but compatible with BlazeEncryptions v1.x)\nPlease type 1 or 2 and press enter." << endl;
	cin >> cryptMethod;
	if (cryptMethod == "1") {
		New();
		return 0;
	}
	if (cryptMethod == "2") {
		old();
		return 0;
	}
	else {
		cout << "Unrecognized Option: '" + cryptMethod + "'. \n";
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
