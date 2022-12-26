#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "keyinfo.h"
using namespace std;
int keyinfo() {
	string keyName;
	cout << "What is the name of the key you want to analyze?" << endl;
	cin >> keyName;
	fstream keyExist;
	keyExist.open(keyName, ios::in);
	if (!keyExist) {
		while (!keyExist) {
			cout << "Your key doesn't exist. Please enter an existing key to analyze" << endl;
			cin >> keyName;
			keyExist.open(keyName, ios::in);
		}
	}
	filesystem::path size{ keyName };
	cout << "Statistics for key: " + keyName + "\n";
	cout << "With this key it is possible to encrypt messages up to " << filesystem::file_size(size) << " characters long." << endl;
	cout << "Press ENTER to exit" << endl;
	cin.get();
	cin.ignore();
	return 0;
}