// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define VERSION "BlazeEncryptions v2.1.4"
#define USAGE "\
Usage: BlazeEncryptions [--old] [--new] [--encrypt] [--decrypt] [--keygen] [--keystats] [-h] [--help] [--version]\n\
Options: --old (Uses the older Encryption/Decryption method for compatibility with BlazeEncryptions v1.x and less secure)\n --new (Uses the Newer Encryption/Decryption method which is more secure but not compatible with v1.x)\n --keygen (Generate Encryption keys)\n --keystats KEYNAME (Shows statistics of an existing key which could be KEYNAME)\n --encrypt (Encrypt a message)\n --decrypt (Decrypt a message)\n --help or -h (Prints this exact messaage)\n --version (Prints out the version of this version of BlazeEncryptions)\n"
#define COPYRIGHT "Copyright (c) 2025 winexe0 <aryan.chandna@icloud.com> Albert Nguyen <azero2113@gmail.com>"
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
#include "new/keyinfo.h"
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
			old::old();
			return 0;
		}
		if (arg == "--new") {
			New::New();
			return 0;
		}
		if (arg == "--encrypt") {
			try {
				cout << "Which Encryption Method would you like to use:\n1. Newer Encryption Method (More Secure, but not compatible with BlazeEncryptions v1.x)\n2. Older Encryption Method (Less Secure, but compatible with BlazeEncryptions v1.x)\nPlease type 1 or 2 and press enter." << endl;
				getline(cin, cryptMethod);
				if (stoi(cryptMethod) != 1 && stoi(cryptMethod) != 2) throw 1;
			}
			catch (...) {
				cout << "Unrecognized Option: '" + cryptMethod + "'. \n";
				main(2, argv);
			}
			if (stoi(cryptMethod) == 1) {
				New::encrypt();
				return 0;
			}
			if (stoi(cryptMethod) == 2) {
				old::encrypt();
				return 0;
			}
		}
		if (arg == "--decrypt") {
			try {
				cout << "Are you decrypting for:\n1. The Newer Encryption Method \n2. The Older Encryption Method\nPlease type 1 or 2 and press enter." << endl;
				getline(cin, cryptMethod);
				if (stoi(cryptMethod) != 1 && stoi(cryptMethod) != 2) throw 1;
			}
			catch (...) {
				cout << "Unrecognized Option: '" + cryptMethod + "'. \n";
				main(2, argv);
			}
			if (stoi(cryptMethod) == 1) {
				New::decrypt();
				return 0;
			}
			if (stoi(cryptMethod) == 2) {
				old::decrypt();
				return 0;
			}
		}
		if (arg == "--keygen") {
			keygen();
			return 0;
		}
		if (arg == "--keystats" && argc == 3) {
			keyinfo(argv[2]);
			return 0;
		}
		if (arg == "--keystats") {
			keyinfo("NULL");
			return 0;
		}
		else {
			cout << VERSION << endl;
			cout << "Invalid argument" << endl;
			cout << USAGE << endl;
			exit(0);
		}
	}
	cout << VERSION << endl;
	try {
		cout << "Which Encryption Method would you like to use:\n1. Newer Encryption Method (More Secure, but not compatible with BlazeEncryptions v1.x)\n2. Older Encryption Method (Less Secure, but compatible with BlazeEncryptions v1.x)\n3. Quit the Program\nPlease type 1, 2, or 3 and press enter." << endl;
		getline(cin, cryptMethod);
		if (stoi(cryptMethod) != 1 && stoi(cryptMethod) != 2 && stoi(cryptMethod) != 3) throw 1;
	}
	catch (...) {
		cout << "Unrecognized Option: '" + cryptMethod + "'. \n";
		main(NULL, NULL);
		return 0;
	}
	if (stoi(cryptMethod) == 1) {
		New::New();
		return 0;
	}
	if (stoi(cryptMethod) == 2) {
		old::old();
		return 0;
	}
	if (stoi(cryptMethod) == 3) {
		return 2;
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
