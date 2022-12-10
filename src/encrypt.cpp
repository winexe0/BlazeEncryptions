#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "split.h"
#include "encrypt.h"
using namespace std;
int encrypt() {
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string newMessage, message, type;
	int key;
	cout << "Do you want to encrypt a text file or a message" << endl;
	cin.ignore();
	getline(cin, type);
	if (type == "text file" || type == "Text File" || type == "File" || type == "file") {
		string fileLocation;
		cout << "What is the name or path of the text file" << endl;
		cin >> fileLocation;
		cout << "Please enter a encryption key to encrypt the text file?" << endl;
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
					if (letterPos == string::npos) {
						newMessage += FileToEncryptContents[i];
					}
					if (letterPos != string::npos) {
						int newPosition;
						newPosition = letterPos + key;
						if (newPosition > alphabet.size()) {
							newPosition = newPosition - alphabet.size();
						}
						int newCharacter = alphabet[newPosition];
						newMessage += newCharacter;
					}
				}
			}
		fstream EncryptedFile;
		EncryptedFile.open(fileLocation + "-Encrypted", ios::out);
		if (!EncryptedFile) {
			cout << "Could not create the encrypted file. Here is the encrypted text file '" + newMessage + "'. Press ENTER to exit";
			cin.ignore();
			cin.get();
		}
		else {
			EncryptedFile << newMessage;
			EncryptedFile.close();
			cout << "Your Encrypted File is saved to " + fileLocation + "-Encrypted. Press ENTER to exit";
			cin.ignore();
			cin.get();
		}
	}
	if (type == "message" || type == "Message") {
		cout << "Please enter a message to encrypt?" << endl;
		getline(cin, message);
		cout << "Please enter a encryption key to encrypt the message?" << endl;
		cin >> key;
		for (int i = 0; i < message.size(); i++) {
			size_t letterPos = alphabet.find(message[i]);
			if (letterPos == string::npos) {
				newMessage += message[i];
			}
			if (letterPos != string::npos) {
				int newPosition;
				newPosition = letterPos + key;
				if (newPosition > alphabet.size()) {
					newPosition = newPosition - alphabet.size();
				}
				int newCharacter = alphabet[newPosition];
				newMessage += newCharacter;
			}
		}
		cout << "Your encrypted message is '" + newMessage + "'. Press ENTER to exit" << endl;
	}
	return 0;
}