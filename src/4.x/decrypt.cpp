#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <cstdint>
#ifdef __SSE2__
#include <immintrin.h>
#endif
#ifdef __ARM_NEON
#include <arm_neon.h>
#endif
#include "../split.h"
#include "decrypt.h"
#include "new.h"
using namespace std;
using namespace fourth;
int fourth::decrypt() {
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
#ifdef __SSE2__
		size_t len = FileToDecryptContents.size();
		newMessage.resize(len);
		
		__m128i addTen = _mm_set1_epi16(10);  // Set 10 in all 16-bit positions
		__m128i charSize = _mm_set1_epi16(characters.size());
		__m128i specialValue = _mm_set1_epi16(92);  // Special case where newPos == 92
	
		for (size_t i = 0; i < len; i += 8) {  // Process 8 characters at a time
			alignas(16) uint16_t keyVals1[8], keyVals2[8], letterPositions[8];
	
			for (int j = 0; j < 8; j++) {
				// Get the position of message[i+j] in characters
				size_t letterPos = characters.find(FileToDecryptContents[i + j]);
				if (letterPos == string::npos) {  // If character is not found, keep it unchanged
					newMessage[i + j] = FileToDecryptContents[i + j];
					letterPositions[j] = 0;  // Placeholder for unused positions
					keyVals1[j] = 0;
					keyVals2[j] = 0;
					continue;
				}
	
				letterPositions[j] = static_cast<uint16_t>(letterPos);
	
				// Convert keyContents characters to integers
				keyVals1[j] = (2 * (i + j) < keyContents.size()) ? keyContents[2 * (i + j)] - '0' : 0;
				keyVals2[j] = ((i + j + 1) < keyContents.size()) ? keyContents[i + j + 1] - '0' : 0;
			}
	
			__m128i keyChunk1 = _mm_load_si128((__m128i*)keyVals1); // Load first key part
			__m128i keyChunk2 = _mm_load_si128((__m128i*)keyVals2); // Load second key part
			__m128i letterPosChunk = _mm_load_si128((__m128i*)letterPositions); // Load original positions
	
			// Multiply first key part by 10
			__m128i shiftedKeys = _mm_mullo_epi16(keyChunk1, addTen);
	
			// Add second key part and letter position
			__m128i newPos = _mm_sub_epi16(_mm_sub_epi16(letterPosChunk, shiftedKeys), keyChunk2);
	
			// Handle overflow by wrapping around
			__m128i underflowMask = _mm_cmplt_epi16(newPos, _mm_setzero_si128());
			newPos = _mm_add_epi16(newPos, _mm_and_si128(underflowMask, charSize));
	
			// Special case: If newPosition == 92, set to 0
			__m128i specialCase = _mm_cmpeq_epi16(newPos, specialValue);
			newPos = _mm_or_si128(_mm_and_si128(specialCase, _mm_setzero_si128()), 
								  _mm_andnot_si128(specialCase, newPos));
	
			// Store the transformed values back into newMessage
			for (int j = 0; j < 8; j++) {
				if (letterPositions[j] == 0) continue;  // Skip unchanged characters
				int idx = ((uint16_t*)&newPos)[j];
				newMessage[i + j] = characters[idx];
			}
		}
		#elif __ARM_NEON
		size_t len = message.size();
		newMessage.resize(len);
	
		uint16x8_t addTen = vdupq_n_u16(10);  // Vector of 10s
		uint16x8_t charSize = vdupq_n_u16(characters.size());
		uint16x8_t specialValue = vdupq_n_u16(92);  // Special case where newPos == 92
		int16x8_t specialValueSigned = vreinterpretq_s16_u16(specialValue);
	
		for (size_t i = 0; i < len; i += 8) {  // Process 8 characters at a time
			uint16_t keyVals1[8], keyVals2[8], letterPositions[8];
	
			for (int j = 0; j < 8; j++) {
				size_t index = i + j;
				if (index >= len) break;
	
				size_t letterPos = characters.find(message[index]);
				if (letterPos == std::string::npos) {
					newMessage[index] = message[index];  // Keep unchanged
					letterPositions[j] = 0;
					keyVals1[j] = 0;
					keyVals2[j] = 0;
					continue;
				}
	
				letterPositions[j] = static_cast<uint16_t>(letterPos);
	
				keyVals1[j] = (2 * index < keyContents.size()) ? keyContents[2 * index] - '0' : 0;
				keyVals2[j] = ((index + 1) < keyContents.size()) ? keyContents[index + 1] - '0' : 0;
			}
	
			uint16x8_t keyChunk1 = vld1q_u16(keyVals1);
			uint16x8_t keyChunk2 = vld1q_u16(keyVals2);
			uint16x8_t letterPosChunk = vld1q_u16(letterPositions);
			uint16x8_t shiftedKeys = vmulq_u16(keyChunk1, addTen);
	
			// Convert unsigned to signed before doing signed operations
			int16x8_t letterPosChunkSigned = vreinterpretq_s16_u16(letterPosChunk);
			int16x8_t shiftedKeysSigned = vreinterpretq_s16_u16(shiftedKeys);
			int16x8_t keyChunk2Signed = vreinterpretq_s16_u16(keyChunk2);
	
			// Multiply first key part by 10
			
	
			// Subtract shiftedKeys and keyChunk2 from letterPosChunk
			int16x8_t newPos = vsubq_s16(vsubq_s16(letterPosChunkSigned, shiftedKeysSigned), keyChunk2Signed);
	
			// Handle overflow/underflow by wrapping around
			uint16x8_t underflowMask = vcltq_s16(newPos, vdupq_n_s16(0));
	
			// Adjust newPos if negative (less than 0), add charSize
			newPos = vbslq_s16(underflowMask, vaddq_s16(newPos, vdupq_n_s16(characters.size())), newPos);
	
	
			// Special case: If newPosition == 92, set to 0
			uint16x8_t specialCase = vceqq_s16(newPos, specialValueSigned);
			newPos = vbslq_s16(specialCase, vdupq_n_s16(0), newPos);
	
			// Store results back into newMessage
			for (int j = 0; j < 8; j++) {
				size_t index = i + j;
				if (index >= len || letterPositions[j] == 0) continue;
				int16_t newPosArray[8];
				vst1q_s16(newPosArray, newPos);  // Store vector into array
	
				for (int j = 0; j < 8; j++) {
					size_t index = i + j;
					if (index >= len || letterPositions[j] == 0) continue;
					newMessage[index] = characters[static_cast<size_t>(newPosArray[j])];
				}
			}
		}
#else

			for (unsigned long long i = 0; i < FileToDecryptContents.size(); i++) {
				string keyContentsInt;
				keyContentsInt = keyContents[2*i];
				size_t letterPos = characters.find(FileToDecryptContents[i]);
				if (letterPos == string::npos) {
					newMessage += FileToDecryptContents[i];
				}
				if (letterPos != string::npos) {
					int newPosition;
					newPosition = letterPos - 10*stoi(keyContentsInt);
					keyContentsInt = keyContents[i+1];
					newPosition = newPosition - stoi(keyContentsInt);
					if (newPosition < 0) {
						newPosition = characters.size() + newPosition;
					}
					if (newPosition == 92) {
						newPosition = 0;
					}
					int newCharacter = characters[newPosition];
					newMessage += newCharacter;
				}
			}
#endif
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
#ifdef __SSE2__
		size_t len = message.size();
		newMessage.resize(len);
		
		__m128i addTen = _mm_set1_epi16(10);  // Set 10 in all 16-bit positions
		__m128i charSize = _mm_set1_epi16(characters.size());
		__m128i specialValue = _mm_set1_epi16(92);  // Special case where newPos == 92
	
		for (size_t i = 0; i < len; i += 8) {  // Process 8 characters at a time
			alignas(16) uint16_t keyVals1[8], keyVals2[8], letterPositions[8];
	
			for (int j = 0; j < 8; j++) {
				// Get the position of message[i+j] in characters
				size_t letterPos = characters.find(message[i + j]);
				if (letterPos == string::npos) {  // If character is not found, keep it unchanged
					newMessage[i + j] = message[i + j];
					letterPositions[j] = 0;  // Placeholder for unused positions
					keyVals1[j] = 0;
					keyVals2[j] = 0;
					continue;
				}
	
				letterPositions[j] = static_cast<uint16_t>(letterPos);
	
				// Convert keyContents characters to integers
				keyVals1[j] = (2 * (i + j) < keyContents.size()) ? keyContents[2 * (i + j)] - '0' : 0;
				keyVals2[j] = ((i + j + 1) < keyContents.size()) ? keyContents[i + j + 1] - '0' : 0;
			}
	
			__m128i keyChunk1 = _mm_load_si128((__m128i*)keyVals1); // Load first key part
			__m128i keyChunk2 = _mm_load_si128((__m128i*)keyVals2); // Load second key part
			__m128i letterPosChunk = _mm_load_si128((__m128i*)letterPositions); // Load original positions
	
			// Multiply first key part by 10
			__m128i shiftedKeys = _mm_mullo_epi16(keyChunk1, addTen);
	
			// Add second key part and letter position
			__m128i newPos = _mm_sub_epi16(_mm_sub_epi16(letterPosChunk, shiftedKeys), keyChunk2);
	
			// Handle overflow by wrapping around
			__m128i underflowMask = _mm_cmplt_epi16(newPos, _mm_setzero_si128());
			newPos = _mm_add_epi16(newPos, _mm_and_si128(underflowMask, charSize));
	
			// Special case: If newPosition == 92, set to 0
			__m128i specialCase = _mm_cmpeq_epi16(newPos, specialValue);
			newPos = _mm_or_si128(_mm_and_si128(specialCase, _mm_setzero_si128()), 
								  _mm_andnot_si128(specialCase, newPos));
	
			// Store the transformed values back into newMessage
			for (int j = 0; j < 8; j++) {
				if (letterPositions[j] == 0) continue;  // Skip unchanged characters
				int idx = ((uint16_t*)&newPos)[j];
				newMessage[i + j] = characters[idx];
			}
		}
		#elif __ARM_NEON
		size_t len = message.size();
		newMessage.resize(len);
	
		uint16x8_t addTen = vdupq_n_u16(10);  // Vector of 10s
		uint16x8_t charSize = vdupq_n_u16(characters.size());
		uint16x8_t specialValue = vdupq_n_u16(92);  // Special case where newPos == 92
		int16x8_t specialValueSigned = vreinterpretq_s16_u16(specialValue);
	
		for (size_t i = 0; i < len; i += 8) {  // Process 8 characters at a time
			uint16_t keyVals1[8], keyVals2[8], letterPositions[8];
	
			for (int j = 0; j < 8; j++) {
				size_t index = i + j;
				if (index >= len) break;
	
				size_t letterPos = characters.find(message[index]);
				if (letterPos == std::string::npos) {
					newMessage[index] = message[index];  // Keep unchanged
					letterPositions[j] = 0;
					keyVals1[j] = 0;
					keyVals2[j] = 0;
					continue;
				}
	
				letterPositions[j] = static_cast<uint16_t>(letterPos);
	
				keyVals1[j] = (2 * index < keyContents.size()) ? keyContents[2 * index] - '0' : 0;
				keyVals2[j] = ((index + 1) < keyContents.size()) ? keyContents[index + 1] - '0' : 0;
			}
	
			uint16x8_t keyChunk1 = vld1q_u16(keyVals1);
			uint16x8_t keyChunk2 = vld1q_u16(keyVals2);
			uint16x8_t letterPosChunk = vld1q_u16(letterPositions);
			uint16x8_t shiftedKeys = vmulq_u16(keyChunk1, addTen);
	
			// Convert unsigned to signed before doing signed operations
			int16x8_t letterPosChunkSigned = vreinterpretq_s16_u16(letterPosChunk);
			int16x8_t shiftedKeysSigned = vreinterpretq_s16_u16(shiftedKeys);
			int16x8_t keyChunk2Signed = vreinterpretq_s16_u16(keyChunk2);
	
			// Multiply first key part by 10
			
	
			// Subtract shiftedKeys and keyChunk2 from letterPosChunk
			int16x8_t newPos = vsubq_s16(vsubq_s16(letterPosChunkSigned, shiftedKeysSigned), keyChunk2Signed);
	
			// Handle overflow/underflow by wrapping around
			uint16x8_t underflowMask = vcltq_s16(newPos, vdupq_n_s16(0));
	
			// Adjust newPos if negative (less than 0), add charSize
			newPos = vbslq_s16(underflowMask, vaddq_s16(newPos, vdupq_n_s16(characters.size())), newPos);
	
	
			// Special case: If newPosition == 92, set to 0
			uint16x8_t specialCase = vceqq_s16(newPos, specialValueSigned);
			newPos = vbslq_s16(specialCase, vdupq_n_s16(0), newPos);
	
			// Store results back into newMessage
			for (int j = 0; j < 8; j++) {
				size_t index = i + j;
				if (index >= len || letterPositions[j] == 0) continue;
				int16_t newPosArray[8];
				vst1q_s16(newPosArray, newPos);  // Store vector into array
	
				for (int j = 0; j < 8; j++) {
					size_t index = i + j;
					if (index >= len || letterPositions[j] == 0) continue;
					newMessage[index] = characters[static_cast<size_t>(newPosArray[j])];
				}
			}
		}
#else
		for (unsigned long long i = 0; i < message.size(); i++) {
			string keyContentsInt;
			keyContentsInt = keyContents[2*i];
			size_t letterPos = characters.find(message[i]);
			if (letterPos == string::npos) {
				newMessage += message[i];
			}
			if (letterPos != string::npos) {
				int newPosition;
				newPosition = letterPos - 10*stoi(keyContentsInt);
				keyContentsInt = keyContents[i+1];
				newPosition = newPosition - stoi(keyContentsInt);
				if (newPosition < 0) {
					newPosition = characters.size() + newPosition;
				}
				if (newPosition == 92) {
					newPosition = 0;
				}
				int newCharacter = characters[newPosition];
				newMessage += newCharacter;
			}
		}
#endif
		cout << "Your decrypted message is '" + newMessage + "'\nPress ENTER to exit" << endl;
		cin.ignore();
		cin.get();
		return 0;
	}
	return 0;
}