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
#include "old.h"
using namespace std;
int old::old() {
	int crypt;
	cout << "What would you like to do\n1. Encrypt\n2. Decrypt\nPlease type 1 or 2 and press enter." << endl;
	cin >> crypt;
	if (crypt == 1) {
		encrypt();
		main(NULL, NULL);
	}
	if (crypt == 2) {
		decrypt();
		main(NULL, NULL);
	}
	else {
		cout << "Unrecognized Option: '" + to_string(crypt) + "'. \n";
		old();
	}
}