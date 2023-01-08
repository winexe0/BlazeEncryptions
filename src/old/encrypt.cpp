#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "../split.h"
#include "encrypt.h"
using namespace std;
int old::encrypt() {
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string ualphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string newMessage, message;
	int key, type;
	cout << "Do you want to\n1. Encrypt a text file\n2. Encrypt a message\nPlease type 1 or 2 and press enter." << endl;
	cin >> type;
	if (type == 1) {
		string fileLocation;
		cout << "What is the name or path of the text file" << endl;
		cin >> fileLocation;
		cout << "Please enter a encryption key in number form to encrypt the text file?" << endl;
		cin >> key;
		fstream FileToEncrypt;
		FileToEncrypt.open(fileLocation, ios::in);
		if (!FileToEncrypt) {
			while (!FileToEncrypt) {
				cout << "Your file '" + fileLocation + "' doesn't exist. Please enter an existing filename." << endl;
				cin >> fileLocation;
				FileToEncrypt.open(fileLocation, ios::in);
			}
		}
			string line, FileToEncryptContents;
			while (getline(FileToEncrypt, line)) {
				vector<string> row_values;
				split(line, '\t', row_values);
				for (auto v : row_values)
					FileToEncryptContents += v;
				for (int i = 0; i < FileToEncryptContents.size(); i++) {
					size_t letterPos = alphabet.find(FileToEncryptContents[i]);
					size_t letterPosU = ualphabet.find(FileToEncryptContents[i]);
					if (letterPos == string::npos && letterPosU == string::npos) {
						newMessage += FileToEncryptContents[i];
					}
					if (letterPos != string::npos) {
						int newPosition;
						newPosition = letterPos + key;
						if (newPosition > alphabet.size()) {
							newPosition = newPosition - alphabet.size();
						}
						if (newPosition == 26) {
							newPosition = 0;
						}
						int newCharacter = alphabet[newPosition];
						newMessage += newCharacter;
					}
					if (letterPosU != string::npos) {
						int newPosition;
						newPosition = letterPosU + key;
						if (newPosition > ualphabet.size()) {
							newPosition = newPosition - ualphabet.size();
						}
						if (newPosition == 26) {
							newPosition = 0;
						}
						int newCharacter = ualphabet[newPosition];
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
	if (type == 2) {
		cout << "Please enter a message to encrypt?" << endl;
		cin.ignore();
		getline(cin, message);
		cout << "Please enter a encryption key in number form to encrypt the message?" << endl;
		cin >> key;
		for (int i = 0; i < message.size(); i++) {
			size_t letterPos = alphabet.find(message[i]);
			size_t letterPosU = ualphabet.find(message[i]);
			if (letterPos == string::npos && letterPosU == string::npos) {
				newMessage += message[i];
			}
			if (letterPos != string::npos) {
				int newPosition;
				newPosition = letterPos + key;
				if (newPosition > alphabet.size()) {
					newPosition = newPosition - alphabet.size();
				}
				if (newPosition == 26) {
					newPosition = 0;
				}
				int newCharacter = alphabet[newPosition];
				newMessage += newCharacter;
			}
			if (letterPosU != string::npos) {
				int newPosition;
				newPosition = letterPosU + key;
				if (newPosition > ualphabet.size()) {
					newPosition = newPosition - ualphabet.size();
				}
				if (newPosition == 26) {
					newPosition = 0;
				}
				int newCharacter = ualphabet[newPosition];
				newMessage += newCharacter;
			}
		}
		cout << "Your encrypted message is '" + newMessage + "'\nPress ENTER to exit" << endl;
		cin.ignore();
		cin.get();
		return 0;
	}
	else {
		cout << "Unrecognized Option: '" + to_string(type) + "'. ";
		encrypt();
	}
	return 0;
}