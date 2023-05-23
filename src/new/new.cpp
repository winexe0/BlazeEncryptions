#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "../main.h"
#include "../split.h"
#include "encrypt.h"
#include "decrypt.h"
#include "keygen.h"
#include "keyinfo.h"
#include "new.h"
using namespace std;
int New::New() {
	int crypt;
	cout << "What would you like to do\n1. Generate Encryption/Decryption Keys\n2. Encrypt\n3. Decrypt\n4. Analyze an existing key\nPlease type 1, 2, 3, or 4 and press enter." << endl;
	cin >> crypt;
	if (crypt == 1) {
		keygen();
		main(NULL, NULL);
	}
	if (crypt == 2) {
		New::encrypt();
		main(NULL, NULL);
	}
	if (crypt == 3) {
		New::decrypt();
		main(NULL, NULL);
	}
	if (crypt == 4) {
		keyinfo("NULL");
		main(NULL, NULL);
	}
	else {
		cout << "Unrecognized Option: '" + to_string(crypt) + "'. \n";
		New();
	}
}