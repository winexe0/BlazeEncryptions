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
int old() {
	int crypt;
	cout << "What would you like to do\n1. Encrypt\n2. Decrypt\n3. Quit The Program\nPlease type 1, 2, or 3 and press enter." << endl;
	cin >> crypt;
	if (crypt == 1) {
		encrypt();
		return 0;
	}
	if (crypt == 2) {
		decrypt();
		return 0;
	}
	if (crypt == 3) {
		return 0;
	}
	else {
		cout << "Unrecognized Option: '" + to_string(crypt) + "'. \n";
		old();
	}
}