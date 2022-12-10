#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include "split.h"
using namespace std;
void split(const string& s, char delim, vector<string>& elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}