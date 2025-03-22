#ifdef _WIN32
#define OS BCryptGenRandom(NULL, &tempRand, 1, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
#include <Windows.h>
#endif // _WIN32
#ifdef __linux__
#define OS getrandom(&tempRand, 1, NULL);
#include <sys/random.h>
#endif // __linux__
#ifdef __APPLE__
#define OS getentropy(&tempRand, 1);
#include <sys/random.h>
#endif // __APPLE__
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
int second::keygen() {
	string numbers = "0123456789";
	string keyNum;
	string length;
	string keyName;
	cout << "How many keys do you want to generate" << endl;
	getline(cin, keyNum);
	for (int i = 0; i < keyNum.size(); i++) {
		if (numbers.find(keyNum[i]) == string::npos) {
			cout << "Please enter a valid number" << endl;
			getline(cin, keyNum);
		}
	}
	cout << "What is the maximum length of your messages" << endl;
	getline(cin, length);
	for (int i = 0; i < length.size(); i++) {
		if (numbers.find(length[i]) == string::npos) {
			cout << "Please enter a valid number" << endl;
			getline(cin, length);
		}
	}
	if (stoul(keyNum) == 1) {
		cout << "What will be the name of your key" << endl;
	}
	else {
		cout << "What will be the name of your keys" << endl;
	}
	getline(cin, keyName);
	fstream key;
	for (int i = 0; i < stoul(keyNum); i++) {
		if (stoul(keyNum) == 1) {
			key.open(keyName + ".txt", ios::out);
		}
		else {
			key.open(keyName + to_string(i) + ".txt", ios::out);
		}
		string tempRandTotal;
		for (int i = 0; i < stoull(length); i++) {
			if (i == 0) {
				long status;
				unsigned char tempRand;
				status = OS;
				int tempRandInt = (int)tempRand % 10;
				tempRandTotal = to_string(tempRandInt);
			}
			if (i != 0) {
				long status;
				unsigned char tempRand;
				status = OS;
				int tempRandInt = (int)tempRand % 10;
				tempRandTotal += to_string(tempRandInt);
			}
		}
		key << tempRandTotal;
		key.close();
	}
	if (stoull(keyNum) == 1) {
		cout << keyNum + " key" + SUCCESSGEN + length + CHARLONG + "key being " + keyName + ".txt." + SAMEDIREXIT << endl;
	}
	else {
		cout << keyNum + " keys" + SUCCESSGEN + length + CHARLONG + "keys being ";
		for (int i = 0; i < stoul(keyNum); i++) {
			if (stoul(keyNum) != (i + 1)) {
				cout << keyName + to_string(i) + ".txt and ";
			}
			if (stoul(keyNum) == (i + 1)) {
				cout << keyName + to_string(i) + ".txt.";
			}
		}
		cout << SAMEDIREXIT << endl;
	}
	cin.get();
	cin.ignore();
	return 0;
}