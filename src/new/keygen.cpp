#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "keygen.h"
using namespace std;
int keygen() {
	unsigned int keyNum;
	unsigned long long length;
	string keyName;
	cout << "How many keys do you want to generate" << endl;
	cin >> keyNum;
	cout << "What is the maximum length of your messages" << endl;
	cin >> length;
	if (keyNum == 1) {
		cout << "What will be the name of your key" << endl;
	}
	else {
		cout << "What will be the name of your keys" << endl;
	}
	cin >> keyName;
	srand(time(0));
	fstream key;
	for (int i = 0; i < keyNum; i++) {
		key.open(keyName + to_string(i) + ".txt", ios::out);
		string tempRandTotal;
		for (int i = 0; i < length; i++) {
			if (i == 0) {
				int tempRand = rand() % 10;
				tempRandTotal = to_string(tempRand);
			}
			if (i != 0) {
				int tempRand = rand() % 10;
				tempRandTotal += to_string(tempRand);
			}
		}
		key << tempRandTotal;
		key.close();
	}
		if (keyNum == 1) {
			cout << to_string(keyNum) + " key have been successfully generated with capability to encrypt messages up to " + to_string(length) + " characters long with the name of the key being " + keyName + ".txt. Press ENTER to exit." << endl;
		}
		else {
			cout << to_string(keyNum) + " keys have been successfully generated with capability to encrypt messages up to " + to_string(length) + " characters long with the name of the keys being ";
			for (int i = 0; i < keyNum; i++) {
				if (keyNum != (i + 1)) {
					cout << keyName + to_string(i) + ".txt and ";
				}
				if (keyNum == (i + 1)) {
					cout << keyName + to_string(i) + ".txt.";
				}
			}
			cout << " Press ENTER to exit." << endl;
		}
		cin.get();
		cin.ignore();
	return 0;
}