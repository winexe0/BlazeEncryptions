#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "../split.h"
#include "encrypt.h"
#include "decrypt.h"
#include "keygen.h"
#include "keyinfo.h"
#include "new.h"
using namespace std;
using namespace second;
int second::second() {
	string crypt;
	try {
		cout << "What would you like to do\n1. Generate Encryption/Decryption Keys\n2. Encrypt\n3. Decrypt\n4. Analyze an existing key\n5. Quit The Program\nPlease type 1, 2, 3, or 4 and press enter." << endl;
		getline(cin, crypt);
		if (stoi(crypt) != 1 && stoi(crypt) != 2 && stoi(crypt) != 3 && stoi(crypt) != 4 && stoi(crypt) != 5) throw 1;
	}
	catch (...) {
		cout << "Unrecognized Option: '" + crypt + "'. \n";
		second::second();
		return 0;
	}
	if (stoi(crypt) == 1) {
		keygen();
		return 0;
	}
	if (stoi(crypt) == 2) {
		encrypt();
		return 0;
	}
	if (stoi(crypt) == 3) {
		decrypt();
		return 0;
	}
	if (stoi(crypt) == 4) {
		keyinfo("NULL");
		return 0;
	}
	if (stoi(crypt) == 5) {
		return 0;
	}
}