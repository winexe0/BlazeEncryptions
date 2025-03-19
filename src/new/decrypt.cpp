#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "../split.h"
#include "decrypt.h"
using namespace std;
int New::decrypt() {
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string ualphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string newMessage, message, key;
	string type;
	try {
		cout << "Do you want to\n1. Decrypt a text file\n2. Decrypt a message\nPlease type 1 or 2 and press enter." << endl;
		getline(cin, type);
		if (stoi(type) != 1 && stoi(type) != 2) throw 1;
	}
	catch (...) {
		cout << "Unrecognized Option: '" + type + "'. ";
		decrypt();
		return 0;
	}
	if (stoi(type) == 1) {
		string fileLocation;
		cout << "What is the name or path of the text file" << endl;
		getline(cin, fileLocation);
		cout << "Please enter the decryption key filename to decrypt the text file?" << endl;
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
		while (getline(keyOpen, Keyline)) {
			vector<string> row_values;
			split(Keyline, '\t', row_values);
			for (auto v : row_values)
				keyContents += v;
		}
		fstream FileToDecrypt;
		FileToDecrypt.open(fileLocation, ios::in);
		if (!FileToDecrypt) {
			while (!FileToDecrypt) {
				cout << "Your file '" + fileLocation + "' doesn't exist. Please enter an existing filename." << endl;
				getline(cin, fileLocation);
				FileToDecrypt.open(fileLocation, ios::in);
			}
		}
		string line, FileToDecryptContents;
		while (getline(FileToDecrypt, line)) {
			vector<string> row_values;
			split(line, '\t', row_values);
			for (auto v : row_values)
				FileToDecryptContents += v;
			for (int i = 0; i < FileToDecryptContents.size(); i++) {
				string keyContentsInt;
				keyContentsInt = keyContents[i];
				size_t letterPos = alphabet.find(FileToDecryptContents[i]);
				size_t letterPosU = ualphabet.find(FileToDecryptContents[i]);
				if (letterPos == string::npos && letterPosU == string::npos) {
					newMessage += FileToDecryptContents[i];
				}
				if (letterPos != string::npos) {
					int newPosition;
					newPosition = letterPos - stoi(keyContentsInt);
					if (newPosition < 0) {
						newPosition = newPosition + alphabet.size();
					}
					if (newPosition == 26) {
						newPosition = 0;
					}
					int newCharacter = alphabet[newPosition];
					newMessage += newCharacter;
				}
				if (letterPosU != string::npos) {
					int newPosition;
					newPosition = letterPosU - stoi(keyContentsInt);
					if (newPosition < 0) {
						newPosition = newPosition + ualphabet.size();
					}
					if (newPosition == 26) {
						newPosition = 0;
					}
					int newCharacter = ualphabet[newPosition];
					newMessage += newCharacter;
				}
			}
		}
		fstream DecryptedFile;
		size_t DotPos = fileLocation.find('.');
		string Final;
		if (DotPos != string::npos) {
			fileLocation[DotPos] = '-';
			if (fileLocation[DotPos + 1] == 't') {
				fileLocation[DotPos + 1] = 'D';
				if (fileLocation[DotPos + 2] == 'x') {
					fileLocation[DotPos + 2] = 'e';
					if (fileLocation[DotPos + 3] == 't') {
						fileLocation[DotPos + 3] = 'c';
						DecryptedFile.open(fileLocation + "rypted.txt", ios::out);
						Final = fileLocation + "rypted.txt";
					}
				}
			}
		}
		if (DotPos == string::npos) {
			DecryptedFile.open(fileLocation + "-Decrypted", ios::out);
			Final = fileLocation + "-Decrypted";
		}
		if (!DecryptedFile) {
			cout << "Could not create the decrypted file. Here is the decrypted text file '" + newMessage + "'\nPress ENTER to exit";
			cin.ignore();
			cin.get();
			return 0;
		}
		else {
			DecryptedFile << newMessage;
			DecryptedFile.close();
			cout << "Your Decrypted File is saved to " + Final + "\nPress ENTER to exit";
			cin.ignore();
			cin.get();
			return 0;
		}
	}
	if (stoi(type) == 2) {
		cout << "Please enter a message to decrypt?" << endl;
		getline(cin, message);
		cout << "Please enter the decryption key filename to decrypt the message?" << endl;
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
		while (getline(keyOpen, line)) {
			vector<string> row_values;
			split(line, '\t', row_values);
			for (auto v : row_values)
				keyContents += v;
		}
		for (int i = 0; i < message.size(); i++) {
			string keyContentsInt;
			keyContentsInt = keyContents[i];
			size_t letterPos = alphabet.find(message[i]);
			size_t letterPosU = ualphabet.find(message[i]);
			if (letterPos == string::npos && letterPosU == string::npos) {
				newMessage += message[i];
			}
			if (letterPos != string::npos) {
				int newPosition;
				newPosition = letterPos - stoi(keyContentsInt);
				if (newPosition < 0) {
					newPosition = alphabet.size() + newPosition;
				}
				if (newPosition == 26) {
					newPosition = 0;
				}
				int newCharacter = alphabet[newPosition];
				newMessage += newCharacter;
			}
			if (letterPosU != string::npos) {
				int newPosition;
				newPosition = letterPosU - stoi(keyContentsInt);
				if (newPosition < 0) {
					newPosition = ualphabet.size() + newPosition;
				}
				if (newPosition == 26) {
					newPosition = 0;
				}
				int newCharacter = ualphabet[newPosition];
				newMessage += newCharacter;
			}
		}
		cout << "Your decrypted message is '" + newMessage + "'\nPress ENTER to exit" << endl;
		cin.ignore();
		cin.get();
		return 0;
	}
	return 0;
}