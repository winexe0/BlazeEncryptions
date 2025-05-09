#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "../split.h"
#include "encrypt.h"
#include "fileSize.h"
#include "new.h"
using namespace fourth;
int fourth::encrypt() {
	string newMessage, message, key;
	string type;
	try {
		cout << "Do you want to\n1. Encrypt a text file\n2. Encrypt a message\nPlease type 1 or 2 and press enter." << endl;
		getline(cin, type);
		if (stoi(type) != 1 && stoi(type) != 2) throw 1;
	}
	catch (...) {
		cout << "Unrecognized Option: '" + type + "'. ";
		encrypt();
		return 0;
	}
	if (stoi(type) == 1) {
		string fileLocation;
		cout << "What is the name or path of the text file" << endl;
		getline(cin, fileLocation);
		cout << "Please enter the encryption key filename to encrypt the text file?" << endl;
		getline(cin, key);
		fstream keyOpen;
		keyOpen.open(key, ios::in);
		while (!keyOpen) {
			keyOpen.open(key + ".txt", ios::in);
			if (!keyOpen) {
				keyOpen.open(key + "0.txt", ios::in);
				if (!keyOpen) {
					cout << "Your key '" + key + "' doesn't exist. Please enter an existing filename." << endl;
					getline(cin, key);
					keyOpen.open(key, ios::in);
				}
			}
		}
		string Keyline, keyContents;
		bool bypass = false;
		//filesystem::path keylength(key);
		while (fileLocation.size() > 2*fileSize(key) || fileLocation.size() > 2*fileSize(key + ".txt") || fileLocation.size() > 2*fileSize(key + "0.txt")) {
			cout << "The key '" + key + "' is not long enough to encrypt your file '" + fileLocation + "'. Please specify a key of at least " + to_string(message.size()) + " in length." << endl;
			getline(cin, key);
			//filesystem::path keylength(key);
			keyOpen.close();
			keyOpen.open(key, ios::in);
			while (!keyOpen) {
				keyOpen.open(key + ".txt", ios::in);
				if (!keyOpen) {
					keyOpen.open(key + "0.txt", ios::in);
					if (!keyOpen) {
						cout << "Your key '" + key + "' doesn't exist. Please enter an existing filename." << endl;
						getline(cin, key);
						keyOpen.open(key, ios::in);
					}
				}
			}
			while (getline(keyOpen, Keyline)) {
				vector<string> row_values;
				split(Keyline, '\t', row_values);
				for (auto v : row_values)
					keyContents += v;
			}
			while (keyContents == "") {
				keyOpen.close();
				keyOpen.open(key + ".txt", ios::in);
				while (!keyOpen) {
					keyOpen.open(key + ".txt", ios::in);
					if (!keyOpen) {
						keyOpen.open(key + "0.txt", ios::in);
						if (!keyOpen) {
							cout << "Your key '" + key + "' doesn't exist. Please enter an existing filename." << endl;
							getline(cin, key);
							keyOpen.open(key, ios::in);
						}
					}
				}
				while (getline(keyOpen, Keyline)) {
					vector<string> row_values;
					split(Keyline, '\t', row_values);
					for (auto v : row_values)
						keyContents += v;
				}
			}
			bypass = true;
		}
		if (bypass == false) {
			keyOpen.close();
			keyOpen.open(key, ios::in);
			while (!keyOpen) {
				keyOpen.open(key + ".txt", ios::in);
				if (!keyOpen) {
					keyOpen.open(key + "0.txt", ios::in);
					if (!keyOpen) {
						cout << "Your key '" + key + "' doesn't exist. Please enter an existing filename." << endl;
						getline(cin, key);
						keyOpen.open(key, ios::in);
					}
				}
			}
			while (getline(keyOpen, Keyline)) {
				vector<string> row_values;
				split(Keyline, '\t', row_values);
				for (auto v : row_values)
					keyContents += v;
			}
		}
		fstream FileToEncrypt;
		FileToEncrypt.open(fileLocation, ios::in);
		if (!FileToEncrypt) {
			while (!FileToEncrypt) {
				cout << "Your file '" + fileLocation + "' doesn't exist. Please enter an existing filename." << endl;
				getline(cin, fileLocation);
				FileToEncrypt.open(fileLocation, ios::in);
			}
		}
		string line, FileToEncryptContents;
		while (getline(FileToEncrypt, line)) {
			vector<string> row_values;
			split(line, '\t', row_values);
			for (auto v : row_values)
				FileToEncryptContents += v;
			for (unsigned long long i = 0; i < FileToEncryptContents.size(); i++) {
				string keyContentsInt;
				keyContentsInt = keyContents[2*i];
				size_t letterPos = characters.find(FileToEncryptContents[i]);
				if (letterPos == string::npos) {
					newMessage += FileToEncryptContents[i];
				}
				if (letterPos != string::npos) {
					int newPosition;
					newPosition = letterPos + 10*stoi(keyContentsInt);
					keyContentsInt = keyContents[2*i+1];
					newPosition = newPosition + stoi(keyContentsInt);
					if (newPosition > characters.size()) {
						newPosition = newPosition - characters.size();
					}
					if (newPosition == 92) {
						newPosition = 0;
					}
					int newCharacter = characters[newPosition];
					newMessage += newCharacter;
				}
			}
		}
		fstream EncryptedFile;
		size_t DotPos = fileLocation.find('.');
		string Final;
		if (DotPos != string::npos) {
			fileLocation[DotPos] = '-';
			if (fileLocation[DotPos + 1] == 't') {
				fileLocation[DotPos + 1] = 'E';
				if (fileLocation[DotPos + 2] == 'x') {
					fileLocation[DotPos + 2] = 'n';
					if (fileLocation[DotPos + 3] == 't') {
						fileLocation[DotPos + 3] = 'c';
						EncryptedFile.open(fileLocation + "rypted.txt", ios::out);
						Final = fileLocation + "rypted.txt";
					}
				}
			}
		}
		if (DotPos == string::npos) {
			EncryptedFile.open(fileLocation + "-Encrypted", ios::out);
			Final = fileLocation + "-Encrypted";
		}
		if (!EncryptedFile) {
			cout << "Could not create the encrypted file. Here is the encrypted text file '" + newMessage + "'\nPress ENTER to exit";
			cin.ignore();
			cin.get();
			return 0;
		}
		else {
			EncryptedFile << newMessage;
			EncryptedFile.close();
			cout << "Your Encrypted File is saved to " + Final + "\nPress ENTER to exit";
			cin.ignore();
			cin.get();
			return 0;
		}
	}
	if (stoi(type) == 2) {
		cout << "Please enter a message to encrypt?" << endl;
		getline(cin, message);
		cout << "Please enter the encryption key filename to encrypt the message?" << endl;
		getline(cin, key);
		fstream keyOpen;
		keyOpen.open(key, ios::in);
		while (!keyOpen) {
			keyOpen.open(key + ".txt", ios::in);
			if (!keyOpen) {
				keyOpen.open(key + "0.txt", ios::in);
				if (!keyOpen) {
					cout << "Your key '" + key + "' doesn't exist. Please enter an existing filename." << endl;
					getline(cin, key);
					keyOpen.open(key, ios::in);
				}

			}
		}
		string line, keyContents;
		bool bypass = false;
		while (message.size() > 2*fileSize(key) || message.size() > 2*fileSize(key + ".txt") || message.size() > 2*fileSize(key + "0.txt")) {
			cout << "The key '" + key + "' is not long enough to encrypt your message '" + message + "'. Please specify a key of at least " + to_string(message.size()) + " in length." << endl;
			getline(cin, key);
			keyOpen.close();
			keyOpen.open(key, ios::in);
			while (!keyOpen) {
				keyOpen.open(key + ".txt", ios::in);
				if (!keyOpen) {
					keyOpen.open(key + "0.txt", ios::in);
					if (!keyOpen) {
						cout << "Your key '" + key + "' doesn't exist. Please enter an existing filename." << endl;
						getline(cin, key);
						keyOpen.open(key, ios::in);
					}
				}
			}
			while (getline(keyOpen, line)) {
				vector<string> row_values;
				split(line, '\t', row_values);
				for (auto v : row_values)
					keyContents += v;
			}
			while (keyContents == "") {
				keyOpen.close();
				keyOpen.open(key + ".txt", ios::in);
				while (!keyOpen) {
					keyOpen.open(key + ".txt", ios::in);
					if (!keyOpen) {
						keyOpen.open(key + "0.txt", ios::in);
						if (!keyOpen) {
							cout << "Your key '" + key + "' doesn't exist. Please enter an existing filename." << endl;
							getline(cin, key);
							keyOpen.open(key, ios::in);
						}
					}
				}
				while (getline(keyOpen, line)) {
					vector<string> row_values;
					split(line, '\t', row_values);
					for (auto v : row_values)
						keyContents += v;
				}
			}
			bypass = true;
		}
		if (bypass == false) {
			keyOpen.close();
			keyOpen.open(key, ios::in);
			while (!keyOpen) {
				keyOpen.open(key + ".txt", ios::in);
				if (!keyOpen) {
					keyOpen.open(key + "0.txt", ios::in);
					if (!keyOpen) {
						cout << "Your key '" + key + "' doesn't exist. Please enter an existing filename." << endl;
						getline(cin, key);
						keyOpen.open(key, ios::in);
					}
				}
			}
			while (getline(keyOpen, line)) {
				vector<string> row_values;
				split(line, '\t', row_values);
				for (auto v : row_values)
					keyContents += v;
			}
			while (keyContents == "") {
				keyOpen.close();
				keyOpen.open(key + ".txt", ios::in);
				while (!keyOpen) {
					keyOpen.open(key + ".txt", ios::in);
					if (!keyOpen) {
						keyOpen.open(key + "0.txt", ios::in);
						if (!keyOpen) {
							cout << "Your key '" + key + "' doesn't exist. Please enter an existing filename." << endl;
							getline(cin, key);
							keyOpen.open(key, ios::in);
						}
					}
				}
				while (getline(keyOpen, line)) {
					vector<string> row_values;
					split(line, '\t', row_values);
					for (auto v : row_values)
						keyContents += v;
				}
			}
		}
		for (unsigned long long i = 0; i < message.size(); i++) {
			string keyContentsInt;
			keyContentsInt = keyContents[2*i];
			size_t letterPos = characters.find(message[i]);
			if (letterPos == string::npos) {
				newMessage += message[i];
			}
			if (letterPos != string::npos) {
				int newPosition;
				newPosition = letterPos + 10*stoi(keyContentsInt);
				keyContentsInt = keyContents[2*i+1];
				newPosition = newPosition + stoi(keyContentsInt);
				if (newPosition > characters.size()) {
					newPosition = newPosition - characters.size();
				}
				if (newPosition == 92) {
					newPosition = 0;
				}
				int newCharacter = characters[newPosition];
				newMessage += newCharacter;
			}
		}
		cout << "Your encrypted message is '" + newMessage + "'\nPress ENTER to exit" << endl;
		cin.ignore();
		cin.get();
		return 0;
	}
	return 0;
}