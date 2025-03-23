// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define VERSION "BlazeEncryptions v3.1"
#define USAGE "\
Usage: BlazeEncryptions [--first] [--second] [--fourth] [--encrypt] [--decrypt] [--keygen] [--keystats] [-h] [--help] [--version]\n\
Options: --first (Uses the 1.x Encryption Method)\n --second (Uses the 2.x-3.x Encryption Method)\n --fourth (Uses the 4.x Encryption Method)\n --keygen (Generate Encryption keys)\n --keystats KEYNAME (Shows statistics of an existing key which could be KEYNAME)\n --encrypt (Encrypt a message)\n --decrypt (Decrypt a message)\n --help or -h (Prints this exact messaage)\n --version (Prints out the version of this version of BlazeEncryptions)\n"
#define COPYRIGHT "Copyright (c) 2025 winexe0 <aryan.chandna@icloud.com> Albert Nguyen <azero2113@gmail.com>"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#define VISTA !IsWindowsVistaSP2OrGreater()
#endif // _WIN32
#ifdef __linux__
#define VISTA false // For non-Windows systems
#endif // __linux__
#ifdef __APPLE__
#define VISTA false // For non-Windows systems
#endif // __APPLE__
#include "split.h"
#include "1.x/old.h"
#include "1.x/decrypt.h"
#include "1.x/encrypt.h"
#include "2.x-3.x/new.h"
#include "2.x-3.x/encrypt.h"
#include "2.x-3.x/decrypt.h"
#include "2.x-3.x/keygen.h"
#include "2.x-3.x/keyinfo.h"
#include "4.x/new.h"
#include "4.x/encrypt.h"
#include "4.x/decrypt.h"
#include "4.x/keygen.h"
#include "4.x/keyinfo.h"
using namespace std;
int main(int argc, char** argv) {
	string cryptMethod;
	if (VISTA) {
       cout << "BlazeEncryptions 3.x and greater requires Windows Vista SP2 or greater to run. Please upgrade your system to run BlazeEncryptions or use BlazeEncryptions 2.x" << endl;
	   return 1;
    }
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
		if (arg == "--first") {
			first::first();
			return 0;
		}
		if (arg == "--second") {
			second::second();
			return 0;
		}
		if (arg == "--fourth") {
			fourth::fourth();
			return 0;
		}
		if (arg == "--encrypt") {
			try {
				cout << "Are you using the:\n1. The 4.x Encryption Method\n2. The 2.x-3.x Encryption Method\n3. 1.x Encryption Method\nPlease type 1, 2, or 3 and press enter." << endl;
				getline(cin, cryptMethod);
				if (stoi(cryptMethod) != 1 && stoi(cryptMethod) != 2 && stoi(cryptMethod) != 3) throw 1;
			}
			catch (...) {
				cout << "Unrecognized Option: '" + cryptMethod + "'. \n";
				main(2, argv);
			}
			if (stoi(cryptMethod) == 1) {
				fourth::encrypt();
				return 0;
			}
			if (stoi(cryptMethod) == 2) {
				second::encrypt();
				return 0;
			}
			if (stoi(cryptMethod) == 3) {
				first::encrypt();
				return 0;
			}
		}
		if (arg == "--decrypt") {
			try {
				cout << "Are you using the:\n1. The 4.x Encryption Method\n2. The 2.x-3.x Encryption Method\n3. 1.x Encryption Method\nPlease type 1, 2, or 3 and press enter." << endl;
				getline(cin, cryptMethod);
				if (stoi(cryptMethod) != 1 && stoi(cryptMethod) != 2 && stoi(cryptMethod) != 3) throw 1;
			}
			catch (...) {
				cout << "Unrecognized Option: '" + cryptMethod + "'. \n";
				main(2, argv);
			}
			if (stoi(cryptMethod) == 1) {
				fourth::decrypt();
				return 0;
			}
			if (stoi(cryptMethod) == 2) {
				second::decrypt();
				return 0;
			}
			if (stoi(cryptMethod) == 3) {
				first::decrypt();
				return 0;
			}
		}
		if (arg == "--keygen") {
			cout << "Which Encryption Method would you like to use:\n1. The 4.x Encryption Method\n2. The 2.x-3.x Encryption Method\nPlease type 1 or 2 and press enter." << endl;
			getline(cin, cryptMethod);
			if (stoi(cryptMethod) == 1) {
				fourth::keygen();
				return 0;
			}
			if (stoi(cryptMethod) == 2) {
				second::keygen();
				return 0;
			}
			return 0;
		}
		if (arg == "--keystats" && argc == 3) {
			cout << "Which Encryption Method would you like to use:\n1. The 4.x Encryption Method\n2. The 2.x-3.x Encryption Method\nPlease type 1 or 2 and press enter." << endl;
			getline(cin, cryptMethod);
			if (stoi(cryptMethod) == 1) {
				fourth::keyinfo(argv[2]);
				return 0;
			}
			if (stoi(cryptMethod) == 2) {
				second::keyinfo(argv[2]);
				return 0;
			}
			return 0;
		}
		if (arg == "--keystats") {
			cout << "Which Encryption Method would you like to use:\n1. The 4.x Encryption Method\n2. The 2.x-3.x Encryption Method\nPlease type 1 or 2 and press enter." << endl;
			getline(cin, cryptMethod);
			if (stoi(cryptMethod) == 1) {
				fourth::keyinfo("NULL");
				return 0;
			}
			if (stoi(cryptMethod) == 2) {
				second::keyinfo("NULL");
				return 0;
			}
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
		cout << "Which Encryption Method would you like to use:\n1. The 4.x Encryption Method\n2. The 2.x-3.x Encryption Method\n3. 1.x Encryption Method\n4. Quit the Program\nPlease type 1, 2, 3, or 4 and press enter." << endl;
		getline(cin, cryptMethod);
		if (stoi(cryptMethod) != 1 && stoi(cryptMethod) != 2 && stoi(cryptMethod) != 3 && stoi(cryptMethod) != 4) throw 1;
	}
	catch (...) {
		cout << "Unrecognized Option: '" + cryptMethod + "'. \n";
		main(NULL, NULL);
		return 0;
	}
	if (stoi(cryptMethod) == 1) {
		fourth::fourth();
		return 0;
	}
	if (stoi(cryptMethod) == 2) {
		second::second();
		return 0;
	}
	if (stoi(cryptMethod) == 3) {
		first::first();
		return 0;
	}
	if (stoi(cryptMethod) == 4) {
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
