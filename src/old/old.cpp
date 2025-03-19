#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "../split.h"
#include "encrypt.h"
#include "decrypt.h"
#include "old.h"
using namespace std;
int old::old() {
	string crypt;
	try {
		cout << "What would you like to do\n1. Encrypt\n2. Decrypt\n3. Quit The Program\nPlease type 1, 2, or 3 and press enter." << endl;
		getline(cin, crypt);
		if (stoi(crypt) != 1 && stoi(crypt) != 2 && stoi(crypt) != 3) throw 1;
	}
	catch (...) {
		cout << "Unrecognized Option: '" + crypt + "'. \n";
		old();
		return 0;
	}
	if (stoi(crypt) == 1) {
		encrypt();
		return 0;
	}
	if (stoi(crypt) == 2) {
		decrypt();
		return 0;
	}
	if (stoi(crypt) == 3) {
		return 0;
	}
}