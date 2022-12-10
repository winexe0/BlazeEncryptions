#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "split.h"
#include "decrypt.h"
using namespace std;
int decrypt() {
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string newMessage, message, type;
	int key;
	cout << "Do you want to decrypt a text file or a message" << endl;
	cin.ignore();
	getline(cin, type);
	if (type == "text file" || type == "Text File" || type == "File" || type == "file") {
		string fileLocation;
		cout << "What is the name or path of the text file" << endl;
		cin >> fileLocation;
		cout << "Please enter the decryption key in number form to decrypt the text file?" << endl;
		cin >> key;
		fstream FileToDecrypt;
		FileToDecrypt.open(fileLocation, ios::in);
		if (!FileToDecrypt) {
			while (!FileToDecrypt) {
				cout << "Your file '" + fileLocation + "' doesn't exist. Please enter an existing filename." << endl;
				cin >> fileLocation;
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
					size_t letterPos = alphabet.find(FileToDecryptContents[i]);
					if (letterPos == string::npos) {
						newMessage += FileToDecryptContents[i];
					}
					if (letterPos != string::npos) {
						int newPosition;
						newPosition = letterPos - key;
						if (newPosition < 0) {
							newPosition = newPosition + alphabet.size();
						}
						int newCharacter = alphabet[newPosition];
						newMessage += newCharacter;
					}
				}
			}
		fstream DecryptedFile;
		DecryptedFile.open(fileLocation + "-Decrypted", ios::out);
		if (!DecryptedFile) {
			cout << "Could not create the decrypted file. Here is the decrypted text file '" + newMessage + "'. Press ENTER to exit";
			cin.ignore();
			cin.get();
		}
		else {
			DecryptedFile << newMessage;
			DecryptedFile.close();
			cout << "Your Decrypted File is saved to " + fileLocation + "-Decrypted. Press ENTER to exit";
			cin.ignore();
			cin.get();
		}
	}
	if (type == "message" || type == "Message") {
		cout << "Please enter a message to decrypt?" << endl;
		getline(cin, message);
		cout << "Please enter a decryption key in number form to decrypt the message?" << endl;
		cin >> key;
		for (int i = 0; i < message.size(); i++) {
			size_t letterPos = alphabet.find(message[i]);
			if (letterPos == string::npos) {
				newMessage += message[i];
			}
			if (letterPos != string::npos) {
				int newPosition;
				newPosition = letterPos - key;
				if (newPosition < 0) {
					newPosition = alphabet.size() + newPosition;
				}
				int newCharacter = alphabet[newPosition];
				newMessage += newCharacter;
			}
		}
		cout << "Your decrypted message is '" + newMessage + "'. Press ENTER to exit" << endl;
	}
	else {
		cout << "Unrecognized Option: '" + type + "'. ";
		decrypt();
	}
	return 0;
}