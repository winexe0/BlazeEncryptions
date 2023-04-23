#define SUCCESSGEN " have been successfully generated with capability to encrypt messages up to "
#define CHARLONG " characters long with the name of the "
#define SAMEDIREXIT " This can be found at the same directory that BlazeEncryptions was run. Press ENTER to exit."
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
	cin.ignore();
	getline(cin, keyName);
	srand(time(0));
	fstream key;
	for (int i = 0; i < keyNum; i++) {
		if (keyNum == 1) {
			key.open(keyName + ".txt", ios::out);
		}
		else {
			key.open(keyName + to_string(i) + ".txt", ios::out);
		}
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
		cout << to_string(keyNum) + " key" + SUCCESSGEN + to_string(length) + CHARLONG + "key being " + keyName + ".txt." + SAMEDIREXIT << endl;
	}
	else {
		cout << to_string(keyNum) + " keys" + SUCCESSGEN + to_string(length) + CHARLONG + "keys being ";
		for (int i = 0; i < keyNum; i++) {
			if (keyNum != (i + 1)) {
				cout << keyName + to_string(i) + ".txt and ";
			}
			if (keyNum == (i + 1)) {
				cout << keyName + to_string(i) + ".txt.";
			}
		}
		cout << SAMEDIREXIT << endl;
	}
	cin.get();
	cin.ignore();
	return 0;
}