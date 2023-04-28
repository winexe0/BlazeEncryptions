#include <iostream>
#include <string>
#include <fstream>
#include "fileSize.h"
#include "keyinfo.h"
using namespace std;
int keyinfo(std::string keyName) {
	if (keyName == "NULL") {
		cout << "What is the name of the key you want to analyze?" << endl;
		cin.ignore();
		getline(cin, keyName);
		fstream keyExist;
		keyExist.open(keyName, ios::in);
		if (!keyExist) {
			keyExist.open(keyName + ".txt", ios::in);
			keyName = keyName + ".txt";
			while (!keyExist) {
				cout << "Your key doesn't exist. Please enter an existing key to analyze" << endl;
				cin >> keyName;
				keyExist.open(keyName, ios::in);
			}
		};
		cout << "Statistics for key: " + keyName + "\n";
		cout << "With this key it is possible to encrypt messages up to " << fileSize(keyName) << " characters long." << endl;
		cout << "Press ENTER to exit" << endl;
		cin.get();
		cin.ignore();
		return 0;
	}
	else {
		fstream keyExist;
		keyExist.open(keyName, ios::in);
		if (!keyExist) {
			keyExist.open(keyName + ".txt", ios::in);
			keyName = keyName + ".txt";
			while (!keyExist) {
				cout << "Your key " + keyName + " doesn't exist." << endl;
				return 1;
			}
		}
		cout << "Statistics for key: " + keyName + "\n";
		cout << "With this key it is possible to encrypt messages up to " << fileSize(keyName) << " characters long." << endl;
		cout << "Press ENTER to exit" << endl;
		cin.get();
		cin.ignore();
		return 0;
	}
}