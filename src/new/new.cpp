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
#include "new.h"
using namespace std;
int New() {
	int crypt;
	cout << "What would you like to do\n1. Generate Encryption/Decryption Keys\n2. Encrypt\n3. Decrypt\n4. Quit The Program\nPlease type 1, 2, 3, or 4 and press enter." << endl;
	cin >> crypt;
	if (crypt == 1) {
		keygen();
		return 0;
	}
	if (crypt == 2) {
		Newencrypt();
		return 0;
	}
	if (crypt == 3) {
		Newdecrypt();
		return 0;
	}
	if (crypt == 4) {
		return 0;
	}
	else {
		cout << "Unrecognized Option: '" + to_string(crypt) + "'. \n";
		New();
	}
}